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

#include "opcua_delete_nodes_item_t.h"

#if (UASDK_INCLUDE_NODE_MANAGEMENT_SERVICE_SET > 0)

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(DeleteNodesItem_t, Structure_t)

bool DeleteNodesItem_t::operator==(DeleteNodesItem_t const & obj) const
{
  return (
      (nodeId == obj.nodeId)
      && (deleteTargetReferences == obj.deleteTargetReferences));
}

bool DeleteNodesItem_t::operator>(DeleteNodesItem_t const & obj) const
{
	return (
		(nodeId > obj.nodeId)
		&& (deleteTargetReferences > obj.deleteTargetReferences));
}

Status_t DeleteNodesItem_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

Status_t DeleteNodesItem_t::CopyFrom(const DeleteNodesItem_t& source)
{
  Status_t status = nodeId->CopyFrom(*source.nodeId);

  if (status.IsBad())
  {
    return status;
  }

  status = deleteTargetReferences.CopyFrom(source.deleteTargetReferences);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t DeleteNodesItem_t::CopyFrom(const BaseDataType_t& source)
{
  const DeleteNodesItem_t* ptr = RuntimeCast<const DeleteNodesItem_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t DeleteNodesItem_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = nodeId->Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = deleteTargetReferences.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t DeleteNodesItem_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, DeleteNodesItem_t& result)
{
  Status_t status = NodeId_t::Decode(buffer, decoder, result.NodeId());
  if (status.IsBad())
  {
    return status;
  }

  status = Boolean_t::Decode(buffer, decoder, result.DeleteTargetReferences());
  if (status.IsBad())
  {
	  return status;
  }

  return status;
}

DeleteNodesItem_t::~DeleteNodesItem_t()
{}

bool DeleteNodesItem_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool DeleteNodesItem_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

uint32_t DeleteNodesItem_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t DeleteNodesItem_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_DeleteNodesItem_Encoding_DefaultBinary;
}

uasdk::IntrusivePtr_t<const NodeId_t> DeleteNodesItem_t::NodeId(void) const
{
	return nodeId;
}

uasdk::IntrusivePtr_t<uasdk::NodeId_t>& DeleteNodesItem_t::NodeId(void)
{
	return nodeId;
}

const uasdk::Boolean_t& DeleteNodesItem_t::DeleteTargetReferences(void) const
{
	return deleteTargetReferences;
}

uasdk::Boolean_t& DeleteNodesItem_t::DeleteTargetReferences(void)
{
	return deleteTargetReferences;
}

} // namespace uasdk

#endif
