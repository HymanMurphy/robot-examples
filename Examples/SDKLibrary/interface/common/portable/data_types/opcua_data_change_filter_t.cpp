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

#include "opcua_data_change_filter_t.h"
#include "buffer_t.h"
#include "opcua_array_ua_t.h"
#include "opcua_byte_t.h"
#include "opcua_double_t.h"
#include "opcua_float_t.h"
#include "opcua_int16_t.h"
#include "opcua_int32_t.h"
#include "opcua_int64_t.h"
#include "opcua_uint16_t.h"
#include "opcua_uint32_t.h"
#include "opcua_uint64_t.h"
#include "opcua_sbyte_t.h"

#if (UASDK_INCLUDE_SUBSCRIPTIONS > 0)

#undef abs
#define abs(x) (((x) < 0)? -(x): (x))//lint !e652

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(DataChangeFilter_t, Structure_t)

template<typename T>
UASDK_DEADBAND_DATA_TYPE DataChangeFilterExtractValue(const BaseDataType_t& base)
{
  UASDK_DEADBAND_DATA_TYPE value = 0;
  T* concrete = RuntimeCast<T *>(base);
  if (concrete)
  {
    value = static_cast<UASDK_DEADBAND_DATA_TYPE>(concrete->Value());
  }
  return value;
}

template <typename T>
bool DataChangeFilterCalculateDeadbandVector(DataChangeFilter_t& obj,
                                             const BaseDataType_t& newValue,
                                             const BaseDataType_t& oldValue,
                                             Range_t& euRange)
{
  T* concreteNew = RuntimeCast<T *>(newValue);
  T* concreteOld = RuntimeCast<T *>(oldValue);

  if (!concreteNew || !concreteOld)
  {
    return false;
  }

  uint32_t count = concreteNew->Count();
  if (count != concreteOld->Count())
  {
    //Array dimensions are different
    return true;
  }

  for (uint32_t i = 0; i < count; i++)
  {
    UASDK_DEADBAND_DATA_TYPE newVal = static_cast<UASDK_DEADBAND_DATA_TYPE>((*concreteNew)[i]->Value());
    UASDK_DEADBAND_DATA_TYPE oldVal = static_cast<UASDK_DEADBAND_DATA_TYPE>((*concreteOld)[i]->Value());

    if (obj.CalculateDeadbandScalar(newVal, oldVal, euRange))
    {
      return true;
    }
  }
  return false;
}

const uint32_t DataChangeFilter_t::DEADBAND_TYPE_NONE = 0;
const uint32_t DataChangeFilter_t::DEADBAND_TYPE_ABSOLUTE = 1;
const uint32_t DataChangeFilter_t::DEADBAND_TYPE_PERCENT = 2;

DataChangeFilter_t::DataChangeFilter_t()
{
  trigger = OPCUA_DATACHANGE_TRIGGER_STATUS_VALUE;
}

DataChangeFilter_t::~DataChangeFilter_t() {}

bool DataChangeFilter_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool DataChangeFilter_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t DataChangeFilter_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t DataChangeFilter_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t DataChangeFilter_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_DataChangeFilter_Encoding_DefaultBinary;
}

const DataChangeFilter_t::DataChangeTrigger_t& DataChangeFilter_t::Trigger(void) const
{
  return trigger;
}

DataChangeFilter_t::DataChangeTrigger_t& DataChangeFilter_t::Trigger(void)
{
  return trigger;
}

const UInt32_t& DataChangeFilter_t::DeadbandType(void) const
{
  return deadbandType;
}

UInt32_t& DataChangeFilter_t::DeadbandType(void)
{
  return deadbandType;
}

const Double_t& DataChangeFilter_t::DeadbandValue(void) const
{
  return deadbandValue;
}

Double_t& DataChangeFilter_t::DeadbandValue(void)
{
  return deadbandValue;
}

DataChangeFilter_t& DataChangeFilter_t::operator=(DataChangeFilter_t const & other)
{
  if (this != &other)
  {
    trigger = other.trigger;
    deadbandType.Value(other.deadbandType.Value());
    deadbandValue.Value(other.deadbandValue.Value());
  }
  return *this;
}

bool DataChangeFilter_t::operator==(DataChangeFilter_t const & obj) const
{
  return (
      (trigger == obj.trigger)
      && (deadbandType == obj.deadbandType)
      && (deadbandValue == obj.deadbandValue));
}

bool DataChangeFilter_t::operator>(DataChangeFilter_t const & obj) const
{
  return (
      (trigger > obj.trigger)
      && (deadbandType > obj.deadbandType)
      && (deadbandValue > obj.deadbandValue));
}

