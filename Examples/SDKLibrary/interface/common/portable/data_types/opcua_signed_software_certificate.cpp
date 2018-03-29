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

#include "opcua_signed_software_certificate.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(SignedSoftwareCertificate_t, Structure_t)

SignedSoftwareCertificate_t::SignedSoftwareCertificate_t()
{
}

bool SignedSoftwareCertificate_t::operator==(SignedSoftwareCertificate_t const & obj) const
{
	return (
		(certificateData == obj.certificateData)
		&& (signature == obj.signature));
}

bool SignedSoftwareCertificate_t::operator>(SignedSoftwareCertificate_t const & obj) const
{
  return (
      (certificateData > obj.certificateData)
      && (signature > obj.signature));
}

Status_t SignedSoftwareCertificate_t::CopyFrom(const SignedSoftwareCertificate_t& source)
{
  Status_t status = certificateData.CopyFrom(source.CertificateData());
  if (status.IsBad())
  {
    return status;
  }

	status = signature.CopyFrom(source.Signature());
	if (status.IsBad())
	{
		return status;
	}

  return status;
}

Status_t SignedSoftwareCertificate_t::CopyFrom(const BaseDataType_t& source)
{
  const SignedSoftwareCertificate_t* ptr = RuntimeCast<const SignedSoftwareCertificate_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t SignedSoftwareCertificate_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = certificateData.Encode(encoder, buffer);
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

Status_t SignedSoftwareCertificate_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, SignedSoftwareCertificate_t& result)
{
  Status_t status = ByteString_t::Decode(buffer, decoder, result.CertificateData());
  if (status.IsBad())
  {
    return status;
  }

	status = ByteString_t::Decode(buffer, decoder, result.Signature());
	if (status.IsBad())
	{
		return status;
	}

  return status;
}

SignedSoftwareCertificate_t::~SignedSoftwareCertificate_t()
{}

bool SignedSoftwareCertificate_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool SignedSoftwareCertificate_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t SignedSoftwareCertificate_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t SignedSoftwareCertificate_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t SignedSoftwareCertificate_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_SignedSoftwareCertificate_Encoding_DefaultBinary;
}


const ByteString_t& SignedSoftwareCertificate_t::CertificateData(void) const
{
  return certificateData;
}

ByteString_t& SignedSoftwareCertificate_t::CertificateData(void)
{
  return certificateData;
}

const ByteString_t& SignedSoftwareCertificate_t::Signature(void) const
{
	return signature;
}

ByteString_t& SignedSoftwareCertificate_t::Signature(void)
{
	return signature;
}

} // namespace uasdk
