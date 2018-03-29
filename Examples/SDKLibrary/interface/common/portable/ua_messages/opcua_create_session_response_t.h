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

#ifndef _OPCUA_CREATE_SESSION_RESPONSE_T_
#define _OPCUA_CREATE_SESSION_RESPONSE_T_


#include "opcua_node_id_t.h"
#include "opcua_endpoint_description_t.h"
#include "opcua_response_header_t.h"
#include "opcua_array_ua_t.h"

#include "opcua_signature_data_t.h"
#include "opcua_duration_t.h"
#include "opcua_response_message_t.h"

namespace uasdk
{

class CreateSessionResponse_t : public ResponseMessage_t
{
private:
  IntrusivePtr_t<const NodeId_t>    sessionId;
  IntrusivePtr_t<const NodeId_t>    authenticationToken;
  Duration_t                        revisedSessionTimeout;
  ByteString_t                      serverNonce;
  ByteString_t                      serverCertificate;
  ArrayUA_t<EndpointDescription_t>  serverEndpoints;
  ArrayUA_t<ByteString_t>           serverSoftwareCertificates;
  SignatureData_t                   serverSignature;
  UInt32_t                          maxRequestMessageSize;

  CreateSessionResponse_t& operator=(CreateSessionResponse_t const &);
  CreateSessionResponse_t(CreateSessionResponse_t const &);

public:
  static const uint32_t TYPE_ID = OpcUaId_CreateSessionResponse;

  CreateSessionResponse_t() {};
  virtual ~CreateSessionResponse_t(){}

  uint32_t TypeId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return TYPE_ID;
  }

  uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return OpcUaId_CreateSessionResponse_Encoding_DefaultBinary;
  }

  const IntrusivePtr_t<const NodeId_t>& SessionId(void) const { return sessionId; }
  IntrusivePtr_t<const NodeId_t>& SessionId(void) { return sessionId; }

  const IntrusivePtr_t<const NodeId_t>& AuthenticationToken(void) const { return authenticationToken; }
  IntrusivePtr_t<const NodeId_t>& AuthenticationToken(void) { return authenticationToken; }

  const Duration_t& RevisedSessionTimeout(void) const { return revisedSessionTimeout; }
  Duration_t& RevisedSessionTimeout(void) { return revisedSessionTimeout; }

  const ByteString_t& ServerNonce(void) const { return serverNonce; }
  ByteString_t& ServerNonce(void) { return serverNonce; }

  const ByteString_t& ServerCertificate(void) const { return serverCertificate; }
  ByteString_t& ServerCertificate(void) { return serverCertificate; }

  const ArrayUA_t<EndpointDescription_t>& ServerEndpoints(void) const { return serverEndpoints; }
  ArrayUA_t<EndpointDescription_t>& ServerEndpoints(void) { return serverEndpoints; }

  const ArrayUA_t<ByteString_t>& ServerSoftwareCertificates(void) const { return  serverSoftwareCertificates; }
  ArrayUA_t<ByteString_t>& ServerSoftwareCertificates(void) { return  serverSoftwareCertificates; }

  const SignatureData_t& ServerSignature(void) const { return serverSignature; }
  SignatureData_t& ServerSignature(void) { return serverSignature; }

  const UInt32_t& MaxRequestMessageSize(void) const { return maxRequestMessageSize; }
  UInt32_t& MaxRequestMessageSize(void) { return maxRequestMessageSize; }

  virtual Status_t EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, CreateSessionResponse_t& result);

};

} // namespace uasdk
#endif // _OPCUA_CREATE_SESSION_RESPONSE_T_
