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

#ifndef _OPCUA_CLOSE_SECURE_CHANNEL_REQUEST_T_
#define _OPCUA_CLOSE_SECURE_CHANNEL_REQUEST_T_


#include "opcua_request_message_t.h"
#include "opcua_string_t.h"
#include "opcua_request_header_t.h"
#include "opcua_array_ua_t.h"

#include "opcua_app_description_t.h"
#include "opcua_boolean_t.h"

namespace uasdk
{

class CloseSecureChannelRequest_t : public RequestMessage_t
{
private:

  CloseSecureChannelRequest_t& operator=(CloseSecureChannelRequest_t const &);
  CloseSecureChannelRequest_t(CloseSecureChannelRequest_t const &);

public:
  static const uint32_t TYPE_ID = OpcUaId_CloseSecureChannelRequest;

  CloseSecureChannelRequest_t(){}
  virtual ~CloseSecureChannelRequest_t(){}

  uint32_t TypeId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return TYPE_ID;
  }

  uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return OpcUaId_CloseSecureChannelRequest_Encoding_DefaultBinary;
  }

  virtual Status_t EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, CloseSecureChannelRequest_t& result);

};

} // namespace uasdk
#endif // _OPCUA_CLOSE_SECURE_CHANNEL_REQUEST_T_
