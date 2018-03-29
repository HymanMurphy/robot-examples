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

#ifndef _OPCUA_MODIFY_MONITORED_ITEMS_REQUEST_T_
#define _OPCUA_MODIFY_MONITORED_ITEMS_REQUEST_T_


#include "opcua_request_message_t.h"
#include "opcua_string_t.h"
#include "opcua_request_header_t.h"
#include "opcua_array_ua_t.h"

#include "opcua_app_description_t.h"
#include "opcua_signature_data_t.h"
#include "opcua_mon_item_create_request_t.h"
#include "opcua_timestamps_to_return_t.h"
#include "opcua_uint32_t.h"
#include "opcua_mon_item_modify_request_t.h"

#if (UASDK_INCLUDE_SUBSCRIPTIONS > 0)

namespace uasdk
{

class ModifyMonitoredItemsRequest_t : public RequestMessage_t
{
private:
  IntegerId_t                         subscriptionId;
  TimestampsToReturn_t                timestampsToReturn;
  ArrayUA_t<MonItemModifyRequest_t>   itemsToModify;

  ModifyMonitoredItemsRequest_t& operator=(ModifyMonitoredItemsRequest_t const &);
  ModifyMonitoredItemsRequest_t(ModifyMonitoredItemsRequest_t const &);

public:
  static const uint32_t TYPE_ID = OpcUaId_ModifyMonitoredItemsRequest;

  ModifyMonitoredItemsRequest_t(){}
  virtual ~ModifyMonitoredItemsRequest_t(){}

  uint32_t TypeId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return TYPE_ID;
  }

  uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return OpcUaId_ModifyMonitoredItemsRequest_Encoding_DefaultBinary;
  }

  const IntegerId_t& SubscriptionId(void) const { return subscriptionId; }
  IntegerId_t& SubscriptionId(void) { return subscriptionId; }

  const TimestampsToReturn_t& TimestampsToReturn(void) const { return timestampsToReturn; }
  TimestampsToReturn_t& TimestampsToReturn(void) { return timestampsToReturn; }

  const ArrayUA_t<MonItemModifyRequest_t>& ItemsToModify(void) const { return itemsToModify; }
  ArrayUA_t<MonItemModifyRequest_t>& ItemsToModify(void) { return itemsToModify; }

  virtual Status_t EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, ModifyMonitoredItemsRequest_t& result);
};

} // namespace uasdk

#endif //UASDK_INCLUDE_SUBSCRIPTIONS

#endif // _OPCUA_MODIFY_MONITORED_ITEMS_REQUEST_T_
