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

#include "opcua_int32_t.h"
#include "opcua_datatype_utilities_t.h"
#include "icodec_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(Int32_t, Number_t<int32_t>)

Int32_t::Int32_t() 
{}

Int32_t::Int32_t(int32_t val) 
  : Number_t<int32_t>(val) 
{}

Int32_t::~Int32_t()
{}

uint32_t Int32_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

Int32_t& Int32_t::operator=(Int32_t const & obj)
{
  value = obj.value;
  return *this;
}

Int32_t& Int32_t::operator=(int32_t const & obj)
{
  value = obj;
  return *this;
}

bool Int32_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool Int32_t::operator==(Int32_t const & obj) const
{
  return Number_t<int32_t>::operator ==(obj);
}

bool Int32_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

bool Int32_t::operator>(Int32_t const & obj) const
{
  return Number_t<int32_t>::operator >(obj);
}

Status_t Int32_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

Status_t Int32_t::CopyFrom(const Int32_t& source)
{
  value = source.value;
  return OpcUa_Good;
}

Status_t Int32_t::CopyFrom(const BaseDataType_t& source)
{
  const Int32_t* ptr = RuntimeCast<const Int32_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t Int32_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  return encoder.Encode(*this, buffer);
}

Status_t Int32_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, Int32_t& result)
{
  return decoder.Decode(buffer, result);
}

}
