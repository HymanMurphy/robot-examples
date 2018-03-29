

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



#include "condition_type_data_t.h"

#if ((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

#include "opcua_node_id_numeric_t.h"
#include "opcua_server_state_t.h"
namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(ConditionTypeData_t, BaseEventTypeData_t);

ConditionTypeData_t::ConditionTypeData_t()
{
}

ConditionTypeData_t::~ConditionTypeData_t()
{
}

bool ConditionTypeData_t::IsOfType(const uint32_t typeId, uint16_t namespaceindex) const
{
	if(namespaceindex != 0) return false;
	return typeId == 2782 || BaseEventTypeData_t::IsOfType(typeId, namespaceindex);
}

Status_t ConditionTypeData_t::Initialise()
{
	Status_t rtnStatus = OpcUa_Good;
	browseName = new SafeRefCount_t<String_t>();
	UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(browseName);
	rtnStatus = browseName->CopyFrom("ConditionType");
	UASDK_RETURN_STATUS_ONLY_IF_BAD(rtnStatus.Value());
	
	conditionClassId.reset();
	
	conditionClassName.reset();
	
	conditionName.reset();
	
	branchId.reset();
	
	retain.reset();
	
	clientUserId.reset();
	
	
	return BaseEventTypeData_t::Initialise();
}

uint32_t ConditionTypeData_t::TypeId(uint16_t& namespaceIndex) const
{
	namespaceIndex = 0;
	return ConditionTypeData_t::TYPE_ID;
}

