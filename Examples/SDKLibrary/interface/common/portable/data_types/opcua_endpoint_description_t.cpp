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

#include "opcua_endpoint_description_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(EndpointDescription_t, Structure_t)

EndpointDescription_t::EndpointDescription_t() : securityLevel(0)
{
}

bool EndpointDescription_t::operator==(EndpointDescription_t const & obj) const
{
  return (
      (endpointUrl == obj.endpointUrl)
      && (applicationDescription == obj.applicationDescription)
      && (serverCertificate == obj.serverCertificate)
      && (securityMode == obj.securityMode)
      && (securityPolicyUri == obj.securityPolicyUri)
      && (userIdentityTokens == obj.userIdentityTokens)
      && (transportProfileUri == obj.transportProfileUri)
      && (securityLevel == obj.securityLevel));
}

bool EndpointDescription_t::operator>(EndpointDescription_t const & obj) const
{
  return (
      (endpointUrl > obj.endpointUrl)
      && (applicationDescription > obj.applicationDescription)
      && (serverCertificate > obj.serverCertificate)
      && (securityMode > obj.securityMode)
      && (securityPolicyUri > obj.securityPolicyUri)
      && (userIdentityTokens > obj.userIdentityTokens)
      && (transportProfileUri > obj.transportProfileUri)
      && (securityLevel > obj.securityLevel));
}

Status_t EndpointDescription_t::CopyFrom(const EndpointDescription_t& source)
{
  Status_t status = endpointUrl.CopyFrom(source.endpointUrl);

  if (status.IsBad())
  {
    return status;
  }

  status = applicationDescription.CopyFrom(source.applicationDescription);
  if (status.IsBad())
  {
    return status;
  }

  status = serverCertificate.CopyFrom(source.serverCertificate);
  if (status.IsBad())
  {
    return status;
  }

  status = securityMode.CopyFrom(source.securityMode);
  if (status.IsBad())
  {
    return status;
  }

  status = securityPolicyUri.CopyFrom(source.securityPolicyUri);
  if (status.IsBad())
  {
    return status;
  }

  status = userIdentityTokens.CopyFrom(source.userIdentityTokens);
  if (status.IsBad())
  {
    return status;
  }

  status = transportProfileUri.CopyFrom(source.transportProfileUri);
  if (status.IsBad())
  {
    return status;
  }

  status = securityLevel.CopyFrom(source.securityLevel);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t EndpointDescription_t::CopyFrom(const BaseDataType_t& source)
{
  const EndpointDescription_t* ptr = RuntimeCast<const EndpointDescription_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t EndpointDescription_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = endpointUrl.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = applicationDescription.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = serverCertificate.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = securityMode.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = securityPolicyUri.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = userIdentityTokens.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = transportProfileUri.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = securityLevel.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return 0;
}

Status_t EndpointDescription_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, EndpointDescription_t& result)
{
  Status_t status = String_t::Decode(buffer, decoder, result.EndpointUrl());
  if (status.IsBad())
  {
    return status;
  }

  status = AppDescription_t::Decode(buffer, decoder, result.ApplicationDescription());
  if (status.IsBad())
  {
    return status;
  }

  status = ByteString_t::Decode(buffer, decoder, result.ServerCertificate());
  if (status.IsBad())
  {
    return status;
  }

  status = MessageSecurityMode_t::Decode(buffer, decoder, result.SecurityMode());
  if (status.IsBad())
  {
    return status;
  }

  status = String_t::Decode(buffer, decoder, result.SecurityPolicyUri());
  if (status.IsBad())
  {
    return status;
  }

  status = ArrayUA_t<UserTokenPolicy_t>::Decode(buffer, decoder, result.UserIdentityTokens());
  if (status.IsBad())
  {
    return status;
  }

  status = String_t::Decode(buffer, decoder, result.TransportProfileUri());
  if (status.IsBad())
  {
    return status;
  }

  status = Byte_t::Decode(buffer, decoder, result.SecurityLevel());
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

EndpointDescription_t::~EndpointDescription_t()
{}

bool EndpointDescription_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool EndpointDescription_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t EndpointDescription_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t EndpointDescription_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t EndpointDescription_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_EndpointDescription_Encoding_DefaultBinary;
}

const String_t& EndpointDescription_t::EndpointUrl(void) const
{
  return endpointUrl;
}

String_t& EndpointDescription_t::EndpointUrl(void)
{
  return endpointUrl;
}

const AppDescription_t& EndpointDescription_t::ApplicationDescription(void) const
{
  return applicationDescription;
}

AppDescription_t& EndpointDescription_t::ApplicationDescription(void)
{
  return applicationDescription;
}

const ByteString_t& EndpointDescription_t::ServerCertificate(void) const
{
  return serverCertificate;
}

ByteString_t& EndpointDescription_t::ServerCertificate(void)
{
  return serverCertificate;
}

const MessageSecurityMode_t& EndpointDescription_t::SecurityMode(void) const
{
  return securityMode;
}

MessageSecurityMode_t& EndpointDescription_t::SecurityMode(void)
{
  return securityMode;
}

const String_t& EndpointDescription_t::SecurityPolicyUri(void) const
{
  return securityPolicyUri;
}

String_t& EndpointDescription_t::SecurityPolicyUri(void)
{
  return securityPolicyUri;
}

const ArrayUA_t<UserTokenPolicy_t>& EndpointDescription_t::UserIdentityTokens(void) const
{
  return userIdentityTokens;
}

ArrayUA_t<UserTokenPolicy_t>& EndpointDescription_t::UserIdentityTokens(void)
{
  return userIdentityTokens;
}

const String_t& EndpointDescription_t::TransportProfileUri(void) const
{
  return transportProfileUri;
}

String_t& EndpointDescription_t::TransportProfileUri(void)
{
  return transportProfileUri;
}

const Byte_t& EndpointDescription_t::SecurityLevel(void) const
{
  return securityLevel;
}

Byte_t& EndpointDescription_t::SecurityLevel(void)
{
  return securityLevel;
}

} // namespace uasdk
