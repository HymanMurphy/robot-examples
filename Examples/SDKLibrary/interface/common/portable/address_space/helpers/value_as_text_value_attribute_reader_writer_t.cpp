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

#include "value_as_text_value_attribute_reader_writer_t.h"

#if ((UASDK_USE_HELPERS > 0) && (UASDK_USE_DATA_ACCESS_HELPERS > 0))

#include "auto_lock_t.h"

#include "opcua_data_value_t.h"
#include "opcua_diagnostic_info_t.h"
#include "opcua_duration_t.h"
#include "opcua_array_ua_t.h"
#include "opcua_enum_value_type_t.h"

#include "opcua_byte_t.h"
#include "opcua_sbyte_t.h"
#include "opcua_int16_t.h"
#include "opcua_uint64_t.h"

namespace uasdk
{
/*
 * private functions
 */
IntrusivePtr_t<const BaseDataType_t> ValueAsTextValueAttributeReaderWriter_t::GetValue(Status_t& result) const
{
  IntrusivePtr_t<const BaseDataType_t> retVal;

  IntrusivePtr_t<IVariableNode_t> node_ = multiStateValueDiscrete->GetVariableNode();
  if(!node_.is_set() || !node_->Value().is_set() || !node_->Value()->Value().is_set())
  {
    result = OpcUa_BadUnexpectedError;
    return retVal;
  }

  IntrusivePtr_t<const BaseDataType_t> value_ = node_->Value()->Value();
  if(!value_.is_set())
  {
    result = OpcUa_BadNoData;
    return retVal;
  }

  int64_t value;

  uint16_t namespaceIndex = 0;
  uint32_t type = value_->TypeId(namespaceIndex);
  switch(type)
  {
    case OpcUaId_Byte:
      {
        IntrusivePtr_t<const Byte_t> temp = RuntimeCast<const Byte_t *>(*value_);
        if(!temp.is_set())
        {
          result = OpcUa_BadTypeMismatch;
          return retVal;
        }

        value = (int64_t)(temp->Value());
      }
      break;

    case OpcUaId_SByte:
      {
        IntrusivePtr_t<const SByte_t> temp = RuntimeCast<const SByte_t *>(*value_);
        if(!temp.is_set())
        {
          result = OpcUa_BadTypeMismatch;
          return retVal;
        }

        value = (int64_t)(temp->Value());
      }
      break;

    case OpcUaId_Int16:
      {
        IntrusivePtr_t<const Int16_t> temp = RuntimeCast<const Int16_t *>(*value_);
        if(!temp.is_set())
        {
          result = OpcUa_BadTypeMismatch;
          return retVal;
        }

        value = (int64_t)(temp->Value());
      }
      break;

    case OpcUaId_UInt16:
      {
        IntrusivePtr_t<const UInt16_t> temp = RuntimeCast<const UInt16_t *>(*value_);
        if(!temp.is_set())
        {
          result = OpcUa_BadTypeMismatch;
          return retVal;
        }

        value = (int64_t)(temp->Value());
      }
      break;

    case OpcUaId_Int32:
      {
        IntrusivePtr_t<const Int32_t> temp = RuntimeCast<const Int32_t *>(*value_);
        if(!temp.is_set())
        {
          result = OpcUa_BadTypeMismatch;
          return retVal;
        }

        value = (int64_t)(temp->Value());
      }
      break;

    case OpcUaId_UInt32:
      {
        IntrusivePtr_t<const UInt32_t> temp = RuntimeCast<const UInt32_t *>(*value_);
        if(!temp.is_set())
        {
          result = OpcUa_BadTypeMismatch;
          return retVal;
        }

        value = (int64_t)(temp->Value());
      }
      break;

    case OpcUaId_Int64:
      {
        IntrusivePtr_t<const Int64_t> temp = RuntimeCast<const Int64_t *>(*value_);
        if(!temp.is_set())
        {
          result = OpcUa_BadTypeMismatch;
          return retVal;
        }

        value = (int64_t)(temp->Value());
      }
      break;

    case OpcUaId_UInt64:
      {
        IntrusivePtr_t<const UInt64_t> temp = RuntimeCast<const UInt64_t *>(*value_);
        if(!temp.is_set())
        {
          result = OpcUa_BadTypeMismatch;
          return retVal;
        }

        value = (int64_t)(temp->Value());
      }
      break;

    default:
      result = OpcUa_BadTypeMismatch;
      return retVal;
  }

  //Check in the Enum values
  IntrusivePtr_t<const ArrayUA_t<EnumValueType_t> > enumValues = multiStateValueDiscrete->GetEnumValuesValue(result);
  if(result.IsBad() || !enumValues.is_set() || (enumValues->Count() <= 0) )
  {
    result = OpcUa_BadNoData;
    return retVal;
  }

  uint32_t count = enumValues->Count();
  for(uint32_t i = 0; i < count; i++)
  {
    IntrusivePtr_t<EnumValueType_t> temp = (*enumValues)[i];
    if(!temp.is_set())
    {
      result = OpcUa_BadUnexpectedError;
      return retVal;
    }

    if(value == temp->Value().Value())
    {
      IntrusivePtr_t<BaseDataType_t> val;
      result = temp->DisplayName().CopyTo(val);
      if(result.IsBad())
      {
        return retVal;
      }

      retVal = val;
      break;
    }
  }

  if(!retVal.is_set())
  {
    result = OpcUa_BadNoData;
    return retVal;
  }

  result = OpcUa_Good;
  return retVal;
}

Status_t ValueAsTextValueAttributeReaderWriter_t::ReadDataValue(const IVariableNode_t& node, bool setSourceTimestamp, IntrusivePtr_t<DataValue_t>& dataValue)
{
  UASDK_UNUSED(node);

  AutoLock_t lk(lock);
  Status_t status;
  IntrusivePtr_t<const BaseDataType_t> temp = GetValue(status);
  if(status.IsBad() || !temp.is_set())
  {
    return status;
  }

  dataValue.reset(new SafeRefCount_t<DataValue_t>());
  if(!dataValue.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  if(setSourceTimestamp)
  {
    IntrusivePtr_t<DateTime_t> dateTime(new SafeRefCount_t<DateTime_t>());
    if(!dateTime.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }
    dateTime->Value(UASDK_datetime());
    dataValue->SourceTimestamp() = dateTime;
  }

  IntrusivePtr_t<StatusCode_t> statusCode_ = new SafeRefCount_t<StatusCode_t>();
  if (!statusCode_.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  statusCode_->Value().Value(OpcUa_Good);
  dataValue->StatusCode() = statusCode_;

  return temp->CopyTo(dataValue->Value());
}

Status_t ValueAsTextValueAttributeReaderWriter_t::ReadDataValueBegin(IntrusivePtr_t<const IVariableNode_t>& node,
                                                              bool setSourceTimestamp,
                                                              IntrusivePtr_t<ICallbackNodeValueAttributeAccessCompleted_t>& completedCallback)
{
  if(!completedCallback.is_set() || !node.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  IntrusivePtr_t<DataValue_t> dataValue;

  Status_t status = ReadDataValue(*node, setSourceTimestamp, dataValue);
  if(status.IsBad() || !dataValue.is_set())
  {
    return status;
  }

  return completedCallback->ReadValueAttributeCompleted(dataValue);
}

/*
 * public functions
 */
ValueAsTextValueAttributeReaderWriter_t::~ValueAsTextValueAttributeReaderWriter_t()
{}

Status_t ValueAsTextValueAttributeReaderWriter_t::Initialize(IntrusivePtr_t<MultiStateValueDiscrete_t>& multiStateValueDiscrete_)
{
  multiStateValueDiscrete = multiStateValueDiscrete_;
  return lock.Initialise();

}

bool ValueAsTextValueAttributeReaderWriter_t::CanReadValueSynchronously(const IVariableNode_t& node)
{
  UASDK_UNUSED(node);
  return true;
}

Status_t ValueAsTextValueAttributeReaderWriter_t::ReadValueAttributeBegin(
  IntrusivePtr_t<const IVariableNode_t>& node,
  uint32_t maxAge,
  bool setSourceTimestamp,
  IntrusivePtr_t<const ArrayUA_t<String_t> >& locales,
  IntrusivePtr_t<const ArrayRef_t<IndexRange_t> >& indexRange,
  uint32_t transactionId,
  uint32_t timeoutHint,
  IntrusivePtr_t<ICallbackNodeValueAttributeAccessCompleted_t>& completedCallback)
{
  UASDK_UNUSED(maxAge);
  UASDK_UNUSED(locales);
  UASDK_UNUSED(indexRange);
  UASDK_UNUSED(transactionId);
  UASDK_UNUSED(timeoutHint);
  return ReadDataValueBegin(node, setSourceTimestamp, completedCallback);
}

Status_t ValueAsTextValueAttributeReaderWriter_t::ReadValueAttribute(
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
  UASDK_UNUSED(locales);
  UASDK_UNUSED(indexRange);
  UASDK_UNUSED(transactionId);
  UASDK_UNUSED(timeoutHint);
  UASDK_UNUSED(diagnosticInfo);
  return ReadDataValue(node, setSourceTimestamp, dataValue);
}

bool ValueAsTextValueAttributeReaderWriter_t::CanWriteValueSynchronously(const IVariableNode_t& node)
{
  UASDK_UNUSED(node);
  return true;
}

Status_t ValueAsTextValueAttributeReaderWriter_t::WriteValueAttributeBegin(IntrusivePtr_t<IVariableNode_t>& node,
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

Status_t ValueAsTextValueAttributeReaderWriter_t::WriteValueAttribute(IVariableNode_t& node,
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

} //namespace uasdk

#endif //UASDK_USE_DATA_ACCESS_HELPERS