Status_t DataChangeFilter_t::CopyFrom(const DataChangeFilter_t& source)
{
  Status_t status = OpcUa_BadOutOfRange;

  if ( (source.trigger < 0) || (source.trigger > OPCUA_DATACHANGE_TRIGGER_END) )
  {
    return status;
  }

  trigger = source.trigger;

  status = deadbandType.CopyFrom(source.deadbandType);
  if (status.IsBad())
  {
    return status;
  }

  status = deadbandValue.CopyFrom(source.deadbandValue);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t DataChangeFilter_t::CopyFrom(const BaseDataType_t& source)
{
  const DataChangeFilter_t* ptr = RuntimeCast<const DataChangeFilter_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t DataChangeFilter_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Int32_t trig_raw((int32_t)trigger);
  Status_t status = trig_raw.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = deadbandType.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = deadbandValue.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return 0;
}

Status_t DataChangeFilter_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, DataChangeFilter_t& result)
{
  Int32_t trig_raw(0);
  Status_t status = Int32_t::Decode(buffer, decoder, trig_raw);
  if (status.IsBad())
  {
    return status;
  }

  result.Trigger() = DataChangeFilter_t::DataChangeTrigger_t(trig_raw.Value());

  status = UInt32_t::Decode(buffer, decoder, result.DeadbandType());
  if (status.IsBad())
  {
    return status;
  }

  status = Double_t::Decode(buffer, decoder, result.DeadbandValue());
  if (status.IsBad())
  {
    return status;
  }

  return 0;
}

bool DataChangeFilter_t::DoesValuePassFilter(DataValue_t& newValue,
                                             DataValue_t& previousValue,
                                             Range_t& euRange)
{
  if ((!newValue.Value().is_set()) || (!previousValue.Value().is_set()))
  {
    //Value(s) are empty
    return true;
  }

  uint16_t namespaceIndex = 0;
  if (newValue.Value()->TypeId(namespaceIndex) != previousValue.Value()->TypeId(namespaceIndex))
  {
    //Value(s) are of different type
    return true;
  }

  if (newValue.Value()->IsArray() != previousValue.Value()->IsArray())
  {
    //Value(s) are of different type
    return true;
  }


  if ((newValue.StatusCode().is_set()) != previousValue.StatusCode().is_set())
  {
    //Status code has changed
    return true;
  }

  if (newValue.StatusCode().is_set() && (*newValue.StatusCode() != *previousValue.StatusCode()))
  {
    //Status code has changed, check for an overflow bit in the previous value (which is acceptable)
    uint32_t overflow = 0x00000480;
    uint32_t s1 = newValue.StatusCode()->Value().Value() | overflow;
    if (s1 != previousValue.StatusCode()->Value().Value())
    {
      return true;
    }
  }

  if (trigger == OPCUA_DATACHANGE_TRIGGER_STATUS)
  {
    //We only care about status and that is unchanged
    return false;
  }

  if ((trigger == OPCUA_DATACHANGE_TRIGGER_STATUS_VALUE_TIMESTAMP)
      && (deadbandType.Value() == DEADBAND_TYPE_NONE))
  {
    if ((newValue.SourceTimestamp().is_set()) !=  previousValue.SourceTimestamp().is_set())
    {
      //Source timestamp has changed
      return true;
    }
    if (newValue.SourceTimestamp().is_set() && (newValue.SourceTimestamp()->Value() != previousValue.SourceTimestamp()->Value()))
    {
      //Source timestamp has changed
      return true;
    }
  }

  //If we get here we care about value changes

  if ((!newValue.Value()->IsNumber()) || (deadbandType.Value() == DEADBAND_TYPE_NONE))
  {
    //There is no dead band or we cannot apply a dead band so check for equality
    return (*newValue.Value() != *previousValue.Value());
  }

  //We have two valid values, let's calculate
  if (newValue.Value()->IsArray())
  {
    return CalculateDeadbandVector(*newValue.Value(), *previousValue.Value(), euRange);
  }
  else
  {
    return CalculateDeadbandScalar(*newValue.Value(), *previousValue.Value(), euRange);
  }
}

