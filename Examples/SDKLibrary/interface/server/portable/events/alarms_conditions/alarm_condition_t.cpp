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

#include "alarm_condition_t.h"

#if ((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

namespace uasdk
{
UA_DEFINE_RUNTIME_TYPE(AlarmCondition_t, AcknowledgeableCondition_t);

/*
 * Private Function
 */
Status_t AlarmCondition_t::InitialiseConditionDataAttributes(void)
{
  UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData);

  //ActiveState
  IntrusivePtr_t<TwoStateVariableType_t> activeState_ = new SafeRefCount_t<TwoStateVariableType_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(activeState_);

  IntrusivePtr_t<ILocalizableText_t> emptyState;

  Status_t status = activeState_->Initialise(false, emptyState, emptyState);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  conditionData->ActiveState() = activeState_;

  //InputNode
  IntrusivePtr_t<NodeIdNumeric_t> inputNode_ = new SafeRefCount_t<NodeIdNumeric_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(inputNode_);

  conditionData->InputNode() = inputNode_;

  //SuppressedState
  IntrusivePtr_t<TwoStateVariableType_t> suppressedState_ = new SafeRefCount_t<TwoStateVariableType_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(suppressedState_);


  status = suppressedState_->Initialise(false, emptyState, emptyState);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  conditionData->SuppressedState() = suppressedState_;
 
  //SuppressedOrShelved
  IntrusivePtr_t<Boolean_t> suppressedOrShelved_ = new SafeRefCount_t<Boolean_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(suppressedOrShelved_);
  suppressedOrShelved_->Value(false);
  conditionData->SuppressedOrShelved() = suppressedOrShelved_;

  //MaxTimeShelved
  IntrusivePtr_t<Duration_t> maxTimeShelved_ = new SafeRefCount_t<Duration_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(maxTimeShelved_);
  maxTimeShelved_->Value(0.0);
  conditionData->MaxTimeShelved() = maxTimeShelved_;

  return OpcUa_Good;
}

Status_t AlarmCondition_t::UpdateActiveState(bool isActive, Status_t quality, uint16_t severity)
{
  Status_t status;

  UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData);
  UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->ActiveState());
  UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->Quality());
  UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->LastSeverity());
  UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->Severity());
  UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->AckedState());
  UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->ConfirmedState());

  IntrusivePtr_t<StatusCode_t> quality_ = new SafeRefCount_t<StatusCode_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(quality_);
  quality_->Value().Value(quality.Value());

  IntrusivePtr_t<UInt16_t> severity_ = new SafeRefCount_t<UInt16_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(severity_);
  severity_->Value(severity);

  IntrusivePtr_t<UInt16_t> lastSeverity_ = new SafeRefCount_t<UInt16_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(severity_);

  status = lastSeverity_->CopyFrom(*conditionData->Severity());
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  int64_t dateTimeValue = UASDK_datetime();

  BeginConditionStateUpdate();
  
  conditionData->LastSeverity()->Value() = lastSeverity_;
  conditionData->Severity() = severity_;

  conditionData->Quality()->Value() = quality_;
  if (conditionData->Quality()->SourceTimestamp().is_set())
  {
    conditionData->Quality()->SourceTimestamp()->Value(dateTimeValue);
  }

  if (conditionData->Time().is_set())
  {
    conditionData->Time()->Value(dateTimeValue);
  }
  
  conditionData->ActiveState()->EffectiveTransitionTime()->Value(dateTimeValue);
  conditionData->ActiveState()->Id()->Value(isActive);
  conditionData->ActiveState()->TransitionTime()->Value(dateTimeValue);
  
  if (isActive)
  {
    //If going active, or updating quality/severity reset confirmed and acknowledged states.
    conditionData->AckedState()->Id()->Value(false);
    conditionData->AckedState()->EffectiveTransitionTime()->Value(dateTimeValue);
    conditionData->AckedState()->TransitionTime()->Value(dateTimeValue);

    conditionData->ConfirmedState()->Id()->Value(false);
    conditionData->ConfirmedState()->EffectiveTransitionTime()->Value(dateTimeValue);
    conditionData->ConfirmedState()->TransitionTime()->Value(dateTimeValue);
  }

  EndConditionStateUpdate();

  return status;
}

