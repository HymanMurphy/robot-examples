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

#include "opcua_browse_continuation_point_t.h"
#include "opcua_datatype_utilities_t.h"
#include "wrap_buffer_t.h"
#include "icodec_t.h"
#include "opcua_node_id_numeric_t.h"
#include "ua_binary_codec_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(BrowseContinuationPoint_t, ByteString_t)

bool BrowseContinuationPoint_t::operator==(BrowseContinuationPoint_t const & obj) const
{
  return (Equal(viewId, obj.viewId)
      && (nodeToBrowse == obj.nodeToBrowse)
      && (maxRefsPerNode == obj.maxRefsPerNode)
      && (startingRefIndex == obj.startingRefIndex)
      && (isValid == obj.isValid));
}

bool BrowseContinuationPoint_t::operator>(BrowseContinuationPoint_t const & obj) const
{
  return (
      GreaterThan(viewId, obj.viewId)
      && (nodeToBrowse > obj.nodeToBrowse)
      && (maxRefsPerNode > obj.maxRefsPerNode)
      && (startingRefIndex > obj.startingRefIndex)
      && (isValid > obj.isValid));
}

Status_t BrowseContinuationPoint_t::CopyFrom(const BrowseContinuationPoint_t& source)
{
  Status_t status;

  if(source.viewId.is_set())
  {
    status = source.viewId->CopyToNodeId(viewId);
    if (status.IsBad())
    {
      return status;
    }
  }
  else
  {
    viewId.reset();
  }

  status = nodeToBrowse.CopyFrom(source.nodeToBrowse);
  if (status.IsBad())
  {
    return status;
  }

  status = maxRefsPerNode.CopyFrom(source.maxRefsPerNode);
  if (status.IsBad())
  {
    return status;
  }

  status = startingRefIndex.CopyFrom(source.startingRefIndex);
  if (status.IsBad())
  {
    return status;
  }

  isValid = source.isValid;

  return status;
}

Status_t BrowseContinuationPoint_t::CopyFrom(const BaseDataType_t& source)
{
  const BrowseContinuationPoint_t* ptr = RuntimeCast<const BrowseContinuationPoint_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

uasdk::Status_t BrowseContinuationPoint_t::CopyFrom(const ByteString_t& source)
{
  return ByteString_t::CopyFrom(source);
}

Status_t BrowseContinuationPoint_t::Configure(IntrusivePtr_t<NodeId_t>& viewId_, BrowseDescription_t& nodeToBrowse_,
                   uint32_t maxRefsPerNode_, uint32_t startingRefIndex_)
{
  Status_t status = 0;

  if (viewId_.is_set())
  {
    status = viewId_->CopyToNodeId(viewId);
    if (status.IsBad())
    {
      return status;
    }
  }
  else
  {
    viewId = new SafeRefCount_t<NodeIdNumeric_t>();
    if (!viewId.is_set())
    {
      return OpcUa_BadOutOfMemory;
    }
  }

  status = nodeToBrowse.CopyFrom(nodeToBrowse_);
  if (status.IsBad())
  {
    return status;
  }

  status = maxRefsPerNode.CopyFrom(maxRefsPerNode_);
  if (status.IsBad())
  {
    return status;
  }

  status = startingRefIndex.CopyFrom(startingRefIndex_);
  if (status.IsBad())
  {
    return status;
  }

  isValid = true;

  return status;
}

uasdk::Status_t BrowseContinuationPoint_t::DecodeAndValidate(void)
{
  isValid = false;
  if (Length() <= 0)
  {
    return OpcUa_Good;
  }

  WrapBuffer_t tempBuf(Data(), Length());
  tempBuf.WriteIndex(Length());

  UABinaryCodec_t decoder;

  Status_t status = NodeId_t::Decode(tempBuf, decoder, ViewId());
  if (!ViewId().is_set() || (status.IsBad()))
  {
    return status;
  }

  status = BrowseDescription_t::Decode(tempBuf, decoder, NodeToBrowse());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(tempBuf, decoder, MaxRefsPerNode());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(tempBuf, decoder, StartingRefIndex());
  if (status.IsBad())
  {
    return status;
  }

  Initialise(0);
  isValid = true;
  return status;
}

Status_t BrowseContinuationPoint_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status;

  if (!isValid)
  {
    return ByteString_t::Encode(encoder, buffer);
  }

  uint32_t lengthIndex = buffer.WriteIndex();

  UInt32_t length;
  status = length.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = encoder.Encode(viewId, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = nodeToBrowse.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = maxRefsPerNode.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = startingRefIndex.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  uint32_t endIndex = buffer.WriteIndex();
  buffer.WriteIndex(lengthIndex);

  length = endIndex - (lengthIndex + sizeof(uint32_t));
  status = length.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  buffer.WriteIndex(endIndex);

  return status;
}

BrowseContinuationPoint_t::BrowseContinuationPoint_t() 
  : isValid(false) 
{}

BrowseContinuationPoint_t::~BrowseContinuationPoint_t() 
{ }

bool BrowseContinuationPoint_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool BrowseContinuationPoint_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

IntrusivePtr_t<const NodeId_t> BrowseContinuationPoint_t::ViewId(void) const
{
  return viewId; 
}

IntrusivePtr_t<NodeId_t>& BrowseContinuationPoint_t::ViewId(void) 
{ 
  return viewId; 
}

const BrowseDescription_t& BrowseContinuationPoint_t::NodeToBrowse(void) const 
{ 
  return nodeToBrowse; 
}

BrowseDescription_t& BrowseContinuationPoint_t::NodeToBrowse(void) 
{
  return nodeToBrowse; 
}

const UInt32_t& BrowseContinuationPoint_t::MaxRefsPerNode(void) const
{ return maxRefsPerNode; }

UInt32_t& BrowseContinuationPoint_t::MaxRefsPerNode(void) 
{
  return maxRefsPerNode; 
}

const UInt32_t& BrowseContinuationPoint_t::StartingRefIndex(void) const
{
  return startingRefIndex; 
}

UInt32_t& BrowseContinuationPoint_t::StartingRefIndex(void) 
{ 
  return startingRefIndex; 
}

bool BrowseContinuationPoint_t::IsValid(void) const 
{ 
  return isValid; 
}

void BrowseContinuationPoint_t::IsValid(bool value)
{
  isValid = value; 
}

Status_t BrowseContinuationPoint_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t BrowseContinuationPoint_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

} // namespace uasdk
