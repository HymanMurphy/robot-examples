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

#include "opcua_delete_nodes_request_t.h"

#if (UASDK_INCLUDE_NODE_MANAGEMENT_SERVICE_SET > 0)

namespace uasdk
{


	const uasdk::ArrayUA_t<uasdk::DeleteNodesItem_t>& DeleteNodesRequest_t::NodesToDelete() const
	{
		return nodesToDelete;
	}


	uasdk::ArrayUA_t<uasdk::DeleteNodesItem_t>& DeleteNodesRequest_t::NodesToDelete()
	{
		return nodesToDelete;
	}

Status_t DeleteNodesRequest_t::EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const
{
#if (UASDK_INCLUDE_CLIENT > 0)
  
  Status_t status = nodesToDelete.Encode(encoder, buffer);
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

Status_t DeleteNodesRequest_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, DeleteNodesRequest_t& result)
{
#if (UASDK_INCLUDE_SERVER > 0)
  Status_t status = result.DecodeHeader(buffer, decoder);
  if (status.IsBad())
  {
    return status;
  }

  status = ArrayUA_t<DeleteNodesItem_t>::Decode(buffer, decoder, result.NodesToDelete());
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

#endif
