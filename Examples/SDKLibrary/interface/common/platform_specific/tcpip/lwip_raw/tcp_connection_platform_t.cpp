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

#if (UASDK_INCLUDE_TCPIP_LWIP_RAW > 0)

#define UA_SERVER_PRINTF

namespace uasdk
{

Status_t TcpConnectionPlatform_t::Initialise(struct tcp_pcb *pcb_, IntrusiveList_t<TcpConnectionPlatform_t>& connections_)
{
  /* Create a unique id for this connection that we can pass to the UA Server as
   * a reference for the TCP/IP connection.
   */

  pcb = pcb_;
  connections = &connections_;
  return rxBuffer.Initialise(1500);
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
  tcp_arg(pcb, NULL);
  tcp_sent(pcb, NULL);
  tcp_recv(pcb, NULL);
  tcp_close(pcb);
  coreConnection.reset();
  connections->RemoveSpecific(*this);
  return OpcUa_Good;
}

Status_t TcpConnectionPlatform_t::Send(IntrusivePtr_t<const IBuffer_t> buffer)
{
  if (!buffer.is_set())
  {
    return OpcUa_GoodCallAgain;
  }

  uint32_t bytesToSend = buffer->DataUnread();

  if (bytesToSend > 0)
  {
    uint32_t length_to_send = bytesToSend;
    uint32_t max_to_send = tcp_sndbuf(pcb);

    if (max_to_send < length_to_send)
    {
      length_to_send = max_to_send;
    }

    if (length_to_send > 0)
    {
      tcp_write(pcb, buffer->ReadAddress(), length_to_send, TCP_WRITE_FLAG_COPY);
      tcp_sent(pcb, opcua_sent);
      pcb->flags |= TF_NODELAY;
      tcp_output(pcb);
    }
    else
    {
      tcp_sent(pcb, NULL);
    }

    UA_SERVER_PRINTF("UAServer_Send_data_callback() sent %lu bytes", length_to_send);

    buffer->IncrementReadIndex(length_to_send);
    uint32_t bytesNotSent = buffer->DataUnread();
    if (bytesNotSent == 0)
    {
      UA_SERVER_PRINTF("server: Sent %u bytes to clientd\n", length_to_send);
      return OpcUa_GoodCallAgain;
    }
    else
    {
      UA_SERVER_PRINTF("server: Sent %u bytes to client (less than requested)\n", length_to_send);
      return OpcUa_BadWouldBlock;
    }
  }
  return OpcUa_GoodCallAgain;
}

Status_t TcpConnectionPlatform_t::Receive(IBuffer_t& buffer)
{
  int32_t bytes_received = rxBuffer.DataUnread();
  if (bytes_received > 0)
  {
    int32_t bytesToCopy = bytes_received;
    if (bytesToCopy > (int32_t)buffer.SpaceRemaining())
    {
      bytesToCopy = buffer.SpaceRemaining();
    }

    buffer.CopyFrom(rxBuffer, bytesToCopy);
    if (rxBuffer.DataUnread() == 0)
    {
      rxBuffer.Clear();
    }

    if (buffer.SpaceRemaining() > 0)
    {
      return OpcUa_Good;
    }
    else
    {
      return OpcUa_GoodCallAgain;
    }
  }
  else
  {
    return OpcUa_BadNoData;
  }
	return OpcUa_Good;
}

void TcpConnectionPlatform_t::NotifyCoreWhenNetworkReady(void)
{
}

void TcpConnectionPlatform_t::NotifyCoreWhenDataAvailable(void)
{
}

Status_t TcpConnectionPlatform_t::DataAvailable(void)
{
  if (coreConnection.is_set())
  {
    return coreConnection->DataAvailable();
  }
  return OpcUa_Good;
}

Status_t TcpConnectionPlatform_t::NetworkReady(void)
{
  if (coreConnection.is_set())
  {
    return coreConnection->NetworkReady();
  }
  return OpcUa_Good;
}


}

#endif //(UASDK_INCLUDE_TCPIP_LWIP_RAW > 0)


