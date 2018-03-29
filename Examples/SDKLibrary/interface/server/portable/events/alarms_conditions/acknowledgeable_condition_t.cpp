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

#include "acknowledgeable_condition_t.h"

#if ((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

namespace uasdk
{
UA_DEFINE_RUNTIME_TYPE(AcknowledgeableCondition_t, BaseCondition_t);

static const char* ACKNOWLEDGE_METHOD_SOURCE_NAME = "Method/Acknowledge";
static const char* CONFIRM_METHOD_SOURCE_NAME = "Method/Confirm";

/*
 * Private Function
 */

Status_t AcknowledgeableCondition_t::InitialiseConditionDataAttributes(void)
{
  UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData);

  //AckedState
  IntrusivePtr_t<TwoStateVariableType_t> ackedState_ = new SafeRefCount_t<TwoStateVariableType_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(ackedState_);

  IntrusivePtr_t<ILocalizableText_t> emptyState;

  Status_t status = ackedState_->Initialise(false, emptyState, emptyState);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  conditionData->AckedState() = ackedState_; 

  //ConfirmedState
  IntrusivePtr_t<TwoStateVariableType_t> confirmedState_ = new SafeRefCount_t<TwoStateVariableType_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(confirmedState_);

  status = confirmedState_->Initialise(false, emptyState, emptyState);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  conditionData->ConfirmedState() = confirmedState_; 

  return OpcUa_Good;
}

/*
* Protected Functions
*/

Status_t AcknowledgeableCondition_t::EvaluteState(uint32_t methodId)
{
  Status_t status;

  switch (methodId)
  {
  case OpcUaId_AcknowledgeableConditionType_Acknowledge:
  {
    status = IsAcknowledged() ? OpcUa_BadConditionBranchAlreadyAcked : \
                                (!IsEnabled() ? OpcUa_BadInvalidState: OpcUa_Good);
  }
  break;

  case OpcUaId_AcknowledgeableConditionType_Confirm:
  {
    status = IsConfirmed() ? OpcUa_BadConditionBranchAlreadyConfirmed : \
                              ((!IsEnabled() || !IsAcknowledged()) ? OpcUa_BadInvalidState : OpcUa_Good);
  }
  break;

  default:
    return OpcUa_BadInvalidArgument;

  }
  return status;
}

Status_t AcknowledgeableCondition_t::InitialiseConditionData(IntrusivePtr_t<ConditionTypeData_t> conditionData_, uint32_t conditionClassId, String_t& conditionName, bool isAllocated)
{
  if (conditionData_.is_set())
  {
    conditionData = RuntimeCast<AcknowledgeableConditionTypeData_t*>(*conditionData_);
    UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData);
  }
  else if (isAllocated)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }
  else
  {
    conditionData = new SafeRefCount_t<AcknowledgeableConditionTypeData_t>();
    UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(conditionData);
  }

  Status_t status = BaseCondition_t::InitialiseConditionData(conditionData, conditionClassId, conditionName, true);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  return AcknowledgeableCondition_t::InitialiseConditionDataAttributes();
}