bool AlarmCondition_t::MayFireEventNotification(void)
{
  //Note:  When shelving is implemented, the shelved state should be considered here too.
  if (conditionData.is_set() && conditionData->SuppressedState().is_set())
  {
    return IsEnabled() && !(conditionData->SuppressedState()->Id()->Value());
  }
  else
  {
    return IsEnabled();
  }
}

Status_t AlarmCondition_t::UpdateSuppressedState(bool isSuppressed, Status_t quality, uint16_t severity)
{
  Status_t status;

  UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData);
  UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->SuppressedState());
  UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->SuppressedOrShelved());
  UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->Quality());
  UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->LastSeverity());
  UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->Severity());

  IntrusivePtr_t<StatusCode_t> quality_ = new SafeRefCount_t<StatusCode_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(quality_);
  quality_->Value().Value(quality.Value());

  IntrusivePtr_t<UInt16_t> severity_ = new SafeRefCount_t<UInt16_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(severity_);
  severity_->Value(severity);

  IntrusivePtr_t<UInt16_t> lastSeverity_ = new SafeRefCount_t<UInt16_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(severity_);

  status = lastSeverity_->CopyFrom(*conditionData->Severity());
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());  

  int64_t dateTimeValue = UASDK_datetime();

  BeginConditionStateUpdate();

  conditionData->LastSeverity()->Value() = lastSeverity_;
  conditionData->Severity() = severity_;

  conditionData->Quality()->Value() = quality_;
  if (conditionData->Quality()->SourceTimestamp().is_set())
  {
    conditionData->Quality()->SourceTimestamp()->Value(dateTimeValue);
  }

  if (conditionData->Time().is_set())
  {
    conditionData->Time()->Value(dateTimeValue);
  }

  conditionData->SuppressedState()->EffectiveTransitionTime()->Value(dateTimeValue);
  conditionData->SuppressedState()->Id()->Value(isSuppressed);
  conditionData->SuppressedState()->TransitionTime()->Value(dateTimeValue);

  //Note: When shelving is implemented, this will have to be updated to check the shelved state.
  conditionData->SuppressedOrShelved()->Value(isSuppressed);
  
  EndConditionStateUpdate();

  return status;
}

/*
* Protected Functions
*/

void AlarmCondition_t::TimerCompleteCallback(void)
{
}

Status_t AlarmCondition_t::EvaluteState(uint32_t methodId)
{
  //This condition do not have any variables/States/Methods. Hence Nothing To Do here.
  UASDK_UNUSED(methodId);
  return OpcUa_BadNothingToDo;
}

Status_t AlarmCondition_t::InitialiseConditionData(IntrusivePtr_t<ConditionTypeData_t> conditionData_, uint32_t conditionClassId, String_t& conditionName, bool isAllocated)
{
  if (conditionData_.is_set())
  {
    conditionData = RuntimeCast<AlarmConditionTypeData_t*>(*conditionData_);
    UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData);
  }
  else if (isAllocated)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }
  else
  {
    conditionData = new SafeRefCount_t<AlarmConditionTypeData_t>();
    UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(conditionData);
  }

  Status_t status = AcknowledgeableCondition_t::InitialiseConditionData(conditionData, conditionClassId, conditionName, true);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  return AlarmCondition_t::InitialiseConditionDataAttributes();
}

