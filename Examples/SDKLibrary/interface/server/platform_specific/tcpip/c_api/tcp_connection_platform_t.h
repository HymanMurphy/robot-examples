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

#if (UASDK_INCLUDE_SERVER)
#if (UASDK_INCLUDE_TCPIP_C_API > 0)

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
    /** Function returns the port
     *
     * @return
     * returns always zero
     */

    uint16_t Port(void) const
    {
      return 0;
    }

    /*****************************************************************************/
    /** Function used to convert the string
     *
     * @return
     * returns String_t value.
     */
    IntrusivePtr_t<String_t> ToString(void) const
    {
      IntrusivePtr_t<String_t> empty;
      return empty;
    }
  };

  uint64_t connectionId;
  IntrusiveList_t<TcpConnectionPlatform_t>* connections;
  IntrusivePtr_t<ITcpConnectionCore_t> coreConnection;

  void* context;

  bool notifyWhenDataAvailable;
  bool networkTxAllowed;
  bool networkRxAllowed;

public:

  /*****************************************************************************/
  /** Constructor for the class.
   *
   */
  TcpConnectionPlatform_t() : connectionId(0), connections(0), context(0), notifyWhenDataAvailable(true), networkTxAllowed(false), networkRxAllowed(false) {}

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~TcpConnectionPlatform_t() {}

  /*****************************************************************************/
  /** Function returns the context pointer value.
   *
   * @return
   * returns void pointer.
   */
  void* Context(void);

  /*****************************************************************************/
  /** Function initializes the pointer.
   *
   *@param[in] value
   *value to be initialize the pointer
   *
   */
  void Context(void* value);

  /*****************************************************************************/
  /** Function initializes the network allowance status.
   *
   *@param[in] value
   *Boolean value which is to be initialize the network allowance status.
   *
   */
  void NetworkTxAllowed(bool value);

  /*****************************************************************************/
  /** Function initializes the network allowance status.
   *
   *@param[in] value
   *Boolean value which is to be initialize the network allowance status.
   *
   */
  void NetworkRxAllowed(bool value);

  /*****************************************************************************/
  /** Function gets the connection ID.
   *
   * @return
   * returns the connection id value
   */
  uint64_t ConnectionId(void);

  /*****************************************************************************/
  /** Function initializes the resources.
   *
   * @param[in] connectionId_
   * connection id which is to be initialize.
   *
   * @param[in] connections_
   * Tcp platform connections to be initialize.
   *
   * @return
   * returns the status of the operation.
   */
  Status_t Initialise(
    uint64_t connectionId_,
    IntrusiveList_t<TcpConnectionPlatform_t>& connections_);

  /*****************************************************************************/
  /** Function returns the dummy ip end points.
   *
   * @return
   * returns the IPEndpoint_t value.
   */
  const IPEndpoint_t& IPEndpoint(void) const;

  /*****************************************************************************/
  /** Function used to check the core connection status.
   *
   * @param[in] connection
   * connection which is to be check and initialize.
   *
   */
  void CoreOpened(IntrusivePtr_t<ITcpConnectionCore_t> connection);

  /*****************************************************************************/
  /** Function used to reset all core connection and call back connections.
   *
   * @return
   * returns the status of the operation.
   *
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
   * returns the status of the operation.
   */
  virtual Status_t Receive(IBuffer_t& buffer);

  /*****************************************************************************/
  /** Notify the core when new data is available from the network
  *
  */
  virtual void NotifyCoreWhenDataAvailable(void);

  /*****************************************************************************/
  /** Notify the core when the network is ready to send data
  *
  */
  virtual void NotifyCoreWhenNetworkReady(void);

  /*****************************************************************************/
  /** This function closes the core connection.
   *
   * @return
   * returns the status of the operation.
   */
  Status_t CloseFromPlatform(void);

  /*****************************************************************************/
  /** This function used to check the data availability.
   *
   * @return
   * returns the status of the operation.
   */
  Status_t DataAvailable(void);

  /*****************************************************************************/
  /** This function used to check whether network is ready or not.
   *
   * @return
   * returns the status of the operation.
   */
  Status_t NetworkReady(void);
};

/*@}*/

}

#endif //UASDK_INCLUDE_TCPIP_C_API
#endif //(UASDK_INCLUDE_SERVER)
#endif // _TCP_CONNECTION_PLATFORM_T_
