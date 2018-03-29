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

#include "opcua_timestamps_to_return_t.h"
#include "opcua_int32_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(TimestampsToReturn_t, Enumeration_t)

TimestampsToReturn_t::TimestampsToReturn_t(Enum_t value_)
{
  value = value_;
}

bool TimestampsToReturn_t::operator==(TimestampsToReturn_t const & obj) const
{
  return (value == obj.value);
}

bool TimestampsToReturn_t::operator>(TimestampsToReturn_t const & obj) const
{
  return (value > obj.value);
}

Status_t TimestampsToReturn_t::CopyFrom(const BaseDataType_t& source)
{
  const TimestampsToReturn_t* ptr = RuntimeCast<const TimestampsToReturn_t *>(source);
  if(!ptr)
  {
    return TryCopyFromInt32(source);
  }

  return CopyFrom(*ptr);
}

Status_t TimestampsToReturn_t::CopyFrom(const TimestampsToReturn_t& source)
{
  Status_t status = OpcUa_BadOutOfRange;
  if(source.value < RETURN_SOURCE || source.value >= END_INVALID)
  {
    return status;
  }

  value = source.value;

  return OpcUa_Good;
}

Status_t TimestampsToReturn_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Int32_t raw_val((int32_t)value);
  Status_t status = raw_val.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t TimestampsToReturn_t::WriteIntToValue(int32_t newValue)
{
  if ((newValue < 0) || (newValue >= END_INVALID))
  {
	  value = END_INVALID;
  }
  else
  {
	  value = static_cast<Enum_t>(newValue);
  }
  return OpcUa_Good;
}

TimestampsToReturn_t::TimestampsToReturn_t(void)
{
  value = RETURN_NEITHER;
}

TimestampsToReturn_t::~TimestampsToReturn_t()
{}

bool TimestampsToReturn_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool TimestampsToReturn_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t TimestampsToReturn_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t TimestampsToReturn_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

const TimestampsToReturn_t::Enum_t& TimestampsToReturn_t::Value(void) const
{
  return value;
}

TimestampsToReturn_t::Enum_t& TimestampsToReturn_t::Value(void)
{
  return value;
}


} // namespace uasdk
