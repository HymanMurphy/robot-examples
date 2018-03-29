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

#include "opcua_message_security_mode_t.h"
#include "opcua_int32_t.h"
#include "opcua_datatype_utilities_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(MessageSecurityMode_t, Enumeration_t)

MessageSecurityMode_t::MessageSecurityMode_t(void) : value(OPCUA_MESSAGE_SECURITY_MODE_INVALID)
{
}

MessageSecurityMode_t::MessageSecurityMode_t(Enum_t value_)
{
  this->value = value_;
}

bool MessageSecurityMode_t::operator==(MessageSecurityMode_t const & obj) const
{
  return value == obj.value;
}

bool MessageSecurityMode_t::operator>(MessageSecurityMode_t const & obj) const
{
  return value > obj.value;
}

Status_t MessageSecurityMode_t::CopyFrom(const MessageSecurityMode_t& source)
{
  Status_t status = OpcUa_BadOutOfRange;

  if ( (source.value < 0) || (source.value > OPCUA_MESSAGE_SECURITY_MODE_END) )
  {
    return status;
  }

  value = source.value;

  return OpcUa_Good;
}

Status_t MessageSecurityMode_t::CopyFrom(const BaseDataType_t& source)
{
  const MessageSecurityMode_t* ptr = RuntimeCast<const MessageSecurityMode_t *>(source);
  if(!ptr)
  {
    return TryCopyFromInt32(source);
  }

  return CopyFrom(*ptr);
}

Status_t MessageSecurityMode_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Int32_t raw_val((int32_t)this->value);
  Status_t status = raw_val.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return 0;
}

Status_t MessageSecurityMode_t::WriteIntToValue(int32_t newValue)
{
  if ((newValue < 0) || (newValue >= OPCUA_MESSAGE_SECURITY_MODE_END))
  {
	  UASDK_RETURN_BAD_STATUS(OpcUa_BadDecodingError);
  }
  else
  {
    value = static_cast<Enum_t>(newValue);
  }
  return OpcUa_Good;
}

MessageSecurityMode_t::~MessageSecurityMode_t()
{}

bool MessageSecurityMode_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool MessageSecurityMode_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t MessageSecurityMode_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t MessageSecurityMode_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

const MessageSecurityMode_t::Enum_t& MessageSecurityMode_t::Value(void) const
{
  return value;
}

MessageSecurityMode_t::Enum_t& MessageSecurityMode_t::Value(void)
{
  return value;
}

} // namespace uasdk
