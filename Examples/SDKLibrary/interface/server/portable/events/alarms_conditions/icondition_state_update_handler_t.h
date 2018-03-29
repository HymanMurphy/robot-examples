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

#ifndef _ICONDITION_STATE_UPDATE_HANDLER_T_
#define _ICONDITION_STATE_UPDATE_HANDLER_T_

#include "uasdk_includes.h"

#if ((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

namespace uasdk
{

/** \addtogroup grpEventsandAC
*@{*/

/*****************************************************************************/
/** \brief IConditionStateUpdateHandler_t
*
* This is a A callback interface included in ICondition_t to allow condition variable and state variable changes 
* to notify the condition that they have been changed, and allow the condition to determine if an event notification is required.
*
*/
class IConditionStateUpdateHandler_t : public virtual IRefCount_t
{
public:
  virtual ~IConditionStateUpdateHandler_t() {}

  /*****************************************************************************/
  /** BeginConditionStateUpdate()
  * Multiple condition state updates can be grouped together in a single notification by calling BeginConditionStateUpdate before
  * calling ConditionStateUpdated().
  * Every call to BeginConditionStateUpdate() must be matched with a call to EndConditionStateUpdate()
  *
  * BeginConditionStateUpdate/EndConditionStateUpdate blocks may be built recursively, and all updates made inside a block
  * will be sent as a single notification at the end.
  *
  */
  virtual void BeginConditionStateUpdate(void) = 0;

  /*****************************************************************************/
  /** FireEventNotification()
  * This method is called to take a copy of the current event information and
  * post it to any subscribed UA clients through monitored items.
  *
  * @return
  * status of the operation
  */
  virtual Status_t FireEventNotification(void) = 0;

  /*****************************************************************************/
  /** ConditionStateUpdated()
  * ConditionStateUpdated should be called every time a condition variable member
  * of the class has been changed.  If it is called inside of a BeginConditionStateUpdate/EndConditionStateUpdate pair,
  * the event notification will be sent when all updates are completed and the final EndCOnditionStateUpdate call is made.
  * If this method is called outside of a Begin.../End ... block, then an event notification is sent immediately.
  *
  * @return
  * status of the operation
  */
  virtual void ConditionStateUpdated(void) = 0;

  /*****************************************************************************/
  /** EndConditionStateUpdate()
  * end of the condition state update
  *
  * @return
  * status of the operation
  */
  virtual void EndConditionStateUpdate(void) = 0;
};

/** @} */

}

#endif //((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

#endif // _ICONDITION_STATE_UPDATE_HANDLER_T_
