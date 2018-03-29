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

const char FILENAME[] = "opcua_create_subscription_request_t.cpp";

#include "opcua_create_subscription_request_t.h"

#if (UASDK_INCLUDE_SUBSCRIPTIONS > 0)

namespace uasdk
{

Status_t CreateSubscriptionRequest_t::EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const
{
#if (UASDK_INCLUDE_CLIENT > 0)
  Status_t status = requestedPublishingInterval.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = requestedLifetimeCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = requestedMaxKeepAliveCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = maxNotificationsPerPublish.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = publishingEnabled.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = priority.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return 0;
#else
  UASDK_UNUSED(encoder);
  UASDK_UNUSED(buffer);
  UASDK_RETURN_BAD_STATUS(OpcUa_BadNotImplemented);
#endif  // (UASDK_INCLUDE_CLIENT > 0)
}

Status_t CreateSubscriptionRequest_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, CreateSubscriptionRequest_t& result)
{
#if (UASDK_INCLUDE_SERVER > 0)
  Status_t status = result.DecodeHeader(buffer, decoder);
  if (status.IsBad())
  {
    return status;
  }

  status = Duration_t::Decode(buffer, decoder, result.RequestedPublishingInterval());
  if (status.IsBad())
  {
    return status;
  }

  status = Counter_t::Decode(buffer, decoder, result.RequestedLifetimeCount());
  if (status.IsBad())
  {
    return status;
  }

  status = Counter_t::Decode(buffer, decoder, result.RequestedMaxKeepAliveCount());
  if (status.IsBad())
  {
    return status;
  }

  status = Counter_t::Decode(buffer, decoder, result.MaxNotificationsPerPublish());
  if (status.IsBad())
  {
    return status;
  }

  status = Boolean_t::Decode(buffer, decoder, result.PublishingEnabled());
  if (status.IsBad())
  {
    return status;
  }

  status = Byte_t::Decode(buffer, decoder, result.Priority());
  if (status.IsBad())
  {
    return status;
  }

  return 0;
#else
  UASDK_RETURN_BAD_STATUS(OpcUa_BadNotImplemented);
#endif  // (UASDK_INCLUDE_SERVER > 0)
}

} // namespace uasdk

#endif //UASDK_INCLUDE_SUBSCRIPTIONS
