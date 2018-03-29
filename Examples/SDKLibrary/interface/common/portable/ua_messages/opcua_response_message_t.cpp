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

#include "opcua_response_message_t.h"
#include "opcua_expanded_node_id_t.h"

namespace uasdk
{

Status_t ResponseMessage_t::EncodeHeader(ICodec_t& encoder, IBuffer_t& buffer) const
{
  return header.Encode(encoder, buffer);
}

Status_t ResponseMessage_t::DecodeHeader(const IBuffer_t& buffer, ICodec_t& decoder)
{
  return ResponseHeader_t::Decode(buffer, decoder, header);
}

} // namespace uasdk
