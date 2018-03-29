

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



#include "acknowledgeable_condition_type_data_t.h"

#if ((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

#include "opcua_node_id_numeric_t.h"
#include "opcua_server_state_t.h"
namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(AcknowledgeableConditionTypeData_t, ConditionTypeData_t);

AcknowledgeableConditionTypeData_t::AcknowledgeableConditionTypeData_t()
{
}

AcknowledgeableConditionTypeData_t::~AcknowledgeableConditionTypeData_t()
{
}

bool AcknowledgeableConditionTypeData_t::IsOfType(const uint32_t typeId, uint16_t namespaceindex) const
{
	if(namespaceindex != 0) return false;
	return typeId == 2881 || ConditionTypeData_t::IsOfType(typeId, namespaceindex);
}

Status_t AcknowledgeableConditionTypeData_t::Initialise()
{
	Status_t rtnStatus = OpcUa_Good;
	browseName = new SafeRefCount_t<String_t>();
	UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(browseName);
	rtnStatus = browseName->CopyFrom("AcknowledgeableConditionType");
	UASDK_RETURN_STATUS_ONLY_IF_BAD(rtnStatus.Value());
	
	
	return ConditionTypeData_t::Initialise();
}

uint32_t AcknowledgeableConditionTypeData_t::TypeId(uint16_t& namespaceIndex) const
{
	namespaceIndex = 0;
	return AcknowledgeableConditionTypeData_t::TYPE_ID;
}

