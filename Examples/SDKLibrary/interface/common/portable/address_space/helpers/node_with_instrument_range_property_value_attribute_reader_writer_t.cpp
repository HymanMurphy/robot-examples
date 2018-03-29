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

#include "node_with_instrument_range_property_value_attribute_reader_writer_t.h"

#if ((UASDK_USE_HELPERS > 0) && (UASDK_USE_DATA_ACCESS_HELPERS > 0))

#include "opcua_datatype_utilities_t.h"
#include "auto_lock_t.h"

#include "opcua_array_ua_t.h"
#include "opcua_byte_t.h"
#include "opcua_sbyte_t.h"
#include "opcua_int16_t.h"
#include "opcua_uint16_t.h"
#include "opcua_int32_t.h"
#include "opcua_uint32_t.h"
#include "opcua_int64_t.h"
#include "opcua_uint64_t.h"
#include "opcua_double_t.h"
#include "opcua_float_t.h"
#include "opcua_complex_number_type_t.h"
#include "opcua_double_complex_number_type_t.h"

#include "address_space_utilities_t.h"

namespace uasdk
{

/*
 * private functions
 */
Status_t NodeWithInstrumentRangePropertyValueAttributeReaderWriter_t::ReadValue(const Array_t<IndexRange_t>& indexRange, bool setSourceTimestamp, IntrusivePtr_t<DataValue_t>& dataValue)
{
  AutoLock_t lk(lock);
  if(!valueOfNodeWithInstrumentRangeProperty.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadNoData);
  }

