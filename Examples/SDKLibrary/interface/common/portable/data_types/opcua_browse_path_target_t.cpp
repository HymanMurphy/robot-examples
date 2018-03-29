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

#include "opcua_browse_path_target_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(BrowsePathTarget_t, Structure_t)

bool BrowsePathTarget_t::operator==(BrowsePathTarget_t const & obj) const
{
  return (
      (targetId == obj.targetId)
      && (remainingPathIndex == obj.remainingPathIndex));
}

bool BrowsePathTarget_t::operator>(BrowsePathTarget_t const & obj) const
{
  return (
      (targetId > obj.targetId)
      && (remainingPathIndex > obj.remainingPathIndex));
}

Status_t BrowsePathTarget_t::CopyFrom(const BrowsePathTarget_t& source)
{
  Status_t status = targetId.CopyFrom(source.targetId);
  if (status.IsBad())
  {
    return status;
  }

  status = remainingPathIndex.CopyFrom(source.remainingPathIndex);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t BrowsePathTarget_t::CopyFrom(const BaseDataType_t& source)
{
  const BrowsePathTarget_t* ptr = RuntimeCast<const BrowsePathTarget_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t BrowsePathTarget_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = targetId.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = remainingPathIndex.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t BrowsePathTarget_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, BrowsePathTarget_t& result)
{
  Status_t status = ExpandedNodeId_t::Decode(buffer, decoder, result.TargetId());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.RemainingPathIndex());
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

BrowsePathTarget_t::~BrowsePathTarget_t() {}

bool BrowsePathTarget_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool BrowsePathTarget_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t BrowsePathTarget_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t BrowsePathTarget_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t BrowsePathTarget_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_BrowsePathTarget_Encoding_DefaultBinary;
}

const ExpandedNodeId_t& BrowsePathTarget_t::TargetId(void) const
{ 
  return targetId; 
}

ExpandedNodeId_t& BrowsePathTarget_t::TargetId(void) 
{ 
  return targetId; 
}

const UInt32_t& BrowsePathTarget_t::RemainingPathIndex(void) const 
{ 
  return remainingPathIndex; 
}

UInt32_t& BrowsePathTarget_t::RemainingPathIndex(void) 
{ 
  return remainingPathIndex; 
}


} // namespace uasdk
