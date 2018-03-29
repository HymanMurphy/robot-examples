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

#ifndef _OPCUA_REQUEST_MESSAGE_T_
#define _OPCUA_REQUEST_MESSAGE_T_


#include "opcua_identifiers.h"
#include "opcua_request_header_t.h"
#include "opcua_message_ua_t.h"

namespace uasdk
{

class RequestMessage_t : public MessageUA_t
{
private:
  RequestHeader_t header;

  RequestMessage_t& operator=(RequestMessage_t const &);
  RequestMessage_t(RequestMessage_t const &);

protected:
  Status_t DecodeHeader(const IBuffer_t& buffer, ICodec_t& decoder);

public:
  RequestMessage_t() {}
  virtual ~RequestMessage_t(){}

  const RequestHeader_t& Header(void) const { return header; }
  RequestHeader_t& Header(void) { return header; }

  Status_t EncodeHeader(ICodec_t& encoder, IBuffer_t& buffer) const;

  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, IntrusivePtr_t<RequestMessage_t>& result)
  {
    return decoder.Decode(buffer, result);
  }

};

} // namespace uasdk
#endif // _OPCUA_REQUEST_MESSAGE_T_
