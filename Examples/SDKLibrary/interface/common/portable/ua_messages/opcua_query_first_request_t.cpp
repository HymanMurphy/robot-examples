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

#include "opcua_query_first_request_t.h"

#if (UASDK_INCLUDE_QUERY_SERVICE_SET > 0)

namespace uasdk
{


	const uasdk::ViewDescription_t& QueryFirstRequest_t::View() const
	{
		return view;
	}

	uasdk::ViewDescription_t& QueryFirstRequest_t::View()
	{
		return view;
	}


	const uasdk::ArrayUA_t<uasdk::NodeTypeDescription_t>& QueryFirstRequest_t::NodeTypes() const
	{
		return nodeTypes;
	}
	
	uasdk::ArrayUA_t<uasdk::NodeTypeDescription_t>& QueryFirstRequest_t::NodeTypes()
	{
		return nodeTypes;
	}


	const ContentFilter_t& QueryFirstRequest_t::Filter(void) const
	{
		return filter;
	}
	
	ContentFilter_t& QueryFirstRequest_t::Filter(void)
	{
		return filter;
	}


	const uasdk::Counter_t& QueryFirstRequest_t::MaxDataSetsToReturn(void) const
	{
		return maxDataSetsToReturn;
	}
	
	uasdk::Counter_t& QueryFirstRequest_t::MaxDataSetsToReturn(void)
	{
		return maxDataSetsToReturn;
	}
	
	const uasdk::Counter_t& QueryFirstRequest_t::MaxReferencesToReturn(void) const
	{
		return maxReferencesToReturn;
	}

	uasdk::Counter_t& QueryFirstRequest_t::MaxReferencesToReturn(void)
	{
		return maxReferencesToReturn;
	}

Status_t QueryFirstRequest_t::EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const
{
#if (UASDK_INCLUDE_CLIENT > 0)
  Status_t status = view.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = nodeTypes.Encode(encoder, buffer);
  if (status.IsBad())
  {
	  return status;
  }
// TODO
//   status = filter.Encode(encoder, buffer);
//   if (status.IsBad())
//   {
// 	  return status;
//   }

  status = maxDataSetsToReturn.Encode(encoder, buffer);
  if (status.IsBad())
  {
	  return status;
  }

  status = maxReferencesToReturn.Encode(encoder, buffer);
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

Status_t QueryFirstRequest_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, QueryFirstRequest_t& result)
{
#if (UASDK_INCLUDE_SERVER > 0)
  Status_t status = result.DecodeHeader(buffer, decoder);
  if (status.IsBad())
  {
    return status;
  }
  
  status = ViewDescription_t::Decode(buffer, decoder, result.View());
  if (status.IsBad())
  {
	  return status;
  }

  status = ArrayUA_t<NodeTypeDescription_t>::Decode(buffer, decoder, result.NodeTypes());
  if (status.IsBad())
  {
    return status;
  }

  //TODO
//   status = ContentFilter_t::Decode(buffer, decoder, result.Filter());
//   if (status.IsBad())
//   {
// 	  return status;
//   }

  status = Counter_t::Decode(buffer, decoder, result.MaxDataSetsToReturn());
  if (status.IsBad())
  {
	  return status;
  }

  status = Counter_t::Decode(buffer, decoder, result.MaxReferencesToReturn());
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

