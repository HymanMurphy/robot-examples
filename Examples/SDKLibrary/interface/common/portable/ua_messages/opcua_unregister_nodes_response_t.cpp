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

#include "opcua_unregister_nodes_response_t.h"

namespace uasdk
{

Status_t UnregisterNodesResponse_t::EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const
{
  UASDK_UNUSED(encoder);
  UASDK_UNUSED(buffer);
#if (UASDK_INCLUDE_SERVER > 0)
  UASDK_UNUSED(encoder);
  UASDK_UNUSED(buffer);
  return 0;
#else
  UASDK_RETURN_BAD_STATUS(OpcUa_BadNotImplemented);
#endif  // (UASDK_INCLUDE_SERVER > 0)
}

Status_t UnregisterNodesResponse_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, UnregisterNodesResponse_t& result)
{
#if (UASDK_INCLUDE_CLIENT > 0)
  Status_t status = result.DecodeHeader(buffer, decoder);
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
