

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



#include "audit_create_session_event_type_data_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "opcua_node_id_numeric_t.h"
#include "opcua_server_state_t.h"
namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(AuditCreateSessionEventTypeData_t, AuditSessionEventTypeData_t);

AuditCreateSessionEventTypeData_t::AuditCreateSessionEventTypeData_t()
{
}

AuditCreateSessionEventTypeData_t::~AuditCreateSessionEventTypeData_t()
{
}

bool AuditCreateSessionEventTypeData_t::IsOfType(const uint32_t typeId, uint16_t namespaceindex) const
{
	if(namespaceindex != 0) return false;
	return typeId == 2071 || AuditSessionEventTypeData_t::IsOfType(typeId, namespaceindex);
}

Status_t AuditCreateSessionEventTypeData_t::Initialise()
{
	Status_t rtnStatus = OpcUa_Good;
	browseName = new SafeRefCount_t<String_t>();
	UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(browseName);
	rtnStatus = browseName->CopyFrom("AuditCreateSessionEventType");
	UASDK_RETURN_STATUS_ONLY_IF_BAD(rtnStatus.Value());
	
	secureChannelId.reset();
	
	clientCertificate.reset();
	
	clientCertificateThumbprint.reset();
	
	revisedSessionTimeout.reset();
	
	
	return AuditSessionEventTypeData_t::Initialise();
}

uint32_t AuditCreateSessionEventTypeData_t::TypeId(uint16_t& namespaceIndex) const
{
	namespaceIndex = 0;
	return AuditCreateSessionEventTypeData_t::TYPE_ID;
}

IntrusivePtr_t<BaseDataType_t> AuditCreateSessionEventTypeData_t::AttributeValue(const uint32_t& typeId, const ArrayUA_t<QualifiedName_t>&browsePath, const uint32_t &_attributeId, const String_t& _indexRange, const ArrayUA_t<String_t> & locales,  Status_t &result)
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
	if(UASDK_strcmp(nameStr, "SecureChannelId") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
		result = OpcUa_Good;
	
		return secureChannelId;
	
	};
	
	
	
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
	
	
	
	if(UASDK_strcmp(nameStr, "RevisedSessionTimeout") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
		result = OpcUa_Good;
	
		return revisedSessionTimeout;
	
	};
	
	
	
	
	/* end class specific attributes */
	
		return AuditSessionEventTypeData_t::AttributeValue(typeId, browsePath, _attributeId, _indexRange, locales, result); 
	}
	
	IntrusivePtr_t<const BaseDataType_t> AuditCreateSessionEventTypeData_t::AttributeValue(const uint32_t& typeId, const ArrayUA_t<QualifiedName_t>&browsePath, const uint32_t &_attributeId, const String_t& _indexRange, const ArrayUA_t<String_t> & locales, Status_t &result) const
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
		if(UASDK_strcmp(nameStr, "SecureChannelId") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
			result = OpcUa_Good;
		
			return secureChannelId;
		
		};
		
		
		
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
		
		
		
		if(UASDK_strcmp(nameStr, "RevisedSessionTimeout") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
			result = OpcUa_Good;
		
			return revisedSessionTimeout;
		
		};
		
		
		
		
		/* end class specific attributes */
		
		return AuditSessionEventTypeData_t::AttributeValue(typeId, browsePath, _attributeId, _indexRange, locales, result); 
	}
	
	Status_t AuditCreateSessionEventTypeData_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
	{
		return CopyToDestination(*this, destination);
	}
	
	Status_t AuditCreateSessionEventTypeData_t::CopyFrom(const BaseDataType_t& source)
	{
		IntrusivePtr_t<const AuditCreateSessionEventTypeData_t> ptr = RuntimeCast<const AuditCreateSessionEventTypeData_t*>(source);
		if (!ptr.is_set())
		{
			return OpcUa_BadTypeMismatch;
		}
		
		return CopyFrom(*ptr);
	}
	
	Status_t AuditCreateSessionEventTypeData_t::CopyFrom(const AuditCreateSessionEventTypeData_t& source)
	{
		Status_t result = OpcUa_Good;
		secureChannelId.reset();
		
		if(source.secureChannelId.is_set())
		
		{
		
		  secureChannelId = new SafeRefCount_t<String_t>();
		
		  if(!secureChannelId.is_set())
		
		  {
		
		    return OpcUa_BadOutOfMemory;
		
		  }
		
		
		
		  result = secureChannelId->CopyFrom(*source.SecureChannelId());
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
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
		
		
		
		revisedSessionTimeout.reset();
		
		if(source.revisedSessionTimeout.is_set())
		
		{
		
		  revisedSessionTimeout = new SafeRefCount_t<Duration_t>();
		
		  if(!revisedSessionTimeout.is_set())
		
		  {
		
		    return OpcUa_BadOutOfMemory;
		
		  }
		
		
		
		  result = revisedSessionTimeout->CopyFrom(*source.RevisedSessionTimeout());
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		
		result = AuditSessionEventTypeData_t::CopyFrom(source);
		return result;
	}
	
} // namespace

#endif //(UASDK_INCLUDE_EVENTS > 0)

