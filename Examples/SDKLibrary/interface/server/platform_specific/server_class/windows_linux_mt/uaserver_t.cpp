/* -----------------------------------------------------------------------------------------------------------------
                                        COPYRIGHT (c) 2009 - 2017
                                         HONEYWELL INC.,
                                        ALL RIGHTS RESERVED

            This software is a copyrighted work and/or information protected as a trade
            secret. Legal rights of Honeywell Inc. in this software are distinct from
            ownership of any medium in which the software is embodied. Copyright or trade
            secret notices included must be reproduced in any copies authorized by
            Honeywell Inc. The information in this software is subject to change without
            notice and should not be considered as a commitment by Honeywell Inc.
----------------------------------------------------------------------------------------------------------------- */

#include "opcua_date_time_t.h"
#include "uaserver_t.h"

#if (UASDK_INCLUDE_SERVER > 0)

#if (UASDK_INCLUDE_SERVER_WINDOWS_LINUX_MT > 0)

#ifdef _WIN32

#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

#define sleep(SltX) taskDelay(SltX*sysClkRateGet())
#define close closesocket
#define MSG_DONTWAIT 0

#elif defined __linux

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/time.h>
#include <unistd.h>
#include <errno.h>
#include <cstring>

#define SOCKET int

#else
#error This module is implemented for Windows and Linux only
#endif

#include <future>
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
#include "file_descriptors_t.h"
#include "safe_intrusive_queue_t.h"
#include "opcua_uint64_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)
#include "event_helper_t.h"
#endif

namespace uasdk
{

  class OperationCompleteListener_t : public IOperationCompleteListener_t, public Allocatable_t
  {
  private:
    std::promise<Status_t> opCompletePromise;

  public:
    Status_t WaitForResult(void)
    {
      std::future<Status_t> f = opCompletePromise.get_future();
      f.wait();
      return f.get();
    }

    virtual void OperationComplete(Status_t result)
    {
      opCompletePromise.set_value(result);
    }

  };


  bool UAServer_t::IsPollDue(uint32_t* last_poll_time_ms, uint32_t* next_poll_time_ms, uint32_t serverCyclicRate)
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
      
      if(next_poll_time_ms)
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
      LOG_INFO("Server-socket() error");
      return -1;
    }

    LOG_INFO("Server-socket() is OK...");

    /*"address already in use" error message */
    if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
      LOG_INFO("Server-setsockopt() error");
      return -1;
    }

    LOG_INFO("Server-setsockopt() is OK...");

    /* bind */
    Status_t status;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    serveraddr.sin_port = htons(port);
    memset(&(serveraddr.sin_zero), '\0', 8);

    if (bind(listener, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1)
    {
      LOG_INFO("Server-bind() error");
      return -1;
    }

    LOG_INFO("Server-bind() is OK...");

    /* listen */
    if (listen(listener, 10) == -1)
    {
      LOG_INFO("Server-listen() error!");
      return -1;
    }

    LOG_INFO("Server-listen() is OK...");

    return listener;
  }

  IntrusivePtr_t<TcpConnectionPlatform_t> UAServer_t::GetConnection(IntrusiveList_t<TcpConnectionPlatform_t>& connections, SOCKET fd)
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

  UAServer_t::~UAServer_t()
  {
    quit.Value(true);
    if (tcpipThread.joinable())
    {
      tcpipThread.join();
    }
  }

  IntrusivePtr_t<IServerConfiguration_t> UAServer_t::CreateConfiguration(Status_t& result)
  {
    return IServerCore_t::CreateConfiguration(result);
  }

  uasdk::IntrusivePtr_t<uasdk::IXmlNodesetIO_t> UAServer_t::CreateXmlNodesetIO(bool doNotAllowDuplicateNodeId, Status_t& result)
  {
    return IServerCore_t::CreateXmlNodesetIO(doNotAllowDuplicateNodeId, result);
  }

  uasdk::IntrusivePtr_t<uasdk::IAddressSpace_t> UAServer_t::CreateAddressSpace(Status_t& result)
  {
    return IServerCore_t::CreateAddressSpace(result);
  }

  uasdk::IntrusivePtr_t<uasdk::IAddressSpace_t> UAServer_t::CreateAddressSpace(uint32_t hashTableNoOfBuckets, Status_t& result)
  {
    return IServerCore_t::CreateAddressSpace(hashTableNoOfBuckets, result);
  }

  uasdk::Status_t UAServer_t::CreateAllocator(uint8_t* buffer, uint32_t bufferLengthInBytes, uint32_t maxAllocationSizeInBytes)
  {
    return IServerCore_t::CreateAllocator(buffer, bufferLengthInBytes, maxAllocationSizeInBytes);
  }

  /*
   * Control methods
   */
  Status_t UAServer_t::Initialise(IntrusivePtr_t<IServerConfiguration_t> configuration, uint32_t threadPoolSize)
  {
#if (UASDK_USE_SYSTEM_HEAP == 0)
    if (!Allocatable_t::Allocator())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadConfigurationError);
    }
