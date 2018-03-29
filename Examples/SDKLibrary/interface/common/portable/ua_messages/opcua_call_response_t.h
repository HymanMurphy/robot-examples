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

#ifndef _OPCUA_CALL_RESPONSE_T_
#define _OPCUA_CALL_RESPONSE_T_


#include "opcua_call_method_result_t.h"
#include "opcua_response_message_t.h"

#if (UASDK_INCLUDE_METHOD_SERVICE_SET > 0)

namespace uasdk
{

class CallResponse_t : public ResponseMessage_t
{
private:
  ArrayUA_t<CallMethodResult_t> results;
  ArrayUA_t<DiagnosticInfo_t> diagnosticInfos;

  CallResponse_t& operator=(CallResponse_t const &);
  CallResponse_t(CallResponse_t const &);

public:
  static const uint32_t TYPE_ID = OpcUaId_CallResponse;

  CallResponse_t() {};
  virtual ~CallResponse_t(){}

  uint32_t TypeId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return TYPE_ID;
  }

  uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return OpcUaId_CallResponse_Encoding_DefaultBinary;
  }

  const ArrayUA_t<CallMethodResult_t>& Results(void) const { return results; }
  ArrayUA_t<CallMethodResult_t>& Results(void) { return results; }

  const ArrayUA_t<DiagnosticInfo_t>& DiagnosticInfos(void) const { return diagnosticInfos; }
  ArrayUA_t<DiagnosticInfo_t>& DiagnosticInfos(void) { return diagnosticInfos; }

  virtual Status_t EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, CallResponse_t& result);
};

} // namespace uasdk

#endif

#endif // _OPCUA_CALL_RESPONSE_T_
