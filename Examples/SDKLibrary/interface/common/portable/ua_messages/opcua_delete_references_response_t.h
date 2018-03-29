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

#ifndef _OPCUA_DELETE_REFERENCES_RESPONSE_T_
#define _OPCUA_DELETE_REFERENCES_RESPONSE_T_

#include "opcua_response_message_t.h"
#include "opcua_array_ua_t.h"
#include "opcua_diagnostic_info_t.h"
#include "opcua_status_code_t.h"

#if (UASDK_INCLUDE_NODE_MANAGEMENT_SERVICE_SET > 0)

namespace uasdk
{

class DeleteReferencesResponse_t : public ResponseMessage_t
{
private:	
	ArrayUA_t<StatusCode_t> results;
	ArrayUA_t<DiagnosticInfo_t> diagnosticInfos;

	DeleteReferencesResponse_t& operator=(DeleteReferencesResponse_t const &);
	DeleteReferencesResponse_t(DeleteReferencesResponse_t const &);

public:
  static const uint32_t TYPE_ID = OpcUaId_DeleteReferencesResponse;

  DeleteReferencesResponse_t() {};
  virtual ~DeleteReferencesResponse_t(){}

  uint32_t TypeId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return TYPE_ID;
  }

  uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return OpcUaId_DeleteReferencesResponse_Encoding_DefaultBinary;
  }
  
  const ArrayUA_t<StatusCode_t>& Results() const;
  ArrayUA_t<StatusCode_t>& Results();

  const ArrayUA_t<DiagnosticInfo_t>& DiagnosticInfos() const;
  ArrayUA_t<DiagnosticInfo_t>& DiagnosticInfos();

  virtual Status_t EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, DeleteReferencesResponse_t& result);
};

} // namespace uasdk

#endif

#endif // _OPCUA_DELETE_REFERENCES_RESPONSE_T_
