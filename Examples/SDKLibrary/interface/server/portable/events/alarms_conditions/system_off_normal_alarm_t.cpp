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

#include "system_off_normal_alarm_t.h"

#if ((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

namespace uasdk
{
UA_DEFINE_RUNTIME_TYPE(SystemOffNormalAlarm_t, OffNormalAlarm_t);

/*
 * Private Function
 */
Status_t SystemOffNormalAlarm_t::InitialiseConditionDataAttributes(void)
{
  return OpcUa_Good;
}

/*
* Protected Functions
*/

Status_t SystemOffNormalAlarm_t::EvaluteState(uint32_t methodId)
{
  //This condition do not have any variables/States/Methods. Hence Nothing To Do here.
  UASDK_UNUSED(methodId);
  return OpcUa_BadNothingToDo;
}

Status_t SystemOffNormalAlarm_t::InitialiseConditionData(IntrusivePtr_t<ConditionTypeData_t> conditionData_, uint32_t conditionClassId, String_t& conditionName, bool isAllocated)
{
  if (conditionData_.is_set())
  {
    conditionData = RuntimeCast<SystemOffNormalAlarmTypeData_t*>(*conditionData_);
    UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData);
  }
  else if (isAllocated)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }
  else
  {
    conditionData = new SafeRefCount_t<SystemOffNormalAlarmTypeData_t>();
    UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(conditionData);
  }

  Status_t status = OffNormalAlarm_t::InitialiseConditionData(conditionData, conditionClassId, conditionName, true);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  return SystemOffNormalAlarm_t::InitialiseConditionDataAttributes();
}

Status_t SystemOffNormalAlarm_t::GetEventData(IntrusivePtr_t<IAttributeAccess_t>& data, IntrusivePtr_t<NodeId_t>& sourceNodeId)
{
  Status_t status;

  IntrusivePtr_t<SystemOffNormalAlarmTypeData_t> data_ = new SafeRefCount_t<SystemOffNormalAlarmTypeData_t>();
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
SystemOffNormalAlarm_t::SystemOffNormalAlarm_t()
{}

SystemOffNormalAlarm_t::~SystemOffNormalAlarm_t()
{}

Status_t SystemOffNormalAlarm_t::Initialise(IntrusivePtr_t<IServerConfiguration_t> configuration_, NodeId_t& conditionId_, uint32_t conditionClassId, String_t& conditionName)
{
  return OffNormalAlarm_t::Initialise(configuration_, conditionId_, conditionClassId, conditionName);
}

Status_t SystemOffNormalAlarm_t::SetMethodListener(IntrusivePtr_t<ISystemOffNormalAlarmMethodListener_t> value)
{
  conditionMethodListener = value;
  return OffNormalAlarm_t::SetMethodListener(value);
}

Status_t SystemOffNormalAlarm_t::CallMethodBegin(IntrusivePtr_t<const NodeId_t> sessionId,
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
  return OffNormalAlarm_t::CallMethodBegin(sessionId, transactionId, userPermissions, timeoutHint, componentOf, method, requestParameters, result, completedCallback);
}

Status_t SystemOffNormalAlarm_t::ReadValueAttribute(
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
  //No variable is available for SystemOffNormalAlarm, then call the parent class ReadValueAttribute
  return OffNormalAlarm_t::ReadValueAttribute(node, maxAge, setSourceTimestamp, locales, indexRange, transactionId, timeoutHint, dataValue, diagnosticInfo);
}

} // namespace uasdk

#endif //((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))


