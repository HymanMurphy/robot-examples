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

#include "opcua_node_id_guid_t.h"
#include "opcua_datatype_utilities_t.h"
#include "icodec_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(NodeIdGuid_t, NodeId_t)

NodeIdGuid_t::NodeIdGuid_t() 
{}

NodeIdGuid_t::~NodeIdGuid_t() {}

bool NodeIdGuid_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool NodeIdGuid_t::operator==(NodeIdGuid_t const & obj) const
{
  return ((namespaceIndex == obj.namespaceIndex)
      && (identifier == obj.identifier));
}

bool NodeIdGuid_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

bool NodeIdGuid_t::operator>(NodeIdGuid_t const & obj) const
{
  return ((namespaceIndex > obj.namespaceIndex)
      && (identifier > obj.identifier));
}

Status_t NodeIdGuid_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

Status_t NodeIdGuid_t::CopyFrom(const BaseDataType_t& source)
{
  const NodeIdGuid_t* ptr = RuntimeCast<const NodeIdGuid_t *>(source);
  if (!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t NodeIdGuid_t::CopyFrom(const NodeIdGuid_t& source)
{
  Status_t status = namespaceIndex.CopyFrom(source.NamespaceIndex());
  if (status.IsBad())
  {
    return status;
  }

  status = identifier.CopyFrom(source.Identifer().Value());
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

uint32_t NodeIdGuid_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

Status_t NodeIdGuid_t::CopyToNodeId(IntrusivePtr_t<NodeId_t>& destination) const
{
  return DuplicateNodeId<NodeIdGuid_t>(*this, destination);
}

NodeId_t::NodeIdIdentifierType_t NodeIdGuid_t::NodeIdIdentiferType(void) const
{
  return NODEID_IDENTIFIER_GUID;
}

const BaseDataType_t& NodeIdGuid_t::IdentiferBase(void) const
{
  return identifier;
}

BaseDataType_t& NodeIdGuid_t::IdentiferBase(void)
{
  return identifier;
}

const Guid_t& NodeIdGuid_t::Identifer(void) const
{
  return identifier;
}

Guid_t& NodeIdGuid_t::Identifer(void)
{
  return identifier;
}

bool NodeIdGuid_t::IsNull(void) const
{
  return identifier.IsNull();
}

uint32_t NodeIdGuid_t::Hash(void) const
{
  uint32_t sum = 0;
  const uint8_t* data = identifier.Value();
  for (int i = 0; i < identifier.GUID_LENGTH; i++)
  {
    sum += data[i];
  }
  return sum;
}

Status_t NodeIdGuid_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  return encoder.Encode(*this, buffer);
}

}
