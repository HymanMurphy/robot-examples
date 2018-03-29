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

#ifndef _OPCUA_REGISTER_NODES_REQUEST_T_
#define _OPCUA_REGISTER_NODES_REQUEST_T_


#include "opcua_request_message_t.h"
#include "opcua_string_t.h"
#include "opcua_request_header_t.h"
#include "opcua_array_ua_t.h"

#include "opcua_app_description_t.h"

namespace uasdk
{

class RegisterNodesRequest_t : public RequestMessage_t
{
private:
  ArrayUA_t<NodeId_t> nodesToRegister;

  RegisterNodesRequest_t& operator=(RegisterNodesRequest_t const &);
  RegisterNodesRequest_t(RegisterNodesRequest_t const &);

public:
  static const uint32_t TYPE_ID = OpcUaId_RegisterNodesRequest;

  RegisterNodesRequest_t(){}
  virtual ~RegisterNodesRequest_t(){}

  uint32_t TypeId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return TYPE_ID;
  }

  uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return OpcUaId_RegisterNodesRequest_Encoding_DefaultBinary;
  }

  const ArrayUA_t<NodeId_t>& NodesToRegister(void) const { return nodesToRegister; }
  ArrayUA_t<NodeId_t>& NodesToRegister(void) { return nodesToRegister; }

  virtual Status_t EncodeBody(ICodec_t& encoder, IBuffer_t& buffer) const;
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, RegisterNodesRequest_t& result);

};

} // namespace uasdk
#endif // _OPCUA_REGISTER_NODES_REQUEST_T_
