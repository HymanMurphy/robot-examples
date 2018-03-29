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

#ifndef _OPCUA_QUERY_FIRST_RESPONSE_T_
#define _OPCUA_QUERY_FIRST_RESPONSE_T_

#include "opcua_response_message_t.h"
#include "opcua_array_ua_t.h"
#include "opcua_querydata_set_t.h"
#include "opcua_parsing_result_t.h"
#include "opcua_browse_continuation_point_t.h"

#if (UASDK_INCLUDE_QUERY_SERVICE_SET > 0)

//TODO: replace the typedef with the real class
typedef void* ContentFilterResult_t;

namespace uasdk
{

class QueryFirstResponse_t : public ResponseMessage_t
{
private:
	ArrayUA_t<QueryDataSet_t> queryDataSets;
	BrowseContinuationPoint_t continuationPoint;
	ArrayUA_t<ParsingResult_t> parsingResults;
	ArrayUA_t<DiagnosticInfo_t> diagnosticInfos;
	ContentFilterResult_t filterResult;

	QueryFirstResponse_t& operator=(QueryFirstResponse_t const &);
	QueryFirstResponse_t(QueryFirstResponse_t const &);

public:
  static const uint32_t TYPE_ID = OpcUaId_QueryFirstResponse;

  QueryFirstResponse_t() {};
  virtual ~QueryFirstResponse_t(){}

  uint32_t TypeId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return TYPE_ID;
  }

  uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return OpcUaId_QueryFirstResponse_Encoding_DefaultBinary;
  }

  const ArrayUA_t<QueryDataSet_t>& QueryDataSets() const;
  ArrayUA_t<QueryDataSet_t>& QueryDataSets();

  const BrowseContinuationPoint_t& ContinuationPoint() const;
  BrowseContinuationPoint_t& ContinuationPoint();

  const ArrayUA_t<ParsingResult_t>& ParsingResults() const;
  ArrayUA_t<ParsingResult_t>& ParsingResults();

  const ArrayUA_t<DiagnosticInfo_t>& DiagnosticInfos() const;
  ArrayUA_t<DiagnosticInfo_t>& DiagnosticInfos();

  const ContentFilterResult_t& FilterResult() const;
  ContentFilterResult_t& FilterResult();

  virtual Status_t EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, QueryFirstResponse_t& result);
};

} // namespace uasdk

#endif

#endif // _OPCUA_QUERY_FIRST_RESPONSE_T_
