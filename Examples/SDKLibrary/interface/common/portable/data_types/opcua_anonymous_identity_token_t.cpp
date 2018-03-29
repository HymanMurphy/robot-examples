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

#include "opcua_anonymous_identity_token_t.h"
#include "opcua_identifiers.h"
#include "buffer_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(AnonymousIdentityToken_t, Structure_t)

AnonymousIdentityToken_t::AnonymousIdentityToken_t()
{
}

bool AnonymousIdentityToken_t::operator==(AnonymousIdentityToken_t const & obj) const
{
  return (policyId == obj.policyId);
}

bool AnonymousIdentityToken_t::operator>(AnonymousIdentityToken_t const & obj) const
{
  return (policyId > obj.policyId);
}

Status_t AnonymousIdentityToken_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

Status_t AnonymousIdentityToken_t::CopyFrom(const AnonymousIdentityToken_t& source)
{
  return policyId.CopyFrom(source.policyId);
}

Status_t AnonymousIdentityToken_t::CopyFrom(const BaseDataType_t& source)
{
  const AnonymousIdentityToken_t* ptr = RuntimeCast<const AnonymousIdentityToken_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t AnonymousIdentityToken_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = policyId.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t AnonymousIdentityToken_t::Decode(const IBuffer_t& buffer,
                                               ICodec_t& decoder,
                                               AnonymousIdentityToken_t& result)
{
  Status_t status = String_t::Decode(buffer, decoder, result.PolicyId());
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

AnonymousIdentityToken_t::~AnonymousIdentityToken_t()
{}

bool AnonymousIdentityToken_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool AnonymousIdentityToken_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

uint32_t AnonymousIdentityToken_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t AnonymousIdentityToken_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_AnonymousIdentityToken_Encoding_DefaultBinary;
}

const String_t& AnonymousIdentityToken_t::PolicyId(void) const
{
  return policyId;
}
String_t& AnonymousIdentityToken_t::PolicyId(void)
{
  return policyId;
}

} // namespace uasdk
