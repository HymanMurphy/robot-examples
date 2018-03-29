

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



#include "base_event_type_data_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "opcua_node_id_numeric_t.h"
#include "opcua_server_state_t.h"
namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(BaseEventTypeData_t, IAttributeAccess_t);

BaseEventTypeData_t::BaseEventTypeData_t()
{
}

BaseEventTypeData_t::~BaseEventTypeData_t()
{
}

bool BaseEventTypeData_t::IsOfType(const uint32_t typeId, uint16_t namespaceindex) const
{
	if(namespaceindex != 0) return false;
	return typeId == 2041;
}

Status_t BaseEventTypeData_t::Initialise()
{
	Status_t rtnStatus = OpcUa_Good;
	browseName = new SafeRefCount_t<String_t>();
	UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(browseName);
	rtnStatus = browseName->CopyFrom("BaseEventType");
	UASDK_RETURN_STATUS_ONLY_IF_BAD(rtnStatus.Value());
	
	
	
	attrNodeId.reset();
	
	attrBrowseName.reset();
	
	attrNodeClass.reset();
	
	attrDisplayName.reset();
	
	attrDescription.reset();
	
	attrDataType.reset();
	
	
	eventId.reset();
	
	eventType.reset();
	
	sourceNode.reset();
	
	sourceName.reset();
	
	time.reset();
	
	receiveTime.reset();
	
	localTime_Offset.reset();
	
	localTime_DaylightSavingInOffset.reset();
	
	localTime.reset();
	
	message.reset();
	
	severity.reset();
	
	
	return rtnStatus;
}

uint32_t BaseEventTypeData_t::TypeId(uint16_t& namespaceIndex) const
{
	namespaceIndex = 0;
	return BaseEventTypeData_t::TYPE_ID;
}

