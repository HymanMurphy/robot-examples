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

#include "opcua_status_code_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(StatusCode_t, BaseDataType_t)

bool StatusCode_t::operator==(StatusCode_t const & obj) const
{
  return (value == obj.value);
}

bool StatusCode_t::operator>(StatusCode_t const & obj) const
{
  return (value.Value() > obj.value.Value());
}

Status_t StatusCode_t::CopyFrom(const BaseDataType_t& source)
{
  const StatusCode_t* ptr = RuntimeCast<const StatusCode_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t StatusCode_t::CopyFrom(const StatusCode_t& source)
{
  return value.CopyFrom(source.Value());
}

Status_t StatusCode_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = value.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return 0;
}

Status_t StatusCode_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, StatusCode_t& result)
{
  Status_t status = UInt32_t::Decode(buffer, decoder, result.Value());
  if (status.IsBad())
  {
    return status;
  }

  return 0;
}

StatusCode_t::StatusCode_t()
  : value(0)
{}

StatusCode_t::StatusCode_t(uint32_t val)
  : value(val)
{}

StatusCode_t::~StatusCode_t()
{}

StatusCode_t& StatusCode_t::operator=(StatusCode_t const & obj)
{
  value = obj.value;
  return *this;
}

StatusCode_t& StatusCode_t::operator=(Status_t const & obj)
{
  value = obj.Value();
  return *this;
}

StatusCode_t& StatusCode_t::operator=(UInt32_t const & value_)
{
  value = value_.Value();
  return *this;
}

StatusCode_t& StatusCode_t::operator=(uint32_t const & value_)
{
  value = value_;
  return *this;
}

bool StatusCode_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool StatusCode_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t StatusCode_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t StatusCode_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

const UInt32_t& StatusCode_t::Value(void) const
{
  return value;
}

UInt32_t& StatusCode_t::Value(void)
{
  return value;
}

Status_t StatusCode_t::ValueAsStatus(void) const
{
  Status_t status(value.Value());
  return status;
}

} // namespace uasdk
