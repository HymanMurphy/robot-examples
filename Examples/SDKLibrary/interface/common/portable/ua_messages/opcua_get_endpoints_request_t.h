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

#ifndef _OPCUA_GET_ENDPOINTS_REQUEST_T_
#define _OPCUA_GET_ENDPOINTS_REQUEST_T_


#include "opcua_string_t.h"
#include "opcua_request_header_t.h"
#include "opcua_array_ua_t.h"

#include "opcua_request_message_t.h"

namespace uasdk
{

class GetEndpointsRequest_t : public RequestMessage_t
{
private:
  String_t              endpointUrl;
  ArrayUA_t<String_t>  localeIds;
  ArrayUA_t<String_t>  profileUris;

  GetEndpointsRequest_t& operator=(GetEndpointsRequest_t const &);
  GetEndpointsRequest_t(GetEndpointsRequest_t const &);

public:
  static const uint32_t TYPE_ID = OpcUaId_GetEndpointsRequest;

  GetEndpointsRequest_t(){}
  virtual ~GetEndpointsRequest_t(){}

  uint32_t TypeId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return TYPE_ID;
  }

  uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return OpcUaId_GetEndpointsRequest_Encoding_DefaultBinary;
  }

  const String_t& EndpointUrl(void) const { return endpointUrl; }
  String_t& EndpointUrl(void) { return endpointUrl; }

  const ArrayUA_t<String_t>& LocaleIds(void) const { return localeIds; }
  ArrayUA_t<String_t>& LocaleIds(void) { return localeIds; }

  const ArrayUA_t<String_t>& ProfileUris(void) const { return profileUris; }
  ArrayUA_t<String_t>& ProfileUris(void) { return profileUris; }

  virtual Status_t EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, GetEndpointsRequest_t& result);

};

} // namespace uasdk
#endif // _OPCUA_GET_ENDPOINTS_REQUEST_T_
