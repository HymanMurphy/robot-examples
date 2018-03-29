

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



#include "audit_activate_session_event_type_data_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "opcua_node_id_numeric_t.h"
#include "opcua_server_state_t.h"
namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(AuditActivateSessionEventTypeData_t, AuditSessionEventTypeData_t);

AuditActivateSessionEventTypeData_t::AuditActivateSessionEventTypeData_t()
{
}

AuditActivateSessionEventTypeData_t::~AuditActivateSessionEventTypeData_t()
{
}

bool AuditActivateSessionEventTypeData_t::IsOfType(const uint32_t typeId, uint16_t namespaceindex) const
{
	if(namespaceindex != 0) return false;
	return typeId == 2075 || AuditSessionEventTypeData_t::IsOfType(typeId, namespaceindex);
}

Status_t AuditActivateSessionEventTypeData_t::Initialise()
{
	Status_t rtnStatus = OpcUa_Good;
	browseName = new SafeRefCount_t<String_t>();
	UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(browseName);
	rtnStatus = browseName->CopyFrom("AuditActivateSessionEventType");
	UASDK_RETURN_STATUS_ONLY_IF_BAD(rtnStatus.Value());
	
	clientSoftwareCertificates_CertificateData.reset();
	
	clientSoftwareCertificates_Signature.reset();
	
	clientSoftwareCertificates.Initialise(0);
	
	userIdentityToken_PolicyId.reset();
	
	userIdentityToken.reset();
	
	secureChannelId.reset();
	
	
	return AuditSessionEventTypeData_t::Initialise();
}

uint32_t AuditActivateSessionEventTypeData_t::TypeId(uint16_t& namespaceIndex) const
{
	namespaceIndex = 0;
	return AuditActivateSessionEventTypeData_t::TYPE_ID;
}

