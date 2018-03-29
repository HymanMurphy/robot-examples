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

#ifndef _ITCP_CONNECTION_CORE_T_
#define _ITCP_CONNECTION_CORE_T_

#include "uasdk_includes.h"

namespace uasdk
{

/** \addtogroup grpTcpIp
 *@{*/

class IPEndpoint_t;
class ITcpConnectionPlatform_t;

class ITcpConnectionCore_t : public IRefCount_t
{
public:
  virtual ~ITcpConnectionCore_t() {};

  /*****************************************************************************/
  /** This function provides IPEndPoint
   *
   *
   *  @return
   *  returns the IP Endpoint information
   */

  virtual const IPEndpoint_t& IPEndpoint(void) const = 0;

  /*****************************************************************************/
  /** This function provides connection timeout
   *
   *
   *  @return
   *  returns unsigned integer value.
   */

  virtual uint32_t ConnectTimeoutInMs(void) const = 0;

  /*****************************************************************************/
  /** This function is enables the platform to be opened.
   *
   * @param[in] connection
   * connection to check the platform opened or not
   *
   * @return
   * returns the status of operation.
   */
  virtual Status_t PlatformOpened(IntrusivePtr_t<ITcpConnectionPlatform_t> connection) = 0;

  /*****************************************************************************/
  /** This function is used to check the connection closed status
   *
   *
   *  @return
   *  returns the status of operation
   */
  virtual Status_t Closed(void) = 0;

  /*****************************************************************************/
  /** This function is used to set the error status.
   *
   * @param[in] error
   * error is of type status_t
   *
   *  @return
   *  returns the status of operation
   */
  virtual Status_t Error(Status_t error) = 0;

  /*****************************************************************************/
  /** This function is used to close the connection
   *
   *
   *  @return
   *  returns the status of operation
   */
  virtual Status_t Close(void) = 0;

  /*****************************************************************************/
  /** This function inform the availability of new data
   *
   *
   *  @return
   *  returns the status of operation
   */
  virtual Status_t DataAvailable(void) = 0;

  /*****************************************************************************/
  /** This function is used to inform the network ready information.
   *
   *  @return
   *  returns the status of operation
   */
  virtual Status_t NetworkReady(void) = 0;
};

/** @} */

}

#endif // _ITCP_CONNECTION_CORE_T_
