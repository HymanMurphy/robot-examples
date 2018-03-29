/* ----------------------------------------------------------------------------------------
                                        COPYRIGHT (c) 2009 - 2017
                                         HONEYWELL INC.,
                                        ALL RIGHTS RESERVED

            This software is a copyrighted work and/or information protected as a trade
            secret. Legal rights of Honeywell Inc. in this software are distinct from
            ownership of any medium in which the software is embodied. Copyright or trade
            secret notices included must be reproduced in any copies authorized by
            Honeywell Inc. The information in this software is subject to change without
            notice and should not be considered as a commitment by Honeywell Inc.
---------------------------------------------------------------------------------------- */

#include "uaserver_t.h"

#if (UASDK_INCLUDE_SERVER > 0)
#if (UASDK_INCLUDE_SERVER_WINDOWS_LINUX_ST > 0)

#include "icertificate_private_key_password_provider_t.h"
#include "icertificate_rejected_list_listener_t.h"
#include "ilog_listener_t.h"
#include "imonitored_item_listener_t.h"
#include "inode_method_handler_t.h"
#include "inode_value_attribute_reader_writer_t.h"
#include "ioperation_complete_listener_t.h"
#include "iregister_node_listener_t.h"
#include "iserver_state_listener_t.h"
#include "ithread_pool_t.h"
#include "itimer_provider_t.h"
#include "itransaction_listener_t.h"
#include "iuser_permissions_provider_t.h"
#include "iuser_permissions_provider_t.h"
#include "safe_ref_count_t.h"
#include "iserver_configuration_t.h"
#include "opcua_build_info_t.h"
#include "opcua_message_security_mode_t.h"
#include "opcua_user_token_policy_t.h"
#include "iaddress_space_t.h"
#include "certificate_generation_parameters_t.h"
#include "iserver_core_t.h"
#include "intrusive_ptr_t.h"
#include "irunnable_t.h"
#include "timer_provider_t.h"
#include "thread_pool_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)
#include "event_helper_t.h"
#endif

namespace uasdk
{

class OperationCompleteListener_t : public IOperationCompleteListener_t, public Allocatable_t
{
private:
  IntrusivePtr_t<IThreadPool_t> threadPool;
  bool isComplete;
  Status_t result;

public:
  OperationCompleteListener_t() : isComplete(false){}

  Status_t Initialise(IntrusivePtr_t<IThreadPool_t>& threadPool_)
  {
    UASDK_ASSERT(threadPool_.is_set());
    UASDK_RETURN_UNEXPECTED_IF_NULL(threadPool_);
    threadPool = threadPool_;
    return OpcUa_Good;
  }

  Status_t WaitForResult(void)
  {
    UASDK_RETURN_UNEXPECTED_IF_NULL(threadPool);

    Status_t status;
    do
    {
      if (isComplete)
      {
        return result;
      }
      status = threadPool->Operate();
    }
    while (status.IsGood());

    return status;
  }

