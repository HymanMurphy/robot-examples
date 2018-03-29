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

#include "opcua_request_message_t.h"
#include "opcua_open_secure_channel_request_t.h"
#include "opcua_get_endpoints_request_t.h"
#include "opcua_service_fault_t.h"
#include "opcua_create_session_request_t.h"
#include "opcua_activate_session_request_t.h"
#include "opcua_close_session_request_t.h"
#include "opcua_cancel_request_t.h"
#include "opcua_browse_request_t.h"
#include "opcua_browse_next_request_t.h"
#include "opcua_translate_browse_paths_request_t.h"
#include "opcua_register_nodes_request_t.h"
#include "opcua_unregister_nodes_request_t.h"
#include "opcua_read_request_t.h"
#include "opcua_write_request_t.h"
#include "opcua_create_subscription_request_t.h"
#include "opcua_modify_subscription_request_t.h"
#include "opcua_transfer_subscriptions_request_t.h"
#include "opcua_delete_subscriptions_request_t.h"
#include "opcua_set_publishing_mode_request_t.h"
#include "opcua_publish_request_t.h"
#include "opcua_republish_request_t.h"
#include "opcua_create_monitored_items_request_t.h"
#include "opcua_modify_monitored_items_request_t.h"
#include "opcua_delete_monitored_items_request_t.h"
#include "opcua_set_monitoring_mode_request_t.h"
#include "opcua_find_servers_request_t.h"
#include "opcua_identifiers.h"
#include "opcua_set_triggering_request_t.h"
#include "opcua_call_request_t.h"
#include "opcua_expanded_node_id_t.h"

namespace uasdk
{

Status_t RequestMessage_t::EncodeHeader(ICodec_t& encoder, IBuffer_t& buffer) const
{
  return header.Encode(encoder, buffer);
}

Status_t RequestMessage_t::DecodeHeader(const IBuffer_t& buffer, ICodec_t& decoder)
{
  return RequestHeader_t::Decode(buffer, decoder, header);
}

} // namespace uasdk
