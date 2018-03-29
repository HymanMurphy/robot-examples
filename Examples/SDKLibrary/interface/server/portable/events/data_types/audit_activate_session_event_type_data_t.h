

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


#ifndef _AUDITACTIVATESESSIONEVENTTYPEDATA_T_H_
#define _AUDITACTIVATESESSIONEVENTTYPEDATA_T_H_
#include "uasdk_includes.h"


#if (UASDK_INCLUDE_EVENTS > 0)

#include "audit_session_event_type_data_t.h"


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

class AuditActivateSessionEventTypeData_t : public AuditSessionEventTypeData_t
{
public:
	UA_DECLARE_RUNTIME_TYPE(AuditActivateSessionEventTypeData_t);
	
	static const uint32_t TYPE_ID = OpcUaId_AuditActivateSessionEventType;
	
	AuditActivateSessionEventTypeData_t();
	virtual ~AuditActivateSessionEventTypeData_t();
	
	virtual Status_t CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const;
	virtual Status_t CopyFrom(const BaseDataType_t& source);
	Status_t CopyFrom(const AuditActivateSessionEventTypeData_t& source);
	
	
	Status_t Initialise(void);
	
	
	
	//IAttributeAccess_t implementation
	
	virtual bool IsOfType(const uint32_t typeId, uint16_t namespaceIndex) const;
	
	virtual IntrusivePtr_t<const BaseDataType_t> AttributeValue(const uint32_t& typeId, const ArrayUA_t<QualifiedName_t>& browsePath, const uint32_t& _attributeId, const String_t& _indexRange, const ArrayUA_t<String_t> &locales, Status_t& result) const;
	
	virtual IntrusivePtr_t<BaseDataType_t> AttributeValue(const uint32_t& typeId, const ArrayUA_t<QualifiedName_t>& browsePath, const uint32_t& _attributeId, const String_t& _indexRange, const ArrayUA_t<String_t> &locales, Status_t& result);
	
	
	
	virtual uint32_t TypeId(uint16_t& namespaceIndex) const;
	
	
	
private:
	//Attributes
	IntrusivePtr_t<String_t> browseName;
	
	IntrusivePtr_t<ByteString_t> clientSoftwareCertificates_CertificateData;
	
	IntrusivePtr_t<ByteString_t> clientSoftwareCertificates_Signature;
	
	ArrayUA_t<SignedSoftwareCertificate_t> clientSoftwareCertificates;
	
	IntrusivePtr_t<String_t> userIdentityToken_PolicyId;
	
	IntrusivePtr_t<UserIdentityToken_t> userIdentityToken;
	
	IntrusivePtr_t<String_t> secureChannelId;
	
	

public:
	//Accessors
	IntrusivePtr_t<const ByteString_t> ClientSoftwareCertificates_CertificateData(void) const {return clientSoftwareCertificates_CertificateData;}
	
	IntrusivePtr_t<ByteString_t> &ClientSoftwareCertificates_CertificateData(void) {return clientSoftwareCertificates_CertificateData;}
	
	
	
	IntrusivePtr_t<const ByteString_t> ClientSoftwareCertificates_Signature(void) const {return clientSoftwareCertificates_Signature;}
	
	IntrusivePtr_t<ByteString_t> &ClientSoftwareCertificates_Signature(void) {return clientSoftwareCertificates_Signature;}
	
	
	
	ArrayUA_t<SignedSoftwareCertificate_t> &ClientSoftwareCertificates(void) {return clientSoftwareCertificates;}
	
	
	
	IntrusivePtr_t<const String_t> UserIdentityToken_PolicyId(void) const {return userIdentityToken_PolicyId;}
	
	IntrusivePtr_t<String_t> &UserIdentityToken_PolicyId(void) {return userIdentityToken_PolicyId;}
	
	
	
	IntrusivePtr_t<const UserIdentityToken_t> UserIdentityToken(void) const {return userIdentityToken;}
	
	IntrusivePtr_t<UserIdentityToken_t> &UserIdentityToken(void) {return userIdentityToken;}
	
	
	
	IntrusivePtr_t<const String_t> SecureChannelId(void) const {return secureChannelId;}
	
	IntrusivePtr_t<String_t> &SecureChannelId(void) {return secureChannelId;}
	
	
	
	
	
	}; //class
} // namespace

#endif //(UASDK_INCLUDE_EVENTS > 0)

#endif /* _AUDITACTIVATESESSIONEVENTTYPEDATA_T_H_ */
