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

#include "opcua_float_t.h"
#include "opcua_datatype_utilities_t.h"
#include "icodec_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(Float_t, Number_t<float>)

Float_t::Float_t() 
{}

Float_t::Float_t(float val) 
  : Number_t<float>(val) 
{}

Float_t::~Float_t() 
{}

uint32_t Float_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

Float_t& Float_t::operator=(Float_t const & obj)
{
  value = obj.value;
  return *this;
}

Float_t& Float_t::operator=(float const & obj)
{
  value = obj;
  return *this;
}

bool Float_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool Float_t::operator==(Float_t const & obj) const
{
  return (value == obj.value) || ((value != value) && (obj.value != obj.value));
}

bool Float_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

bool Float_t::operator>(Float_t const & obj) const
{
  return Number_t<float>::operator >(obj);
}

Status_t Float_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

Status_t Float_t::CopyFrom(const Float_t& source)
{
  value = source.value;
  return OpcUa_Good;
}

Status_t Float_t::CopyFrom(const BaseDataType_t& source)
{
  const Float_t* ptr = RuntimeCast<const Float_t *>(source);
  if (!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t Float_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  return encoder.Encode(*this, buffer);
}

Status_t Float_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, Float_t& result)
{
  return decoder.Decode(buffer, result);
}

}
