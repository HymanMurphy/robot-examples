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

#include "opcua_node_id_string_t.h"
#include "opcua_datatype_utilities_t.h"
#include "icodec_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(NodeIdString_t, NodeId_t)

NodeIdString_t::NodeIdString_t() 
{}

NodeIdString_t::~NodeIdString_t()
{}

bool NodeIdString_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool NodeIdString_t::operator==(NodeIdString_t const & obj) const
{
  return ((namespaceIndex == obj.namespaceIndex)
      && (identifier == obj.identifier));
}

bool NodeIdString_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

bool NodeIdString_t::operator>(NodeIdString_t const & obj) const
{
  return ((namespaceIndex > obj.namespaceIndex)
      && (identifier > obj.identifier));
}

Status_t NodeIdString_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

Status_t NodeIdString_t::CopyFrom(const BaseDataType_t& source)
{
  const NodeIdString_t* ptr = RuntimeCast<const NodeIdString_t *>(source);
  if (!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t NodeIdString_t::CopyFrom(const NodeIdString_t& source)
{
  Status_t status = namespaceIndex.CopyFrom(source.NamespaceIndex());
  if (status.IsBad())
  {
    return status;
  }

  status = identifier.CopyFrom(source.Identifer());
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t NodeIdString_t::CopyFrom(const NodeIdString_t& source, const String_t& indexRange)
{
  UASDK_UNUSED(indexRange);
  return CopyFrom(source);
}

uint32_t NodeIdString_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

Status_t NodeIdString_t::CopyToNodeId(IntrusivePtr_t<NodeId_t>& destination) const
{
  return DuplicateNodeId<NodeIdString_t>(*this, destination);
}

NodeId_t::NodeIdIdentifierType_t NodeIdString_t::NodeIdIdentiferType(void) const
{
  return NODEID_IDENTIFIER_STRING;
}

const BaseDataType_t& NodeIdString_t::IdentiferBase(void) const
{
  return identifier;
}

BaseDataType_t& NodeIdString_t::IdentiferBase(void)
{
  return identifier;
}

const String_t& NodeIdString_t::Identifer(void) const
{
  return identifier;
}

String_t& NodeIdString_t::Identifer(void)
{
  return identifier;
}

bool NodeIdString_t::IsNull(void) const
{
  return identifier.IsNull();
}

uint32_t NodeIdString_t::Hash(void) const
{
  if (identifier.Length() <= 0)
  {
    return 0;
  }

  ScopedPtr_t<Array_t<char> > id;
  if (identifier.ToString(id).IsBad())
  {
    return 0;
  }

  const uint8_t* data = reinterpret_cast<const uint8_t*>(id->Value());
  uint32_t sum = 0;
  int32_t length = identifier.Length();
  for (int32_t i = 0; i < length; i++)
  {
    sum += data[i];
  }
  return sum;
}

Status_t NodeIdString_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  return encoder.Encode(*this, buffer);
}

}
