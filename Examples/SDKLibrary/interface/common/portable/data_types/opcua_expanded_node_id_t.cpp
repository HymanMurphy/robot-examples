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

#include "opcua_expanded_node_id_t.h"
#include "opcua_datatype_utilities_t.h"
#include "icodec_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(ExpandedNodeId_t, BaseDataType_t);

ExpandedNodeId_t::ExpandedNodeId_t() : serverIndex(0)
{
}

bool ExpandedNodeId_t::operator==(ExpandedNodeId_t const & obj) const
{
  return (
      Equal(nodeid, obj.nodeid)
      && (namespaceUri == obj.namespaceUri)
      && (serverIndex == obj.serverIndex) );
}

bool ExpandedNodeId_t::operator>(ExpandedNodeId_t const & obj) const
{
  return (
      GreaterThan(nodeid, obj.nodeid)
      && (namespaceUri > obj.namespaceUri)
      && (serverIndex > obj.serverIndex) );
}

Status_t ExpandedNodeId_t::CopyFrom(const ExpandedNodeId_t& source)
{
  if(!source.nodeid.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  Status_t status = source.nodeid->CopyToNodeId(nodeid);
  if (status.IsBad())
  {
    return status;
  }

  status = namespaceUri.CopyFrom(source.namespaceUri);
  if (status.IsBad())
  {
    return status;
  }

  status = serverIndex.CopyFrom(source.serverIndex);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t ExpandedNodeId_t::CopyFrom(const BaseDataType_t& source)
{
  const ExpandedNodeId_t* ptr = RuntimeCast<const ExpandedNodeId_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t ExpandedNodeId_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  return encoder.Encode(*this, buffer);
}

Status_t ExpandedNodeId_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, ExpandedNodeId_t& result)
{
  return decoder.Decode(buffer, result);
}

ExpandedNodeId_t::~ExpandedNodeId_t()
{}

bool ExpandedNodeId_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool ExpandedNodeId_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t ExpandedNodeId_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t ExpandedNodeId_t::TypeId(uint16_t& namespaceIndex) const

{
  namespaceIndex = 0; return TYPE_ID;
}

IntrusivePtr_t<const NodeId_t> ExpandedNodeId_t::Nodeid(void) const
{
  return nodeid;
}

IntrusivePtr_t<NodeId_t>& ExpandedNodeId_t::Nodeid(void)
{
  return nodeid;
}

const String_t& ExpandedNodeId_t::NamespaceUri(void) const
{
  return namespaceUri;
}

String_t& ExpandedNodeId_t::NamespaceUri(void)
{
  return namespaceUri;
}

const UInt32_t& ExpandedNodeId_t::ServerIndex(void) const
{
  return serverIndex;
}

UInt32_t& ExpandedNodeId_t::ServerIndex(void)
{
  return serverIndex;
}

} // namespace uasdk
