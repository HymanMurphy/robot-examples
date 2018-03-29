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

#include "opcua_request_header_t.h"
#include "opcua_extensible_parameter_t.h"
#include "icodec_t.h"

namespace uasdk
{

RequestHeader_t::RequestHeader_t() : requestHandle(0), returnDiagnostics(0),
    timeoutHint(0), additionalHeader()
{
}

RequestHeader_t::~RequestHeader_t(void)
{
}

Status_t RequestHeader_t::CopyFrom(const RequestHeader_t& source)
{
  Status_t status;
  if (source.authenticationToken.is_set())
  {
    source.authenticationToken->CopyToNodeId(authenticationToken);
    if (status.IsBad())
    {
      return status;
    }
  }
  else
  {
    authenticationToken.reset();
  }
  status = timestamp.CopyFrom(source.timestamp);
  if (status.IsBad())
  {
    return status;
  }
  status = requestHandle.CopyFrom(source.requestHandle);
  if (status.IsBad())
  {
    return status;
  }
  status = returnDiagnostics.CopyFrom(source.returnDiagnostics);
  if (status.IsBad())
  {
    return status;
  }
  status = auditEntry.CopyFrom(source.auditEntry);
  if (status.IsBad())
  {
    return status;
  }
  status = timeoutHint.CopyFrom(source.timeoutHint);
  if (status.IsBad())
  {
    return status;
  }
  return additionalHeader.CopyFrom(source.additionalHeader);
}

Status_t RequestHeader_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
#if (UASDK_INCLUDE_CLIENT > 0)
  Status_t status = encoder.Encode(authenticationToken, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = timestamp.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = requestHandle.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = returnDiagnostics.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = auditEntry.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = timeoutHint.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = additionalHeader.Encode(encoder, buffer);
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

Status_t RequestHeader_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, RequestHeader_t& result)
{
#if (UASDK_INCLUDE_SERVER > 0)
  Status_t status = NodeId_t::Decode(buffer, decoder, result.AuthenticationToken());
  if (status.IsBad())
  {
    return status;
  }

  status = DateTime_t::Decode(buffer, decoder, result.Timestamp());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.RequestHandle());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.ReturnDiagnostics());
  if (status.IsBad())
  {
    return status;
  }

  status = String_t::Decode(buffer, decoder, result.AuditEntry());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.TimeoutHint());
  if (status.IsBad())
  {
    return status;
  }

  status = ExtensibleParameter_t::Decode(buffer, decoder, result.AdditionalHeader());
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
