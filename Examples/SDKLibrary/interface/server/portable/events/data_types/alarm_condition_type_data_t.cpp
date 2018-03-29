

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



#include "alarm_condition_type_data_t.h"

#if ((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

#include "opcua_node_id_numeric_t.h"
#include "opcua_server_state_t.h"
namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(AlarmConditionTypeData_t, AcknowledgeableConditionTypeData_t);

AlarmConditionTypeData_t::AlarmConditionTypeData_t()
{
}

AlarmConditionTypeData_t::~AlarmConditionTypeData_t()
{
}

bool AlarmConditionTypeData_t::IsOfType(const uint32_t typeId, uint16_t namespaceindex) const
{
	if(namespaceindex != 0) return false;
	return typeId == 2915 || AcknowledgeableConditionTypeData_t::IsOfType(typeId, namespaceindex);
}

Status_t AlarmConditionTypeData_t::Initialise()
{
	Status_t rtnStatus = OpcUa_Good;
	browseName = new SafeRefCount_t<String_t>();
	UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(browseName);
	rtnStatus = browseName->CopyFrom("AlarmConditionType");
	UASDK_RETURN_STATUS_ONLY_IF_BAD(rtnStatus.Value());
	
	inputNode.reset();
	
	suppressedOrShelved.reset();
	
	maxTimeShelved.reset();
	
	ShelvingState_unshelveTime.reset();
	
	
	return AcknowledgeableConditionTypeData_t::Initialise();
}

uint32_t AlarmConditionTypeData_t::TypeId(uint16_t& namespaceIndex) const
{
	namespaceIndex = 0;
	return AlarmConditionTypeData_t::TYPE_ID;
}

