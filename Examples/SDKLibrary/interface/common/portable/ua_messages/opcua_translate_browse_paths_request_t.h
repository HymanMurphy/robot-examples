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

#ifndef _OPCUA_TRANSLATE_BROWSE_PATHS_REQUEST_T_
#define _OPCUA_TRANSLATE_BROWSE_PATHS_REQUEST_T_


#include "opcua_string_t.h"
#include "opcua_request_header_t.h"
#include "opcua_array_ua_t.h"

#include "opcua_app_description_t.h"
#include "opcua_browse_path_t.h"
#include "opcua_request_message_t.h"

namespace uasdk
{

class TranslateBrowsePathsRequest_t : public RequestMessage_t
{
private:
  ArrayUA_t<BrowsePath_t>  browsePaths;

  TranslateBrowsePathsRequest_t& operator=(TranslateBrowsePathsRequest_t const &);
  TranslateBrowsePathsRequest_t(TranslateBrowsePathsRequest_t const &);

public:
  static const uint32_t TYPE_ID = OpcUaId_TranslateBrowsePathsToNodeIdsRequest;

  TranslateBrowsePathsRequest_t(){}
  virtual ~TranslateBrowsePathsRequest_t(){}

  uint32_t TypeId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return TYPE_ID;
  }

  uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return OpcUaId_TranslateBrowsePathsToNodeIdsRequest_Encoding_DefaultBinary;
  }

  const ArrayUA_t<BrowsePath_t>& BrowsePaths(void) const { return browsePaths; }
  ArrayUA_t<BrowsePath_t>& BrowsePaths(void) { return browsePaths; }

  virtual Status_t EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, TranslateBrowsePathsRequest_t& result);
};

} // namespace uasdk
#endif // _OPCUA_TRANSLATE_BROWSE_PATHS_REQUEST_T_
