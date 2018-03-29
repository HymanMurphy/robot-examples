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

#include "base_condition_t.h"

#if ((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(BaseCondition_t, ICondition_t);

static const char* ENABLE_METHOD_SOURCE_NAME = "Method/Enable";
static const char* DISABLE_METHOD_SOURCE_NAME = "Method/Disable";
static const char* ADD_COMMENT_METHOD_SOURCE_NAME = "Method/Comment";

/*
 * Private Function
 */
Status_t BaseCondition_t::InitialiseConditionDataAttributes(uint32_t conditionClassId, String_t& conditionName)
{
  if (!configuration.is_set() || !configuration->AddressSpace().is_set() || !conditionData.is_set() || !conditionId.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  Status_t status;

  //Base Event Properties
  IntrusivePtr_t<NodeId_t> sourceNode;

  IntrusivePtr_t<String_t> sourceName = new SafeRefCount_t<String_t>();
  UASDK_RETURN_UNEXPECTED_IF_NULL(sourceName);
  status = sourceName->CopyFrom(conditionName);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  IntrusivePtr_t<ILocalizableText_t> localizableText;
  IntrusivePtr_t<const ArrayUA_t<String_t> > localeIds;

  status = EventHelper_t::CreateEventAndSetBaseEventProperties(configuration, sourceNode, sourceName,
    EventSeverity_t::OPCUA_EVENT_SEVERITY_LOW, localizableText, localeIds, conditionData, true);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  //ConditionClassId
  NodeIdNumeric_t conditionClassId_(0, conditionClassId);
  IntrusivePtr_t<INode_t> conditionClassNode = configuration->AddressSpace()->FindNode(conditionClassId_, status);
  if (!conditionClassNode.is_set() || status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  UASDK_RETURN_UNEXPECTED_IF_NULL(conditionClassNode->NodeId());
  status = conditionClassNode->NodeId()->CopyToNodeId(conditionData->ConditionClassId());
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  //ConditionClassName
  IntrusivePtr_t<LocalizableTextFromDisplayName_t> textFromDisplayName = new SafeRefCount_t<LocalizableTextFromDisplayName_t>();
  if (!textFromDisplayName.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  status = textFromDisplayName->Initialise(conditionClassNode);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  IntrusivePtr_t<const LocalizedText_t> localizedText_ = textFromDisplayName->GetLocalizedText(status);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
  UASDK_RETURN_UNEXPECTED_IF_NULL(localizedText_);

  IntrusivePtr_t<LocalizedText_t> conditionClassName_ = new SafeRefCount_t<LocalizedText_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(conditionClassName_);

  status = conditionClassName_->CopyFrom(*localizedText_);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  conditionData->ConditionClassName() = conditionClassName_;
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  //ConditionName
  IntrusivePtr_t<String_t> conditionName_ = new SafeRefCount_t<String_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(conditionName_);

  status = conditionName_->CopyFrom(conditionName);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  conditionData->ConditionName() = conditionName_;

  //BranchId
  IntrusivePtr_t<NodeId_t> branchId_ = new SafeRefCount_t<NodeIdNumeric_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(branchId_);

  conditionData->BranchId() = branchId_;

  //EanbledState
  IntrusivePtr_t<TwoStateVariableType_t> enabledState_ = new SafeRefCount_t<TwoStateVariableType_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(enabledState_);

  IntrusivePtr_t<ILocalizableText_t> emptyState;
  status = enabledState_->Initialise(true, emptyState, emptyState);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  conditionData->EnabledState() = enabledState_;

  //Retain
  IntrusivePtr_t<Boolean_t> retain_ = new SafeRefCount_t<Boolean_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(retain_);

  retain_->Value(IsEnabled());
  conditionData->Retain() = retain_;

  //Quality
  IntrusivePtr_t<ConditionVariableType_t> quality_ = ConditionVariableType_t::CreateConditionVariableTypeWithDefaultValues(OpcUaId_StatusCode, status);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
  conditionData->Quality() = quality_;

  //LastSeverity
  IntrusivePtr_t<ConditionVariableType_t> lastSeverity_ = ConditionVariableType_t::CreateConditionVariableTypeWithDefaultValues(OpcUaId_UInt16, status);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
  conditionData->LastSeverity() = lastSeverity_;

  //Comment
  IntrusivePtr_t<ConditionVariableType_t> comment_ = ConditionVariableType_t::CreateConditionVariableTypeWithDefaultValues(OpcUaId_LocalizedText, status);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
  conditionData->Comment() = comment_;

  //ClientUserId
  IntrusivePtr_t<String_t> clientUserId_ = new SafeRefCount_t<String_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(clientUserId_);
  conditionData->ClientUserId() = clientUserId_;

  //Default attributes

  //AttributeNodeId
  status = conditionId->CopyToNodeId(conditionData->AttributeNodeId());
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  //AttributeDataType
  uint16_t namespaceIndex = 0;
  NodeIdNumeric_t attributeDataType_;
  attributeDataType_.Initialise(namespaceIndex, conditionData->TypeId(namespaceIndex));

  status = attributeDataType_.CopyToNodeId(conditionData->AttributeDataType());
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  //AttributeBrowseName
  IntrusivePtr_t<QualifiedName_t> attributeBrowseName_ = new SafeRefCount_t<QualifiedName_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(attributeBrowseName_);
  attributeBrowseName_->NamespaceIndex().Value(conditionId->NamespaceIndex().Value());

  status = attributeBrowseName_->Name().CopyFrom(conditionName);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  conditionData->AttributeBrowseName() = attributeBrowseName_;

  return status;
}

Status_t BaseCondition_t::UpdateEnabledState(bool isEnabled_)
{
  Status_t status;

  UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData);
  UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->EnabledState());

  IntrusivePtr_t<Boolean_t> retain_ = new SafeRefCount_t<Boolean_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(retain_);
  retain_->Value(isEnabled_);

  int64_t dateTimeValue = UASDK_datetime();

  conditionData->EnabledState()->EffectiveTransitionTime()->Value(dateTimeValue);
  conditionData->EnabledState()->Id()->Value(isEnabled_);
  conditionData->EnabledState()->TransitionTime()->Value(dateTimeValue);

  conditionData->Retain() = retain_;

  ConditionStateUpdated();

  //FireAuditConditon Event  
  String_t sourceName;
  LocalizedText_t message;

  ByteString_t affectedEventId;
  LocalizedText_t comment;
  uint32_t methodIdentifier = 0;

  status = message.Locale().CopyFrom(LOCALE_DEFAULT);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  if (isEnabled_)
  {
    status = sourceName.CopyFrom(ENABLE_METHOD_SOURCE_NAME);
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

    status = message.Text().CopyFrom(ENABLE_METHOD_MESSAGE);
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

    methodIdentifier = OpcUaId_ConditionType_Enable;
  }
  else
  {
    status = sourceName.CopyFrom(DISABLE_METHOD_SOURCE_NAME);
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

    status = message.Text().CopyFrom(DISABLE_METHOD_MESSAGE);
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

    methodIdentifier = OpcUaId_ConditionType_Disable;
  }

  IntrusivePtr_t<NodeId_t> methodId;
  status = GetMethodNodeIdFromStandardNodeId(methodIdentifier, methodId);
  if (status.IsBad() || !methodId.is_set())
  {
    NodeIdNumeric_t methodIdTemp;
    methodIdTemp.Initialise(0, methodIdentifier);
    status = methodIdTemp.CopyToNodeId(methodId);
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
  }

  if (configuration->EventTypesActivationStatus() & ENABLE_AUDIT_CONDITION_ENABLE_EVENT_TYPE)
  {
    Status_t auditEventStatus = EventHelper_t::FireAuditConditionEvents(configuration, conditionId, OpcUaId_AuditConditionEnableEventType, sourceName, message, methodId, affectedEventId, comment);
    if (auditEventStatus.IsBad())
    {
      //Log it
    }
  }

  return status;
}

/*
 * Protected Functions
*/

Status_t BaseCondition_t::EvaluteState(uint32_t methodId)
{
  Status_t status;
  switch (methodId)
  {
  case OpcUaId_ConditionType_Enable:
    status = IsEnabled() ? OpcUa_BadConditionAlreadyEnabled : OpcUa_Good;
    break;

  case OpcUaId_ConditionType_Disable:
    status = !IsEnabled() ? OpcUa_BadConditionAlreadyDisabled : OpcUa_Good;
    break;

  default:
    return OpcUa_BadInvalidArgument;
  }
  return status;
}

Status_t BaseCondition_t::InitialiseConditionData(IntrusivePtr_t<ConditionTypeData_t> conditionData_, uint32_t conditionClassId, String_t& conditionName, bool isAllocated)
{
  UASDK_UNUSED(isAllocated);
  UASDK_RETURN_INVALID_ARGUMENT_IF_NULL(conditionData_);

  conditionData = conditionData_;

  return BaseCondition_t::InitialiseConditionDataAttributes(conditionClassId, conditionName);
}

uint32_t BaseCondition_t::GetStandardNodeId(const INode_t& node)
{
  if (addressSpaceModeler.is_set())
  {
    return addressSpaceModeler->GetStandardNodeId(node);
  }

  return 0;
}

Status_t BaseCondition_t::GetMethodNodeIdFromStandardNodeId(uint32_t standardNodeId, IntrusivePtr_t<NodeId_t>& methodId)
{
  if (addressSpaceModeler.is_set())
  {
    return addressSpaceModeler->GetMethodNodeIdFromStandardNodeId(standardNodeId, methodId);
  }
  return OpcUa_BadMethodInvalid;
}

Status_t BaseCondition_t::OnDisable(const IUserPermissions_t& userPermissions)
{
  Status_t status = Disable();
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
  if (conditionMethodListener.is_set())
  {
    conditionMethodListener->OnDisable(*this, userPermissions, status);
  }

  return status;
}

Status_t BaseCondition_t::OnEnable(const IUserPermissions_t& userPermissions)
{
  Status_t status = Enable();
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
  if (conditionMethodListener.is_set())
  {
    conditionMethodListener->OnEnable(*this, userPermissions, status);
  }

  return status;
}

Status_t BaseCondition_t::OnAddComment(const IUserPermissions_t& userPermissions, IntrusivePtr_t<const CallMethodRequest_t>& requestParameters)
{
  IntrusivePtr_t<ByteString_t> eventId;
  IntrusivePtr_t<LocalizedText_t> comment;

  Status_t status = AddressSpaceUtilities_t::CastInputArguments(requestParameters->InputArguments(), eventId, comment);
  if (!eventId.is_set() || !comment.is_set() || status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  status = AddComment(*eventId, *comment);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
  if (conditionMethodListener.is_set())
  {
    conditionMethodListener->OnAddComment(*this, userPermissions, *eventId, *comment, status);
  }

  return status;
}

void BaseCondition_t::BeginConditionStateUpdate(void)
{
  AutoLock_t lk(lock);
  conditionStateCounter++;
  if (conditionStateCounter <= 0)
  {
    conditionStateCounter = 1;
  }
}

bool BaseCondition_t::MayFireEventNotification(void)
{
  return IsEnabled();
}

Status_t BaseCondition_t::FireEventNotification(void)
{
  UASDK_RETURN_UNEXPECTED_IF_NULL(configuration);

  //If condition instance is disabled, DO NOT send event notifications.
  if (MayFireEventNotification() == false)
  {
    return OpcUa_BadNothingToDo;
  }

  Status_t status;
  IntrusivePtr_t<IAttributeAccess_t> data;
  IntrusivePtr_t<NodeId_t> sourceNodeId;
  status = GetEventData(data, sourceNodeId);
  if (status.IsBad() || !data.is_set())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  status = configuration->EventDispatcher()->FireEventObject(data, sourceNodeId);

  return status;
}

void BaseCondition_t::ConditionStateUpdated()
{
  bool fireEvent = false;
  {
    AutoLock_t lk(lock);
    if (conditionStateCounter <= 0)
    {
      fireEvent = true;
      conditionStateCounter = 0;
    }
  }

  if (fireEvent)
  {
    FireEventNotification();
  }  
}

void BaseCondition_t::EndConditionStateUpdate(void)
{
  bool fireEvent = false;
  {
    AutoLock_t lk(lock);
    conditionStateCounter--;

    if (conditionStateCounter <= 0)
    {
      conditionStateCounter = 0;
      fireEvent = true;
    }
  }

  if (fireEvent)
  {
    FireEventNotification();
  }
}

Status_t BaseCondition_t::EvaluateQualityFromEnabledState(IntrusivePtr_t<ConditionVariableType_t>& quality_)
{
  StatusCode_t statusCode_;
  Status_t status;

  quality_ = ConditionVariableType_t::CreateConditionVariableTypeWithDefaultValues(OpcUaId_StatusCode, status);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  if (!IsEnabled())
  {    
    statusCode_.Value().Value(OpcUa_BadConditionDisabled);
  }
  else
  {
    statusCode_.Value().Value(OpcUa_Good);
  }

  status = statusCode_.CopyTo(quality_->Value());
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  return status;
}

Status_t BaseCondition_t::UpdateCommentState(ByteString_t& eventId, LocalizedText_t& comment)
{
  Status_t status;

  //Comment
  IntrusivePtr_t<ConditionVariableType_t> comment_ = ConditionVariableType_t::CreateConditionVariableTypeWithDefaultValues(OpcUaId_LocalizedText, status);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
  status = comment.CopyTo(comment_->Value());
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  //EventId
  IntrusivePtr_t<ByteString_t> eventId_ = new SafeRefCount_t<ByteString_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(eventId_);
  status = eventId_->CopyFrom(eventId);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  BeginConditionStateUpdate();

  conditionData->Comment() = comment_;
  //conditionData_->EventId() = eventId_;//NOTE: This is NOT supported now, it will be applicable when Condition Branches are implemented.

  EndConditionStateUpdate();

  return status;
}

/*
* Public function
*/
BaseCondition_t::BaseCondition_t() : conditionStateCounter(0)
{}

BaseCondition_t::~BaseCondition_t()
{
	UnmountFromAddressSpace();
	conditionId.reset();
  configuration.reset();
  baseObject.reset();
  conditionMethodListener.reset();
  conditionData.reset();
 }

Status_t BaseCondition_t::Initialise(IntrusivePtr_t<IServerConfiguration_t> configuration_, NodeId_t& conditionId_, uint32_t conditionClassId, String_t& conditionName)
{
  UASDK_RETURN_INVALID_ARGUMENT_IF_NULL(configuration_);
  UASDK_RETURN_INVALID_ARGUMENT_IF_NULL(configuration_->ConditionRegistrar());

  Status_t status = configuration_->ConditionRegistrar()->CheckConditionIdIsAvaiable(conditionId_);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  status = conditionId_.CopyToNodeId(conditionId);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  configuration = configuration_;

  //The derived class InitialiseConditionData() will be called here since it is virtual.
  status = InitialiseConditionData(conditionData, conditionClassId, conditionName);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  status = lock.Initialise();
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  return OpcUa_Good;
}

Status_t BaseCondition_t::InitialiseEnabledStateLocalizationValues(IntrusivePtr_t<ILocalizableText_t> enabledStateTrueState, IntrusivePtr_t<ILocalizableText_t> enabledStateFalseState)
{
  UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData);
  UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->EnabledState());

  conditionData->EnabledState()->TrueState() = enabledStateTrueState;
  conditionData->EnabledState()->FalseState() = enabledStateFalseState;
  
  return OpcUa_Good;
}

