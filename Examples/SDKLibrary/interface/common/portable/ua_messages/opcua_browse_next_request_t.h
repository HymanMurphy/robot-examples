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

#ifndef _OPCUA_BROWSE_NEXT_REQUEST_T_
#define _OPCUA_BROWSE_NEXT_REQUEST_T_


#include "opcua_browse_continuation_point_t.h"
#include "opcua_string_t.h"
#include "opcua_request_header_t.h"
#include "opcua_array_ua_t.h"

#include "opcua_app_description_t.h"
#include "opcua_boolean_t.h"
#include "opcua_request_message_t.h"

namespace uasdk
{

class BrowseNextRequest_t : public RequestMessage_t
{
private:
  Boolean_t               releaseContinuationPoints;
  ArrayUA_t<ByteString_t> continuationPoints;

  BrowseNextRequest_t& operator=(BrowseNextRequest_t const &);
  BrowseNextRequest_t(BrowseNextRequest_t const &);

public:
  static const uint32_t TYPE_ID = OpcUaId_BrowseNextRequest;

  BrowseNextRequest_t(){}
  virtual ~BrowseNextRequest_t(){}

  uint32_t TypeId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return TYPE_ID;
  }

  uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return OpcUaId_BrowseNextRequest_Encoding_DefaultBinary;
  }

  const Boolean_t& ReleaseContinuationPoints(void) const { return releaseContinuationPoints; }
  Boolean_t& ReleaseContinuationPoints(void) { return releaseContinuationPoints; }

  const ArrayUA_t<ByteString_t>& ContinuationPoints(void) const { return continuationPoints; }
  ArrayUA_t<ByteString_t>& ContinuationPoints(void) { return continuationPoints; }

  virtual Status_t EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, BrowseNextRequest_t& result);

};

} // namespace uasdk
#endif // _OPCUA_BROWSE_NEXT_REQUEST_T_
