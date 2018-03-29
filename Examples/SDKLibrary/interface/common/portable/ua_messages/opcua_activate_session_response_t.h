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

#ifndef _OPCUA_ACTIVATE_SESSION_RESPONSE_T_
#define _OPCUA_ACTIVATE_SESSION_RESPONSE_T_


#include "opcua_endpoint_description_t.h"
#include "opcua_response_header_t.h"
#include "opcua_array_ua_t.h"

#include "opcua_status_code_t.h"
#include "opcua_response_message_t.h"

namespace uasdk
{

class ActivateSessionResponse_t : public ResponseMessage_t
{
private:
  ByteString_t                  serverNonce;
  ArrayUA_t<StatusCode_t>       results;
  ArrayUA_t<DiagnosticInfo_t>   diagnosticInfos;

  ActivateSessionResponse_t& operator=(ActivateSessionResponse_t const &);
  ActivateSessionResponse_t(ActivateSessionResponse_t const &);

public:
  static const uint32_t TYPE_ID = OpcUaId_ActivateSessionResponse;

  ActivateSessionResponse_t() {};
  virtual ~ActivateSessionResponse_t(){}

  uint32_t TypeId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return TYPE_ID;
  }

  uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return OpcUaId_ActivateSessionResponse_Encoding_DefaultBinary;
  }

  const ByteString_t& ServerNonce(void) const { return serverNonce; }
  ByteString_t& ServerNonce(void) { return serverNonce; }

  const ArrayUA_t<StatusCode_t>& Results(void) const {  return results; }
  ArrayUA_t<StatusCode_t>& Results(void) {  return results; }

  const ArrayUA_t<DiagnosticInfo_t>& DiagnosticInfos(void) const { return diagnosticInfos; }
  ArrayUA_t<DiagnosticInfo_t>& DiagnosticInfos(void) { return diagnosticInfos; }

  virtual Status_t EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, ActivateSessionResponse_t& result);

};

} // namespace uasdk
#endif // _OPCUA_ACTIVATE_SESSION_RESPONSE_T_
