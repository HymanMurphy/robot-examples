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

#include "opcua_eu_information_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(EUInformation_t, Structure_t)

bool EUInformation_t::operator==(EUInformation_t const & obj) const
{
  return (
      (namespaceUri == obj.namespaceUri)
      && (unitId == obj.unitId)
      && (displayName == obj.displayName)
      && (description == obj.description));
}

bool EUInformation_t::operator>(EUInformation_t const & obj) const
{
  return (
      (namespaceUri > obj.namespaceUri)
      && (unitId > obj.unitId)
      && (displayName > obj.displayName)
      && (description > obj.description));
}

Status_t EUInformation_t::CopyFrom(const EUInformation_t& source)
{
  Status_t status = namespaceUri.CopyFrom(source.namespaceUri);

  if (status.IsBad())
  {
    return status;
  }

  status = unitId.CopyFrom(source.unitId);
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

Status_t EUInformation_t::CopyFrom(const BaseDataType_t& source)
{
  const EUInformation_t* ptr = RuntimeCast<const EUInformation_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t EUInformation_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = namespaceUri.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = unitId.Encode(encoder, buffer);
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

Status_t EUInformation_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, EUInformation_t& result)
{
  Status_t status = String_t::Decode(buffer, decoder, result.NamespaceUri());
  if (status.IsBad())
  {
    return status;
  }

  status = Int32_t::Decode(buffer, decoder, result.UnitId());
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

EUInformation_t::EUInformation_t()
{}

EUInformation_t::~EUInformation_t()
{}

bool EUInformation_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool EUInformation_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t EUInformation_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t EUInformation_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t EUInformation_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_EUInformation_Encoding_DefaultBinary;
}

const String_t& EUInformation_t::NamespaceUri(void) const
{
  return namespaceUri;
}

String_t& EUInformation_t::NamespaceUri(void)
{
  return namespaceUri;
}

const Int32_t& EUInformation_t::UnitId(void) const
{
  return unitId;
}

Int32_t& EUInformation_t::UnitId(void)
{
  return unitId;
}

const LocalizedText_t& EUInformation_t::DisplayName(void) const
{
  return displayName;
}

LocalizedText_t& EUInformation_t::DisplayName(void)
{
  return displayName;
}

const LocalizedText_t& EUInformation_t::Description(void) const
{
  return description;
}

LocalizedText_t& EUInformation_t::Description(void)
{
  return description;
}

} // namespace uasdk
