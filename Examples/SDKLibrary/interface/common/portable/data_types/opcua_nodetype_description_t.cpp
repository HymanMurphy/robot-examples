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

#include "opcua_nodetype_description_t.h"
#include "opcua_extensible_parameter_t.h"

#if (UASDK_INCLUDE_QUERY_SERVICE_SET > 0)

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(NodeTypeDescription_t, Structure_t)

bool NodeTypeDescription_t::operator==(NodeTypeDescription_t const & obj) const
{
  return (
      (typeDefinitionNode == obj.typeDefinitionNode)
      && (includeSubtypes == obj.includeSubtypes)
      && (dataToReturn == obj.dataToReturn));
}

bool NodeTypeDescription_t::operator>(NodeTypeDescription_t const & obj) const
{
  return (
	  (typeDefinitionNode > obj.typeDefinitionNode)
	  && (includeSubtypes > obj.includeSubtypes)
	  && (dataToReturn > obj.dataToReturn));
}

Status_t NodeTypeDescription_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

Status_t NodeTypeDescription_t::CopyFrom(const NodeTypeDescription_t& source)
{
  Status_t status = typeDefinitionNode.CopyFrom(source.typeDefinitionNode);

  if (status.IsBad())
  {
    return status;
  }

  status = includeSubtypes.CopyFrom(source.includeSubtypes);
  if (status.IsBad())
  {
    return status;
  }

  status = dataToReturn.CopyFrom(source.dataToReturn);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t NodeTypeDescription_t::CopyFrom(const BaseDataType_t& source)
{
  const NodeTypeDescription_t* ptr = RuntimeCast<const NodeTypeDescription_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t NodeTypeDescription_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = typeDefinitionNode.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = includeSubtypes.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = dataToReturn.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t NodeTypeDescription_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, NodeTypeDescription_t& result)
{
  Status_t status = ExpandedNodeId_t::Decode(buffer, decoder, result.TypeDefinitionNode());
  if (status.IsBad())
  {
    return status;
  }

  status = Boolean_t::Decode(buffer, decoder, result.IncludeSubtypes());
  if (status.IsBad())
  {
    return status;
  }

  status = ArrayUA_t<QueryDataDescription_t>::Decode(buffer, decoder, result.DataToReturn());
  if (status.IsBad())
  {
    return status;
  }
  return status;
}

NodeTypeDescription_t::~NodeTypeDescription_t()
{}

bool NodeTypeDescription_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool NodeTypeDescription_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

uint32_t NodeTypeDescription_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t NodeTypeDescription_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_NodeTypeDescription_Encoding_DefaultBinary;
}

const uasdk::ExpandedNodeId_t& NodeTypeDescription_t::TypeDefinitionNode() const
{
	return typeDefinitionNode;
}

uasdk::ExpandedNodeId_t& NodeTypeDescription_t::TypeDefinitionNode()
{
	return typeDefinitionNode;
}

const uasdk::Boolean_t& NodeTypeDescription_t::IncludeSubtypes(void) const
{
	return includeSubtypes;
}

uasdk::Boolean_t& NodeTypeDescription_t::IncludeSubtypes(void)
{
	return includeSubtypes;
}

const uasdk::ArrayUA_t<uasdk::QueryDataDescription_t>& NodeTypeDescription_t::DataToReturn(void) const
{
	return dataToReturn;
}

uasdk::ArrayUA_t<uasdk::QueryDataDescription_t>& NodeTypeDescription_t::DataToReturn(void)
{
	return dataToReturn;
}

} // namespace uasdk

#endif
