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

#include "opcua_delete_references_item_t.h"
#include "icodec_t.h"

#if (UASDK_INCLUDE_NODE_MANAGEMENT_SERVICE_SET > 0)

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(DeleteReferencesItem_t, Structure_t)

bool DeleteReferencesItem_t::operator==(DeleteReferencesItem_t const & obj) const
{
  return (
      (sourceNodeId == obj.sourceNodeId)
      && (referenceTypeId == obj.referenceTypeId)
	  && (isForward == obj.isForward)
	  && (targetNodeId == obj.targetNodeId)
	  && (deleteBidirectional == obj.deleteBidirectional));
}

bool DeleteReferencesItem_t::operator>(DeleteReferencesItem_t const & obj) const
{
	return (
		(sourceNodeId > obj.sourceNodeId)
		&& (referenceTypeId > obj.referenceTypeId)
		&& (isForward > obj.isForward)
		&& (targetNodeId > obj.targetNodeId)
		&& (deleteBidirectional > obj.deleteBidirectional));
}

Status_t DeleteReferencesItem_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

Status_t DeleteReferencesItem_t::CopyFrom(const DeleteReferencesItem_t& source)
{
  Status_t status = sourceNodeId->CopyFrom(*source.sourceNodeId);

  if (status.IsBad())
  {
    return status;
  }

  status = referenceTypeId->CopyFrom(*source.referenceTypeId);
  if (status.IsBad())
  {
    return status;
  }

  status = isForward.CopyFrom(source.isForward);
  if (status.IsBad())
  {
	  return status;
  }


  status = targetNodeId.CopyFrom(source.targetNodeId);
  if (status.IsBad())
  {
	  return status;
  }

  status = deleteBidirectional.CopyFrom(source.deleteBidirectional);
  if (status.IsBad())
  {
	  return status;
  }

  return status;
}

Status_t DeleteReferencesItem_t::CopyFrom(const BaseDataType_t& source)
{
  const DeleteReferencesItem_t* ptr = RuntimeCast<const DeleteReferencesItem_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t DeleteReferencesItem_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = encoder.Encode(sourceNodeId, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = encoder.Encode(referenceTypeId, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = isForward.Encode(encoder, buffer);
  if (status.IsBad())
  {
	  return status;
  }

  status = targetNodeId.Encode(encoder, buffer);
  if (status.IsBad())
  {
	  return status;
  }

  status = deleteBidirectional.Encode(encoder, buffer);
  if (status.IsBad())
  {
	  return status;
  }

  return status;
}

Status_t DeleteReferencesItem_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, DeleteReferencesItem_t& result)
{
	Status_t status = NodeId_t::Decode(buffer, decoder, result.SourceNodeId());
	if (status.IsBad())
	{
		return status;
	}

	status = NodeId_t::Decode(buffer, decoder, result.ReferenceTypeId());
	if (status.IsBad())
	{
		return status;
	}

  status = Boolean_t::Decode(buffer, decoder, result.IsForward());
  if (status.IsBad())
  {
	  return status;
  }

  status = ExpandedNodeId_t::Decode(buffer, decoder, result.TargetNodeId());
  if (status.IsBad())
  {
	  return status;
  }

  status = Boolean_t::Decode(buffer, decoder, result.DeleteBidirectional());
  if (status.IsBad())
  {
	  return status;
  }

  return status;
}

DeleteReferencesItem_t::~DeleteReferencesItem_t()
{}

bool DeleteReferencesItem_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool DeleteReferencesItem_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

uint32_t DeleteReferencesItem_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t DeleteReferencesItem_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_DeleteReferencesItem_Encoding_DefaultBinary;
}

IntrusivePtr_t<const NodeId_t> DeleteReferencesItem_t::SourceNodeId(void) const
{
	return sourceNodeId;
}

IntrusivePtr_t<NodeId_t>& DeleteReferencesItem_t::SourceNodeId(void)
{
	return sourceNodeId;
}

IntrusivePtr_t<const NodeId_t> DeleteReferencesItem_t::ReferenceTypeId(void) const
{
	return referenceTypeId;
}

IntrusivePtr_t<NodeId_t>& DeleteReferencesItem_t::ReferenceTypeId(void)
{
	return referenceTypeId;
}

const Boolean_t & DeleteReferencesItem_t::IsForward(void) const
{
	return isForward;
}

Boolean_t & DeleteReferencesItem_t::IsForward(void)
{
	return isForward;
}

const ExpandedNodeId_t & DeleteReferencesItem_t::TargetNodeId(void) const
{
	return targetNodeId;
}

ExpandedNodeId_t & DeleteReferencesItem_t::TargetNodeId(void)
{
	return targetNodeId;
}

const Boolean_t & DeleteReferencesItem_t::DeleteBidirectional(void) const
{
	return deleteBidirectional;
}

Boolean_t & DeleteReferencesItem_t::DeleteBidirectional(void)
{
	return deleteBidirectional;
}

} // namespace uasdk

#endif
