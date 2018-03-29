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

#ifndef _TCP_CONNECTION_PLATFORM_T_
#define _TCP_CONNECTION_PLATFORM_T_

#include "file_descriptors_t.h"

#if (UASDK_INCLUDE_TCPIP_WINDOWS_LINUX_SOCKETS_SELECT_MT > 0)

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#endif

#include "itcp_connection_platform_t.h"
#include "uasdk_includes.h"
#include "allocatable_t.h"
#include "ip_endpoint_t.h"
#include "intrusive_ptr_t.h"
#include "opcua_string_t.h"
#include "itcp_connection_core_t.h"
#include "intrusive_list_t.h"
#include "safe_intrusive_queue_t.h"
#include "opcua_uint64_t.h"
#include "atomic_t.h"

#ifdef _WIN32

#define suseconds_t long

#elif defined __linux

#define SOCKET int

#else
#error This module is implemented for Windows and Linux only
#endif

namespace uasdk
{
/** \addtogroup grpTcpIp
 *@{*/

/*****************************************************************************/
/** \brief TcpConnectionPlatform_t
 *
 * A class implements the TCP connection management
 *
 */
class TcpConnectionPlatform_t : public ITcpConnectionPlatform_t, public Allocatable_t
{
private:
  class DummyIPEndpoint_t : public IPEndpoint_t
  {
  /*****************************************************************************/
  /** This is used for getting dummy port value
   *
   * @return
   * return 0
   */
    uint16_t Port(void) const
    {
      return 0;
    }

  /*****************************************************************************/
  /** Function used to get empty string for Dummy IP port
   *
   * @return
   * Empty string will be returned. Called is advised not to dereference.
   */
    IntrusivePtr_t<String_t> ToString(void) const
    {
        IntrusivePtr_t<String_t> empty;
        return empty;
    }
  };

  SOCKET socket;
  IntrusivePtr_t<FileDescriptors_t> fileDescriptors;
  IntrusivePtr_t<ITcpConnectionCore_t> coreConnection;
  IntrusivePtr_t<SafeIntrusiveQueue_t<UInt64_t> > socketsToClose;
  Atomic_t<bool> notifyOnDataAvailable;

  Lock_t lock;

  /*****************************************************************************/
  /** This function used to notify socket file descriptor for write operation when
   *  network is available.
   *
   */
  void NotifyCoreWhenNetworkReady(void);

public:
  virtual ~TcpConnectionPlatform_t()
  {
  }

  /*****************************************************************************/
  /** Function used to get the socket file descriptor.
   *
   * @return
   * returns socket file descriptor value.
   */
  SOCKET Socket(void);

  /*****************************************************************************/
  /** This function used to initialize the resource of Tcp_connection class.
   *
   * @param[in] socket_
   * socket file descriptor
   *
   * @param[in] fileDescriptors_
   *  file descriptors
   *
   * @param[in] socketsToClose_
   * IntrusivePtr class object
   *
   * @return
   * returns status of the operation.
   */
  Status_t Initialise(SOCKET socket_,
    IntrusivePtr_t<FileDescriptors_t>& fileDescriptors_,
    IntrusivePtr_t<SafeIntrusiveQueue_t<UInt64_t> > socketsToClose_);

  /*****************************************************************************/
  /** Function used to get the ip endpoint
   *
   * @return
   * returns IPEndpoint_t class object.
   */
  const IPEndpoint_t& IPEndpoint(void) const;

  /*****************************************************************************/
  /** Function used to set the connection information
   *
   * @param[in] connection
   * connection to be assigned
   */
  void CoreOpened(IntrusivePtr_t<ITcpConnectionCore_t> connection);

  /*****************************************************************************/
  /** Function used to close the Tcp connection.
   *
   * @return
   * returns status of the operation.
   */
  Status_t Close(void);

  /*****************************************************************************/
  /** Function used to send the buffer data to the client over Socket.
   *
   * @param[in]buffer
   * data which is to be send over socket
   *
   * @return
   * returns the status of the operation
   */
  virtual Status_t Send(IntrusivePtr_t<const IBuffer_t> buffer);

  /*****************************************************************************/
  /** Function used to receive the data from the client over Socket.
   *
   * @param[out]buffer
   * store the data which is received from the client
   *
   * @return
   * returns the status of the operation
   */
  virtual Status_t Receive(IBuffer_t& buffer);

  /*****************************************************************************/
  /** This function sets the value true when the data is available.
   *
   */
  virtual void NotifyCoreWhenDataAvailable(void);

  /*****************************************************************************/
  /** This function checks the error status of Tcp connection.
   *
   * @return
   * returns error status.
   */
  Status_t Error(Status_t error);

  /*****************************************************************************/
  /** This function used to check the data availabality..
   *
   * @return
   * returns status of the operation.
   */
  Status_t DataAvailable(void);

  /*****************************************************************************/
  /** This function used to check whether network is ready or not.
   *
   * @return
   * returns status of the operation.
   */
  Status_t NetworkReady(void);

  void Delete(void);

};

/** @} */

}

#endif //UASDK_INCLUDE_TCPIP_WINDOWS_LINUX_SOCKETS_SELECT_MT

#endif // _TCP_CONNECTION_PLATFORM_T_
