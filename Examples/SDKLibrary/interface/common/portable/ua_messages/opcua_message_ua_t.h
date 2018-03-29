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

#ifndef _OPCUA_MESSAGE_UA_T_
#define _OPCUA_MESSAGE_UA_T_

#include "iuser_permissions_t.h"
#include "allocatable_t.h"
#include "opcua_identifiers.h"
#include "opcua_request_header_t.h"
#include "opcua_response_header_t.h"
#include "buffer_t.h"
#include "opcua_message_security_mode_t.h"
#include "icodec_t.h"

namespace uasdk
{

class MessageUA_t : public IRefCount_t, public Allocatable_t
{
public:
  struct StackInfo_t
  {
    uint32_t                              stackRequestId;
    uint32_t                              stackSecureChannelId;
    SecurityPolicy_t                      stackSecurityPolicy;
    MessageSecurityMode_t::Enum_t         stackMessageSecurityMode;
    IntrusivePtr_t<const ByteString_t>    senderCertificate;
    IntrusivePtr_t<const NodeId_t>        sessionId;
    IntrusivePtr_t<IUserPermissions_t>    sessionUserPermissions;
    IntrusivePtr_t<const ArrayUA_t<String_t> > sessionLocales;
  };

protected:
  StackInfo_t stackInfo;

  MessageUA_t& operator=(MessageUA_t const &);
  MessageUA_t(MessageUA_t const &);

public:
  MessageUA_t() {}
  virtual ~MessageUA_t(){}

  const StackInfo_t& StackInfo(void) const { return stackInfo; }
  StackInfo_t& StackInfo(void) { return stackInfo; }

  uint32_t TypeId(void) const
  {
    uint16_t namespaceIndex = 0;
    return TypeId(namespaceIndex);
  }

  virtual uint32_t TypeId(uint16_t& namespaceIndex) const = 0;

  uint32_t BinaryEncodingId(void) const
  {
    uint16_t namespaceIndex = 0;
    return BinaryEncodingId(namespaceIndex);
  }

  virtual uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const = 0;

  Status_t Encode(ICodec_t& encoder, IBuffer_t& buffer) const
  {
    return encoder.Encode(*this, buffer);
  }

  virtual Status_t EncodeHeader(ICodec_t& encoder, IBuffer_t& buffer) const = 0;
  virtual Status_t EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const = 0;
};

} // namespace uasdk
#endif // _OPCUA_MESSAGE_UA_T_