  dataValue.reset(new SafeRefCount_t<DataValue_t>());
  if (!dataValue.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  //Status_t status = dataValue->WriteSubsetFrom(indexRange, *valueOfNodeWithInstrumentRangeProperty );
  IntrusivePtr_t<BaseDataType_t> temp;
  Status_t status = valueOfNodeWithInstrumentRangeProperty->WriteSubsetTo(indexRange, temp);
  if (status.IsBad() || !temp.is_set())
  {
    return status;
  }
  status = dataValue->CopyFrom(*temp);
  if (status.IsBad())
  {
    return status;
  }
  
  if (!setSourceTimestamp)
  {
    IntrusivePtr_t<DateTime_t> dateTime;
    dataValue->SourceTimestamp() = dateTime;
  }

  IntrusivePtr_t<StatusCode_t> statusCode_ = new SafeRefCount_t<StatusCode_t>();
  if (!statusCode_.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  statusCode_->Value().Value(OpcUa_Good);
  dataValue->StatusCode() = statusCode_;

  return OpcUa_Good;
}

Status_t NodeWithInstrumentRangePropertyValueAttributeReaderWriter_t::WriteValue(const Array_t<IndexRange_t>& indexRange, const DataValue_t& dataValue)
{
  if(!dataValue.Value().is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }
  IntrusivePtr_t<const BaseDataType_t> value_ = dataValue.Value();

  UASDK_RETURN_UNEXPECTED_IF_NULL(instrumentRangeNode);
  UASDK_RETURN_UNEXPECTED_IF_NULL(instrumentRangeNode->Value());
  UASDK_RETURN_UNEXPECTED_IF_NULL(instrumentRangeNode->Value()->Value());

  IntrusivePtr_t<const Range_t> instrumentRange_ = RuntimeCast<const Range_t*>(*(instrumentRangeNode->Value()->Value()));
  if(!instrumentRange_.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  Status_t status = AddressSpaceUtilities_t::RangeCheck(*instrumentRange_, *value_);
  if(status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  AutoLock_t lk(lock);
  //Write the DataValue
  IntrusivePtr_t<DataValue_t> value = valueOfNodeWithInstrumentRangeProperty;
  if(!value.is_set())
  {
    value.reset(new SafeRefCount_t<DataValue_t>());
    if(!value.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }
  }

  //status = value_->WriteSubsetTo(indexRange, value->Value());
  if(value->Value().is_set())
  {
    status = value->Value()->WriteSubsetFrom(indexRange, *value_);
  }
  else
  {
    status = value->WriteSubsetFrom(indexRange, dataValue);
  }
  if (status.IsBad())
  {
    return status;
  }

  if (dataValue.SourceTimestamp().is_set())
  {
    IntrusivePtr_t<DateTime_t> sourceTimestamp = new SafeRefCount_t<DateTime_t>();
    if (!sourceTimestamp.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }
    sourceTimestamp->Value(dataValue.SourceTimestamp()->Value());
    value->SourceTimestamp() = sourceTimestamp;
  }

  if (dataValue.SourcePicoseconds().is_set())
  {
    IntrusivePtr_t<UInt16_t> sourcePicoseconds = new SafeRefCount_t<UInt16_t>();
    if (!sourcePicoseconds.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }
    sourcePicoseconds->Value(dataValue.SourcePicoseconds()->Value());
    value->SourcePicoseconds() = sourcePicoseconds;
  }

  if (dataValue.StatusCode().is_set())
  {
    IntrusivePtr_t<StatusCode_t> statusCode_ = new SafeRefCount_t<StatusCode_t>();
    if (!statusCode_.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }
    statusCode_->Value().Value(dataValue.StatusCode()->Value().Value());
    value->StatusCode() = statusCode_;
  }

  valueOfNodeWithInstrumentRangeProperty = value;
  return OpcUa_Good;
}

/*
 * public functions implementation
 */

NodeWithInstrumentRangePropertyValueAttributeReaderWriter_t::~NodeWithInstrumentRangePropertyValueAttributeReaderWriter_t()
{}

Status_t NodeWithInstrumentRangePropertyValueAttributeReaderWriter_t::Initialize(
          IntrusivePtr_t<const DataValue_t> valueOfNodeWithInstrumentRangeProperty_, IntrusivePtr_t<IVariableNode_t>& instrumentRangeNode_)
{
  Status_t status;

  if(valueOfNodeWithInstrumentRangeProperty_.is_set())
  {
    valueOfNodeWithInstrumentRangeProperty.reset(new SafeRefCount_t<DataValue_t>());
    if(!valueOfNodeWithInstrumentRangeProperty.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }

    status = valueOfNodeWithInstrumentRangeProperty->CopyFrom(*valueOfNodeWithInstrumentRangeProperty_);
  }

  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  instrumentRangeNode = instrumentRangeNode_;
  return lock.Initialise();
}

bool NodeWithInstrumentRangePropertyValueAttributeReaderWriter_t::CanReadValueSynchronously(const IVariableNode_t& node)
{
  UASDK_UNUSED(node);
  return true;
}

Status_t NodeWithInstrumentRangePropertyValueAttributeReaderWriter_t::ReadValueAttributeBegin(
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
  UASDK_UNUSED(locales);
  UASDK_UNUSED(transactionId);
  UASDK_UNUSED(timeoutHint);

  if (!indexRange.is_set() || !completedCallback.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  IntrusivePtr_t<DataValue_t> dataValue;

  Status_t status = ReadValue(*indexRange, setSourceTimestamp, dataValue);
  if (status.IsBad() || !dataValue.is_set())
  {
    return status;
  }

  return completedCallback->ReadValueAttributeCompleted(dataValue);
}

Status_t NodeWithInstrumentRangePropertyValueAttributeReaderWriter_t::ReadValueAttribute(
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
  UASDK_UNUSED(node);
  UASDK_UNUSED(maxAge);
  UASDK_UNUSED(locales);
  UASDK_UNUSED(transactionId);
  UASDK_UNUSED(timeoutHint);
  UASDK_UNUSED(diagnosticInfo);
  return ReadValue(indexRange, setSourceTimestamp, dataValue);
}

/*
 * writer implementation
 */

bool NodeWithInstrumentRangePropertyValueAttributeReaderWriter_t::CanWriteValueSynchronously(const IVariableNode_t& node)
{
  UASDK_UNUSED(node);
  return true;
}

Status_t NodeWithInstrumentRangePropertyValueAttributeReaderWriter_t::WriteValueAttributeBegin(IntrusivePtr_t<IVariableNode_t>& node,
                                                                                               IntrusivePtr_t<const ArrayRef_t<IndexRange_t> > indexRange,
                                                                                               IntrusivePtr_t<const DataValue_t> dataValue,
                                                                                               uint32_t transactionId,
                                                                                               uint32_t timeoutHint,
                                                                                               IntrusivePtr_t<ICallbackNodeValueAttributeAccessCompleted_t>& completedCallback)
{
  UASDK_UNUSED(node);
  UASDK_UNUSED(transactionId);
  UASDK_UNUSED(timeoutHint);

  if(!indexRange.is_set() || !dataValue.is_set() || !completedCallback.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  Status_t status = WriteValue(*indexRange, *dataValue);
  if(status.IsBad())
  {
    return status;
  }

  return completedCallback->WriteValueAttributeCompleted(status);
}

Status_t NodeWithInstrumentRangePropertyValueAttributeReaderWriter_t::WriteValueAttribute(IVariableNode_t& node,
                                                                                const Array_t<IndexRange_t>& indexRange,
                                                                                IntrusivePtr_t<const DataValue_t> dataValue,
                                                                                uint32_t transactionId,
                                                                                uint32_t timeoutHint,
                                                                                IntrusivePtr_t<DiagnosticInfo_t>& diagnosticInfo)
{
  UASDK_UNUSED(node);
  UASDK_UNUSED(transactionId);
  UASDK_UNUSED(timeoutHint);
  UASDK_UNUSED(diagnosticInfo);

  if(!dataValue.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  return WriteValue(indexRange, *dataValue);
}

} // namespace uasdk

#endif  //UASDK_USE_DATA_ACCESS_HELPERS
