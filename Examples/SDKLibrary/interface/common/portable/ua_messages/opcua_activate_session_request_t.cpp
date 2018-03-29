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

#include "opcua_activate_session_request_t.h"

namespace uasdk
{

Status_t ActivateSessionRequest_t::EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const
{
#if (UASDK_INCLUDE_CLIENT > 0)
  Status_t status = clientSignature.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = clientSoftwareCertificates.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = localeIds.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = userIdentityToken.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = userTokenSignature.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return status;
#else
  UASDK_UNUSED(encoder);
  UASDK_UNUSED(buffer);
  UASDK_RETURN_BAD_STATUS(OpcUa_BadNotImplemented);
#endif  // (UASDK_INCLUDE_CLIENT > 0)
}

Status_t ActivateSessionRequest_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, ActivateSessionRequest_t& result)
{
#if (UASDK_INCLUDE_SERVER > 0)
  Status_t status = result.DecodeHeader(buffer, decoder);
  if (status.IsBad())
  {
    return status;
  }

  status = SignatureData_t::Decode(buffer, decoder, result.ClientSignature());
  if (status.IsBad())
  {
    return status;
  }
  
  status = ArrayUA_t<ByteString_t>::Decode(buffer, decoder, result.ClientSoftwareCertificates());
  if (status.IsBad())
  {
    return status;
  }

  status = ArrayUA_t<String_t>::Decode(buffer, decoder, result.LocaleIds());
  if (status.IsBad())
  {
    return status;
  }

  status = ExtensibleParameter_t::Decode(buffer, decoder, result.UserIdentityToken());
  if (status.IsBad())
  {
    return status;
  }

  status = SignatureData_t::Decode(buffer, decoder, result.UserTokenSignature());
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