#endif

    quit.Value(false);

    Status_t status;
    core = IServerCore_t::Create(status);
    if (!core.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }

    IntrusivePtr_t<ThreadPool_t> threadPool_ = new SafeRefCount_t<ThreadPool_t>();
    if (!threadPool_.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }
    status = threadPool_->Initialise(threadPoolSize);
    if (status.IsBad())
    {
      return status;
    }
    threadPool = threadPool_;

    IntrusivePtr_t<TimerProvider_t> timerProvider_ = new SafeRefCount_t<TimerProvider_t>();
    if (!timerProvider_.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }
    status = timerProvider_->Initialise(configuration->ServerCyclicRateInMs());
    if (status.IsBad())
    {
      return status;
    }

    timerProvider = timerProvider_;

    IntrusivePtr_t<OperationCompleteListener_t> callbackOpComplete = new SafeRefCount_t<OperationCompleteListener_t>();
    if (!callbackOpComplete.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }

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

    tcpipThread = std::thread(&UAServer_t::TcpipRun, this, core, timerProvider);
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

    Status_t status = core->Start(callbackOpComplete);
    if (status.IsBad())
    {
      return status;
    }

    status = callbackOpComplete->WaitForResult();
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

			//wait for a while to allow event director send notification to client before shut down
      std::this_thread::sleep_for(std::chrono::seconds(2));
    }
#endif //UASDK_INCLUDE_EVENTS

    return callbackOpComplete->WaitForResult();
  }

  uasdk::Status_t UAServer_t::Terminate(void)
  {
    Status_t result;
    Status_t status = threadPool->Shutdown();
    if (status.IsBad())
    {
      result = status;
    }

    quit.Value(true);
    if (tcpipThread.joinable())
    {
      tcpipThread.join();
    }

    status = timerProvider->Shutdown();
    if (status.IsBad())
    {
      result = status;
    }

    return core->Shutdown();
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

    Status_t status = core->SecurityRefreshCertificateDirectoryStores(UA_CERTIFICATE_GROUP_DEFAULT_USER_GROUP,
      callbackOpComplete);
    if (status.IsBad())
    {
      return status;
    }

    status = callbackOpComplete->WaitForResult();
    return status;
  }

  void UAServer_t::TcpipRun(IntrusivePtr_t<IServerCore_t> core, IntrusivePtr_t<ITimerProvider_t> timerProvider)
  {
    UASDK_RETURN_IF_NULL(core);
    UASDK_RETURN_IF_NULL(timerProvider);

    IntrusivePtr_t<UAServer_t> me = this;
    
    Status_t status;

    IntrusivePtr_t<FileDescriptors_t> fileDescriptors;
    IntrusiveList_t<TcpConnectionPlatform_t> connections;
    IntrusivePtr_t<SafeIntrusiveQueue_t<UInt64_t> > socketsToClose;

    //TODO error handling
    fileDescriptors = new SafeRefCount_t<FileDescriptors_t>();
    if (!fileDescriptors.is_set())
    {
      return;
    }
    status = fileDescriptors->Initialise();
    if (status.IsBad())
    {
      return;
    }

    socketsToClose = new SafeRefCount_t<SafeIntrusiveQueue_t<UInt64_t> >();
    if (!socketsToClose.is_set())
    {
      return;
    }
    status = socketsToClose->Initialise();
    if (status.IsBad())
    {
      return;
    }

    /* maximum file descriptor number */
    int fdmax = 0;

    /* listening socket descriptor */
    SOCKET listener;

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

    UASDK_RETURN_IF_NULL(core->GetConfiguration(status));
    uint32_t serverCyclicRateInMs = core->GetConfiguration(status)->ServerCyclicRateInMs();
    uint32_t port = core->GetConfiguration(status)->ServerEndpointTCPPort();

    uint32_t last_poll_time_ms = UASDK_millisecond();
    uint32_t next_poll_time_ms = last_poll_time_ms + serverCyclicRateInMs;

    /* select() timeout */
    struct timeval timeout;

#ifdef _WIN32
    {
      WORD wVersionRequested;
      WSADATA wsaData;
      int err;

      /* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
      wVersionRequested = MAKEWORD(2, 2);

      err = WSAStartup(wVersionRequested, &wsaData);
      if (err != 0)
      {
        /* Tell the user that we could not find a usable */
        /* Winsock DLL.                                  */
        printf("WSAStartup failed with error: %d\n", err);
        return;
      }
    }
#endif

    /* get the listener */
    if ((listener = Start_listener(port)) == -1)
    {
      CONNECTION_LOG_ERROR("Could not start listener");
      return;
    }

    /* add the listener to the master set */
    fileDescriptors->Add(listener);
    fileDescriptors->AddToRead(listener);

#ifndef _WIN32
    /* keep track of the biggest file descriptor */
    fdmax = listener; /* so far, it's this one*/
