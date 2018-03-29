/* ----------------------------------------------------------------------------------------
                                        COPYRIGHT (c) 2009 - 2017
                                         HONEYWELL INC.,
                                        ALL RIGHTS RESERVED

            This software is a copyrighted work and/or information protected as a trade
            secret. Legal rights of Honeywell Inc. in this software are distinct from
            ownership of any medium in which the software is embodied. Copyright or trade
            secret notices included must be reproduced in any copies authorized by
            Honeywell Inc. The information in this software is subject to change without
            notice and should not be considered as a commitment by Honeywell Inc.
---------------------------------------------------------------------------------------- */

#include "value_attribute_reader_writer_for_c_api.h"
#if (UASDK_INCLUDE_SERVER)
#if (UASDK_INCLUDE_SERVER_C_API > 0)

#include "ua_server.h"
#include "opcua_datatype_utilities_t.h"

#include "opcua_base_data_type_t.h"
#include "opcua_array_ua_t.h"
#include "opcua_boolean_t.h"
#include "opcua_sbyte_t.h"
#include "opcua_byte_t.h"
#include "opcua_int16_t.h"
#include "opcua_uint16_t.h"
#include "opcua_int32_t.h"
#include "opcua_uint32_t.h"
#include "opcua_int64_t.h"
#include "opcua_uint64_t.h"
#include "opcua_float_t.h"
#include "opcua_double_t.h"
#include "opcua_string_t.h"
#include "opcua_date_time_t.h"
#include "opcua_guid_t.h"
#include "opcua_bytestring_t.h"
#include "opcua_xml_element_t.h"
#include "browse_names_t.h"
#include "address_space_utilities_t.h"
#include "opcua_datatype_utilities_t.h"
#include "opcua_range_t.h"
#include "utilities.h"

namespace uasdk
{

/*
 * private functions
 */

Status_t ConvertToString(uint8_t* data, int32_t length, Array_t<char>& result)
{
  if(!data || (length < 0))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  Status_t status = result.Initialise(length + 1);
  if(status.IsBad())
  {
    return status;
  }

  if(length > 0)
  {
    UASDK_memcpy(result.Value(), data, length);
  }

  result[length] = '\0';

  return OpcUa_Good;
}
 
template<typename T, typename U>
Status_t CopyToUaValue(T& val_, U* rawValue_)
{
  if (!rawValue_)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  val_.Value(*rawValue_);
  return OpcUa_Good;
}

Status_t CopyToUaValue(Guid_t& val_, uint8_t* rawValue_)
{
  if (!rawValue_)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  return val_.CopyFrom(rawValue_);
}

Status_t CopyToUaValue(ByteString_t& val_, UA_Byte_string_t* rawValue_)
{
  if (!rawValue_ || !rawValue_->data || !rawValue_->length || (rawValue_->max_length < 0))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  return val_.CopyFrom(rawValue_->data, rawValue_->length);
}

Status_t CopyToUaValue(String_t& val_, UA_Var_string_t* rawValue_)
{
  if (!rawValue_ || !rawValue_->data || (rawValue_->length < 0) || (rawValue_->max_length < 0))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  Array_t<char> str;
  Status_t status = ConvertToString(rawValue_->data, rawValue_->length, str);
  if(status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  return val_.CopyFrom((const char*)str.Value(), (uint32_t)(str.Count() + 1));
}

Status_t CopyToUaValue(XmlElement_t& val_, UA_Xml_element_t* rawValue_)
{
  if (!rawValue_ || !rawValue_->data || (rawValue_->length < 0) || (rawValue_->max_length < 0))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  Array_t<char> str;
  Status_t status = ConvertToString(rawValue_->data, rawValue_->length, str);
  if(status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  return val_.CopyFrom((const char*)str.Value(), (uint32_t)(str.Count() + 1));
}

template<typename T, typename U>
Status_t CopyToRawValue(T& val_, U* rawValue_)
{
  if (!rawValue_)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  *rawValue_ = val_.Value();
  return OpcUa_Good;
}

Status_t CopyToRawValue(const Guid_t& val_, uint8_t* rawValue_)
{
  if (UASDK_memcpy(rawValue_, val_.Value(), val_.GUID_LENGTH) != rawValue_)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  return OpcUa_Good;
}

Status_t CopyToRawValue(const ByteString_t& val_, UA_Byte_string_t* rawValue_)
{
  if (!rawValue_ || !rawValue_->data)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  if (val_.Length() > rawValue_->max_length)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfRange);
  }

  if (val_.Data())
  {
    UASDK_memcpy(rawValue_->data, val_.Data(), val_.Length());
  }
  rawValue_->length = val_.Length();

  return OpcUa_Good;
}

Status_t CopyToRawValue(const String_t& val_, UA_Var_string_t* rawValue_)
{
  if (!rawValue_ || !rawValue_->data)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  if (val_.Length() > rawValue_->max_length)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfRange);
  }

  UA_UTF8_string_t temp = val_.ToLegacy();
  if (!temp.data)
  {
    UASDK_memcpy(rawValue_->data, "", 1);
    rawValue_->length = 0;
  }
  else
  {
    UASDK_memcpy(rawValue_->data, (temp.data), temp.length);
    rawValue_->length = temp.length;
  }

  return OpcUa_Good;
}