bool DataChangeFilter_t::CalculateDeadbandScalar(const BaseDataType_t& newValue,
                                                 const BaseDataType_t& oldValue,
                                                 Range_t& euRange)
{
  UASDK_DEADBAND_DATA_TYPE newVal = 0.0f;
  UASDK_DEADBAND_DATA_TYPE oldVal = 0.0f;

  uint16_t namespaceIndex = 0;
  switch (newValue.TypeId(namespaceIndex))
  {
  case OpcUaId_SByte:
    newVal = DataChangeFilterExtractValue<const SByte_t>(newValue);
    oldVal = DataChangeFilterExtractValue<const SByte_t>(oldValue);
  	break;

  case OpcUaId_Byte:
    newVal = DataChangeFilterExtractValue<const Byte_t>(newValue);
    oldVal = DataChangeFilterExtractValue<const Byte_t>(oldValue);
    break;

  case OpcUaId_Int16:
    newVal = DataChangeFilterExtractValue<const Int16_t>(newValue);
    oldVal = DataChangeFilterExtractValue<const Int16_t>(oldValue);
    break;

  case OpcUaId_UInt16:
    newVal = DataChangeFilterExtractValue<const UInt16_t>(newValue);
    oldVal = DataChangeFilterExtractValue<const UInt16_t>(oldValue);
    break;

  case OpcUaId_Int32:
    newVal = DataChangeFilterExtractValue<const Int32_t>(newValue);
    oldVal = DataChangeFilterExtractValue<const Int32_t>(oldValue);
    break;

  case OpcUaId_UInt32:
    newVal = DataChangeFilterExtractValue<const UInt32_t>(newValue);
    oldVal = DataChangeFilterExtractValue<const UInt32_t>(oldValue);
    break;

  case OpcUaId_Int64:
    newVal = DataChangeFilterExtractValue<const Int64_t>(newValue);
    oldVal = DataChangeFilterExtractValue<const Int64_t>(oldValue);
    break;

  case OpcUaId_UInt64:
    newVal = DataChangeFilterExtractValue<const UInt64_t>(newValue);
    oldVal = DataChangeFilterExtractValue<const UInt64_t>(oldValue);
    break;

  case OpcUaId_Float:
    newVal = DataChangeFilterExtractValue<const Float_t>(newValue);
    oldVal = DataChangeFilterExtractValue<const Float_t>(oldValue);
    break;

  case OpcUaId_Double:
    newVal = DataChangeFilterExtractValue<const Double_t>(newValue);
    oldVal = DataChangeFilterExtractValue<const Double_t>(oldValue);
    break;

  default:
    return true;
  }

  return CalculateDeadbandScalar(newVal, oldVal, euRange);
}

bool DataChangeFilter_t::CalculateDeadbandVector(const BaseDataType_t& newValue,
                                                 const BaseDataType_t& oldValue,
                                                 Range_t& euRange)
{
  uint16_t namespaceIndex = 0;
  switch (newValue.TypeId(namespaceIndex))
  {
  case OpcUaId_SByte:
      return DataChangeFilterCalculateDeadbandVector<const ArrayUA_t<SByte_t> >(*this, newValue, oldValue, euRange);

  case OpcUaId_Byte:
    return DataChangeFilterCalculateDeadbandVector<const ArrayUA_t<Byte_t> >(*this, newValue, oldValue, euRange);

  case OpcUaId_Int16:
    return DataChangeFilterCalculateDeadbandVector<const ArrayUA_t<Int16_t> >(*this, newValue, oldValue, euRange);

  case OpcUaId_UInt16:
    return DataChangeFilterCalculateDeadbandVector<const ArrayUA_t<UInt16_t> >(*this, newValue, oldValue, euRange);

  case OpcUaId_Int32:
    return DataChangeFilterCalculateDeadbandVector<const ArrayUA_t<Int32_t> >(*this, newValue, oldValue, euRange);

  case OpcUaId_UInt32:
    return DataChangeFilterCalculateDeadbandVector<const ArrayUA_t<UInt32_t> >(*this, newValue, oldValue, euRange);

  case OpcUaId_Int64:
    return DataChangeFilterCalculateDeadbandVector<const ArrayUA_t<Int64_t> >(*this, newValue, oldValue, euRange);

  case OpcUaId_UInt64:
    return DataChangeFilterCalculateDeadbandVector<const ArrayUA_t<UInt64_t> >(*this, newValue, oldValue, euRange);

  case OpcUaId_Float:
    return DataChangeFilterCalculateDeadbandVector<const ArrayUA_t<Float_t> >(*this, newValue, oldValue, euRange);

  case OpcUaId_Double:
    return DataChangeFilterCalculateDeadbandVector<const ArrayUA_t<Double_t> >(*this, newValue, oldValue, euRange);

  default:
    return false;
  }
  return false;
}

bool DataChangeFilter_t::CalculateDeadbandScalar( UASDK_DEADBAND_DATA_TYPE new_val, UASDK_DEADBAND_DATA_TYPE old_val, Range_t& euRange )
{
  switch (deadbandType.Value())
  {
  case DEADBAND_TYPE_ABSOLUTE:
    return (abs(old_val - new_val) > (UASDK_DEADBAND_DATA_TYPE)deadbandValue.Value());

  case DEADBAND_TYPE_PERCENT:
    return (abs(old_val - new_val) > (((UASDK_DEADBAND_DATA_TYPE)deadbandValue.Value()) / (UASDK_DEADBAND_DATA_TYPE)100.0f) * ((UASDK_DEADBAND_DATA_TYPE)euRange.High().Value() - (UASDK_DEADBAND_DATA_TYPE)euRange.Low().Value()));

  case DEADBAND_TYPE_NONE:
  default:
    return (new_val != old_val);
  }
}

} // namespace uasdk

#endif
