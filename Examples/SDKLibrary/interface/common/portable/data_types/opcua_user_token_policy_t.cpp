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

#include "opcua_user_token_policy_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(UserTokenPolicy_t, Structure_t);

UserTokenPolicy_t::UserTokenPolicy_t()
{
}

bool UserTokenPolicy_t::operator==(UserTokenPolicy_t const & obj) const
{
  return (
      (policyId == obj.policyId)
      && (tokenType == obj.tokenType)
      && (issuedTokenType == obj.issuedTokenType)
      && (issuerEndpointUrl == obj.issuerEndpointUrl)
      && (securityPolicyUri == obj.securityPolicyUri));
}

bool UserTokenPolicy_t::operator>(UserTokenPolicy_t const & obj) const
{
  return (
      (policyId > obj.policyId)
      && (tokenType > obj.tokenType)
      && (issuedTokenType > obj.issuedTokenType)
      && (issuerEndpointUrl > obj.issuerEndpointUrl)
      && (securityPolicyUri > obj.securityPolicyUri));
}

Status_t UserTokenPolicy_t::CopyFrom(const BaseDataType_t& source)
{
  const UserTokenPolicy_t* ptr = RuntimeCast<const UserTokenPolicy_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t UserTokenPolicy_t::CopyFrom(const UserTokenPolicy_t& source)
{
  Status_t status = policyId.CopyFrom(source.policyId);
  if (status.IsBad())
  {
    return status;
  }

  status = tokenType.CopyFrom(source.tokenType);
  if (status.IsBad())
  {
    return status;
  }

  status = issuedTokenType.CopyFrom(source.issuedTokenType);
  if (status.IsBad())
  {
    return status;
  }

  status = issuerEndpointUrl.CopyFrom(source.issuerEndpointUrl);
  if (status.IsBad())
  {
    return status;
  }

  status = securityPolicyUri.CopyFrom(source.securityPolicyUri);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t UserTokenPolicy_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = policyId.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = tokenType.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = issuedTokenType.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = issuerEndpointUrl.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = securityPolicyUri.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t UserTokenPolicy_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, UserTokenPolicy_t& result)
{
  Status_t status = String_t::Decode(buffer, decoder, result.PolicyId());
  if (status.IsBad())
  {
    return status;
  }

  status = UserIdentityTokenType_t::Decode(buffer, decoder, result.TokenType());
  if (status.IsBad())
  {
    return status;
  }

  status = String_t::Decode(buffer, decoder, result.IssuedTokenType());
  if (status.IsBad())
  {
    return status;
  }

  status = String_t::Decode(buffer, decoder, result.IssuerEndpointUrl());
  if (status.IsBad())
  {
    return status;
  }

  status = String_t::Decode(buffer, decoder, result.SecurityPolicyUri());
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

UserTokenPolicy_t::~UserTokenPolicy_t() 
{}

bool UserTokenPolicy_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool UserTokenPolicy_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t UserTokenPolicy_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t UserTokenPolicy_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t UserTokenPolicy_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_UserTokenPolicy_Encoding_DefaultBinary;
}

const String_t& UserTokenPolicy_t::PolicyId(void) const
{
  return policyId;
}

String_t& UserTokenPolicy_t::PolicyId(void)
{
  return policyId;
}

const UserIdentityTokenType_t& UserTokenPolicy_t::TokenType(void) const
{
  return tokenType;
}

UserIdentityTokenType_t& UserTokenPolicy_t::TokenType(void)
{
  return tokenType;
}

const String_t& UserTokenPolicy_t::IssuedTokenType(void) const
{
  return issuedTokenType;
}

String_t& UserTokenPolicy_t::IssuedTokenType(void)
{
  return issuedTokenType;
}

const String_t& UserTokenPolicy_t::IssuerEndpointUrl(void) const
{
  return issuerEndpointUrl;
}

String_t& UserTokenPolicy_t::IssuerEndpointUrl(void)
{
  return issuerEndpointUrl;
}

const String_t& UserTokenPolicy_t::SecurityPolicyUri(void) const
{
  return securityPolicyUri;
}

String_t& UserTokenPolicy_t::SecurityPolicyUri(void)
{
  return securityPolicyUri;
}

} // namespace uasdk
