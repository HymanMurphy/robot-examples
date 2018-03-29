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
 
#include "opcua_int64_t.h"
#include "opcua_datatype_utilities_t.h"
#include "icodec_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(Int64_t, Number_t<int64_t>)

Int64_t::Int64_t() 
{}

Int64_t::Int64_t(int64_t val) 
  : Number_t<int64_t>(val) 
{}

Int64_t::~Int64_t() 
{}

uint32_t Int64_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

Int64_t& Int64_t::operator=(Int64_t const & obj)
{
  value = obj.value;
  return *this;
}

Int64_t& Int64_t::operator=(int64_t const & obj)
{
  value = obj;
  return *this;
}

bool Int64_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool Int64_t::operator==(Int64_t const & obj) const
{
  return Number_t<int64_t>::operator ==(obj);
}

bool Int64_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

bool Int64_t::operator>(Int64_t const & obj) const
{
  return Number_t<int64_t>::operator >(obj);
}

Status_t Int64_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

Status_t Int64_t::CopyFrom(const Int64_t& source)
{
  value = source.value;
  return OpcUa_Good;
}

Status_t Int64_t::CopyFrom(const BaseDataType_t& source)
{
  const Int64_t* ptr = RuntimeCast<const Int64_t *>(source);
  if (!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t Int64_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  return encoder.Encode(*this, buffer);
}

Status_t Int64_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, Int64_t& result)
{
  return decoder.Decode(buffer, result);
}

}
