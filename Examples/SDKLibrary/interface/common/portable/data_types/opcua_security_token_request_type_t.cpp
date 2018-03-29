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

#include "opcua_security_token_request_type_t.h"
#include "opcua_int32_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(SecurityTokenRequestType_t, Enumeration_t)

SecurityTokenRequestType_t::SecurityTokenRequestType_t(void)
  : value(OPCUA_SECURITY_TOKEN_REQUEST_TYPE_ISSUE)
{
}

SecurityTokenRequestType_t::SecurityTokenRequestType_t(Enum_t value_)
{
  value = value_;
}

bool SecurityTokenRequestType_t::operator==(SecurityTokenRequestType_t const & obj) const
{
  return (value == obj.value);
}

bool SecurityTokenRequestType_t::operator>(SecurityTokenRequestType_t const & obj) const
{
  return (value > obj.value);
}

Status_t SecurityTokenRequestType_t::CopyFrom(const BaseDataType_t& source)
{
  const SecurityTokenRequestType_t* ptr = RuntimeCast<const SecurityTokenRequestType_t *>(source);
  if(!ptr)
  {
    return TryCopyFromInt32(source);
  }

  return CopyFrom(*ptr);
}

Status_t SecurityTokenRequestType_t::CopyFrom(const SecurityTokenRequestType_t& source)
{
  Status_t status = OpcUa_BadOutOfRange;
  if(source.value < OPCUA_SECURITY_TOKEN_REQUEST_TYPE_ISSUE || source.value >= OPCUA_SECURITY_TOKEN_REQUEST_TYPE_END)
  {
    return status;
  }
  value = source.value;

  return OpcUa_Good;
}

Status_t SecurityTokenRequestType_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Int32_t raw_val((int32_t)value);
  Status_t status = raw_val.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t SecurityTokenRequestType_t::WriteIntToValue(int32_t newValue)
{
  if ((newValue < 0) || (newValue >= OPCUA_SECURITY_TOKEN_REQUEST_TYPE_END))
  {
	  UASDK_RETURN_BAD_STATUS(OpcUa_BadDecodingError);
  }
  else
  {
    value = static_cast<Enum_t>(newValue);
  }
  return OpcUa_Good;
}

SecurityTokenRequestType_t::~SecurityTokenRequestType_t()
{}

bool SecurityTokenRequestType_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool SecurityTokenRequestType_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t SecurityTokenRequestType_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t SecurityTokenRequestType_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

const SecurityTokenRequestType_t::Enum_t& SecurityTokenRequestType_t::Value(void) const
{
  return value;
}

SecurityTokenRequestType_t::Enum_t& SecurityTokenRequestType_t::Value(void)
{
  return value;
}

} // namespace uasdk
