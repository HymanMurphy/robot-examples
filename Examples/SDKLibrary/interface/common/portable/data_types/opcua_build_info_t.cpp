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

#include "opcua_build_info_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(BuildInfo_t, Structure_t)

bool BuildInfo_t::operator==(BuildInfo_t const & obj) const
{
  return (
      (productUri == obj.productUri)
      && (manufacturerName == obj.manufacturerName)
      && (productName == obj.productName)
      && (softwareVersion == obj.softwareVersion)
      && (buildNumber == obj.buildNumber)
      && (buildDate == obj.buildDate));
}

bool BuildInfo_t::operator>(BuildInfo_t const & obj) const
{
  return (
      (productUri > obj.productUri)
      && (manufacturerName > obj.manufacturerName)
      && (productName > obj.productName)
      && (softwareVersion > obj.softwareVersion)
      && (buildNumber > obj.buildNumber)
      && (buildDate > obj.buildDate));
}

Status_t BuildInfo_t::CopyFrom(const BuildInfo_t& source)
{
  Status_t status = productUri.CopyFrom(source.productUri);

  if (status.IsBad())
  {
    return status;
  }

  status = manufacturerName.CopyFrom(source.manufacturerName);
  if (status.IsBad())
  {
    return status;
  }

  status = productName.CopyFrom(source.productName);
  if (status.IsBad())
  {
    return status;
  }

  status = softwareVersion.CopyFrom(source.softwareVersion);
  if (status.IsBad())
  {
    return status;
  }

  status = buildNumber.CopyFrom(source.buildNumber);
  if (status.IsBad())
  {
    return status;
  }

  status = buildDate.CopyFrom(source.buildDate);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t BuildInfo_t::CopyFrom(const BaseDataType_t& source)
{
  const BuildInfo_t* ptr = RuntimeCast<const BuildInfo_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t BuildInfo_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = productUri.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = manufacturerName.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = productName.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = softwareVersion.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = buildNumber.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = buildDate.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t BuildInfo_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, BuildInfo_t& result)
{
  Status_t status = String_t::Decode(buffer, decoder, result.ProductUri());
  if (status.IsBad())
  {
    return status;
  }

  status = String_t::Decode(buffer, decoder, result.ManufacturerName());
  if (status.IsBad())
  {
    return status;
  }

  status = String_t::Decode(buffer, decoder, result.ProductName());
  if (status.IsBad())
  {
    return status;
  }

  status = String_t::Decode(buffer, decoder, result.SoftwareVersion());
  if (status.IsBad())
  {
    return status;
  }

  status = String_t::Decode(buffer, decoder, result.BuildNumber());
  if (status.IsBad())
  {
    return status;
  }

  status = result.BuildDate().Decode(buffer, decoder, result.BuildDate());
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

BuildInfo_t::~BuildInfo_t() {}

bool BuildInfo_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool BuildInfo_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t BuildInfo_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t BuildInfo_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t BuildInfo_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_BuildInfo_Encoding_DefaultBinary;
}

const String_t& BuildInfo_t::ProductUri(void) const 
{
  return productUri; 
}

String_t& BuildInfo_t::ProductUri(void) 
{
  return productUri; 
}

const String_t& BuildInfo_t::ManufacturerName(void) const
{ 
  return manufacturerName; 
}

String_t& BuildInfo_t::ManufacturerName(void) 
{ 
  return manufacturerName; 
}

const String_t& BuildInfo_t::ProductName(void) const 
{
  return productName; 
}

String_t& BuildInfo_t::ProductName(void) 
{
  return productName; 
}

const String_t& BuildInfo_t::SoftwareVersion(void) const
{
  return softwareVersion; 
}

String_t& BuildInfo_t::SoftwareVersion(void)
{
  return softwareVersion; 
}

const String_t& BuildInfo_t::BuildNumber(void) const 
{
  return buildNumber; 
}

String_t& BuildInfo_t::BuildNumber(void) 
{
  return buildNumber; 
}

const UtcTime_t& BuildInfo_t::BuildDate(void) const 
{
  return buildDate; 
}

UtcTime_t& BuildInfo_t::BuildDate(void)
{
  return buildDate; 
}

} // namespace uasdk
