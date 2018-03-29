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

#include "opcua_create_session_request_t.h"

namespace uasdk
{

Status_t CreateSessionRequest_t::EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const
{
#if (UASDK_INCLUDE_CLIENT > 0)
  Status_t status = clientDescription.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = serverUri.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = endpointUrl.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = sessionName.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = clientNonce.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = clientCertificate.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = requestedSessionTimeout.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = maxResponseMessageSize.Encode(encoder, buffer);
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

Status_t CreateSessionRequest_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, CreateSessionRequest_t& result)
{
#if (UASDK_INCLUDE_SERVER > 0)
  Status_t status = result.DecodeHeader(buffer, decoder);
  if (status.IsBad())
  {
    return status;
  }

  status = AppDescription_t::Decode(buffer, decoder, result.ClientDescription());
  if (status.IsBad())
  {
    return status;
  }

  status = String_t::Decode(buffer, decoder, result.ServerUri());
  if (status.IsBad())
  {
    return status;
  }

  status = String_t::Decode(buffer, decoder, result.EndpointUrl());
  if (status.IsBad())
  {
    return status;
  }

  status = String_t::Decode(buffer, decoder, result.SessionName());
  if (status.IsBad())
  {
    return status;
  }

  status = ByteString_t::Decode(buffer, decoder, result.ClientNonce());
  if (status.IsBad())
  {
    return status;
  }

  status = ByteString_t::Decode(buffer, decoder, result.ClientCertificate());
  if (status.IsBad())
  {
    return status;
  }

  status = Duration_t::Decode(buffer, decoder, result.RequestedSessionTimeout());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.MaxResponseMessageSize());
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
