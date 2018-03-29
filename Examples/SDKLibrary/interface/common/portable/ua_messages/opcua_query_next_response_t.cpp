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

#include "opcua_query_next_response_t.h"

#if (UASDK_INCLUDE_QUERY_SERVICE_SET > 0)

namespace uasdk
{
	const ArrayUA_t<QueryDataSet_t>& QueryNextResponse_t::QueryDataSets() const
	{
		return queryDataSets;
	}
	ArrayUA_t<QueryDataSet_t>& QueryNextResponse_t::QueryDataSets()
	{
		return queryDataSets;
	}
	const BrowseContinuationPoint_t & QueryNextResponse_t::RevisedContinuationPoint() const
	{
		return revisedContinuationPoint;
	}
	BrowseContinuationPoint_t & QueryNextResponse_t::RevisedContinuationPoint()
	{
		return revisedContinuationPoint;
	}
	Status_t QueryNextResponse_t::EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const
{
#if (UASDK_INCLUDE_SERVER > 0)
  Status_t status = queryDataSets.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = revisedContinuationPoint.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return 0;
#else
  UASDK_RETURN_BAD_STATUS(OpcUa_BadNotImplemented);
#endif  //(UASDK_INCLUDE_SERVER > 0)
}

Status_t QueryNextResponse_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, QueryNextResponse_t& result)
{
#if (UASDK_INCLUDE_CLIENT > 0)
  Status_t status = result.DecodeHeader(buffer, decoder);
  if (status.IsBad())
  {
    return status;
  }

  status = ArrayUA_t<QueryDataSet_t>::Decode(buffer, decoder, result.QueryDataSets());
  if (status.IsBad())
  {
    return status;
  }

  status = BrowseContinuationPoint_t::Decode(buffer, decoder, result.RevisedContinuationPoint());
  if (status.IsBad())
  {
    return status;
  }

  return 0;
#else
  UASDK_UNUSED(buffer);
  UASDK_UNUSED(decoder);
  UASDK_UNUSED(result);
  UASDK_RETURN_BAD_STATUS(OpcUa_BadNotImplemented);
#endif  //(UASDK_INCLUDE_CLIENT > 0)
}

} // namespace uasdk

#endif

