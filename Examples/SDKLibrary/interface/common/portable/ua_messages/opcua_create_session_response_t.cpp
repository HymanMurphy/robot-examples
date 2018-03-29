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

#include "opcua_create_session_response_t.h"

namespace uasdk
{

Status_t CreateSessionResponse_t::EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const
{
#if (UASDK_INCLUDE_SERVER > 0)
  Status_t status = encoder.Encode(sessionId, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = encoder.Encode(authenticationToken, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = revisedSessionTimeout.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = serverNonce.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = serverCertificate.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = serverEndpoints.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = serverSoftwareCertificates.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = serverSignature.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = maxRequestMessageSize.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return 0;
#else
  UASDK_RETURN_BAD_STATUS(OpcUa_BadNotImplemented);
#endif  // (UASDK_INCLUDE_SERVER > 0)
}

Status_t CreateSessionResponse_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, CreateSessionResponse_t& result)
{
#if (UASDK_INCLUDE_CLIENT > 0)
  Status_t status = result.DecodeHeader(buffer, decoder);
  if (status.IsBad())
  {
    return status;
  }

  IntrusivePtr_t<NodeId_t> localSessionId;
  status = NodeId_t::Decode(buffer, decoder, localSessionId);
  if (status.IsBad() || !localSessionId.is_set())
  {
    return status;
  }
  else
  {
	  result.SessionId() = localSessionId;
  }

  IntrusivePtr_t<NodeId_t> localAuthenticationToken;
  status = NodeId_t::Decode(buffer, decoder, localAuthenticationToken);
  if (status.IsBad() || !localAuthenticationToken.is_set())
  {
    return status;
  }
  else
  {
	  result.AuthenticationToken() = localAuthenticationToken;
  }

  status = Duration_t::Decode(buffer, decoder, result.RevisedSessionTimeout());
  if (status.IsBad())
  {
    return status;
  }

  status = ByteString_t::Decode(buffer, decoder, result.ServerNonce());
  if (status.IsBad())
  {
    return status;
  }

  status = ByteString_t::Decode(buffer, decoder, result.ServerCertificate());
  if (status.IsBad())
  {
    return status;
  }

  status = ArrayUA_t<EndpointDescription_t>::Decode(buffer, decoder, result.ServerEndpoints());
  if (status.IsBad())
  {
    return status;
  }

  status = ArrayUA_t<ByteString_t>::Decode(buffer, decoder, result.ServerSoftwareCertificates());
  if (status.IsBad())
  {
    return status;
  }

  status = SignatureData_t::Decode(buffer, decoder, result.ServerSignature());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.MaxRequestMessageSize());
  if (status.IsBad())
  {
    return status;
  }

  return 0;
#else
  UASDK_UNUSED(buffer);
  UASDK_UNUSED(decoder);
  UASDK_UNUSED(result);
  UASDK_RETURN_BAD_STATUS(OpcUa_BadNotImplemented);
#endif  // (UASDK_INCLUDE_CLIENT > 0)
}

} // namespace uasdk