IntrusivePtr_t<BaseDataType_t> AcknowledgeableConditionTypeData_t::AttributeValue(const uint32_t& typeId, const ArrayUA_t<QualifiedName_t>&browsePath, const uint32_t &_attributeId, const String_t& _indexRange, const ArrayUA_t<String_t> & locales,  Status_t &result)
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
	if(UASDK_strcmp(nameStr, "AckedState") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 11
	
	{
	
		result = OpcUa_Good;
	
		IntrusivePtr_t<LocalizedText_t> localizedText;
	
		localizedText = new SafeRefCount_t<LocalizedText_t>();
	
		if (localizedText.is_set())
	
		{
	
			if (ackedState.is_set() && ackedState->Value().is_set())
	
			{
	
			localizedText->CopyFrom(*ackedState->Value()->GetLocalizedText(locales, result));
	
			}
	
		}
	
		else
	
		{
	
			result = OpcUa_BadOutOfMemory;
	
		}
	
		return localizedText;
	
	
	
	}
	
	
	
	if(UASDK_strcmp(nameStr, "AckedState.Id") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
	if(AckedState().is_set())
	
	{
	
		
	
		result = OpcUa_Good;
	
		return AckedState()->Id();
	
	}
	
	result = OpcUa_BadAttributeIdInvalid;
	
	return emptyResult;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "AckedState.TransitionTime") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
	if(AckedState().is_set())
	
	{
	
		
	
		result = OpcUa_Good;
	
		return AckedState()->TransitionTime();
	
	}
	
	result = OpcUa_BadAttributeIdInvalid;
	
	return emptyResult;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "ConfirmedState") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 11
	
	{
	
		result = OpcUa_Good;
	
		IntrusivePtr_t<LocalizedText_t> localizedText;
	
		localizedText = new SafeRefCount_t<LocalizedText_t>();
	
		if (localizedText.is_set())
	
		{
	
			if (confirmedState.is_set() && confirmedState->Value().is_set())
	
			{
	
			localizedText->CopyFrom(*confirmedState->Value()->GetLocalizedText(locales, result));
	
			}
	
		}
	
		else
	
		{
	
			result = OpcUa_BadOutOfMemory;
	
		}
	
		return localizedText;
	
	
	
	}
	
	
	
	if(UASDK_strcmp(nameStr, "ConfirmedState.Id") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
	if(ConfirmedState().is_set())
	
	{
	
		
	
		result = OpcUa_Good;
	
		return ConfirmedState()->Id();
	
	}
	
	result = OpcUa_BadAttributeIdInvalid;
	
	return emptyResult;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "ConfirmedState.TransitionTime") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
	if(ConfirmedState().is_set())
	
	{
	
		
	
		result = OpcUa_Good;
	
		return ConfirmedState()->TransitionTime();
	
	}
	
	result = OpcUa_BadAttributeIdInvalid;
	
	return emptyResult;
	
	};
	
	
	
	
	/* end class specific attributes */
	
		return ConditionTypeData_t::AttributeValue(typeId, browsePath, _attributeId, _indexRange, locales, result); 
	}
	
	IntrusivePtr_t<const BaseDataType_t> AcknowledgeableConditionTypeData_t::AttributeValue(const uint32_t& typeId, const ArrayUA_t<QualifiedName_t>&browsePath, const uint32_t &_attributeId, const String_t& _indexRange, const ArrayUA_t<String_t> & locales, Status_t &result) const
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
		if(UASDK_strcmp(nameStr, "AckedState") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 11
		
		{
		
			result = OpcUa_Good;
		
			IntrusivePtr_t<LocalizedText_t> localizedText;
		
			localizedText = new SafeRefCount_t<LocalizedText_t>();
		
			if (localizedText.is_set())
		
			{
		
				if (ackedState.is_set() && ackedState->Value().is_set())
		
				{
		
				localizedText->CopyFrom(*ackedState->Value()->GetLocalizedText(locales, result));
		
				}
		
			}
		
			else
		
			{
		
				result = OpcUa_BadOutOfMemory;
		
			}
		
			return localizedText;
		
		
		
		}
		
		
		
		if(UASDK_strcmp(nameStr, "AckedState.Id") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
		if(AckedState().is_set())
		
		{
		
			
		
			result = OpcUa_Good;
		
			return AckedState()->Id();
		
		}
		
		result = OpcUa_BadAttributeIdInvalid;
		
		return emptyResult;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "AckedState.TransitionTime") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
		if(AckedState().is_set())
		
		{
		
			
		
			result = OpcUa_Good;
		
			return AckedState()->TransitionTime();
		
		}
		
		result = OpcUa_BadAttributeIdInvalid;
		
		return emptyResult;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "ConfirmedState") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 11
		
		{
		
			result = OpcUa_Good;
		
			IntrusivePtr_t<LocalizedText_t> localizedText;
		
			localizedText = new SafeRefCount_t<LocalizedText_t>();
		
			if (localizedText.is_set())
		
			{
		
				if (confirmedState.is_set() && confirmedState->Value().is_set())
		
				{
		
				localizedText->CopyFrom(*confirmedState->Value()->GetLocalizedText(locales, result));
		
				}
		
			}
		
			else
		
			{
		
				result = OpcUa_BadOutOfMemory;
		
			}
		
			return localizedText;
		
		
		
		}
		
		
		
		if(UASDK_strcmp(nameStr, "ConfirmedState.Id") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
		if(ConfirmedState().is_set())
		
		{
		
			
		
			result = OpcUa_Good;
		
			return ConfirmedState()->Id();
		
		}
		
		result = OpcUa_BadAttributeIdInvalid;
		
		return emptyResult;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "ConfirmedState.TransitionTime") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
		if(ConfirmedState().is_set())
		
		{
		
			
		
			result = OpcUa_Good;
		
			return ConfirmedState()->TransitionTime();
		
		}
		
		result = OpcUa_BadAttributeIdInvalid;
		
		return emptyResult;
		
		};
		
		
		
		
		/* end class specific attributes */
		
		return ConditionTypeData_t::AttributeValue(typeId, browsePath, _attributeId, _indexRange, locales, result); 
	}
	
	Status_t AcknowledgeableConditionTypeData_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
	{
		return CopyToDestination(*this, destination);
	}
	
	Status_t AcknowledgeableConditionTypeData_t::CopyFrom(const BaseDataType_t& source)
	{
		IntrusivePtr_t<const AcknowledgeableConditionTypeData_t> ptr = RuntimeCast<const AcknowledgeableConditionTypeData_t*>(source);
		if (!ptr.is_set())
		{
			return OpcUa_BadTypeMismatch;
		}
		
		return CopyFrom(*ptr);
	}
	
	Status_t AcknowledgeableConditionTypeData_t::CopyFrom(const AcknowledgeableConditionTypeData_t& source)
	{
		Status_t result = OpcUa_Good;
		ackedState.reset();
		
		if(source.ackedState.is_set())
		
		{
		
		  result = source.ackedState->CopyTo(ackedState);
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		confirmedState.reset();
		
		if(source.confirmedState.is_set())
		
		{
		
		  result = source.confirmedState->CopyTo(confirmedState);
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		
		result = ConditionTypeData_t::CopyFrom(source);
		return result;
	}
	
} // namespace

#endif //((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

