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

#ifndef _OPCUA_REQUEST_HEADER_T_
#define _OPCUA_REQUEST_HEADER_T_


#include "opcua_date_time_t.h"
#include "opcua_uint32_t.h"
#include "opcua_string_t.h"
#include "opcua_structure_t.h"
#include "opcua_extensible_parameter_t.h"

namespace uasdk
{

class RequestHeader_t
{
private:
  IntrusivePtr_t<NodeId_t>  authenticationToken;
  DateTime_t                timestamp;
  UInt32_t                  requestHandle;
  UInt32_t                  returnDiagnostics;
  String_t                  auditEntry;
  UInt32_t                  timeoutHint;
  ExtensibleParameter_t     additionalHeader;

public:
  RequestHeader_t();
  ~RequestHeader_t(void);

  IntrusivePtr_t<const NodeId_t> AuthenticationToken(void) const { return authenticationToken; }
  IntrusivePtr_t<NodeId_t>& AuthenticationToken(void) { return authenticationToken; }

  const DateTime_t& Timestamp(void) const { return timestamp; }
  DateTime_t& Timestamp(void) { return timestamp; }

  const UInt32_t& RequestHandle(void) const { return requestHandle; }
  UInt32_t& RequestHandle(void) { return requestHandle; }

  const UInt32_t& ReturnDiagnostics(void) const { return returnDiagnostics; }
  UInt32_t& ReturnDiagnostics(void) { return returnDiagnostics; }

  const String_t& AuditEntry(void) const { return auditEntry; }
  String_t& AuditEntry(void) { return auditEntry; }

  const UInt32_t& TimeoutHint(void) const { return timeoutHint; }
  UInt32_t& TimeoutHint(void) { return timeoutHint; }

  const ExtensibleParameter_t& AdditionalHeader(void) const  { return additionalHeader;  }
  ExtensibleParameter_t& AdditionalHeader(void)  { return additionalHeader;  }

  Status_t CopyFrom(const RequestHeader_t& source);

  Status_t Encode(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, RequestHeader_t& result);
};

} // namespace uasdk
#endif // _OPCUA_REQUEST_HEADER_T_
