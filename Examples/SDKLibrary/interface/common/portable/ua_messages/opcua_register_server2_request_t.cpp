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

#include "opcua_register_server2_request_t.h"

#if (UASDK_INCLUDE_ADDITIONAL_DISCOVERY_SERVICES > 0)

namespace uasdk
{


	const uasdk::RegisteredServer_t& RegisterServer2Request_t::Server() const
	{
		return server;
	}


	uasdk::RegisteredServer_t& RegisterServer2Request_t::Server()
	{
		return server;
	}


	const uasdk::ArrayUA_t<uasdk::ExtensibleParameter_t>& RegisterServer2Request_t::DiscoveryConfiguration() const
	{
		return discoveryConfiguration;
	}


	uasdk::ArrayUA_t<uasdk::ExtensibleParameter_t>& RegisterServer2Request_t::DiscoveryConfiguration()
	{
		return discoveryConfiguration;
	}

Status_t RegisterServer2Request_t::EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const
{
#if (UASDK_INCLUDE_CLIENT > 0)
  Status_t status = server.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = discoveryConfiguration.Encode(encoder, buffer);
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

Status_t RegisterServer2Request_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, RegisterServer2Request_t& result)
{
#if (UASDK_INCLUDE_SERVER > 0)
  Status_t status = result.DecodeHeader(buffer, decoder);
  if (status.IsBad())
  {
    return status;
  }

  status = RegisteredServer_t::Decode(buffer, decoder, result.Server());
  if (status.IsBad())
  {
    return status;
  }

  status = ArrayUA_t<ExtensibleParameter_t>::Decode(buffer, decoder, result.DiscoveryConfiguration());
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