IntrusivePtr_t<const NodeId_t> BaseCondition_t::ConditionId(void)
{
  return conditionId;
}

IntrusivePtr_t<const IObjectNode_t> BaseCondition_t::ConditionNode(Status_t& result) const
{
  IntrusivePtr_t<const IObjectNode_t> empty;
  if (!baseObject.is_set() || !baseObject->GetObjectNode().is_set())
  {
    result = OpcUa_BadNoEntryExists;
    return empty;
  }
  result = OpcUa_Good;
  return baseObject->GetObjectNode();
}

bool BaseCondition_t::IsEnabled(void)
{
  if (conditionData.is_set() && conditionData->EnabledState().is_set())
  {
	  return conditionData->EnabledState()->Id()->Value();
  }
  else
  {
    return false;
  }
}

Status_t BaseCondition_t::Disable(void)
{
  Status_t status = EvaluteState(OpcUaId_ConditionType_Disable);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  return UpdateEnabledState(false); 
}

Status_t BaseCondition_t::Enable(void)
{
  Status_t status = EvaluteState(OpcUaId_ConditionType_Enable);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  return UpdateEnabledState(true);
}

Status_t BaseCondition_t::AddComment(ByteString_t& eventId, LocalizedText_t& comment)
{
  UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData);

  Status_t status = UpdateCommentState(eventId, comment);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
  
  //FireAuditConditon Event  
  String_t sourceName;
  status = sourceName.CopyFrom(ADD_COMMENT_METHOD_SOURCE_NAME);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  LocalizedText_t message;
  status = message.Locale().CopyFrom(LOCALE_DEFAULT);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
  status = message.Text().CopyFrom(ADD_COMMENT_METHOD_MESSAGE);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  uint32_t methodIdentifier = OpcUaId_ConditionType_AddComment;
  IntrusivePtr_t<NodeId_t> methodId;
  status = GetMethodNodeIdFromStandardNodeId(methodIdentifier, methodId);
  if (status.IsBad() || !methodId.is_set())
  {
    NodeIdNumeric_t methodIdTemp;
    methodIdTemp.Initialise(0, methodIdentifier);
    status = methodIdTemp.CopyToNodeId(methodId);
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
  }

  if (configuration->EventTypesActivationStatus() & ENABLE_AUDIT_CONDITION_COMMENT_EVENT_TYPE)
  {
    Status_t auditEventStatus = EventHelper_t::FireAuditConditionEvents(configuration, conditionId, OpcUaId_AuditConditionCommentEventType, sourceName, message, methodId, eventId, comment);
    if (auditEventStatus.IsBad())
    {
      //Log it
    }
  }

  return status;
}

