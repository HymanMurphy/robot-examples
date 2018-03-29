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

#ifndef _OPCUA_TRANSFER_SUBSCRIPTIONS_REQUEST_T_
#define _OPCUA_TRANSFER_SUBSCRIPTIONS_REQUEST_T_


#include "opcua_request_message_t.h"
#include "opcua_string_t.h"
#include "opcua_request_header_t.h"
#include "opcua_array_ua_t.h"

#include "opcua_app_description_t.h"
#include "opcua_signature_data_t.h"
#include "opcua_mon_item_create_request_t.h"
#include "opcua_timestamps_to_return_t.h"
#include "opcua_uint32_t.h"
#include "opcua_boolean_t.h"

#if (UASDK_INCLUDE_SUBSCRIPTIONS > 0 && UASDK_INCLUDE_TRANSFER_SUBSCRIPTIONS_SERVICE > 0)

namespace uasdk
{

class TransferSubscriptionsRequest_t : public RequestMessage_t
{
private:
  ArrayUA_t<IntegerId_t>    subscriptionIds;
  Boolean_t                 sendInitialValues;

  TransferSubscriptionsRequest_t& operator=(TransferSubscriptionsRequest_t const &);
  TransferSubscriptionsRequest_t(TransferSubscriptionsRequest_t const &);

public:
  static const uint32_t TYPE_ID = OpcUaId_TransferSubscriptionsRequest;

  TransferSubscriptionsRequest_t(){}
  virtual ~TransferSubscriptionsRequest_t(){}

  uint32_t TypeId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return TYPE_ID;
  }

  uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return OpcUaId_TransferSubscriptionsRequest_Encoding_DefaultBinary;
  }

  const ArrayUA_t<IntegerId_t>& SubscriptionIds(void) const { return subscriptionIds; }
  ArrayUA_t<IntegerId_t>& SubscriptionIds(void) { return subscriptionIds; }

  const Boolean_t& SendInitialValues(void) const { return sendInitialValues; }
  Boolean_t& SendInitialValues(void) { return sendInitialValues; }

  virtual Status_t EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, TransferSubscriptionsRequest_t& result);

};

} // namespace uasdk

#endif

#endif // _OPCUA_TRANSFER_SUBSCRIPTIONS_REQUEST_T_
