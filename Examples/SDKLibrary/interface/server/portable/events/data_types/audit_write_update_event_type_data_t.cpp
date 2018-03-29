

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



#include "audit_write_update_event_type_data_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "opcua_node_id_numeric_t.h"
#include "opcua_server_state_t.h"
namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(AuditWriteUpdateEventTypeData_t, AuditUpdateEventTypeData_t);

AuditWriteUpdateEventTypeData_t::AuditWriteUpdateEventTypeData_t()
{
}

AuditWriteUpdateEventTypeData_t::~AuditWriteUpdateEventTypeData_t()
{
}

bool AuditWriteUpdateEventTypeData_t::IsOfType(const uint32_t typeId, uint16_t namespaceindex) const
{
	if(namespaceindex != 0) return false;
	return typeId == 2100 || AuditUpdateEventTypeData_t::IsOfType(typeId, namespaceindex);
}

Status_t AuditWriteUpdateEventTypeData_t::Initialise()
{
	Status_t rtnStatus = OpcUa_Good;
	browseName = new SafeRefCount_t<String_t>();
	UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(browseName);
	rtnStatus = browseName->CopyFrom("AuditWriteUpdateEventType");
	UASDK_RETURN_STATUS_ONLY_IF_BAD(rtnStatus.Value());
	
	attributeId.reset();
	
	indexRange.reset();
	
	oldValue.reset();
	
	newValue.reset();
	
	
	return AuditUpdateEventTypeData_t::Initialise();
}

uint32_t AuditWriteUpdateEventTypeData_t::TypeId(uint16_t& namespaceIndex) const
{
	namespaceIndex = 0;
	return AuditWriteUpdateEventTypeData_t::TYPE_ID;
}

IntrusivePtr_t<BaseDataType_t> AuditWriteUpdateEventTypeData_t::AttributeValue(const uint32_t& typeId, const ArrayUA_t<QualifiedName_t>&browsePath, const uint32_t &_attributeId, const String_t& _indexRange, const ArrayUA_t<String_t> & locales,  Status_t &result)
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
	if(UASDK_strcmp(nameStr, "AttributeId") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
		result = OpcUa_Good;
	
		return attributeId;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "IndexRange") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
		result = OpcUa_Good;
	
		return indexRange;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "OldValue") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
		result = OpcUa_Good;
	
		return oldValue;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "NewValue") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
		result = OpcUa_Good;
	
		return newValue;
	
	};
	
	
	
	
	/* end class specific attributes */
	
		return AuditUpdateEventTypeData_t::AttributeValue(typeId, browsePath, _attributeId, _indexRange, locales, result); 
	}
	
	IntrusivePtr_t<const BaseDataType_t> AuditWriteUpdateEventTypeData_t::AttributeValue(const uint32_t& typeId, const ArrayUA_t<QualifiedName_t>&browsePath, const uint32_t &_attributeId, const String_t& _indexRange, const ArrayUA_t<String_t> & locales, Status_t &result) const
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
		if(UASDK_strcmp(nameStr, "AttributeId") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
			result = OpcUa_Good;
		
			return attributeId;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "IndexRange") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
			result = OpcUa_Good;
		
			return indexRange;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "OldValue") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
			result = OpcUa_Good;
		
			return oldValue;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "NewValue") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
			result = OpcUa_Good;
		
			return newValue;
		
		};
		
		
		
		
		/* end class specific attributes */
		
		return AuditUpdateEventTypeData_t::AttributeValue(typeId, browsePath, _attributeId, _indexRange, locales, result); 
	}
	
	Status_t AuditWriteUpdateEventTypeData_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
	{
		return CopyToDestination(*this, destination);
	}
	
	Status_t AuditWriteUpdateEventTypeData_t::CopyFrom(const BaseDataType_t& source)
	{
		IntrusivePtr_t<const AuditWriteUpdateEventTypeData_t> ptr = RuntimeCast<const AuditWriteUpdateEventTypeData_t*>(source);
		if (!ptr.is_set())
		{
			return OpcUa_BadTypeMismatch;
		}
		
		return CopyFrom(*ptr);
	}
	
	Status_t AuditWriteUpdateEventTypeData_t::CopyFrom(const AuditWriteUpdateEventTypeData_t& source)
	{
		Status_t result = OpcUa_Good;
		attributeId.reset();
		
		if(source.attributeId.is_set())
		
		{
		
		  attributeId = new SafeRefCount_t<UInt32_t>();
		
		  if(!attributeId.is_set())
		
		  {
		
		    return OpcUa_BadOutOfMemory;
		
		  }
		
		
		
		  result = attributeId->CopyFrom(*source.AttributeId());
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		indexRange.reset();
		
		if(source.indexRange.is_set())
		
		{
		
		  indexRange = new SafeRefCount_t<NumericRange_t>();
		
		  if(!indexRange.is_set())
		
		  {
		
		    return OpcUa_BadOutOfMemory;
		
		  }
		
		
		
		  result = indexRange->CopyFrom(*source.IndexRange());
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		oldValue.reset();
		
		if(source.oldValue.is_set())
		
		{
		
		  result = source.oldValue->CopyTo(oldValue);
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		newValue.reset();
		
		if(source.newValue.is_set())
		
		{
		
		  result = source.newValue->CopyTo(newValue);
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		
		result = AuditUpdateEventTypeData_t::CopyFrom(source);
		return result;
	}
	
} // namespace

#endif //(UASDK_INCLUDE_EVENTS > 0)

