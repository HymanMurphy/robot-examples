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

#if (UASDK_INCLUDE_TCPIP_WINDOWS_LINUX_SOCKETS_SELECT_ST > 0)

#ifdef _WIN32

#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

#define sleep(SltX) taskDelay(SltX*sysClkRateGet())
#define suseconds_t long
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

#define SOCKET int

#else
#error This module is implemented for Windows and Linux only
#endif

#include <stdio.h>
#include <string.h>

#include "ibuffer_t.h"

namespace uasdk
{
#ifdef _WIN32
  Status_t TcpConnectionPlatform_t::Initialise(SOCKET socket_, fd_set& master_fds_, fd_set& read_fds_, fd_set& write_fds_,
    IntrusiveList_t<TcpConnectionPlatform_t>& connections_)
#else
Status_t TcpConnectionPlatform_t::Initialise(int socket_, fd_set& master_fds_, fd_set& read_fds_, fd_set& write_fds_,
                                             IntrusiveList_t<TcpConnectionPlatform_t>& connections_)
#endif
{
  socket = socket_;
  master_fds = &master_fds_;
  read_fds = &read_fds_;
  write_fds = &write_fds_;
  connections = &connections_;
  return OpcUa_Good;
}
#ifdef _WIN32
SOCKET
#else
int 
#endif
TcpConnectionPlatform_t::Socket(void)
{
  return socket;
}

const IPEndpoint_t& TcpConnectionPlatform_t::IPEndpoint(void) const
{
  static SafeRefCount_t<DummyIPEndpoint_t> dummy;
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
	CONNECTION_LOG_INFO("TcpConnectionPlatform_t::Close() socket %d", socket);

  close(socket);
  FD_CLR(socket, master_fds);
  FD_CLR(socket, read_fds);
  FD_CLR(socket, write_fds);
  if (coreConnection.is_set())
  {
    coreConnection->Closed();
    coreConnection.reset();
  }
  if (connections)
  {
    connections->RemoveSpecific(*this);
  }
  return OpcUa_Good;
}

IntrusivePtr_t<ITcpConnectionCore_t> TcpConnectionPlatform_t::CoreConnection(void)
{
  return coreConnection;
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
    int32_t bytes_sent = send(socket, (const char*)buffer->ReadAddress(), bytesToSend, MSG_DONTWAIT);
    if (bytes_sent < 0)
    {
#ifdef _WIN32
      int error = WSAGetLastError();
      if (error == WSAEWOULDBLOCK)
#else
      CONNECTION_LOG_ERROR("send() error, errno: %d", errno);
      if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
#endif
      {
        CONNECTION_LOG_INFO("send would block");
        return OpcUa_BadWouldBlock;
      }
#ifndef _WIN32
      else if (errno == EINTR)
      {
        /* Interrupted. Ask SDK to try again */
        return OpcUa_GoodCallAgain;
      }
#endif
      else
      {
        CONNECTION_LOG_ERROR("send failed, closing connection");
        UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
      }
    }
    else
    {
      buffer->IncrementReadIndex(bytes_sent);
      uint32_t bytesNotSent = buffer->DataUnread();
      if (bytesNotSent == 0)
      {
        CONNECTION_LOG_INFO("Sent %u bytes on socket: %d", bytes_sent, socket);
        return OpcUa_GoodCallAgain;
      }
      else
      {
        CONNECTION_LOG_INFO("Sent %u bytes (less than requested)on socket: %d", bytes_sent, socket);
        return OpcUa_BadWouldBlock;
      }
    }
  }
  return OpcUa_GoodCallAgain;
}

Status_t TcpConnectionPlatform_t::Receive(IBuffer_t& buffer)
{
  int32_t bytes_received = 0;

  bytes_received = recv(
      socket,
      (char*)buffer.WriteAddress(),
      buffer.SpaceRemaining(),
      0);

  CONNECTION_LOG_INFO("Received %d bytes on socket: %d", bytes_received, socket);

  if (bytes_received <= 0)
  {
    /* got error or connection closed by client */
    if(bytes_received == 0)
    {/* connection closed */
      CONNECTION_LOG_INFO("socket %u hung up", socket);
      UASDK_RETURN_BAD_STATUS(OpcUa_BadConnectionClosed);
    }
    else
    {
#ifndef _WIN32
      CONNECTION_LOG_INFO("recv() error, errno: %d", errno);
      if (errno == EINTR)
      {
        /* Interrupted. Ask SDK to try again */
        return OpcUa_GoodCallAgain;
      }
      else
#endif
      {
        CONNECTION_LOG_INFO("recv() error");
      }
    }
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }
  else
  {
    buffer.IncrementWriteIndex(bytes_received);
    if (buffer.SpaceRemaining() > 0)
    {
      return OpcUa_Good;
    }
    else
    {
      return OpcUa_GoodCallAgain;
    }
  }
}

void TcpConnectionPlatform_t::NotifyCoreWhenNetworkReady(void)
{
  CONNECTION_LOG_INFO("NotifyCoreWhenNetworkReady()");

  FD_SET(socket, write_fds);
}

void TcpConnectionPlatform_t::NotifyCoreWhenDataAvailable(void)
{
  CONNECTION_LOG_INFO("NotifyCoreWhenDataAvailable()");

  FD_SET(socket, read_fds);
}


}

#endif //UASDK_INCLUDE_TCPIP_WINDOWS_LINUX_SOCKETS_SELECT_ST
