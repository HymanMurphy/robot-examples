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

#ifndef _ICALLBACK_EVENT_HISTRIZED_T_
#define _ICALLBACK_EVENT_HISTRIZED_T_

#include "uasdk_includes.h"
#include "opcua_event_field_list_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

namespace uasdk
{

class ICallbackEventHistorized_t :public IRefCount_t
{
public:
  virtual ~ICallbackEventHistorized_t() {}

  /*****************************************************************************/
  /** Historize the event
   *
   *  @param[in] events
   *  The array of the event field list to be historized
   *
   * @return
   * Status of the operation.
   */
  virtual Status_t HistorizeEvent(IntrusivePtr_t<ArrayUA_t<EventFieldList_t> > events) = 0;

};

/*@}*/

}

#endif //UASDK_INCLUDE_EVENTS

#endif // _ICALLBACK_EVENT_HISTRIZED_T_
