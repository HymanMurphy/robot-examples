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

#ifndef _OPCUA_REGISTER_SERVER_RESPONSE_T_
#define _OPCUA_REGISTER_SERVER_RESPONSE_T_


#include "opcua_response_message_t.h"
#include "opcua_response_header_t.h"

#if (UASDK_INCLUDE_ADDITIONAL_DISCOVERY_SERVICES > 0)

namespace uasdk
{

class RegisterServerResponse_t : public ResponseMessage_t
{
private:

  RegisterServerResponse_t& operator=(RegisterServerResponse_t const &);
  RegisterServerResponse_t(RegisterServerResponse_t const &);

public:
  static const uint32_t TYPE_ID = OpcUaId_RegisterServerResponse;

  RegisterServerResponse_t() {};
  virtual ~RegisterServerResponse_t(){}

  uint32_t TypeId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return TYPE_ID;
  }

  uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return OpcUaId_RegisterServerResponse_Encoding_DefaultBinary;
  }

  virtual Status_t EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, RegisterServerResponse_t& result);
};

} // namespace uasdk

#endif

#endif // _OPCUA_REGISTER_SERVER_RESPONSE_T_
