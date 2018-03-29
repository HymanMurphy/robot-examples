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

#ifndef _OPCUA_READ_RESPONSE_T_
#define _OPCUA_READ_RESPONSE_T_


#include "opcua_response_message_t.h"
#include "opcua_endpoint_description_t.h"
#include "opcua_response_header_t.h"
#include "opcua_array_ua_t.h"

#include "opcua_data_value_t.h"
#include "opcua_diagnostic_info_t.h"

namespace uasdk
{

class ReadResponse_t : public ResponseMessage_t
{
private:
  ArrayUA_t<DataValue_t>  results;
  ArrayUA_t<DiagnosticInfo_t> diagnosticInfos;

  ReadResponse_t& operator=(ReadResponse_t const &);
  ReadResponse_t(ReadResponse_t const &);

public:
  static const uint32_t TYPE_ID = OpcUaId_ReadResponse;

  ReadResponse_t() {};
  virtual ~ReadResponse_t(){}

  uint32_t TypeId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return TYPE_ID;
  }

  uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return OpcUaId_ReadResponse_Encoding_DefaultBinary;
  }

  const ArrayUA_t<DataValue_t>& Results(void) const { return results; }
  ArrayUA_t<DataValue_t>& Results(void) { return results; }

  const ArrayUA_t<DiagnosticInfo_t>& DiagnosticInfos(void) const { return diagnosticInfos; }
  ArrayUA_t<DiagnosticInfo_t>& DiagnosticInfos(void) { return diagnosticInfos; }

  virtual Status_t EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, ReadResponse_t& result);
};

} // namespace uasdk
#endif // _OPCUA_READ_RESPONSE_T_
