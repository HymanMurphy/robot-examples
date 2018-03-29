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

#include "opcua_browse_result_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(BrowseResult_t, Structure_t)

bool BrowseResult_t::operator==(BrowseResult_t const & obj) const
{
  return (
      (statusCode == obj.statusCode)
      && Equal(continuationPoint, obj.continuationPoint)
      && (references == obj.references));
}

bool BrowseResult_t::operator>(BrowseResult_t const & obj) const
{
  return (
      (statusCode > obj.statusCode)
      && GreaterThan(continuationPoint, obj.continuationPoint)
      && (references > obj.references));
}

Status_t BrowseResult_t::CopyFrom(const BrowseResult_t& source)
{
  Status_t status = statusCode.CopyFrom(source.statusCode);
  if (status.IsBad())
  {
    return status;
  }

  if (!source.continuationPoint.is_set())
  {
    continuationPoint.reset();
  }
  else
  {
    if (!continuationPoint.is_set())
    {
      continuationPoint = new SafeRefCount_t<ByteString_t>();
      if (!continuationPoint.is_set())
      {
        return OpcUa_BadOutOfMemory;
      }
    }
    status = continuationPoint->CopyFrom(*source.continuationPoint);
    if (status.IsBad())
    {
      return status;
    }
  }

  status = references.CopyFrom(source.references);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t BrowseResult_t::CopyFrom(const BaseDataType_t& source)
{
  const BrowseResult_t* ptr = RuntimeCast<const BrowseResult_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t BrowseResult_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = statusCode.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  if (!continuationPoint.is_set())
  {
    ByteString_t emptyContinuationPoint;
    status = emptyContinuationPoint.Encode(encoder, buffer);
  }
  else
  {
    status = continuationPoint->Encode(encoder, buffer);
  }
  if (status.IsBad())
  {
    return status;
  }

  status = references.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t BrowseResult_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, BrowseResult_t& result)
{
  Status_t status = StatusCode_t::Decode(buffer, decoder, result.StatusCode());
  if (status.IsBad())
  {
    return status;
  }

  result.ContinuationPoint() = new SafeRefCount_t<ByteString_t>();
  if (!result.ContinuationPoint().is_set())
  {
    return OpcUa_BadOutOfMemory;
  }
  status = ByteString_t::Decode(buffer, decoder, *result.ContinuationPoint());
  if (status.IsBad())
  {
    return status;
  }
  if (result.ContinuationPoint()->IsNull() || (result.ContinuationPoint()->Length() == 0))
  {
    result.ContinuationPoint().reset();
  }

  status = ArrayUA_t<ReferenceDescription_t>::Decode(buffer, decoder, result.References());
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

BrowseResult_t::~BrowseResult_t() 
{}

bool BrowseResult_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool BrowseResult_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t BrowseResult_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t BrowseResult_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t BrowseResult_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_BrowseResult_Encoding_DefaultBinary;
}

const StatusCode_t& BrowseResult_t::StatusCode(void) const 
{
  return statusCode; 
}

StatusCode_t& BrowseResult_t::StatusCode(void) 
{
  return statusCode; 
}

IntrusivePtr_t<const ByteString_t> BrowseResult_t::ContinuationPoint(void) const
{
  return continuationPoint; 
}

IntrusivePtr_t<ByteString_t>& BrowseResult_t::ContinuationPoint(void)
{
  return continuationPoint; 
}

const ArrayUA_t<ReferenceDescription_t>& BrowseResult_t::References(void) const
{
  return references; 
}

ArrayUA_t<ReferenceDescription_t>& BrowseResult_t::References(void) 
{
  return references; 
}

} // namespace uasdk
