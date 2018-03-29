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

#include "opcua_signature_data_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(SignatureData_t, Structure_t)

bool SignatureData_t::operator==(SignatureData_t const & obj) const
{
  return (
       (algorithm == obj.algorithm)
       && (signature == obj.signature));
}

bool SignatureData_t::operator>(SignatureData_t const & obj) const
{
  return (
      (algorithm > obj.algorithm)
      && (signature > obj.signature));
}

Status_t SignatureData_t::CopyFrom(const BaseDataType_t& source)
{
  const SignatureData_t* ptr = RuntimeCast<const SignatureData_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t SignatureData_t::CopyFrom(const SignatureData_t& source)
{
  Status_t status = algorithm.CopyFrom(source.algorithm);
  if(status.IsBad())
  {
   return status;
  }

  status = signature.CopyFrom(source.signature);
  if(status.IsBad())
  {
   return status;
  }

  return OpcUa_Good;
}

Status_t SignatureData_t::CopyFrom(const SignatureData_t& source, const String_t& indexRange)
{
  UASDK_UNUSED(indexRange);
  return CopyFrom(source);
}

Status_t SignatureData_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = algorithm.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = signature.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t SignatureData_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, SignatureData_t& result)
{
  Status_t status = String_t::Decode(buffer, decoder, result.Algorithm());
  if (status.IsBad())
  {
    return status;
  }

  status = ByteString_t::Decode(buffer, decoder, result.Signature());
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

SignatureData_t::SignatureData_t()
{}

SignatureData_t::~SignatureData_t()
{}

bool SignatureData_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool SignatureData_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t SignatureData_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t SignatureData_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t SignatureData_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_SignatureData_Encoding_DefaultBinary;
}

const String_t& SignatureData_t::Algorithm(void) const
{
  return algorithm;
}

String_t& SignatureData_t::Algorithm(void)
{
  return algorithm;
}

const ByteString_t& SignatureData_t::Signature(void) const
{
  return signature;
}

ByteString_t& SignatureData_t::Signature(void)
{
  return signature;
}

} // namespace uasdk
