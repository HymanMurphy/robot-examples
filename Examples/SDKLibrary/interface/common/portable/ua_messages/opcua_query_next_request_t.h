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

#ifndef _OPCUA_QUERY_NEXT_REQUEST_T_
#define _OPCUA_QUERY_NEXT_REQUEST_T_

#include "opcua_request_message_t.h"
#include "opcua_boolean_t.h"
#include "opcua_browse_continuation_point_t.h"

#if (UASDK_INCLUDE_QUERY_SERVICE_SET > 0)

namespace uasdk
{

class QueryNextRequest_t : public RequestMessage_t
{
private:
	Boolean_t releaseContinuationPoint;
	BrowseContinuationPoint_t continuationPoint;

	QueryNextRequest_t& operator=(QueryNextRequest_t const &);
	QueryNextRequest_t(QueryNextRequest_t const &);
public:
  static const uint32_t TYPE_ID = OpcUaId_QueryNextRequest;

  QueryNextRequest_t(){}
  virtual ~QueryNextRequest_t(){}

  uint32_t TypeId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return TYPE_ID;
  }

  uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return OpcUaId_QueryNextRequest_Encoding_DefaultBinary;
  }

  const Boolean_t& ReleaseContinuationPoint() const;
  Boolean_t& ReleaseContinuationPoint();

  const BrowseContinuationPoint_t& ContinuationPoint() const;
  BrowseContinuationPoint_t& ContinuationPoint();
  
  virtual Status_t EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, QueryNextRequest_t& result);

};

} // namespace uasdk

#endif

#endif // _OPCUA_QUERY_NEXT_REQUEST_T_
