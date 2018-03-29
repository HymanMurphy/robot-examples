

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



#include "audit_open_secure_channel_event_type_data_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "opcua_node_id_numeric_t.h"
#include "opcua_server_state_t.h"
namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(AuditOpenSecureChannelEventTypeData_t, AuditChannelEventTypeData_t);

AuditOpenSecureChannelEventTypeData_t::AuditOpenSecureChannelEventTypeData_t()
{
}

AuditOpenSecureChannelEventTypeData_t::~AuditOpenSecureChannelEventTypeData_t()
{
}

bool AuditOpenSecureChannelEventTypeData_t::IsOfType(const uint32_t typeId, uint16_t namespaceindex) const
{
	if(namespaceindex != 0) return false;
	return typeId == 2060 || AuditChannelEventTypeData_t::IsOfType(typeId, namespaceindex);
}

Status_t AuditOpenSecureChannelEventTypeData_t::Initialise()
{
	Status_t rtnStatus = OpcUa_Good;
	browseName = new SafeRefCount_t<String_t>();
	UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(browseName);
	rtnStatus = browseName->CopyFrom("AuditOpenSecureChannelEventType");
	UASDK_RETURN_STATUS_ONLY_IF_BAD(rtnStatus.Value());
	
	clientCertificate.reset();
	
	clientCertificateThumbprint.reset();
	
	requestType_securityTokenRequestType.reset();
	
	requestType.reset();
	
	securityPolicyUri.reset();
	
	securityMode_messageSecurityMode.reset();
	
	securityMode.reset();
	
	requestedLifetime.reset();
	
	
	return AuditChannelEventTypeData_t::Initialise();
}

uint32_t AuditOpenSecureChannelEventTypeData_t::TypeId(uint16_t& namespaceIndex) const
{
	namespaceIndex = 0;
	return AuditOpenSecureChannelEventTypeData_t::TYPE_ID;
}

