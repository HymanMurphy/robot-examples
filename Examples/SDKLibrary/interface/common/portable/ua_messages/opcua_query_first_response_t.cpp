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

#include "opcua_query_first_response_t.h"

#if (UASDK_INCLUDE_QUERY_SERVICE_SET > 0)

namespace uasdk
{

Status_t QueryFirstResponse_t::EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const
{
#if (UASDK_INCLUDE_SERVER > 0)
  Status_t status = queryDataSets.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = continuationPoint.Encode(encoder, buffer);
  if (status.IsBad())
  {
	  return status;
  }

  status = parsingResults.Encode(encoder, buffer);
  if (status.IsBad())
  {
	  return status;
  }

  status = diagnosticInfos.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  //TODO
//   status = filterResult.Encode(encoder, buffer);
//   if (status.IsBad())
//   {
// 	  return status;
//   }

  return 0;
#else
  UASDK_RETURN_BAD_STATUS(OpcUa_BadNotImplemented);
#endif  //(UASDK_INCLUDE_SERVER > 0)
}

Status_t QueryFirstResponse_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, QueryFirstResponse_t& result)
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

  status = BrowseContinuationPoint_t::Decode(buffer, decoder, result.ContinuationPoint());
  if (status.IsBad())
  {
    return status;
  }

  status = ArrayUA_t<ParsingResult_t>::Decode(buffer, decoder, result.ParsingResults());
  if (status.IsBad())
  {
	  return status;
  }

  status = ArrayUA_t<DiagnosticInfo_t>::Decode(buffer, decoder, result.DiagnosticInfos());
  if (status.IsBad())
  {
	  return status;
  }

  //TODO
//   status = ContentFilterResult_t::Decode(buffer, decoder, result.FilterResult());
//   if (status.IsBad())
//   {
// 	  return status;
//   }

  return 0;
#else
  UASDK_UNUSED(buffer);
  UASDK_UNUSED(decoder);
  UASDK_UNUSED(result);
  UASDK_RETURN_BAD_STATUS(OpcUa_BadNotImplemented);
#endif  //(UASDK_INCLUDE_CLIENT > 0)
}

const ArrayUA_t<QueryDataSet_t>& QueryFirstResponse_t::QueryDataSets() const
{
	return queryDataSets;
}

ArrayUA_t<QueryDataSet_t>& QueryFirstResponse_t::QueryDataSets()
{
	return queryDataSets;
}

const BrowseContinuationPoint_t & QueryFirstResponse_t::ContinuationPoint() const
{
	return continuationPoint;
}

BrowseContinuationPoint_t & QueryFirstResponse_t::ContinuationPoint()
{
	return continuationPoint;
}

const ArrayUA_t<ParsingResult_t>& QueryFirstResponse_t::ParsingResults() const
{
	return parsingResults;
}

ArrayUA_t<ParsingResult_t>& QueryFirstResponse_t::ParsingResults()
{
	return parsingResults;
}

const ArrayUA_t<DiagnosticInfo_t>& QueryFirstResponse_t::DiagnosticInfos() const
{
	return diagnosticInfos;
}

ArrayUA_t<DiagnosticInfo_t>& QueryFirstResponse_t::DiagnosticInfos()
{
	return diagnosticInfos;
}

const ContentFilterResult_t & QueryFirstResponse_t::FilterResult() const
{
	return filterResult;
}

ContentFilterResult_t & QueryFirstResponse_t::FilterResult()
{
	return filterResult;
}

} // namespace uasdk

#endif