Status_t AcknowledgeableCondition_t::GetEventData(IntrusivePtr_t<IAttributeAccess_t>& data, IntrusivePtr_t<NodeId_t>& sourceNodeId)
{
  Status_t status;

  IntrusivePtr_t<AcknowledgeableConditionTypeData_t> data_ = new SafeRefCount_t<AcknowledgeableConditionTypeData_t>();
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

Status_t AcknowledgeableCondition_t::OnAcknowledge(const IUserPermissions_t& userPermissions, IntrusivePtr_t<const CallMethodRequest_t>& requestParameters)
{
  IntrusivePtr_t<ByteString_t> eventId;
  IntrusivePtr_t<LocalizedText_t> comment;

  Status_t status = AddressSpaceUtilities_t::CastInputArguments(requestParameters->InputArguments(), eventId, comment);
  if (!eventId.is_set() || !comment.is_set() || status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  status = Acknowledge(*eventId, *comment);
  if (conditionMethodListener.is_set())
  {
    conditionMethodListener->OnAcknowledge(*this, userPermissions, *eventId, *comment, status);
  }

  return status;
}

Status_t AcknowledgeableCondition_t::OnConfirm(const IUserPermissions_t& userPermissions, IntrusivePtr_t<const CallMethodRequest_t>& requestParameters)
{
  IntrusivePtr_t<ByteString_t> eventId;
  IntrusivePtr_t<LocalizedText_t> comment;

  Status_t status = AddressSpaceUtilities_t::CastInputArguments(requestParameters->InputArguments(), eventId, comment);
  if (!eventId.is_set() || !comment.is_set() || status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  status = Confirm(*eventId, *comment);
  if (conditionMethodListener.is_set())
  {
    conditionMethodListener->OnConfirm(*this, userPermissions, *eventId, *comment, status);
  }

  return status;
}

/*
* Public Functions
*/
AcknowledgeableCondition_t::AcknowledgeableCondition_t()
{}

AcknowledgeableCondition_t::~AcknowledgeableCondition_t()
{}

Status_t AcknowledgeableCondition_t::Initialise(IntrusivePtr_t<IServerConfiguration_t> configuration_, NodeId_t& conditionId_, uint32_t conditionClassId, String_t& conditionName)
{
  return BaseCondition_t::Initialise(configuration_, conditionId_, conditionClassId, conditionName);
}

Status_t AcknowledgeableCondition_t::InitialiseAckedStateLocalizationValues(IntrusivePtr_t<ILocalizableText_t> ackedStateTrueState, IntrusivePtr_t<ILocalizableText_t> ackedStateFalseState)
{
  UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData);
  UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->AckedState());

  conditionData->AckedState()->TrueState() = ackedStateTrueState;
  conditionData->AckedState()->FalseState() = ackedStateFalseState;

  return OpcUa_Good;
}

Status_t AcknowledgeableCondition_t::InitialiseConfirmedStateLocalizationValues(IntrusivePtr_t<ILocalizableText_t> confirmedStateTrueState, IntrusivePtr_t<ILocalizableText_t> confirmedStateFalseState)
{
  UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData);
  UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->ConfirmedState());

  conditionData->ConfirmedState()->TrueState() = confirmedStateTrueState;
  conditionData->ConfirmedState()->FalseState() = confirmedStateFalseState;

  return OpcUa_Good;
}

bool AcknowledgeableCondition_t::IsAcknowledged()
{
  if (conditionData.is_set() && conditionData->AckedState().is_set())
  {
    return conditionData->AckedState()->Id()->Value();
  }
  else
  {
    return false;
  }
}

bool AcknowledgeableCondition_t::IsConfirmed()
{
  if (conditionData.is_set() && conditionData->ConfirmedState().is_set())
  {
    return conditionData->ConfirmedState()->Id()->Value();
  }
  else
  {
    return false;
  }
}

Status_t AcknowledgeableCondition_t::Acknowledge(ByteString_t& eventId, LocalizedText_t& comment)
{
  Status_t status = EvaluteState(OpcUaId_AcknowledgeableConditionType_Acknowledge);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());  

  int64_t dateTimeValue = UASDK_datetime();

  BeginConditionStateUpdate();

  status = BaseCondition_t::UpdateCommentState(eventId, comment);
  if (status.IsGood())
  {
    //AckedState
    conditionData->AckedState()->EffectiveTransitionTime()->Value(dateTimeValue);
    conditionData->AckedState()->Id()->Value(true);
    conditionData->AckedState()->TransitionTime()->Value(dateTimeValue);

    //ConfirmedState
    conditionData->ConfirmedState()->EffectiveTransitionTime()->Value(dateTimeValue);
    conditionData->ConfirmedState()->Id()->Value(false);
    conditionData->ConfirmedState()->TransitionTime()->Value(dateTimeValue);
  }

  EndConditionStateUpdate();
  
  //FireAuditConditon Event  
  String_t sourceName;
  status = sourceName.CopyFrom(ACKNOWLEDGE_METHOD_SOURCE_NAME);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  LocalizedText_t message;
  status = message.Locale().CopyFrom(LOCALE_DEFAULT);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
  status = message.Text().CopyFrom(ACKNOWLEDGE_METHOD_MESSAGE);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  uint32_t methodIdentifier = OpcUaId_AcknowledgeableConditionType_Acknowledge;
  IntrusivePtr_t<NodeId_t> methodId;
  status = GetMethodNodeIdFromStandardNodeId(methodIdentifier, methodId);
  if (status.IsBad() || !methodId.is_set())
  {
    NodeIdNumeric_t methodIdTemp;
    methodIdTemp.Initialise(0, methodIdentifier);
    status = methodIdTemp.CopyToNodeId(methodId);
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
  }

  if (configuration->EventTypesActivationStatus() & ENABLE_AUDIT_CONDITION_ACKNOWLEDGE_EVENT_TYPE)
  {
    Status_t auditEventStatus = EventHelper_t::FireAuditConditionEvents(configuration, conditionId, OpcUaId_AuditConditionAcknowledgeEventType, sourceName, message, methodId, eventId, comment);
    if (auditEventStatus.IsBad())
    {
      //Log it
    }
  }

  return status;
}

