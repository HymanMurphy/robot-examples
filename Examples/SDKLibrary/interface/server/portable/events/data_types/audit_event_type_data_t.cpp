

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



#include "audit_event_type_data_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "opcua_node_id_numeric_t.h"
#include "opcua_server_state_t.h"
namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(AuditEventTypeData_t, BaseEventTypeData_t);

AuditEventTypeData_t::AuditEventTypeData_t()
{
}

AuditEventTypeData_t::~AuditEventTypeData_t()
{
}

bool AuditEventTypeData_t::IsOfType(const uint32_t typeId, uint16_t namespaceindex) const
{
	if(namespaceindex != 0) return false;
	return typeId == 2052 || BaseEventTypeData_t::IsOfType(typeId, namespaceindex);
}

Status_t AuditEventTypeData_t::Initialise()
{
	Status_t rtnStatus = OpcUa_Good;
	browseName = new SafeRefCount_t<String_t>();
	UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(browseName);
	rtnStatus = browseName->CopyFrom("AuditEventType");
	UASDK_RETURN_STATUS_ONLY_IF_BAD(rtnStatus.Value());
	
	actionTimeStamp.reset();
	
	status.reset();
	
	serverId.reset();
	
	clientAuditEntryId.reset();
	
	clientUserId.reset();
	
	
	return BaseEventTypeData_t::Initialise();
}

uint32_t AuditEventTypeData_t::TypeId(uint16_t& namespaceIndex) const
{
	namespaceIndex = 0;
	return AuditEventTypeData_t::TYPE_ID;
}

IntrusivePtr_t<BaseDataType_t> AuditEventTypeData_t::AttributeValue(const uint32_t& typeId, const ArrayUA_t<QualifiedName_t>&browsePath, const uint32_t &_attributeId, const String_t& _indexRange, const ArrayUA_t<String_t> & locales,  Status_t &result)
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
	if(UASDK_strcmp(nameStr, "ActionTimeStamp") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
		result = OpcUa_Good;
	
		return actionTimeStamp;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "Status") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
		result = OpcUa_Good;
	
		return status;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "ServerId") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
		result = OpcUa_Good;
	
		return serverId;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "ClientAuditEntryId") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
		result = OpcUa_Good;
	
		return clientAuditEntryId;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "ClientUserId") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
		result = OpcUa_Good;
	
		return clientUserId;
	
	};
	
	
	
	
	/* end class specific attributes */
	
		return BaseEventTypeData_t::AttributeValue(typeId, browsePath, _attributeId, _indexRange, locales, result); 
	}
	
	IntrusivePtr_t<const BaseDataType_t> AuditEventTypeData_t::AttributeValue(const uint32_t& typeId, const ArrayUA_t<QualifiedName_t>&browsePath, const uint32_t &_attributeId, const String_t& _indexRange, const ArrayUA_t<String_t> & locales, Status_t &result) const
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
		if(UASDK_strcmp(nameStr, "ActionTimeStamp") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
			result = OpcUa_Good;
		
			return actionTimeStamp;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "Status") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
			result = OpcUa_Good;
		
			return status;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "ServerId") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
			result = OpcUa_Good;
		
			return serverId;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "ClientAuditEntryId") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
			result = OpcUa_Good;
		
			return clientAuditEntryId;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "ClientUserId") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
			result = OpcUa_Good;
		
			return clientUserId;
		
		};
		
		
		
		
		/* end class specific attributes */
		
		return BaseEventTypeData_t::AttributeValue(typeId, browsePath, _attributeId, _indexRange, locales, result); 
	}
	
	Status_t AuditEventTypeData_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
	{
		return CopyToDestination(*this, destination);
	}
	
	Status_t AuditEventTypeData_t::CopyFrom(const BaseDataType_t& source)
	{
		IntrusivePtr_t<const AuditEventTypeData_t> ptr = RuntimeCast<const AuditEventTypeData_t*>(source);
		if (!ptr.is_set())
		{
			return OpcUa_BadTypeMismatch;
		}
		
		return CopyFrom(*ptr);
	}
	
	Status_t AuditEventTypeData_t::CopyFrom(const AuditEventTypeData_t& source)
	{
		Status_t result = OpcUa_Good;
		actionTimeStamp.reset();
		
		if(source.actionTimeStamp.is_set())
		
		{
		
		  actionTimeStamp = new SafeRefCount_t<UtcTime_t>();
		
		  if(!actionTimeStamp.is_set())
		
		  {
		
		    return OpcUa_BadOutOfMemory;
		
		  }
		
		
		
		  result = actionTimeStamp->CopyFrom(*source.ActionTimeStamp());
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		status.reset();
		
		if(source.status.is_set())
		
		{
		
		  status = new SafeRefCount_t<Boolean_t>();
		
		  if(!status.is_set())
		
		  {
		
		    return OpcUa_BadOutOfMemory;
		
		  }
		
		
		
		  result = status->CopyFrom(*source.Status());
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		serverId.reset();
		
		if(source.serverId.is_set())
		
		{
		
		  serverId = new SafeRefCount_t<String_t>();
		
		  if(!serverId.is_set())
		
		  {
		
		    return OpcUa_BadOutOfMemory;
		
		  }
		
		
		
		  result = serverId->CopyFrom(*source.ServerId());
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		clientAuditEntryId.reset();
		
		if(source.clientAuditEntryId.is_set())
		
		{
		
		  clientAuditEntryId = new SafeRefCount_t<String_t>();
		
		  if(!clientAuditEntryId.is_set())
		
		  {
		
		    return OpcUa_BadOutOfMemory;
		
		  }
		
		
		
		  result = clientAuditEntryId->CopyFrom(*source.ClientAuditEntryId());
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		clientUserId.reset();
		
		if(source.clientUserId.is_set())
		
		{
		
		  clientUserId = new SafeRefCount_t<String_t>();
		
		  if(!clientUserId.is_set())
		
		  {
		
		    return OpcUa_BadOutOfMemory;
		
		  }
		
		
		
		  result = clientUserId->CopyFrom(*source.ClientUserId());
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		
		result = BaseEventTypeData_t::CopyFrom(source);
		return result;
	}
	
} // namespace

#endif //(UASDK_INCLUDE_EVENTS > 0)

