/* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                        COPYRIGHT (c) 2009 - 2017
                                         HONEYWELL INC.,
                                        ALL RIGHTS RESERVED

            This software is a copyrighted work and/or information protected as a trade
            secret. Legal rights of Honeywell Inc. in this software are distinct from
            ownership of any medium in which the software is embodied. Copyright or trade
            secret notices included must be reproduced in any copies authorized by
            Honeywell Inc. The information in this software is subject to change without
            notice and should not be considered as a commitment by Honeywell Inc.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////// */

#ifndef _TCP_CONNECTION_PLATFORM_T_
#define _TCP_CONNECTION_PLATFORM_T_

#include "uasdk_includes.h"

#if (UASDK_INCLUDE_TCPIP_WINDOWS_LINUX_SOCKETS_SELECT_ST > 0)

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#endif

#include "itcp_connection_platform_t.h"
#include "allocatable_t.h"
#include "ip_endpoint_t.h"
#include "intrusive_ptr_t.h"
#include "opcua_string_t.h"
#include "itcp_connection_core_t.h"
#include "intrusive_list_t.h"

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

#ifdef _WIN32
  SOCKET socket;
#else
  int socket;
#endif
  fd_set* read_fds;
  fd_set* write_fds;
  fd_set* master_fds;
  IntrusiveList_t<TcpConnectionPlatform_t>* connections;
  IntrusivePtr_t<ITcpConnectionCore_t> coreConnection;

  /*****************************************************************************/
  /** This function used to notify socket file descriptor for write operation when
   * network is available.
   *
   */
  void NotifyCoreWhenNetworkReady(void);

public:
  virtual ~TcpConnectionPlatform_t()
  {
  }


#ifdef _WIN32

  /*****************************************************************************/
  /** Function used to get the socket file descriptor in windows platform.
   *
   * @return
   * returns SOCKET file descriptor value.
   */
  SOCKET Socket(void);

  /*****************************************************************************/
  /** This function used to initialize the resource of Tcp_connection class in windows platform.
   *
   * @param[in] socket_
   * socket file descriptor
   *
   * @param[in] master_fds_
   *  master descriptors
   *
   * @param[in] read_fds_
   * read descriptors
   *
   * @param[in] write_fds_
   * write descriptors
   *
   * @param[in] connections_
   * read descriptors
   *
   * @return
   * returns status of the operation.
   */
  Status_t Initialise(SOCKET socket_, fd_set& master_fds_, fd_set& read_fds_, fd_set& write_fds_,
    IntrusiveList_t<TcpConnectionPlatform_t>& connections_);
#else
  /*****************************************************************************/
  /** Function used to get the socket file descriptor.for non windows platforms
   *
   * @return
   * returns SOCKET file descriptor value.
   */
  int Socket(void);

  /*****************************************************************************/
  /** This function used to initialize the resource of Tcp_connection class for non Windows platform.
   *
   * @param[in] socket_
   * socket file descriptor
   *
   * @param[in] master_fds_
   *  master descriptors
   *
   * @param[in] read_fds_
   * read descriptors
   *
   * @param[in] write_fds_
   * write descriptors
   *
   * @param[in] connections_
   * read descriptors
   *
   * @return
   * returns status of the operation.
   */
  Status_t Initialise(int socket_, fd_set& master_fds_, fd_set& read_fds_, fd_set& write_fds_,
    IntrusiveList_t<TcpConnectionPlatform_t>& connections_);
#endif

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
  /** This function notify after data is availablility in socket
   *
   */
  virtual void NotifyCoreWhenDataAvailable(void);

  /*****************************************************************************/
  /** Function used to get the connection information
   *
    * @return
   *  An intrusive reference counting Boost-style smart pointer to the
   *  TCP Connection. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<ITcpConnectionCore_t> CoreConnection(void);
};

/*@}*/

}

#endif //UASDK_INCLUDE_TCPIP_WINDOWS_LINUX_SOCKETS_SELECT_ST

#endif // _TCP_CONNECTION_PLATFORM_T_
