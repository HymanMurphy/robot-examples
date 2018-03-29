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

#include "opcua_set_monitoring_mode_request_t.h"

#if (UASDK_INCLUDE_SUBSCRIPTIONS > 0)

namespace uasdk
{

Status_t SetMonitoringModeRequest_t::EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const
{
#if (UASDK_INCLUDE_CLIENT > 0)
  Status_t status = subscriptionId.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = monitoringMode.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = monitoredItemIds.Encode(encoder, buffer);
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

Status_t SetMonitoringModeRequest_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, SetMonitoringModeRequest_t& result)
{
#if (UASDK_INCLUDE_SERVER > 0)
  Status_t status = result.DecodeHeader(buffer, decoder);
  if (status.IsBad())
  {
    return status;
  }

  status = IntegerId_t::Decode(buffer, decoder, result.SubscriptionId());
  if (status.IsBad())
  {
    return status;
  }

  status = MonitoringMode_t::Decode(buffer, decoder, result.MonitoringMode());
  if (status.IsBad())
  {
    return status;
  }

  status = ArrayUA_t<IntegerId_t>::Decode(buffer, decoder, result.MonitoredItemIds());
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
