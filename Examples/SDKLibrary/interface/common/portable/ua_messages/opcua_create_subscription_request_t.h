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

#ifndef _OPCUA_CREATE_SUBSCRIPTION_REQUEST_T_
#define _OPCUA_CREATE_SUBSCRIPTION_REQUEST_T_

#include "opcua_request_message_t.h"
#include "opcua_string_t.h"
#include "opcua_request_header_t.h"
#include "opcua_array_ua_t.h"

#include "opcua_app_description_t.h"
#include "opcua_signature_data_t.h"
#include "opcua_mon_item_create_request_t.h"
#include "opcua_timestamps_to_return_t.h"
#include "opcua_boolean_t.h"
#include "opcua_byte_t.h"

#if (UASDK_INCLUDE_SUBSCRIPTIONS > 0)

namespace uasdk
{

class CreateSubscriptionRequest_t : public RequestMessage_t
{
private:
  Duration_t             requestedPublishingInterval;
  Counter_t              requestedLifetimeCount;
  Counter_t              requestedMaxKeepAliveCount;
  Counter_t              maxNotificationsPerPublish;
  Boolean_t              publishingEnabled;
  Byte_t                 priority;

  CreateSubscriptionRequest_t& operator=(CreateSubscriptionRequest_t const &);
  CreateSubscriptionRequest_t(CreateSubscriptionRequest_t const &);

public:
  static const uint32_t TYPE_ID = OpcUaId_CreateSubscriptionRequest;

  CreateSubscriptionRequest_t(){}
  virtual ~CreateSubscriptionRequest_t(){}

  uint32_t TypeId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return TYPE_ID;
  }

  uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return OpcUaId_CreateSubscriptionRequest_Encoding_DefaultBinary;
  }

  const Duration_t& RequestedPublishingInterval(void) const { return requestedPublishingInterval; }
  Duration_t& RequestedPublishingInterval(void) { return requestedPublishingInterval; }

  const Counter_t& RequestedLifetimeCount(void) const { return requestedLifetimeCount; }
  Counter_t& RequestedLifetimeCount(void) { return requestedLifetimeCount; }

  const Counter_t& RequestedMaxKeepAliveCount(void) const { return requestedMaxKeepAliveCount; }
  Counter_t& RequestedMaxKeepAliveCount(void) { return requestedMaxKeepAliveCount; }

  const Counter_t& MaxNotificationsPerPublish(void) const { return maxNotificationsPerPublish; }
  Counter_t& MaxNotificationsPerPublish(void) { return maxNotificationsPerPublish; }

  const Boolean_t& PublishingEnabled(void) const { return publishingEnabled; }
  Boolean_t& PublishingEnabled(void) { return publishingEnabled; }

  const Byte_t& Priority(void) const { return priority; }
  Byte_t& Priority(void) { return priority; }

  virtual Status_t EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, CreateSubscriptionRequest_t& result);

};

} // namespace uasdk

#endif //UASDK_INCLUDE_SUBSCRIPTIONS

#endif // _OPCUA_CREATE_SUBSCRIPTION_REQUEST_T_
