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

#include "certificate_expiration_alarm_t.h"

#if ((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

namespace uasdk
{
UA_DEFINE_RUNTIME_TYPE(CertificateExpirationAlarm_t, SystemOffNormalAlarm_t);

/*
 * Private Function
 */
Status_t CertificateExpirationAlarm_t::InitialiseConditionDataAttributes(void)
{
  UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData);
  
  //SourceNodeId - This Alarm is NOT mounted to the address space.
  //Hence setting the sourceNodeId to Server Node as this is an alarm at server level.
  conditionData->SourceNode() = EventHelper_t::GetServerNodeId();

  //Severity - This is an high alarm
  IntrusivePtr_t<UInt16_t> severity_ = new SafeRefCount_t<UInt16_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(severity_);
  severity_->Value(EventSeverity_t::OPCUA_EVENT_SEVERITY_HIGH);
  conditionData->Severity() = severity_;

  //ExpirationDate
  IntrusivePtr_t<DateTime_t> expirationDate_ = new SafeRefCount_t<DateTime_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(expirationDate_);

  conditionData->ExpirationDate() = expirationDate_;

  //CertificateType
  IntrusivePtr_t<NodeId_t> certificateType_ = new SafeRefCount_t<NodeIdNumeric_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(certificateType_);

  conditionData->CertificateType() = certificateType_;

  //Certificate
  IntrusivePtr_t<ByteString_t> certificate_ = new SafeRefCount_t<ByteString_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(certificate_);

  conditionData->Certificate() = certificate_;

  if (conditionData->Retain().is_set())
  {
    conditionData->Retain()->Value(false);
  }

  if (conditionData->Severity().is_set())
  {
    conditionData->Severity()->Value(CERTIFICATE_EXPIRATION_ALARM_INACTIVE_SEVERITY);
  }

  return OpcUa_Good;
}

/*
* Protected Functions
*/

Status_t CertificateExpirationAlarm_t::EvaluteState(uint32_t methodId)
{
  //This condition do not have any variables/States/Methods. Hence Nothing To Do here.
  UASDK_UNUSED(methodId);
  return OpcUa_BadNothingToDo;
}

Status_t CertificateExpirationAlarm_t::InitialiseConditionData(IntrusivePtr_t<ConditionTypeData_t> conditionData_, uint32_t conditionClassId, String_t& conditionName, bool isAllocated)
{
  if (conditionData_.is_set())
  {
    conditionData = RuntimeCast<CertificateExpirationAlarmTypeData_t*>(*conditionData_);
    UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData);
  }
  else if (isAllocated)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }
  else
  {
    conditionData = new SafeRefCount_t<CertificateExpirationAlarmTypeData_t>();
    UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(conditionData);
  }

  Status_t status = SystemOffNormalAlarm_t::InitialiseConditionData(conditionData, conditionClassId, conditionName, true);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  return CertificateExpirationAlarm_t::InitialiseConditionDataAttributes();
}

Status_t CertificateExpirationAlarm_t::GetEventData(IntrusivePtr_t<IAttributeAccess_t>& data, IntrusivePtr_t<NodeId_t>& sourceNodeId)
{
  Status_t status;

  IntrusivePtr_t<CertificateExpirationAlarmTypeData_t> data_ = new SafeRefCount_t<CertificateExpirationAlarmTypeData_t>();
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
CertificateExpirationAlarm_t::CertificateExpirationAlarm_t()
{}

CertificateExpirationAlarm_t::~CertificateExpirationAlarm_t()
{}

Status_t CertificateExpirationAlarm_t::Initialise(IntrusivePtr_t<IServerConfiguration_t> configuration_, NodeId_t& conditionId_, uint32_t conditionClassId, String_t& conditionName)
{
  return SystemOffNormalAlarm_t::Initialise(configuration_, conditionId_, conditionClassId, conditionName);
}

Status_t CertificateExpirationAlarm_t::SetMethodListener(IntrusivePtr_t<ICertificateExpirationAlarmMethodListener_t> value)
{
  conditionMethodListener = value;
  return SystemOffNormalAlarm_t::SetMethodListener(value);
}

Status_t CertificateExpirationAlarm_t::UpdateCertificateExpirationState(IntrusivePtr_t<DateTime_t> expirationDate, IntrusivePtr_t<NodeId_t> certificateType, IntrusivePtr_t<ByteString_t> certificate, IntrusivePtr_t<Duration_t> expirationLimit)
{
  UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData);

  Status_t status;

  BeginConditionStateUpdate();

  status = TransitionToActiveState(OpcUa_Good, CERTIFICATE_EXPIRATION_ALARM_SEVERITY);

  if (status.IsGood())
  {
    conditionData->ExpirationDate() = expirationDate;
    conditionData->CertificateType() = certificateType;
    conditionData->Certificate() = certificate;
    conditionData->ExpirationLimit() = expirationLimit;

    if (conditionData->Retain().is_set())
    {
      conditionData->Retain()->Value(true);
    }

    //SourceNodeId - This Alarm is NOT mounted to the address space.
    //Hence setting the sourceNodeId to Server Node as this is an alarm at server level.
    conditionData->SourceNode() = EventHelper_t::GetServerNodeId();
  }

  EndConditionStateUpdate();

  return status;
}

Status_t CertificateExpirationAlarm_t::CallMethodBegin(IntrusivePtr_t<const NodeId_t> sessionId,
  uint32_t transactionId,
  const IUserPermissions_t& userPermissions,
  uint32_t timeoutHint,
  IntrusivePtr_t<INode_t>& componentOf,
  IntrusivePtr_t<IMethodNode_t>& method,
  IntrusivePtr_t<const CallMethodRequest_t>& requestParameters,
  IntrusivePtr_t<CallMethodResult_t>& result,
  IntrusivePtr_t<ICallbackCallMethodCompleted_t>& completedCallback)
{
  //No method is available for CertificateExpirationAlarm, then call the parent class CallMethodBegin
  return SystemOffNormalAlarm_t::CallMethodBegin(sessionId, transactionId, userPermissions, timeoutHint, componentOf, method, requestParameters, result, completedCallback);
}

Status_t CertificateExpirationAlarm_t::ReadValueAttribute(
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

  Status_t status;
  IntrusivePtr_t<BaseDataType_t> value;

  uint32_t standardNodeId = GetStandardNodeId(node);
  switch (standardNodeId)
  {
  case OpcUaId_CertificateExpirationAlarmType_ExpirationDate:
  {
    UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->ExpirationDate());
    status = conditionData->ExpirationDate()->CopyTo(value);
  }
  break;

  case OpcUaId_CertificateExpirationAlarmType_ExpirationLimit:
  {
    UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->ExpirationLimit());
    status = conditionData->ExpirationLimit()->CopyTo(value);
  }
  break;

  case OpcUaId_CertificateExpirationAlarmType_CertificateType:
  {
    UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->CertificateType());
    status = conditionData->CertificateType()->CopyTo(value);
  }
  break;

  case OpcUaId_CertificateExpirationAlarmType_Certificate:
  {
    UASDK_RETURN_UNEXPECTED_IF_NULL(conditionData->Certificate());
    status = conditionData->Certificate()->CopyTo(value);
  }
  break;

    default:
      return SystemOffNormalAlarm_t::ReadValueAttribute(node, maxAge, setSourceTimestamp, locales, indexRange, transactionId, timeoutHint, dataValue, diagnosticInfo);
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


