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

#include "opcua_reference_description_t.h"
#include "opcua_datatype_utilities_t.h"
#include "icodec_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(ReferenceDescription_t, Structure_t)

bool ReferenceDescription_t::operator==(ReferenceDescription_t const & obj) const
{
  return (
      Equal(refTypeId, obj.refTypeId)
      && (isForward == obj.isForward)
      && (nodeId == obj.nodeId)
      && (browseName == obj.browseName)
      && (displayName == obj.displayName)
      && (nodeclass == obj.nodeclass)
      && (typeDefinition == obj.typeDefinition));
}

bool ReferenceDescription_t::operator>(ReferenceDescription_t const & obj) const
{
  return (
      GreaterThan(refTypeId, obj.refTypeId)
      && (isForward > obj.isForward)
      && (nodeId > obj.nodeId)
      && (browseName > obj.browseName)
      && (displayName > obj.displayName)
      && (nodeclass > obj.nodeclass)
      && (typeDefinition > obj.typeDefinition));
}

Status_t ReferenceDescription_t::CopyFrom(const BaseDataType_t& source)
{
  const ReferenceDescription_t* ptr = RuntimeCast<const ReferenceDescription_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t ReferenceDescription_t::CopyFrom(const ReferenceDescription_t& source)
{
  if(!source.refTypeId.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  Status_t status = source.refTypeId->CopyToNodeId(refTypeId);
  if (status.IsBad())
  {
    return status;
  }

  status = isForward.CopyFrom(source.isForward);
  if (status.IsBad())
  {
    return status;
  }

  status = nodeId.CopyFrom(source.nodeId);
  if (status.IsBad())
  {
    return status;
  }

  status = browseName.CopyFrom(source.browseName);
  if (status.IsBad())
  {
    return status;
  }

  status = displayName.CopyFrom(source.displayName);
  if (status.IsBad())
  {
    return status;
  }

  status = nodeclass.CopyFrom(source.nodeclass);
  if (status.IsBad())
  {
    return status;
  }

  status = typeDefinition.CopyFrom(source.typeDefinition);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t ReferenceDescription_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status;

  status = encoder.Encode(refTypeId, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = isForward.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = nodeId.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = browseName.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = displayName.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = nodeclass.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = typeDefinition.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t ReferenceDescription_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, ReferenceDescription_t& result)
{
  Status_t status = NodeId_t::Decode(buffer, decoder, result.RefTypeId());
  if (status.IsBad())
  {
    return status;
  }

  status = Boolean_t::Decode(buffer, decoder, result.IsForward());
  if (status.IsBad())
  {
    return status;
  }

  status = result.NodeId().Decode(buffer, decoder, result.NodeId());
  if (status.IsBad())
  {
    return status;
  }

  status = QualifiedName_t::Decode(buffer, decoder, result.BrowseName());
  if (status.IsBad())
  {
    return status;
  }

  status = LocalizedText_t::Decode(buffer, decoder, result.DisplayName());
  if (status.IsBad())
  {
    return status;
  }

  status = NodeClass_t::Decode(buffer, decoder, result.Nodeclass());
  if (status.IsBad())
  {
    return status;
  }

  status = result.TypeDefinition().Decode(buffer, decoder, result.TypeDefinition());
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

ReferenceDescription_t::~ReferenceDescription_t()
{}

bool ReferenceDescription_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool ReferenceDescription_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t ReferenceDescription_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t ReferenceDescription_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t ReferenceDescription_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_ReferenceDescription_Encoding_DefaultBinary;
}

IntrusivePtr_t<const NodeId_t> ReferenceDescription_t::RefTypeId(void) const
{
  return refTypeId;
}

IntrusivePtr_t<NodeId_t>& ReferenceDescription_t::RefTypeId(void)
{
  return refTypeId;
}

const Boolean_t& ReferenceDescription_t::IsForward(void) const
{
  return isForward;
}

Boolean_t& ReferenceDescription_t::IsForward(void)
{
  return isForward;
}

const ExpandedNodeId_t& ReferenceDescription_t::NodeId(void) const
{
  return nodeId;
}

ExpandedNodeId_t& ReferenceDescription_t::NodeId(void)
{
  return nodeId;
}

const QualifiedName_t& ReferenceDescription_t::BrowseName(void) const
{
  return browseName;
}

QualifiedName_t& ReferenceDescription_t::BrowseName(void)
{
  return browseName;
}

const LocalizedText_t& ReferenceDescription_t::DisplayName(void) const
{
  return displayName;
}

LocalizedText_t& ReferenceDescription_t::DisplayName(void)
{
  return displayName;
}

const NodeClass_t& ReferenceDescription_t::Nodeclass(void) const
{
  return nodeclass;
}

NodeClass_t& ReferenceDescription_t::Nodeclass(void)
{
  return nodeclass;
}

const ExpandedNodeId_t& ReferenceDescription_t::TypeDefinition(void) const
{
  return typeDefinition;
}

ExpandedNodeId_t& ReferenceDescription_t::TypeDefinition(void)
{
  return typeDefinition;
}

} // namespace uasdk