IntrusivePtr_t<BaseDataType_t> AuditActivateSessionEventTypeData_t::AttributeValue(const uint32_t& typeId, const ArrayUA_t<QualifiedName_t>&browsePath, const uint32_t &_attributeId, const String_t& _indexRange, const ArrayUA_t<String_t> & locales,  Status_t &result)
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
	if(UASDK_strcmp(nameStr, "ClientSoftwareCertificates.CertificateData") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 1
	
	{
	
		result = OpcUa_Good;
	
		return clientSoftwareCertificates_CertificateData;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "ClientSoftwareCertificates.Signature") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 1
	
	{
	
		result = OpcUa_Good;
	
		return clientSoftwareCertificates_Signature;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "ClientSoftwareCertificates") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE)  //From  5
	
	{
	
		if(_indexRange.IsNull() == false || _indexRange.Length() == 0)
	
		{
	
			result = OpcUa_Good;
	
			return clientSoftwareCertificates;
	
		}
	
		else
	
		{
	
			Array_t<IndexRange_t> subRanges;
	
			result = Utilities_t::ValidateIndexRange(_indexRange, subRanges);
	
			if(result == OpcUa_Good)
	
			{
	
				IntrusivePtr_t<BaseDataType_t> subArray;
	
				result = clientSoftwareCertificates.WriteSubsetTo(subRanges, subArray);
	
				return subArray;
	
			}
	
		}
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "UserIdentityToken.PolicyId") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 1
	
	{
	
		result = OpcUa_Good;
	
		return userIdentityToken_PolicyId;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "UserIdentityToken") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
		result = OpcUa_Good;
	
		return userIdentityToken;
	
	};
	
	
	
	if(UASDK_strcmp(nameStr, "SecureChannelId") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
	
	{
	
		result = OpcUa_Good;
	
		return secureChannelId;
	
	};
	
	
	
	
	/* end class specific attributes */
	
		return AuditSessionEventTypeData_t::AttributeValue(typeId, browsePath, _attributeId, _indexRange, locales, result); 
	}
	
	IntrusivePtr_t<const BaseDataType_t> AuditActivateSessionEventTypeData_t::AttributeValue(const uint32_t& typeId, const ArrayUA_t<QualifiedName_t>&browsePath, const uint32_t &_attributeId, const String_t& _indexRange, const ArrayUA_t<String_t> & locales, Status_t &result) const
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
		if(UASDK_strcmp(nameStr, "ClientSoftwareCertificates.CertificateData") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 1
		
		{
		
			result = OpcUa_Good;
		
			return clientSoftwareCertificates_CertificateData;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "ClientSoftwareCertificates.Signature") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 1
		
		{
		
			result = OpcUa_Good;
		
			return clientSoftwareCertificates_Signature;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "ClientSoftwareCertificates") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE)  //From  5
		
		{
		
			if(_indexRange.IsNull() == false || _indexRange.Length() == 0)
		
			{
		
				result = OpcUa_Good;
		
				return clientSoftwareCertificates;
		
			}
		
			else
		
			{
		
				Array_t<IndexRange_t> subRanges;
		
				result = Utilities_t::ValidateIndexRange(_indexRange, subRanges);
		
				if(result == OpcUa_Good)
		
				{
		
					IntrusivePtr_t<BaseDataType_t> subArray;
		
					result = clientSoftwareCertificates.WriteSubsetTo(subRanges, subArray);
		
					return subArray;
		
				}
		
			}
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "UserIdentityToken.PolicyId") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 1
		
		{
		
			result = OpcUa_Good;
		
			return userIdentityToken_PolicyId;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "UserIdentityToken") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
			result = OpcUa_Good;
		
			return userIdentityToken;
		
		};
		
		
		
		if(UASDK_strcmp(nameStr, "SecureChannelId") == 0 && _attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE) //From 4
		
		{
		
			result = OpcUa_Good;
		
			return secureChannelId;
		
		};
		
		
		
		
		/* end class specific attributes */
		
		return AuditSessionEventTypeData_t::AttributeValue(typeId, browsePath, _attributeId, _indexRange, locales, result); 
	}
	
	Status_t AuditActivateSessionEventTypeData_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
	{
		return CopyToDestination(*this, destination);
	}
	
	Status_t AuditActivateSessionEventTypeData_t::CopyFrom(const BaseDataType_t& source)
	{
		IntrusivePtr_t<const AuditActivateSessionEventTypeData_t> ptr = RuntimeCast<const AuditActivateSessionEventTypeData_t*>(source);
		if (!ptr.is_set())
		{
			return OpcUa_BadTypeMismatch;
		}
		
		return CopyFrom(*ptr);
	}
	
	Status_t AuditActivateSessionEventTypeData_t::CopyFrom(const AuditActivateSessionEventTypeData_t& source)
	{
		Status_t result = OpcUa_Good;
		if(source.clientSoftwareCertificates_CertificateData.is_set())
		
		{
		
		clientSoftwareCertificates_CertificateData.reset();
		
		  clientSoftwareCertificates_CertificateData = new SafeRefCount_t<ByteString_t>();
		
		  if(!clientSoftwareCertificates_CertificateData.is_set())
		
		  {
		
		    return OpcUa_BadOutOfMemory;
		
		  }
		
		
		
		  result = clientSoftwareCertificates_CertificateData->CopyFrom(*source.ClientSoftwareCertificates_CertificateData());
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		if(source.clientSoftwareCertificates_Signature.is_set())
		
		{
		
		clientSoftwareCertificates_Signature.reset();
		
		  clientSoftwareCertificates_Signature = new SafeRefCount_t<ByteString_t>();
		
		  if(!clientSoftwareCertificates_Signature.is_set())
		
		  {
		
		    return OpcUa_BadOutOfMemory;
		
		  }
		
		
		
		  result = clientSoftwareCertificates_Signature->CopyFrom(*source.ClientSoftwareCertificates_Signature());
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		clientSoftwareCertificates.Initialise(0);
		
		result = clientSoftwareCertificates.CopyFrom(source.clientSoftwareCertificates);
		
		if(result.IsBad())
		
		{
		
		  return result;
		
		}
		
		
		
		if(source.userIdentityToken_PolicyId.is_set())
		
		{
		
		userIdentityToken_PolicyId.reset();
		
		  userIdentityToken_PolicyId = new SafeRefCount_t<String_t>();
		
		  if(!userIdentityToken_PolicyId.is_set())
		
		  {
		
		    return OpcUa_BadOutOfMemory;
		
		  }
		
		
		
		  result = userIdentityToken_PolicyId->CopyFrom(*source.UserIdentityToken_PolicyId());
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
		userIdentityToken.reset();
		
		if(source.userIdentityToken.is_set())
		
		{
		
		  userIdentityToken = new SafeRefCount_t<UserIdentityToken_t>();
		
		  if(!userIdentityToken.is_set())
		
		  {
		
		    return OpcUa_BadOutOfMemory;
		
		  }
		
		
		
		  result = userIdentityToken->CopyFrom(*source.UserIdentityToken());
		
		  if(result.IsBad())
		
		  {
		
		    return result;
		
		  }
		
		}
		
		
		
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
		
		
		
		
		result = AuditSessionEventTypeData_t::CopyFrom(source);
		return result;
	}
	
} // namespace

#endif //(UASDK_INCLUDE_EVENTS > 0)

