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

#ifndef _CONDITION_VARIABLE_TYPE_T_
#define _CONDITION_VARIABLE_TYPE_T_

#include "uasdk_includes.h"

#if ((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

#include "allocatable_t.h"
#include "opcua_date_time_t.h"
#include "opcua_localized_text_t.h"
#include "ilocalizable_text_t.h"

namespace uasdk
{
/** \addtogroup grpEventsandAC
*@{*/

/*****************************************************************************/
/** \brief ConditionVariableType_t
*
* This class implements the ConditionVariableType
* Various information elements of a Condition are not considered to be states.
* However, a change in their value is considered important and supposed to trigger an Event Notification.
*
*/
class ConditionVariableType_t : public Allocatable_t, public IRefCount_t
{
private:

  /*****************************************************************************/
  /* @var IntrusivePtr_t<BaseDataType_t> value
  * value is the value of this variable.
  */
  IntrusivePtr_t<BaseDataType_t> value;

  /*****************************************************************************/
  /* @var IntrusivePtr_t<UtcTime_t> sourceTimeStamp
  * sourceTimeStamp indicates the time of the last change of the Value of this ConditionVariable.
  */
  IntrusivePtr_t<UtcTime_t> sourceTimeStamp;

public:

  /*****************************************************************************/
  /** Constructor for the class.
  *
  */
  ConditionVariableType_t();

  /*****************************************************************************/
  /** Destructor for the class.
  *
  */
  virtual ~ConditionVariableType_t();

  /*****************************************************************************/
  /** Initialise() the ConditionVariableType
  *
  * @return
  * status of the operation
  */
  Status_t Initialise();

  /*****************************************************************************/
  /** Get the Value value
  *
  * @return
  * Returns the Value value
  */
  IntrusivePtr_t<const BaseDataType_t> Value(void) const;

  /*****************************************************************************/
  /** Set the Value value
  *
  * @return
  * Returns the Value value
  */
  IntrusivePtr_t<BaseDataType_t>& Value(void);

  /*****************************************************************************/
  /** Get the SourceTimestamp value
  *
  * @return
  * Returns the SourceTimestamp value
  */
  IntrusivePtr_t<const UtcTime_t> SourceTimestamp(void) const;

  /*****************************************************************************/
  /** Set the SourceTimestamp value
  *
  * @return
  * Returns the SourceTimestamp value
  */
  IntrusivePtr_t<UtcTime_t>& SourceTimestamp(void); 

  /*****************************************************************************/
  /** Copy from the source
  *
  * @param[in] const ConditionVariableType_t& source
  *  ConditionVariableType_t source to copy from
  *
  * @return
  * Status of the operation
  */
  Status_t CopyFrom(const ConditionVariableType_t& source);

  /*****************************************************************************/
  /** Copy to the destination
  *
  * @param[out] IntrusivePtr_t<ConditionVariableType_t>& destination
  * Destination data type
  *
  * @return
  * Status of the operation
  */
  Status_t CopyTo(IntrusivePtr_t<ConditionVariableType_t>& destination);

  /*****************************************************************************/
  /** CreateConditionVariableTypeWithDefaultValues
  * Helper method to create condition variable based on the input data type
  *
  * @param[in] valueType
  * data type of the value
  *
  * @param[out] result
  * status of the operation
  *
  * @return
  * condition variable instance with default values
  */
  static IntrusivePtr_t<ConditionVariableType_t> CreateConditionVariableTypeWithDefaultValues(uint32_t valueType, Status_t& result);

};

/** @} */

}

#endif //((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

#endif // _CONDITION_VARIABLE_TYPE_T_
