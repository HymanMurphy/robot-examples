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

#ifndef _OPCUA_MODIFY_SUBSCRIPTION_RESPONSE_T_
#define _OPCUA_MODIFY_SUBSCRIPTION_RESPONSE_T_


#include "opcua_response_message_t.h"
#include "opcua_endpoint_description_t.h"
#include "opcua_response_header_t.h"
#include "opcua_array_ua_t.h"

#include "opcua_mon_item_create_result_t.h"
#include "opcua_diagnostic_info_t.h"

#if (UASDK_INCLUDE_SUBSCRIPTIONS > 0)

namespace uasdk
{

class ModifySubscriptionResponse_t : public ResponseMessage_t
{
private:
  Duration_t         revisedPublishingInterval;
  Counter_t          revisedLifetimeCount;
  Counter_t          revisedMaxKeepAliveCount;

  ModifySubscriptionResponse_t& operator=(ModifySubscriptionResponse_t const &);
  ModifySubscriptionResponse_t(ModifySubscriptionResponse_t const &);

public:
  static const uint32_t TYPE_ID = OpcUaId_ModifySubscriptionResponse;

  ModifySubscriptionResponse_t() {};
  virtual ~ModifySubscriptionResponse_t(){}

  uint32_t TypeId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return TYPE_ID;
  }

  uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return OpcUaId_ModifySubscriptionResponse_Encoding_DefaultBinary;
  }

  const Duration_t& RevisedPublishingInterval(void) const  { return revisedPublishingInterval; }
  Duration_t& RevisedPublishingInterval(void)  { return revisedPublishingInterval; }

  const Counter_t& RevisedLifetimeCount(void) const  { return revisedLifetimeCount; }
  Counter_t& RevisedLifetimeCount(void)  { return revisedLifetimeCount; }

  const Counter_t& RevisedMaxKeepAliveCount(void) const  { return revisedMaxKeepAliveCount;  }
  Counter_t& RevisedMaxKeepAliveCount(void)  { return revisedMaxKeepAliveCount;  }

  virtual Status_t EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, ModifySubscriptionResponse_t& result);
};

} // namespace uasdk

#endif //UASDK_INCLUDE_SUBSCRIPTIONS

#endif // _OPCUA_MODIFY_SUBSCRIPTION_RESPONSE_T_
