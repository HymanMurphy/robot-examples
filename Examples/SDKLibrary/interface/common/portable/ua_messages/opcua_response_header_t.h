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

#ifndef _OPCUA_RESPONSE_HEADER_T_
#define _OPCUA_RESPONSE_HEADER_T_


#include "opcua_date_time_t.h"
#include "opcua_uint32_t.h"
#include "opcua_diagnostic_info_t.h"
#include "opcua_string_t.h"
#include "opcua_array_ua_t.h"
#include "opcua_extensible_parameter_t.h"

namespace uasdk
{

class ResponseHeader_t
{
private:
  DateTime_t              timestamp;
  UInt32_t                requestHandle;
  StatusCode_t            serviceResult;
  DiagnosticInfo_t        serviceDiagnostics;
  ArrayUA_t<String_t>     stringTable;
  ExtensibleParameter_t   additionalHeader;

public:
  ResponseHeader_t();
  ~ResponseHeader_t(void);

  const DateTime_t& Timestamp(void) const { return timestamp; }
  DateTime_t& Timestamp(void) { return timestamp; }

  const UInt32_t& RequestHandle(void) const { return requestHandle; }
  UInt32_t& RequestHandle(void) { return requestHandle; }

  const StatusCode_t& ServiceResult(void) const { return serviceResult; }
  StatusCode_t& ServiceResult(void) { return serviceResult; }

  const DiagnosticInfo_t& ServiceDiagnostics(void) const { return serviceDiagnostics; }
  DiagnosticInfo_t& ServiceDiagnostics(void) { return serviceDiagnostics; }

  const ArrayUA_t<String_t>& StringTable(void) const  { return stringTable; }
  ArrayUA_t<String_t>& StringTable(void) { return stringTable; }

  const ExtensibleParameter_t& AdditionalHeader(void) const  { return additionalHeader;  }
  ExtensibleParameter_t& AdditionalHeader(void) { return additionalHeader;  }

  Status_t Encode(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, ResponseHeader_t& result);
};

} // namespace uasdk
#endif // _OPCUA_REQUEST_HEADER_T_