Status_t BaseCondition_t::MountToAddressSpace(const String_t& browseName, uint32_t hasTypeDefinitionId, NodeId_t& parentNodeId)
{
  if (!conditionId.is_set() || !configuration.is_set() || !configuration->AddressSpace().is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  if (baseObject.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadNodeIdExists);
  }

  Status_t status;

  addressSpaceModeler = new SafeRefCount_t<AddressSpaceModeler_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(addressSpaceModeler);

  IntrusivePtr_t<IAddressSpace_t> addressSpace = configuration->AddressSpace();
  UASDK_RETURN_UNEXPECTED_IF_NULL(addressSpace);

  status = addressSpaceModeler->Initialise(addressSpace, conditionId);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  IntrusivePtr_t<INode_t> parentNode = addressSpace->FindNode(parentNodeId, status);
  if (!parentNode.is_set() || status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  IntrusivePtr_t<BaseObject_t> baseObject_;
  uint16_t namespaceIndex = conditionId->NamespaceIndex().Value();
  const BaseDataType_t& identifier = conditionId->IdentiferBase();

  switch (conditionId->NodeIdIdentiferType())
  {
  case NodeId_t::NODEID_IDENTIFIER_NUMERIC:
  {
    const UInt32_t* id = RuntimeCast<const UInt32_t*>(identifier);
    if (!id)
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
    }
    baseObject_ = BaseObject_t::CreateWithNumericId(namespaceIndex, id->Value(), addressSpace, browseName, hasTypeDefinitionId, status);
  }
  break;

  case NodeId_t::NODEID_IDENTIFIER_STRING:
  {
    const String_t* id = RuntimeCast<const String_t*>(identifier);
    if (!id)
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
    }
    baseObject_ = BaseObject_t::CreateWithStringId(namespaceIndex, *id, addressSpace, browseName, hasTypeDefinitionId, status);
  }
  break;

  case NodeId_t::NODEID_IDENTIFIER_GUID:
  {
    const Guid_t* id = RuntimeCast<const Guid_t*>(identifier);
    if (!id)
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
    }
    baseObject_ = BaseObject_t::CreateWithGuidId(namespaceIndex, *id, addressSpace, browseName, hasTypeDefinitionId, status);
  }
  break;

  case NodeId_t::NODEID_IDENTIFIER_OPAQUE:
  {
    const ByteString_t* id = RuntimeCast<const ByteString_t*>(identifier);
    if (!id)
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
    }
    baseObject_ = BaseObject_t::CreateWithOpaqueId(namespaceIndex, *id, addressSpace, browseName, hasTypeDefinitionId, status);
  }
  break;

  default:
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }//switch (conditionId->NodeIdIdentiferType())

  if (!baseObject_.is_set() || !baseObject_->GetObjectNode().is_set() || status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
  baseObject_->Hide(false);
  baseObject_->RemoveNodesOnDeletion(true);  
  baseObject = baseObject_;

  status = AddressSpaceUtilities_t::CreateReference(*configuration->AddressSpace(), parentNode, baseObject_->GetObjectNode(), OpcUaId_HasComponent);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  status = AddressSpaceUtilities_t::CreateReference(*configuration->AddressSpace(), parentNode, baseObject_->GetObjectNode(), OpcUaId_HasNotifier);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  NodeIdNumeric_t typeId(0, hasTypeDefinitionId);
  NodeIdNumeric_t baseTypeId(0, OpcUaId_BaseEventType);

  IntrusivePtr_t<INodeValueAttributeReaderWriter_t> readerWriter = this;
  IntrusivePtr_t<INodeMethodHandler_t> methodHandler = this;
  return addressSpaceModeler->AddNodesUsingTypeInformation(typeId, *conditionId, true, readerWriter, methodHandler, baseTypeId);
}

