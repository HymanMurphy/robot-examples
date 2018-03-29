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

#include "discrete_alarm_t.h"

#if ((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

namespace uasdk
{
UA_DEFINE_RUNTIME_TYPE(DiscreteAlarm_t, AlarmCondition_t);

/*
 * Private Function
 */
Status_t DiscreteAlarm_t::InitialiseConditionDataAttributes(void)
{
  UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData);

  return OpcUa_Good;
}

/*
* Protected Functions
*/

Status_t DiscreteAlarm_t::EvaluteState(uint32_t methodId)
{
  //This condition do not have any variables/States/Methods. Hence Nothing To Do here.
  UASDK_UNUSED(methodId);
  return OpcUa_BadNothingToDo;
}

Status_t DiscreteAlarm_t::InitialiseConditionData(IntrusivePtr_t<ConditionTypeData_t> conditionData_, uint32_t conditionClassId, String_t& conditionName, bool isAllocated)
{
  if (conditionData_.is_set())
  {
    conditionData = RuntimeCast<DiscreteAlarmTypeData_t*>(*conditionData_);
    UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData);
  }
  else if (isAllocated)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }
  else
  {
    conditionData = new SafeRefCount_t<DiscreteAlarmTypeData_t>();
    UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(conditionData);
  }

  Status_t status = AlarmCondition_t::InitialiseConditionData(conditionData, conditionClassId, conditionName, true);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  return DiscreteAlarm_t::InitialiseConditionDataAttributes();
}

Status_t DiscreteAlarm_t::GetEventData(IntrusivePtr_t<IAttributeAccess_t>& data, IntrusivePtr_t<NodeId_t>& sourceNodeId)
{
  Status_t status;

  IntrusivePtr_t<DiscreteAlarmTypeData_t> data_ = new SafeRefCount_t<DiscreteAlarmTypeData_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(data_);

  UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData);
  status = data_->CopyFrom(*conditionData);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  status = EvaluateQualityFromEnabledState(data_->Quality());
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  sourceNodeId = data_->SourceNode();
  data = data_;

  return status;
}

/*
* Public Functions
*/
DiscreteAlarm_t::DiscreteAlarm_t()
{}

DiscreteAlarm_t::~DiscreteAlarm_t()
{}

Status_t DiscreteAlarm_t::Initialise(IntrusivePtr_t<IServerConfiguration_t> configuration_, NodeId_t& conditionId_, uint32_t conditionClassId, String_t& conditionName)
{
  return AlarmCondition_t::Initialise(configuration_, conditionId_, conditionClassId, conditionName);
}

Status_t DiscreteAlarm_t::SetMethodListener(IntrusivePtr_t<IDiscreteAlarmMethodListener_t> value)
{
  conditionMethodListener = value;
  return AlarmCondition_t::SetMethodListener(value);
}

Status_t DiscreteAlarm_t::CallMethodBegin(IntrusivePtr_t<const NodeId_t> sessionId,
  uint32_t transactionId,
  const IUserPermissions_t& userPermissions,
  uint32_t timeoutHint,
  IntrusivePtr_t<INode_t>& componentOf,
  IntrusivePtr_t<IMethodNode_t>& method,
  IntrusivePtr_t<const CallMethodRequest_t>& requestParameters,
  IntrusivePtr_t<CallMethodResult_t>& result,
  IntrusivePtr_t<ICallbackCallMethodCompleted_t>& completedCallback)
{
  //No method is available for DiscreteAlarm, then call the parent class CallMethodBegin
  return AlarmCondition_t::CallMethodBegin(sessionId, transactionId, userPermissions, timeoutHint, componentOf, method, requestParameters, result, completedCallback);
}

Status_t DiscreteAlarm_t::ReadValueAttribute(
  const IVariableNode_t& node,
  uint32_t maxAge,
  bool setSourceTimestamp,
  const ArrayUA_t<String_t>& locales,
  const Array_t<IndexRange_t>& indexRange,
  uint32_t transactionId,
  uint32_t timeoutHint,
  IntrusivePtr_t<DataValue_t>& dataValue,
  IntrusivePtr_t<DiagnosticInfo_t>& diagnosticInfo)
{
  UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData);

  //No variable is available for DiscreteAlarm, then call the parent class ReadValueAttribute
  return AlarmCondition_t::ReadValueAttribute(node, maxAge, setSourceTimestamp, locales, indexRange, transactionId, timeoutHint, dataValue, diagnosticInfo);
}

} // namespace uasdk

#endif //((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))


