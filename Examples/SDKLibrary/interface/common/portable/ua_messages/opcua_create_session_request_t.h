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

#ifndef _OPCUA_CREATE_SESSION_REQUEST_T_
#define _OPCUA_CREATE_SESSION_REQUEST_T_


#include "opcua_string_t.h"
#include "opcua_request_header_t.h"
#include "opcua_array_ua_t.h"

#include "opcua_app_description_t.h"
#include "opcua_duration_t.h"
#include "opcua_request_message_t.h"

namespace uasdk
{

class CreateSessionRequest_t : public RequestMessage_t
{
private:
  AppDescription_t  clientDescription;
  String_t          serverUri;
  String_t          endpointUrl;
  String_t          sessionName;
  ByteString_t      clientNonce;
  ByteString_t      clientCertificate;
  Duration_t        requestedSessionTimeout;
  UInt32_t          maxResponseMessageSize;

  CreateSessionRequest_t& operator=(CreateSessionRequest_t const &);
  CreateSessionRequest_t(CreateSessionRequest_t const &);

public:
  static const uint32_t TYPE_ID = OpcUaId_CreateSessionRequest;

  CreateSessionRequest_t(){}
  virtual ~CreateSessionRequest_t(){}

  uint32_t TypeId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return TYPE_ID;
  }

  uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return OpcUaId_CreateSessionRequest_Encoding_DefaultBinary;
  }

  const AppDescription_t& ClientDescription(void) const { return clientDescription; }
  AppDescription_t& ClientDescription(void) { return clientDescription; }

  const String_t& ServerUri(void) const { return serverUri; }
  String_t& ServerUri(void) { return serverUri; }

  const String_t& EndpointUrl(void) const { return endpointUrl; }
  String_t& EndpointUrl(void) { return endpointUrl; }

  const String_t& SessionName(void) const { return sessionName; }
  String_t& SessionName(void) { return sessionName; }

  const ByteString_t& ClientNonce(void) const { return clientNonce; }
  ByteString_t& ClientNonce(void) { return clientNonce; }

  const ByteString_t& ClientCertificate(void) const { return clientCertificate; }
  ByteString_t& ClientCertificate(void) { return clientCertificate; }

  const Duration_t& RequestedSessionTimeout(void) const { return requestedSessionTimeout; }
  Duration_t& RequestedSessionTimeout(void) { return requestedSessionTimeout; }

  const UInt32_t& MaxResponseMessageSize(void) const { return maxResponseMessageSize; }
  UInt32_t& MaxResponseMessageSize(void) { return maxResponseMessageSize; }

  virtual Status_t EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, CreateSessionRequest_t& result);

};

} // namespace uasdk
#endif // _OPCUA_CREATE_SESSION_REQUEST_T_
