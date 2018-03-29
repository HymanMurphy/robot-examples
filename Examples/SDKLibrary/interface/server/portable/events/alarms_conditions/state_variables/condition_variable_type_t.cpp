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

#include "condition_variable_type_t.h"

#if ((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

#include "opcua_status_code_t.h"
#include "opcua_uint16_t.h"

namespace uasdk
{

ConditionVariableType_t::ConditionVariableType_t()
{
}

ConditionVariableType_t::~ConditionVariableType_t()
{
}

Status_t ConditionVariableType_t::Initialise()
{
  return OpcUa_Good;
}

IntrusivePtr_t<const BaseDataType_t> ConditionVariableType_t::Value(void) const
{ 
  return value; 
}

IntrusivePtr_t<BaseDataType_t>& ConditionVariableType_t::Value(void)
{ 
  return value; 
}

IntrusivePtr_t<const UtcTime_t> ConditionVariableType_t::SourceTimestamp(void) const
{
  return sourceTimeStamp;
}

IntrusivePtr_t<UtcTime_t>& ConditionVariableType_t::SourceTimestamp(void)
{ 
  return sourceTimeStamp; 
}

Status_t ConditionVariableType_t::CopyFrom(const ConditionVariableType_t& source)
{
  Status_t status;

  if (source.Value().is_set())
  {
    status = source.Value()->CopyTo(value);
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
  }

  if (source.SourceTimestamp().is_set())
  {
    if (!sourceTimeStamp.is_set())
    {
      sourceTimeStamp = new SafeRefCount_t<UtcTime_t>();
      UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(sourceTimeStamp);
    }
    status = sourceTimeStamp->CopyFrom(*source.SourceTimestamp());
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
  }

  return OpcUa_Good;
}

Status_t ConditionVariableType_t::CopyTo(IntrusivePtr_t<ConditionVariableType_t>& destination)
{
  IntrusivePtr_t<ConditionVariableType_t> destination_ = new SafeRefCount_t<ConditionVariableType_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(destination_);

  Status_t status = destination_->CopyFrom(*this);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  destination = destination_;

  return OpcUa_Good;
}

IntrusivePtr_t<ConditionVariableType_t> ConditionVariableType_t::CreateConditionVariableTypeWithDefaultValues(uint32_t valueType, Status_t& result)
{
  IntrusivePtr_t<ConditionVariableType_t> empty;
  IntrusivePtr_t<ConditionVariableType_t> conditionVariableType_ = new SafeRefCount_t<ConditionVariableType_t>();
  if (!conditionVariableType_.is_set())
  {
    result = OpcUa_BadOutOfMemory;
    return empty;
  }

  IntrusivePtr_t<UtcTime_t> sourceTimestamp_ = new SafeRefCount_t<UtcTime_t>();
  if (!sourceTimestamp_.is_set())
  {
    result = OpcUa_BadOutOfMemory;
    return empty;
  }

  IntrusivePtr_t<BaseDataType_t> value_;

  switch (valueType)
  {
  case OpcUaId_UInt16:
    value_ = new SafeRefCount_t<UInt16_t>();    
    break;
  case OpcUaId_StatusCode:
    value_ = new SafeRefCount_t<StatusCode_t>();
    break;
  case OpcUaId_LocalizedText:
    value_ = new SafeRefCount_t<LocalizedText_t>();
    break;
  default:
    break;
  }

  if (!value_.is_set())
  {
    result = OpcUa_BadOutOfMemory;
    return empty;
  }

  conditionVariableType_->Value() = value_;
  conditionVariableType_->SourceTimestamp() = sourceTimestamp_;

  return conditionVariableType_;
}

} //namespace uasdk

#endif //((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))
