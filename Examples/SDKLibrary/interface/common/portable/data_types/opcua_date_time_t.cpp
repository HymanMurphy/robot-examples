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

#include "opcua_date_time_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(DateTime_t, BaseDataType_t)

bool DateTime_t::operator==(DateTime_t const & obj) const
{
  return value == obj.value;
}

bool DateTime_t::operator>(DateTime_t const & obj) const
{
  return value > obj.value;
}

Status_t DateTime_t::CopyFrom(const DateTime_t& source)
{
  Status_t status = value.CopyFrom(source.value);

  if(status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t DateTime_t::CopyFrom(const BaseDataType_t& source)
{
  const DateTime_t* ptr = RuntimeCast<const DateTime_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t DateTime_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = value.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t DateTime_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, DateTime_t& result)
{
  Int64_t value;
  Status_t status = Int64_t::Decode(buffer, decoder, value);
  if (status.IsBad())
  {
    return status;
  }
  result.Value(value.Value());

  return status;
}

DateTime_t::DateTime_t() 
  : value(0) 
{}

DateTime_t::DateTime_t(int64_t val) 
  : value(val) 
{}

DateTime_t::~DateTime_t(void) 
{}

DateTime_t& DateTime_t::operator=(DateTime_t const & obj)
{
  value = obj.value;
  return *this;
}

DateTime_t& DateTime_t::operator=(Int64_t const & obj)
{
  value = obj;
  return *this;
}

DateTime_t& DateTime_t::operator=(int64_t const & obj)
{
  value = obj;
  return *this;
}

bool DateTime_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool DateTime_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t DateTime_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t DateTime_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

int64_t DateTime_t::Value(void) const 
{ 
  return value.Value(); 
}

void DateTime_t::Value(int64_t val) 
{ 
  value.Value(val); 
}

} // namespace uasdk