Status_t CopyToRawValue(const XmlElement_t& val_, UA_Xml_element_t* rawValue_)
{
  if (!rawValue_ || !rawValue_->data)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  if (val_.Length() > rawValue_->max_length)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfRange);
  }

  if (!val_.Payload().Data())
  {
    UASDK_memcpy(rawValue_->data, "", 1);
    rawValue_->length = 0;
  }
  else
  {
    UASDK_memcpy(rawValue_->data, val_.Payload().Data(), val_.Length());
    rawValue_->length = val_.Length();
  }

  return OpcUa_Good;
}

template<typename T, typename U>
Status_t ValueAttributeReaderWriterForCAPI_t::UpdateToBaseDataValue(U* rawValue_, IntrusivePtr_t<BaseDataType_t>& value_)
{
  if (!rawValue_)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  Status_t status;
  if (!maxArrayLength)
  {
    T val_;
    status = CopyToUaValue(val_, rawValue_);
    if (status.IsBad())
    {
      UASDK_RETURN_BAD_STATUS(status.Value());
    }

    status = val_.CopyTo(value_);
    if (status.IsBad() || !value_.is_set())
    {
      UASDK_RETURN_BAD_STATUS(status.Value());
    }
  }
  else
  {
    if (maxArrayLength < actualArraySize)
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfRange);
    }

    IntrusivePtr_t< ArrayUA_t<T> > arrayVal_(new SafeRefCount_t< ArrayUA_t<T> >());
    if (!arrayVal_.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }

    status = arrayVal_->Initialise(actualArraySize);
    if (status.IsBad())
    {
      UASDK_RETURN_BAD_STATUS(status.Value());
    }

    for (uint32_t i = 0; i < actualArraySize; i++)
    {
      T val_;

      uint32_t rawValueIndex = i;
      if (val_.TYPE_ID == OpcUaId_Guid)
      {
        rawValueIndex = (i * Guid_t::GUID_LENGTH);
      }

      status = CopyToUaValue(val_, &(rawValue_[rawValueIndex]));
      if (status.IsBad())
      {
        UASDK_RETURN_BAD_STATUS(status.Value());
      }

      IntrusivePtr_t<T> temp(new SafeRefCount_t<T>());
      if (!temp.is_set())
      {
        UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
      }

      status = temp->CopyFrom(val_);
      if (status.IsBad())
      {
        UASDK_RETURN_BAD_STATUS(status.Value());
      }

      (*arrayVal_)[i] = temp;
    }

    value_ = arrayVal_;
  }

  return status;
}

