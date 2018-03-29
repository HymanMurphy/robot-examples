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

#include "opcua_datatype_utilities_t.h"

#include "opcua_anonymous_identity_token_t.h"
#include "opcua_application_type_t.h"
#include "opcua_app_description_t.h"
#include "opcua_argument_t.h"
#include "opcua_array_ua_t.h"
#include "opcua_axis_information_t.h"
#include "opcua_axis_scale_enumeration_t.h"
#include "opcua_base_data_type_t.h"
#include "opcua_boolean_t.h"
#include "opcua_browse_continuation_point_t.h"
#include "opcua_browse_description_t.h"
#include "opcua_browse_path_result_t.h"
#include "opcua_browse_path_t.h"
#include "opcua_browse_path_target_t.h"
#include "opcua_browse_result_t.h"
#include "opcua_build_info_t.h"
#include "opcua_bytestring_t.h"
#include "opcua_byte_t.h"
#include "opcua_call_method_request_t.h"
#include "opcua_call_method_result_t.h"
#include "opcua_channel_security_token_t.h"
#include "opcua_complex_number_type_t.h"
#include "opcua_data_change_notification_t.h"
#include "opcua_data_change_filter_t.h"
#include "opcua_data_value_t.h"
#include "opcua_data_change_notification_t.h"
#include "opcua_date_time_t.h"
#include "opcua_diagnostic_info_t.h"
#include "opcua_double_t.h"
#include "opcua_double_complex_number_type_t.h"
#include "opcua_duration_t.h"
#include "opcua_endpoint_description_t.h"
#include "opcua_enum_value_type_t.h"
#include "opcua_eu_information_t.h"
#include "opcua_expanded_node_id_t.h"
#include "opcua_extensible_parameter_t.h"
#include "opcua_float_t.h"
#include "opcua_guid_t.h"
#include "opcua_int16_t.h"
#include "opcua_int32_t.h"
#include "opcua_int64_t.h"
#include "opcua_localized_text_t.h"
#include "opcua_mon_item_create_request_t.h"
#include "opcua_mon_item_create_result_t.h"
#include "opcua_mon_item_modify_request_t.h"
#include "opcua_mon_item_modify_result_t.h"
#include "opcua_node_id_guid_t.h"
#include "opcua_node_id_numeric_t.h"
#include "opcua_node_id_opaque_t.h"
#include "opcua_node_id_string_t.h"
#include "opcua_node_id_t.h"
#include "opcua_notification_message_t.h"
#include "opcua_qualified_name_t.h"
#include "opcua_range_t.h"
#include "opcua_read_value_id_t.h"
#include "opcua_redundancy_support_t.h"
#include "opcua_reference_description_t.h"
#include "opcua_relative_path_element_t.h"
#include "opcua_sbyte_t.h"
#include "opcua_server_status_t.h"
#include "opcua_signature_data_t.h"
#include "opcua_status_change_notification_t.h"
#include "opcua_subscription_acknowledgement_t.h"
#include "opcua_timestamps_to_return_t.h"
#include "opcua_transfer_result_t.h"
#include "opcua_uint16_t.h"
#include "opcua_uint32_t.h"
#include "opcua_uint64_t.h"
#include "opcua_username_identity_token_t.h"
#include "opcua_user_token_policy_t.h"
#include "opcua_string_t.h"
#include "opcua_view_description_t.h"
#include "opcua_write_value_t.h"
#include "opcua_x509_identity_token_t.h"
#include "opcua_xml_element_t.h"
#include "opcua_xv_type_t.h"
#include "opcua_mon_item_notification_t.h"
#include "opcua_security_token_request_type_t.h"

namespace uasdk
{

bool DataTypeUtilities_t::IsANumber(const NodeId_t& typeId)
{
  const NodeIdNumeric_t* numericId = RuntimeCast<const NodeIdNumeric_t *>(typeId);
  if (!numericId)
  {
    return false;
  }
  if (!numericId->NamespaceIndex().Value() == 0)
  {
    return false;
  }

  uint32_t typeIdentifier = numericId->Identifer().Value();

  return (
    (typeIdentifier == OpcUaId_Integer)
    || (typeIdentifier == OpcUaId_SByte)
    || (typeIdentifier == OpcUaId_Int16)
    || (typeIdentifier == OpcUaId_Int32)
    || (typeIdentifier == OpcUaId_Int64)
    || (typeIdentifier == OpcUaId_Byte)
    || (typeIdentifier == OpcUaId_UInt16)
    || (typeIdentifier == OpcUaId_UInt32)
    || (typeIdentifier == OpcUaId_UInt64)
    || (typeIdentifier == OpcUaId_Double)
    || (typeIdentifier == OpcUaId_Float)
    );
}

}
