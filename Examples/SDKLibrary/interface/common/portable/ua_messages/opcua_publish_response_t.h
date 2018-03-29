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

#ifndef _OPCUA_PUBLISH_RESPONSE_T_
#define _OPCUA_PUBLISH_RESPONSE_T_


#include "opcua_response_message_t.h"
#include "opcua_endpoint_description_t.h"
#include "opcua_response_header_t.h"
#include "opcua_array_ua_t.h"

#include "opcua_mon_item_create_result_t.h"
#include "opcua_diagnostic_info_t.h"
#include "opcua_notification_message_t.h"
#include "opcua_boolean_t.h"

#if (UASDK_INCLUDE_SUBSCRIPTIONS > 0)

namespace uasdk
{

class PublishResponse_t : public ResponseMessage_t
{
private:
  IntegerId_t                   subscriptionId;
  ArrayUA_t<Counter_t>          availableSequenceNumbers;
  Boolean_t                     moreNotifications;
  NotificationMessage_t         notificationMessage;
  ArrayUA_t<StatusCode_t>       results;
  ArrayUA_t<DiagnosticInfo_t>   diagnosticInfos;

  PublishResponse_t& operator=(PublishResponse_t const &);
  PublishResponse_t(PublishResponse_t const &);

public:
  static const uint32_t TYPE_ID = OpcUaId_PublishResponse;

  PublishResponse_t() {};
  virtual ~PublishResponse_t(){}

  uint32_t TypeId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return TYPE_ID;
  }

  uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return OpcUaId_PublishResponse_Encoding_DefaultBinary;
  }

  const IntegerId_t& SubscriptionId(void) const { return subscriptionId; }
  IntegerId_t& SubscriptionId(void) { return subscriptionId; }

  const ArrayUA_t<Counter_t>& AvailableSequenceNumbers(void) const  { return availableSequenceNumbers;  }
  ArrayUA_t<Counter_t>& AvailableSequenceNumbers(void)  { return availableSequenceNumbers;  }

  const Boolean_t& MoreNotifications(void) const { return moreNotifications; }
  Boolean_t& MoreNotifications(void) { return moreNotifications; }

  const NotificationMessage_t& NotificationMessage(void) const  { return notificationMessage; }
  NotificationMessage_t& NotificationMessage(void) { return notificationMessage; }

  const ArrayUA_t<StatusCode_t>& Results(void) const {  return results; }
  ArrayUA_t<StatusCode_t>& Results(void) {  return results; }

  const ArrayUA_t<DiagnosticInfo_t>& DiagnosticInfos(void) const { return diagnosticInfos; }
  ArrayUA_t<DiagnosticInfo_t>& DiagnosticInfos(void) { return diagnosticInfos; }

  virtual Status_t EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, PublishResponse_t& result);
};

} // namespace uasdk

#endif //UASDK_INCLUDE_SUBSCRIPTIONS

#endif // _OPCUA_PUBLISH_RESPONSE_T_