IntrusivePtr_t<BaseDataType_t> AlarmConditionTypeData_t::AttributeValue(const uint32_t& typeId, const ArrayUA_t<QualifiedName_t>&browsePath, const uint32_t &_attributeId, const String_t& _indexRange, const ArrayUA_t<String_t> & locales,  Status_t &result)
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
	if(UASDK_strcmp(nameStr, "InputNode") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
		result = OpcUa_Good;
	
		return inputNode;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "SuppressedOrShelved") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
		result = OpcUa_Good;
	
		return suppressedOrShelved;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "MaxTimeShelved") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
		result = OpcUa_Good;
	
		return maxTimeShelved;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "ActiveState") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 11
	
	{
	
		result = OpcUa_Good;
	
		IntrusivePtr_t<LocalizedText_t> localizedText;
	
		localizedText = new SafeRefCount_t<LocalizedText_t>();
	
		if (localizedText.is_set())
	
		{
	
			if (activeState.is_set() && activeState->Value().is_set())
	
			{
	
			localizedText->CopyFrom(*activeState->Value()->GetLocalizedText(locales, result));
	
			}
	
		}
	
		else
	
		{
	
			result = OpcUa_BadOutOfMemory;
	
		}
	
		return localizedText;
	
	
	
	}
	
	
	
	if(UASDK_strcmp(nameStr, "ActiveState.Id") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
	if(ActiveState().is_set())
	
	{
	
		
	
		result = OpcUa_Good;
	
		return ActiveState()->Id();
	
	}
	
	result = OpcUa_BadAttributeIdInvalid;
	
	return emptyResult;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "ActiveState.EffectiveDisplayName") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
	if(ActiveState().is_set())
	
	{
	
		
	
		result = OpcUa_Good;
	
		return ActiveState()->EffectiveDisplayName();
	
	}
	
	result = OpcUa_BadAttributeIdInvalid;
	
	return emptyResult;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "ActiveState.TransitionTime") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
	if(ActiveState().is_set())
	
	{
	
		
	
		result = OpcUa_Good;
	
		return ActiveState()->TransitionTime();
	
	}
	
	result = OpcUa_BadAttributeIdInvalid;
	
	return emptyResult;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "ActiveState.EffectiveTransitionTime") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
	if(ActiveState().is_set())
	
	{
	
		
	
		result = OpcUa_Good;
	
		return ActiveState()->EffectiveTransitionTime();
	
	}
	
	result = OpcUa_BadAttributeIdInvalid;
	
	return emptyResult;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "SuppressedState") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 11
	
	{
	
		result = OpcUa_Good;
	
		IntrusivePtr_t<LocalizedText_t> localizedText;
	
		localizedText = new SafeRefCount_t<LocalizedText_t>();
	
		if (localizedText.is_set())
	
		{
	
			if (suppressedState.is_set() && suppressedState->Value().is_set())
	
			{
	
			localizedText->CopyFrom(*suppressedState->Value()->GetLocalizedText(locales, result));
	
			}
	
		}
	
		else
	
		{
	
			result = OpcUa_BadOutOfMemory;
	
		}
	
		return localizedText;
	
	
	
	}
	
	
	
	if(UASDK_strcmp(nameStr, "SuppressedState.Id") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
	if(SuppressedState().is_set())
	
	{
	
		
	
		result = OpcUa_Good;
	
		return SuppressedState()->Id();
	
	}
	
	result = OpcUa_BadAttributeIdInvalid;
	
	return emptyResult;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "SuppressedState.TransitionTime") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
	if(SuppressedState().is_set())
	
	{
	
		
	
		result = OpcUa_Good;
	
		return SuppressedState()->TransitionTime();
	
	}
	
	result = OpcUa_BadAttributeIdInvalid;
	
	return emptyResult;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "ShelvingState.UnshelveTime") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
		result = OpcUa_Good;
	
		return ShelvingState_unshelveTime;
	
	};
	
	
	
	
	/* end class specific attributes */
	
		return AcknowledgeableConditionTypeData_t::AttributeValue(typeId, browsePath, _attributeId, _indexRange, locales, result); 
	}
	
	IntrusivePtr_t<const BaseDataType_t> AlarmConditionTypeData_t::AttributeValue(const uint32_t& typeId, const ArrayUA_t<QualifiedName_t>&browsePath, const uint32_t &_attributeId, const String_t& _indexRange, const ArrayUA_t<String_t> & locales, Status_t &result) const
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
		if(UASDK_strcmp(nameStr, "InputNode") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
			result = OpcUa_Good;
		
			return inputNode;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "SuppressedOrShelved") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
			result = OpcUa_Good;
		
			return suppressedOrShelved;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "MaxTimeShelved") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
			result = OpcUa_Good;
		
			return maxTimeShelved;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "ActiveState") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 11
		
		{
		
			result = OpcUa_Good;
		
			IntrusivePtr_t<LocalizedText_t> localizedText;
		
			localizedText = new SafeRefCount_t<LocalizedText_t>();
		
			if (localizedText.is_set())
		
			{
		
				if (activeState.is_set() && activeState->Value().is_set())
		
				{
		
				localizedText->CopyFrom(*activeState->Value()->GetLocalizedText(locales, result));
		
				}
		
			}
		
			else
		
			{
		
				result = OpcUa_BadOutOfMemory;
		
			}
		
			return localizedText;
		
		
		
		}
		
		
		
		if(UASDK_strcmp(nameStr, "ActiveState.Id") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
		if(ActiveState().is_set())
		
		{
		
			
		
			result = OpcUa_Good;
		
			return ActiveState()->Id();
		
		}
		
		result = OpcUa_BadAttributeIdInvalid;
		
		return emptyResult;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "ActiveState.EffectiveDisplayName") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
		if(ActiveState().is_set())
		
		{
		
			
		
			result = OpcUa_Good;
		
			return ActiveState()->EffectiveDisplayName();
		
		}
		
		result = OpcUa_BadAttributeIdInvalid;
		
		return emptyResult;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "ActiveState.TransitionTime") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
		if(ActiveState().is_set())
		
		{
		
			
		
			result = OpcUa_Good;
		
			return ActiveState()->TransitionTime();
		
		}
		
		result = OpcUa_BadAttributeIdInvalid;
		
		return emptyResult;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "ActiveState.EffectiveTransitionTime") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
		if(ActiveState().is_set())
		
		{
		
			
		
			result = OpcUa_Good;
		
			return ActiveState()->EffectiveTransitionTime();
		
		}
		
		result = OpcUa_BadAttributeIdInvalid;
		
		return emptyResult;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "SuppressedState") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 11
		
		{
		
			result = OpcUa_Good;
		
			IntrusivePtr_t<LocalizedText_t> localizedText;
		
			localizedText = new SafeRefCount_t<LocalizedText_t>();
		
			if (localizedText.is_set())
		
			{
		
				if (suppressedState.is_set() && suppressedState->Value().is_set())
		
				{
		
				localizedText->CopyFrom(*suppressedState->Value()->GetLocalizedText(locales, result));
		
				}
		
			}
		
			else
		
			{
		
				result = OpcUa_BadOutOfMemory;
		
			}
		
			return localizedText;
		
		
		
		}
		
		
		
		if(UASDK_strcmp(nameStr, "SuppressedState.Id") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
		if(SuppressedState().is_set())
		
		{
		
			
		
			result = OpcUa_Good;
		
			return SuppressedState()->Id();
		
		}
		
		result = OpcUa_BadAttributeIdInvalid;
		
		return emptyResult;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "SuppressedState.TransitionTime") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
		if(SuppressedState().is_set())
		
		{
		
			
		
			result = OpcUa_Good;
		
			return SuppressedState()->TransitionTime();
		
		}
		
		result = OpcUa_BadAttributeIdInvalid;
		
		return emptyResult;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "ShelvingState.UnshelveTime") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
			result = OpcUa_Good;
		
			return ShelvingState_unshelveTime;
		
		};
		
		
		
		
		/* end class specific attributes */
		
		return AcknowledgeableConditionTypeData_t::AttributeValue(typeId, browsePath, _attributeId, _indexRange, locales, result); 
	}
	
	Status_t AlarmConditionTypeData_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
	{
		return CopyToDestination(*this, destination);
	}
	
	Status_t AlarmConditionTypeData_t::CopyFrom(const BaseDataType_t& source)
	{
		IntrusivePtr_t<const AlarmConditionTypeData_t> ptr = RuntimeCast<const AlarmConditionTypeData_t*>(source);
		if (!ptr.is_set())
		{
			return OpcUa_BadTypeMismatch;
		}
		
		return CopyFrom(*ptr);
	}
	
	Status_t AlarmConditionTypeData_t::CopyFrom(const AlarmConditionTypeData_t& source)
	{
		Status_t result = OpcUa_Good;
		inputNode.reset();
		
		if(source.inputNode.is_set())
		
		{
		
		  result = source.inputNode->CopyToNodeId(inputNode);
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		suppressedOrShelved.reset();
		
		if(source.suppressedOrShelved.is_set())
		
		{
		
		  suppressedOrShelved = new SafeRefCount_t<Boolean_t>();
		
		  if(!suppressedOrShelved.is_set())
		
		  {
		
		    return OpcUa_BadOutOfMemory;
		
		  }
		
		
		
		  result = suppressedOrShelved->CopyFrom(*source.SuppressedOrShelved());
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		maxTimeShelved.reset();
		
		if(source.maxTimeShelved.is_set())
		
		{
		
		  maxTimeShelved = new SafeRefCount_t<Duration_t>();
		
		  if(!maxTimeShelved.is_set())
		
		  {
		
		    return OpcUa_BadOutOfMemory;
		
		  }
		
		
		
		  result = maxTimeShelved->CopyFrom(*source.MaxTimeShelved());
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		activeState.reset();
		
		if(source.activeState.is_set())
		
		{
		
		  result = source.activeState->CopyTo(activeState);
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		suppressedState.reset();
		
		if(source.suppressedState.is_set())
		
		{
		
		  result = source.suppressedState->CopyTo(suppressedState);
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		ShelvingState_unshelveTime.reset();
		
		if(source.ShelvingState_unshelveTime.is_set())
		
		{
		
		  ShelvingState_unshelveTime = new SafeRefCount_t<Duration_t>();
		
		  if(!ShelvingState_unshelveTime.is_set())
		
		  {
		
		    return OpcUa_BadOutOfMemory;
		
		  }
		
		
		
		  result = ShelvingState_unshelveTime->CopyFrom(*source.ShelvingState_UnshelveTime());
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		
		result = AcknowledgeableConditionTypeData_t::CopyFrom(source);
		return result;
	}
	
} // namespace

#endif //((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

