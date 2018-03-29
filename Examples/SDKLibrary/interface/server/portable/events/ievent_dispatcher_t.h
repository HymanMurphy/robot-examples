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

#ifndef _IEVENT_DISPATCHER_T_
#define _IEVENT_DISPATCHER_T_

#include "iattribute_access_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

namespace uasdk
{

/** \addtogroup grpEventsandAC
*@{*/

/*****************************************************************************/
/** \brief Event Dispatcher
*
* A class that is used to fire an event
*
*/
class IEventDispatcher_t :public IRefCount_t
{
public:
  virtual ~IEventDispatcher_t() {}

  /*****************************************************************************/
  /** Fire the event
   * This function will be used to fire an event
   *
   *  @param[in] eventObject
   *  The event object to be fired
   *
   *  @param[in] eventSourceNode
   *  The node Id of the event source node
   *
   * @return
   * Status of the operation.
   */
  virtual Status_t FireEventObject(IntrusivePtr_t<IAttributeAccess_t> eventObject,
																	 IntrusivePtr_t<NodeId_t> eventSourceNode) = 0;

};

/** @} */

}

#endif //UASDK_INCLUDE_EVENTS

#endif // _IEVENT_DISPATCHER_T_
