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

#ifndef _TRIP_ALARM_T_
#define _TRIP_ALARM_T_

#include "off_normal_alarm_t.h"

#if ((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

#include "trip_alarm_type_data_t.h"

namespace uasdk
{

/** \addtogroup grpEventsandAC
*@{*/

/*****************************************************************************/
/** \brief ITripAlarmMethodListener_t
*
* This class is used to add callback listener for the condition methods.
* The methods of this class should be implemented in the application layer.
*
*/
class ITripAlarmMethodListener_t : public IOffNormalAlarmMethodListener_t
{
  //It do not have any methods. It can act as a place holder for sub-classes
};

/*****************************************************************************/
/** \brief TripAlarm_t
*
* The TripAlarmType is a specialization of the OffNormalAlarmType intended to represent an equipment trip Condition.
*
*/
class TripAlarm_t : public OffNormalAlarm_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(TripAlarm_t);

private:

  /*****************************************************************************/
  /* @var IntrusivePtr_t<TripAlarmTypeData_t> conditionData
  * conditionData is a structure which holds all the variables of the condition.
  */
  IntrusivePtr_t<TripAlarmTypeData_t> conditionData;

  /*****************************************************************************/
  /** InitialiseConditionDataAttributes()
  * InitialiseConditionDataAttributes will initialize the data object attributes
  *
  * @return
  * status of the operation
  */
  Status_t InitialiseConditionDataAttributes(void);

protected:

  /*****************************************************************************/
  /* @var IntrusivePtr_t<ITripAlarmMethodListener_t> conditionMethodListener
  * conditionMethodListener is used to register for callback listeners.
  */
  IntrusivePtr_t<ITripAlarmMethodListener_t> conditionMethodListener;

  /*****************************************************************************/
  /** EvaluteState()
  * EvaluteState will evaluate the current state of the condition
  *
  * @param[in] methodId
  * methodId is the type Id of the method from which the EvaluateState is called.
  *
  * @return
  * return the status of the operation.
  */
  Status_t EvaluteState(uint32_t methodId);

  /*****************************************************************************/
  /** InitialiseConditionData()
  * InitialiseConditionData will initialize the data object
  *
  * @param[in] conditionData_
  * input condition data object
  *
  * @param[in] conditionClassId
  * The ConditionClassId Property of the ConditionType is used to assign a Condition to a ConditionClass.
  *
  * @param[in] conditionName
  * ConditionName identifies the Condition instance that the Event originated from
  *
  * @param[in] isAllocated
  * if this flag is false, conditionData object will be allocated, else it will only assign the input data object to the member variable.
  *
  * @return
  * status of the operation
  */
  virtual Status_t InitialiseConditionData(IntrusivePtr_t<ConditionTypeData_t> conditionData_, uint32_t conditionClassId, String_t& conditionName, bool isAllocated = false);

  /*****************************************************************************/
  /** GetEventData()
  * GetEventData to be fired to the client
  *
  * @param[out] data
  * copy of the data to be sent as an event
  *
  * @param[out] sourceNodeId
  * source node id associated with the event
  *
  * @return
  * status of the operation
  */
  virtual Status_t GetEventData(IntrusivePtr_t<IAttributeAccess_t>& data, IntrusivePtr_t<NodeId_t>& sourceNodeId);  

public:

  /*****************************************************************************/
  /** Constructor for the class.
  *
  */
  TripAlarm_t();

  /*****************************************************************************/
  /** Destructor for the class.
  *
  */
  virtual ~TripAlarm_t();

  /*****************************************************************************/
  /** Initialise()
  * this method is used to create condition and update in the condition registrar of the condition is created successfully.
  *
  * @param[in] configuration_
  * server configuration
  *
  * @param[in] conditionId_
  * id for the condition
  *
  * @param[in] conditionClassId
  * class id of the condition
  *
  * @param[in] conditionName
  * ConditionName identifies the Condition instance that the Event originated from
  *
  * @return
  * status of the operation
  */
  virtual Status_t Initialise(IntrusivePtr_t<IServerConfiguration_t> configuration_, NodeId_t& conditionId_, uint32_t conditionClassId, String_t& conditionName);
  
  /*****************************************************************************/
  /** SetMethodListener()
  * set the method handler for the callback listener
  *
  * @param[in] value
  * callback listener instance
  *
  * @return
  * status of the operation
  */
  virtual Status_t SetMethodListener(IntrusivePtr_t<ITripAlarmMethodListener_t> value);