IntrusivePtr_t<BaseDataType_t> AuditOpenSecureChannelEventTypeData_t::AttributeValue(const uint32_t& typeId, const ArrayUA_t<QualifiedName_t>&browsePath, const uint32_t &_attributeId, const String_t& _indexRange, const ArrayUA_t<String_t> & locales,  Status_t &result)
{
	
    UASDK_UNUSED(_indexRange);
	result = OpcUa_BadInvalidArgument;
	IntrusivePtr_t<BaseDataType_t> emptyResult;
	emptyResult.reset();
	
	uint16_t namespaceIndex = 0;
	if (!IsOfType(typeId, namespaceIndex))
	{
		return emptyResult;
	}
		
		char nameStr[1024] = { 0 };
    char *loc = &nameStr[0];
		uint32_t nameStrSize = static_cast<uint32_t>(sizeof(nameStr));
    for (uint32_t index = 0; index < browsePath.Count() && static_cast<uint32_t>(loc - nameStr) < (nameStrSize - 2); ++index)
    {
      UASDK_strncat(loc, nameStrSize - (loc - nameStr), (char*)(browsePath[index]->Name().Payload().Data()), browsePath[index]->Name().Payload().Length());
      loc += browsePath[index]->Name().Payload().Length();
      if (index < (browsePath.Count() - 1) && static_cast<uint32_t>(loc - nameStr) < (nameStrSize - 2))
      {
        *loc = '.';
        ++loc;
        *loc = '\0';
      }
	  	nameStrSize = static_cast<uint32_t>(sizeof(nameStr));
		}

	
	/* Start class specific attributes */
	if(UASDK_strcmp(nameStr, "ClientCertificate") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
		result = OpcUa_Good;
	
		return clientCertificate;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "ClientCertificateThumbprint") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
		result = OpcUa_Good;
	
		return clientCertificateThumbprint;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "RequestType.SecurityTokenRequestType") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 2
	
	{
	
		result = OpcUa_Good;
	
		return requestType_securityTokenRequestType;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "RequestType") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
		result = OpcUa_Good;
	
		return requestType;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "SecurityPolicyUri") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
		result = OpcUa_Good;
	
		return securityPolicyUri;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "SecurityMode.MessageSecurityMode") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 2
	
	{
	
		result = OpcUa_Good;
	
		return securityMode_messageSecurityMode;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "SecurityMode") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
		result = OpcUa_Good;
	
		return securityMode;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "RequestedLifetime") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
		result = OpcUa_Good;
	
		return requestedLifetime;
	
	};
	
	
	
	
	/* end class specific attributes */
	
		return AuditChannelEventTypeData_t::AttributeValue(typeId, browsePath, _attributeId, _indexRange, locales, result); 
	}
	
	IntrusivePtr_t<const BaseDataType_t> AuditOpenSecureChannelEventTypeData_t::AttributeValue(const uint32_t& typeId, const ArrayUA_t<QualifiedName_t>&browsePath, const uint32_t &_attributeId, const String_t& _indexRange, const ArrayUA_t<String_t> & locales, Status_t &result) const
	{
		
    UASDK_UNUSED(_indexRange);
		IntrusivePtr_t<BaseDataType_t> emptyResult;
		emptyResult.reset();
		result = OpcUa_BadInvalidArgument;
		
		uint16_t namespaceIndex = 0;
		if (!IsOfType(typeId, namespaceIndex))
		{
			return emptyResult;
		}
			
		char nameStr[1024] = { 0 };
    char *loc = &nameStr[0];
		uint32_t nameStrSize = static_cast<uint32_t>(sizeof(nameStr));
    for (uint32_t index = 0; index < browsePath.Count() && static_cast<uint32_t>(loc - nameStr) < (nameStrSize - 2); ++index)
    {
      UASDK_strncat(loc, nameStrSize - (loc - nameStr), (char*)(browsePath[index]->Name().Payload().Data()), browsePath[index]->Name().Payload().Length());
      loc += browsePath[index]->Name().Payload().Length();
      if (index < (browsePath.Count() - 1) && static_cast<uint32_t>(loc - nameStr) < (nameStrSize - 2))
      {
        *loc = '.';
        ++loc;
        *loc = '\0';
      }
	  	nameStrSize = static_cast<uint32_t>(sizeof(nameStr));
		}

		
		/* Start class specific attributes */
		if(UASDK_strcmp(nameStr, "ClientCertificate") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
			result = OpcUa_Good;
		
			return clientCertificate;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "ClientCertificateThumbprint") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
			result = OpcUa_Good;
		
			return clientCertificateThumbprint;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "RequestType.SecurityTokenRequestType") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 2
		
		{
		
			result = OpcUa_Good;
		
			return requestType_securityTokenRequestType;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "RequestType") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
			result = OpcUa_Good;
		
			return requestType;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "SecurityPolicyUri") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
			result = OpcUa_Good;
		
			return securityPolicyUri;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "SecurityMode.MessageSecurityMode") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 2
		
		{
		
			result = OpcUa_Good;
		
			return securityMode_messageSecurityMode;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "SecurityMode") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
			result = OpcUa_Good;
		
			return securityMode;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "RequestedLifetime") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
			result = OpcUa_Good;
		
			return requestedLifetime;
		
		};
		
		
		
		
		/* end class specific attributes */
		
		return AuditChannelEventTypeData_t::AttributeValue(typeId, browsePath, _attributeId, _indexRange, locales, result); 
	}
	
	Status_t AuditOpenSecureChannelEventTypeData_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
	{
		return CopyToDestination(*this, destination);
	}
	
	Status_t AuditOpenSecureChannelEventTypeData_t::CopyFrom(const BaseDataType_t& source)
	{
		IntrusivePtr_t<const AuditOpenSecureChannelEventTypeData_t> ptr = RuntimeCast<const AuditOpenSecureChannelEventTypeData_t*>(source);
		if (!ptr.is_set())
		{
			return OpcUa_BadTypeMismatch;
		}
		
		return CopyFrom(*ptr);
	}
	
	Status_t AuditOpenSecureChannelEventTypeData_t::CopyFrom(const AuditOpenSecureChannelEventTypeData_t& source)
	{
		Status_t result = OpcUa_Good;
		clientCertificate.reset();
		
		if(source.clientCertificate.is_set())
		
		{
		
		  clientCertificate = new SafeRefCount_t<ByteString_t>();
		
		  if(!clientCertificate.is_set())
		
		  {
		
		    return OpcUa_BadOutOfMemory;
		
		  }
		
		
		
		  result = clientCertificate->CopyFrom(*source.ClientCertificate());
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		clientCertificateThumbprint.reset();
		
		if(source.clientCertificateThumbprint.is_set())
		
		{
		
		  clientCertificateThumbprint = new SafeRefCount_t<String_t>();
		
		  if(!clientCertificateThumbprint.is_set())
		
		  {
		
		    return OpcUa_BadOutOfMemory;
		
		  }
		
		
		
		  result = clientCertificateThumbprint->CopyFrom(*source.ClientCertificateThumbprint());
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		requestType_securityTokenRequestType.reset();
		
		if(source.requestType_securityTokenRequestType.is_set())
		
		{
		
		  requestType_securityTokenRequestType = new SafeRefCount_t<Int32_t>();
		
		  if(!requestType_securityTokenRequestType.is_set())
		
		  {
		
		    return OpcUa_BadOutOfMemory;
		
		  }
		
		
		
		  result = requestType_securityTokenRequestType->CopyFrom(*source.RequestType_SecurityTokenRequestType());
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		requestType.reset();
		
		if(source.requestType.is_set())
		
		{
		
		  requestType = new SafeRefCount_t<SecurityTokenRequestType_t>();
		
		  if(!requestType.is_set())
		
		  {
		
		    return OpcUa_BadOutOfMemory;
		
		  }
		
		
		
		  result = requestType->CopyFrom(*source.RequestType());
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		securityPolicyUri.reset();
		
		if(source.securityPolicyUri.is_set())
		
		{
		
		  securityPolicyUri = new SafeRefCount_t<String_t>();
		
		  if(!securityPolicyUri.is_set())
		
		  {
		
		    return OpcUa_BadOutOfMemory;
		
		  }
		
		
		
		  result = securityPolicyUri->CopyFrom(*source.SecurityPolicyUri());
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		securityMode_messageSecurityMode.reset();
		
		if(source.securityMode_messageSecurityMode.is_set())
		
		{
		
		  securityMode_messageSecurityMode = new SafeRefCount_t<Int32_t>();
		
		  if(!securityMode_messageSecurityMode.is_set())
		
		  {
		
		    return OpcUa_BadOutOfMemory;
		
		  }
		
		
		
		  result = securityMode_messageSecurityMode->CopyFrom(*source.SecurityMode_MessageSecurityMode());
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		securityMode.reset();
		
		if(source.securityMode.is_set())
		
		{
		
		  securityMode = new SafeRefCount_t<MessageSecurityMode_t>();
		
		  if(!securityMode.is_set())
		
		  {
		
		    return OpcUa_BadOutOfMemory;
		
		  }
		
		
		
		  result = securityMode->CopyFrom(*source.SecurityMode());
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		requestedLifetime.reset();
		
		if(source.requestedLifetime.is_set())
		
		{
		
		  requestedLifetime = new SafeRefCount_t<Duration_t>();
		
		  if(!requestedLifetime.is_set())
		
		  {
		
		    return OpcUa_BadOutOfMemory;
		
		  }
		
		
		
		  result = requestedLifetime->CopyFrom(*source.RequestedLifetime());
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		
		result = AuditChannelEventTypeData_t::CopyFrom(source);
		return result;
	}
	
} // namespace

#endif //(UASDK_INCLUDE_EVENTS > 0)

