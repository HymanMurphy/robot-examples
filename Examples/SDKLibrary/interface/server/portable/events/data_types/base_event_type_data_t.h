

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


#ifndef _BASEEVENTTYPEDATA_T_H_
#define _BASEEVENTTYPEDATA_T_H_
#include "uasdk_includes.h"


#if (UASDK_INCLUDE_EVENTS > 0)



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

class BaseEventTypeData_t : public IAttributeAccess_t
{
public:
	UA_DECLARE_RUNTIME_TYPE(BaseEventTypeData_t);
	
	static const uint32_t TYPE_ID = OpcUaId_BaseEventType;
	
	BaseEventTypeData_t();
	virtual ~BaseEventTypeData_t();
	
	virtual Status_t CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const;
	virtual Status_t CopyFrom(const BaseDataType_t& source);
	Status_t CopyFrom(const BaseEventTypeData_t& source);
	
	
	Status_t Initialise(void);
	
	
	
	//IAttributeAccess_t implementation
	
	virtual bool IsOfType(const uint32_t typeId, uint16_t namespaceIndex) const;
	
	virtual IntrusivePtr_t<const BaseDataType_t> AttributeValue(const uint32_t& typeId, const ArrayUA_t<QualifiedName_t>& browsePath, const uint32_t& _attributeId, const String_t& _indexRange, const ArrayUA_t<String_t> &locales, Status_t& result) const;
	
	virtual IntrusivePtr_t<BaseDataType_t> AttributeValue(const uint32_t& typeId, const ArrayUA_t<QualifiedName_t>& browsePath, const uint32_t& _attributeId, const String_t& _indexRange, const ArrayUA_t<String_t> &locales, Status_t& result);
	
	
	
	virtual uint32_t TypeId(uint16_t& namespaceIndex) const;
	
	
	
private:
	//Attributes
	
	
	    
	
	IntrusivePtr_t<NodeId_t> attrNodeId;
	
	IntrusivePtr_t<QualifiedName_t> attrBrowseName;
	
	IntrusivePtr_t<NodeClass_t> attrNodeClass;
	
	IntrusivePtr_t<ILocalizableText_t> attrDisplayName;
	
	IntrusivePtr_t<ILocalizableText_t> attrDescription;
	
	IntrusivePtr_t<NodeId_t> attrDataType;
	
	
	IntrusivePtr_t<String_t> browseName;
	
	IntrusivePtr_t<ByteString_t> eventId;
	
	IntrusivePtr_t<NodeId_t> eventType;
	
	IntrusivePtr_t<NodeId_t> sourceNode;
	
	IntrusivePtr_t<String_t> sourceName;
	
	IntrusivePtr_t<UtcTime_t> time;
	
	IntrusivePtr_t<UtcTime_t> receiveTime;
	
	IntrusivePtr_t<Int16_t> localTime_Offset;
	
	IntrusivePtr_t<Boolean_t> localTime_DaylightSavingInOffset;
	
	IntrusivePtr_t<TimeZoneDataType_t> localTime;
	
	IntrusivePtr_t<LocalizedText_t> message;
	
	IntrusivePtr_t<UInt16_t> severity;
	
	

public:
	//Accessors
	
	
	IntrusivePtr_t<const NodeId_t> AttributeNodeId(void) const {return attrNodeId;}
	
	IntrusivePtr_t<NodeId_t> &AttributeNodeId(void) {return attrNodeId;}
	
	
	
	IntrusivePtr_t<const QualifiedName_t> AttributeBrowseName(void) const {return attrBrowseName;}
	
	IntrusivePtr_t<QualifiedName_t> &AttributeBrowseName(void) {return attrBrowseName;}
	
	
	
	IntrusivePtr_t<const ILocalizableText_t> AttributeDisplayName(void) const {return attrDisplayName;}
	
	IntrusivePtr_t<ILocalizableText_t> &AttributeDisplayName(void) {return attrDisplayName;}
	
	
	
	IntrusivePtr_t<const ILocalizableText_t> AttributeDescription(void) const {return attrDescription;}
	
	IntrusivePtr_t<ILocalizableText_t> &AttributeDescription(void) {return attrDescription;}
	
	
	
	IntrusivePtr_t<const NodeId_t> AttributeDataType(void) const {return attrDataType;}
	
	IntrusivePtr_t<NodeId_t> &AttributeDataType(void) {return attrDataType;}
	
		
	
	
	IntrusivePtr_t<const ByteString_t> EventId(void) const {return eventId;}
	
	IntrusivePtr_t<ByteString_t> &EventId(void) {return eventId;}
	
	
	
	IntrusivePtr_t<const NodeId_t> EventType(void) const {return eventType;}
	
	IntrusivePtr_t<NodeId_t> &EventType(void) {return eventType;}
	
	
	
	IntrusivePtr_t<const NodeId_t> SourceNode(void) const {return sourceNode;}
	
	IntrusivePtr_t<NodeId_t> &SourceNode(void) {return sourceNode;}
	
	
	
	IntrusivePtr_t<const String_t> SourceName(void) const {return sourceName;}
	
	IntrusivePtr_t<String_t> &SourceName(void) {return sourceName;}
	
	
	
	IntrusivePtr_t<const UtcTime_t> Time(void) const {return time;}
	
	IntrusivePtr_t<UtcTime_t> &Time(void) {return time;}
	
	
	
	IntrusivePtr_t<const UtcTime_t> ReceiveTime(void) const {return receiveTime;}
	
	IntrusivePtr_t<UtcTime_t> &ReceiveTime(void) {return receiveTime;}
	
	
	
	IntrusivePtr_t<const Int16_t> LocalTime_Offset(void) const {return localTime_Offset;}
	
	IntrusivePtr_t<Int16_t> &LocalTime_Offset(void) {return localTime_Offset;}
	
	
	
	IntrusivePtr_t<const Boolean_t> LocalTime_DaylightSavingInOffset(void) const {return localTime_DaylightSavingInOffset;}
	
	IntrusivePtr_t<Boolean_t> &LocalTime_DaylightSavingInOffset(void) {return localTime_DaylightSavingInOffset;}
	
	
	
	IntrusivePtr_t<const TimeZoneDataType_t> LocalTime(void) const {return localTime;}
	
	IntrusivePtr_t<TimeZoneDataType_t> &LocalTime(void) {return localTime;}
	
	
	
	IntrusivePtr_t<const LocalizedText_t> Message(void) const {return message;}
	
	IntrusivePtr_t<LocalizedText_t> &Message(void) {return message;}
	
	
	
	IntrusivePtr_t<const UInt16_t> Severity(void) const {return severity;}
	
	IntrusivePtr_t<UInt16_t> &Severity(void) {return severity;}
	
	
	
	
	
	}; //class
} // namespace

#endif //(UASDK_INCLUDE_EVENTS > 0)

#endif /* _BASEEVENTTYPEDATA_T_H_ */