Status_t AlarmCondition_t::GetEventData(IntrusivePtr_t<IAttributeAccess_t>& data, IntrusivePtr_t<NodeId_t>& sourceNodeId)
{
  Status_t status;

  IntrusivePtr_t<AlarmConditionTypeData_t> data_ = new SafeRefCount_t<AlarmConditionTypeData_t>();
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

Status_t AlarmCondition_t::OnUnShelve(const IUserPermissions_t& userPermissions)
{
  Status_t status = UnShelved();
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
  if (conditionMethodListener.is_set())
  {
    conditionMethodListener->OnUnShelve(*this, userPermissions, status);
  }

  return status;
}

Status_t AlarmCondition_t::OnTimedShelve(const IUserPermissions_t& userPermissions, IntrusivePtr_t<const CallMethodRequest_t>& requestParameters)
{
  IntrusivePtr_t<Duration_t> shelvingTime;

  Status_t status = AddressSpaceUtilities_t::CastInputArguments(requestParameters->InputArguments(), shelvingTime);
  if (!shelvingTime.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  status = TimedShelve(*shelvingTime);
  if (conditionMethodListener.is_set())
  {
    conditionMethodListener->OnTimedShelve(*this, userPermissions, *shelvingTime, status);
  }

  return status;
}

Status_t AlarmCondition_t::OnOneShotShelve(const IUserPermissions_t& userPermissions)
{
  UASDK_UNUSED(userPermissions);
  return OneShotShelve();
}

/*
* Public Functions
*/
AlarmCondition_t::AlarmCondition_t()
{}

AlarmCondition_t::~AlarmCondition_t()
{}

Status_t AlarmCondition_t::Initialise(IntrusivePtr_t<IServerConfiguration_t> configuration_, NodeId_t& conditionId_, uint32_t conditionClassId, String_t& conditionName)
{
  return AcknowledgeableCondition_t::Initialise(configuration_, conditionId_, conditionClassId, conditionName);
}

Status_t AlarmCondition_t::InitialiseInputNode(IntrusivePtr_t<NodeId_t> inputNode_)
{
  UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData);
  UASDK_RETURN_INVALID_ARGUMENT_IF_NULL(inputNode_);

  conditionData->InputNode() = inputNode_;

  return OpcUa_Good;
}

Status_t AlarmCondition_t::InitialiseActiveStateLocalizationValues(IntrusivePtr_t<ILocalizableText_t> activeStateTrueState, IntrusivePtr_t<ILocalizableText_t> activeStateFalseState)
{
  UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData);
  UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->ActiveState());

  conditionData->ActiveState()->TrueState() = activeStateTrueState;
  conditionData->ActiveState()->FalseState() = activeStateFalseState;

  return OpcUa_Good;
}

Status_t AlarmCondition_t::InitialiseSuppressedStateLocalizationValues(IntrusivePtr_t<ILocalizableText_t> suppressedStateTrueState, IntrusivePtr_t<ILocalizableText_t> suppressedStateFalseState)
{
  UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData);
  UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->SuppressedState());

  conditionData->SuppressedState()->TrueState() = suppressedStateTrueState;
  conditionData->SuppressedState()->FalseState() = suppressedStateFalseState;

  return OpcUa_Good;
}

bool AlarmCondition_t::IsActive(void)
{
  if (conditionData.is_set() && conditionData->ActiveState().is_set())
  {
    return conditionData->ActiveState()->Id()->Value();
  }
  else
  {
    return false;
  }
}

bool AlarmCondition_t::IsSuppressed(void)
{
  if (conditionData.is_set() && conditionData->SuppressedState().is_set())
  {
    return conditionData->SuppressedState()->Id()->Value();
  }
  else
  {
    return false;
  }
}

bool AlarmCondition_t::IsShelved(void)
{
  return false;
}

Duration_t AlarmCondition_t::UnshelveTime(void)
{
  return unshelveTime;
}

Status_t AlarmCondition_t::UnShelved(void)
{
  return OpcUa_BadNotImplemented;
}

Status_t AlarmCondition_t::TimedShelve(Duration_t shelvingTime)
{
  UASDK_UNUSED(shelvingTime);
  return OpcUa_BadNotImplemented;
}

Status_t AlarmCondition_t::OneShotShelve(void)
{
  return OpcUa_BadNotImplemented;
}

Status_t AlarmCondition_t::SetMethodListener(IntrusivePtr_t<IAlarmConditionMethodListener_t> value)
{
  conditionMethodListener = value;
  return AcknowledgeableCondition_t::SetMethodListener(value);
}

