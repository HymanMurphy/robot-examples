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

#ifndef _OPCUA_DELETE_MONITORED_ITEMS_RESPONSE_T_
#define _OPCUA_DELETE_MONITORED_ITEMS_RESPONSE_T_


#include "opcua_response_message_t.h"
#include "opcua_endpoint_description_t.h"
#include "opcua_response_header_t.h"
#include "opcua_array_ua_t.h"

#include "opcua_mon_item_create_result_t.h"
#include "opcua_diagnostic_info_t.h"
#include "opcua_mon_item_modify_result_t.h"

#if (UASDK_INCLUDE_SUBSCRIPTIONS > 0)

namespace uasdk
{

class DeleteMonitoredItemsResponse_t : public ResponseMessage_t
{
private:
  ArrayUA_t<StatusCode_t>       results;
  ArrayUA_t<DiagnosticInfo_t>   diagnosticInfos;

  DeleteMonitoredItemsResponse_t& operator=(DeleteMonitoredItemsResponse_t const &);
  DeleteMonitoredItemsResponse_t(DeleteMonitoredItemsResponse_t const &);

public:
  static const uint32_t TYPE_ID = OpcUaId_DeleteMonitoredItemsResponse;

  DeleteMonitoredItemsResponse_t() {};
  virtual ~DeleteMonitoredItemsResponse_t(){}

  uint32_t TypeId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return TYPE_ID;
  }

  uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return OpcUaId_DeleteMonitoredItemsResponse_Encoding_DefaultBinary;
  }

  const ArrayUA_t<StatusCode_t>& Results(void) const  { return results; }
  ArrayUA_t<StatusCode_t>& Results(void)  { return results; }

  const ArrayUA_t<DiagnosticInfo_t>& DiagnosticInfos(void) const { return diagnosticInfos; }
  ArrayUA_t<DiagnosticInfo_t>& DiagnosticInfos(void) { return diagnosticInfos; }

  virtual Status_t EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, DeleteMonitoredItemsResponse_t& result);
};

} // namespace uasdk

#endif //UASDK_INCLUDE_SUBSCRIPTIONS

#endif // _OPCUA_DELETE_MONITORED_ITEMS_RESPONSE_T_