Status_t ValueAttributeReaderWriterForCAPI_t::ConvertRawDataToUaData(UA_Value_t& rawData)
{
  Status_t status;
  IntrusivePtr_t<BaseDataType_t> value;

  switch (valueType)
  {
    case UA_TYPE_Boolean:
      status = UpdateToBaseDataValue<Boolean_t>((bool*)(rawData.value_Boolean), value);
      break;

    case UA_TYPE_SByte:
      status = UpdateToBaseDataValue<SByte_t>((rawData.value_SByte), value);
      break;

    case UA_TYPE_Byte:
      status = UpdateToBaseDataValue<Byte_t>((rawData.value_Byte), value);
      break;

    case UA_TYPE_Int16:
      status = UpdateToBaseDataValue<Int16_t>((rawData.value_Int16), value);
      break;

    case UA_TYPE_UInt16:
      status = UpdateToBaseDataValue<UInt16_t>((rawData.value_UInt16), value);
      break;

    case UA_TYPE_Int32:
      status = UpdateToBaseDataValue<Int32_t>((rawData.value_Int32), value);
      break;

    case UA_TYPE_UInt32:
      status = UpdateToBaseDataValue<UInt32_t>((rawData.value_UInt32), value);
      break;

    case UA_TYPE_Int64:
      status = UpdateToBaseDataValue<Int64_t>(rawData.value_Int64, value);
      break;

    case UA_TYPE_UInt64:
      status = UpdateToBaseDataValue<UInt64_t>((rawData.value_UInt64), value);
      break;

    case UA_TYPE_Float:
      status = UpdateToBaseDataValue<Float_t>((rawData.value_Float), value);
      break;
      
    case UA_TYPE_Double:
      status = UpdateToBaseDataValue<Double_t>((rawData.value_Double), value);
      break;

    case UA_TYPE_String:
      status = UpdateToBaseDataValue<String_t>((rawData.value_String), value);
      break;

    case UA_TYPE_DateTime:
      status = UpdateToBaseDataValue<DateTime_t>((rawData.value_DateTime), value);
      break;

    case UA_TYPE_Guid:
      status = UpdateToBaseDataValue<Guid_t>((rawData.value_GUID), value);
      break;

    case UA_TYPE_ByteString:
      status = UpdateToBaseDataValue<ByteString_t>((rawData.value_ByteString), value);
      break;

    case UA_TYPE_XmlElement:
      status = UpdateToBaseDataValue<XmlElement_t>((rawData.value_XmlElement), value);
      break;

    default:
      UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  if (status.IsBad() || !value.is_set())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  if (dataValue_.is_set() && dataValue_->Value().is_set())
  {
    if (*(dataValue_->Value()) == *value)
    {
      return OpcUa_Good;
    }
  }

  {
    AutoLock_t lk(lock);
    dataValue_.reset(new SafeRefCount_t<DataValue_t>());
    if (!dataValue_.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }

    dataValue_->Value() = value;
  }
  return OpcUa_Good;
}

Status_t ValueAttributeReaderWriterForCAPI_t::ReadValue(UA_Value_t& rawData, Status_t& statusCode_, int64_t& sourceTimeStamp)
{
  if (!rawData.value_Any)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadNoData);
  }

  if(statusCode_.IsBad())
  {
    return statusCode_;
  }

  {
    AutoLock_t lk(lock);
    Status_t status = ConvertRawDataToUaData(rawData);
    if (status.IsBad() || !dataValue_.is_set())
    {
      UASDK_RETURN_BAD_STATUS(status.Value());
    }

    IntrusivePtr_t<DateTime_t> sourceTimeStamp_(new SafeRefCount_t<DateTime_t>());
    if (!sourceTimeStamp_.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }
    sourceTimeStamp_->Value(sourceTimeStamp);
    dataValue_->SourceTimestamp() = sourceTimeStamp_;
    
    IntrusivePtr_t<StatusCode_t> statusCode_ = new SafeRefCount_t<StatusCode_t>();
    if (!statusCode_.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }
    statusCode_->Value().Value(OpcUa_Good);
    dataValue_->StatusCode() = statusCode_;

    return OpcUa_Good;
  }
}

