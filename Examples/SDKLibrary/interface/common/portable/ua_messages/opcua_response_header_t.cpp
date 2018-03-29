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

#include "opcua_response_header_t.h"
#include "icodec_t.h"

namespace uasdk
{

ResponseHeader_t::ResponseHeader_t() : requestHandle(0), serviceResult(0), additionalHeader()
{
}

ResponseHeader_t::~ResponseHeader_t(void)
{
}

Status_t ResponseHeader_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
#if (UASDK_INCLUDE_SERVER > 0)
  Status_t status = timestamp.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = requestHandle.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = serviceResult.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = serviceDiagnostics.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = stringTable.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = encoder.EncodeExtensionObject(additionalHeader.Payload(), buffer);
  if (status.IsBad())
  {
    return status;
  }

  return 0;
#else
  UASDK_RETURN_BAD_STATUS(OpcUa_BadNotImplemented);
#endif  // (UASDK_INCLUDE_SERVER > 0)
}

Status_t ResponseHeader_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, ResponseHeader_t& result)
{
#if (UASDK_INCLUDE_CLIENT > 0)
  Status_t status = DateTime_t::Decode(buffer, decoder, result.Timestamp());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.RequestHandle());
  if (status.IsBad())
  {
    return status;
  }

  status = StatusCode_t::Decode(buffer, decoder, result.ServiceResult());
  if (status.IsBad())
  {
    return status;
  }

  status = DiagnosticInfo_t::Decode(buffer, decoder, result.ServiceDiagnostics());
  if (status.IsBad())
  {
    return status;
  }

  status = ArrayUA_t<String_t>::Decode(buffer, decoder, result.StringTable());
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
  UASDK_UNUSED(buffer);
  UASDK_UNUSED(decoder);
  UASDK_UNUSED(result);
  UASDK_RETURN_BAD_STATUS(OpcUa_BadNotImplemented);
#endif  // (UASDK_INCLUDE_CLIENT > 0)
}

} // namespace uasdk
