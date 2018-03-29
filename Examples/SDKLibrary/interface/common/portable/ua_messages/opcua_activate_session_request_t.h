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

#ifndef _OPCUA_ACTIVATE_SESSION_REQUEST_T_
#define _OPCUA_ACTIVATE_SESSION_REQUEST_T_


#include "opcua_string_t.h"
#include "opcua_request_header_t.h"
#include "opcua_array_ua_t.h"
#include "opcua_app_description_t.h"
#include "opcua_signature_data_t.h"
#include "opcua_request_message_t.h"
#include "opcua_extensible_parameter_t.h"

namespace uasdk
{

class ActivateSessionRequest_t : public RequestMessage_t
{
private:
  SignatureData_t           clientSignature;
  ArrayUA_t<ByteString_t>   clientSoftwareCertificates;
  ArrayUA_t<String_t>       localeIds;
  ExtensibleParameter_t     userIdentityToken;
  SignatureData_t           userTokenSignature;

  ActivateSessionRequest_t& operator=(ActivateSessionRequest_t const &);
  ActivateSessionRequest_t(ActivateSessionRequest_t const &);

public:
  ActivateSessionRequest_t(){}
  virtual ~ActivateSessionRequest_t(){}

  static const uint32_t TYPE_ID = OpcUaId_ActivateSessionRequest;

  uint32_t TypeId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return TYPE_ID;
  }

  uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return OpcUaId_ActivateSessionRequest_Encoding_DefaultBinary;
  }

  const SignatureData_t& ClientSignature(void) const { return clientSignature; }
  SignatureData_t& ClientSignature(void) { return clientSignature; }

  const ArrayUA_t<ByteString_t>& ClientSoftwareCertificates(void) const { return clientSoftwareCertificates; }
  ArrayUA_t<ByteString_t>& ClientSoftwareCertificates(void) { return clientSoftwareCertificates; }

  const ArrayUA_t<String_t>& LocaleIds(void) const { return localeIds; }
  ArrayUA_t<String_t>& LocaleIds(void) { return localeIds; }

  const ExtensibleParameter_t& UserIdentityToken(void) const { return userIdentityToken; }
  ExtensibleParameter_t& UserIdentityToken(void) { return userIdentityToken; }

  const SignatureData_t& UserTokenSignature(void) const { return userTokenSignature; }
  SignatureData_t& UserTokenSignature(void) { return userTokenSignature; }

  virtual Status_t EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, ActivateSessionRequest_t& result);
};

} // namespace uasdk
#endif // _OPCUA_ACTIVATE_SESSION_REQUEST_T_
