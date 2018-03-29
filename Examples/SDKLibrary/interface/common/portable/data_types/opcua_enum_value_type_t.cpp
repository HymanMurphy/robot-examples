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

#include "opcua_enum_value_type_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(EnumValueType_t, Structure_t)

bool EnumValueType_t::operator==(EnumValueType_t const & obj) const
{
  return (
      (value == obj.value)
      && (displayName == obj.displayName)
      && (description == obj.description));
}

bool EnumValueType_t::operator>(EnumValueType_t const & obj) const
{
  return (
      (value > obj.value)
      && (displayName > obj.displayName)
      && (description > obj.description));
}

Status_t EnumValueType_t::CopyFrom(const EnumValueType_t& source)
{
  Status_t status = value.CopyFrom(source.value);

  if (status.IsBad())
  {
    return status;
  }

  status = displayName.CopyFrom(source.displayName);
  if (status.IsBad())
  {
    return status;
  }

  status = description.CopyFrom(source.description);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t EnumValueType_t::CopyFrom(const BaseDataType_t& source)
{
  const EnumValueType_t* ptr = RuntimeCast<const EnumValueType_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t EnumValueType_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = value.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = displayName.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = description.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t EnumValueType_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, EnumValueType_t& result)
{
  Status_t status = Int64_t::Decode(buffer, decoder, result.Value());
  if (status.IsBad())
  {
    return status;
  }

  status = LocalizedText_t::Decode(buffer, decoder, result.DisplayName());
  if (status.IsBad())
  {
    return status;
  }

  status = LocalizedText_t::Decode(buffer, decoder, result.Description());
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

EnumValueType_t::EnumValueType_t()
{}

EnumValueType_t::~EnumValueType_t() 
{}

bool EnumValueType_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool EnumValueType_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t EnumValueType_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t EnumValueType_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t EnumValueType_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_EnumValueType_Encoding_DefaultBinary;
}

const Int64_t& EnumValueType_t::Value(void) const
{
  return value;
}

Int64_t& EnumValueType_t::Value(void)
{
  return value;
}

const LocalizedText_t& EnumValueType_t::DisplayName(void) const
{
  return displayName;
}

LocalizedText_t& EnumValueType_t::DisplayName(void)
{
  return displayName;
}

const LocalizedText_t& EnumValueType_t::Description(void) const
{
  return description;
}

LocalizedText_t& EnumValueType_t::Description(void)
{
  return description;
}

} // namespace uasdk