Status_t AlarmCondition_t::TransitionToActiveState(Status_t quality, uint16_t severity)
{
  return UpdateActiveState(true, quality, severity);
}

Status_t AlarmCondition_t::TransitionToInactiveState(Status_t quality, uint16_t severity)
{
  return UpdateActiveState(false, quality, severity);
}

Status_t AlarmCondition_t::TransitionToSuppressedState(Status_t quality, uint16_t severity)
{
  return UpdateSuppressedState(true, quality, severity);
}

Status_t AlarmCondition_t::TransitionToUnsuppressedState(Status_t quality, uint16_t severity)
{
  return UpdateSuppressedState(false, quality, severity);
}

Status_t AlarmCondition_t::CallMethodBegin(IntrusivePtr_t<const NodeId_t> sessionId,
  uint32_t transactionId,
  const IUserPermissions_t& userPermissions,
  uint32_t timeoutHint,
  IntrusivePtr_t<INode_t>& componentOf,
  IntrusivePtr_t<IMethodNode_t>& method,
  IntrusivePtr_t<const CallMethodRequest_t>& requestParameters,
  IntrusivePtr_t<CallMethodResult_t>& result,
  IntrusivePtr_t<ICallbackCallMethodCompleted_t>& completedCallback)
{
  if (!method.is_set() || !completedCallback.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  Status_t status;

  uint32_t standardNodeId = GetStandardNodeId(*method);
  switch (standardNodeId)
  {
  case OpcUaId_AlarmConditionType_ShelvingState_Unshelve:
  case OpcUaId_AlarmConditionType_ShelvingState_OneShotShelve:
  case OpcUaId_AlarmConditionType_ShelvingState_TimedShelve:
    status = OpcUa_BadNotImplemented;
    break;
  default:
    //If method is not found then call the parent class CallMethodBegin is called
    return AcknowledgeableCondition_t::CallMethodBegin(sessionId, transactionId, userPermissions, timeoutHint, componentOf, method, requestParameters, result, completedCallback);
  }

  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  result.reset(new SafeRefCount_t<CallMethodResult_t>());
  if (!result.is_set())
  {
    return OpcUa_BadOutOfMemory;
  }
  result->StatusCode() = OpcUa_Good;

  return completedCallback->CallMethodCompleted(result);
}

Status_t AlarmCondition_t::ReadValueAttribute(
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
  UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->ActiveState());
  UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->SuppressedState());  

  Status_t status;
  IntrusivePtr_t<BaseDataType_t> value;

  uint32_t standardNodeId = GetStandardNodeId(node);
  switch (standardNodeId)
  {
  case OpcUaId_AlarmConditionType_ActiveState:
  {
    IntrusivePtr_t<const ILocalizableText_t> activeStateValue = conditionData->ActiveState()->Value();
    if (!activeStateValue.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
    }
    IntrusivePtr_t<const LocalizedText_t> activeStateResolvedValue = activeStateValue->GetLocalizedText(locales, status);
    if (activeStateResolvedValue.is_set() && status.IsGood())
    {
      status = activeStateResolvedValue->CopyTo(value);
    }
  }
  break;

  case OpcUaId_AlarmConditionType_ActiveState_EffectiveTransitionTime:
  {
    status = conditionData->ActiveState()->EffectiveTransitionTime()->CopyTo(value);
  }
  break;

  case OpcUaId_AlarmConditionType_ActiveState_FalseState:
  {
    IntrusivePtr_t<const ILocalizableText_t> state_ = conditionData->ActiveState()->FalseState();
    if (!state_.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
    }
    IntrusivePtr_t<const LocalizedText_t> stateResolvedValue = state_->GetLocalizedText(locales, status);
    if (stateResolvedValue.is_set() && status.IsGood())
    {
      status = stateResolvedValue->CopyTo(value);
    }
  }
  break;

  case OpcUaId_AlarmConditionType_ActiveState_Id:
  {
    status = conditionData->ActiveState()->Id()->CopyTo(value);
  }
  break;

  case OpcUaId_AlarmConditionType_ActiveState_TransitionTime:
  {
    status = conditionData->ActiveState()->TransitionTime()->CopyTo(value);
  }
  break;

  case OpcUaId_AlarmConditionType_ActiveState_TrueState:
  {
    IntrusivePtr_t<const ILocalizableText_t> state_ = conditionData->ActiveState()->TrueState();
    if (!state_.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
    }
    IntrusivePtr_t<const LocalizedText_t> stateResolvedValue = state_->GetLocalizedText(locales, status);
    if (stateResolvedValue.is_set() && status.IsGood())
    {
      status = stateResolvedValue->CopyTo(value);
    }
  }
  break;

  case OpcUaId_AlarmConditionType_InputNode:
  {
    if (!conditionData->InputNode().is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
    }
    status = conditionData->InputNode()->CopyTo(value);
  }
  break;

  case OpcUaId_AlarmConditionType_SuppressedState:
  {
    IntrusivePtr_t<const ILocalizableText_t> suppressedStateValue = conditionData->SuppressedState()->Value();
    if (!suppressedStateValue.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
    }
    IntrusivePtr_t<const LocalizedText_t> suppressedStateResolvedValue = suppressedStateValue->GetLocalizedText(locales, status);
    if (suppressedStateResolvedValue.is_set() && status.IsGood())
    {
      status = suppressedStateResolvedValue->CopyTo(value);
    }
  }
  break;

  case OpcUaId_AlarmConditionType_SuppressedState_EffectiveTransitionTime:
  {
    status = conditionData->SuppressedState()->EffectiveTransitionTime()->CopyTo(value);
  }
  break;

  case OpcUaId_AlarmConditionType_SuppressedState_FalseState:
  {
    IntrusivePtr_t<const ILocalizableText_t> state_ = conditionData->SuppressedState()->FalseState();
    if (!state_.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
    }
    IntrusivePtr_t<const LocalizedText_t> stateResolvedValue = state_->GetLocalizedText(locales, status);
    if (stateResolvedValue.is_set() && status.IsGood())
    {
      status = stateResolvedValue->CopyTo(value);
    }
  }
  break;

  case OpcUaId_AlarmConditionType_SuppressedState_Id:
  {
    status = conditionData->SuppressedState()->Id()->CopyTo(value);
  }
  break;

  case OpcUaId_AlarmConditionType_SuppressedState_TransitionTime:
  {
    status = conditionData->SuppressedState()->TransitionTime()->CopyTo(value);
  }
  break;

  case OpcUaId_AlarmConditionType_SuppressedState_TrueState:
  {
    IntrusivePtr_t<const ILocalizableText_t> state_ = conditionData->SuppressedState()->TrueState();
    if (!state_.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
    }
    IntrusivePtr_t<const LocalizedText_t> stateResolvedValue = state_->GetLocalizedText(locales, status);
    if (stateResolvedValue.is_set() && status.IsGood())
    {
      status = stateResolvedValue->CopyTo(value);
    }
  }
  break;

  case OpcUaId_AlarmConditionType_SuppressedOrShelved:
  {
    UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->SuppressedOrShelved());
    status = conditionData->SuppressedOrShelved()->CopyTo(value);
  }
  break;

  case OpcUaId_AlarmConditionType_MaxTimeShelved:
  {
    UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->MaxTimeShelved());
    status = conditionData->MaxTimeShelved()->CopyTo(value);
  }
  break;

  default:
    return AcknowledgeableCondition_t::ReadValueAttribute(node, maxAge, setSourceTimestamp, locales, indexRange, transactionId, timeoutHint, dataValue, diagnosticInfo);
  }

  if (!value.is_set() || status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  uint32_t statusCode = IsEnabled() ? OpcUa_Good : OpcUa_BadConditionDisabled;

  return AddressSpaceModeler_t::ReadValue(*value, setSourceTimestamp, statusCode, dataValue);
}

} // namespace uasdk

#endif //((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))


