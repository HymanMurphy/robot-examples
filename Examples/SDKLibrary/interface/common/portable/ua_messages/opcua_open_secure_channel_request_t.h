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

#ifndef _OPCUA_OPEN_SECURE_CHANNEL_REQUEST_T_
#define _OPCUA_OPEN_SECURE_CHANNEL_REQUEST_T_


#include "opcua_uint32_t.h"
#include "opcua_int32_t.h"
#include "opcua_request_header_t.h"
#include "opcua_security_token_request_type_t.h"
#include "opcua_message_security_mode_t.h"

#include "opcua_request_message_t.h"

namespace uasdk
{

class OpenSecureChannelRequest_t : public RequestMessage_t
{
private:
  UInt32_t                      clientProtocolVersion;
  SecurityTokenRequestType_t    requestType;
  MessageSecurityMode_t         messageSecurityMode;
  ByteString_t                  clientNonce;
  Int32_t                       requestedLifetime;

  OpenSecureChannelRequest_t& operator=(OpenSecureChannelRequest_t const &);
  OpenSecureChannelRequest_t(OpenSecureChannelRequest_t const &);

public:
  static const uint32_t TYPE_ID = OpcUaId_OpenSecureChannelRequest;

  OpenSecureChannelRequest_t() : clientProtocolVersion(0), requestedLifetime(0) {}
  virtual ~OpenSecureChannelRequest_t(){}

  uint32_t TypeId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return TYPE_ID;
  }

  uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return OpcUaId_OpenSecureChannelRequest_Encoding_DefaultBinary;
  }

  const UInt32_t& ClientProtocolVersion(void) const { return clientProtocolVersion; }
  UInt32_t& ClientProtocolVersion(void) { return clientProtocolVersion; }

  const SecurityTokenRequestType_t& RequestType(void) const { return requestType; }
  SecurityTokenRequestType_t& RequestType(void) { return requestType; }

  const MessageSecurityMode_t& MessageSecurityMode(void) const { return messageSecurityMode; }
  MessageSecurityMode_t& MessageSecurityMode(void) { return messageSecurityMode; }

  const ByteString_t& ClientNonce(void) const { return clientNonce; }
  ByteString_t& ClientNonce(void) { return clientNonce; }

  const Int32_t& RequestedLifetime(void) const { return requestedLifetime; }
  Int32_t& RequestedLifetime(void) { return requestedLifetime; }

  virtual Status_t EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, OpenSecureChannelRequest_t& result);

};

} // namespace uasdk
#endif // _OPCUA_OPEN_SECURE_CHANNEL_REQUEST_T_
