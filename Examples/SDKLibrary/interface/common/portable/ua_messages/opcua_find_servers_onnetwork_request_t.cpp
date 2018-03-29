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

#include "opcua_find_servers_onnetwork_request_t.h"

#if (UASDK_INCLUDE_ADDITIONAL_DISCOVERY_SERVICES > 0)

namespace uasdk
{

Status_t FindServersOnNetworkRequest_t::EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const
{
#if (UASDK_INCLUDE_CLIENT > 0)
  Status_t status = startingRecordId.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = maxRecordsToReturn.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = serverCapabilityFilter.Encode(encoder, buffer);
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

Status_t FindServersOnNetworkRequest_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, FindServersOnNetworkRequest_t& result)
{
#if (UASDK_INCLUDE_SERVER > 0)
  Status_t status = result.DecodeHeader(buffer, decoder);
  if (status.IsBad())
  {
    return status;
  }

  status = Counter_t::Decode(buffer, decoder, result.StartingRecordId());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.MaxRecordsToReturn());
  if (status.IsBad())
  {
    return status;
  }

  status = ArrayUA_t<String_t>::Decode(buffer, decoder, result.ServerCapabilityFilter());
  if (status.IsBad())
  {
    return status;
  }

  return 0;
#else
  UASDK_RETURN_BAD_STATUS(OpcUa_BadNotImplemented);
#endif  // (UASDK_INCLUDE_SERVER > 0)
}

const Counter_t& FindServersOnNetworkRequest_t::StartingRecordId() const
{
	return startingRecordId;
}

Counter_t& FindServersOnNetworkRequest_t::StartingRecordId()
{
	return startingRecordId;
}

const UInt32_t& FindServersOnNetworkRequest_t::MaxRecordsToReturn() const
{
	return maxRecordsToReturn;
}

UInt32_t& FindServersOnNetworkRequest_t::MaxRecordsToReturn()
{
	return maxRecordsToReturn;
}

const ArrayUA_t<String_t>& FindServersOnNetworkRequest_t::ServerCapabilityFilter() const
{
	return serverCapabilityFilter;
}

ArrayUA_t<String_t>& FindServersOnNetworkRequest_t::ServerCapabilityFilter()
{
	return serverCapabilityFilter;
}

uint32_t FindServersOnNetworkRequest_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
	namespaceIndex = 0; return OpcUaId_FindServersOnNetworkRequest_Encoding_DefaultBinary;
}

uint32_t FindServersOnNetworkRequest_t::TypeId(uint16_t& namespaceIndex) const
{
	namespaceIndex = 0; return TYPE_ID;
}

} // namespace uasdk

#endif

