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

#include "opcua_username_identity_token_t.h"
#include "opcua_identifiers.h"
#include "ibuffer_t.h"
#include "opcua_datatype_utilities_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(UsernameIdentityToken_t, Structure_t)

UsernameIdentityToken_t::UsernameIdentityToken_t()
{
}

bool UsernameIdentityToken_t::operator==(UsernameIdentityToken_t const & obj) const
{
  return (
      (policyId == obj.policyId)
      && (username == obj.username)
      && (password == obj.password)
      && (encryptionAlgorithm == obj.encryptionAlgorithm));
}

bool UsernameIdentityToken_t::operator>(UsernameIdentityToken_t const & obj) const
{
  return (
      (policyId > obj.policyId)
      && (username > obj.username)
      && (password > obj.password)
      && (encryptionAlgorithm > obj.encryptionAlgorithm));
}

Status_t UsernameIdentityToken_t::CopyFrom(const BaseDataType_t& source)
{
  const UsernameIdentityToken_t* ptr = RuntimeCast<const UsernameIdentityToken_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t UsernameIdentityToken_t::CopyFrom(const UsernameIdentityToken_t& source)
{
  Status_t status = policyId.CopyFrom(source.policyId);
  if (status.IsBad())
  {
    return status;
  }

  status = username.CopyFrom(source.username);
  if (status.IsBad())
  {
    return status;
  }

  status = password.CopyFrom(source.password);
  if (status.IsBad())
  {
    return status;
  }

  status = encryptionAlgorithm.CopyFrom(source.encryptionAlgorithm);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t UsernameIdentityToken_t::CopyFrom(const UsernameIdentityToken_t& source, const String_t& indexRange)
{
  UASDK_UNUSED(indexRange);
  return CopyFrom(source);
}

Status_t UsernameIdentityToken_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = policyId.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = username.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = password.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = encryptionAlgorithm.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t UsernameIdentityToken_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, UsernameIdentityToken_t& result)
{
  Status_t status = String_t::Decode(buffer, decoder, result.PolicyId());
  if (status.IsBad())
  {
    return status;
  }

  status = String_t::Decode(buffer, decoder, result.Username());
  if (status.IsBad())
  {
    return status;
  }

  status = ByteString_t::Decode(buffer, decoder, result.Password());
  if (status.IsBad())
  {
    return status;
  }

  status = String_t::Decode(buffer, decoder, result.EncryptionAlgorithm());
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

UsernameIdentityToken_t::~UsernameIdentityToken_t()
{}

bool UsernameIdentityToken_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool UsernameIdentityToken_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t UsernameIdentityToken_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t UsernameIdentityToken_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t UsernameIdentityToken_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_UserNameIdentityToken_Encoding_DefaultBinary;
}

const String_t& UsernameIdentityToken_t::PolicyId(void) const
{
  return policyId;
}

String_t& UsernameIdentityToken_t::PolicyId(void)
{
  return policyId;
}

const String_t& UsernameIdentityToken_t::Username(void) const
{
  return username;
}

String_t& UsernameIdentityToken_t::Username(void)
{
  return username;
}

const ByteString_t& UsernameIdentityToken_t::Password(void) const
{
  return password;
}

ByteString_t& UsernameIdentityToken_t::Password(void)
{
  return password;
}

const String_t& UsernameIdentityToken_t::EncryptionAlgorithm(void) const
{
  return encryptionAlgorithm;
}

String_t& UsernameIdentityToken_t::EncryptionAlgorithm(void)
{
  return encryptionAlgorithm;
}

} // namespace uasdk
