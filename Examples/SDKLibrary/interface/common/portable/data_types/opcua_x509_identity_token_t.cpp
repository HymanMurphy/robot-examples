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

#include "opcua_x509_identity_token_t.h"
#include "opcua_identifiers.h"
#include "ibuffer_t.h"
#include "opcua_datatype_utilities_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(X509IdentityToken_t, Structure_t)

X509IdentityToken_t::X509IdentityToken_t()
{
}

bool X509IdentityToken_t::operator==(X509IdentityToken_t const & obj) const
{
  return (
      (policyId == obj.policyId)
      && (certificateData == obj.certificateData));
}

bool X509IdentityToken_t::operator>(X509IdentityToken_t const & obj) const
{
  return (
      (policyId > obj.policyId)
      && (certificateData > obj.certificateData));
}

Status_t X509IdentityToken_t::CopyFrom(const BaseDataType_t& source)
{
  const X509IdentityToken_t* ptr = RuntimeCast<const X509IdentityToken_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t X509IdentityToken_t::CopyFrom(const X509IdentityToken_t& source)
{
  Status_t status = policyId.CopyFrom(source.policyId);
  if (status.IsBad())
  {
    return status;
  }

  status = certificateData.CopyFrom(source.certificateData);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t X509IdentityToken_t::CopyFrom(const X509IdentityToken_t& source, const String_t& indexRange)
{
  UASDK_UNUSED(indexRange);
  return CopyFrom(source);
}

Status_t X509IdentityToken_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = policyId.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = certificateData.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t X509IdentityToken_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, X509IdentityToken_t& result)
{
  Status_t status = String_t::Decode(buffer, decoder, result.PolicyId());
  if (status.IsBad())
  {
    return status;
  }

  status = ByteString_t::Decode(buffer, decoder, result.CertificateData());
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

X509IdentityToken_t::~X509IdentityToken_t()
{}

bool X509IdentityToken_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool X509IdentityToken_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t X509IdentityToken_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t X509IdentityToken_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t X509IdentityToken_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_X509IdentityToken_Encoding_DefaultBinary;
}

const String_t& X509IdentityToken_t::PolicyId(void) const
{
  return policyId;
}

String_t& X509IdentityToken_t::PolicyId(void)
{
  return policyId;
}

const ByteString_t& X509IdentityToken_t::CertificateData(void) const
{
  return certificateData;
}

ByteString_t& X509IdentityToken_t::CertificateData(void)
{
  return certificateData;
}

} // namespace uasdk
