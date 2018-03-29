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

#include "opcua_double_t.h"
#include "opcua_datatype_utilities_t.h"
#include "icodec_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(Double_t, Number_t<double>)

Double_t::Double_t() 
{}

Double_t::Double_t(double val) 
  : Number_t<double>(val)
{}

Double_t::~Double_t() 
{}

uint32_t Double_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

Double_t& Double_t::operator=(Double_t const & obj)
{
  value = obj.value;
  return *this;
}

Double_t& Double_t::operator=(double const & obj)
{
  value = obj;
  return *this;
}

bool Double_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool Double_t::operator==(Double_t const & obj) const
{
  return (value == obj.value) || ((value != value) && (obj.value != obj.value));
}

bool Double_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

bool Double_t::operator>(Double_t const & obj) const
{
  return Number_t<double>::operator >(obj);
}

Status_t Double_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

Status_t Double_t::CopyFrom(const Double_t& source)
{
  value = source.Value();
  return OpcUa_Good;
}

Status_t Double_t::CopyFrom(const BaseDataType_t& source)
{
  const Double_t* ptr = RuntimeCast<const Double_t *>(source);
  if (!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t Double_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  return encoder.Encode(*this, buffer);
}

Status_t Double_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, Double_t& result)
{
  return decoder.Decode(buffer, result);
}

}
