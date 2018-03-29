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

#ifndef _OPCUA_SET_TRIGGERING_RESPONSE_T_
#define _OPCUA_SET_TRIGGERING_RESPONSE_T_


#include "opcua_response_message_t.h"
#include "opcua_response_header_t.h"
#include "opcua_array_ua_t.h"

#include "opcua_diagnostic_info_t.h"

#if (UASDK_INCLUDE_SUBSCRIPTIONS > 0)

namespace uasdk
{

class SetTriggeringResponse_t : public ResponseMessage_t
{
private:
  ArrayUA_t<StatusCode_t>       addResults;
  ArrayUA_t<DiagnosticInfo_t>   addDiagnosticInfos;
  ArrayUA_t<StatusCode_t>       removeResults;
  ArrayUA_t<DiagnosticInfo_t>   removeDiagnosticInfos;

  SetTriggeringResponse_t& operator=(SetTriggeringResponse_t const &);
  SetTriggeringResponse_t(SetTriggeringResponse_t const &);

public:
  static const uint32_t TYPE_ID = OpcUaId_SetTriggeringResponse;

  SetTriggeringResponse_t() {};
  virtual ~SetTriggeringResponse_t(){}

  uint32_t TypeId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return TYPE_ID;
  }

  uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return OpcUaId_SetTriggeringResponse_Encoding_DefaultBinary;
  }

  const ArrayUA_t<StatusCode_t>& AddResults(void) const { return addResults;  }
  ArrayUA_t<StatusCode_t>& AddResults(void) { return addResults;  }

  const ArrayUA_t<DiagnosticInfo_t>& AddDiagnosticInfos(void) const  { return addDiagnosticInfos;  }
  ArrayUA_t<DiagnosticInfo_t>& AddDiagnosticInfos(void) { return addDiagnosticInfos;  }

  const ArrayUA_t<StatusCode_t>& RemoveResults(void) const  { return removeResults; }
  ArrayUA_t<StatusCode_t>& RemoveResults(void) { return removeResults; }

  const ArrayUA_t<DiagnosticInfo_t>& RemoveDiagnosticInfos(void) const  { return removeDiagnosticInfos;  }
  ArrayUA_t<DiagnosticInfo_t>& RemoveDiagnosticInfos(void) { return removeDiagnosticInfos;  }

  virtual Status_t EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, SetTriggeringResponse_t& result);
};

} // namespace uasdk

#endif //UASDK_INCLUDE_SUBSCRIPTIONS

#endif // _OPCUA_SET_TRIGGERING_RESPONSE_T_