Status_t AcknowledgeableCondition_t::Confirm(ByteString_t& eventId, LocalizedText_t& comment)
{
  Status_t status = EvaluteState(OpcUaId_AcknowledgeableConditionType_Confirm);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  int64_t dateTimeValue = UASDK_datetime();

  BeginConditionStateUpdate();

  status = BaseCondition_t::UpdateCommentState(eventId, comment);
  if (status.IsGood())
  {
    //ConfirmedState
    conditionData->ConfirmedState()->EffectiveTransitionTime()->Value(dateTimeValue);
    conditionData->ConfirmedState()->Id()->Value(true);
    conditionData->ConfirmedState()->TransitionTime()->Value(dateTimeValue);
  }

  EndConditionStateUpdate();

  //FireAuditConditon Event  
  String_t sourceName;
  status = sourceName.CopyFrom(CONFIRM_METHOD_SOURCE_NAME);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  LocalizedText_t message;
  status = message.Locale().CopyFrom(LOCALE_DEFAULT);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
  status = message.Text().CopyFrom(CONFIRM_METHOD_MESSAGE);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  uint32_t methodIdentifier = OpcUaId_AcknowledgeableConditionType_Confirm;
  IntrusivePtr_t<NodeId_t> methodId;
  status = GetMethodNodeIdFromStandardNodeId(methodIdentifier, methodId);
  if (status.IsBad() || !methodId.is_set())
  {
    NodeIdNumeric_t methodIdTemp;
    methodIdTemp.Initialise(0, methodIdentifier);
    status = methodIdTemp.CopyToNodeId(methodId);
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
  }

  if (configuration->EventTypesActivationStatus() & ENABLE_AUDIT_CONDITION_CONFIRM_EVENT_TYPE)
  {
    Status_t auditEventStatus = EventHelper_t::FireAuditConditionEvents(configuration, conditionId, OpcUaId_AuditConditionConfirmEventType, sourceName, message, methodId, eventId, comment);
    if (auditEventStatus.IsBad())
    {
      //Log it
    }
  }

  return status;
}

Status_t AcknowledgeableCondition_t::SetMethodListener(IntrusivePtr_t<IAcknowledgableConditionMethodListener_t> value)
{
  conditionMethodListener = value;
  return BaseCondition_t::SetMethodListener(value);
}

