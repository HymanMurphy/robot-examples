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

#include "tcp_connection_platform_t.h"

#if (UASDK_INCLUDE_SERVER)
#if (UASDK_INCLUDE_TCPIP_C_API > 0)

#include "ua_server.h"
#include "ibuffer_t.h"

//#define UA_SERVER_PRINTF
#define UA_SERVER_PRINTF Print_time(); printf

namespace uasdk
{

Status_t TcpConnectionPlatform_t::Initialise(uint64_t connectionId_,
    IntrusiveList_t<TcpConnectionPlatform_t>& connections_)
{
  connectionId = connectionId_;
  connections = &connections_;
  return OpcUa_Good;
}


void* TcpConnectionPlatform_t::Context(void)
{
  return context;
}

void TcpConnectionPlatform_t::Context(void* value)
{
  context = value;
}


void TcpConnectionPlatform_t::NetworkTxAllowed(bool value)
{
  networkTxAllowed = value;
}

void TcpConnectionPlatform_t::NetworkRxAllowed(bool value)
{
  networkRxAllowed = value;
}

uint64_t TcpConnectionPlatform_t::ConnectionId(void)
{
  return connectionId;
}

const IPEndpoint_t& TcpConnectionPlatform_t::IPEndpoint(void) const
{
  static RefCount_t<DummyIPEndpoint_t> dummy;
  return dummy;
}

void TcpConnectionPlatform_t::CoreOpened(IntrusivePtr_t<ITcpConnectionCore_t> connection)
{
  if (!coreConnection.is_set())
  {
    coreConnection = connection;
  }
}

Status_t TcpConnectionPlatform_t::Close(void)
{
  UAServer_Callback_close_connection(connectionId);
  coreConnection.reset();
  connections->RemoveSpecific(*this);
  return OpcUa_Good;
}

Status_t TcpConnectionPlatform_t::Send(IntrusivePtr_t<const IBuffer_t> buffer)
{
  if (!networkTxAllowed)
  {
    return OpcUa_BadWouldBlock;
  }

  if (!buffer.is_set())
  {
    return OpcUa_GoodCallAgain;
  }

  uint32_t bytesToSend = buffer->ContiguousDataUnread();
  bool_t acceptsMoreData = TRUE;

  if (bytesToSend > 0)
  {
    uint32_t noOfBytesSent = 0;

    do
    {
      acceptsMoreData = UAServer_Callback_data_send(
        context,
        connectionId,
        buffer->ReadAddress(),
        bytesToSend,
        &noOfBytesSent);

      if (noOfBytesSent > bytesToSend)
      {
        return OpcUa_BadUnexpectedError;
      }

      buffer->IncrementReadIndex(noOfBytesSent);
      bytesToSend = buffer->ContiguousDataUnread();

    } while ((acceptsMoreData == TRUE) && (bytesToSend > 0));
  }

  if (acceptsMoreData == TRUE)
  {
    return OpcUa_GoodCallAgain;
  }
  else
  {
    return OpcUa_Good;
  }
}

Status_t TcpConnectionPlatform_t::Receive(IBuffer_t& buffer)
{
  if (!networkRxAllowed)
  {
    return OpcUa_BadNoData;
  }

  uint32_t bytesToReceive = buffer.ContiguousSpaceRemaining();
  bool_t moreDataAvailable = FALSE;

  if (bytesToReceive > 0)
  {
    uint32_t noOfBytesReceived = 0;

    moreDataAvailable = UAServer_Callback_data_receive(
      context,
      connectionId,
      buffer.WriteAddress(),
      bytesToReceive,
      &noOfBytesReceived);

    if (noOfBytesReceived > bytesToReceive)
    {
      return OpcUa_BadUnexpectedError;
    }

    buffer.IncrementWriteIndex(noOfBytesReceived);

    if (moreDataAvailable == TRUE)
    {
      return OpcUa_GoodCallAgain;
    }
    else
    {
      return OpcUa_Good;
    }
  }
  return OpcUa_GoodCallAgain;
}

void TcpConnectionPlatform_t::NotifyCoreWhenDataAvailable(void)
{
  notifyWhenDataAvailable = true;
}

void TcpConnectionPlatform_t::NotifyCoreWhenNetworkReady(void)
{
}

uasdk::Status_t TcpConnectionPlatform_t::CloseFromPlatform(void)
{
  if (coreConnection.is_set())
  {
    return coreConnection->Close();
  }
  return OpcUa_Good;
}


uasdk::Status_t TcpConnectionPlatform_t::DataAvailable(void)
{
  if (coreConnection.is_set() && notifyWhenDataAvailable)
  {
    notifyWhenDataAvailable = false;
    return coreConnection->DataAvailable();
  }
  return OpcUa_Good;
}


uasdk::Status_t TcpConnectionPlatform_t::NetworkReady(void)
{
  if (coreConnection.is_set())
  {
    return coreConnection->NetworkReady();
  }
  return OpcUa_Good;
}

}

#endif //UASDK_INCLUDE_TCPIP_C_API
#endif //(UASDK_INCLUDE_SERVER)
