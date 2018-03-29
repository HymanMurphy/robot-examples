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

#ifndef _ITCP_CONNECTION_PROVIDER_T_
#define _ITCP_CONNECTION_PROVIDER_T_

#include "uasdk_includes.h"

namespace uasdk
{

/** \addtogroup grpTcpIp
 *@{*/

class ITcpConnectionCore_t;

class ITcpConnectionProvider_t
{
public:
  virtual ~ITcpConnectionProvider_t() {};

  /*****************************************************************************/
  /**This  function is used to open the new connection.
   *
   * @param[in] connection
   * new connection to be opened.
   *
   * @return
   * returns the status of the operation.
   */

  virtual Status_t TcpOpenNewConnection(IntrusivePtr_t<ITcpConnectionCore_t>& connection) = 0;
};

/** @} */

}

#endif // _ITCP_CONNECTION_PROVIDER_T_