IntrusivePtr_t<BaseDataType_t> ConditionTypeData_t::AttributeValue(const uint32_t& typeId, const ArrayUA_t<QualifiedName_t>&browsePath, const uint32_t &_attributeId, const String_t& _indexRange, const ArrayUA_t<String_t> & locales,  Status_t &result)
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
	if(UASDK_strcmp(nameStr, "ConditionClassId") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
		result = OpcUa_Good;
	
		return conditionClassId;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "ConditionClassName") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
		result = OpcUa_Good;
	
		return conditionClassName;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "ConditionName") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
		result = OpcUa_Good;
	
		return conditionName;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "BranchId") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
		result = OpcUa_Good;
	
		return branchId;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "Retain") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
		result = OpcUa_Good;
	
		return retain;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "ClientUserId") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
		result = OpcUa_Good;
	
		return clientUserId;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "EnabledState") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 11
	
	{
	
		result = OpcUa_Good;
	
		IntrusivePtr_t<LocalizedText_t> localizedText;
	
		localizedText = new SafeRefCount_t<LocalizedText_t>();
	
		if (localizedText.is_set())
	
		{
	
			if (enabledState.is_set() && enabledState->Value().is_set())
	
			{
	
			localizedText->CopyFrom(*enabledState->Value()->GetLocalizedText(locales, result));
	
			}
	
		}
	
		else
	
		{
	
			result = OpcUa_BadOutOfMemory;
	
		}
	
		return localizedText;
	
	
	
	}
	
	
	
	if(UASDK_strcmp(nameStr, "EnabledState.Id") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
	if(EnabledState().is_set())
	
	{
	
		
	
		result = OpcUa_Good;
	
		return EnabledState()->Id();
	
	}
	
	result = OpcUa_BadAttributeIdInvalid;
	
	return emptyResult;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "EnabledState.EffectiveDisplayName") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
	if(EnabledState().is_set())
	
	{
	
		
	
		result = OpcUa_Good;
	
		return EnabledState()->EffectiveDisplayName();
	
	}
	
	result = OpcUa_BadAttributeIdInvalid;
	
	return emptyResult;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "EnabledState.TransitionTime") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
	if(EnabledState().is_set())
	
	{
	
		
	
		result = OpcUa_Good;
	
		return EnabledState()->TransitionTime();
	
	}
	
	result = OpcUa_BadAttributeIdInvalid;
	
	return emptyResult;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "EnabledState.EffectiveTransitionTime") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
	if(EnabledState().is_set())
	
	{
	
		
	
		result = OpcUa_Good;
	
		return EnabledState()->EffectiveTransitionTime();
	
	}
	
	result = OpcUa_BadAttributeIdInvalid;
	
	return emptyResult;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "Quality") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 11
	
	{
	
		result = OpcUa_Good;
	
		return quality->Value();
	
	}
	
	
	
	if(UASDK_strcmp(nameStr, "Quality.SourceTimestamp") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
	if(Quality().is_set())
	
	{
	
		
	
		result = OpcUa_Good;
	
		return Quality()->SourceTimestamp();
	
	}
	
	result = OpcUa_BadAttributeIdInvalid;
	
	return emptyResult;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "LastSeverity") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 11
	
	{
	
		result = OpcUa_Good;
	
		return lastSeverity->Value();
	
	}
	
	
	
	if(UASDK_strcmp(nameStr, "LastSeverity.SourceTimestamp") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
	if(LastSeverity().is_set())
	
	{
	
		
	
		result = OpcUa_Good;
	
		return LastSeverity()->SourceTimestamp();
	
	}
	
	result = OpcUa_BadAttributeIdInvalid;
	
	return emptyResult;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "Comment") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 11
	
	{
	
		result = OpcUa_Good;
	
		return comment->Value();
	
	}
	
	
	
	if(UASDK_strcmp(nameStr, "Comment.SourceTimestamp") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
	if(Comment().is_set())
	
	{
	
		
	
		result = OpcUa_Good;
	
		return Comment()->SourceTimestamp();
	
	}
	
	result = OpcUa_BadAttributeIdInvalid;
	
	return emptyResult;
	
	};
	
	
	
	
	/* end class specific attributes */
	
		return BaseEventTypeData_t::AttributeValue(typeId, browsePath, _attributeId, _indexRange, locales, result); 
	}
	
	IntrusivePtr_t<const BaseDataType_t> ConditionTypeData_t::AttributeValue(const uint32_t& typeId, const ArrayUA_t<QualifiedName_t>&browsePath, const uint32_t &_attributeId, const String_t& _indexRange, const ArrayUA_t<String_t> & locales, Status_t &result) const
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
		if(UASDK_strcmp(nameStr, "ConditionClassId") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
			result = OpcUa_Good;
		
			return conditionClassId;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "ConditionClassName") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
			result = OpcUa_Good;
		
			return conditionClassName;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "ConditionName") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
			result = OpcUa_Good;
		
			return conditionName;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "BranchId") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
			result = OpcUa_Good;
		
			return branchId;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "Retain") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
			result = OpcUa_Good;
		
			return retain;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "ClientUserId") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
			result = OpcUa_Good;
		
			return clientUserId;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "EnabledState") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 11
		
		{
		
			result = OpcUa_Good;
		
			IntrusivePtr_t<LocalizedText_t> localizedText;
		
			localizedText = new SafeRefCount_t<LocalizedText_t>();
		
			if (localizedText.is_set())
		
			{
		
				if (enabledState.is_set() && enabledState->Value().is_set())
		
				{
		
				localizedText->CopyFrom(*enabledState->Value()->GetLocalizedText(locales, result));
		
				}
		
			}
		
			else
		
			{
		
				result = OpcUa_BadOutOfMemory;
		
			}
		
			return localizedText;
		
		
		
		}
		
		
		
		if(UASDK_strcmp(nameStr, "EnabledState.Id") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
		if(EnabledState().is_set())
		
		{
		
			
		
			result = OpcUa_Good;
		
			return EnabledState()->Id();
		
		}
		
		result = OpcUa_BadAttributeIdInvalid;
		
		return emptyResult;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "EnabledState.EffectiveDisplayName") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
		if(EnabledState().is_set())
		
		{
		
			
		
			result = OpcUa_Good;
		
			return EnabledState()->EffectiveDisplayName();
		
		}
		
		result = OpcUa_BadAttributeIdInvalid;
		
		return emptyResult;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "EnabledState.TransitionTime") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
		if(EnabledState().is_set())
		
		{
		
			
		
			result = OpcUa_Good;
		
			return EnabledState()->TransitionTime();
		
		}
		
		result = OpcUa_BadAttributeIdInvalid;
		
		return emptyResult;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "EnabledState.EffectiveTransitionTime") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
		if(EnabledState().is_set())
		
		{
		
			
		
			result = OpcUa_Good;
		
			return EnabledState()->EffectiveTransitionTime();
		
		}
		
		result = OpcUa_BadAttributeIdInvalid;
		
		return emptyResult;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "Quality") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 11
		
		{
		
			result = OpcUa_Good;
		
			return quality->Value();
		
		}
		
		
		
		if(UASDK_strcmp(nameStr, "Quality.SourceTimestamp") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
		if(Quality().is_set())
		
		{
		
			
		
			result = OpcUa_Good;
		
			return Quality()->SourceTimestamp();
		
		}
		
		result = OpcUa_BadAttributeIdInvalid;
		
		return emptyResult;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "LastSeverity") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 11
		
		{
		
			result = OpcUa_Good;
		
			return lastSeverity->Value();
		
		}
		
		
		
		if(UASDK_strcmp(nameStr, "LastSeverity.SourceTimestamp") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
		if(LastSeverity().is_set())
		
		{
		
			
		
			result = OpcUa_Good;
		
			return LastSeverity()->SourceTimestamp();
		
		}
		
		result = OpcUa_BadAttributeIdInvalid;
		
		return emptyResult;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "Comment") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 11
		
		{
		
			result = OpcUa_Good;
		
			return comment->Value();
		
		}
		
		
		
		if(UASDK_strcmp(nameStr, "Comment.SourceTimestamp") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
		if(Comment().is_set())
		
		{
		
			
		
			result = OpcUa_Good;
		
			return Comment()->SourceTimestamp();
		
		}
		
		result = OpcUa_BadAttributeIdInvalid;
		
		return emptyResult;
		
		};
		
		
		
		
		/* end class specific attributes */
		
		return BaseEventTypeData_t::AttributeValue(typeId, browsePath, _attributeId, _indexRange, locales, result); 
	}
	
	Status_t ConditionTypeData_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
	{
		return CopyToDestination(*this, destination);
	}
	
	Status_t ConditionTypeData_t::CopyFrom(const BaseDataType_t& source)
	{
		IntrusivePtr_t<const ConditionTypeData_t> ptr = RuntimeCast<const ConditionTypeData_t*>(source);
		if (!ptr.is_set())
		{
			return OpcUa_BadTypeMismatch;
		}
		
		return CopyFrom(*ptr);
	}
	
	Status_t ConditionTypeData_t::CopyFrom(const ConditionTypeData_t& source)
	{
		Status_t result = OpcUa_Good;
		conditionClassId.reset();
		
		if(source.conditionClassId.is_set())
		
		{
		
		  result = source.conditionClassId->CopyToNodeId(conditionClassId);
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		conditionClassName.reset();
		
		if(source.conditionClassName.is_set())
		
		{
		
		  conditionClassName = new SafeRefCount_t<LocalizedText_t>();
		
		  if(!conditionClassName.is_set())
		
		  {
		
		    return OpcUa_BadOutOfMemory;
		
		  }
		
		
		
		  result = conditionClassName->CopyFrom(*source.ConditionClassName());
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		conditionName.reset();
		
		if(source.conditionName.is_set())
		
		{
		
		  conditionName = new SafeRefCount_t<String_t>();
		
		  if(!conditionName.is_set())
		
		  {
		
		    return OpcUa_BadOutOfMemory;
		
		  }
		
		
		
		  result = conditionName->CopyFrom(*source.ConditionName());
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		branchId.reset();
		
		if(source.branchId.is_set())
		
		{
		
		  result = source.branchId->CopyToNodeId(branchId);
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		retain.reset();
		
		if(source.retain.is_set())
		
		{
		
		  retain = new SafeRefCount_t<Boolean_t>();
		
		  if(!retain.is_set())
		
		  {
		
		    return OpcUa_BadOutOfMemory;
		
		  }
		
		
		
		  result = retain->CopyFrom(*source.Retain());
		
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
		
		
		
		enabledState.reset();
		
		if(source.enabledState.is_set())
		
		{
		
		  result = source.enabledState->CopyTo(enabledState);
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		quality.reset();
		
		if(source.quality.is_set())
		
		{
		
		  result = source.quality->CopyTo(quality);
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		lastSeverity.reset();
		
		if(source.lastSeverity.is_set())
		
		{
		
		  result = source.lastSeverity->CopyTo(lastSeverity);
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		comment.reset();
		
		if(source.comment.is_set())
		
		{
		
		  result = source.comment->CopyTo(comment);
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		
		result = BaseEventTypeData_t::CopyFrom(source);
		return result;
	}
	
} // namespace

#endif //((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

