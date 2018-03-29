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

#ifndef _OPCUA_DELETE_NODES_RESPONSE_T_
#define _OPCUA_DELETE_NODES_RESPONSE_T_

#include "opcua_response_message_t.h"
#include "opcua_status_code_t.h"
#include "opcua_array_ua_t.h"
#include "opcua_diagnostic_info_t.h"

#if (UASDK_INCLUDE_NODE_MANAGEMENT_SERVICE_SET > 0)

namespace uasdk
{

class DeleteNodesResponse_t : public ResponseMessage_t
{
private:	
	ArrayUA_t<StatusCode_t> results;
	ArrayUA_t<DiagnosticInfo_t> diagnosticInfos;

	DeleteNodesResponse_t& operator=(DeleteNodesResponse_t const &);
	DeleteNodesResponse_t(DeleteNodesResponse_t const &);

public:
  static const uint32_t TYPE_ID = OpcUaId_DeleteNodesResponse;

  DeleteNodesResponse_t() {};
  virtual ~DeleteNodesResponse_t(){}

  uint32_t TypeId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return TYPE_ID;
  }

  uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return OpcUaId_DeleteNodesResponse_Encoding_DefaultBinary;
  }
  
  const ArrayUA_t<StatusCode_t>& Results() const;
  ArrayUA_t<StatusCode_t>& Results();

  const ArrayUA_t<DiagnosticInfo_t>& DiagnosticInfos() const;
  ArrayUA_t<DiagnosticInfo_t>& DiagnosticInfos();

  virtual Status_t EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, DeleteNodesResponse_t& result);
};

} // namespace uasdk

#endif

#endif // _OPCUA_DELETE_NODES_RESPONSE_T_
