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

#ifndef _OPCUA_OPEN_SECURE_CHANNEL_RESPONSE_T_
#define _OPCUA_OPEN_SECURE_CHANNEL_RESPONSE_T_


#include "opcua_uint32_t.h"
#include "opcua_response_header_t.h"
#include "opcua_channel_security_token_t.h"
#include "opcua_bytestring_t.h"

#include "opcua_response_message_t.h"

namespace uasdk
{

class OpenSecureChannelResponse_t : public ResponseMessage_t
{
private:
  UInt32_t                  serverProtocolVersion;
  ChannelSecurityToken_t    securityToken;
  ByteString_t              serverNonce;

  OpenSecureChannelResponse_t& operator=(OpenSecureChannelResponse_t const &);
  OpenSecureChannelResponse_t(OpenSecureChannelResponse_t const &);

public:
  static const uint32_t TYPE_ID = OpcUaId_OpenSecureChannelResponse;

  OpenSecureChannelResponse_t() : serverProtocolVersion(0) {}
  virtual ~OpenSecureChannelResponse_t(){}

  uint32_t TypeId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return TYPE_ID;
  }

  uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return OpcUaId_OpenSecureChannelResponse_Encoding_DefaultBinary;
  }

  const UInt32_t& ServerProtocolVersion(void) const { return serverProtocolVersion; }
  UInt32_t& ServerProtocolVersion(void) { return serverProtocolVersion; }

  const ChannelSecurityToken_t& SecurityToken(void) const { return securityToken; }
  ChannelSecurityToken_t& SecurityToken(void) { return securityToken; }

  const ByteString_t& ServerNonce(void) const { return serverNonce; }
  ByteString_t& ServerNonce(void) { return serverNonce; }

  virtual Status_t EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, OpenSecureChannelResponse_t& result);

};

} // namespace uasdk
#endif // _OPCUA_OPEN_SECURE_CHANNEL_RESPONSE_T_
