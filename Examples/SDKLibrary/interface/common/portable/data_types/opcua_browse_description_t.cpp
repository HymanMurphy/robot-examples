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

#include "opcua_browse_description_t.h"
#include "icodec_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(BrowseDescription_t, Structure_t)

bool BrowseDescription_t::operator==(BrowseDescription_t const & obj) const
{
  return (
      Equal(nodeId, obj.nodeId)
      && (browseDirection == obj.browseDirection)
      && Equal(refTypeId, obj.refTypeId)
      && (includeSubtypes == obj.includeSubtypes)
      && (nodeclassMask == obj.nodeclassMask)
      && (resultMask == obj.resultMask));
}

bool BrowseDescription_t::operator>(BrowseDescription_t const & obj) const
{
  return (
      GreaterThan(nodeId, obj.nodeId)
      && (browseDirection > obj.browseDirection)
      && GreaterThan(refTypeId, obj.refTypeId)
      && (includeSubtypes > obj.includeSubtypes)
      && (nodeclassMask > obj.nodeclassMask)
      && (resultMask > obj.resultMask));
}

Status_t BrowseDescription_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

Status_t BrowseDescription_t::CopyFrom(const BrowseDescription_t& source)
{
  if(!source.nodeId.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  Status_t status = source.nodeId->CopyToNodeId(nodeId);
  if (status.IsBad())
  {
    return status;
  }

  status = browseDirection.CopyFrom(source.browseDirection);
  if (status.IsBad())
  {
    return status;
  }

  if(source.refTypeId.is_set())
  {
    status = source.refTypeId->CopyToNodeId(refTypeId);
    if (status.IsBad())
    {
      return status;
    }
  }
  else
  {
    refTypeId.reset();
  }

  status = includeSubtypes.CopyFrom(source.includeSubtypes);
  if (status.IsBad())
  {
    return status;
  }

  status = nodeclassMask.CopyFrom(source.nodeclassMask);
  if (status.IsBad())
  {
    return status;
  }

  status = resultMask.CopyFrom(source.resultMask);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t BrowseDescription_t::CopyFrom(const BaseDataType_t& source)
{
  const BrowseDescription_t* ptr = RuntimeCast<const BrowseDescription_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t BrowseDescription_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = OpcUa_Good;

  if(!nodeId.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadEncodingError);
  }

  status = nodeId->Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = browseDirection.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = encoder.Encode(refTypeId, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = includeSubtypes.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = nodeclassMask.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = resultMask.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t BrowseDescription_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, BrowseDescription_t& result)
{
  Status_t status = NodeId_t::Decode(buffer, decoder, result.NodeId());
  if (!result.NodeId().is_set() || (status.IsBad()))
  {
    return status;
  }

  status = BrowseDirection_t::Decode(buffer, decoder, result.BrowseDirection());
  if (status.IsBad())
  {
    return status;
  }

  status = NodeId_t::Decode(buffer, decoder, result.RefTypeId());
  if (status.IsBad())
  {
    return status;
  }

  status = Boolean_t::Decode(buffer, decoder, result.IncludeSubtypes());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.NodeclassMask());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.ResultMask());
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

bool BrowseDescription_t::FilterNodeClass( NodeClass_t::Enum_t node_class ) const
{
  if (this->nodeclassMask.Value() == 0)
  {
    return true;
  }

  switch (node_class)
  {
  case NodeClass_t::OPCUA_NODECLASS_OBJECT:
  	return ((nodeclassMask.Value() & NodeClass_t::OPCUA_NODECLASS_OBJECT) != 0);

  case NodeClass_t::OPCUA_NODECLASS_VARIABLE:
    return ((nodeclassMask.Value() & NodeClass_t::OPCUA_NODECLASS_VARIABLE) != 0);

  case NodeClass_t::OPCUA_NODECLASS_METHOD:
    return ((nodeclassMask.Value() & NodeClass_t::OPCUA_NODECLASS_METHOD) != 0);

  case NodeClass_t::OPCUA_NODECLASS_OBJECT_TYPE:
    return ((nodeclassMask.Value() & NodeClass_t::OPCUA_NODECLASS_OBJECT_TYPE) != 0);

  case NodeClass_t::OPCUA_NODECLASS_VARIABLE_TYPE:
    return ((nodeclassMask.Value() & NodeClass_t::OPCUA_NODECLASS_VARIABLE_TYPE) != 0);

  case NodeClass_t::OPCUA_NODECLASS_REFERENCE_TYPE:
    return ((nodeclassMask.Value() & NodeClass_t::OPCUA_NODECLASS_REFERENCE_TYPE) != 0);

  case NodeClass_t::OPCUA_NODECLASS_DATA_TYPE:
    return ((nodeclassMask.Value() & NodeClass_t::OPCUA_NODECLASS_DATA_TYPE) != 0);

  case NodeClass_t::OPCUA_NODECLASS_VIEW:
    return ((nodeclassMask.Value() & NodeClass_t::OPCUA_NODECLASS_VIEW) != 0);

  default:
    return false;
  }
}

BrowseDescription_t::~BrowseDescription_t() 
{}

bool BrowseDescription_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool BrowseDescription_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

uint32_t BrowseDescription_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t BrowseDescription_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_BrowseDescription_Encoding_DefaultBinary;
}

IntrusivePtr_t<const NodeId_t> BrowseDescription_t::NodeId(void) const 
{
  return nodeId; 
}

IntrusivePtr_t<NodeId_t>& BrowseDescription_t::NodeId(void) 
{ 
  return nodeId; 
}

const BrowseDirection_t& BrowseDescription_t::BrowseDirection(void) const 
{
  return browseDirection; 
}

BrowseDirection_t& BrowseDescription_t::BrowseDirection(void) 
{
  return browseDirection; 
}

IntrusivePtr_t<const NodeId_t> BrowseDescription_t::RefTypeId(void) const 
{
  return refTypeId; 
}

IntrusivePtr_t<NodeId_t>& BrowseDescription_t::RefTypeId(void)
{
  return refTypeId; 
}

const Boolean_t& BrowseDescription_t::IncludeSubtypes(void) const 
{
  return includeSubtypes; 
}

Boolean_t& BrowseDescription_t::IncludeSubtypes(void)
{
  return includeSubtypes; 
}

const UInt32_t& BrowseDescription_t::NodeclassMask(void) const 
{
  return nodeclassMask; 
}

UInt32_t& BrowseDescription_t::NodeclassMask(void) 
{
  return nodeclassMask;
}

const UInt32_t& BrowseDescription_t::ResultMask(void) const 
{ 
  return resultMask; 
}

UInt32_t& BrowseDescription_t::ResultMask(void) 
{ 
  return resultMask; 
}

}