Status_t BaseCondition_t::SetMethodListener(IntrusivePtr_t<IBaseConditionMethodListener_t> value)
{
  conditionMethodListener = value;
  return OpcUa_Good;
}

void BaseCondition_t::UnmountFromAddressSpace()
{
  addressSpaceModeler.reset();
  baseObject.reset();
}

Status_t BaseCondition_t::RelocateInAddressSpace(const String_t& browseName, uint32_t hasTypeDefinitionId, NodeId_t& newParentNodeId)
{
  Status_t status;

  if (!configuration.is_set() || !configuration->AddressSpace().is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  if (!baseObject.is_set() || !baseObject->GetObjectNode().is_set())
  {
    return MountToAddressSpace(browseName, hasTypeDefinitionId, newParentNodeId);
  }

  IntrusivePtr_t<INode_t> parentNode = configuration->AddressSpace()->FindNode(newParentNodeId, status);
  if (!parentNode.is_set() || status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  //Steps to relocate a condition in the addressSpace
  //1. First remove all inverse references 2. Find and remove the ComponentOf reference from the condition object 3. Create new reference with the new parent Node
  status = AddressSpaceUtilities_t::RemoveAllInverseReferences(*baseObject->GetObjectNode(), *configuration->AddressSpace());
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  IntrusivePtr_t<IReference_t> reference;
  status = AddressSpaceUtilities_t::GetReference(*baseObject->GetObjectNode(), OpcUaId_HasComponent, false, reference);
  if (!reference.is_set() || status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
  status = baseObject->GetObjectNode()->ReferencesRemoveReference(*reference);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  status = AddressSpaceUtilities_t::CreateReference(*configuration->AddressSpace(), parentNode, baseObject->GetObjectNode(), OpcUaId_HasComponent);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  return status;
}

bool BaseCondition_t::IsMountedToAddressSpace(void)
{
  if (!baseObject.is_set())
  {
    return false;
  }
  return true;
}

IntrusivePtr_t<ConditionTypeData_t>& BaseCondition_t::ConditionData(void)
{
  return conditionData;
}

Status_t BaseCondition_t::CallMethodBegin(IntrusivePtr_t<const NodeId_t> sessionId,
                                          uint32_t transactionId,
                                          const IUserPermissions_t& userPermissions,
                                          uint32_t timeoutHint,
                                          IntrusivePtr_t<INode_t>& componentOf,
                                          IntrusivePtr_t<IMethodNode_t>& method,
                                          IntrusivePtr_t<const CallMethodRequest_t>& requestParameters,
                                          IntrusivePtr_t<CallMethodResult_t>& result,
                                          IntrusivePtr_t<ICallbackCallMethodCompleted_t>& completedCallback)
{
  UASDK_UNUSED(sessionId);
  UASDK_UNUSED(transactionId);
  UASDK_UNUSED(userPermissions);
  UASDK_UNUSED(timeoutHint);
  UASDK_UNUSED(componentOf);

  if (!method.is_set() || !completedCallback.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  Status_t status;

  uint32_t standardNodeId = GetStandardNodeId(*method);
  switch (standardNodeId)
  {
    case OpcUaId_ConditionType_Disable:
      status = OnDisable(userPermissions);
      break;

    case OpcUaId_ConditionType_Enable:
      status = OnEnable(userPermissions);
      break;

    case OpcUaId_ConditionType_AddComment:
      status = OnAddComment(userPermissions, requestParameters);
      break;

    default:
      return OpcUa_BadMethodInvalid;
  }

  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  result.reset(new SafeRefCount_t<CallMethodResult_t>());
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(result);

  result->StatusCode() = OpcUa_Good;

  return completedCallback->CallMethodCompleted(result);
}

bool BaseCondition_t::CanReadValueSynchronously(const IVariableNode_t& node)
{
  UASDK_UNUSED(node);
  return true;
}

Status_t BaseCondition_t::ReadValueAttributeBegin(
  IntrusivePtr_t<const IVariableNode_t>& node,
  uint32_t maxAge,
  bool setSourceTimestamp,
  IntrusivePtr_t<const ArrayUA_t<String_t> >& locales,
  IntrusivePtr_t<const ArrayRef_t<IndexRange_t> >& indexRange,
  uint32_t transactionId,
  uint32_t timeoutHint,
  IntrusivePtr_t<ICallbackNodeValueAttributeAccessCompleted_t>& completedCallback)
{
  UASDK_UNUSED(node);
  UASDK_UNUSED(maxAge);
  UASDK_UNUSED(setSourceTimestamp);
  UASDK_UNUSED(locales);
  UASDK_UNUSED(indexRange);
  UASDK_UNUSED(transactionId);
  UASDK_UNUSED(timeoutHint);
  UASDK_UNUSED(completedCallback);

  UASDK_RETURN_BAD_STATUS(OpcUa_BadNotReadable);
}

Status_t BaseCondition_t::ReadValueAttribute(
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
  UASDK_UNUSED(maxAge);
  UASDK_UNUSED(indexRange);
  UASDK_UNUSED(transactionId);
  UASDK_UNUSED(timeoutHint);
  UASDK_UNUSED(diagnosticInfo);

  if (!configuration.is_set() || !configuration->AddressSpace().is_set() || !conditionData.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  Status_t status;
  IntrusivePtr_t<BaseDataType_t> value;

  uint32_t standardNodeId = GetStandardNodeId(node);
  switch (standardNodeId)
  {
  case OpcUaId_ConditionType_ConditionClassId:
  {
    UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->ConditionClassId());
    status = conditionData->ConditionClassId()->CopyTo(value);
  }
  break;

  case OpcUaId_ConditionType_ConditionClassName:
  {
    UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->ConditionClassId());
    UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->ConditionClassName());

    status = conditionData->ConditionClassName()->CopyTo(value);
  }
  break;

  case OpcUaId_ConditionType_ConditionName:
  {
    UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->ConditionName());
    status = conditionData->ConditionName()->CopyTo(value);
  }
  break;

  case OpcUaId_ConditionType_BranchId:
  {
    UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->BranchId());
    status = conditionData->BranchId()->CopyTo(value);
  }
  break;

  case OpcUaId_ConditionType_Retain:
  {
    UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->Retain());
    status = conditionData->Retain()->CopyTo(value);
  }
  break;

  case OpcUaId_ConditionType_EnabledState:
  case OpcUaId_AcknowledgeableConditionType_EnabledState:
  case OpcUaId_AlarmConditionType_EnabledState:
  {
    IntrusivePtr_t<const ILocalizableText_t> enabledStateValue = conditionData->EnabledState()->Value();
    UASDK_RETURN_UNEXPECTED_IF_NULL(enabledStateValue);

    IntrusivePtr_t<const LocalizedText_t> enabledStateResolvedValue = enabledStateValue->GetLocalizedText(locales, status);
    if (enabledStateResolvedValue.is_set() && status.IsGood())
    {
      status = enabledStateResolvedValue->CopyTo(value);
    }
  }
  break;

  case OpcUaId_ConditionType_EnabledState_EffectiveTransitionTime:
  {
    UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->EnabledState());
    status = conditionData->EnabledState()->EffectiveTransitionTime()->CopyTo(value);
  }
  break;

  case OpcUaId_ConditionType_EnabledState_FalseState:
  {
    IntrusivePtr_t<const ILocalizableText_t> state_ = conditionData->EnabledState()->FalseState();
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

  case OpcUaId_ConditionType_EnabledState_Id:
  case OpcUaId_AlarmConditionType_EnabledState_Id:
  {
    UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->EnabledState());
    status = conditionData->EnabledState()->Id()->CopyTo(value);
  }
  break;

  case OpcUaId_ConditionType_EnabledState_EffectiveDisplayName:
  {
    UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->EnabledState());
    UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->EnabledState()->EffectiveDisplayName());
    status = conditionData->EnabledState()->EffectiveDisplayName()->CopyTo(value);
  }
  break;

  case OpcUaId_ConditionType_EnabledState_TransitionTime:
  {
    UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->EnabledState());
    status = conditionData->EnabledState()->TransitionTime()->CopyTo(value);
  }
  break;

  case OpcUaId_ConditionType_EnabledState_TrueState:
  {
    IntrusivePtr_t<const ILocalizableText_t> state_ = conditionData->EnabledState()->TrueState();
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

  case OpcUaId_ConditionType_Quality:
  {
    UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->Quality());
    UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->Quality()->Value());
    status = conditionData->Quality()->Value()->CopyTo(value);
  }
  break;

  case OpcUaId_ConditionType_Quality_SourceTimestamp:
  {
    UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->Quality());
    UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->Quality()->SourceTimestamp());
    status = conditionData->Quality()->SourceTimestamp()->CopyTo(value);
  }
  break;

  case OpcUaId_ConditionType_LastSeverity:
  {
    UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->LastSeverity());
    UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->LastSeverity()->Value());
    status = conditionData->LastSeverity()->Value()->CopyTo(value);
  }
  break;

  case OpcUaId_ConditionType_LastSeverity_SourceTimestamp:
  {
    UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->LastSeverity());
    UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->LastSeverity()->SourceTimestamp());
    status = conditionData->LastSeverity()->SourceTimestamp()->CopyTo(value);
  }
  break;

  case OpcUaId_ConditionType_Comment:
  {
    UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->Comment());
    UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->Comment()->Value());
    status = conditionData->Comment()->Value()->CopyTo(value);
  }
  break;

  case OpcUaId_ConditionType_Comment_SourceTimestamp:
  {
    UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->Comment());
    UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->Comment()->SourceTimestamp());
    status = conditionData->Comment()->SourceTimestamp()->CopyTo(value);
  }
  break;

  case OpcUaId_ConditionType_ClientUserId:
  {
    UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->ClientUserId());
    status = conditionData->ClientUserId()->CopyTo(value);
  }
  break;

  default:
  {
    if (!node.Value().is_set() && node.DataType().is_set())
    {
      const UInt32_t* dataType = RuntimeCast<const UInt32_t* >(node.DataType()->IdentiferBase());
      if (dataType)
      {
        status = AddressSpaceModeler_t::InitialiseValue(dataType->Value(), value);
      }
    }
  }
  break;
  }
  if (!value.is_set() || status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  uint32_t statusCode = IsEnabled() ? OpcUa_Good : OpcUa_BadConditionDisabled;

  return AddressSpaceModeler_t::ReadValue(*value, setSourceTimestamp, statusCode, dataValue);
}

