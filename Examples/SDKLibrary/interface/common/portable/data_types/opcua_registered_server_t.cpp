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

#include "opcua_registered_server_t.h"

#if (UASDK_INCLUDE_ADDITIONAL_DISCOVERY_SERVICES > 0)

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(RegisteredServer_t, Structure_t)

bool RegisteredServer_t::operator==(RegisteredServer_t const & obj) const
{
  return (
      (serverUri == obj.serverUri)
      && (productUri == obj.productUri)
      && (serverNames == obj.serverNames)
      && (serverType == obj.serverType)
      && (gatewayServerUri == obj.gatewayServerUri)
      && (discoveryUrls == obj.discoveryUrls)
      && (semaphoreFilePath == obj.semaphoreFilePath)
	  && (isOnline == obj.isOnline));
}

bool RegisteredServer_t::operator>(RegisteredServer_t const & obj) const
{
	return (
		(serverUri > obj.serverUri)
		&& (productUri > obj.productUri)
		&& (serverNames > obj.serverNames)
		&& (serverType > obj.serverType)
		&& (gatewayServerUri > obj.gatewayServerUri)
		&& (discoveryUrls > obj.discoveryUrls)
		&& (semaphoreFilePath > obj.semaphoreFilePath)
		&& (isOnline > obj.isOnline));
}

Status_t RegisteredServer_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

Status_t RegisteredServer_t::CopyFrom(const RegisteredServer_t& source)
{
  Status_t status = serverUri.CopyFrom(source.serverUri);

  if (status.IsBad())
  {
    return status;
  }

  status = productUri.CopyFrom(source.productUri);
  if (status.IsBad())
  {
    return status;
  }

  status = serverNames.CopyFrom(source.serverNames);
  if (status.IsBad())
  {
    return status;
  }

  status = serverType.CopyFrom(source.serverType);
  if (status.IsBad())
  {
    return status;
  }

  status = gatewayServerUri.CopyFrom(source.gatewayServerUri);
  if (status.IsBad())
  {
    return status;
  }

  status = discoveryUrls.CopyFrom(source.discoveryUrls);
  if (status.IsBad())
  {
    return status;
  }

  status = semaphoreFilePath.CopyFrom(source.semaphoreFilePath);
  if (status.IsBad())
  {
	  return status;
  }

  status = isOnline.CopyFrom(source.isOnline);
  if (status.IsBad())
  {
	  return status;
  }

  return status;
}

Status_t RegisteredServer_t::CopyFrom(const BaseDataType_t& source)
{
  const RegisteredServer_t* ptr = RuntimeCast<const RegisteredServer_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t RegisteredServer_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = serverUri.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = productUri.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = serverNames.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = serverType.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = gatewayServerUri.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = discoveryUrls.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = semaphoreFilePath.Encode(encoder, buffer);
  if (status.IsBad())
  {
	  return status;
  }

  status = isOnline.Encode(encoder, buffer);
  if (status.IsBad())
  {
	  return status;
  }

  return status;
}

Status_t RegisteredServer_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, RegisteredServer_t& result)
{
  Status_t status = String_t::Decode(buffer, decoder, result.ServerUri());
  if (status.IsBad()) 
  {
    return status;
  }

  status = String_t::Decode(buffer, decoder, result.ProductUri());
  if (status.IsBad())
  {
    return status;
  }

  status = ArrayUA_t<LocalizedText_t>::Decode(buffer, decoder, result.ServerNames());
  if (status.IsBad())
  {
    return status;
  }

  status = ApplicationType_t::Decode(buffer, decoder, result.ServerType());
  if (status.IsBad())
  {
    return status;
  }

  status = String_t::Decode(buffer, decoder, result.GatewayServerUri());
  if (status.IsBad())
  {
    return status;
  }

  status = ArrayUA_t<String_t>::Decode(buffer, decoder, result.DiscoveryUrls());
  if (status.IsBad())
  {
    return status;
  }

  status = String_t::Decode(buffer, decoder, result.SemaphoreFilePath());
  if (status.IsBad())
  {
	  return status;
  }

  status = Boolean_t::Decode(buffer, decoder, result.IsOnline());
  if (status.IsBad())
  {
	  return status;
  }

  return status;
}

RegisteredServer_t::~RegisteredServer_t()
{}

bool RegisteredServer_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool RegisteredServer_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

uint32_t RegisteredServer_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t RegisteredServer_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_RegisteredServer_Encoding_DefaultBinary;
}

const String_t& RegisteredServer_t::ServerUri(void) const
{
  return serverUri; 
}

String_t& RegisteredServer_t::ServerUri(void)
{ 
  return serverUri;
}

const String_t& RegisteredServer_t::ProductUri(void) const
{ 
  return productUri; 
}

String_t& RegisteredServer_t::ProductUri(void)
{
  return productUri; 
}

const  ArrayUA_t<LocalizedText_t>& RegisteredServer_t::ServerNames(void) const
{ 
  return serverNames;
}

ArrayUA_t<LocalizedText_t>& RegisteredServer_t::ServerNames(void)
{ 
  return serverNames;
}

const ApplicationType_t& RegisteredServer_t::ServerType(void) const
{
  return serverType; 
}

ApplicationType_t& RegisteredServer_t::ServerType(void)
{
  return serverType;
}

const String_t& RegisteredServer_t::GatewayServerUri(void) const
{
  return gatewayServerUri; 
}

String_t& RegisteredServer_t::GatewayServerUri(void)
{ 
  return gatewayServerUri; 
}

const ArrayUA_t<String_t>& RegisteredServer_t::DiscoveryUrls(void) const
{
  return discoveryUrls; 
}

ArrayUA_t<String_t>& RegisteredServer_t::DiscoveryUrls(void)
{ 
  return discoveryUrls; 
}

const String_t& RegisteredServer_t::SemaphoreFilePath(void) const
{
	return semaphoreFilePath;
}

String_t& RegisteredServer_t::SemaphoreFilePath(void)
{
	return semaphoreFilePath;
}

const Boolean_t& RegisteredServer_t::IsOnline(void) const
{
	return isOnline;
}

Boolean_t& RegisteredServer_t::IsOnline(void)
{
	return isOnline;
}

} // namespace uasdk

#endif
