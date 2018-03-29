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

#include "opcua_node_id_t.h"
#include "opcua_datatype_utilities_t.h"
#include "icodec_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(NodeId_t, BaseDataType_t)

NodeId_t::NodeId_t() : namespaceIndex(0)
{
}

Status_t NodeId_t::Decode(const IBuffer_t& buffer,
                          ICodec_t& decoder,
                          IntrusivePtr_t<NodeId_t>& result)
{
  return decoder.Decode(buffer, result);
}

NodeId_t::~NodeId_t()
{}

uint32_t NodeId_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

const UInt16_t&NodeId_t::NamespaceIndex(void) const
{
  return namespaceIndex;
}

UInt16_t& NodeId_t::NamespaceIndex(void)
{
  return namespaceIndex;
}

} // namespace uasdk
