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

#ifndef _OPCUA_SET_MONITORING_MODE_REQUEST_T_
#define _OPCUA_SET_MONITORING_MODE_REQUEST_T_


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

class SetMonitoringModeRequest_t : public RequestMessage_t
{
private:
  IntegerId_t               subscriptionId;
  MonitoringMode_t          monitoringMode;
  ArrayUA_t<IntegerId_t>    monitoredItemIds;

  SetMonitoringModeRequest_t& operator=(SetMonitoringModeRequest_t const &);
  SetMonitoringModeRequest_t(SetMonitoringModeRequest_t const &);

public:
  static const uint32_t TYPE_ID = OpcUaId_SetMonitoringModeRequest;

  SetMonitoringModeRequest_t(){}
  virtual ~SetMonitoringModeRequest_t(){}

  uint32_t TypeId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return TYPE_ID;
  }

  uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return OpcUaId_SetMonitoringModeRequest_Encoding_DefaultBinary;
  }

  const IntegerId_t& SubscriptionId(void) const { return subscriptionId; }
  IntegerId_t& SubscriptionId(void) { return subscriptionId; }

  const MonitoringMode_t& MonitoringMode(void) const { return monitoringMode; }
  MonitoringMode_t& MonitoringMode(void) { return monitoringMode; }

  const ArrayUA_t<IntegerId_t>& MonitoredItemIds(void) const { return monitoredItemIds; }
  ArrayUA_t<IntegerId_t>& MonitoredItemIds(void) { return monitoredItemIds; }

  virtual Status_t EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, SetMonitoringModeRequest_t& result);
};

} // namespace uasdk

#endif //UASDK_INCLUDE_SUBSCRIPTIONS

#endif // _OPCUA_SET_MONITORING_MODE_REQUEST_T_