template<typename T, typename U>
Status_t ValueAttributeReaderWriterForCAPI_t::UpdateFromBaseDataValue(U* rawValue_, uint32_t& newLengthOfArray)
{
  if (!dataValue_.is_set() || !dataValue_->Value().is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }
  IntrusivePtr_t<const BaseDataType_t> value_ = dataValue_->Value();
  if (!value_.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  Status_t status;
  if (!value_->IsArray())
  {
    const T* val = RuntimeCast<const T*>(*value_);
    if (!val)
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
    }
    status = CopyToRawValue(*val, rawValue_);
    if (status.IsBad())
    {
      return status;
    }

    newLengthOfArray = 0;
  }
  else
  {
    const ArrayUA_t<T>* val = RuntimeCast<const ArrayUA_t<T>* >(*value_);
    if (!val)
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
    }

    if (val->Size() <= 0)
    {
      newLengthOfArray = val->Size();
      return OpcUa_Good;
    }

    uint32_t startIndex;
    uint32_t endIndex;

    if (indexRange_.Size() > 0)
    {
      startIndex = indexRange_[0].start;
      endIndex = (indexRange_[0].end);

      if ((startIndex < 0) || (startIndex > endIndex) || (startIndex >= maxArrayLength) || (endIndex >= maxArrayLength))
      {
        UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfRange);
      }
      newLengthOfArray = actualArraySize;
    }
    else
    {
      startIndex = 0;
      endIndex = (val->Size() - 1);

      if (endIndex >= maxArrayLength)
      {
        UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfRange);
      }
      newLengthOfArray = val->Size();
    }
    
    for (uint32_t i = startIndex; i <= endIndex; i++)
    {
      IntrusivePtr_t<T> temp = (*val)[i];
      if (!temp.is_set())
      {
        UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
      }

      uint32_t rawValueIndex = i;
      if (temp->TYPE_ID == OpcUaId_Guid)
      {
        rawValueIndex = (i * Guid_t::GUID_LENGTH);
      }

      status = CopyToRawValue(const_cast<const T&>(*temp), &rawValue_[rawValueIndex]);
      if (status.IsBad())
      {
        return status;
      }
    }
  }

  return OpcUa_Good;
}

