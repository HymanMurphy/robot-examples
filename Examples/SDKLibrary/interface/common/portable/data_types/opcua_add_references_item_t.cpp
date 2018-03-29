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

#include "opcua_add_references_item_t.h"
#include "icodec_t.h"

#if (UASDK_INCLUDE_NODE_MANAGEMENT_SERVICE_SET > 0)

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(AddReferencesItem_t, Structure_t)

bool AddReferencesItem_t::operator==(AddReferencesItem_t const & obj) const
{
  return (
      (sourceNodeId == obj.sourceNodeId)
      && (referenceTypeId == obj.referenceTypeId)
	  && (isForward == obj.isForward)
	  && (targetServerUri == obj.targetServerUri)
	  && (targetNodeId == obj.targetNodeId)
	  && (targetNodeClass == obj.targetNodeClass));
}

bool AddReferencesItem_t::operator>(AddReferencesItem_t const & obj) const
{
	return (
		(sourceNodeId > obj.sourceNodeId)
		&& (referenceTypeId > obj.referenceTypeId)
		&& (isForward > obj.isForward)
		&& (targetServerUri > obj.targetServerUri)
		&& (targetNodeId > obj.targetNodeId)
		&& (targetNodeClass > obj.targetNodeClass));
}

Status_t AddReferencesItem_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

Status_t AddReferencesItem_t::CopyFrom(const AddReferencesItem_t& source)
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

  status = targetServerUri.CopyFrom(source.targetServerUri);
  if (status.IsBad())
  {
	  return status;
  }

  status = targetNodeId.CopyFrom(source.targetNodeId);
  if (status.IsBad())
  {
	  return status;
  }

  status = targetNodeClass.CopyFrom(source.targetNodeClass);
  if (status.IsBad())
  {
	  return status;
  }

  return status;
}

Status_t AddReferencesItem_t::CopyFrom(const BaseDataType_t& source)
{
  const AddReferencesItem_t* ptr = RuntimeCast<const AddReferencesItem_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t AddReferencesItem_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
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

  status = targetServerUri.Encode(encoder, buffer);
  if (status.IsBad())
  {
	  return status;
  }

  status = targetNodeId.Encode(encoder, buffer);
  if (status.IsBad())
  {
	  return status;
  }

  status = targetNodeClass.Encode(encoder, buffer);
  if (status.IsBad())
  {
	  return status;
  }

  return status;
}

Status_t AddReferencesItem_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, AddReferencesItem_t& result)
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

  status = String_t::Decode(buffer, decoder, result.TargetServerUri());
  if (status.IsBad())
  {
	  return status;
  }

  status = ExpandedNodeId_t::Decode(buffer, decoder, result.TargetNodeId());
  if (status.IsBad())
  {
	  return status;
  }

  status = NodeClass_t::Decode(buffer, decoder, result.TargetNodeClass());
  if (status.IsBad())
  {
	  return status;
  }

  return status;
}

AddReferencesItem_t::~AddReferencesItem_t()
{}

bool AddReferencesItem_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool AddReferencesItem_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

uint32_t AddReferencesItem_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t AddReferencesItem_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_AddReferencesItem_Encoding_DefaultBinary;
}

IntrusivePtr_t<const NodeId_t> AddReferencesItem_t::SourceNodeId(void) const
{
	return sourceNodeId;
}

IntrusivePtr_t<NodeId_t>& AddReferencesItem_t::SourceNodeId(void)
{
	return sourceNodeId;
}

IntrusivePtr_t<const NodeId_t> AddReferencesItem_t::ReferenceTypeId(void) const
{
	return referenceTypeId;
}

IntrusivePtr_t<NodeId_t>& AddReferencesItem_t::ReferenceTypeId(void)
{
	return referenceTypeId;
}

const Boolean_t & AddReferencesItem_t::IsForward(void) const
{
	return isForward;
}

Boolean_t & AddReferencesItem_t::IsForward(void)
{
	return isForward;
}

const String_t & AddReferencesItem_t::TargetServerUri(void) const
{
	return targetServerUri;
}

String_t & AddReferencesItem_t::TargetServerUri(void)
{
	return targetServerUri;
}

const ExpandedNodeId_t & AddReferencesItem_t::TargetNodeId(void) const
{
	return targetNodeId;
}

ExpandedNodeId_t & AddReferencesItem_t::TargetNodeId(void)
{
	return targetNodeId;
}

const NodeClass_t & AddReferencesItem_t::TargetNodeClass(void) const
{
	return targetNodeClass;
}

NodeClass_t & AddReferencesItem_t::TargetNodeClass(void)
{
	return targetNodeClass;
}

} // namespace uasdk

#endif

