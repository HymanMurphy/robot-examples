

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


#ifndef _AUDITOPENSECURECHANNELEVENTTYPEDATA_T_H_
#define _AUDITOPENSECURECHANNELEVENTTYPEDATA_T_H_
#include "uasdk_includes.h"


#if (UASDK_INCLUDE_EVENTS > 0)

#include "audit_channel_event_type_data_t.h"


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

class AuditOpenSecureChannelEventTypeData_t : public AuditChannelEventTypeData_t
{
public:
	UA_DECLARE_RUNTIME_TYPE(AuditOpenSecureChannelEventTypeData_t);
	
	static const uint32_t TYPE_ID = OpcUaId_AuditOpenSecureChannelEventType;
	
	AuditOpenSecureChannelEventTypeData_t();
	virtual ~AuditOpenSecureChannelEventTypeData_t();
	
	virtual Status_t CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const;
	virtual Status_t CopyFrom(const BaseDataType_t& source);
	Status_t CopyFrom(const AuditOpenSecureChannelEventTypeData_t& source);
	
	
	Status_t Initialise(void);
	
	
	
	//IAttributeAccess_t implementation
	
	virtual bool IsOfType(const uint32_t typeId, uint16_t namespaceIndex) const;
	
	virtual IntrusivePtr_t<const BaseDataType_t> AttributeValue(const uint32_t& typeId, const ArrayUA_t<QualifiedName_t>& browsePath, const uint32_t& _attributeId, const String_t& _indexRange, const ArrayUA_t<String_t> &locales, Status_t& result) const;
	
	virtual IntrusivePtr_t<BaseDataType_t> AttributeValue(const uint32_t& typeId, const ArrayUA_t<QualifiedName_t>& browsePath, const uint32_t& _attributeId, const String_t& _indexRange, const ArrayUA_t<String_t> &locales, Status_t& result);
	
	
	
	virtual uint32_t TypeId(uint16_t& namespaceIndex) const;
	
	
	
private:
	//Attributes
	IntrusivePtr_t<String_t> browseName;
	
	IntrusivePtr_t<ByteString_t> clientCertificate;
	
	IntrusivePtr_t<String_t> clientCertificateThumbprint;
	
	IntrusivePtr_t<Int32_t> requestType_securityTokenRequestType;
	
	IntrusivePtr_t<SecurityTokenRequestType_t> requestType;
	
	IntrusivePtr_t<String_t> securityPolicyUri;
	
	IntrusivePtr_t<Int32_t> securityMode_messageSecurityMode;
	
	IntrusivePtr_t<MessageSecurityMode_t> securityMode;
	
	IntrusivePtr_t<Duration_t> requestedLifetime;
	
	

public:
	//Accessors
	IntrusivePtr_t<const ByteString_t> ClientCertificate(void) const {return clientCertificate;}
	
	IntrusivePtr_t<ByteString_t> &ClientCertificate(void) {return clientCertificate;}
	
	
	
	IntrusivePtr_t<const String_t> ClientCertificateThumbprint(void) const {return clientCertificateThumbprint;}
	
	IntrusivePtr_t<String_t> &ClientCertificateThumbprint(void) {return clientCertificateThumbprint;}
	
	
	
	IntrusivePtr_t<const Int32_t> RequestType_SecurityTokenRequestType(void) const {return requestType_securityTokenRequestType;}
	
	IntrusivePtr_t<Int32_t> &RequestType_SecurityTokenRequestType(void) {return requestType_securityTokenRequestType;}
	
	
	
	IntrusivePtr_t<const SecurityTokenRequestType_t> RequestType(void) const {return requestType;}
	
	IntrusivePtr_t<SecurityTokenRequestType_t> &RequestType(void) {return requestType;}
	
	
	
	IntrusivePtr_t<const String_t> SecurityPolicyUri(void) const {return securityPolicyUri;}
	
	IntrusivePtr_t<String_t> &SecurityPolicyUri(void) {return securityPolicyUri;}
	
	
	
	IntrusivePtr_t<const Int32_t> SecurityMode_MessageSecurityMode(void) const {return securityMode_messageSecurityMode;}
	
	IntrusivePtr_t<Int32_t> &SecurityMode_MessageSecurityMode(void) {return securityMode_messageSecurityMode;}
	
	
	
	IntrusivePtr_t<const MessageSecurityMode_t> SecurityMode(void) const {return securityMode;}
	
	IntrusivePtr_t<MessageSecurityMode_t> &SecurityMode(void) {return securityMode;}
	
	
	
	IntrusivePtr_t<const Duration_t> RequestedLifetime(void) const {return requestedLifetime;}
	
	IntrusivePtr_t<Duration_t> &RequestedLifetime(void) {return requestedLifetime;}
	
	
	
	
	
	}; //class
} // namespace

#endif //(UASDK_INCLUDE_EVENTS > 0)

#endif /* _AUDITOPENSECURECHANNELEVENTTYPEDATA_T_H_ */
