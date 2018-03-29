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

#include "opcua_query_next_request_t.h"

#if (UASDK_INCLUDE_QUERY_SERVICE_SET > 0)

namespace uasdk
{
	const Boolean_t & QueryNextRequest_t::ReleaseContinuationPoint() const
	{
		return releaseContinuationPoint;
	}
	Boolean_t & QueryNextRequest_t::ReleaseContinuationPoint()
	{
		return releaseContinuationPoint;
	}
	const BrowseContinuationPoint_t & QueryNextRequest_t::ContinuationPoint() const
	{
		return continuationPoint;
	}
	BrowseContinuationPoint_t & QueryNextRequest_t::ContinuationPoint()
	{
		return continuationPoint;
	}
	
	Status_t QueryNextRequest_t::EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const
	{
	#if (UASDK_INCLUDE_CLIENT > 0)

	  Status_t status = releaseContinuationPoint.Encode(encoder, buffer);
	  if (status.IsBad())
	  {
		return status;
	  }

	  status = continuationPoint.Encode(encoder, buffer);
	  if (status.IsBad())
	  {
		  return status;
	  }
	  return 0;
	#else
	  UASDK_UNUSED(encoder);
	  UASDK_UNUSED(buffer);
	  UASDK_RETURN_BAD_STATUS(OpcUa_BadNotImplemented);
	#endif  // (UASDK_INCLUDE_CLIENT > 0)
	}

Status_t QueryNextRequest_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, QueryNextRequest_t& result)
{
#if (UASDK_INCLUDE_SERVER > 0)
  Status_t status = result.DecodeHeader(buffer, decoder);
  if (status.IsBad())
  {
    return status;
  }

  status = Boolean_t::Decode(buffer, decoder, result.ReleaseContinuationPoint());
  if (status.IsBad())
  {
    return status;
  }

  status = BrowseContinuationPoint_t::Decode(buffer, decoder, result.ContinuationPoint());
  if (status.IsBad())
  {
	  return status;
  }
  return 0;
#else
  UASDK_RETURN_BAD_STATUS(OpcUa_BadNotImplemented);
#endif  // (UASDK_INCLUDE_SERVER > 0)
}

} // namespace uasdk

#endif

