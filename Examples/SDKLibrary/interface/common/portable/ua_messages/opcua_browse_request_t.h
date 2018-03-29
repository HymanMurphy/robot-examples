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

#ifndef _OPCUA_BROWSE_REQUEST_T_
#define _OPCUA_BROWSE_REQUEST_T_


#include "opcua_string_t.h"
#include "opcua_request_header_t.h"
#include "opcua_array_ua_t.h"

#include "opcua_app_description_t.h"
#include "opcua_view_description_t.h"
#include "opcua_browse_description_t.h"
#include "opcua_request_message_t.h"

namespace uasdk
{

class BrowseRequest_t : public RequestMessage_t
{
private:
  ViewDescription_t                 view;
  Counter_t                         requestedMaxRefPerNode;
  ArrayUA_t<BrowseDescription_t>    nodesToBrowse;

  BrowseRequest_t& operator=(BrowseRequest_t const &);
  BrowseRequest_t(BrowseRequest_t const &);

public:
  static const uint32_t TYPE_ID = OpcUaId_BrowseRequest;

  BrowseRequest_t(){}
  virtual ~BrowseRequest_t(){}

  uint32_t TypeId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return TYPE_ID;
  }

  uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return OpcUaId_BrowseRequest_Encoding_DefaultBinary;
  }

  const ViewDescription_t& View(void) const { return view; }
  ViewDescription_t& View(void) { return view; }

  const Counter_t& RequestedMaxRefPerNode(void) const { return requestedMaxRefPerNode; }
  Counter_t& RequestedMaxRefPerNode(void) { return requestedMaxRefPerNode; }

  const ArrayUA_t<BrowseDescription_t>& NodesToBrowse(void) const { return nodesToBrowse; }
  ArrayUA_t<BrowseDescription_t>& NodesToBrowse(void) { return nodesToBrowse; }

  virtual Status_t EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, BrowseRequest_t& result);

};

} // namespace uasdk
#endif // _OPCUA_BROWSE_REQUEST_T_
