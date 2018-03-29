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

#include "opcua_axis_scale_enumeration_t.h"
#include "opcua_int32_t.h"

#if (UASDK_INCLUDE_ADDITIONAL_DA_TYPES > 0)

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(AxisScaleEnumeration_t, Enumeration_t)

AxisScaleEnumeration_t::AxisScaleEnumeration_t(void) : value(OPCUA_AXIS_SCALE_ENUMERATION_LINEAR_0)
{
}

AxisScaleEnumeration_t::AxisScaleEnumeration_t(Enum_t value_)
{
  value = value_;
}

AxisScaleEnumeration_t::~AxisScaleEnumeration_t(void)
{
}

bool AxisScaleEnumeration_t::operator==(AxisScaleEnumeration_t const & obj) const
{
  return value == obj.value;
}

bool AxisScaleEnumeration_t::operator>(AxisScaleEnumeration_t const & obj) const
{
  if ( (obj.value < 0) || (obj.value > OPCUA_AXIS_SCALE_ENUMERATION_END))
  {
    return false;
  }

  return (value > obj.value);
}

Status_t AxisScaleEnumeration_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

Status_t AxisScaleEnumeration_t::CopyFrom(const AxisScaleEnumeration_t& source)
{
  Status_t status;

  if ( (source.value < 0) || (source.value > OPCUA_AXIS_SCALE_ENUMERATION_END))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfRange);
  }

  value = source.value;

  return OpcUa_Good;
}

Status_t AxisScaleEnumeration_t::CopyFrom(const BaseDataType_t& source)
{
  const AxisScaleEnumeration_t* ptr = RuntimeCast<const AxisScaleEnumeration_t *>(source);
  if(!ptr)
  {
    return TryCopyFromInt32(source);
  }

  return CopyFrom(*ptr);
}

Status_t AxisScaleEnumeration_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Int32_t raw_val((int32_t)value);
  Status_t status = raw_val.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t AxisScaleEnumeration_t::WriteIntToValue(int32_t newValue)
{
  if ((newValue < 0) || (newValue >= OPCUA_AXIS_SCALE_ENUMERATION_END))
  {
	  UASDK_RETURN_BAD_STATUS(OpcUa_BadDecodingError);
  }
  else
  {
    value = static_cast<Enum_t>(newValue);
  }
  return OpcUa_Good;
}

bool AxisScaleEnumeration_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool AxisScaleEnumeration_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

uint32_t AxisScaleEnumeration_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

const AxisScaleEnumeration_t::Enum_t& AxisScaleEnumeration_t::Value(void) const
{
  return value;
}

AxisScaleEnumeration_t::Enum_t& AxisScaleEnumeration_t::Value(void)
{
  return value;
}

} //namespace uasdk

#endif
