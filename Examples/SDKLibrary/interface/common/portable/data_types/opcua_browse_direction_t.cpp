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

#include "opcua_browse_direction_t.h"
#include "opcua_int32_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(BrowseDirection_t, Enumeration_t)

BrowseDirection_t::BrowseDirection_t(Enum_t value_)
{
  value = value_;
}

bool BrowseDirection_t::operator==(BrowseDirection_t const & obj) const
{
  return value == obj.value;
}

bool BrowseDirection_t::operator>(BrowseDirection_t const & obj) const
{
  if ( (obj.value < 0) || obj.value > DIRECTION_END)
  {
    return false;
  }

  return (value > obj.value);
}

Status_t BrowseDirection_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

Status_t BrowseDirection_t::CopyFrom(const BrowseDirection_t& source)
{
  Status_t status = OpcUa_BadOutOfRange;

  if ( (source.value < 0) || (source.value > DIRECTION_END))
  {
    return status;
  }

  value = source.value;

  return OpcUa_Good;
}

Status_t BrowseDirection_t::CopyFrom(const BaseDataType_t& source)
{
  const BrowseDirection_t* ptr = RuntimeCast<const BrowseDirection_t *>(source);
  if(!ptr)
  {
    return TryCopyFromInt32(source);
  }

  return CopyFrom(*ptr);
}

Status_t BrowseDirection_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Int32_t raw_val((int32_t)value);
  Status_t status = raw_val.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t BrowseDirection_t::WriteIntToValue(int32_t newValue)
{
  if ((newValue < 0) || (newValue >= DIRECTION_END))
  {
    value = DIRECTION_INVALID;
  }
  else
  {
    value = static_cast<Enum_t>(newValue);
  }
  return OpcUa_Good;
}

BrowseDirection_t::BrowseDirection_t(void) 
  : value(DIRECTION_FORWARD) 
{}

BrowseDirection_t::~BrowseDirection_t() 
{}

bool BrowseDirection_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool BrowseDirection_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

uint32_t BrowseDirection_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

const BrowseDirection_t::Enum_t& BrowseDirection_t::Value(void) const
{ 
  return value; 
}

BrowseDirection_t::Enum_t& BrowseDirection_t::Value(void) 
{ 
  return value; 
}

} // namespace uasdk
