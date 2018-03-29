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

#ifndef _OPCUA_CALL_REQUEST_T_
#define _OPCUA_CALL_REQUEST_T_


#include "opcua_call_method_request_t.h"
#include "opcua_request_message_t.h"

#if (UASDK_INCLUDE_METHOD_SERVICE_SET > 0)

namespace uasdk
{

class CallRequest_t : public RequestMessage_t
{
private:
  ArrayUA_t<CallMethodRequest_t> methodsToCall;

  CallRequest_t& operator=(CallRequest_t const &);
  CallRequest_t(CallRequest_t const &);

public:
  static const uint32_t TYPE_ID = OpcUaId_CallRequest;

  CallRequest_t(){}
  virtual ~CallRequest_t(){}

  uint32_t TypeId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return TYPE_ID;
  }

  uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return OpcUaId_CallRequest_Encoding_DefaultBinary;
  }

  const ArrayUA_t<CallMethodRequest_t>& MethodsToCall(void) const { return methodsToCall; }
  ArrayUA_t<CallMethodRequest_t>& MethodsToCall(void) { return methodsToCall; }

  virtual Status_t EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, CallRequest_t& result);

};

} // namespace uasdk

#endif

#endif // _OPCUA_CALL_REQUEST_T_
