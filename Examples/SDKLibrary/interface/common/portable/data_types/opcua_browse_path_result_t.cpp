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

#include "opcua_browse_path_result_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(BrowsePathResult_t, Structure_t)

bool BrowsePathResult_t::operator==(BrowsePathResult_t const & obj) const
{
  return (
      (statusCode == obj.statusCode)
      && (targets == obj.targets));
}

bool BrowsePathResult_t::operator>(BrowsePathResult_t const & obj) const
{
  return (
      (statusCode > obj.statusCode)
      && (targets > obj.targets));
}

Status_t BrowsePathResult_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

Status_t BrowsePathResult_t::CopyFrom(const BrowsePathResult_t& source)
{
  Status_t status = statusCode.CopyFrom(source.statusCode);

  if (status.IsBad())
  {
    return status;
  }

  status = targets.CopyFrom(source.targets);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t BrowsePathResult_t::CopyFrom(const BaseDataType_t& source)
{
  const BrowsePathResult_t* ptr = RuntimeCast<const BrowsePathResult_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t BrowsePathResult_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = statusCode.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = targets.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t BrowsePathResult_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, BrowsePathResult_t& result)
{
  Status_t status = StatusCode_t::Decode(buffer, decoder, result.StatusCode());
  if (status.IsBad())
  {
    return status;
  }

  status = ArrayUA_t<BrowsePathTarget_t>::Decode(buffer, decoder, result.Targets());
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

BrowsePathResult_t::~BrowsePathResult_t() 
{}

bool BrowsePathResult_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool BrowsePathResult_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

uint32_t BrowsePathResult_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t BrowsePathResult_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_BrowsePathResult_Encoding_DefaultBinary;
}

const StatusCode_t& BrowsePathResult_t::StatusCode(void) const
{ 
  return statusCode; 
}

StatusCode_t& BrowsePathResult_t::StatusCode(void)
{
  return statusCode; 
}

const ArrayUA_t<BrowsePathTarget_t>& BrowsePathResult_t::Targets(void) const 
{
  return targets; 
}

ArrayUA_t<BrowsePathTarget_t>& BrowsePathResult_t::Targets(void) 
{ 
  return targets; 
}

} // namespace uasdk