#endif

    IsPollDue(&last_poll_time_ms, &next_poll_time_ms, serverCyclicRateInMs);

    /* loop */
    while (quit.Value() == false)
    {
      /* copy it */
      error_fds = fileDescriptors->GetMaster();
      read_fds = fileDescriptors->GetRead();
      write_fds = fileDescriptors->GetWrite();

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
          continue;
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

            IntrusivePtr_t<TcpConnectionPlatform_t> connection = GetConnection(connections, fd);
            if (connection.is_set())
            {
              connection->Error(OpcUa_BadConnectionClosed);
              connections.RemoveSpecific(*connection);
              connection->Delete();
            }
          }
          else
          {
            CONNECTION_LOG_ERROR("server: listener has failed, restarting connection");

            close(fd);
            fileDescriptors->Remove(fd);

            if ((listener = Start_listener(port)) == -1)
            {
              CONNECTION_LOG_WARNING("Could not start listener");
              continue;
            }

            /* add the listener to the master set */
            fileDescriptors->Add(listener);
            fileDescriptors->AddToRead(listener);

#ifndef _WIN32
            if (newfd > fdmax)
            { /* keep track of the maximum */
              fdmax = newfd;
            }
#endif
          }
        }
      }

      /* Close sockets requested by SDK */
      IntrusivePtr_t<UInt64_t> socketToClose = socketsToClose->Pop();
      while (socketToClose.is_set())
      {
#ifdef _WIN32
        close(static_cast<SOCKET>(socketToClose->Value()));
        fileDescriptors->Remove(static_cast<SOCKET>(socketToClose->Value()));
        IntrusivePtr_t<TcpConnectionPlatform_t> connection = GetConnection(connections, static_cast<SOCKET>(socketToClose->Value()));
#else
        close(socketToClose->Value());
        fileDescriptors->Remove(socketToClose->Value());
        IntrusivePtr_t<TcpConnectionPlatform_t> connection = GetConnection(connections, socketToClose->Value());
#endif  //_WIN32
        if (connection.is_set())
        {
          connections.RemoveSpecific(*connection);
          connection->Delete();
        }
        socketToClose = socketsToClose->Pop();
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
              break;
            }
#endif

            /* If white list is populated check it */
            bool connectPermitted = true;
            IntrusivePtr_t<IServerConfiguration_t> configuration = core->GetConfiguration(status);
            UASDK_RETURN_IF_NULL(configuration);
            if (configuration->IsIPAddressWhiteListInUse())
            {
              ByteString_t octets;
              status = octets.Initialise(sizeof(clientaddr.sin_addr.s_addr));
              if (status.IsBad())
              {
                return;
              }
              const uint8_t* source = reinterpret_cast<const uint8_t*>(&clientaddr.sin_addr.s_addr);
              status = octets.CopyFrom(source, octets.Length());
              if (status.IsBad())
              {
                return;
              }
              if (!configuration->IsIPAddressInWhiteList(octets))
              {
                connectPermitted = false;
              }
            }

            if (connectPermitted)
            {
              /* add to master set */
              fileDescriptors->Add(newfd);
              fileDescriptors->AddToRead(newfd);

#ifndef _WIN32
              if (newfd > fdmax)
              { /* keep track of the maximum */
                fdmax = newfd;
              }
#endif
              CONNECTION_LOG_INFO("%s: New connection on socket %d", inet_ntoa(clientaddr.sin_addr), newfd);

              Status_t status;
              IntrusivePtr_t<TcpConnectionPlatform_t> newConnection = new SafeRefCount_t<TcpConnectionPlatform_t>();
              if (newConnection.is_set())
              {
                status = newConnection->Initialise(newfd, fileDescriptors, socketsToClose);
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
                IntrusivePtr_t<TcpConnectionPlatform_t> connection = GetConnection(connections, fd);
                if (connection.is_set())
                {
                  connection->Error(OpcUa_BadConnectionClosed);
                  connections.RemoveSpecific(*connection);
                  connection->Delete();
                }
                else
                {
                  close(newfd);
                  fileDescriptors->Remove(newfd);
                }
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
          fileDescriptors->RemoveFromWrite(fd);

          IntrusivePtr_t<TcpConnectionPlatform_t> connection = GetConnection(connections, fd);
          if (connection.is_set())
          {
            connection->NetworkReady();
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
          IntrusivePtr_t<TcpConnectionPlatform_t> connection = GetConnection(connections, fd);
          if (connection.is_set())
          {
            connection->DataAvailable();
          }
        }
      }

      if (IsPollDue(&last_poll_time_ms, &next_poll_time_ms, serverCyclicRateInMs))
      {
        timerProvider->Poll();
      }

      //Delay for about 1ms so that we do not burn CPU cycles while waiting for data to be consumed
      std::this_thread::sleep_for(std::chrono::milliseconds(1));

    }// while{quit.Value() == false)

    //Close all connections
    IntrusivePtr_t<TcpConnectionPlatform_t> connection;
    do 
    {
      connection = connections.GetFirst();
      if (connection.is_set())
      {
        close(connection->Socket());
        connections.DeleteAtHead();
        connection->Delete();
      }

    } while (connection.is_set());
    
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
      SYSTEM_STATUS_CHANGE_EVENT_SEVERITY,
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

#endif //UASDK_INCLUDE_SERVER_WINDOWS_LINUX_MT
#endif //#if (UASDK_INCLUDE_SERVER > 0)
