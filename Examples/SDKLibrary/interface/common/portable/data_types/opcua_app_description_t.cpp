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

#include "opcua_app_description_t.h"
#include "opcua_extensible_parameter_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(AppDescription_t, Structure_t)

bool AppDescription_t::operator==(AppDescription_t const & obj) const
{
  return (
      (applicationUri == obj.applicationUri)
      && (productUri == obj.productUri)
      && (applicationName == obj.applicationName)
      && (applicationType == obj.applicationType)
      && (gatewayServerUri == obj.gatewayServerUri)
      && (discoveryProfileUri == obj.discoveryProfileUri)
      && (discoveryUrls == obj.discoveryUrls));
}

bool AppDescription_t::operator>(AppDescription_t const & obj) const
{
  return (
      (applicationUri > obj.applicationUri)
      && (productUri > obj.productUri)
      && (applicationName > obj.applicationName)
      && (applicationType > obj.applicationType)
      && (gatewayServerUri > obj.gatewayServerUri)
      && (discoveryProfileUri > obj.discoveryProfileUri)
      && (discoveryUrls > obj.discoveryUrls));
}

Status_t AppDescription_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

Status_t AppDescription_t::CopyFrom(const AppDescription_t& source)
{
  Status_t status = applicationUri.CopyFrom(source.applicationUri);

  if (status.IsBad())
  {
    return status;
  }

  status = productUri.CopyFrom(source.productUri);
  if (status.IsBad())
  {
    return status;
  }

  status = applicationName.CopyFrom(source.applicationName);
  if (status.IsBad())
  {
    return status;
  }

  status = applicationType.CopyFrom(source.applicationType);
  if (status.IsBad())
  {
    return status;
  }

  status = gatewayServerUri.CopyFrom(source.gatewayServerUri);
  if (status.IsBad())
  {
    return status;
  }

  status = discoveryProfileUri.CopyFrom(source.discoveryProfileUri);
  if (status.IsBad())
  {
    return status;
  }

  status = discoveryUrls.CopyFrom(source.discoveryUrls);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t AppDescription_t::CopyFrom(const BaseDataType_t& source)
{
  const AppDescription_t* ptr = RuntimeCast<const AppDescription_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t AppDescription_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = applicationUri.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = productUri.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = applicationName.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = applicationType.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = gatewayServerUri.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = discoveryProfileUri.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = discoveryUrls.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t AppDescription_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, AppDescription_t& result)
{
  Status_t status = String_t::Decode(buffer, decoder, result.ApplicationUri());
  if (status.IsBad())
  {
    return status;
  }

  status = String_t::Decode(buffer, decoder, result.ProductUri());
  if (status.IsBad())
  {
    return status;
  }

  status = LocalizedText_t::Decode(buffer, decoder, result.ApplicationName());
  if (status.IsBad())
  {
    return status;
  }

  status = ApplicationType_t::Decode(buffer, decoder, result.ApplicationType());
  if (status.IsBad())
  {
    return status;
  }

  status = String_t::Decode(buffer, decoder, result.GatewayServerUri());
  if (status.IsBad())
  {
    return status;
  }

  status = String_t::Decode(buffer, decoder, result.DiscoveryProfileUri());
  if (status.IsBad())
  {
    return status;
  }

  status = ArrayUA_t<String_t>::Decode(buffer, decoder, result.DiscoveryUrls());
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

AppDescription_t::~AppDescription_t()
{}

bool AppDescription_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool AppDescription_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

uint32_t AppDescription_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t AppDescription_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_ApplicationDescription_Encoding_DefaultBinary;
}

const String_t& AppDescription_t::ApplicationUri(void) const 
{
  return applicationUri; 
}

String_t& AppDescription_t::ApplicationUri(void) 
{ 
  return applicationUri; 
}

const String_t& AppDescription_t::ProductUri(void) const
{ 
  return productUri; 
}

String_t& AppDescription_t::ProductUri(void) 
{
  return productUri; 
}

const LocalizedText_t& AppDescription_t::ApplicationName(void) const 
{ 
  return applicationName; 
}

LocalizedText_t& AppDescription_t::ApplicationName(void) 
{ 
  return applicationName; 
}

const ApplicationType_t& AppDescription_t::ApplicationType(void) const 
{
  return applicationType; 
}

ApplicationType_t& AppDescription_t::ApplicationType(void)
{
  return applicationType; 
}

const String_t& AppDescription_t::GatewayServerUri(void) const
{
  return gatewayServerUri; 
}

String_t& AppDescription_t::GatewayServerUri(void) 
{ 
  return gatewayServerUri; 
}

const String_t& AppDescription_t::DiscoveryProfileUri(void) const 
{
  return discoveryProfileUri; 
}

String_t& AppDescription_t::DiscoveryProfileUri(void) 
{ 
  return discoveryProfileUri; 
}

const ArrayUA_t<String_t>& AppDescription_t::DiscoveryUrls(void) const
{
  return discoveryUrls; 
}

ArrayUA_t<String_t>& AppDescription_t::DiscoveryUrls(void) 
{ 
  return discoveryUrls; 
}

} // namespace uasdk
