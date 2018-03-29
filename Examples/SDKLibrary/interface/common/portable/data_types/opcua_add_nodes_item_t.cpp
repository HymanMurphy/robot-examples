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

#include "opcua_add_nodes_item_t.h"
#include "icodec_t.h"

#if (UASDK_INCLUDE_NODE_MANAGEMENT_SERVICE_SET > 0)

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(AddNodesItem_t, Structure_t)

bool AddNodesItem_t::operator==(AddNodesItem_t const & obj) const
{
  return (
      (parentNodeId == obj.parentNodeId)
      && (referenceTypeId == obj.referenceTypeId)
	  && (requestedNewNodeId == obj.requestedNewNodeId)
	  && (browseName == obj.browseName)
	  && (nodeClass == obj.nodeClass)
	  && (nodeAttributes == obj.nodeAttributes)
	  && (typeDefinition == obj.typeDefinition));
}

bool AddNodesItem_t::operator>(AddNodesItem_t const & obj) const
{
	return (
		(parentNodeId > obj.parentNodeId)
		&& (referenceTypeId > obj.referenceTypeId)
		&& (requestedNewNodeId > obj.requestedNewNodeId)
		&& (browseName > obj.browseName)
		&& (nodeClass > obj.nodeClass)
		&& (nodeAttributes > obj.nodeAttributes)
		&& (typeDefinition > obj.typeDefinition));
}

Status_t AddNodesItem_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

Status_t AddNodesItem_t::CopyFrom(const AddNodesItem_t& source)
{
  Status_t status = parentNodeId.CopyFrom(source.parentNodeId);

  if (status.IsBad())
  {
    return status;
  }

  status = referenceTypeId->CopyFrom(*source.referenceTypeId);
  if (status.IsBad())
  {
    return status;
  }

  status = requestedNewNodeId.CopyFrom(source.requestedNewNodeId);
  if (status.IsBad())
  {
	  return status;
  }

  status = browseName.CopyFrom(source.browseName);
  if (status.IsBad())
  {
	  return status;
  }

  status = nodeClass.CopyFrom(source.nodeClass);
  if (status.IsBad())
  {
	  return status;
  }

  status = nodeAttributes.CopyFrom(source.nodeAttributes);
  if (status.IsBad())
  {
	  return status;
  }

  status = typeDefinition.CopyFrom(source.typeDefinition);
  if (status.IsBad())
  {
	  return status;
  }

  return status;
}

Status_t AddNodesItem_t::CopyFrom(const BaseDataType_t& source)
{
  const AddNodesItem_t* ptr = RuntimeCast<const AddNodesItem_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}


const uasdk::ExpandedNodeId_t& AddNodesItem_t::TypeDefinition(void) const
{
	return typeDefinition;
}

uasdk::ExpandedNodeId_t& AddNodesItem_t::TypeDefinition(void)
{
	return typeDefinition;
}

Status_t AddNodesItem_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = parentNodeId.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = encoder.Encode(referenceTypeId, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = requestedNewNodeId.Encode(encoder, buffer);
  if (status.IsBad())
  {
	  return status;
  }

  status = browseName.Encode(encoder, buffer);
  if (status.IsBad())
  {
	  return status;
  }

  status = nodeClass.Encode(encoder, buffer);
  if (status.IsBad())
  {
	  return status;
  }

  status = nodeAttributes.Encode(encoder, buffer);
  if (status.IsBad())
  {
	  return status;
  }

  status = typeDefinition.Encode(encoder, buffer);
  if (status.IsBad())
  {
	  return status;
  }

  return status;
}

Status_t AddNodesItem_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, AddNodesItem_t& result)
{
  Status_t status = ExpandedNodeId_t::Decode(buffer, decoder, result.ParentNodeId());
  if (status.IsBad()) 
  {
    return status;
  }

  status = NodeId_t::Decode(buffer, decoder, result.ReferenceTypeId());
  if (status.IsBad())
  {
    return status;
  }

  status = ExpandedNodeId_t::Decode(buffer, decoder, result.RequestedNewNodeId());
  if (status.IsBad())
  {
	  return status;
  }

  status = QualifiedName_t::Decode(buffer, decoder, result.BrowseName());
  if (status.IsBad())
  {
	  return status;
  }

  status = NodeClass_t::Decode(buffer, decoder, result.NodeClass());
  if (status.IsBad())
  {
	  return status;
  }

  status = ExtensibleParameter_t::Decode(buffer, decoder, result.NodeAttributes());
  if (status.IsBad())
  {
	  return status;
  }

  status = ExpandedNodeId_t::Decode(buffer, decoder, result.TypeDefinition());
  if (status.IsBad())
  {
	  return status;
  }

  return status;
}

AddNodesItem_t::~AddNodesItem_t()
{}

bool AddNodesItem_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool AddNodesItem_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

uint32_t AddNodesItem_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t AddNodesItem_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_AddNodesItem_Encoding_DefaultBinary;
}

const uasdk::ExpandedNodeId_t& AddNodesItem_t::ParentNodeId(void) const
{
	return parentNodeId;
}

uasdk::ExpandedNodeId_t& AddNodesItem_t::ParentNodeId(void)
{
	return parentNodeId;
}

uasdk::IntrusivePtr_t<const NodeId_t> AddNodesItem_t::ReferenceTypeId(void) const
{
	return referenceTypeId;
}

uasdk::IntrusivePtr_t<uasdk::NodeId_t>& AddNodesItem_t::ReferenceTypeId(void)
{
	return referenceTypeId;
}

const uasdk::ExpandedNodeId_t& AddNodesItem_t::RequestedNewNodeId(void) const
{
	return requestedNewNodeId;
}

uasdk::ExpandedNodeId_t& AddNodesItem_t::RequestedNewNodeId(void)
{
	return requestedNewNodeId;
}

const uasdk::QualifiedName_t& AddNodesItem_t::BrowseName(void) const
{
	return browseName;
}

uasdk::QualifiedName_t& AddNodesItem_t::BrowseName(void)
{
	return browseName;
}

const uasdk::NodeClass_t& AddNodesItem_t::NodeClass(void) const
{
	return nodeClass;
}

uasdk::NodeClass_t& AddNodesItem_t::NodeClass(void)
{
	return nodeClass;
}

const uasdk::ExtensibleParameter_t& AddNodesItem_t::NodeAttributes(void) const
{
	return nodeAttributes;
}

uasdk::ExtensibleParameter_t& AddNodesItem_t::NodeAttributes(void)
{
	return nodeAttributes;
}

} // namespace uasdk

#endif

