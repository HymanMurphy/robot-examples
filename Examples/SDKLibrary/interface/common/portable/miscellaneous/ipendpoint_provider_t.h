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

#ifndef _IIP_ENDPOINT_PROVIDER_T
#define _IIP_ENDPOINT_PROVIDER_T

#include "uasdk_includes.h"

namespace uasdk
{
/** \addtogroup grpMiscellaneous
 *@{*/

class ICallbackIPEndpointLookupComplete_t
{
public:
  virtual ~ICallbackIPEndpointLookupComplete_t() {};

  /*****************************************************************************/
  /** This function is used to overload the "()" operator
   *
   * @param[in] result
   * result is of status type
   *
   * @param[out]ipEndpoint
   * ipEndpoint is of IntrusivePtr_t type.
   *
   * @return
   * returns status os the operation.
   */
  virtual Status_t operator()(Status_t result,
                              IntrusivePtr_t<IPEndpoint_t>& ipEndpoint) = 0;
};

class IIPEndpointProvider_t
{
public:
  virtual ~IIPEndpointProvider_t() {};

  /*****************************************************************************/
  /** This function is used to lookup the IP.
   *
   * @param[in] hostname
   * host name
   *
   * @param[in] completedCallback
   * pointer to callback function to be called after endpoint is found
   *
   * @return
   * returns status os the operation.
   */
  virtual Status_t IPEndpointLookupBegin(String_t& hostname,
                                         IntrusivePtr_t<ICallbackIPEndpointLookupComplete_t>& completedCallback) = 0;
};

/** @} */

}

#endif // _IIP_ENDPOINT_PROVIDER_T
