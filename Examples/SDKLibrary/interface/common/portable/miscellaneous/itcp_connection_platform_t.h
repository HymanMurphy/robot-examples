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

#ifndef _ITCP_CONNECTION_PLATFORM_T_
#define _ITCP_CONNECTION_PLATFORM_T_

#include "uasdk_includes.h"
#include "iref_count_t.h"
#include "intrusive_ptr_t.h"
#include "status_t.h"

namespace uasdk
{

/** \addtogroup grpTcpIp
 *@{*/

class IBuffer_t;
class IPEndpoint_t;
class ITcpConnectionCore_t;

class ITcpConnectionPlatform_t : public IRefCount_t
{
public:
  virtual ~ITcpConnectionPlatform_t() {};

  /*****************************************************************************/
  /** This function provides IPEndPoint
   *
   *
   *  @return
   *  returns the value in IPEndpoint_t type.
   */

  virtual const IPEndpoint_t& IPEndpoint(void) const = 0;

  /*****************************************************************************/
  /** This function used to inform platform layer about the connection opened.
   *
   * @param[in] connection
   * TCP/IP connection
   */
  virtual void CoreOpened(IntrusivePtr_t<ITcpConnectionCore_t> connection) = 0;

  /*****************************************************************************/
  /** This function is used to close the connection.
   *
   */
  virtual Status_t Close(void) = 0;

  /*****************************************************************************/
  /** Function provided by platform to enable core to send data to the network
   *
   * This method will be called repeatedly whenever the core has data to send.
   * The platform may write the data to the TCP/IP stack synchronously or it may
   * take a pointer to the buffer and write the data asynchronously.
   * If the platform writes the data asynchronously it must write the buffers to
   * the TCP/IP stack in order.
   * If the platform tells the core via the return code that the TCP/IP stack
   * accept more data it must call NetworkReady() on the core connection to
   * restart data transmission when the TCP/IP stack is ready to accept more
   * data.
   *
   * @param[in] buffer
   * A buffer containing the data to be written.
   *
   * @return
   * The result of the operation. Possible value are:
   *
   * OpcUa_Good                     All of the data was successfully written but
   *                                the TCP/IP stack cannot accept more data.
   *
   * OpcUa_GoodCallAgain            All of the data was successfully written and
   *                                the TCP/IP stack can accept more data.
   *
   * OpcUa_BadWouldBlock            Not all of the data was written. The buffer
   *                                can be inspected by the caller to see what
   *                                was written. It is possible that zero bytes
   *                                was written.
   *
   * OpcUa_GoodCompletesAsynchronously  The platform will take responsibility
   *                                    for sending the data. The TCP/IP stack can
   *                                    accept more data.
   *
   * Any other status code          A fatal error has occurred.
   *
   */
  virtual Status_t Send(IntrusivePtr_t<const IBuffer_t> buffer) = 0;

  /*****************************************************************************/
  /** Function provided by platform to enable core to receive data from the network
   *
   * This method will be called repeatedly whenever the core wants to receive data.
   * The buffer length provided may be less than the data available.
   * If the platform tells the core via the return code that there is no more data
   * to read it must call DataAvailable() on the core connection to
   * restart data reception when more data is available for reading.
   * data.
   *
   * @param[in] buffer
   * A buffer to write the data into.
   *
   * @return
   * The result of the operation. Possible value are:
   *
   * OpcUa_Good                     All of the data available was successfully
   *                                written to the buffer and there is no more data
   *                                available.
   *
   * OpcUa_GoodCallAgain            The buffer was successfully filled with data and
   *                                there is more data available.
   *
   * OpcUa_BadNoData                There is no data available to be read.
   *
   * Any other status code          A fatal error has occurred.
   *
   */
  virtual Status_t Receive(IBuffer_t& buffer) = 0;

  /*****************************************************************************/
  /** Notify the core when new data is available from the network
   *
   */
  virtual void NotifyCoreWhenDataAvailable(void) = 0;

  /*****************************************************************************/
  /** Notify the core when the network is ready to send data
  *
  */
  virtual void NotifyCoreWhenNetworkReady(void) = 0;
};

/** @} */

}

#endif // _ITCP_CONNECTION_PLATFORM_T_
