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

#include "filter_operator_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "opcua_int32_t.h"
#include "opcua_status_codes.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(FilterOperator_t, Enumeration_t);

FilterOperator_t::FilterOperator_t()
{
	value = FILTER_OP_END;
}

FilterOperator_t::FilterOperator_t(FilterOperator_t::Enum_t value_)
{
  if ( (value_ < FILTER_OP_EQUAL) || value_ >= FILTER_OP_END)
  {
    value = FILTER_OP_END;
  }
  else
  {
    value = value_;
  }
}

FilterOperator_t::~FilterOperator_t()
{
}

bool FilterOperator_t::operator==(BaseDataType_t const & obj) const
{
	return OperatorEqualTo(*this, obj);
}

bool FilterOperator_t::operator==(FilterOperator_t const & obj) const
{
  return (
    (value == obj.value));
}

bool FilterOperator_t::operator>(BaseDataType_t const & obj) const
{
	return OperatorGreaterThan(*this, obj);
}

bool FilterOperator_t::operator>(FilterOperator_t const & obj) const
{
  if ( (obj.value < FILTER_OP_EQUAL) || obj.value >= FILTER_OP_END)
  {
    return false;
  }

  return (value > obj.value);
}

Status_t FilterOperator_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
	return CopyToDestination(*this, destination);
}

Status_t FilterOperator_t::WriteIntToValue(int32_t newValue)
{
  if (newValue >= FILTER_OP_EQUAL && newValue <= FILTER_OP_BITWISEOR)
  {
    value = (Enum_t)newValue;
    return OpcUa_Good;
  }

  return OpcUa_BadInvalidArgument;
}

Status_t FilterOperator_t::CopyFrom(const BaseDataType_t& source)
{
  IntrusivePtr_t<const FilterOperator_t> ptr = RuntimeCast<const FilterOperator_t*>(source);
  if (!ptr.is_set())
  {
    return OpcUa_BadTypeMismatch;
  }

  return CopyFrom(*ptr);
}

Status_t FilterOperator_t::CopyFrom(const FilterOperator_t& source)
{
  Status_t status = OpcUa_BadOutOfRange;

  if ( (source.value < FILTER_OP_EQUAL) || (source.value >= FILTER_OP_END))
  {
    return status;
  }

  value = source.value;
  return OpcUa_Good;
}

uint32_t FilterOperator_t::TypeId(uint16_t& namespaceIndex)  const
{
	namespaceIndex = 0; return TYPE_ID;
}

const FilterOperator_t::Enum_t& FilterOperator_t::Value(void) const 
{ 
	return value; 
}

FilterOperator_t::Enum_t& FilterOperator_t::Value(void) 
{ 
	return value; 
}

Status_t FilterOperator_t::Value(FilterOperator_t::Enum_t value_) 
{ 
	value = value_; 
	return OpcUa_Good; 
}

Status_t FilterOperator_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Int32_t raw_val((int32_t)value);
  Status_t status = raw_val.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t FilterOperator_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, FilterOperator_t& result)
{
  Int32_t raw_val(0);
  Status_t status = Int32_t::Decode(buffer, decoder, raw_val);
  if (status.IsBad())
  {
    return status;
  }

  if ( (raw_val.Value() < FILTER_OP_EQUAL) || (raw_val.Value() >= FILTER_OP_END) )
  {
    return OpcUa_BadDecodingError;
  }
  else
  {
    result.Value() = FilterOperator_t::Enum_t(raw_val.Value());
  }

  return status;
}
	
} // namespace uasdk

#endif // UASDK_INCLUDE_EVENTS
