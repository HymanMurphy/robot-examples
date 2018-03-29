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

#include "opcua_user_identity_token_type_t.h"
#include "opcua_int32_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(UserIdentityTokenType_t, Enumeration_t)

UserIdentityTokenType_t::UserIdentityTokenType_t(void)
: value(OPCUA_USER_IDENTITY_TOKEN_TYPE_ANONYMOUS)
{
}

UserIdentityTokenType_t::UserIdentityTokenType_t(Enum_t value_)
{
  value = value_;
}

bool UserIdentityTokenType_t::operator==(UserIdentityTokenType_t const & obj) const
{
  return (value == obj.value);
}

bool UserIdentityTokenType_t::operator>(UserIdentityTokenType_t const & obj) const
{
  return (value > obj.value);
}

Status_t UserIdentityTokenType_t::CopyFrom(const BaseDataType_t& source)
{
  const UserIdentityTokenType_t* ptr = RuntimeCast<const UserIdentityTokenType_t *>(source);
  if(!ptr)
  {
    return TryCopyFromInt32(source);
  }

  return CopyFrom(*ptr);
}

Status_t UserIdentityTokenType_t::CopyFrom(const UserIdentityTokenType_t& source)
{
  Status_t status = OpcUa_BadOutOfRange;
  if(source.value < OPCUA_USER_IDENTITY_TOKEN_TYPE_ANONYMOUS || source.value > OPCUA_USER_IDENTITY_TOKEN_TYPE_END)
  {
    return status;
  }
  value = source.value;

  return OpcUa_Good;
}

Status_t UserIdentityTokenType_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Int32_t raw_val((int32_t)value);
  Status_t status = raw_val.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t UserIdentityTokenType_t::WriteIntToValue(int32_t newValue)
{
  if ((newValue < 0) || (newValue >= OPCUA_USER_IDENTITY_TOKEN_TYPE_END))
  {
	  UASDK_RETURN_BAD_STATUS(OpcUa_BadDecodingError);
  }
  else
  {
    value = static_cast<Enum_t>(newValue);
  }
  return OpcUa_Good;
}

UserIdentityTokenType_t::~UserIdentityTokenType_t()
{}

bool UserIdentityTokenType_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool UserIdentityTokenType_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t UserIdentityTokenType_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t UserIdentityTokenType_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

const UserIdentityTokenType_t::Enum_t& UserIdentityTokenType_t::Value(void) const
{
  return value;
}

UserIdentityTokenType_t::Enum_t& UserIdentityTokenType_t::Value(void)
{
  return value;
}

} // namespace uasdk
