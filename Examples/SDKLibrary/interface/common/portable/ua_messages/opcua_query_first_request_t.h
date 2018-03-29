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

#ifndef _OPCUA_QUERY_FIRST_REQUEST_T_
#define _OPCUA_QUERY_FIRST_REQUEST_T_

#include "opcua_request_message_t.h"
#include "opcua_view_description_t.h"
#include "opcua_array_ua_t.h"
#include "opcua_nodetype_description_t.h"
#include "opcua_uint32_t.h"


#if (UASDK_INCLUDE_QUERY_SERVICE_SET > 0)

//TODO:ContenFilter will be provided by Collin's team
typedef void* ContentFilter_t;

namespace uasdk
{

class QueryFirstRequest_t : public RequestMessage_t
{
private:
	ViewDescription_t view;
	ArrayUA_t<NodeTypeDescription_t> nodeTypes;
	ContentFilter_t		filter;
	Counter_t		maxDataSetsToReturn;
	Counter_t     maxReferencesToReturn;

	QueryFirstRequest_t& operator=(QueryFirstRequest_t const &);
	QueryFirstRequest_t(QueryFirstRequest_t const &);

public:
  static const uint32_t TYPE_ID = OpcUaId_QueryFirstRequest;

  QueryFirstRequest_t(){}
  virtual ~QueryFirstRequest_t(){}

  uint32_t TypeId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return TYPE_ID;
  }

  uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return OpcUaId_QueryFirstRequest_Encoding_DefaultBinary;
  }

  const ViewDescription_t& View() const;
  ViewDescription_t& View();

  const ArrayUA_t<NodeTypeDescription_t>& NodeTypes() const;
  ArrayUA_t<NodeTypeDescription_t>& NodeTypes();

  const ContentFilter_t& Filter(void) const;
  ContentFilter_t& Filter(void);

  const Counter_t& MaxDataSetsToReturn(void) const;
  Counter_t& MaxDataSetsToReturn(void);

  const Counter_t& MaxReferencesToReturn(void) const;
  Counter_t& MaxReferencesToReturn(void);

  virtual Status_t EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, QueryFirstRequest_t& result);

};

} // namespace uasdk

#endif

#endif // _OPCUA_QUERY_FIRST_REQUEST_T_
