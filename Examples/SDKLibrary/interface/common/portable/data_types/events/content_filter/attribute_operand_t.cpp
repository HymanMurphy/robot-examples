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

#include "attribute_operand_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(AttributeOperand_t, FilterOperand_t);

AttributeOperand_t::AttributeOperand_t()
{
}

AttributeOperand_t::~AttributeOperand_t()
{
}

bool AttributeOperand_t::operator==(BaseDataType_t const & obj) const
{
	return OperatorEqualTo(*this, obj);
}

bool AttributeOperand_t::operator==(AttributeOperand_t const & obj) const
{
  return (
    (nodeId == obj.nodeId)
    &&(alias == obj.alias)
    &&(browsePath == obj.browsePath)
    &&(attributeId == obj.attributeId)
    &&(indexRange == obj.indexRange));
}

bool AttributeOperand_t::operator>(BaseDataType_t const & obj) const
{
	return OperatorGreaterThan(*this, obj);
}

bool AttributeOperand_t::operator>(AttributeOperand_t const & obj) const
{
  return (
    (nodeId > obj.nodeId)
    &&(alias > obj.alias)
    &&(browsePath > obj.browsePath)
    &&(attributeId > obj.attributeId)
    &&(indexRange > obj.indexRange));
}

Status_t AttributeOperand_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
	return CopyToDestination(*this, destination);
}

Status_t AttributeOperand_t::CopyFrom(const BaseDataType_t& source)
{
	IntrusivePtr_t<const AttributeOperand_t> ptr = RuntimeCast<const AttributeOperand_t *>(source);
  if (!ptr.is_set())
  {
    return OpcUa_BadTypeMismatch;
  }

  return CopyFrom(*ptr);
}

Status_t AttributeOperand_t::CopyFrom(const AttributeOperand_t& source)
{
  if( (!source.nodeId.is_set()))
  {
    return OpcUa_BadUnexpectedError;
  }

  Status_t status = source.nodeId->CopyToNodeId(nodeId);
  if (status.IsBad())
  {
    return status;
  }

  status = alias.CopyFrom(source.alias);
  if (status.IsBad())
  {
    return status;
  }

  status = browsePath.CopyFrom(source.browsePath);
  if (status.IsBad())
  {
    return status;
  }

  status = attributeId.CopyFrom(source.attributeId);
  if (status.IsBad())
  {
    return status;
  }

  status = indexRange.CopyFrom(source.indexRange);
  if (status.IsBad())
  {
    return status;
  }
  return OpcUa_Good;
}

uint32_t AttributeOperand_t::TypeId(uint16_t& namespaceIndex)  const
{
	namespaceIndex = 0; return TYPE_ID;
}

IntrusivePtr_t<const NodeId_t> AttributeOperand_t::NodeId() const
{ 
	return nodeId;
}

IntrusivePtr_t<NodeId_t>& AttributeOperand_t::NodeId() 
{ 
	return nodeId;
}

const String_t& AttributeOperand_t::Alias() const 
{ 
	return alias; 
}

String_t& AttributeOperand_t::Alias()
{ 
	return alias;
}

const ArrayUA_t<RelativePathElement_t>& AttributeOperand_t::BrowsePath() const 
{ 
	return browsePath; 
}

ArrayUA_t<RelativePathElement_t>& AttributeOperand_t::BrowsePath()
{ 
	return browsePath; 
}

const IntegerId_t& AttributeOperand_t::AttributeId() const 
{
	return attributeId;
}

IntegerId_t& AttributeOperand_t::AttributeId() 
{ 
	return attributeId;
}

const String_t& AttributeOperand_t::IndexRange() const 
{ 
	return indexRange;
}

String_t& AttributeOperand_t::IndexRange() 
{ 
	return indexRange;
}

uint32_t AttributeOperand_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
	namespaceIndex = 0; return OpcUaId_AttributeOperand_Encoding_DefaultBinary;
}

Status_t AttributeOperand_t::GetValue(const INode_t& node, IContentFilter_t* filter, IntrusivePtr_t<IAttributeAccess_t>& eventAttributes, IntrusivePtr_t<IServerConfiguration_t> configuration, IntrusivePtr_t<BaseDataType_t>& value, IntrusivePtr_t<ContentFilterElementResult_t>& elementResult, bool diagnosticsRequested)
{
	UASDK_UNUSED(node);
	UASDK_UNUSED(filter);
	UASDK_UNUSED(eventAttributes);
	UASDK_UNUSED(configuration);
	UASDK_UNUSED(value);
	UASDK_UNUSED(elementResult);
	UASDK_UNUSED(diagnosticsRequested);
	return OpcUa_BadNotImplemented;
}

Status_t AttributeOperand_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = OpcUa_Good;

  if (!nodeId.is_set())
  {
    return OpcUa_BadEncodingError;
  }

  status = nodeId->Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = alias.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = browsePath.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = attributeId.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = indexRange.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t AttributeOperand_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, IntrusivePtr_t<AttributeOperand_t>& result)
{
	if (!result.is_set())
	{
		result = new SafeRefCount_t<AttributeOperand_t>();
		if (!result.is_set())
		{
			return OpcUa_BadOutOfMemory;
		}
	}

  Status_t status = NodeId_t::Decode(buffer, decoder, result->NodeId());
  if (status.IsBad())
  {
    return status;
  }

  status = String_t::Decode(buffer, decoder, result->Alias());
  if (status.IsBad())
  {
    return status;
  }

  status = ArrayUA_t<RelativePathElement_t>::Decode(buffer, decoder, result->BrowsePath());
  if (status.IsBad())
  {
    return status;
  }

  status = IntegerId_t::Decode(buffer, decoder, result->AttributeId());
  if (status.IsBad())
  {
    return status;
  }

  status = String_t::Decode(buffer, decoder, result->IndexRange());
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}
	
} // namespace uasdke

#endif // UASDK_INCLUDE_EVENTS
