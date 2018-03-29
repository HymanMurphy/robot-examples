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

#include "opcua_node_class_t.h"
#include "opcua_int32_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(NodeClass_t, Enumeration_t)

NodeClass_t::NodeClass_t(void)
{
  value = OPCUA_NODECLASS_INVALID;
}

NodeClass_t::NodeClass_t(Enum_t value_)
{
  value = value_;
}

bool NodeClass_t::operator==(NodeClass_t const & obj) const
{
  return value == obj.value;
}

bool NodeClass_t::operator>(NodeClass_t const & obj) const
{
  return value > obj.value;
}

Status_t NodeClass_t::CopyFrom(const BaseDataType_t& source)
{
  const NodeClass_t* ptr = RuntimeCast<const NodeClass_t *>(source);
  if(!ptr)
  {
    return TryCopyFromInt32(source);
  }

  return CopyFrom(*ptr);
}

Status_t NodeClass_t::CopyFrom(const NodeClass_t& source)
{
  Status_t status = OpcUa_BadOutOfRange;
  if ( (source.value < OPCUA_NODECLASS_INVALID) || (source.value > OPCUA_NODECLASS_END))
  {
    return status;
  }

  value = source.value;

  return OpcUa_Good;
}

Status_t NodeClass_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Int32_t value_((int32_t)value);
  Status_t status = value_.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t NodeClass_t::WriteIntToValue(int32_t newValue)
{
  if ((newValue < 0) || (newValue >= OPCUA_NODECLASS_END))
  {
	  UASDK_RETURN_BAD_STATUS(OpcUa_BadDecodingError);
  }
  else
  {
    value = static_cast<Enum_t>(newValue);
  }
  return OpcUa_Good;
}

NodeClass_t::~NodeClass_t()
{}

NodeClass_t& NodeClass_t::operator=(NodeClass_t const & rhs)
{
  value = rhs.Value();
  return *this;
}

NodeClass_t& NodeClass_t::operator=(Enum_t const & rhs)
{
  value = rhs;
  return *this;
}

bool NodeClass_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool NodeClass_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t NodeClass_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t NodeClass_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

const NodeClass_t::Enum_t& NodeClass_t::Value(void) const
{
  return value;
}

NodeClass_t::Enum_t& NodeClass_t::Value(void)
{
  return value;
}

} // namespace uasdk
