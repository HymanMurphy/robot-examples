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

#ifndef _OPCUA_READ_REQUEST_T_
#define _OPCUA_READ_REQUEST_T_


#include "opcua_request_message_t.h"
#include "opcua_string_t.h"
#include "opcua_request_header_t.h"
#include "opcua_array_ua_t.h"

#include "opcua_app_description_t.h"
#include "opcua_timestamps_to_return_t.h"
#include "opcua_read_value_id_t.h"
#include "opcua_duration_t.h"

namespace uasdk
{

class ReadRequest_t : public RequestMessage_t
{
private:
  Duration_t                  maxAge;
  TimestampsToReturn_t        timestampsToReturn;
  ArrayUA_t<ReadValueId_t>    nodesToRead;

  ReadRequest_t& operator=(ReadRequest_t const &);
  ReadRequest_t(ReadRequest_t const &);

public:
  static const uint32_t TYPE_ID = OpcUaId_ReadRequest;

  ReadRequest_t(){}
  virtual ~ReadRequest_t(){}

  uint32_t TypeId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return TYPE_ID;
  }

  uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return OpcUaId_ReadRequest_Encoding_DefaultBinary;
  }

  const Duration_t& MaxAge(void) const { return maxAge; }
  Duration_t& MaxAge(void) { return maxAge; }

  const TimestampsToReturn_t& TimestampsToReturn(void) const { return timestampsToReturn; }
  TimestampsToReturn_t& TimestampsToReturn(void) { return timestampsToReturn; }

  const ArrayUA_t<ReadValueId_t>& NodesToRead(void) const { return nodesToRead; }
  ArrayUA_t<ReadValueId_t>& NodesToRead(void) { return nodesToRead; }

  virtual Status_t EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, ReadRequest_t& result);

};

} // namespace uasdk
#endif // _OPCUA_READ_REQUEST_T_
