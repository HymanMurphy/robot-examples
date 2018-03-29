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

#include "opcua_xv_type_t.h"

#if (UASDK_INCLUDE_ADDITIONAL_DA_TYPES > 0)

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(XVType_t, Structure_t)

bool XVType_t::operator==(XVType_t const & obj) const
{
  return (  (x == obj.x)
          && (value == obj.value)  );
}

bool XVType_t::operator>(XVType_t const & obj) const
{
  return (  (x > obj.x)
          && (value > obj.value) );
}

Status_t XVType_t::CopyFrom(const BaseDataType_t& source)
{
  const XVType_t* ptr = RuntimeCast<const XVType_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t XVType_t::CopyFrom(const XVType_t& source)
{
  Status_t status = x.CopyFrom(source.x);
  if (status.IsBad())
  {
    return status;
  }

  status = value.CopyFrom(source.value);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t XVType_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = x.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = value.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t XVType_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, XVType_t& result)
{
  Status_t status = Double_t::Decode(buffer, decoder, result.X());
  if (status.IsBad())
  {
    return status;
  }

  status = Float_t::Decode(buffer, decoder, result.Value());
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

XVType_t::~XVType_t()
{}

bool XVType_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool XVType_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t XVType_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t XVType_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t XVType_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_XVType_Encoding_DefaultBinary;
}

const Double_t& XVType_t::X(void) const
{
  return x;
}

Double_t& XVType_t::X(void)
{
  return x;
}

const Float_t& XVType_t::Value(void) const
{
  return value;
}

Float_t& XVType_t::Value(void)
{
  return value;
}

} //namespace uasdk

#endif
