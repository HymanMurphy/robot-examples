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

#ifndef _OPCUA_SET_TRIGGERING_REQUEST_T_
#define _OPCUA_SET_TRIGGERING_REQUEST_T_


#include "opcua_request_message_t.h"
#include "opcua_string_t.h"
#include "opcua_request_header_t.h"
#include "opcua_array_ua_t.h"

#include "opcua_app_description_t.h"

#if (UASDK_INCLUDE_SUBSCRIPTIONS > 0)

namespace uasdk
{

class SetTriggeringRequest_t : public RequestMessage_t
{
private:
  IntegerId_t               subscriptionId;
  IntegerId_t               triggeringItemId;
  ArrayUA_t<IntegerId_t>    linksToAdd;
  ArrayUA_t<IntegerId_t>    linksToRemove;

  SetTriggeringRequest_t& operator=(SetTriggeringRequest_t const &);
  SetTriggeringRequest_t(SetTriggeringRequest_t const &);

public:
  static const uint32_t TYPE_ID = OpcUaId_SetTriggeringRequest;

  SetTriggeringRequest_t(){}
  virtual ~SetTriggeringRequest_t(){}

  uint32_t TypeId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return TYPE_ID;
  }

  uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return OpcUaId_SetTriggeringRequest_Encoding_DefaultBinary;
  }

  const IntegerId_t& SubscriptionId(void) const { return subscriptionId; }
  IntegerId_t& SubscriptionId(void) { return subscriptionId; }

  const IntegerId_t& TriggeringItemId(void) const { return triggeringItemId; }
  IntegerId_t& TriggeringItemId(void) { return triggeringItemId; }

  const ArrayUA_t<IntegerId_t>& LinksToAdd(void) const { return linksToAdd; }
  ArrayUA_t<IntegerId_t>& LinksToAdd(void) { return linksToAdd; }

  const ArrayUA_t<IntegerId_t>& LinksToRemove(void) const { return linksToRemove; }
  ArrayUA_t<IntegerId_t>& LinksToRemove(void) { return linksToRemove; }

  virtual Status_t EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, SetTriggeringRequest_t& result);

};

} // namespace uasdk

#endif //UASDK_INCLUDE_SUBSCRIPTIONS

#endif // _OPCUA_SET_TRIGGERING_REQUEST_T_