IntrusivePtr_t<BaseDataType_t> BaseEventTypeData_t::AttributeValue(const uint32_t& typeId, const ArrayUA_t<QualifiedName_t>&browsePath, const uint32_t &_attributeId, const String_t& _indexRange, const ArrayUA_t<String_t> & locales,  Status_t &result)
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

	
	
	
	
	
	if(browsePath.Count() == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_NODEID)
	
	{
	
		result = OpcUa_Good;
	
	    return attrNodeId;
	
	}
	
	        
	
	        
	
	if(browsePath.Count() == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_BROWSENAME)
	
	{
	
		result = OpcUa_Good;
	
	    return attrBrowseName;
	
	}
	
	        
	
	if(browsePath.Count() == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_DISPLAYNAME)
	
	{
	
		result = OpcUa_Good;
	
		IntrusivePtr_t<LocalizedText_t> localizedText;
	
		localizedText = new SafeRefCount_t<LocalizedText_t>();
	
	    if (localizedText.is_set())
	
		{
	
			if (attrDisplayName.is_set())
	
			{
	
				localizedText->CopyFrom(*attrDisplayName->GetLocalizedText(locales, result));
	
			}
	
		    return localizedText;
	
		}
	
		else
	
		{
	
			result = OpcUa_BadOutOfMemory;
	
	        return emptyResult;
	
		}
	
	}
	
	        
	
	if(browsePath.Count() == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_DESCRIPTION)
	
	{
	
		            
	
		result = OpcUa_Good;
	
		IntrusivePtr_t<LocalizedText_t> localizedText;
	
		localizedText = new SafeRefCount_t<LocalizedText_t>();
	
	    if (localizedText.is_set())
	
		{
	
			if (attrDescription.is_set())
	
			{
	
				localizedText->CopyFrom(*attrDescription->GetLocalizedText(locales, result));
	
	            return localizedText;
	
			}
	
		}
	
		else
	
		{
	
			result = OpcUa_BadOutOfMemory;
	
	        return emptyResult;
	
		}
	
	}
	
	        
	
	if(browsePath.Count() == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_DATATYPE)
	
	{
	
		result = OpcUa_Good;
	
	    return attrDataType;
	
	}
	
	
	/* Start class specific attributes */
	if(UASDK_strcmp(nameStr, "EventId") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
		result = OpcUa_Good;
	
		return eventId;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "EventType") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
		result = OpcUa_Good;
	
		return eventType;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "SourceNode") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
		result = OpcUa_Good;
	
		return sourceNode;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "SourceName") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
		result = OpcUa_Good;
	
		return sourceName;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "Time") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
		result = OpcUa_Good;
	
		return time;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "ReceiveTime") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
		result = OpcUa_Good;
	
		return receiveTime;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "LocalTime.Offset") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 1
	
	{
	
		result = OpcUa_Good;
	
		return localTime_Offset;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "LocalTime.DaylightSavingInOffset") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 1
	
	{
	
		result = OpcUa_Good;
	
		return localTime_DaylightSavingInOffset;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "LocalTime") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
		result = OpcUa_Good;
	
		return localTime;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "Message") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
		result = OpcUa_Good;
	
		return message;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "Severity") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
		result = OpcUa_Good;
	
		return severity;
	
	};
	
	
	
	
	/* end class specific attributes */
	
		return emptyResult;
	}
	
	IntrusivePtr_t<const BaseDataType_t> BaseEventTypeData_t::AttributeValue(const uint32_t& typeId, const ArrayUA_t<QualifiedName_t>&browsePath, const uint32_t &_attributeId, const String_t& _indexRange, const ArrayUA_t<String_t> & locales, Status_t &result) const
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

		
		
		
		
		
		if(browsePath.Count() == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_NODEID)
		
		{
		
			result = OpcUa_Good;
		
		    return attrNodeId;
		
		}
		
		        
		
		        
		
		if(browsePath.Count() == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_BROWSENAME)
		
		{
		
			result = OpcUa_Good;
		
		    return attrBrowseName;
		
		}
		
		        
		
		if(browsePath.Count() == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_DISPLAYNAME)
		
		{
		
			result = OpcUa_Good;
		
			IntrusivePtr_t<LocalizedText_t> localizedText;
		
			localizedText = new SafeRefCount_t<LocalizedText_t>();
		
		    if (localizedText.is_set())
		
			{
		
				if (attrDisplayName.is_set())
		
				{
		
					localizedText->CopyFrom(*attrDisplayName->GetLocalizedText(locales, result));
		
				}
		
			    return localizedText;
		
			}
		
			else
		
			{
		
				result = OpcUa_BadOutOfMemory;
		
		        return emptyResult;
		
			}
		
		}
		
		        
		
		if(browsePath.Count() == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_DESCRIPTION)
		
		{
		
			            
		
			result = OpcUa_Good;
		
			IntrusivePtr_t<LocalizedText_t> localizedText;
		
			localizedText = new SafeRefCount_t<LocalizedText_t>();
		
		    if (localizedText.is_set())
		
			{
		
				if (attrDescription.is_set())
		
				{
		
					localizedText->CopyFrom(*attrDescription->GetLocalizedText(locales, result));
		
		            return localizedText;
		
				}
		
			}
		
			else
		
			{
		
				result = OpcUa_BadOutOfMemory;
		
		        return emptyResult;
		
			}
		
		}
		
		        
		
		if(browsePath.Count() == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_DATATYPE)
		
		{
		
			result = OpcUa_Good;
		
		    return attrDataType;
		
		}
		
		
		/* Start class specific attributes */
		if(UASDK_strcmp(nameStr, "EventId") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
			result = OpcUa_Good;
		
			return eventId;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "EventType") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
			result = OpcUa_Good;
		
			return eventType;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "SourceNode") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
			result = OpcUa_Good;
		
			return sourceNode;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "SourceName") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
			result = OpcUa_Good;
		
			return sourceName;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "Time") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
			result = OpcUa_Good;
		
			return time;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "ReceiveTime") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
			result = OpcUa_Good;
		
			return receiveTime;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "LocalTime.Offset") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 1
		
		{
		
			result = OpcUa_Good;
		
			return localTime_Offset;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "LocalTime.DaylightSavingInOffset") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 1
		
		{
		
			result = OpcUa_Good;
		
			return localTime_DaylightSavingInOffset;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "LocalTime") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
			result = OpcUa_Good;
		
			return localTime;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "Message") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
			result = OpcUa_Good;
		
			return message;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "Severity") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
			result = OpcUa_Good;
		
			return severity;
		
		};
		
		
		
		
		/* end class specific attributes */
		
		return emptyResult;
	}
	
	Status_t BaseEventTypeData_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
	{
		return CopyToDestination(*this, destination);
	}
	
	Status_t BaseEventTypeData_t::CopyFrom(const BaseDataType_t& source)
	{
		IntrusivePtr_t<const BaseEventTypeData_t> ptr = RuntimeCast<const BaseEventTypeData_t*>(source);
		if (!ptr.is_set())
		{
			return OpcUa_BadTypeMismatch;
		}
		
		return CopyFrom(*ptr);
	}
	
	Status_t BaseEventTypeData_t::CopyFrom(const BaseEventTypeData_t& source)
	{
		Status_t result = OpcUa_Good;
		
		
		attrNodeId.reset();
		
		if(source.attrNodeId.is_set())
		
		{
		
		    result = source.attrNodeId->CopyToNodeId(attrNodeId);
		
		    if(result.IsBad())
		
		    {
		
		        return result;
		
		    }
		
		}
		
		
		
				
		
		attrBrowseName.reset();
		
		if(source.attrBrowseName.is_set())
		
		{
		
		  attrBrowseName = new SafeRefCount_t<QualifiedName_t>();
		
		  if (!attrBrowseName.is_set())
		
		  {
		
		    return OpcUa_BadOutOfMemory;
		
		  }
		
		  result = attrBrowseName->CopyFrom(*source.attrBrowseName);
		
				
		
		  if(result.IsBad())	
		
		  {
		
			return result;
		
		  }	
		
		}
		
		
		
		attrDisplayName.reset();
		
		if(source.attrDisplayName.is_set())
		
		{
		
		    result = source.attrDisplayName->CopyTo(attrDisplayName);
		
		    if(result.IsBad())
		
		    {
		
		        return result;
		
		    }
		
		}
		
		attrDescription.reset();
		
		if(source.attrDescription.is_set())
		
		{
		
		    result = source.attrDescription->CopyTo(attrDescription);
		
		    if(result.IsBad())
		
		    {
		
		        return result;
		
		    }
		
		}
		
		
		
		attrDataType.reset();
		
		if(source.attrDataType.is_set())
		
		{
		
		    result = source.attrDataType->CopyToNodeId(attrDataType);
		
		    if(result.IsBad())
		
		    {
		
		        return result;
		
		    }
		
		}
		
		
		
		
		eventId.reset();
		
		if(source.eventId.is_set())
		
		{
		
		  eventId = new SafeRefCount_t<ByteString_t>();
		
		  if(!eventId.is_set())
		
		  {
		
		    return OpcUa_BadOutOfMemory;
		
		  }
		
		
		
		  result = eventId->CopyFrom(*source.EventId());
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		eventType.reset();
		
		if(source.eventType.is_set())
		
		{
		
		  result = source.eventType->CopyToNodeId(eventType);
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		sourceNode.reset();
		
		if(source.sourceNode.is_set())
		
		{
		
		  result = source.sourceNode->CopyToNodeId(sourceNode);
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		sourceName.reset();
		
		if(source.sourceName.is_set())
		
		{
		
		  sourceName = new SafeRefCount_t<String_t>();
		
		  if(!sourceName.is_set())
		
		  {
		
		    return OpcUa_BadOutOfMemory;
		
		  }
		
		
		
		  result = sourceName->CopyFrom(*source.SourceName());
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		time.reset();
		
		if(source.time.is_set())
		
		{
		
		  time = new SafeRefCount_t<UtcTime_t>();
		
		  if(!time.is_set())
		
		  {
		
		    return OpcUa_BadOutOfMemory;
		
		  }
		
		
		
		  result = time->CopyFrom(*source.Time());
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		receiveTime.reset();
		
		if(source.receiveTime.is_set())
		
		{
		
		  receiveTime = new SafeRefCount_t<UtcTime_t>();
		
		  if(!receiveTime.is_set())
		
		  {
		
		    return OpcUa_BadOutOfMemory;
		
		  }
		
		
		
		  result = receiveTime->CopyFrom(*source.ReceiveTime());
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		if(source.localTime_Offset.is_set())
		
		{
		
		localTime_Offset.reset();
		
		  localTime_Offset = new SafeRefCount_t<Int16_t>();
		
		  if(!localTime_Offset.is_set())
		
		  {
		
		    return OpcUa_BadOutOfMemory;
		
		  }
		
		
		
		  result = localTime_Offset->CopyFrom(*source.LocalTime_Offset());
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		if(source.localTime_DaylightSavingInOffset.is_set())
		
		{
		
		localTime_DaylightSavingInOffset.reset();
		
		  localTime_DaylightSavingInOffset = new SafeRefCount_t<Boolean_t>();
		
		  if(!localTime_DaylightSavingInOffset.is_set())
		
		  {
		
		    return OpcUa_BadOutOfMemory;
		
		  }
		
		
		
		  result = localTime_DaylightSavingInOffset->CopyFrom(*source.LocalTime_DaylightSavingInOffset());
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		localTime.reset();
		
		if(source.localTime.is_set())
		
		{
		
		  localTime = new SafeRefCount_t<TimeZoneDataType_t>();
		
		  if(!localTime.is_set())
		
		  {
		
		    return OpcUa_BadOutOfMemory;
		
		  }
		
		
		
		  result = localTime->CopyFrom(*source.LocalTime());
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		message.reset();
		
		if(source.message.is_set())
		
		{
		
		  message = new SafeRefCount_t<LocalizedText_t>();
		
		  if(!message.is_set())
		
		  {
		
		    return OpcUa_BadOutOfMemory;
		
		  }
		
		
		
		  result = message->CopyFrom(*source.Message());
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		severity.reset();
		
		if(source.severity.is_set())
		
		{
		
		  severity = new SafeRefCount_t<UInt16_t>();
		
		  if(!severity.is_set())
		
		  {
		
		    return OpcUa_BadOutOfMemory;
		
		  }
		
		
		
		  result = severity->CopyFrom(*source.Severity());
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		
		return result;
	}
	
} // namespace

#endif //(UASDK_INCLUDE_EVENTS > 0)

