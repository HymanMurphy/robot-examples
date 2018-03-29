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

#include "opcua_browse_path_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(BrowsePath_t, Structure_t)

bool BrowsePath_t::operator==(BrowsePath_t const & obj) const
{
    return (
        Equal(startingNode, obj.startingNode)
        && (relativePath == obj.relativePath));
}

bool BrowsePath_t::operator>(BrowsePath_t const & obj) const
{
  return (
      GreaterThan(startingNode, obj.startingNode)
      && (relativePath > obj.relativePath));
}

Status_t BrowsePath_t::CopyFrom(const BrowsePath_t& source)
{
  if(!source.startingNode.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  Status_t status = source.startingNode->CopyToNodeId(startingNode);
  if (status.IsBad())
  {
    return status;
  }

  status = relativePath.CopyFrom(source.relativePath);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t BrowsePath_t::CopyFrom(const BaseDataType_t& source)
{
  const BrowsePath_t* ptr = RuntimeCast<const BrowsePath_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t BrowsePath_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  if(!startingNode.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadEncodingError);
  }

  Status_t status = startingNode->Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = relativePath.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t BrowsePath_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, BrowsePath_t& result)
{
  Status_t status = NodeId_t::Decode(buffer, decoder, result.StartingNode());
  if (status.IsBad())
  {
    return status;
  }

  status = ArrayUA_t<RelativePathElement_t>::Decode(buffer, decoder, result.RelativePath());
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

BrowsePath_t::~BrowsePath_t() 
{}

bool BrowsePath_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool BrowsePath_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t BrowsePath_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t BrowsePath_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t BrowsePath_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_BrowsePath_Encoding_DefaultBinary;
}

IntrusivePtr_t<const NodeId_t> BrowsePath_t::StartingNode(void) const 
{ 
  return startingNode; 
}

IntrusivePtr_t<NodeId_t>& BrowsePath_t::StartingNode(void) 
{ 
  return startingNode; 
}

const ArrayUA_t<RelativePathElement_t>& BrowsePath_t::RelativePath(void) const
{ 
  return relativePath; 
}

ArrayUA_t<RelativePathElement_t>& BrowsePath_t::RelativePath(void) 
{ 
  return relativePath; 
}

} // namespace uasdk
