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

#include "opcua_redundancy_support_t.h"
#include "opcua_int32_t.h"
#include "opcua_datatype_utilities_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(RedundancySupport_t, Enumeration_t)

RedundancySupport_t::RedundancySupport_t(void) : value(OPCUA_REDUNDANCY_SUPPORT_NONE_0)
{
}

RedundancySupport_t::RedundancySupport_t(Enum_t value_)
{
  value = value_;
}

RedundancySupport_t::~RedundancySupport_t(void)
{
}

bool RedundancySupport_t::operator==(RedundancySupport_t const & obj) const
{
  return value == obj.value;
}

bool RedundancySupport_t::operator>(RedundancySupport_t const & obj) const
{
  if ( (obj.value < 0) || (obj.value > OPCUA_REDUNDANCY_SUPPORT_END))
  {
    return false;
  }

  return (value > obj.value);
}

Status_t RedundancySupport_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

Status_t RedundancySupport_t::CopyFrom(const RedundancySupport_t& source)
{
  Status_t status;

  if ( (source.value < 0) || (source.value > OPCUA_REDUNDANCY_SUPPORT_END))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfRange);
  }

  value = source.value;

  return OpcUa_Good;
}

Status_t RedundancySupport_t::CopyFrom(const BaseDataType_t& source)
{
  const RedundancySupport_t* ptr = RuntimeCast<const RedundancySupport_t *>(source);
  if(!ptr)
  {
    return TryCopyFromInt32(source);
  }

  return CopyFrom(*ptr);
}

Status_t RedundancySupport_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Int32_t raw_val((int32_t)value);
  Status_t status = raw_val.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t RedundancySupport_t::WriteIntToValue(int32_t newValue)
{
  if ((newValue < 0) || (newValue >= OPCUA_REDUNDANCY_SUPPORT_END))
  {
	  UASDK_RETURN_BAD_STATUS(OpcUa_BadDecodingError);
  }
  else
  {
    value = static_cast<Enum_t>(newValue);
  }
  return OpcUa_Good;
}

bool RedundancySupport_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool RedundancySupport_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

uint32_t RedundancySupport_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

const RedundancySupport_t::Enum_t& RedundancySupport_t::Value(void) const
{
  return value;
}

RedundancySupport_t::Enum_t& RedundancySupport_t::Value(void)
{
  return value;
}

} //namespace uasdk;
