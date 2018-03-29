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

#ifndef _ICALLBACK_EVENT_LOGGED_T_
#define _ICALLBACK_EVENT_LOGGED_T_

#include "iattribute_access_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

namespace uasdk
{
/** \addtogroup grpEventsandAC
*@{*/

/*****************************************************************************/
/** \brief Event Logger callback
*
* A class that is used to log the events
*
*/
class ICallbackEventLogged_t :public IRefCount_t
{
public:
  virtual ~ICallbackEventLogged_t() {}

  /*****************************************************************************/
  /** Log the event
   *
   *  @param[in] eventObject
   *  The event object to be logged
   *
   *  @param[out] eventRecordId
   *  The string which represents the event record Id
   *
   * @return
   * Status of the operation.
   */
  virtual Status_t LogEvent(IntrusivePtr_t<IAttributeAccess_t> eventObject, String_t& eventRecordId) = 0;

};

/** @} */

}

#endif //UASDK_INCLUDE_EVENTS

#endif // _ICALLBACK_EVENT_LOGGED_T_