  virtual void OperationComplete(Status_t result_)
  {
    result = result_;
    isComplete = true;
  }

};

bool UAServer_t::IsServerPollDue(uint32_t* last_poll_time_ms, uint32_t* next_poll_time_ms, uint32_t serverCyclicRate)
{
  bool result = false;
  const int64_t INTERVAL = serverCyclicRate;
  int64_t time_now = UASDK_millisecond();
  int64_t last_poll_time = 0;
  if (last_poll_time_ms)
  {
    last_poll_time = *last_poll_time_ms;
  }

  int64_t next_poll_time = last_poll_time + INTERVAL;

  if (time_now < last_poll_time)
  {
    time_now += UINT32_MAX;
  }
  if (next_poll_time < last_poll_time)
  {
    next_poll_time += UINT32_MAX;
  }

  if (time_now >= next_poll_time)
  {
    result = true;

    do
    {
      next_poll_time += INTERVAL;
    } while (next_poll_time < time_now);

    if (last_poll_time_ms)
    {
      *last_poll_time_ms = (next_poll_time - INTERVAL) % UINT32_MAX;
    }

    if (next_poll_time_ms)
    {
      *next_poll_time_ms = next_poll_time % UINT32_MAX;
    }
  }

  return result;
}

suseconds_t UAServer_t::PollDelay(uint32_t last_poll_time_ms, uint32_t next_poll_time_ms)
{
  int64_t time_now = UASDK_millisecond();
  int64_t last_poll_time = last_poll_time_ms;
  int64_t next_poll_time = next_poll_time_ms;
  int64_t delay = 1;

  if (time_now < last_poll_time)
  {
    time_now += UINT32_MAX;
  }
  if (next_poll_time < last_poll_time)
  {
    next_poll_time += UINT32_MAX;
  }

  if (time_now < next_poll_time)
  {
    delay = (next_poll_time - time_now) * 1000;
  }

  return (suseconds_t)delay;
}

uasdk::IntrusivePtr_t<uasdk::TcpConnectionPlatform_t> UAServer_t::GetConnection(SOCKET fd)
{
  connections.ResetCurrent();
  IntrusivePtr_t<TcpConnectionPlatform_t> connection;

  do
  {
    connection = connections.GetNext();
    if (connection.is_set())
    {
      if (connection->Socket() == fd)
      {
        return connection;
      }
    }
  } while (connection.is_set());
  return connection;
}

SOCKET UAServer_t::Start_listener(uint32_t port)
{
  SOCKET listener;

  /* server address */
  struct sockaddr_in serveraddr;

#ifdef __linux
  int yes = 1;
#else
  char yes = 1;
#endif

  /* get the listener */
  if ((listener = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    CONNECTION_LOG_ERROR("Server-socket() error");
    return -1;
  }

  CONNECTION_LOG_INFO("Server-socket() is OK...");

  /*"address already in use" error message */
  if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
  {
    CONNECTION_LOG_ERROR("Server-setsockopt() error");
    return -1;
  }

  CONNECTION_LOG_INFO("Server-setsockopt() is OK...");

  /* bind */
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = INADDR_ANY;
  serveraddr.sin_port = htons(port);
  memset(&(serveraddr.sin_zero), '\0', 8);

  if (bind(listener, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1)
  {
    CONNECTION_LOG_ERROR("Server-bind() error");
    return -1;
  }

  CONNECTION_LOG_INFO("Server-bind() is OK...");

  /* listen */
  if (listen(listener, 10) == -1)
  {
    CONNECTION_LOG_ERROR("Server-listen() error!");
    return -1;
  }

  CONNECTION_LOG_INFO("Server-listen() is OK...");

  return listener;
}

UAServer_t::UAServer_t()
{
  listener = -1;
  fdmax = 0;
  FD_ZERO(&master);
  FD_ZERO(&master_read_fds);
  FD_ZERO(&master_write_fds);

  last_poll_time_ms = UASDK_millisecond();
  next_poll_time_ms = last_poll_time_ms + 50;
}

IntrusivePtr_t<IServerConfiguration_t> UAServer_t::CreateConfiguration(Status_t& result)
{
  return IServerCore_t::CreateConfiguration(result);
}

uasdk::IntrusivePtr_t<uasdk::IXmlNodesetIO_t> UAServer_t::CreateXmlNodesetIO(bool doNotAllowDuplicateNodeId, Status_t& result)
{
  return IServerCore_t::CreateXmlNodesetIO(doNotAllowDuplicateNodeId, result);
}

uasdk::IntrusivePtr_t<uasdk::IAddressSpace_t> UAServer_t::CreateAddressSpace(uint32_t hashTableNoOfBuckets, Status_t& result)
{
  return IServerCore_t::CreateAddressSpace(hashTableNoOfBuckets, result);
}

uasdk::IntrusivePtr_t<uasdk::IAddressSpace_t> UAServer_t::CreateAddressSpace(Status_t& result)
{
  return IServerCore_t::CreateAddressSpace(result);
}

uasdk::Status_t UAServer_t::CreateAllocator(uint8_t* buffer, uint32_t bufferLengthInBytes, uint32_t maxAllocationSizeInBytes)
{
  return IServerCore_t::CreateAllocator(buffer, bufferLengthInBytes, maxAllocationSizeInBytes);
}

/*
 * Control methods
 */
Status_t UAServer_t::Initialise(IntrusivePtr_t<IServerConfiguration_t> configuration)
{
  #if (UASDK_USE_SYSTEM_HEAP == 0)
    if (!Allocatable_t::Allocator())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadConfigurationError);
    }
  #endif

#ifdef _WIN32
    {
      WORD wVersionRequested;
      WSADATA wsaData;
      int err;

      /* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
      wVersionRequested = MAKEWORD(2, 2);

      err = WSAStartup(wVersionRequested, &wsaData);
      if (err != 0) {
        /* Tell the user that we could not find a usable */
        /* Winsock DLL.                                  */
        return OpcUa_BadTcpInternalError;
      }
    }
#endif

