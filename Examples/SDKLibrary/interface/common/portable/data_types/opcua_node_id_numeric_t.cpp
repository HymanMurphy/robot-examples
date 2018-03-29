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

#include "opcua_node_id_numeric_t.h"
#include "opcua_byte_t.h"
#include "opcua_datatype_utilities_t.h"
#include "icodec_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(NodeIdNumeric_t, NodeId_t)

NodeIdNumeric_t::NodeIdNumeric_t()
{
}

NodeIdNumeric_t::NodeIdNumeric_t(uint16_t namespaceIndex_, uint32_t identifier_)
{
  Initialise(namespaceIndex_, identifier_);
}

bool NodeIdNumeric_t::operator==(NodeIdNumeric_t const & obj) const
{
  return (
      (namespaceIndex == obj.namespaceIndex)
      && (identifier == obj.Identifer()));
}

bool NodeIdNumeric_t::operator>(NodeIdNumeric_t const & obj) const
{
  return (
      (namespaceIndex > obj.namespaceIndex)
      && (identifier > obj.Identifer()));
}

Status_t NodeIdNumeric_t::CopyFrom(const BaseDataType_t& source)
{
  const NodeIdNumeric_t* ptr = RuntimeCast<const NodeIdNumeric_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t NodeIdNumeric_t::CopyFrom(const NodeIdNumeric_t& source)
{
  Status_t status = namespaceIndex.CopyFrom(source.NamespaceIndex());
  if(status.IsBad())
  {
    return status;
  }

  status = identifier.CopyFrom(source.Identifer());
  if(status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t NodeIdNumeric_t::CopyToNodeId(IntrusivePtr_t<NodeId_t>& destination) const
{
  return DuplicateNodeId<NodeIdNumeric_t>(*this, destination);
}

void NodeIdNumeric_t::Initialise(uint16_t namespaceIndex_, uint32_t value)
{
  namespaceIndex.Value(namespaceIndex_);
  identifier.Value(value);
}

void NodeIdNumeric_t::Initialise(uint32_t value)
{
  return Initialise(0, value);
}

Status_t NodeIdNumeric_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  return encoder.Encode(*this, buffer);
}

NodeIdNumeric_t::~NodeIdNumeric_t()
{}

bool NodeIdNumeric_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool NodeIdNumeric_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t NodeIdNumeric_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t NodeIdNumeric_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

NodeIdNumeric_t::NodeIdIdentifierType_t NodeIdNumeric_t::NodeIdIdentiferType(void) const
{
  return NODEID_IDENTIFIER_NUMERIC;
}

const BaseDataType_t& NodeIdNumeric_t::IdentiferBase(void) const
{
  return identifier;
}

BaseDataType_t& NodeIdNumeric_t::IdentiferBase(void)
{
  return identifier;
}

const UInt32_t& NodeIdNumeric_t::Identifer(void) const
{
  return identifier;
}

UInt32_t& NodeIdNumeric_t::Identifer(void)
{
  return identifier;
}

bool NodeIdNumeric_t::IsNull(void) const
{
  return identifier.Value() == 0;
}

uint32_t NodeIdNumeric_t::Hash(void) const
{
  return identifier.Value();
}

} // namespace uasdk
