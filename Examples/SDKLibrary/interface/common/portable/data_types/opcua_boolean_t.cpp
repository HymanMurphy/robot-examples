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

#include "opcua_boolean_t.h"
#include "opcua_datatype_utilities_t.h"
#include "icodec_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(Boolean_t, BaseDataType_t)

Boolean_t::Boolean_t() 
  : value(false) 
{}

Boolean_t::Boolean_t(bool value_)
{
  value = value_;
}

Boolean_t::Boolean_t(const Boolean_t& other)
  : BaseDataType_t()
{
  value = other.value;
}

Boolean_t::~Boolean_t()
{}

Boolean_t& Boolean_t::operator =(const Boolean_t& obj)
{
  value = obj.value;
  return *this;
}

bool Boolean_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool Boolean_t::operator==(Boolean_t const & obj) const
{
  return value == obj.value;
}

bool Boolean_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

bool Boolean_t::operator>(Boolean_t const & obj) const
{
  return value > obj.value;
}

Status_t Boolean_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

Status_t Boolean_t::CopyFrom(const Boolean_t& source)
{
  value = source.value;
  return OpcUa_Good;
}

Status_t Boolean_t::CopyFrom(const BaseDataType_t& source)
{
  const Boolean_t* ptr = RuntimeCast<const Boolean_t *>(source);
  if (!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

uint32_t Boolean_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

bool Boolean_t::Value(void) const
{
  return (value != 0);
}

Status_t Boolean_t::Value(bool val)
{
  value = (uint8_t)val;

  return OpcUa_Good;
}

Status_t Boolean_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  return encoder.Encode(*this, buffer);
}

Status_t Boolean_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, Boolean_t& result)
{
  return decoder.Decode(buffer, result);
}

}