  Status_t status;
  core = IServerCore_t::Create(status);
  if (!core.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  threadPool = new SafeRefCount_t<ThreadPool_t>();
  if (!threadPool.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  IntrusivePtr_t<TimerProvider_t> timerProvider_ = new SafeRefCount_t<TimerProvider_t>();
  if (!timerProvider_.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
    status = timerProvider_->Initialise();
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  timerProvider = timerProvider_;

  IntrusivePtr_t<OperationCompleteListener_t> callbackOpComplete = new SafeRefCount_t<OperationCompleteListener_t>();
  if (!callbackOpComplete.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  callbackOpComplete->Initialise(threadPool);

  status = core->Initialise(configuration, threadPool, timerProvider, callbackOpComplete);
  if (status.IsBad())
  {
    return status;
  }

  status = callbackOpComplete->WaitForResult();
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t UAServer_t::Start(const String_t& license)
{
  UASDK_UNUSED(license);
  IntrusivePtr_t<OperationCompleteListener_t> callbackOpComplete = new SafeRefCount_t<OperationCompleteListener_t>();
  if (!callbackOpComplete.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  callbackOpComplete->Initialise(threadPool);

  Status_t status = core->Start(callbackOpComplete);
  if (status.IsBad())
  {
    return status;
  }

  status =  callbackOpComplete->WaitForResult();
  if (status.IsBad())
  {
  	return status;
  }

#if (UASDK_INCLUDE_EVENTS > 0)
    IntrusivePtr_t<IServerConfiguration_t> configuration = core->GetConfiguration(status);
		if (status.IsBad() || !configuration.is_set())
		{
			UASDK_RETURN_BAD_STATUS(OpcUa_BadConfigurationError);
		}

    if (configuration->EventTypesActivationStatus() & ENABLE_SYSTEM_STATUS_CHANGE_EVENT_TYPE)
    {
      status = FireSystemStatusChangeEvent(ServerState_t::OPCUA_SERVER_STATE_RUNNING);
      if (status.IsBad())
      {
				//Log it
      }
    }
#endif //UASDK_INCLUDE_EVENTS

    return status;
  }

Status_t UAServer_t::Stop(void)
{
  IntrusivePtr_t<OperationCompleteListener_t> callbackOpComplete = new SafeRefCount_t<OperationCompleteListener_t>();
  if (!callbackOpComplete.is_set())
  {
	  UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  callbackOpComplete->Initialise(threadPool);

  Status_t status = core->Stop(callbackOpComplete);
  if (status.IsBad())
  {
	  return status;
  }

#if (UASDK_INCLUDE_EVENTS > 0)
  Status_t result;
    IntrusivePtr_t<IServerConfiguration_t> configuration = core->GetConfiguration(result);
		if (result.IsBad() || !configuration.is_set())
		{
			UASDK_RETURN_BAD_STATUS(OpcUa_BadConfigurationError);
		}

    if (configuration->EventTypesActivationStatus() & ENABLE_SYSTEM_STATUS_CHANGE_EVENT_TYPE)
    {
      result = FireSystemStatusChangeEvent(ServerState_t::OPCUA_SERVER_STATE_SHUTDOWN);
      if (result.IsBad())
      {
				//Log it
      }
    }
#endif //UASDK_INCLUDE_EVENTS

    return callbackOpComplete->WaitForResult();
  }

uasdk::Status_t UAServer_t::Terminate(void)
{
	Status_t result;
  if (listener > 0)
  {
    close(listener);
  }

  //Server is shutting down so close all sockets and signal server core
  IntrusivePtr_t<TcpConnectionPlatform_t> connection = connections.GetFirst();
  while (connection.is_set())
  {
    connection->Close();
    connections.DeleteCurrent();
    connection = connections.GetFirst();
  }

  Status_t status;
  do
  {
    status = threadPool->Operate();
  } while (status.IsGood());

  status = threadPool->Shutdown();
  if (status.IsBad())
  {
    result = status;
  }

  status = timerProvider->Shutdown();
  if (status.IsBad())
  {
    result = status;
  }

  return core->Shutdown();
}

Status_t UAServer_t::Poll(void)
{
  return TcpipRun();
}

/*
 * Configuration methods
 */
IntrusivePtr_t<IServerConfiguration_t> UAServer_t::GetConfiguration(Status_t& result)
{
  if (core.is_set())
  {
    return core->GetConfiguration(result);
  }
  result = OpcUa_BadConfigurationError;
  IntrusivePtr_t<IServerConfiguration_t> empty;
  return empty;
}

/*
 * Security methods
 */
Status_t UAServer_t::SecurityValidateApplicationInstanceCertificate(SecurityPolicy_t securityPolicy)
{
  UASDK_RETURN_UNEXPECTED_IF_NULL(core);
  return core->SecurityValidateApplicationInstanceCertificate(securityPolicy);
}

Status_t UAServer_t::SecurityCreateSelfSignedApplicationInstanceCertificate(
    IntrusivePtr_t<const CertificateGenerationParameters_t> parameters)
{
  UASDK_RETURN_UNEXPECTED_IF_NULL(core);

  IntrusivePtr_t<OperationCompleteListener_t> callbackOpComplete = new SafeRefCount_t<OperationCompleteListener_t>();
  if (!callbackOpComplete.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  callbackOpComplete->Initialise(threadPool);

  Status_t status = core->SecurityCreateSelfSignedApplicationInstanceCertificate(parameters,
                                                                                 callbackOpComplete);
  if (status.IsBad())
  {
    return status;
  }

  status = callbackOpComplete->WaitForResult();
  return status;
}

Status_t UAServer_t::SecurityCreateCertificateDirectoryStores(void)
{
  UASDK_RETURN_UNEXPECTED_IF_NULL(core);

  IntrusivePtr_t<OperationCompleteListener_t> callbackOpComplete = new SafeRefCount_t<OperationCompleteListener_t>();
  if (!callbackOpComplete.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  callbackOpComplete->Initialise(threadPool);

  Status_t status = core->SecurityCreateCertificateDirectoryStores(callbackOpComplete);
  if (status.IsBad())
  {
    return status;
  }

  status = callbackOpComplete->WaitForResult();
  return status;
}

Status_t UAServer_t::SecurityRefreshApplicationCertificateDirectoryStores(void)
{
  UASDK_RETURN_UNEXPECTED_IF_NULL(core);

  IntrusivePtr_t<OperationCompleteListener_t> callbackOpComplete = new SafeRefCount_t<OperationCompleteListener_t>();
  if (!callbackOpComplete.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  callbackOpComplete->Initialise(threadPool);

  Status_t status = core->SecurityRefreshCertificateDirectoryStores(UA_CERTIFICATE_GROUP_DEFAULT_APPLICATION_GROUP,
                                                                    callbackOpComplete);
  if (status.IsBad())
  {
    return status;
  }

  status = callbackOpComplete->WaitForResult();
  return status;
}

Status_t UAServer_t::SecurityRefreshUserCertificateDirectoryStores(void)
{
  UASDK_RETURN_UNEXPECTED_IF_NULL(core);

  IntrusivePtr_t<OperationCompleteListener_t> callbackOpComplete = new SafeRefCount_t<OperationCompleteListener_t>();
  if (!callbackOpComplete.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  callbackOpComplete->Initialise(threadPool);

  Status_t status = core->SecurityRefreshCertificateDirectoryStores(UA_CERTIFICATE_GROUP_DEFAULT_USER_GROUP,
                                                                    callbackOpComplete);
  if (status.IsBad())
  {
    return status;
  }

  status = callbackOpComplete->WaitForResult();
  return status;
}

Status_t UAServer_t::TcpipRun(void)
{
  /* client address */
  struct sockaddr_in clientaddr;

  /* newly accept()ed socket descriptor */
  SOCKET newfd = 0;

  /* for setsockopt() SO_REUSEADDR, below */
  socklen_t addrlen;

  fd_set write_fds;
  fd_set read_fds;
  fd_set error_fds;

#ifdef __linux
  int i;
#else
  u_int i;
#endif

  Status_t status;
  IntrusivePtr_t<IServerConfiguration_t> configuration = core->GetConfiguration(status);
  UASDK_RETURN_UNEXPECTED_IF_NULL(configuration);
  uint32_t serverCyclicRateInMs = configuration->ServerCyclicRateInMs();
  uint32_t port = configuration->ServerEndpointTCPPort();

  /* select() timeout */
  struct timeval timeout;

  /* get the listener */
  if (listener == -1)
  {
    if ((listener = Start_listener(port)) == -1)
    {
      CONNECTION_LOG_ERROR("Could not start listener");
      return OpcUa_BadTcpInternalError;
    }

    /* add the listener to the master set */
    FD_SET(listener, &master);
    FD_SET(listener, &master_read_fds);

#ifndef _WIN32
    /* keep track of the biggest file descriptor */
    fdmax = listener; /* so far, it's this one*/
#endif

    IsServerPollDue(&last_poll_time_ms, &next_poll_time_ms, serverCyclicRateInMs);
  }

  /* copy it */
  error_fds = master;
  read_fds = master_read_fds;
  write_fds = master_write_fds;

  timeout.tv_sec = 0;
  timeout.tv_usec = PollDelay(last_poll_time_ms, next_poll_time_ms);

  /* Wait until a network event or the polling interval times out */
  if (select(fdmax + 1, &read_fds, &write_fds, &error_fds, &timeout) == -1)
  {
#ifdef _WIN32
    CONNECTION_LOG_ERROR("Tcpip_run(), Server-select() error");
#else
    CONNECTION_LOG_ERROR("Tcpip_run(), Server-select() error, errno: %d", errno);
    if (errno == EINTR)
    {
      return OpcUa_Good;
    }
#endif
  }

  /* Check for errors */
#ifdef _WIN32
  for (i = 0; i < error_fds.fd_count; i++)
  {
    SOCKET fd = error_fds.fd_array[i];
#else
  for (i = 0; i <= fdmax; i++)
  {
    int fd = i;
#endif
    if (FD_ISSET(fd, &error_fds))
    {
      if (fd != listener)
      {
        CONNECTION_LOG_ERROR("server: socket has failed, closing connection");

        IntrusivePtr_t<TcpConnectionPlatform_t> connection = GetConnection(fd);
        if (connection.is_set() && connection->CoreConnection().is_set())
        {
          connection->CoreConnection()->Error(OpcUa_BadConnectionClosed);
          connections.RemoveSpecific(*connection);
        }
      }
      else
      {
        CONNECTION_LOG_ERROR("server: listener has failed, restarting connection");

        close(fd);
        FD_CLR(fd, &master);
        FD_CLR(fd, &master_read_fds);

        if ((listener = Start_listener(port)) == -1)
        {
          CONNECTION_LOG_ERROR("Could not start listener");
          return OpcUa_BadTcpInternalError;
        }

        /* add the listener to the master set */
        FD_SET(listener, &master);
        FD_SET(listener, &master_read_fds);

#ifndef _WIN32
        if (newfd > fdmax)
        { /* keep track of the maximum */
          fdmax = newfd;
        }
#endif
      }
    }
  }

  /* Process new connections */
#ifdef _WIN32
  for (i = 0; i < read_fds.fd_count; i++)
  {
    SOCKET fd = read_fds.fd_array[i];
#else
  for (i = 0; i <= fdmax; i++)
  {
    int fd = i;
#endif
    if (FD_ISSET(fd, &read_fds) && (fd == listener))
    {
      /* handle new connections */
      addrlen = sizeof(clientaddr);

      if ((newfd = accept(listener, (struct sockaddr *)&clientaddr, &addrlen)) == -1)
      {
        CONNECTION_LOG_ERROR("Server-accept() error");
      }
      else
      {
        CONNECTION_LOG_INFO("Server-accept() is OK...");

#ifdef _WIN32
        {
          u_long iMode = 1;
          int iResult = ioctlsocket(newfd, FIONBIO, &iMode);
          if (iResult != NO_ERROR)
          {
            CONNECTION_LOG_ERROR("ioctlsocket failed with error: %ld", iResult);
          }
        }
#else
        int flow_control = fcntl(newfd, F_GETFL);
        if (fcntl(newfd, F_SETFL, O_NONBLOCK | flow_control))
        {
          CONNECTION_LOG_ERROR("fcntl() error");
          close(newfd);
          return OpcUa_BadTcpInternalError;
        }
#endif

        /* If white list is populated check it */
        bool connectPermitted = true;
        IntrusivePtr_t<IServerConfiguration_t> configuration = core->GetConfiguration(status);
        UASDK_RETURN_UNEXPECTED_IF_NULL(configuration);
        if (configuration->IsIPAddressWhiteListInUse())
        {
          ByteString_t octets;
          status = octets.Initialise(sizeof(clientaddr.sin_addr.s_addr));
          if (status.IsBad())
          {
            UASDK_RETURN_BAD_STATUS(status.Value());
          }
          const uint8_t* source = reinterpret_cast<const uint8_t*>(&clientaddr.sin_addr.s_addr);
          status = octets.CopyFrom(source, octets.Length());
          if (status.IsBad())
          {
            UASDK_RETURN_BAD_STATUS(status.Value());
          }
          if (!configuration->IsIPAddressInWhiteList(octets))
          {
            connectPermitted = false;
          }
        }

        if (connectPermitted)
        {
          FD_SET(newfd, &master); /* add to master set */

#ifndef _WIN32
          if (newfd > fdmax)
          { /* keep track of the maximum */
            fdmax = newfd;
          }
          CONNECTION_LOG_INFO("%s: New connection on socket %d", inet_ntoa(clientaddr.sin_addr), newfd);
#endif

          Status_t status;
          IntrusivePtr_t<TcpConnectionPlatform_t> newConnection = new SafeRefCount_t<TcpConnectionPlatform_t>();
          if (newConnection.is_set())
          {
            status = newConnection->Initialise(newfd, master, master_read_fds, master_write_fds, connections);
            if (status.IsGood())
            {
              status = core->TCPNewConnectionReceived(newConnection);
              if (status.IsGood())
              {
                status = connections.AddToTail(*newConnection);
              }
            }
          }
          else
          {
            status = OpcUa_BadOutOfMemory;
          }

          if (status.IsBad())
          {
            IntrusivePtr_t<TcpConnectionPlatform_t> connection = GetConnection(fd);
            if (connection.is_set() && connection->CoreConnection().is_set())
            {
              connection->CoreConnection()->Error(OpcUa_BadConnectionClosed);
            }
            else
            {
              close(newfd);
              FD_CLR(newfd, &master);
            }
            connections.RemoveSpecific(*connection);
            return status;
          }
        }
        else
        {
          close(newfd);
        }

      }
    }
  }

  /* Communicate network ready to core */
#ifdef _WIN32
  for (i = 0; i < write_fds.fd_count; i++)
  {
    SOCKET fd = write_fds.fd_array[i];
#else
  for (i = 0; i <= fdmax; i++)
  {
    int fd = i;
#endif
    if (FD_ISSET(fd, &write_fds))
    {
      FD_CLR(fd, &master_write_fds);

      IntrusivePtr_t<TcpConnectionPlatform_t> connection = GetConnection(fd);
      if (connection.is_set() && connection->CoreConnection().is_set())
      {
#ifndef _WIN32
        CONNECTION_LOG_INFO("NetworkReady() on socket %d", fd);
#endif
        connection->CoreConnection()->NetworkReady();
      }
    }
  }

  /* Communicate data available to core */
#ifdef _WIN32
  for (i = 0; i < read_fds.fd_count; i++)
  {
    SOCKET fd = read_fds.fd_array[i];
#else
  for (i = 0; i <= fdmax; i++)
  {
    int fd = i;
#endif
    if (FD_ISSET(fd, &read_fds) && (fd != listener))
    {
      FD_CLR(fd, &master_read_fds);
      IntrusivePtr_t<TcpConnectionPlatform_t> connection = GetConnection(fd);
      if (connection.is_set() && connection->CoreConnection().is_set())
      {
#ifndef _WIN32
        CONNECTION_LOG_INFO("DataAvailable() on socket %d", fd);
#endif
        connection->CoreConnection()->DataAvailable();
      }
    }
  }

  if (IsServerPollDue(&last_poll_time_ms, &next_poll_time_ms, serverCyclicRateInMs))
  {
    timerProvider->Poll();
  }

  do
  {
    status = threadPool->Operate();
  } while (status.IsGood());

  return OpcUa_Good;
  }

#if (UASDK_INCLUDE_EVENTS > 0)
  Status_t UAServer_t::FireEvent(IntrusivePtr_t<IAttributeAccess_t> event,
																 IntrusivePtr_t<NodeId_t>& eventSource,
                                 IntrusivePtr_t<UtcTime_t>& receiveTime)
  {
  	if (core.is_set())
    {
      return core->FireEvent(event, eventSource, receiveTime);
    }

		UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

	Status_t UAServer_t::FireSystemStatusChangeEvent(ServerState_t::Enum_t state)
	{
		Status_t status;

		//SourceNode
		IntrusivePtr_t<NodeId_t> sourceNodeId = EventHelper_t::GetServerNodeId();

		//SourceName
		IntrusivePtr_t<String_t> sourceName = new SafeRefCount_t<String_t>();
		status = sourceName->CopyFrom("SystemName-LocalHost");
		if (status.IsBad())
		{
			return status;
		}

		//Message
		//Adding Englist Text
		IntrusivePtr_t<ILocalizableText_t> message;
		String_t locale, text;
		locale.CopyFrom(LOCALE_EN);
		if (ServerState_t::OPCUA_SERVER_STATE_RUNNING == state)
		{
			text.CopyFrom("System is running now");
		}
		else if (ServerState_t::OPCUA_SERVER_STATE_SHUTDOWN == state)
		{
			text.CopyFrom("System is shutting down now");
		}

		status = EventHelper_t::AddToLocalizableTextStored(locale, text, message);
		if (status.IsBad())
		{
			return status;
		}
		//Adding French Text
		locale.CopyFrom(LOCALE_FR);
		if (ServerState_t::OPCUA_SERVER_STATE_RUNNING == state)
		{
			text.CopyFrom("Le système est en cours d'exécution maintenant");
		}
		else if (ServerState_t::OPCUA_SERVER_STATE_SHUTDOWN == state)
		{
			text.CopyFrom("Le système est en cours d'arrêt maintenant");
		}

		status = EventHelper_t::AddToLocalizableTextStored(locale, text, message);
		if (status.IsBad())
		{
			return status;
		}
		//Adding German Text
		locale.CopyFrom(LOCALE_GR);
		if (ServerState_t::OPCUA_SERVER_STATE_RUNNING == state)
		{
			text.CopyFrom("System läuft jetzt");
		}
		else if (ServerState_t::OPCUA_SERVER_STATE_SHUTDOWN == state)
		{
			text.CopyFrom("System heruntergefahren wird jetzt");
		}

		status = EventHelper_t::AddToLocalizableTextStored(locale, text, message);
		if (status.IsBad())
		{
			return status;
		}

		// Severity
		IntrusivePtr_t<UInt16_t> severity = new SafeRefCount_t<UInt16_t>();
		if (!severity.is_set())
		{
			return status;
		}
		severity->Value(EventSeverity_t::OPCUA_EVENT_SEVERITY_LOW);

		//Server State
		IntrusivePtr_t<ServerState_t> serverState = new SafeRefCount_t<ServerState_t>();
		if (!serverState.is_set())
		{
			return status;
		}
		serverState->Value() = /*ServerState_t::OPCUA_SERVER_STATE_RUNNING*/state;

		IntrusivePtr_t<SystemStatusChangeEventTypeData_t> systemStatusChangeEvent;
		IntrusivePtr_t<const ArrayUA_t<String_t> > localeIds;//Empty parameter is passed. The below method will take the default values.

		if (!core.is_set())
		{
			UASDK_RETURN_BAD_STATUS(OpcUa_BadConfigurationError);
		}

		IntrusivePtr_t<IServerConfiguration_t> configuration = core->GetConfiguration(status);
		if (status.IsBad() || !configuration.is_set())
		{
			UASDK_RETURN_BAD_STATUS(OpcUa_BadConfigurationError);
		}

		status = EventHelper_t::CreateEventAndSetBaseEventProperties(configuration,
			sourceNodeId,
			sourceName,
			severity->Value(),
			message,
			localeIds,
			systemStatusChangeEvent,
			false);
		systemStatusChangeEvent->SystemState() = serverState;

		if (status.IsBad())
		{
			return status;
		}

		status = FireEvent(systemStatusChangeEvent, systemStatusChangeEvent->SourceNode(), systemStatusChangeEvent->ReceiveTime());
		
		return status;
	}

	Status_t UAServer_t::RegisterAuditEventListener(IntrusivePtr_t<IAuditEventListener_t>& auditEventListener)
	{
		return core->RegisterAuditEventListener(auditEventListener);
	}

#endif //UASDK_INCLUDE_EVENTS

}

#endif //UASDK_INCLUDE_SERVER_WINDOWS_LINUX_ST
#endif //(UASDK_INCLUDE_SERVER > 0)
