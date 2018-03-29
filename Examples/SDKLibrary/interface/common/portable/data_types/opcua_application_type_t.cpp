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

#include "opcua_application_type_t.h"
#include "opcua_int32_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(ApplicationType_t, Enumeration_t)

ApplicationType_t::ApplicationType_t(void) : value(OPCUA_APPLICATION_TYPE_SERVER)
{
}

ApplicationType_t::ApplicationType_t(Enum_t value_)
{
  value = value_;
}

ApplicationType_t::~ApplicationType_t(void)
{
}

bool ApplicationType_t::operator==(ApplicationType_t const & obj) const
{
  return value == obj.value;
}

bool ApplicationType_t::operator>(ApplicationType_t const & obj) const
{
  if ( (obj.value < 0) || (obj.value > OPCUA_APPLICATION_TYPE_END))
  {
    return false;
  }

  return (value > obj.value);
}

Status_t ApplicationType_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

Status_t ApplicationType_t::CopyFrom(const ApplicationType_t& source)
{
  Status_t status;

  if ( (source.value < 0) || (source.value > OPCUA_APPLICATION_TYPE_END))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfRange);
  }

  value = source.value;

  return OpcUa_Good;
}

Status_t ApplicationType_t::CopyFrom(const BaseDataType_t& source)
{
  const ApplicationType_t* ptr = RuntimeCast<const ApplicationType_t *>(source);
  if(!ptr)
  {
    return TryCopyFromInt32(source);
  }

  return CopyFrom(*ptr);
}

Status_t ApplicationType_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Int32_t raw_val((int32_t)value);
  Status_t status = raw_val.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t ApplicationType_t::WriteIntToValue(int32_t newValue)
{
  if ((newValue < 0) || (newValue >= OPCUA_APPLICATION_TYPE_END))
  {
	  UASDK_RETURN_BAD_STATUS(OpcUa_BadDecodingError);
  }
  else
  {
    value = static_cast<Enum_t>(newValue);
  }
  return OpcUa_Good;
}

bool ApplicationType_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool ApplicationType_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

uint32_t ApplicationType_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

const ApplicationType_t::Enum_t& ApplicationType_t::Value(void) const 
{
  return value; 
}

ApplicationType_t::Enum_t& ApplicationType_t::Value(void) 
{
  return value; 
}

} // namespace uasdk
