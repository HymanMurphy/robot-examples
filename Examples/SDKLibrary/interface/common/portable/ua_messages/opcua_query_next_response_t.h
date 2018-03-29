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

#ifndef _OPCUA_QUERY_NEXT_RESPONSE_T_
#define _OPCUA_QUERY_NEXT_RESPONSE_T_

#include "opcua_response_message_t.h"
#include "opcua_querydata_set_t.h"
#include "opcua_browse_continuation_point_t.h"
#include "opcua_array_ua_t.h"

#if (UASDK_INCLUDE_QUERY_SERVICE_SET > 0)

namespace uasdk
{

class QueryNextResponse_t : public ResponseMessage_t
{
private:
	ArrayUA_t<QueryDataSet_t> queryDataSets;
	BrowseContinuationPoint_t revisedContinuationPoint;

	QueryNextResponse_t& operator=(QueryNextResponse_t const &);
	QueryNextResponse_t(QueryNextResponse_t const &);

public:
  static const uint32_t TYPE_ID = OpcUaId_QueryNextResponse;

  QueryNextResponse_t() {};
  virtual ~QueryNextResponse_t(){}

  uint32_t TypeId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return TYPE_ID;
  }

  uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return OpcUaId_QueryNextResponse_Encoding_DefaultBinary;
  }

  const ArrayUA_t<QueryDataSet_t>& QueryDataSets() const;
  ArrayUA_t<QueryDataSet_t>& QueryDataSets();

  const BrowseContinuationPoint_t& RevisedContinuationPoint() const;
  BrowseContinuationPoint_t& RevisedContinuationPoint();

  virtual Status_t EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, QueryNextResponse_t& result);
};

} // namespace uasdk

#endif

#endif // _OPCUA_QUERY_NEXT_RESPONSE_T_