bool BaseCondition_t::CanWriteValueSynchronously(const IVariableNode_t& node)
{
  UASDK_UNUSED(node);
  return true;
}

Status_t BaseCondition_t::WriteValueAttributeBegin(
  IntrusivePtr_t<IVariableNode_t>& node,
  IntrusivePtr_t<const ArrayRef_t<IndexRange_t> > indexRange,
  IntrusivePtr_t<const DataValue_t> dataValue,
  uint32_t transactionId,
  uint32_t timeoutHint,
  IntrusivePtr_t<ICallbackNodeValueAttributeAccessCompleted_t>& completedCallback)
{
  UASDK_UNUSED(node);
  UASDK_UNUSED(indexRange);
  UASDK_UNUSED(dataValue);
  UASDK_UNUSED(transactionId);
  UASDK_UNUSED(timeoutHint);
  UASDK_UNUSED(completedCallback);

  UASDK_RETURN_BAD_STATUS(OpcUa_BadNotWritable);
}

Status_t BaseCondition_t::WriteValueAttribute(
  IVariableNode_t& node,
  const Array_t<IndexRange_t>& indexRange,
  IntrusivePtr_t<const DataValue_t> dataValue,
  uint32_t transactionId,
  uint32_t timeoutHint,
  IntrusivePtr_t<DiagnosticInfo_t>& diagnosticInfo)
{
  UASDK_UNUSED(node);
  UASDK_UNUSED(indexRange);
  UASDK_UNUSED(dataValue);
  UASDK_UNUSED(transactionId);
  UASDK_UNUSED(timeoutHint);
  UASDK_UNUSED(diagnosticInfo);

  UASDK_RETURN_BAD_STATUS(OpcUa_BadNotWritable);
}

} // namespace uasdk

#endif //((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))
