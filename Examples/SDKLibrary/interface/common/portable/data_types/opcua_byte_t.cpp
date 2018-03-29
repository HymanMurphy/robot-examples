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


#include "opcua_byte_t.h"
#include "opcua_datatype_utilities_t.h"
#include "icodec_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(Byte_t, Number_t<uint8_t>)

Byte_t::Byte_t() 
{}

Byte_t::Byte_t(uint8_t val) 
  : Number_t<uint8_t>(val)
{}

Byte_t::~Byte_t() 
{}

Byte_t& Byte_t::operator=(Byte_t const & obj)
{
  value = obj.value;
  return *this;
}

Byte_t& Byte_t::operator=(uint8_t const & obj)
{
  value = obj;
  return *this;
}

bool Byte_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool Byte_t::operator==(Byte_t const & obj) const
{
  return Number_t<uint8_t>::operator ==(obj);
}

bool Byte_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

bool Byte_t::operator>(Byte_t const & obj) const
{
  return Number_t<uint8_t>::operator >(obj);
}

Status_t Byte_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

Status_t Byte_t::CopyFrom(const Byte_t& source)
{
  value = source.value;
  return OpcUa_Good;
}

Status_t Byte_t::CopyFrom(const BaseDataType_t& source)
{
  const Byte_t* ptr = RuntimeCast<const Byte_t *>(source);
  if (!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

uint32_t Byte_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

Status_t Byte_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  return encoder.Encode(*this, buffer);
}

Status_t Byte_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, Byte_t& result)
{
  return decoder.Decode(buffer, result);
}

}
