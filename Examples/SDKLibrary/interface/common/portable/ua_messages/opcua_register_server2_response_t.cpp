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

#include "opcua_register_server2_response_t.h"

#if (UASDK_INCLUDE_ADDITIONAL_DISCOVERY_SERVICES > 0)

namespace uasdk
{


	const uasdk::ArrayUA_t<uasdk::StatusCode_t>& RegisterServer2Response_t::ConfigurationResults() const
	{
		return configurationResults;
	}


	uasdk::ArrayUA_t<uasdk::StatusCode_t>& RegisterServer2Response_t::ConfigurationResults()
	{
		return configurationResults;
	}


	const uasdk::ArrayUA_t<uasdk::DiagnosticInfo_t>& RegisterServer2Response_t::DiagnosticInfos() const
	{
		return diagnosticInfos;
	}


	uasdk::ArrayUA_t<uasdk::DiagnosticInfo_t>& RegisterServer2Response_t::DiagnosticInfos()
	{
		return diagnosticInfos;
	}

Status_t RegisterServer2Response_t::EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const
{
#if (UASDK_INCLUDE_SERVER > 0)
  Status_t status = configurationResults.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = diagnosticInfos.Encode(encoder, buffer);
  if (status.IsBad())
  {
	  return status;
}

  return 0;
#else
  UASDK_RETURN_BAD_STATUS(OpcUa_BadNotImplemented);
#endif  // (UASDK_INCLUDE_SERVER > 0)
}

Status_t RegisterServer2Response_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, RegisterServer2Response_t& result)
{
#if (UASDK_INCLUDE_CLIENT > 0)
  Status_t status = result.DecodeHeader(buffer, decoder);
  if (status.IsBad())
  {
    return status;
  }

  status = ArrayUA_t<StatusCode_t>::Decode(buffer, decoder, result.ConfigurationResults());
  if (status.IsBad())
  {
    return status;
  }

  status = ArrayUA_t<DiagnosticInfo_t>::Decode(buffer, decoder, result.DiagnosticInfos());
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

#endif

