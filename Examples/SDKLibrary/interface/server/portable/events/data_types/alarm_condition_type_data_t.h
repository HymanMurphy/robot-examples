

/* ------------------------------------------------------------------------------------------------------------------

																				COPYRIGHT (c) 2009 - 2017

																				HONEYWELL INC.,

																				ALL RIGHTS RESERVED



						This software is a copyrighted work and/or information protected as a trade

						secret. Legal rights of Honeywell Inc. in this software are distinct from

						ownership of any medium in which the software is embodied. Copyright or trade

						secret notices included must be reproduced in any copies authorized by

						Honeywell Inc. The information in this software is subject to change without

						notice and should not be considered as a commitment by Honeywell Inc.

--------------------------------------------------------------------------------------------------------------------- */


#ifndef _ALARMCONDITIONTYPEDATA_T_H_
#define _ALARMCONDITIONTYPEDATA_T_H_
#include "uasdk_includes.h"


#if ((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

#include "acknowledgeable_condition_type_data_t.h"


#include "iattribute_access_t.h"

#include "opcua_identifiers.h"

#include "opcua_node_id_t.h"

#include "opcua_uint16_t.h"

#include "opcua_double_t.h"

#include "opcua_date_time_t.h"

#include "opcua_time_zone_data_type_t.h"

#include "opcua_localized_text_t.h"

#include "opcua_bytestring_t.h"

#include "opcua_array_ua_t.h"

#include "opcua_string_t.h"

#include "opcua_byte_t.h"

#include "opcua_base_data_type_t.h"

#include "opcua_server_state_t.h"

#include "attribute_id_mask_t.h"

#include "intrusive_list_t.h"

#include "opcua_status_code_t.h"

#include "opcua_expanded_node_id_t.h"

#include "opcua_node_class_t.h"

#include "opcua_add_nodes_item_t.h" 

#include "opcua_user_identity_token_type_t.h"

#include "opcua_security_token_request_type_t.h"

#include "opcua_message_security_mode_t.h"

#include "opcua_delete_nodes_item_t.h"

#include "opcua_add_references_item_t.h"

#include "opcua_delete_references_item_t.h"

#include "opcua_duration_t.h"

#include "opcua_signed_software_certificate.h"

#include "opcua_model_change_structure_data_type_t.h"

#include "opcua_semantic_change_structure_data_type_t.h"

#include "utilities.h"

#include "opcua_node_id_numeric_t.h"

#include "opcua_node_id_string_t.h"

#include "opcua_node_id_guid_t.h"

#include "opcua_node_id_opaque_t.h"

#include "opcua_server_state_t.h"

#include "two_state_variable_type_t.h"

#include "condition_variable_type_t.h"

#include "ilocalizable_text_t.h"

				

#define UserIdentityToken_t ExtensibleParameter_t

#define NumericRange_t String_t


namespace uasdk
{ 

class AlarmConditionTypeData_t : public AcknowledgeableConditionTypeData_t
{
public:
	UA_DECLARE_RUNTIME_TYPE(AlarmConditionTypeData_t);
	
	static const uint32_t TYPE_ID = OpcUaId_AlarmConditionType;
	
	AlarmConditionTypeData_t();
	virtual ~AlarmConditionTypeData_t();
	
	virtual Status_t CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const;
	virtual Status_t CopyFrom(const BaseDataType_t& source);
	Status_t CopyFrom(const AlarmConditionTypeData_t& source);
	
	
	Status_t Initialise(void);
	
	
	
	//IAttributeAccess_t implementation
	
	virtual bool IsOfType(const uint32_t typeId, uint16_t namespaceIndex) const;
	
	virtual IntrusivePtr_t<const BaseDataType_t> AttributeValue(const uint32_t& typeId, const ArrayUA_t<QualifiedName_t>& browsePath, const uint32_t& _attributeId, const String_t& _indexRange, const ArrayUA_t<String_t> &locales, Status_t& result) const;
	
	virtual IntrusivePtr_t<BaseDataType_t> AttributeValue(const uint32_t& typeId, const ArrayUA_t<QualifiedName_t>& browsePath, const uint32_t& _attributeId, const String_t& _indexRange, const ArrayUA_t<String_t> &locales, Status_t& result);
	
	
	
	virtual uint32_t TypeId(uint16_t& namespaceIndex) const;
	
	
	
private:
	//Attributes
	IntrusivePtr_t<String_t> browseName;
	
	IntrusivePtr_t<NodeId_t> inputNode;
	
	IntrusivePtr_t<Boolean_t> suppressedOrShelved;
	
	IntrusivePtr_t<Duration_t> maxTimeShelved;
	
	IntrusivePtr_t<TwoStateVariableType_t> activeState;
	
	IntrusivePtr_t<TwoStateVariableType_t> suppressedState;
	
	IntrusivePtr_t<Duration_t> ShelvingState_unshelveTime;
	
	

public:
	//Accessors
	IntrusivePtr_t<const NodeId_t> InputNode(void) const {return inputNode;}
	
	IntrusivePtr_t<NodeId_t> &InputNode(void) {return inputNode;}
	
	
	
	IntrusivePtr_t<const Boolean_t> SuppressedOrShelved(void) const {return suppressedOrShelved;}
	
	IntrusivePtr_t<Boolean_t> &SuppressedOrShelved(void) {return suppressedOrShelved;}
	
	
	
	IntrusivePtr_t<const Duration_t> MaxTimeShelved(void) const {return maxTimeShelved;}
	
	IntrusivePtr_t<Duration_t> &MaxTimeShelved(void) {return maxTimeShelved;}
	
	
	
	IntrusivePtr_t<const TwoStateVariableType_t> ActiveState(void) const { return activeState;}
	
	IntrusivePtr_t<TwoStateVariableType_t> &ActiveState(void) { return activeState;}
	
	IntrusivePtr_t<const TwoStateVariableType_t> SuppressedState(void) const { return suppressedState;}
	
	IntrusivePtr_t<TwoStateVariableType_t> &SuppressedState(void) { return suppressedState;}
	
	IntrusivePtr_t<const Duration_t> ShelvingState_UnshelveTime(void) const {return ShelvingState_unshelveTime;}
	
	IntrusivePtr_t<Duration_t> &ShelvingState_UnshelveTime(void) {return ShelvingState_unshelveTime;}
	
	
	
	
	
	}; //class
} // namespace

#endif //((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

#endif /* _ALARMCONDITIONTYPEDATA_T_H_ */
