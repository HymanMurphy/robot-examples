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

#ifndef _OPCUA_FIND_SERVERS_ONNETWORK_REQUEST_T_
#define _OPCUA_FIND_SERVERS_ONNETWORK_REQUEST_T_


#include "opcua_request_message_t.h"
#include "opcua_string_t.h"
#include "opcua_request_header_t.h"
#include "opcua_array_ua_t.h"

#if (UASDK_INCLUDE_ADDITIONAL_DISCOVERY_SERVICES > 0)

namespace uasdk
{

class FindServersOnNetworkRequest_t : public RequestMessage_t
{
private:
  Counter_t              startingRecordId;
  UInt32_t   maxRecordsToReturn;
  ArrayUA_t<String_t>   serverCapabilityFilter;

  FindServersOnNetworkRequest_t& operator=(FindServersOnNetworkRequest_t const &);
  FindServersOnNetworkRequest_t(FindServersOnNetworkRequest_t const &);

public:
	static const uint32_t TYPE_ID = OpcUaId_FindServersOnNetworkRequest;

  FindServersOnNetworkRequest_t(){}
  virtual ~FindServersOnNetworkRequest_t(){}

  uint32_t TypeId(uint16_t& namespaceIndex) const;

  uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const;

  const Counter_t& StartingRecordId() const;
  Counter_t& StartingRecordId();

  const UInt32_t& MaxRecordsToReturn() const;
  UInt32_t& MaxRecordsToReturn();

  const ArrayUA_t<String_t>& ServerCapabilityFilter() const;
  ArrayUA_t<String_t>& ServerCapabilityFilter();

  virtual Status_t EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, FindServersOnNetworkRequest_t& result);

};

} // namespace uasdk

#endif

#endif // _OPCUA_FIND_SERVERS_ONNETWORK_REQUEST_T_
