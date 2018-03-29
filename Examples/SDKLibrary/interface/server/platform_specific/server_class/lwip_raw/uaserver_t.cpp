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

#if (UASDK_INCLUDE_SERVER_LWIP_RAW > 0)

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
#include "tcp_connection_platform_t.h"

namespace uasdk
{

static IntrusivePtr_t<UAServer_t> server;
static IntrusivePtr_t<IServerCore_t> serverCore;
static IntrusivePtr_t<IntrusiveList_t<TcpConnectionPlatform_t> > tcpConnections;

extern "C"
{

static void opcua_err(void *arg, err_t err)
{
  /* An error occurred */
  IntrusivePtr_t<TcpConnectionPlatform_t> connection = (TcpConnectionPlatform_t*)arg;

  LWIP_UNUSED_ARG(err);

  if (connection.is_set())
  {
    connection->Close();
  }
}

static err_t opcua_recv(void *arg, struct tcp_pcb *pcb, struct pbuf *p, err_t err)
{
  /* Incoming data available to receive */

  Status_t status = 0;
  IntrusivePtr_t<TcpConnectionPlatform_t> connection = (TcpConnectionPlatform_t*)arg;
  err_t return_code = ERR_OK;

  if ((err == ERR_OK) && (p != NULL) && connection.is_set())
  {
    struct pbuf *pbuf = p;

    if (connection->rxBuffer.IsEmpty())
    {
      uint32_t total_length = pbuf->tot_len;

      while (connection->rxBuffer.DataUnread() < total_length)
      {
        UASDK_ASSERT(pbuf->len > 0);
        UASDK_ASSERT(connection->rxBuffer.Write_index() >= 0);
        UASDK_ASSERT(connection->rxBuffer.Read_index() == 0);
        UASDK_ASSERT(connection->rxBuffer.Write_index() < TCP_WND);
        UASDK_ASSERT(pbuf->len < (TCP_WND - connection->rxBuffer.Write_index()));

        connection->rxBuffer.Write(pbuf->payload, pbuf->len);

        pbuf = pbuf->next;
      }

      /* Inform TCP that we have taken the data. */
      tcp_recved(pcb, p->tot_len);
    }
    else
    {
      return_code = ERR_BUF;
    }

    status = connection->DataAvailable();
    if (status.IsBad())
    {
      if (connection->Close().IsBad())
      {
        tcp_abort(pcb);
      }
    }

    if ((return_code == ERR_OK) && p)
    {
      pbuf_free(p);
    }
  }
  else
  {
    if (p)
    {
      pbuf_free(p);
    }
    if (connection->Close().IsBad())
    {
      tcp_abort(pcb);
    }
  }

  return return_code;
}

static err_t opcua_accept(void *arg, struct tcp_pcb *pcb, err_t err)
{
  LWIP_UNUSED_ARG(arg);
  LWIP_UNUSED_ARG(err);

  /* New TCP connection received */
  IntrusivePtr_t<TcpConnectionPlatform_t> connection = new SafeRefCount_t<TcpConnectionPlatform_t>();
  if (!connection.is_set())
  {
    return ERR_MEM;
  }

  /* Initialize the structure. */
  connection->Initialise(pcb, *tcpConnections);
  Status_t status = tcpConnections->AddToTail(*connection);
  if (status.IsBad())
  {
    return ERR_MEM;
  }
  status = serverCore->TCPNewConnectionReceived(connection);
  if (status.IsBad())
  {
    return ERR_MEM;
  }

  server->Poll();

  /* Tell TCP that this is the structure we wish to be passed for our callbacks. */
  tcp_arg(pcb, connection.get());

  /* Tell TCP that we wish to be informed of incoming data by a call to the opcua_recv() function. */
  tcp_recv(pcb, opcua_recv);

  tcp_err(pcb, opcua_err);

  return ERR_OK;
}

err_t opcua_sent(void *arg, struct tcp_pcb *pcb, u16_t len)
{
  /* Outgoing data sent */

  TcpConnectionPlatform_t* connection = 0;
  connection = (TcpConnectionPlatform_t*)arg;

  LWIP_UNUSED_ARG(len);

  if(!arg)
  {
    return ERR_OK;
  }

  Status_t status = connection->NetworkReady();
  if (status.IsBad())
  {
    if (connection->Close().IsBad())
    {
      tcp_abort(pcb);
      return ERR_RST;
    }
  }

  tcp_sent(pcb, NULL);

  return ERR_OK;
}

} //extern "C"

//namespace uasdk
//{

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

UAServer_t::UAServer_t() : listenerPCB(0)
{
  lastPollTimeMs = UASDK_millisecond();
  nextPollTimeMs = lastPollTimeMs + 50;
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

  Status_t status;
  core = IServerCore_t::Create(status);
  if (!core.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  serverCore = core;
  server = this;
  tcpConnections = connections;

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
  status = callbackOpComplete->WaitForResult();
  if (status.IsBad())
  {
    return status;
  }

  IntrusivePtr_t<IServerConfiguration_t> configuration = core->GetConfiguration(status);
  if (!configuration.is_set())
  {
    return status;
  }
  uint32_t tcpPort = configuration->ServerEndpointTCPPort();

  listenerPCB = tcp_new();
  tcp_bind(listenerPCB, IP_ADDR_ANY, tcpPort);
  listenerPCB = tcp_listen(listenerPCB);
  tcp_accept(listenerPCB, opcua_accept);
  return OpcUa_Good;
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

  return callbackOpComplete->WaitForResult();
}

uasdk::Status_t UAServer_t::Terminate(void)
{
  Status_t result;

  serverCore.reset();
  tcpConnections.reset();

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
  Status_t status;

  if (!core.is_set())
  {
    return OpcUa_BadConfigurationError;
  }

  IntrusivePtr_t<IServerConfiguration_t> configuration = core->GetConfiguration(status);
  if (!configuration.is_set())
  {
    return status;
  }

  uint32_t serverCyclicRateInMs = configuration->ServerCyclicRateInMs();

  if (IsServerPollDue(&lastPollTimeMs, &nextPollTimeMs, serverCyclicRateInMs))
  {
    timerProvider->Poll();
  }

  do
  {
    status = threadPool->Operate();
  }
  while (status.IsGood());

  return OpcUa_Good;
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

}

#endif //UASDK_INCLUDE_SERVER_LWIP_RAW