  /*****************************************************************************/
  /** Begins calling the method of the node
  *
  *  If the method call is successful
  *  completedCallback.CallMethodCompleted() will be called by the method handler
  *  when the method has completed. If this function returns a bad status code
  *  completedCallback.CallMethodCompleted() will not be called by the method
  *  handler.
  *
  * @param[in] sessionId
  * The ID of the session making the call. Will be null if the call is not being made
  * in the context of a session.
  *
  * @param[in] transationId
  * A non-zero unique identifier for a collection of methods being called as a
  * group (typically by the Call Service). Can be optionally used in conjunction
  * with a transaction listener to optimise processing of method calls by the
  * application. If calling the method outside of the Call Service should be set
  * to zero.
  *
  * @param[in] userPermissions
  * An object used to identify a specific user and authenticate that user's
  * access permissions.
  *
  * @param[in] timeoutHint
  * The timeoutHint in milliseconds provided by the Call Service. The method
  * handler can optionally consider this hint when replying to the caller.
  * Should be set to zero where no timeoutHint is provided.
  *
  * @param[in] componentOf
  * The object that defines the context for the method call. Must be referenced by
  * a ComponentOf reference from the Method.
  *
  * @param[in] requestParameters
  * The parameters of the method call.
  *
  * @param[in] method
  * The method to be called
  *
  * @param[in] result
  * Object to store the result of the method call.
  *
  * @param[out] completedCallback
  * The CallMethodCompleted() function of this interface will be called by the method
  * handler if this function returns a good status code.
  *
  * @return
  * The result of the operation. If the status code is good then the method handler
  * has been successfully launched and will return the method result in due course. If
  * the status code is bad the method handler was not successfully launched.
  *
  */
  virtual Status_t CallMethodBegin(IntrusivePtr_t<const NodeId_t> sessionId,
    uint32_t transactionId,
    const IUserPermissions_t& userPermissions,
    uint32_t timeoutHint,
    IntrusivePtr_t<INode_t>& componentOf,
    IntrusivePtr_t<IMethodNode_t>& method,
    IntrusivePtr_t<const CallMethodRequest_t>& requestParameters,
    IntrusivePtr_t<CallMethodResult_t>& result,
    IntrusivePtr_t<ICallbackCallMethodCompleted_t>& completedCallback);

  /*****************************************************************************/
  /** Reading the value attribute of the node synchronously
  *
  * @param[in] node
  * variable node from which data will be read
  *
  * @param[in] maxAge
  * The maxAge of the value in milliseconds provided by the Read Service. The reader
  * can optionally consider this when replying to the caller.
  * Should be set to zero where no maxAge is provided.
  *
  * @param[in] setSourceTimestamp
  * Set the source timestamp in the data value.
  *
  * @param[in] locales
  * A list of locales in order of preference to use when reading LocalizedText.
  *
  * @param[in] indexRange
  * The index range to apply to the value if it is an array.
  *
  * @param[in] transactionId
  * A non-zero unique identifier for a collection of nodes being read as a
  * group (typically by the Read Service). Can be optionally used in conjunction
  * with a transaction listener to optimise processing of read operations by the
  * application. If reading the node outside of the Read Service should be set
  * to zero.
  *
  * @param[in] timeoutHint
  * The timeoutHint in milliseconds provided by the Read Service. The reader
  * can optionally consider this hint when replying to the caller.
  * Should be set to zero where no timeoutHint is provided.
  *
  * @param[out] dataValue
  * That read from the node will be update to the dataValue
  *
  * @param[out] diagnosticInfo
  * Intrusive pointer of type DiagnosticInfo_t returning any diagnostic information
  * required.
  *
  * @return
  * The result of the operation.
  *
  */
  virtual Status_t ReadValueAttribute(
    const IVariableNode_t& node,
    uint32_t maxAge,
    bool setSourceTimestamp,
    const ArrayUA_t<String_t>& locales,
    const Array_t<IndexRange_t>& indexRange,
    uint32_t transactionId,
    uint32_t timeoutHint,
    IntrusivePtr_t<DataValue_t>& dataValue,
    IntrusivePtr_t<DiagnosticInfo_t>& diagnosticInfo);
};

/** @} */

} // namespace uasdk

#endif //((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

#endif // _TRIP_ALARM_T_
