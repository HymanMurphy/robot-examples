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

#include "opcua_double_complex_number_type_t.h"

#if (UASDK_INCLUDE_ADDITIONAL_DA_TYPES > 0)

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(DoubleComplexNumberType_t, Structure_t)

bool DoubleComplexNumberType_t::operator==(DoubleComplexNumberType_t const & obj) const
{
  return (  (real == obj.real)
          && (imaginary == obj.imaginary)  );
}

bool DoubleComplexNumberType_t::operator>(DoubleComplexNumberType_t const & obj) const
{
  return (  (real > obj.real)
          && (imaginary > obj.imaginary) );
}

Status_t DoubleComplexNumberType_t::CopyFrom(const BaseDataType_t& source)
{
  const DoubleComplexNumberType_t* ptr = RuntimeCast<const DoubleComplexNumberType_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t DoubleComplexNumberType_t::CopyFrom(const DoubleComplexNumberType_t& source)
{
  Status_t status = real.CopyFrom(source.real);
  if (status.IsBad())
  {
    return status;
  }

  status = imaginary.CopyFrom(source.imaginary);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t DoubleComplexNumberType_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = real.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = imaginary.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t DoubleComplexNumberType_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, DoubleComplexNumberType_t& result)
{
  Status_t status = Double_t::Decode(buffer, decoder, result.Real());
  if (status.IsBad())
  {
    return status;
  }

  status = Double_t::Decode(buffer, decoder, result.Imaginary());
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

DoubleComplexNumberType_t::~DoubleComplexNumberType_t() {}

bool DoubleComplexNumberType_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool DoubleComplexNumberType_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t DoubleComplexNumberType_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t DoubleComplexNumberType_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t DoubleComplexNumberType_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_DoubleComplexNumberType_Encoding_DefaultBinary;
}

const Double_t& DoubleComplexNumberType_t::Real(void) const
{
  return real;
}

Double_t& DoubleComplexNumberType_t::Real(void)
{
  return real;
}

const Double_t& DoubleComplexNumberType_t::Imaginary(void) const
{
  return imaginary;
}

Double_t& DoubleComplexNumberType_t::Imaginary(void)
{
  return imaginary;
}

} //namespace uasdk

#endif
