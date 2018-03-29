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

#include "opcua_open_secure_channel_request_t.h"

namespace uasdk
{

Status_t OpenSecureChannelRequest_t::EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const
{
#if (UASDK_INCLUDE_CLIENT > 0)
  Status_t status = clientProtocolVersion.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = requestType.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = messageSecurityMode.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = clientNonce.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = requestedLifetime.Encode(encoder, buffer);
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

Status_t OpenSecureChannelRequest_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, OpenSecureChannelRequest_t& result)
{
#if (UASDK_INCLUDE_SERVER > 0)
  Status_t status = result.DecodeHeader(buffer, decoder);
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.ClientProtocolVersion());
  if (status.IsBad())
  {
    return status;
  }

  status = SecurityTokenRequestType_t::Decode(buffer, decoder, result.RequestType());
  if (status.IsBad())
  {
    return status;
  }

  status = MessageSecurityMode_t::Decode(buffer, decoder, result.MessageSecurityMode());
  if (status.IsBad())
  {
    return status;
  }

  status = ByteString_t::Decode(buffer, decoder, result.ClientNonce());
  if (status.IsBad())
  {
    return status;
  }

  status = Int32_t::Decode(buffer, decoder, result.RequestedLifetime());
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