Status_t AcknowledgeableCondition_t::CallMethodBegin(IntrusivePtr_t<const NodeId_t> sessionId,
  uint32_t transactionId,
  const IUserPermissions_t& userPermissions,
  uint32_t timeoutHint,
  IntrusivePtr_t<INode_t>& componentOf,
  IntrusivePtr_t<IMethodNode_t>& method,
  IntrusivePtr_t<const CallMethodRequest_t>& requestParameters,
  IntrusivePtr_t<CallMethodResult_t>& result,
  IntrusivePtr_t<ICallbackCallMethodCompleted_t>& completedCallback)
{
  if (!method.is_set() || !method->BrowseName().is_set() || !completedCallback.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  Status_t status;

  uint32_t standardNodeId = GetStandardNodeId(*method);
  switch (standardNodeId)
  {
  case OpcUaId_AcknowledgeableConditionType_Acknowledge:
    status = OnAcknowledge(userPermissions, requestParameters);
    break;

  case OpcUaId_AcknowledgeableConditionType_Confirm:
    status = OnConfirm(userPermissions, requestParameters);
    break;

  default:
    //If method is not found then call the parent class CallMethodBegin is called
    return BaseCondition_t::CallMethodBegin(sessionId, transactionId, userPermissions, timeoutHint, componentOf, method, requestParameters, result, completedCallback);
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

Status_t AcknowledgeableCondition_t::ReadValueAttribute(
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
  UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->AckedState());
  UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->ConfirmedState());

  Status_t status;
  IntrusivePtr_t<BaseDataType_t> value;

  uint32_t standardNodeId = GetStandardNodeId(node);
  switch (standardNodeId)
  {
  case OpcUaId_AcknowledgeableConditionType_AckedState:
  {
    IntrusivePtr_t<const ILocalizableText_t> ackedStateValue = conditionData->AckedState()->Value();
    if (!ackedStateValue.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
    }
    IntrusivePtr_t<const LocalizedText_t> ackedStateResolvedValue = ackedStateValue->GetLocalizedText(locales, status);
    if (ackedStateResolvedValue.is_set() && status.IsGood())
    {
      status = ackedStateResolvedValue->CopyTo(value);
    }
  }
  break;

  case OpcUaId_AcknowledgeableConditionType_AckedState_FalseState:
  {
    IntrusivePtr_t<const ILocalizableText_t> state_ = conditionData->AckedState()->FalseState();
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

  case OpcUaId_AcknowledgeableConditionType_AckedState_Id:
  {
    status = conditionData->AckedState()->Id()->CopyTo(value);
  }
  break;

  case OpcUaId_AcknowledgeableConditionType_AckedState_TransitionTime:
  {
    status = conditionData->AckedState()->TransitionTime()->CopyTo(value);
  }
  break;

  case OpcUaId_AcknowledgeableConditionType_AckedState_EffectiveTransitionTime:
  {
    status = conditionData->AckedState()->EffectiveTransitionTime()->CopyTo(value);
  }
  break;

  case OpcUaId_AcknowledgeableConditionType_AckedState_TrueState:
  {
    IntrusivePtr_t<const ILocalizableText_t> state_ = conditionData->AckedState()->TrueState();
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

  case OpcUaId_AcknowledgeableConditionType_ConfirmedState:
  {
    IntrusivePtr_t<const ILocalizableText_t> confirmedStateValue = conditionData->ConfirmedState()->Value();
    if (!confirmedStateValue.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
    }
    IntrusivePtr_t<const LocalizedText_t> confirmedStateResolvedValue = confirmedStateValue->GetLocalizedText(locales, status);
    if (confirmedStateResolvedValue.is_set() && status.IsGood())
    {
      status = confirmedStateResolvedValue->CopyTo(value);
    }
  }
  break;

  case OpcUaId_AcknowledgeableConditionType_ConfirmedState_FalseState:
  {
    IntrusivePtr_t<const ILocalizableText_t> state_ = conditionData->ConfirmedState()->FalseState();
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

  case OpcUaId_AcknowledgeableConditionType_ConfirmedState_Id:
  {
    status = conditionData->ConfirmedState()->Id()->CopyTo(value);
  }
  break;

  case OpcUaId_AcknowledgeableConditionType_ConfirmedState_TransitionTime:
  {
    status = conditionData->ConfirmedState()->TransitionTime()->CopyTo(value);
  }
  break;

  case OpcUaId_AcknowledgeableConditionType_ConfirmedState_EffectiveTransitionTime:
  {
    status = conditionData->ConfirmedState()->EffectiveTransitionTime()->CopyTo(value);
  }
  break;

  case OpcUaId_AcknowledgeableConditionType_ConfirmedState_TrueState:
  {
    IntrusivePtr_t<const ILocalizableText_t> state_ = conditionData->ConfirmedState()->TrueState();
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

  default:
    return BaseCondition_t::ReadValueAttribute(node, maxAge, setSourceTimestamp, locales, indexRange, transactionId, timeoutHint, dataValue, diagnosticInfo);
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


