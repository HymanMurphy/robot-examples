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

#include "tcp_connection_platform_t.h"

#if (UASDK_INCLUDE_TCPIP_WINDOWS_LINUX_SOCKETS_SELECT_MT > 0)

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

#include "safe_ref_count_t.h"

#include <stdio.h>
#include <string.h>

#include "opcua_uint64_t.h"
#include "ibuffer_t.h"

namespace uasdk
{

Status_t TcpConnectionPlatform_t::Initialise(SOCKET socket_,
    IntrusivePtr_t<FileDescriptors_t>& fileDescriptors_,
    IntrusivePtr_t<SafeIntrusiveQueue_t<UInt64_t> > socketsToClose_)
{
  socket = socket_;
  fileDescriptors = fileDescriptors_;
  socketsToClose = socketsToClose_;
  notifyOnDataAvailable.Value(true);
  return lock.Initialise();
}

void TcpConnectionPlatform_t::NotifyCoreWhenNetworkReady(void)
{
  fileDescriptors->AddToWrite(socket);
}

SOCKET TcpConnectionPlatform_t::Socket(void)
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
  AutoLock_t lk(lock);

  CONNECTION_LOG_INFO("server: TcpConnectionPlatform_t::Close() socket %d", socket);
  fileDescriptors->Remove(socket);
  coreConnection.reset();

  IntrusivePtr_t<UInt64_t> socketToClose = new SafeRefCount_t<UInt64_t>();
  if (!socketToClose.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  socketToClose->Value(socket);
  return socketsToClose->Push(socketToClose);
}

Status_t TcpConnectionPlatform_t::Send(IntrusivePtr_t<const IBuffer_t> buffer)
{
  AutoLock_t lk(lock);

  if (!buffer.is_set())
  {
    return OpcUa_GoodCallAgain;
  }

  uint32_t bytesToSend = buffer->DataUnread();

  CONNECTION_LOG_INFO("Sending %u bytes", bytesToSend);

  if (bytesToSend > 0)
  {
    int32_t bytes_sent = send(socket, (const char*)buffer->ReadAddress(), bytesToSend, MSG_DONTWAIT);
    if (bytes_sent < 0)
    {
#ifdef _WIN32
      int error = WSAGetLastError();
      if (error == WSAEWOULDBLOCK)
#else
      CONNECTION_LOG_WARNING("UAServer_Callback_data_send(), send() error, errno: %d", errno);
      if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
#endif
      {
        CONNECTION_LOG_INFO("server: send would block");
        UASDK_RETURN_BAD_STATUS(OpcUa_BadWouldBlock);
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
        CONNECTION_LOG_ERROR("server: send failed, closing connection");
        UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
      }
    }
    else
    {
      buffer->IncrementReadIndex(bytes_sent);
      uint32_t bytesNotSent = buffer->DataUnread();
      if (bytesNotSent == 0)
      {
        CONNECTION_LOG_INFO("Sent %u bytes", bytes_sent);
        return OpcUa_GoodCallAgain;
      }
      else
      {
        CONNECTION_LOG_INFO("Sent %u bytes", bytes_sent);
        UASDK_RETURN_BAD_STATUS(OpcUa_BadWouldBlock);
      }
    }
  }
  return OpcUa_GoodCallAgain;
}

Status_t TcpConnectionPlatform_t::Receive(IBuffer_t& buffer)
{
  AutoLock_t lk(lock);

  int32_t bytes_received = 0;

  bytes_received = recv(
      socket,
      (char*)buffer.WriteAddress(),
      buffer.SpaceRemaining(),
      0);

  CONNECTION_LOG_INFO("Received %u bytes from client on socket: %d", bytes_received, socket);

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
    	CONNECTION_LOG_ERROR("UAServer_Callback_data_receive(), recv() error, errno: %d", errno);
      if (errno == EINTR)
      {
        /* Interrupted. Ask SDK to try again */
        return OpcUa_GoodCallAgain;
      }
      else if (errno == EAGAIN)
      {
        /* No data available for reading */
    	  NotifyCoreWhenDataAvailable();
        return OpcUa_Good;
      }
      else
#else
      int error = WSAGetLastError();
      if (error == WSAEWOULDBLOCK)
      {
        NotifyCoreWhenDataAvailable();
        return OpcUa_Good;
      }
      else
#endif
      {
        CONNECTION_LOG_ERROR("recv() error");
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

void TcpConnectionPlatform_t::NotifyCoreWhenDataAvailable(void)
{
  notifyOnDataAvailable.Value(true);
}

uasdk::Status_t TcpConnectionPlatform_t::Error(Status_t error)
{
  AutoLock_t lk(lock);

  if (coreConnection.is_set())
  {
    return coreConnection->Error(error);
  }
  UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidState);
}

uasdk::Status_t TcpConnectionPlatform_t::DataAvailable(void)
{
  AutoLock_t lk(lock);

  if (coreConnection.is_set())
  {
    if (notifyOnDataAvailable.Value())
    {
      notifyOnDataAvailable.Value(false);
      return coreConnection->DataAvailable();
    }
    else
    {
      return OpcUa_Good;
    }
  }
  UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidState);
}

uasdk::Status_t TcpConnectionPlatform_t::NetworkReady(void)
{
  AutoLock_t lk(lock);

  if (coreConnection.is_set())
  {
    return coreConnection->NetworkReady();
  }
  UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidState);
}

void TcpConnectionPlatform_t::Delete(void)
{
  AutoLock_t lk(lock);
  coreConnection.reset();
}

}

#endif //UASDK_INCLUDE_TCPIP_WINDOWS_LINUX_SOCKETS_SELECT_MT