Status_t ValueAttributeReaderWriterForCAPI_t::WriteValue(UA_Value_t& rawData, int64_t& sourceTimeStamp, uint32_t& newLengthOfArray)
{
  if (!dataValue_.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  Status_t status;
  switch (valueType)
  {
    case UA_TYPE_Boolean:
      status = UpdateFromBaseDataValue<Boolean_t>((bool*)(rawData.value_Boolean), newLengthOfArray);
      break;

    case UA_TYPE_SByte:
      status = UpdateFromBaseDataValue<SByte_t>((rawData.value_SByte), newLengthOfArray);
      break;

    case UA_TYPE_Byte:
      status = UpdateFromBaseDataValue<Byte_t>((rawData.value_Byte), newLengthOfArray);
      break;

    case UA_TYPE_Int16:
      status = UpdateFromBaseDataValue<Int16_t>((rawData.value_Int16), newLengthOfArray);
      break;

    case UA_TYPE_UInt16:
      status = UpdateFromBaseDataValue<UInt16_t>((rawData.value_UInt16), newLengthOfArray);
      break;

    case UA_TYPE_Int32:
      status = UpdateFromBaseDataValue<Int32_t>((rawData.value_Int32), newLengthOfArray);
      break;

    case UA_TYPE_UInt32:
      status = UpdateFromBaseDataValue<UInt32_t>((rawData.value_UInt32), newLengthOfArray);
      break;

    case UA_TYPE_Int64:
      status = UpdateFromBaseDataValue<Int64_t>((rawData.value_Int64), newLengthOfArray);
      break;

    case UA_TYPE_UInt64:
      status = UpdateFromBaseDataValue<UInt64_t>((rawData.value_UInt64), newLengthOfArray);
      break;

    case UA_TYPE_Float:
      status = UpdateFromBaseDataValue<Float_t>((rawData.value_Float), newLengthOfArray);
      break;

    case UA_TYPE_Double:
      status = UpdateFromBaseDataValue<Double_t>((rawData.value_Double), newLengthOfArray);
      break;

    case UA_TYPE_String:
      status = UpdateFromBaseDataValue<String_t>((rawData.value_String), newLengthOfArray);
      break;

    case UA_TYPE_DateTime:
      status = UpdateFromBaseDataValue<DateTime_t>((rawData.value_DateTime), newLengthOfArray);
      break;

    case UA_TYPE_Guid:
      status = UpdateFromBaseDataValue<Guid_t>((rawData.value_GUID), newLengthOfArray);
      break;

    case UA_TYPE_ByteString:
      status = UpdateFromBaseDataValue<ByteString_t>((rawData.value_ByteString), newLengthOfArray);
      break;

    case UA_TYPE_XmlElement:
      status = UpdateFromBaseDataValue<XmlElement_t>((rawData.value_XmlElement), newLengthOfArray);
      break;

    default:
      UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  if (dataValue_->SourceTimestamp().is_set())
  {
    sourceTimeStamp = dataValue_->SourceTimestamp()->Value();
  }

  return OpcUa_Good;
}

#if ((UASDK_USE_HELPERS > 0) && (UASDK_USE_DATA_ACCESS_HELPERS > 0))
IntrusivePtr_t<IVariableNode_t> ValueAttributeReaderWriterForCAPI_t::GetInstrumentRangePropertyNode(const IVariableNode_t& parentNode, Status_t& result)
{
  IntrusivePtr_t<IVariableNode_t> instrumentRangeNode;
  String_t browseName;

  if (!addressSpace.is_set())
  {
    return instrumentRangeNode;
  }

  result = browseName.CopyFrom(BROWSE_NAME_INSTRUMENT_RANGE);
  if (result.IsBad())
  {
    return instrumentRangeNode;
  }
  
  result = AddressSpaceUtilities_t::GetProperty(parentNode, *addressSpace, browseName, instrumentRangeNode);
  if (result.IsBad() || !instrumentRangeNode.is_set())
  {
    return instrumentRangeNode;
  }


  result = OpcUa_Good;
  return instrumentRangeNode;
}

Status_t ValueAttributeReaderWriterForCAPI_t::IsInRange(const IVariableNode_t& instrumentRangeNode, const DataValue_t& parentNodeValue)
{
  if (!instrumentRangeNode.Value().is_set() || !instrumentRangeNode.Value()->Value().is_set() || !parentNodeValue.Value().is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  IntrusivePtr_t<const Range_t> range_ = RuntimeCast<const Range_t*>(*(instrumentRangeNode.Value()->Value()));
  if (!range_.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return AddressSpaceUtilities_t::RangeCheck(*range_, *(parentNodeValue.Value()));
}
#endif  //#if (UASDK_USE_DATA_ACCESS_HELPERS > 0)

/*
 * public functions
 */

ValueAttributeReaderWriterForCAPI_t::ValueAttributeReaderWriterForCAPI_t()
  : nodeHandle(0),
    maxArrayLength(0),
    actualArraySize(0),
    valueType(UA_TYPE_Invalid),
    timeoutHint_(0),
    deferralHandle(0)
{}

ValueAttributeReaderWriterForCAPI_t::~ValueAttributeReaderWriterForCAPI_t()
{
}

Status_t ValueAttributeReaderWriterForCAPI_t::Initialize(uintptr_t nodeHandle_, uint32_t maxArrayLength_, UA_Value_type_t valueType_, IntrusivePtr_t<IAddressSpace_t>& addressSpace_)
{
  if (!addressSpace_.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  nodeHandle = nodeHandle_;
  maxArrayLength = maxArrayLength_;
  actualArraySize = maxArrayLength;
  valueType = valueType_;
  addressSpace = addressSpace_;

  return lock.Initialise();
}

void ValueAttributeReaderWriterForCAPI_t::PerformRead(UA_Value_t rawData_, Status_t statusCode_, int64_t sourceTimeStamp_)
{
  statusCode = ReadValue(rawData_, statusCode_, sourceTimeStamp_);
}

void ValueAttributeReaderWriterForCAPI_t::PerformWrite(UA_Value_t& rawData_, int64_t& sourceTimeStamp_, uint32_t& newLengthOfArray)
{
  statusCode = WriteValue(rawData_, sourceTimeStamp_, newLengthOfArray);
  {
    AutoLock_t lk(lock);
    actualArraySize = newLengthOfArray;
  }
}

Status_t ValueAttributeReaderWriterForCAPI_t::SetWriteOperationLevelResultCode(Status_t resultCode)
{
  if (resultCode.IsBad() && (resultCode != statusCode))
  {
    statusCode = resultCode;
  }

  return OpcUa_Good;
}

bool ValueAttributeReaderWriterForCAPI_t::IsReadOperationDeferred(void)
{
  if (deferralHandle > 0)
  {
    return true;
  }

  return false;
}

uint32_t ValueAttributeReaderWriterForCAPI_t::GetReadTimeOutHint(void)
{
  return timeoutHint_;
}

Status_t ValueAttributeReaderWriterForCAPI_t::UpdateDeferralHandle(uintptr_t* deferralHandle_)
{
  if (!deferralHandle_)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  if (deferralHandle > 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadNotReadable);
  }

  {
    AutoLock_t lk(lock);
    deferralHandle = *deferralHandle_;
  }

  return OpcUa_Good;
}

Status_t ValueAttributeReaderWriterForCAPI_t::ReadDeferralComplete(void)
{
  if (!deferralHandle || !readCompletedCallback.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  if (statusCode.IsBad() || !dataValue_.is_set())
  {
    UASDK_RETURN_BAD_STATUS(statusCode.Value());
  }

  IntrusivePtr_t<DataValue_t> temp (new SafeRefCount_t<DataValue_t>());
  if(!temp.is_set())
  {
	  UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  Status_t status = temp->CopyFrom(*dataValue_);
  if(status.IsBad())
  {
	  UASDK_RETURN_BAD_STATUS(statusCode.Value());
  }
  status = readCompletedCallback->ReadValueAttributeCompleted(temp);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  {
    AutoLock_t lk(lock);
    timeoutHint_ = 0;
    deferralHandle = 0;
    readCompletedCallback.reset();
  }

  return OpcUa_Good;
}

void ValueAttributeReaderWriterForCAPI_t::CallApplicationLayerRead(void)
{
  UAServer_Callback_read(nodeHandle, valueType, maxArrayLength, (uintptr_t)this);
}

bool ValueAttributeReaderWriterForCAPI_t::CanReadValueSynchronously(const IVariableNode_t& node)
{
  UASDK_UNUSED(node);
  //return false; //Asynchronous read is supported in the next release
  return true;
}

Status_t ValueAttributeReaderWriterForCAPI_t::ReadValueAttributeBegin(
  IntrusivePtr_t<const IVariableNode_t>& node,
  uint32_t maxAge,
  bool setSourceTimestamp,
  IntrusivePtr_t<const ArrayUA_t<String_t> >& locales,
  IntrusivePtr_t<const ArrayRef_t<IndexRange_t> >& indexRange,
  uint32_t transactionId,
  uint32_t timeoutHint,
  IntrusivePtr_t<ICallbackNodeValueAttributeAccessCompleted_t>& completedCallback)
{
#if 0   //Eanble this for next release
  UASDK_UNUSED(node);
  UASDK_UNUSED(maxAge);
  UASDK_UNUSED(setSourceTimestamp);
  UASDK_UNUSED(locales);
  UASDK_UNUSED(indexRange);
  UASDK_UNUSED(transactionId);
  timeoutHint_ = timeoutHint;

  if (!node.is_set() || !completedCallback.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  Status_t status;
  //For backup in case of error
#if (UASDK_USE_DATA_ACCESS_HELPERS > 0)
  IntrusivePtr_t<DataValue_t> backup;
  if (dataValue_.is_set())
  {
    backup.reset(new SafeRefCount_t<DataValue_t>);
    if (!backup.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }
    status = backup->CopyFrom(*dataValue_);
    if (status.IsBad())
    {
      UASDK_RETURN_BAD_STATUS(status.Value());
    }
  }
#endif  //#if (UASDK_USE_DATA_ACCESS_HELPERS > 0)

  CallApplicationLayerRead();

  if (statusCode.IsBad() || (!deferralHandle && !dataValue_.is_set()) )
  {
    UASDK_RETURN_BAD_STATUS(statusCode.Value());
  }

#if ((UASDK_USE_HELPERS > 0) && (UASDK_USE_DATA_ACCESS_HELPERS > 0))
  //Do the range check first. If there is any Instrument range property
  {
    IntrusivePtr_t<IVariableNode_t> instrumentRangeNode = GetInstrumentRangePropertyNode(*node, status);
    if (instrumentRangeNode.is_set() && status.IsGood())
    {
      status = IsInRange(*instrumentRangeNode, *dataValue_);
      if (status.IsBad())
      {
        dataValue_ = backup;
        UASDK_RETURN_BAD_STATUS(status.Value());
      }
    }
  }
#endif  //#if (UASDK_USE_DATA_ACCESS_HELPERS > 0)

  if(!deferralHandle)
  {
	  IntrusivePtr_t<DataValue_t> temp (new SafeRefCount_t<DataValue_t>());
	  if(!temp.is_set())
	  {
	    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
	  }
	  status = temp->CopyFrom(*dataValue_);
	  if(status.IsBad())
	  {
	    UASDK_RETURN_BAD_STATUS(statusCode.Value());
	  }
    return completedCallback->ReadValueAttributeCompleted(temp);
  }
  if(!readCompletedCallback.is_set())
  {
    readCompletedCallback = completedCallback;
  }
  return OpcUa_Good;
#else
  UASDK_UNUSED(node);
  UASDK_UNUSED(maxAge);
  UASDK_UNUSED(setSourceTimestamp);
  UASDK_UNUSED(locales);
  UASDK_UNUSED(indexRange);
  UASDK_UNUSED(transactionId);
  UASDK_UNUSED(timeoutHint);
  UASDK_UNUSED(completedCallback);

  return OpcUa_BadNotReadable;
#endif  //0
}

Status_t ValueAttributeReaderWriterForCAPI_t::ReadValueAttribute(
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
#if 0   // Enable this from next release
  UASDK_UNUSED(node);
  UASDK_UNUSED(maxAge);
  UASDK_UNUSED(setSourceTimestamp);
  UASDK_UNUSED(locales);
  UASDK_UNUSED(indexRange);
  UASDK_UNUSED(transactionId);
  UASDK_UNUSED(timeoutHint);
  UASDK_UNUSED(dataValue);
  UASDK_UNUSED(diagnosticInfo);

  return OpcUa_BadNotReadable;
#else

  UASDK_UNUSED(node);
  UASDK_UNUSED(maxAge);
  UASDK_UNUSED(setSourceTimestamp);
  UASDK_UNUSED(locales);
  UASDK_UNUSED(transactionId);
  UASDK_UNUSED(diagnosticInfo);

  timeoutHint_ = timeoutHint;
  
  Status_t status;
  
  //For backup in case of error
#if (UASDK_USE_DATA_ACCESS_HELPERS > 0)
  IntrusivePtr_t<DataValue_t> backup;
  if (dataValue_.is_set())
  {
    backup.reset(new SafeRefCount_t<DataValue_t>);
    if (!backup.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }
    status = backup->CopyFrom(*dataValue_);
    if (status.IsBad())
    {
      UASDK_RETURN_BAD_STATUS(status.Value());
    }
  }
#endif  //#if (UASDK_USE_DATA_ACCESS_HELPERS > 0)

  CallApplicationLayerRead();

  if (statusCode.IsBad() || !dataValue_.is_set())
  {
    UASDK_RETURN_BAD_STATUS(statusCode.Value());
  }

#if ((UASDK_USE_HELPERS > 0) && (UASDK_USE_DATA_ACCESS_HELPERS > 0))
  //Do the range check first. If there is any Instrument range property
  {
    IntrusivePtr_t<IVariableNode_t> instrumentRangeNode = GetInstrumentRangePropertyNode(node, status);
    if (instrumentRangeNode.is_set() && status.IsGood())
    {
      status = IsInRange(*instrumentRangeNode, *dataValue_);
      if (status.IsBad())
      {
        dataValue_ = backup;
        UASDK_RETURN_BAD_STATUS(status.Value());
      }
    }
  }
#endif  //#if (UASDK_USE_DATA_ACCESS_HELPERS > 0)

  dataValue.reset(new SafeRefCount_t<DataValue_t>());
  if (!dataValue.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  return dataValue->WriteSubsetFrom(indexRange, *dataValue_);

#endif  //0
}

bool ValueAttributeReaderWriterForCAPI_t::CanWriteValueSynchronously(const IVariableNode_t& node)
{
  UASDK_UNUSED(node);
  return true;
}

Status_t ValueAttributeReaderWriterForCAPI_t::WriteValueAttributeBegin(
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

  UASDK_RETURN_BAD_STATUS(OpcUa_BadNotSupported);
}

Status_t ValueAttributeReaderWriterForCAPI_t::WriteValueAttribute(
  IVariableNode_t& node,
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

  if (!dataValue_.is_set() || !dataValue.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  Status_t status;

#if ((UASDK_USE_HELPERS > 0) && (UASDK_USE_DATA_ACCESS_HELPERS > 0))
  //Do the range check first. If there is any Instrument range property
  {
    IntrusivePtr_t<IVariableNode_t> instrumentRangeNode = GetInstrumentRangePropertyNode(node, status);
    if (instrumentRangeNode.is_set() && status.IsGood())
    {
      status = IsInRange(*instrumentRangeNode, *dataValue);
      if (status.IsBad())
      {
        UASDK_RETURN_BAD_STATUS(status.Value());
      }
    }
  }
#endif  //#if (UASDK_USE_DATA_ACCESS_HELPERS > 0)

  //For backup in case of error
  IntrusivePtr_t<DataValue_t> backup(new SafeRefCount_t<DataValue_t>);
  if (!backup.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  {
    AutoLock_t lk(lock);
    status = backup->CopyFrom(*dataValue_);
    if (status.IsBad())
    {
      UASDK_RETURN_BAD_STATUS(status.Value());
    }

    status = dataValue_->WriteSubsetFrom(indexRange, *dataValue);
    if (status.IsBad())
    {
      dataValue_ = backup;
      UASDK_RETURN_BAD_STATUS(status.Value());
    }
  }

  indexRange_ = indexRange;
  UAServer_Callback_write(nodeHandle, valueType, status.Value(), maxArrayLength, (uintptr_t)this);

  //If there was error while writing, keep the old value!
  if (statusCode.IsBad())
  {
    dataValue_ = backup;
  }

  return statusCode;
}

} //namespace uasdk

#endif // UASDK_INCLUDE_SERVER_C_API
#endif //(UASDK_INCLUDE_SERVER)
