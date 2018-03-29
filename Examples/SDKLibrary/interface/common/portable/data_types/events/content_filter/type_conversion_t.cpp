/* -----------------------------------------------------------------------------------------------------------------
                                        COPYRIGHT (c) 2009 - 2017
                                         HONEYWELL INC.,
                                        ALL RIGHTS RESERVED

            This software is a copyrighted work and/or information protected as a trade
            secret. Legal rights of Honeywell Inc. in this software are distinct from
            ownership of any medium in which the software is embodied. Copyright or trade
            secret notices included must be reproduced in any copies authorized by
            Honeywell Inc. The information in this software is subject to change without
            notice and should not be considered as a commitment by Honeywell Inc.
----------------------------------------------------------------------------------------------------------------- */

#include "type_conversion_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "opcua_boolean_t.h"
#include "opcua_byte_t.h"
#include "opcua_double_t.h"
#include "opcua_float_t.h"
#include "opcua_int16_t.h"
#include "opcua_int32_t.h"
#include "opcua_int64_t.h"
#include "opcua_sbyte_t.h"
#include "opcua_uint16_t.h"
#include "opcua_uint32_t.h"
#include "opcua_uint64_t.h"
#include "opcua_bytestring_t.h"
#include "opcua_string_t.h"
#include "opcua_date_time_t.h"
#include "opcua_guid_t.h"
#include "opcua_status_code_t.h"
#include "opcua_node_id_t.h"
#include "opcua_expanded_node_id_t.h"
#include "opcua_localized_text_t.h"
#include "opcua_qualified_name_t.h"
#include "opcua_xml_element_t.h"
#include "safe_ref_count_t.h"
#include "opcua_node_id_string_t.h"
#include "opcua_node_id_guid_t.h"
#include "opcua_node_id_numeric_t.h"
#include "opcua_node_id_opaque_t.h"


namespace uasdk
{
  
TypeConversion_t::TypeConversion_t()
{
}

TypeConversion_t::~TypeConversion_t()
{
}

int64_t TypeConversion_t::Ifloor(float x)
{
	if (x >= 0)
	{
		return static_cast<int64_t>(x);
	}
	else
	{
		int64_t y = static_cast<int64_t>(x);
		return ((float)y == x) ? y : y - 1;
	}
}

Status_t TypeConversion_t::ConvertGuidToString(IntrusivePtr_t<Guid_t>& guidPtr, IntrusivePtr_t<String_t>& sourceValue)
{
	int i;
	int32_t len;
	uint32_t data1;
	uint16_t data2;
	uint16_t data3;
	uint8_t  data4[8];
	uint16_t data5[4];
	uint32_t pos = 0;
	char cstr[37];

	if (!guidPtr.is_set() || !sourceValue.is_set())
	{
		return OpcUa_BadFilterOperandInvalid;
	}

	uint32_t *pData1 = reinterpret_cast<uint32_t *>(guidPtr->Value());
	data1 = *pData1;
	uint16_t *pData2 = reinterpret_cast<uint16_t *>(guidPtr->Value() + 4);
	data2 = *pData2;
	uint16_t *pData3 = reinterpret_cast<uint16_t *>(guidPtr->Value() + 6);
	data3 = *pData3;

	uint8_t *pData4[8];
	for (i = 0; i < 8; i++)
	{
		pData4[i] = static_cast<uint8_t *>(guidPtr->Value() + 8 + i);
		data4[i] = *pData4[i];
	}

	for (i = 0; i < 4; i++)
	{
		data5[i] = (((data4[2 * i] << 8) & 0xff00) | (data4[2 * i + 1] & 0xff));
	}

	sourceValue->Payload().Initialise(36);

	len = UASDK_unsigned_integer_to_hex_string(data1, 8, cstr+pos, 10);
	if (len < 0)
	{
		return OpcUa_BadFilterOperandInvalid;
	}

	pos += len;
	cstr[pos++] = '-';

	len = UASDK_unsigned_integer_to_hex_string(data2, 4, cstr+pos, 6);
	if (len < 0)
	{
		return OpcUa_BadFilterOperandInvalid;
	}

	pos += len;
	cstr[pos++] = '-';

	len = UASDK_unsigned_integer_to_hex_string(data3, 4, cstr+pos, 6);
	if (len < 0)
	{
		return OpcUa_BadFilterOperandInvalid;
	}

	pos += len;
	cstr[pos++] = '-';

	len = UASDK_unsigned_integer_to_hex_string(data5[0], 4, cstr+pos, 6);
	if (len < 0)
	{
		return OpcUa_BadFilterOperandInvalid;
	}

	pos += len;
	cstr[pos++] = '-';

	for (i = 1; i < 4; i++)
	{
		len = UASDK_unsigned_integer_to_hex_string(data5[i], 4, cstr+pos, 6);
		if (len < 0)
		{
			return OpcUa_BadFilterOperandInvalid;
		}

		pos += len;
	}

	UASDK_memcpy(sourceValue->Payload().Data(), cstr, pos);
	return OpcUa_Good;
}

Status_t TypeConversion_t::ConvertStringToGuid(IntrusivePtr_t<String_t>& sourceValue, IntrusivePtr_t<Guid_t>& guidPtr)
{
	int i;
	int32_t len;
	uint32_t data1;
	uint16_t data2;
	uint16_t data3;
	uint16_t data5[4];
	uint64_t u64;
	char cstr[37];
	char csubstr[5];
	char *end;

	if (!guidPtr.is_set() || !sourceValue.is_set())
	{
		return OpcUa_BadFilterOperandInvalid;
	}

	len = sourceValue->Payload().Length();
	if (len != 36)
	{
		return OpcUa_BadFilterOperandInvalid;
	}

	//validate string first
	for (int32_t i = 0; i < len; i++)
	{
		if ((8 == i) || (13 == i) || (18 == i) || (23 == i))
		{
			if (sourceValue->Payload().Data()[i] != '-')
			{
				return OpcUa_BadFilterOperandInvalid;
			}
		}
		else
		{
			if (!((sourceValue->Payload().Data()[i] >= '0' && sourceValue->Payload().Data()[i] <= '9')
					|| (sourceValue->Payload().Data()[i] >= 'A' && sourceValue->Payload().Data()[i] <= 'F')
					|| (sourceValue->Payload().Data()[i] >= 'a' && sourceValue->Payload().Data()[i] <= 'f')))
			{
				return OpcUa_BadFilterOperandInvalid;
			}
		}
	}

	UASDK_memcpy(cstr, sourceValue->Payload().Data(), len);
	cstr[36] = '\0';

	cstr[8] = '\0';
	end = 0;
	u64 =  UASDK_strtoull(cstr, &end, 16);
	if (  (end == cstr)
		|| (*end != '\0') )
	{
	  return OpcUa_BadFilterOperandInvalid;
	}

	if (u64 > UINT32_MAX)
	{
	  return OpcUa_BadFilterOperandInvalid;
	}

	data1 = static_cast<uint32_t>(u64);
	UASDK_memcpy(guidPtr->Value(), &data1, 4);

	cstr[13] = '\0';
	end = 0;
	u64 =  UASDK_strtoull(cstr+9, &end, 16);
	if (  (end == cstr+9)
			|| (*end != '\0') )
	{
	  return OpcUa_BadFilterOperandInvalid;
	}

	if (u64 > UINT16_MAX)
	{
	  return OpcUa_BadFilterOperandInvalid;
	}

	data2 = static_cast<uint16_t>(u64);
	UASDK_memcpy(guidPtr->Value()+4, &data2, 2);

	cstr[18] = '\0';
	end = 0;
	u64 =  UASDK_strtoull(cstr+14, &end, 16);
	if (  (end == cstr+14)
			|| (*end != '\0') )
	{
	  return OpcUa_BadFilterOperandInvalid;
	}

	if (u64 > UINT16_MAX)
	{
	  return OpcUa_BadFilterOperandInvalid;
	}

	data3 = static_cast<uint16_t>(u64);
	UASDK_memcpy(guidPtr->Value()+6, &data3, 2);

	cstr[23] = '\0';
	end = 0;
	u64 =  UASDK_strtoull(cstr+19, &end, 16);
	if (  (end == cstr+19)
			|| (*end != '\0') )
	{
	  return OpcUa_BadFilterOperandInvalid;
	}

	if (u64 > UINT16_MAX)
	{
	  return OpcUa_BadFilterOperandInvalid;
	}

	data5[0] = static_cast<uint16_t>(u64);
	data5[0] = ((data5[0] & 0xff) << 8) | ((data5[0] >> 8) & 0xff);
	UASDK_memcpy(guidPtr->Value()+8, &data5[0], 2);

	for (i = 1; i<4; i++)
	{
		UASDK_memcpy(csubstr, cstr+20+i*4, 4);
		csubstr[4] = '\0';

		end = 0;
		u64 =  UASDK_strtoull(csubstr, &end, 16);
		if (  (end == csubstr)
				|| (*end != '\0') )
		{
			return OpcUa_BadFilterOperandInvalid;
		}

		if (u64 > UINT16_MAX)
		{
			return OpcUa_BadFilterOperandInvalid;
		}

		data5[i] = static_cast<uint16_t>(u64);
		data5[i] = ((data5[i] & 0xff) << 8) | ((data5[i] >> 8) & 0xff);
		UASDK_memcpy(guidPtr->Value()+8+i*2, &data5[i], 2);
	}

	return OpcUa_Good;
}

int32_t TypeConversion_t::FindFirstSubstr(IntrusivePtr_t<String_t>& strPtr, const char *substrPtr, int32_t startPos)
{
	int32_t i, j, k;
	int32_t strLen;
	int32_t substrLen;
	char *ptr = (char *)substrPtr;
	bool found = false;

	if (!strPtr.is_set() || NULL == substrPtr)
	{
		return -1;
	}

	strLen = (int32_t)strPtr->Payload().Length();

	substrLen = 0;
	while(*ptr++ != '\0')
	{
		substrLen++;
	}

	if ( (substrLen > strLen) || (startPos > (strLen-substrLen)))
	{
		return -1;
	}

	for (i = startPos; i <= (strLen-substrLen); i++)
	{
		k = 0;
		for (j = 0; j<substrLen; j++)
		{
			if (strPtr->Payload().Data()[i+j] == substrPtr[j])
			{
				k++;
			}
			else
			{
				break;
			}
		}

		if (k == substrLen)
		{
			found = true;
			break;
		}
	}

	if (found)
	{
		return i;
	}
	else
	{
		return -1;
	}
}

Status_t TypeConversion_t::ConvertNodeIdToString(IntrusivePtr_t<NodeId_t>& nodeidPtr, IntrusivePtr_t<String_t>& sourceValue)
{
	uint16_t namespaceIndex = 0;
	uint32_t pos = 0;
	int32_t len;
	uint32_t precision = 1;
	//ns=65536;g=36+1
	//ns=65536;i=10+1
	char cstr[48];

	if (!nodeidPtr.is_set())
	{
		return OpcUa_BadFilterOperandInvalid;
	}

	IntrusivePtr_t<String_t> strPtr = new SafeRefCount_t<String_t>();
	if (!strPtr.is_set())
	{
		return OpcUa_BadOutOfMemory;
	}

	//transfer value
	namespaceIndex = nodeidPtr->NamespaceIndex().Value();
	if (namespaceIndex != 0)
	{
		cstr[pos++] = 'n';
		cstr[pos++] = 's';
		cstr[pos++] = '=';

		len = UASDK_unsigned_integer_to_string(namespaceIndex, precision, cstr+pos, 5);
		if (len < 0)
		{
			return OpcUa_BadFilterOperandInvalid;
		}

		pos += len;
		cstr[pos++] = ';';
	}

	switch (nodeidPtr->NodeIdIdentiferType())
	{
	case NodeId_t::NODEID_IDENTIFIER_NUMERIC:
		{
			IntrusivePtr_t<NodeIdNumeric_t> nnodeidPtr = RuntimeCast<NodeIdNumeric_t*>(*nodeidPtr);
			if (!nnodeidPtr.is_set())
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			cstr[pos++] = 'i';
			cstr[pos++] = '=';

			len = UASDK_unsigned_integer_to_string(nnodeidPtr->Identifer().Value(), precision, cstr+pos, 10);
			if (len < 0)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			pos += len;

			strPtr->Payload().Initialise(pos);
			UASDK_memcpy(strPtr->Payload().Data(), cstr, pos);
		}
		break;

	case NodeId_t::NODEID_IDENTIFIER_STRING:
		{
			IntrusivePtr_t<NodeIdString_t> snodeidPtr = RuntimeCast<NodeIdString_t*>(*nodeidPtr);
			if (!snodeidPtr.is_set())
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			len  = snodeidPtr->Identifer().Payload().Length();
			if (len < 1)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			cstr[pos++] = 's';
			cstr[pos++] = '=';

			strPtr->Payload().Initialise(pos+len);
			UASDK_memcpy(strPtr->Payload().Data(), cstr, pos);
			UASDK_memcpy(strPtr->Payload().Data()+pos, snodeidPtr->Identifer().Payload().Data(), len);
		}
		break;

	case NodeId_t::NODEID_IDENTIFIER_GUID:
		{
			IntrusivePtr_t<NodeIdGuid_t> gnodeidPtr = RuntimeCast<NodeIdGuid_t*>(*nodeidPtr);
			if (!gnodeidPtr.is_set())
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//prepare to convert a Guid to a sub-String first
			IntrusivePtr_t<String_t> gstrPtr = new SafeRefCount_t<String_t>();
			if (!gstrPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			IntrusivePtr_t<Guid_t> guidPtr = new SafeRefCount_t<Guid_t>();
			if (!guidPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			Status_t status = guidPtr->CopyFrom(gnodeidPtr->Identifer());
			if (status.IsBad())
			{
				return status;
			}

			status = ConvertGuidToString(guidPtr, gstrPtr);
			if (status.IsBad())
			{
				return status;
			}

			len = gstrPtr->Payload().Length();
			if (len < 1)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			cstr[pos++] = 'g';
			cstr[pos++] = '=';

			strPtr->Payload().Initialise(pos+len);
			UASDK_memcpy(strPtr->Payload().Data(), cstr, pos);
			UASDK_memcpy(strPtr->Payload().Data()+pos, gstrPtr->Payload().Data(), len);
		}
		break;

	case NodeId_t::NODEID_IDENTIFIER_OPAQUE:
		{
			IntrusivePtr_t<NodeIdOpaque_t> onodeidPtr = RuntimeCast<NodeIdOpaque_t*>(*nodeidPtr);
			if (!onodeidPtr.is_set())
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			len = onodeidPtr->Identifer().Length();
			if (len < 1)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			cstr[pos++] = 'b';
			cstr[pos++] = '=';

			strPtr->Payload().Initialise(pos+len);
			UASDK_memcpy(strPtr->Payload().Data(), cstr, pos);
			UASDK_memcpy(strPtr->Payload().Data()+pos, onodeidPtr->Identifer().Data(), len);
		}
		break;

	default:
		return OpcUa_BadFilterOperandInvalid;
		break;
	}

	sourceValue = strPtr;
	return OpcUa_Good;
}

Status_t TypeConversion_t::ConvertStringToNodeId(IntrusivePtr_t<String_t>& sourceValue, IntrusivePtr_t<NodeId_t>& nodeidPtr, bool uriPresent)
{
  uint16_t namespaceIndex = 0;
  int32_t pos, prev_pos;
  int32_t Len;
  char *end;

  if (!sourceValue.is_set())
  {
  	return OpcUa_BadFilterOperandInvalid;
  }

  Len = sourceValue->Payload().Length();
  if (Len < 1)
  {
  	return OpcUa_BadFilterOperandInvalid;
  }

  prev_pos = 0;
  if (!uriPresent)
  {
	  pos = FindFirstSubstr(sourceValue, "ns=");
	  if (pos >= 0)
	  {
	    prev_pos = pos;
	    pos = FindFirstSubstr(sourceValue, ";", prev_pos);
	    if (pos < 0)
	    {
	      return OpcUa_BadFilterOperandInvalid;
	    }

	    if ( (pos - prev_pos) <= 3 )
	    {
	      return OpcUa_BadFilterOperandInvalid;
	    }

	    char u16[6];
	    if (pos-(prev_pos+3) > 5)
	    {
	      return OpcUa_BadFilterOperandInvalid;
	    }

	    UASDK_memcpy(u16, sourceValue->Payload().Data()+prev_pos+3, pos-(prev_pos+3));
	    u16[pos-(prev_pos+3)] = '\0';

	    end = 0;
	    uint64_t ul = UASDK_strtoull(u16, &end, 10);
	    if (  (end == u16)
	    		|| (*end != '\0') )
	    {
	      return OpcUa_BadFilterOperandInvalid;
	    }

	    if (ul > UINT16_MAX)
	    {
	      return OpcUa_BadFilterOperandInvalid;
	    }

	    namespaceIndex = static_cast<uint16_t>(ul);
	    prev_pos = pos;
	  }
	  else
	  {
		pos = 0;
		prev_pos = pos;
	  }
  }

  pos = FindFirstSubstr(sourceValue, "i=", prev_pos);
  if (pos >= 0)
  {
    //numeric nodeid
    uint32_t identifier;
    char u32[11];
    if ((Len - pos -2) > 10)
    {
    	return OpcUa_BadFilterOperandInvalid;
    }

    UASDK_memcpy(u32, sourceValue->Payload().Data()+pos+2, (Len-pos-2));
    u32[Len-pos-2] = '\0';

    end = 0;
    uint64_t ul = UASDK_strtoull(u32, &end, 10);
    if (   (end == u32)
    		|| (*end != '\0') )
		{
			return OpcUa_BadFilterOperandInvalid;
		}

    if (ul > UINT32_MAX)
		{
			return OpcUa_BadFilterOperandInvalid;
		}

		IntrusivePtr_t<NodeIdNumeric_t> nPtr = new SafeRefCount_t<NodeIdNumeric_t>();
		if (!nPtr.is_set())
		{
			return OpcUa_BadOutOfMemory;
		}

		identifier = static_cast<uint32_t>(ul);

		nPtr->Initialise(namespaceIndex, identifier);
		nodeidPtr = nPtr;
		return OpcUa_Good;
  }
  else
  {
    pos = FindFirstSubstr(sourceValue, "s=", prev_pos);
    if (pos >= 0)
    {
    	//string nodeid
      int32_t identifierLen;

			IntrusivePtr_t<NodeIdString_t> sPtr = new SafeRefCount_t<NodeIdString_t>();
			if (!sPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			identifierLen = Len - (pos+2);
			if (0 == identifierLen)
			{
				//so null identifier
				sPtr->Identifer().Payload().Initialise(-1);
			}
			else
			{
				sPtr->Identifer().Payload().Initialise(identifierLen);
				UASDK_memcpy(sPtr->Identifer().Payload().Data(), sourceValue->Payload().Data() + (pos+2), identifierLen);
			}

			nodeidPtr = sPtr;
			nodeidPtr->NamespaceIndex() = namespaceIndex;
			return OpcUa_Good;
    }
    else
    {
      pos = FindFirstSubstr(sourceValue, "g=", prev_pos);
      if (pos >= 0)
      {
    	  //guid nodeid
    	  int32_t identifierLen;

    	  IntrusivePtr_t<NodeIdGuid_t> gPtr = new SafeRefCount_t<NodeIdGuid_t>();
    	  if (!gPtr.is_set())
    	  {
    		  return OpcUa_BadOutOfMemory;
    	  }

    	  IntrusivePtr_t<Guid_t> guidPtr = new SafeRefCount_t<Guid_t>();
    	  if (!guidPtr.is_set())
    	  {
    		  return OpcUa_BadOutOfMemory;
    	  }

    	  IntrusivePtr_t<String_t> gStrPtr = new SafeRefCount_t<String_t>();
    	  if (!gStrPtr.is_set())
    	  {
    		  return OpcUa_BadOutOfMemory;
    	  }

    	  identifierLen = Len - (pos+2);
    	  if (identifierLen < 36)
    	  {
    		  return OpcUa_BadOutOfMemory;
    	  }

    	  gStrPtr->Payload().Initialise(identifierLen);
    	  UASDK_memcpy(gStrPtr->Payload().Data(), sourceValue->Payload().Data()+(pos+2), identifierLen);

    	  Status_t status = ConvertStringToGuid(gStrPtr, guidPtr);
    	  if (status.IsBad())
    	  {
    		  return status;
    	  }

    	  gPtr->Identifer().CopyFrom(*guidPtr);
    	  nodeidPtr = gPtr;
    	  nodeidPtr->NamespaceIndex() = namespaceIndex;
    	  return OpcUa_Good;
      }
      else
      {
      	pos = FindFirstSubstr(sourceValue, "b=", prev_pos);
				if (pos < 0)
				{
					return OpcUa_BadFilterOperandInvalid;
				}

				//opague nodeid
				int32_t identifierLen;

				IntrusivePtr_t<NodeIdOpaque_t> oPtr = new SafeRefCount_t<NodeIdOpaque_t>();
				if (!oPtr.is_set())
				{
					return OpcUa_BadOutOfMemory;
				}

				identifierLen = Len - (pos+2);
				if (0 == identifierLen)
				{
					//so null identifier
					oPtr->Identifer().Initialise(-1);
				}
				else
				{
					oPtr->Identifer().Initialise(identifierLen);
					UASDK_memcpy(oPtr->Identifer().Data(), sourceValue->Payload().Data() + (pos+2), identifierLen);
				}

				nodeidPtr = oPtr;
				nodeidPtr->NamespaceIndex() = namespaceIndex;
				return OpcUa_Good;
      }
    }
  }

  return OpcUa_BadFilterOperandInvalid;
}

Status_t TypeConversion_t::ConvertExpandedNodeidToString(IntrusivePtr_t<ExpandedNodeId_t>& expandednodeidPtr, IntrusivePtr_t<String_t>& sourceValue)
{
	Status_t status = OpcUa_Good;
	int32_t len;
	uint32_t pos = 0;
	//svr=4294967296;nsu=x; x=1003
	char cstr[MAX_STR_LEN_FOR_EXP_NODEID_NAMESPACE_URI+224];

	if (!expandednodeidPtr.is_set())
	{
		return OpcUa_BadFilterOperandInvalid;
	}

	if (!expandednodeidPtr->Nodeid().is_set())
	{
		return OpcUa_BadFilterOperandInvalid;
	}

	IntrusivePtr_t<String_t> strPtr = new SafeRefCount_t<String_t>();
	if (!strPtr.is_set())
	{
		return OpcUa_BadOutOfMemory;
	}

	if (expandednodeidPtr->ServerIndex().Value() != 0)
	{
		cstr[pos++] = 's';
		cstr[pos++] = 'v';
		cstr[pos++] = 'r';
		cstr[pos++] = '=';

		len = UASDK_unsigned_integer_to_string(expandednodeidPtr->ServerIndex().Value(), 0, cstr+pos, 10);
		if (len < 0)
		{
			return OpcUa_BadFilterOperandInvalid;
		}

		pos += len;
		cstr[pos++] = ';';
	}

	len = expandednodeidPtr->NamespaceUri().Payload().Length();
	if (len > MAX_STR_LEN_FOR_EXP_NODEID_NAMESPACE_URI)
	{
		return OpcUa_BadFilterOperandInvalid;
	}

	if (len > 0)
	{
		cstr[pos++] = 'n';
		cstr[pos++] = 's';
		cstr[pos++] = 'u';
		cstr[pos++] = '=';

		for (int32_t i = 0; i < len; i++)
		{
			if (';' == expandednodeidPtr->NamespaceUri().Payload().Data()[i])
			{
				cstr[pos++] = '%';
				cstr[pos++] = '3';
				cstr[pos++] = 'B';
			}
			else if ('%' == expandednodeidPtr->NamespaceUri().Payload().Data()[i])
			{
				cstr[pos++] = '%';
				cstr[pos++] = '2';
				cstr[pos++] = '5';
			}
			else
			{
				UASDK_memcpy(cstr+pos, (expandednodeidPtr->NamespaceUri().Payload().Data()+i), 1);
				pos += 1;
			}
		}

		cstr[pos++] = ';';
	}

	IntrusivePtr_t<String_t> nodeidStrPtr;
	status = ConvertNodeIdToString(expandednodeidPtr->Nodeid(), nodeidStrPtr);
	if (!nodeidStrPtr.is_set() || nodeidStrPtr->Payload().Length() < 1 || status.IsBad())
	{
		return OpcUa_BadFilterOperandInvalid;
	}

	len = nodeidStrPtr->Payload().Length();
	strPtr->Payload().Initialise(pos+len);
	UASDK_memcpy(strPtr->Payload().Data(), cstr, pos);
	UASDK_memcpy(strPtr->Payload().Data()+pos, nodeidStrPtr->Payload().Data(), len);

	sourceValue = strPtr;
	return OpcUa_Good;
}

Status_t TypeConversion_t::ConvertStringToExpandedNodeid(IntrusivePtr_t<String_t>& sourceValue, IntrusivePtr_t<ExpandedNodeId_t>& expandednodeidPtr)
{
	UInt32_t serverindex = 0;
	int32_t pos, prev_pos;
	int32_t Len;
	char *end;
	bool uriPresent = false;

	if (!sourceValue.is_set())
	{
		return OpcUa_BadFilterOperandInvalid;
	}

	Len = sourceValue->Payload().Length();
	if (Len < 1)
	{
		return OpcUa_BadFilterOperandInvalid;
	}

	IntrusivePtr_t<String_t> uriPtr = new SafeRefCount_t<String_t>();
	if (!uriPtr.is_set())
	{
		return OpcUa_BadOutOfMemory;
	}
	uriPtr->Payload().Initialise(-1);

	prev_pos = 0;
	pos = FindFirstSubstr(sourceValue, "svr=", prev_pos);
	if (pos >= 0)
	{
		prev_pos = pos;
		pos = FindFirstSubstr(sourceValue, ";", prev_pos);
		if (pos < 0)
		{
			return OpcUa_BadFilterOperandInvalid;
		}

		if ((pos - prev_pos) <= 4)
		{
			return OpcUa_BadFilterOperandInvalid;
		}

		char u32[11];
		if ((pos -prev_pos - 4) > 10)
		{
			return OpcUa_BadFilterOperandInvalid;
		}

		UASDK_memcpy(u32, sourceValue->Payload().Data()+prev_pos+4, (pos -prev_pos - 4));
		u32[pos -prev_pos - 4] = '\0';

		end = 0;
		uint64_t ul = UASDK_strtoull(u32, &end, 10);
		if (   (end == u32)
				|| (*end != '\0') )
		{
			return OpcUa_BadFilterOperandInvalid;
		}

		if (ul > UINT32_MAX)
		{
			return OpcUa_BadFilterOperandInvalid;
		}

		serverindex = (uint32_t)ul;
		prev_pos = pos;
	}
	else
	{
		pos = 0;
		prev_pos = pos;
	}

	pos = FindFirstSubstr(sourceValue, "nsu=", prev_pos);
	if (pos >= 0)
	{
		prev_pos = pos;
		pos = FindFirstSubstr(sourceValue, ";", prev_pos);
		if (pos < 0)
		{
			return OpcUa_BadFilterOperandInvalid;
		}

		if ((pos - prev_pos) <= 4)
		{
			return OpcUa_BadFilterOperandInvalid;
		}

		uriPtr->Payload().Initialise(pos - (prev_pos + 4));
		UASDK_memcpy(uriPtr->Payload().Data(), sourceValue->Payload().Data()+prev_pos+4, pos - (prev_pos + 4));
		uriPresent = true;
		prev_pos = pos;
	}
	else
	{
		pos = prev_pos;
	}

	if (Len - pos < 3)
	{
		return OpcUa_BadFilterOperandInvalid;
	}

	IntrusivePtr_t<String_t> substrPtr = new SafeRefCount_t<String_t>();
	if (!substrPtr.is_set())
	{
		return OpcUa_BadOutOfMemory;
	}

	substrPtr->Payload().Initialise(Len-pos-1);
	UASDK_memcpy(substrPtr->Payload().Data(), sourceValue->Payload().Data()+pos+1, Len-pos-1);

	IntrusivePtr_t<NodeId_t> nodeidPtr;
	Status_t status = ConvertStringToNodeId(substrPtr, nodeidPtr, uriPresent);
	if (!nodeidPtr.is_set() || status.IsBad())
	{
		return OpcUa_BadFilterOperandInvalid;
	}

	IntrusivePtr_t<ExpandedNodeId_t> expNodeidPtr = new SafeRefCount_t<ExpandedNodeId_t>();
	if (!expNodeidPtr.is_set())
	{
		return OpcUa_BadOutOfMemory;
	}

	//set value
	expNodeidPtr->Nodeid() = nodeidPtr;
	expNodeidPtr->ServerIndex().CopyFrom(serverindex);
	expNodeidPtr->NamespaceUri().CopyFrom(*uriPtr);

	expandednodeidPtr = expNodeidPtr;
	return OpcUa_Good;
}

Status_t TypeConversion_t::ConvertBooleanTo(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType)
{
	uint16_t targetNamespaceIndex;
	Status_t status = OpcUa_Good;

	IntrusivePtr_t<Boolean_t> sourceValue;
	sourceValue.reset(new SafeRefCount_t<Boolean_t>());
	if (!sourceValue.is_set())
	{
		return OpcUa_BadOutOfMemory;
	}

	status = sourceValue->CopyFrom(*sourceType);
	if (status.IsBad())
	{
		return status;
	}

	switch (targetType->TypeId(targetNamespaceIndex))
	{
	case  OpcUaId_Boolean:
		{
			targetType = sourceValue;
			break;
		}
	case  OpcUaId_Byte:
		{
			IntrusivePtr_t<Byte_t> tPtr = new SafeRefCount_t<Byte_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<uint8_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Double:
		{
			IntrusivePtr_t<Double_t> tPtr = new SafeRefCount_t<Double_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<double>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Float:
		{
			IntrusivePtr_t<Float_t> tPtr = new SafeRefCount_t<Float_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<float>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Int16:
		{
			IntrusivePtr_t<Int16_t> tPtr = new SafeRefCount_t<Int16_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<int16_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Int32:
		{
			IntrusivePtr_t<Int32_t> tPtr = new SafeRefCount_t<Int32_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<int32_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Int64:
		{
			IntrusivePtr_t<Int64_t> tPtr = new SafeRefCount_t<Int64_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<int64_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_SByte:
		{
			IntrusivePtr_t<SByte_t> tPtr = new SafeRefCount_t<SByte_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<int8_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_String:
		{
			IntrusivePtr_t<String_t> tPtr = new SafeRefCount_t<String_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (sourceValue->Value())
			{
				uint8_t data[] = "true";
				tPtr->Payload().Initialise(sizeof(data));
				UASDK_memcpy(tPtr->Payload().Data(), data, sizeof(data));
			}
			else
			{
				uint8_t data[] = "false";
				tPtr->Payload().Initialise(sizeof(data));
				UASDK_memcpy(tPtr->Payload().Data(), data, sizeof(data));
			}

			targetType = tPtr;
			break;
		}

	case  OpcUaId_UInt16:
		{
			IntrusivePtr_t<UInt16_t> tPtr = new SafeRefCount_t<UInt16_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<uint16_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_UInt32:
		{
			IntrusivePtr_t<UInt32_t> tPtr = new SafeRefCount_t<UInt32_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<uint32_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_UInt64:
		{
			IntrusivePtr_t<UInt64_t> tPtr = new SafeRefCount_t<UInt64_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<uint64_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	default:
		return OpcUa_BadFilterOperandInvalid;
		break;
	}

	return status;
}

Status_t TypeConversion_t::ConvertByteTo(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType)
{
	uint16_t targetNamespaceIndex;
	Status_t status = OpcUa_Good;

	IntrusivePtr_t<Byte_t> sourceValue;
	sourceValue.reset(new SafeRefCount_t<Byte_t>());
	if (!sourceValue.is_set())
	{
		return OpcUa_BadOutOfMemory;
	}

	status = sourceValue->CopyFrom(*sourceType);
	if (status.IsBad())
	{
		return status;
	}

	switch (targetType->TypeId(targetNamespaceIndex))
	{
	case  OpcUaId_Boolean:
		{
			IntrusivePtr_t<Boolean_t> tPtr = new SafeRefCount_t<Boolean_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(sourceValue->Value() > 0 ? 1 : 0);

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Byte:
		{
			targetType = sourceValue;
			break;
		}

	case  OpcUaId_Double:
		{
			IntrusivePtr_t<Double_t> tPtr = new SafeRefCount_t<Double_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<double>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Float:
		{
			IntrusivePtr_t<Float_t> tPtr = new SafeRefCount_t<Float_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<float>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Int16:
		{
			IntrusivePtr_t<Int16_t> tPtr = new SafeRefCount_t<Int16_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<int16_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Int32:
		{
			IntrusivePtr_t<Int32_t> tPtr = new SafeRefCount_t<Int32_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<int32_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Int64:
		{
			IntrusivePtr_t<Int64_t> tPtr = new SafeRefCount_t<Int64_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<int64_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_SByte:
		{
			IntrusivePtr_t<SByte_t> tPtr = new SafeRefCount_t<SByte_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (sourceValue->Value() > INT8_MAX)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<int8_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_String:
		{
			IntrusivePtr_t<String_t> tPtr = new SafeRefCount_t<String_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			char cstr[MAX_STR_LEN_FOR_64_BIT_INTEGER + 1];
			int32_t len = 0;
					uint32_t precision = 0;

			len = UASDK_unsigned_integer_to_string(sourceValue->Value(), precision, cstr, MAX_STR_LEN_FOR_64_BIT_INTEGER);
			if (len < 1)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			tPtr->Payload().Initialise(len);
			UASDK_memcpy(tPtr->Payload().Data(), cstr, len);

			targetType = tPtr;
			break;
		}

	case  OpcUaId_UInt16:
		{
			IntrusivePtr_t<UInt16_t> tPtr = new SafeRefCount_t<UInt16_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<uint16_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_UInt32:
		{
			IntrusivePtr_t<UInt32_t> tPtr = new SafeRefCount_t<UInt32_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<uint32_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_UInt64:
		{
			IntrusivePtr_t<UInt64_t> tPtr = new SafeRefCount_t<UInt64_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<uint64_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	default:
		return OpcUa_BadFilterOperandInvalid;
		break;
	}

	return status;
}

Status_t TypeConversion_t::ConvertDoubleTo(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType)
{
	uint16_t targetNamespaceIndex;
	Status_t status = OpcUa_Good;

	IntrusivePtr_t<Double_t> sourceValue;
	sourceValue.reset(new SafeRefCount_t<Double_t>());
	if (!sourceValue.is_set())
	{
		return OpcUa_BadOutOfMemory;
	}

	status = sourceValue->CopyFrom(*sourceType);
	if (status.IsBad())
	{
		return status;
	}

	switch (targetType->TypeId(targetNamespaceIndex))
	{
	case  OpcUaId_Boolean:
		{
			IntrusivePtr_t<Boolean_t> tPtr = new SafeRefCount_t<Boolean_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			int64_t integer = Ifloor((float)(sourceValue->Value() + 0.5));
			if (integer < 0)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			if (integer > 0)
			{
				tPtr->Value(true);
			}
			else
			{
				tPtr->Value(false);
			}

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Byte:
		{
			IntrusivePtr_t<Byte_t> tPtr = new SafeRefCount_t<Byte_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			int64_t integer = Ifloor((float)(sourceValue->Value() + 0.5));
			if ((integer < 0) || (integer > UINT8_MAX))
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<uint8_t>(integer));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Double:
		{
			targetType = sourceValue;
			break;
		}

	case  OpcUaId_Float:
		{
			IntrusivePtr_t<Float_t> tPtr = new SafeRefCount_t<Float_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<float>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Int16:
		{
			IntrusivePtr_t<Int16_t> tPtr = new SafeRefCount_t<Int16_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			int64_t integer = Ifloor((float)(sourceValue->Value() + 0.5));
			if ((integer < INT16_MIN) || (integer > INT16_MAX))
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<int16_t>(integer));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Int32:
		{
			IntrusivePtr_t<Int32_t> tPtr = new SafeRefCount_t<Int32_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			int64_t integer = Ifloor((float)(sourceValue->Value() + 0.5));
			if ((integer < INT32_MIN) || (integer > INT32_MAX))
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<int32_t>(integer));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Int64:
		{
			IntrusivePtr_t<Int64_t> tPtr = new SafeRefCount_t<Int64_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			int64_t integer = Ifloor((float)(sourceValue->Value() + 0.5));

			//transfer value
			tPtr->Value(static_cast<int64_t>(integer));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_SByte:
		{
			IntrusivePtr_t<SByte_t> tPtr = new SafeRefCount_t<SByte_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			int64_t integer = Ifloor((float)(sourceValue->Value() + 0.5));
			if ((integer < INT8_MIN) || (integer > INT8_MAX))
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<int8_t>(integer));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_String:
		{
			IntrusivePtr_t<String_t> tPtr = new SafeRefCount_t<String_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			char cstr[MAX_STR_LEN_FOR_DOUBLE + 1];
			int32_t len = 0;
			uint32_t precision = 0;

			len = UASDK_double_to_string(sourceValue->Value(), precision, cstr, MAX_STR_LEN_FOR_DOUBLE);
			if (len < 1)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			tPtr->Payload().Initialise(len);
			UASDK_memcpy(tPtr->Payload().Data(), cstr, len);

			targetType = tPtr;
			break;
		}

	case  OpcUaId_UInt16:
		{
			IntrusivePtr_t<UInt16_t> tPtr = new SafeRefCount_t<UInt16_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			int64_t integer = Ifloor((float)(sourceValue->Value() + 0.5));
			if ((integer < 0) || (integer > INT16_MAX))
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<uint16_t>(integer));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_UInt32:
		{
			IntrusivePtr_t<UInt32_t> tPtr = new SafeRefCount_t<UInt32_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			int64_t integer = Ifloor((float)(sourceValue->Value() + 0.5));
			if ((integer < 0) || (integer > INT32_MAX))
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<uint32_t>(integer));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_UInt64:
		{
			IntrusivePtr_t<UInt64_t> tPtr = new SafeRefCount_t<UInt64_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			int64_t integer = Ifloor((float)(sourceValue->Value() + 0.5));
			if (integer < 0)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<uint64_t>(integer));

			targetType = tPtr;
			break;
		}

	default:
		return OpcUa_BadFilterOperandInvalid;
		break;
	}
	return status;
}

Status_t TypeConversion_t::ConvertFloatTo(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType)
{
	uint16_t targetNamespaceIndex;
	Status_t status = OpcUa_Good;

	IntrusivePtr_t<Float_t> sourceValue;
	sourceValue.reset(new SafeRefCount_t<Float_t>());
	if (!sourceValue.is_set())
	{
		return OpcUa_BadOutOfMemory;
	}

	status = sourceValue->CopyFrom(*sourceType);
	if (status.IsBad())
	{
		return status;
	}

	switch (targetType->TypeId(targetNamespaceIndex))
	{
	case  OpcUaId_Boolean:
		{
			IntrusivePtr_t<Boolean_t> tPtr = new SafeRefCount_t<Boolean_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			int64_t integer = Ifloor((float)(sourceValue->Value() + 0.5));
			if (integer < 0)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			if (integer > 0)
			{
				tPtr->Value(true);
			}
			else
			{
				tPtr->Value(false);
			}

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Byte:
		{
			IntrusivePtr_t<Byte_t> tPtr = new SafeRefCount_t<Byte_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			int64_t integer = Ifloor((float)(sourceValue->Value() + 0.5));
			if ((integer < 0) || (integer > UINT8_MAX))
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<uint8_t>(integer));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Double:
		{
			IntrusivePtr_t<Double_t> tPtr = new SafeRefCount_t<Double_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<double>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Float:
		{
			targetType = sourceValue;
			break;
		}

	case  OpcUaId_Int16:
		{
			IntrusivePtr_t<Int16_t> tPtr = new SafeRefCount_t<Int16_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			int64_t integer = Ifloor((float)(sourceValue->Value() + 0.5));
			if ((integer < INT16_MIN) || (integer > INT16_MAX))
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<int16_t>(integer));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Int32:
		{
			IntrusivePtr_t<Int32_t> tPtr = new SafeRefCount_t<Int32_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			int64_t integer = Ifloor((float)(sourceValue->Value() + 0.5));
			if ((integer < INT32_MIN) || (integer > INT32_MAX))
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<int32_t>(integer));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Int64:
		{
			IntrusivePtr_t<Int64_t> tPtr = new SafeRefCount_t<Int64_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			int64_t integer = Ifloor((float)(sourceValue->Value() + 0.5));

			//transfer value
			tPtr->Value(static_cast<int64_t>(integer));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_SByte:
		{
			IntrusivePtr_t<SByte_t> tPtr = new SafeRefCount_t<SByte_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			int64_t integer = Ifloor((float)(sourceValue->Value() + 0.5));
			if ((integer < INT8_MIN) || (integer > INT8_MAX))
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<int8_t>(integer));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_String:
		{
			IntrusivePtr_t<String_t> tPtr = new SafeRefCount_t<String_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			char cstr[MAX_STR_LEN_FOR_FLOAT + 1];
			int32_t len = 0;
			uint32_t precision = 0;

			len = UASDK_float_to_string(sourceValue->Value(), precision, cstr, MAX_STR_LEN_FOR_FLOAT);
			if (len < 1)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			tPtr->Payload().Initialise(len);
			UASDK_memcpy(tPtr->Payload().Data(), cstr, len);

			targetType = tPtr;
			break;
		}

	case  OpcUaId_UInt16:
		{
			IntrusivePtr_t<UInt16_t> tPtr = new SafeRefCount_t<UInt16_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			int64_t integer = Ifloor((float)(sourceValue->Value() + 0.5));
			if ((integer < 0) || (integer > INT16_MAX))
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<uint16_t>(integer));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_UInt32:
		{
			IntrusivePtr_t<UInt32_t> tPtr = new SafeRefCount_t<UInt32_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			int64_t integer = Ifloor((float)(sourceValue->Value() + 0.5));
			if ((integer < 0) || (integer > INT32_MAX))
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<uint32_t>(integer));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_UInt64:
		{
			IntrusivePtr_t<UInt64_t> tPtr = new SafeRefCount_t<UInt64_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			int64_t integer = Ifloor((float)(sourceValue->Value() + 0.5));
			if (integer < 0)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<uint64_t>(integer));

			targetType = tPtr;
			break;
		}

	default:
		return OpcUa_BadFilterOperandInvalid;
		break;
	}

	return status;
}

Status_t TypeConversion_t::ConvertInt16To(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType)
{
	uint16_t targetNamespaceIndex;
	Status_t status = OpcUa_Good;

	IntrusivePtr_t<Int16_t> sourceValue;
	sourceValue.reset(new SafeRefCount_t<Int16_t>());
	if (!sourceValue.is_set())
	{
		return OpcUa_BadOutOfMemory;
	}

	status = sourceValue->CopyFrom(*sourceType);
	if (status.IsBad())
	{
		return status;
	}

	switch (targetType->TypeId(targetNamespaceIndex))
	{
	case  OpcUaId_Boolean:
		{
			IntrusivePtr_t<Boolean_t> tPtr = new SafeRefCount_t<Boolean_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (sourceValue->Value() < 0)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			if (sourceValue->Value() > 0)
			{
				tPtr->Value(true);
			}
			else
			{
				tPtr->Value(false);
			}

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Byte:
		{
			IntrusivePtr_t<Byte_t> tPtr = new SafeRefCount_t<Byte_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if ((sourceValue->Value() < 0) || (sourceValue->Value() > UINT8_MAX))
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<uint8_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Double:
		{
			IntrusivePtr_t<Double_t> tPtr = new SafeRefCount_t<Double_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<double>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Float:
		{
			IntrusivePtr_t<Float_t> tPtr = new SafeRefCount_t<Float_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<float>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_SByte:
		{
			IntrusivePtr_t<SByte_t> tPtr = new SafeRefCount_t<SByte_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if ((sourceValue->Value() < INT8_MIN) || (sourceValue->Value() > INT8_MAX))
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<int8_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Int16:
		{
			targetType = sourceValue;
			break;
		}

	case  OpcUaId_Int32:
		{
			IntrusivePtr_t<Int32_t> tPtr = new SafeRefCount_t<Int32_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<int32_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Int64:
		{
			IntrusivePtr_t<Int64_t> tPtr = new SafeRefCount_t<Int64_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<int64_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_String:
		{
			IntrusivePtr_t<String_t> tPtr = new SafeRefCount_t<String_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			char cstr[MAX_STR_LEN_FOR_64_BIT_INTEGER + 1];
			int32_t len = 0;
			uint32_t precision = 0;

			len = UASDK_signed_integer_to_string((int64_t)sourceValue->Value(), precision, cstr, MAX_STR_LEN_FOR_64_BIT_INTEGER);
			if (len < 1)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			tPtr->Payload().Initialise(len);
			UASDK_memcpy(tPtr->Payload().Data(), cstr, len);

			targetType = tPtr;
			break;
		}

	case  OpcUaId_UInt16:
		{
			IntrusivePtr_t<UInt16_t> tPtr = new SafeRefCount_t<UInt16_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (sourceValue->Value() < 0)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<uint16_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_UInt32:
		{
			IntrusivePtr_t<UInt32_t> tPtr = new SafeRefCount_t<UInt32_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (sourceValue->Value() < 0)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<uint32_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_UInt64:
		{
			IntrusivePtr_t<UInt64_t> tPtr = new SafeRefCount_t<UInt64_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (sourceValue->Value() < 0)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<uint64_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	default:
		return OpcUa_BadFilterOperandInvalid;
		break;
	}

	return status;
}

Status_t TypeConversion_t::ConvertInt32To(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType)
{
	uint16_t targetNamespaceIndex;
	Status_t status = OpcUa_Good;

	IntrusivePtr_t<Int32_t> sourceValue;
	sourceValue.reset(new SafeRefCount_t<Int32_t>());
	if (!sourceValue.is_set())
	{
		return OpcUa_BadOutOfMemory;
	}

	status = sourceValue->CopyFrom(*sourceType);
	if (status.IsBad())
	{
		return status;
	}

	switch (targetType->TypeId(targetNamespaceIndex))
	{
	case  OpcUaId_Boolean:
		{
			IntrusivePtr_t<Boolean_t> tPtr = new SafeRefCount_t<Boolean_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (sourceValue->Value() < 0)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			if (sourceValue->Value() > 0)
			{
				tPtr->Value(true);
			}
			else
			{
				tPtr->Value(false);
			}

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Byte:
		{
			IntrusivePtr_t<Byte_t> tPtr = new SafeRefCount_t<Byte_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if ((sourceValue->Value() < 0) || (sourceValue->Value() > UINT8_MAX))
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<uint8_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Double:
		{
			IntrusivePtr_t<Double_t> tPtr = new SafeRefCount_t<Double_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<double>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Float:
		{
			IntrusivePtr_t<Float_t> tPtr = new SafeRefCount_t<Float_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<float>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_SByte:
		{
			IntrusivePtr_t<SByte_t> tPtr = new SafeRefCount_t<SByte_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if ((sourceValue->Value() < INT8_MIN) || (sourceValue->Value() > INT8_MAX))
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<int8_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Int16:
		{
			IntrusivePtr_t<Int16_t> tPtr = new SafeRefCount_t<Int16_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if ((sourceValue->Value() < INT16_MIN) || (sourceValue->Value() > INT16_MAX))
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<int16_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Int32:
		{
			targetType = sourceValue;
			break;
		}

	case  OpcUaId_Int64:
		{
			IntrusivePtr_t<Int64_t> tPtr = new SafeRefCount_t<Int64_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<int64_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_StatusCode:
		{
			IntrusivePtr_t<StatusCode_t> tPtr = new SafeRefCount_t<StatusCode_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			uint32_t u32 = sourceValue->Value();
			tPtr->Value().Value(u32);

			targetType = tPtr;
			break;
		}

	case  OpcUaId_String:
		{
			IntrusivePtr_t<String_t> tPtr = new SafeRefCount_t<String_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			char cstr[MAX_STR_LEN_FOR_64_BIT_INTEGER + 1];
			int32_t len = 0;
			uint32_t precision = 0;

			len = UASDK_signed_integer_to_string(sourceValue->Value(), precision, cstr, MAX_STR_LEN_FOR_64_BIT_INTEGER);
			if (len < 1)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			tPtr->Payload().Initialise(len);
			UASDK_memcpy(tPtr->Payload().Data(), cstr, len);

			targetType = tPtr;
			break;
		}

	case  OpcUaId_UInt16:
		{
			IntrusivePtr_t<UInt16_t> tPtr = new SafeRefCount_t<UInt16_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if ((sourceValue->Value() < 0) || (sourceValue->Value() > UINT16_MAX))
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<uint16_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_UInt32:
		{
			IntrusivePtr_t<UInt32_t> tPtr = new SafeRefCount_t<UInt32_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (sourceValue->Value() < 0)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<uint32_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_UInt64:
		{
			IntrusivePtr_t<UInt64_t> tPtr = new SafeRefCount_t<UInt64_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (sourceValue->Value() < 0)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<uint64_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	default:
		return OpcUa_BadFilterOperandInvalid;
		break;
	}

	return status;
}

Status_t TypeConversion_t::ConvertInt64To(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType)
{
	uint16_t targetNamespaceIndex;
	Status_t status = OpcUa_Good;

	IntrusivePtr_t<Int64_t> sourceValue;
	sourceValue.reset(new SafeRefCount_t<Int64_t>());
	if (!sourceValue.is_set())
	{
		return OpcUa_BadOutOfMemory;
	}

	status = sourceValue->CopyFrom(*sourceType);
	if (status.IsBad())
	{
		return status;
	}

	switch (targetType->TypeId(targetNamespaceIndex))
	{
	case  OpcUaId_Boolean:
		{
			IntrusivePtr_t<Boolean_t> tPtr = new SafeRefCount_t<Boolean_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (sourceValue->Value() < 0)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			if (sourceValue->Value() > 0)
			{
				tPtr->Value(true);
			}
			else
			{
				tPtr->Value(false);
			}

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Byte:
		{
			IntrusivePtr_t<Byte_t> tPtr = new SafeRefCount_t<Byte_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if ((sourceValue->Value() < 0) || (sourceValue->Value() > UINT8_MAX))
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<uint8_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Double:
		{
			IntrusivePtr_t<Double_t> tPtr = new SafeRefCount_t<Double_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<double>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Float:
		{
			IntrusivePtr_t<Float_t> tPtr = new SafeRefCount_t<Float_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<float>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Int16:
		{
			IntrusivePtr_t<Int16_t> tPtr = new SafeRefCount_t<Int16_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if ((sourceValue->Value() < INT16_MIN) || (sourceValue->Value() > INT16_MAX))
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<int16_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Int32:
		{
			IntrusivePtr_t<Int32_t> tPtr = new SafeRefCount_t<Int32_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if ((sourceValue->Value() < INT32_MIN) || (sourceValue->Value() > INT32_MAX))
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<int32_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Int64:
		{
			targetType = sourceValue;
			break;
		}

	case  OpcUaId_SByte:
		{
			IntrusivePtr_t<SByte_t> tPtr = new SafeRefCount_t<SByte_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if ((sourceValue->Value() < INT8_MIN) || (sourceValue->Value() > INT8_MAX))
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<int8_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_StatusCode:
		{
			IntrusivePtr_t<StatusCode_t> tPtr = new SafeRefCount_t<StatusCode_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if ((sourceValue->Value() < INT32_MIN) || (sourceValue->Value() > INT32_MAX))
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value() = static_cast<uint32_t>(sourceValue->Value());

			targetType = tPtr;
			break;
		}

	case  OpcUaId_String:
		{
			IntrusivePtr_t<String_t> tPtr = new SafeRefCount_t<String_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			char cstr[MAX_STR_LEN_FOR_64_BIT_INTEGER + 1];
			int32_t len = 0;
			uint32_t precision = 0;

			len = UASDK_signed_integer_to_string(sourceValue->Value(), precision, cstr, MAX_STR_LEN_FOR_64_BIT_INTEGER);
			if (len < 1)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			tPtr->Payload().Initialise(len);
			UASDK_memcpy(tPtr->Payload().Data(), cstr, len);

			targetType = tPtr;
			break;
		}

	case  OpcUaId_UInt16:
		{
			IntrusivePtr_t<UInt16_t> tPtr = new SafeRefCount_t<UInt16_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if ((sourceValue->Value() < 0) || (sourceValue->Value() > UINT16_MAX))
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<uint16_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_UInt32:
		{
			IntrusivePtr_t<UInt32_t> tPtr = new SafeRefCount_t<UInt32_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if ((sourceValue->Value() < 0) || (sourceValue->Value() > UINT32_MAX))
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<uint32_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_UInt64:
		{
			IntrusivePtr_t<UInt64_t> tPtr = new SafeRefCount_t<UInt64_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (sourceValue->Value() < 0)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<uint64_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	default:
		return OpcUa_BadFilterOperandInvalid;
		break;
	}

	return status;
}

Status_t TypeConversion_t::ConvertSByteTo(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType)
{
	uint16_t targetNamespaceIndex;
	Status_t status = OpcUa_Good;

	IntrusivePtr_t<SByte_t> sourceValue;
	sourceValue.reset(new SafeRefCount_t<SByte_t>());
	if (!sourceValue.is_set())
	{
		return OpcUa_BadOutOfMemory;
	}

	status = sourceValue->CopyFrom(*sourceType);
	if (status.IsBad())
	{
		return status;
	}

	switch (targetType->TypeId(targetNamespaceIndex))
	{
	case  OpcUaId_Boolean:
		{
			IntrusivePtr_t<Boolean_t> tPtr = new SafeRefCount_t<Boolean_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (sourceValue->Value() < 0)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			if (sourceValue->Value() > 0)
			{
				tPtr->Value(true);
			}
			else
			{
				tPtr->Value(false);
			}

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Double:
		{
			IntrusivePtr_t<Double_t> tPtr = new SafeRefCount_t<Double_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<double>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Float:
		{
			IntrusivePtr_t<Float_t> tPtr = new SafeRefCount_t<Float_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<float>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Int16:
		{
			IntrusivePtr_t<Int16_t> tPtr = new SafeRefCount_t<Int16_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<int16_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Int32:
		{
			IntrusivePtr_t<Int32_t> tPtr = new SafeRefCount_t<Int32_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<int32_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Int64:
		{
			IntrusivePtr_t<Int64_t> tPtr = new SafeRefCount_t<Int64_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<int64_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Byte:
		{
			IntrusivePtr_t<Byte_t> tPtr = new SafeRefCount_t<Byte_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (sourceValue->Value() < 0)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<uint8_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_SByte:
		{
			targetType = sourceValue;
			break;
		}

	case  OpcUaId_String:
		{
			IntrusivePtr_t<String_t> tPtr = new SafeRefCount_t<String_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			char cstr[MAX_STR_LEN_FOR_64_BIT_INTEGER + 1];
			int32_t len = 0;
			uint32_t precision = 1;

			len = UASDK_signed_integer_to_string(sourceValue->Value(), precision, cstr, MAX_STR_LEN_FOR_64_BIT_INTEGER);
			if (len < 1)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			tPtr->Payload().Initialise(len);
			UASDK_memcpy(tPtr->Payload().Data(), cstr, len);

			targetType = tPtr;
			break;
		}

	case  OpcUaId_UInt16:
		{
			IntrusivePtr_t<UInt16_t> tPtr = new SafeRefCount_t<UInt16_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (sourceValue->Value() < 0)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<uint16_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_UInt32:
		{
			IntrusivePtr_t<UInt32_t> tPtr = new SafeRefCount_t<UInt32_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (sourceValue->Value() < 0)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<uint32_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_UInt64:
		{
			IntrusivePtr_t<UInt64_t> tPtr = new SafeRefCount_t<UInt64_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (sourceValue->Value() < 0)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<uint64_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	default:
		return OpcUa_BadFilterOperandInvalid;
		break;
	}
	return status;
}

Status_t TypeConversion_t::ConvertStringTo(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType)
{
	char *end;
	int32_t len;
	uint16_t targetNamespaceIndex;
	char cstr[MAX_STR_LEN_FOR_64_BIT_INTEGER + 1];
	Status_t status = OpcUa_Good;

	IntrusivePtr_t<String_t> sourceValue;
	sourceValue.reset(new SafeRefCount_t<String_t>());
	if (!sourceValue.is_set())
	{
		return OpcUa_BadOutOfMemory;
	}

	status = sourceValue->CopyFrom(*sourceType);
	if (status.IsBad())
	{
		return status;
	}

	len = sourceValue->Payload().Length();
	if ((len < 1) || (sourceValue->Payload().Data() == 0))
	{
		return OpcUa_BadFilterOperandInvalid;
	}

	switch (targetType->TypeId(targetNamespaceIndex))
	{
	case  OpcUaId_Boolean:
		{
			IntrusivePtr_t<Boolean_t> tPtr = new SafeRefCount_t<Boolean_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			uint8_t data0[] = "true";
			uint8_t data1[] = "1";

			if ((0 == UASDK_memcmp(sourceValue->Payload().Data(), data0, sourceValue->Payload().Length())) || (0 == UASDK_memcmp(sourceValue->Payload().Data(), data1, sourceValue->Payload().Length())))
			{
				tPtr->Value(true);
			}
			else
			{
				uint8_t data2[] = "false";
				uint8_t data3[] = "0";
				if ((0 == UASDK_memcmp(sourceValue->Payload().Data(), data2, sourceValue->Payload().Length())) || (0 == UASDK_memcmp(sourceValue->Payload().Data(), data3, sourceValue->Payload().Length())))
				{
					tPtr->Value(false);
				}
				else
				{
					return OpcUa_BadFilterOperandInvalid;
				}
			}

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Byte:
		{
			IntrusivePtr_t<Byte_t> tPtr = new SafeRefCount_t<Byte_t>();
			if (!tPtr.is_set())
			{

				return OpcUa_BadOutOfMemory;
			}

			if (len > MAX_STR_LEN_FOR_64_BIT_INTEGER)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			UASDK_memcpy(cstr, sourceValue->Payload().Data(), len);
			cstr[len] = '\0';

			end = 0;
			int64_t lnum = UASDK_strtoll(cstr, &end, 10);
			if ((end == cstr)
					|| (*end != '\0') )
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			if ((lnum > UINT8_MAX) || (lnum < 0))
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			tPtr->Value(static_cast<uint8_t>(lnum));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_DateTime:
		{
			IntrusivePtr_t<DateTime_t> tPtr = new SafeRefCount_t<DateTime_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (len > MAX_STR_LEN_FOR_64_BIT_INTEGER)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			UASDK_memcpy(cstr, sourceValue->Payload().Data(), len);
			cstr[len] = '\0';

			end = 0;
			int64_t lnum = UASDK_strtoll(cstr, &end, 10);
			if ((end == cstr)
					|| (*end != '\0') )
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			if (lnum > INT64_MAX || lnum < INT64_MIN)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			tPtr->Value(lnum);

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Double:
		{
			IntrusivePtr_t<Double_t> tPtr = new SafeRefCount_t<Double_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (len > MAX_STR_LEN_FOR_64_BIT_INTEGER)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			UASDK_memcpy(cstr, sourceValue->Payload().Data(), len);
			cstr[len] = '\0';

			double dnum = UASDK_strtod(cstr, &end);
			if (end == cstr)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			tPtr->Value(dnum);

			targetType = tPtr;
			break;
		}

	case  OpcUaId_ExpandedNodeId:
		{
			IntrusivePtr_t<ExpandedNodeId_t> tPtr;
			status = ConvertStringToExpandedNodeid(sourceValue, tPtr);
			if (status.IsBad())
			{
				return status;
			}

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Float:
		{
			IntrusivePtr_t<Float_t> tPtr = new SafeRefCount_t<Float_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (len > MAX_STR_LEN_FOR_64_BIT_INTEGER)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			UASDK_memcpy(cstr, sourceValue->Payload().Data(), len);
			cstr[len] = '\0';

			float fnum = UASDK_strtof(cstr, &end);
			if (end == cstr)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			tPtr->Value(fnum);

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Guid:
		{
			IntrusivePtr_t<Guid_t> tPtr = new SafeRefCount_t<Guid_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			status = ConvertStringToGuid(sourceValue, tPtr);
			if (status.IsBad())
			{
				return status;
			}

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Int16:
		{
			IntrusivePtr_t<Int16_t> tPtr = new SafeRefCount_t<Int16_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (len > MAX_STR_LEN_FOR_64_BIT_INTEGER)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			UASDK_memcpy(cstr, sourceValue->Payload().Data(), len);
			cstr[len] = '\0';

			end = 0;
			int64_t lnum = UASDK_strtoll(cstr, &end, 10);
			if ((end == cstr)
					|| (*end != '\0') )
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			if (lnum > INT16_MAX || lnum < INT16_MIN)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			tPtr->Value(static_cast<int16_t>(lnum));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Int32:
		{
			IntrusivePtr_t<Int32_t> tPtr = new SafeRefCount_t<Int32_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (len > MAX_STR_LEN_FOR_64_BIT_INTEGER)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			UASDK_memcpy(cstr, sourceValue->Payload().Data(), len);
			cstr[len] = '\0';

			end = 0;
			int64_t lnum = UASDK_strtoll(cstr, &end, 10);
			if ((end == cstr)
					|| (*end != '\0') )
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			if (lnum > INT32_MAX || lnum < INT32_MIN)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			tPtr->Value(static_cast<int32_t>(lnum));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Int64:
		{
			IntrusivePtr_t<Int64_t> tPtr = new SafeRefCount_t<Int64_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (len > MAX_STR_LEN_FOR_64_BIT_INTEGER)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			UASDK_memcpy(cstr, sourceValue->Payload().Data(), len);
			cstr[len] = '\0';

			end = 0;
			int64_t lnum = UASDK_strtoll(cstr, &end, 10);
			if ((end == cstr)
					|| (*end != '\0') )
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			if (lnum > INT64_MAX || lnum < INT64_MIN)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			tPtr->Value(lnum);

			targetType = tPtr;
			break;
		}

	case  OpcUaId_NodeId:
		{
			IntrusivePtr_t<NodeId_t> tPtr;
			status = ConvertStringToNodeId(sourceValue, tPtr);
			if (status.IsBad())
			{
				return status;
			}

			targetType = tPtr;
			break;
		}

	case  OpcUaId_SByte:
		{
			IntrusivePtr_t<SByte_t> tPtr = new SafeRefCount_t<SByte_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (len > MAX_STR_LEN_FOR_64_BIT_INTEGER)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			UASDK_memcpy(cstr, sourceValue->Payload().Data(), len);
			cstr[len] = '\0';

			end = 0;
			int64_t lnum = UASDK_strtoll(cstr, &end, 10);
			if ((end == cstr)
					|| (*end != '\0') )
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			if (lnum > INT8_MAX || lnum < INT8_MIN)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			tPtr->Value(static_cast<int8_t>(lnum));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_String:
		{
			targetType = sourceValue;
			break;
		}

	case  OpcUaId_LocalizedText:
		{
			IntrusivePtr_t<LocalizedText_t> tPtr = new SafeRefCount_t<LocalizedText_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			IntrusivePtr_t<String_t> nullStrPtr = new SafeRefCount_t<String_t>();
			if (!nullStrPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//set to a NuLL string
			nullStrPtr->Payload().Initialise(-1);

			//transfer value
			tPtr->Locale().CopyFrom(*nullStrPtr);
			tPtr->Text().CopyFrom(*sourceValue);

			targetType = tPtr;
			break;
		}

	case  OpcUaId_QualifiedName:
		{
			IntrusivePtr_t<QualifiedName_t> tPtr = new SafeRefCount_t<QualifiedName_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->NamespaceIndex().Value(0);
			tPtr->Name().CopyFrom(*sourceValue);

			targetType = tPtr;
			break;
		}

	case  OpcUaId_UInt16:
		{
			IntrusivePtr_t<UInt16_t> tPtr = new SafeRefCount_t<UInt16_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (len > MAX_STR_LEN_FOR_64_BIT_INTEGER)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			UASDK_memcpy(cstr, sourceValue->Payload().Data(), len);
			cstr[len] = '\0';

			end = 0;
			int64_t lnum = UASDK_strtoll(cstr, &end, 10);
			if ((end == cstr)
					|| (*end != '\0') )
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			if ((lnum > UINT16_MAX) || (lnum < 0))
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			tPtr->Value(static_cast<uint16_t>(lnum));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_UInt32:
		{
			IntrusivePtr_t<UInt32_t> tPtr = new SafeRefCount_t<UInt32_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (len > MAX_STR_LEN_FOR_64_BIT_INTEGER)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			UASDK_memcpy(cstr, sourceValue->Payload().Data(), len);
			cstr[len] = '\0';

			end = 0;
			int64_t lnum = UASDK_strtoll(cstr, &end, 10);
			if ((end == cstr)
					|| (*end != '\0') )
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			if ((lnum > UINT32_MAX) || (lnum < 0))
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			tPtr->Value(static_cast<uint32_t>(lnum));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_UInt64:
		{
			IntrusivePtr_t<UInt64_t> tPtr = new SafeRefCount_t<UInt64_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (len > MAX_STR_LEN_FOR_64_BIT_INTEGER)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			UASDK_memcpy(cstr, sourceValue->Payload().Data(), len);
			cstr[len] = '\0';

			end = 0;
			int64_t lnum = UASDK_strtoll(cstr, &end, 10);
			if ((end == cstr)
					|| (*end != '\0') )
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			if ((lnum > UINT64_MAX) || (lnum < 0))
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			tPtr->Value(static_cast<uint64_t>(lnum));

			targetType = tPtr;
			break;
		}

	default:
		return OpcUa_BadFilterOperandInvalid;
		break;
	}

	return status;
}

Status_t TypeConversion_t::ConvertUInt16To(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType)
{
	uint16_t targetNamespaceIndex;
	Status_t status = OpcUa_Good;

	IntrusivePtr_t<UInt16_t> sourceValue;
	sourceValue.reset(new SafeRefCount_t<UInt16_t>());
	if (!sourceValue.is_set())
	{
		return OpcUa_BadOutOfMemory;
	}

	status = sourceValue->CopyFrom(*sourceType);
	if (status.IsBad())
	{
		return status;
	}

	switch (targetType->TypeId(targetNamespaceIndex))
	{
	case  OpcUaId_Boolean:
		{
			IntrusivePtr_t<Boolean_t> tPtr = new SafeRefCount_t<Boolean_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			if (sourceValue->Value() > 0)
			{
				tPtr->Value(true);
			}
			else
			{
				tPtr->Value(false);
			}

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Byte:
		{
			IntrusivePtr_t<Byte_t> tPtr = new SafeRefCount_t<Byte_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (sourceValue->Value() > UINT8_MAX)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<uint8_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Double:
		{
			IntrusivePtr_t<Double_t> tPtr = new SafeRefCount_t<Double_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<double>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Float:
		{
			IntrusivePtr_t<Float_t> tPtr = new SafeRefCount_t<Float_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<float>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_SByte:
		{
			IntrusivePtr_t<SByte_t> tPtr = new SafeRefCount_t<SByte_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (sourceValue->Value() > INT8_MAX)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<int8_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Int16:
		{
			IntrusivePtr_t<Int16_t> tPtr = new SafeRefCount_t<Int16_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (sourceValue->Value() > INT16_MAX)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<int16_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Int32:
		{
			IntrusivePtr_t<Int32_t> tPtr = new SafeRefCount_t<Int32_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<int32_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Int64:
		{
			IntrusivePtr_t<Int64_t> tPtr = new SafeRefCount_t<Int64_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<int64_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_StatusCode:
		{
			IntrusivePtr_t<StatusCode_t> tPtr = new SafeRefCount_t<StatusCode_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			uint16_t u16 = sourceValue->Value();
			uint32_t value = tPtr->Value().Value();
			value = (value & 0xffff) | ((u16 << 16) & 0xffff0000);
			tPtr->Value().Value(value);

			targetType = tPtr;
			break;
		}

	case  OpcUaId_String:
		{
			IntrusivePtr_t<String_t> tPtr = new SafeRefCount_t<String_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			char cstr[MAX_STR_LEN_FOR_64_BIT_INTEGER + 1];
			int32_t len = 0;
			uint32_t precision = 0;

			len = UASDK_unsigned_integer_to_string(sourceValue->Value(), precision, cstr, MAX_STR_LEN_FOR_64_BIT_INTEGER);
			if (len < 1)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			tPtr->Payload().Initialise(len);
			UASDK_memcpy(tPtr->Payload().Data(), cstr, len);

			targetType = tPtr;
			break;
		}

	case  OpcUaId_UInt16:
		{
			targetType = sourceValue;
			break;
		}

	case  OpcUaId_UInt32:
		{
			IntrusivePtr_t<UInt32_t> tPtr = new SafeRefCount_t<UInt32_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<uint32_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_UInt64:
		{
			IntrusivePtr_t<UInt64_t> tPtr = new SafeRefCount_t<UInt64_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<uint64_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	default:
		return OpcUa_BadFilterOperandInvalid;
		break;
	}

	return status;
}

Status_t TypeConversion_t::ConvertUInt32To(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType)
{
	uint16_t targetNamespaceIndex;
	Status_t status = OpcUa_Good;

	IntrusivePtr_t<UInt32_t> sourceValue;
	sourceValue.reset(new SafeRefCount_t<UInt32_t>());
	if (!sourceValue.is_set())
	{
		return OpcUa_BadOutOfMemory;
	}

	status = sourceValue->CopyFrom(*sourceType);
	if (status.IsBad())
	{
		return status;
	}

	switch (targetType->TypeId(targetNamespaceIndex))
	{
	case  OpcUaId_Boolean:
		{
			IntrusivePtr_t<Boolean_t> tPtr = new SafeRefCount_t<Boolean_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			if (sourceValue->Value() > 0)
			{
				tPtr->Value(true);
			}
			else
			{
				tPtr->Value(false);
			}

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Byte:
		{
			IntrusivePtr_t<Byte_t> tPtr = new SafeRefCount_t<Byte_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (sourceValue->Value() > UINT8_MAX)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<uint8_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Double:
		{
			IntrusivePtr_t<Double_t> tPtr = new SafeRefCount_t<Double_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<double>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Float:
		{
			IntrusivePtr_t<Float_t> tPtr = new SafeRefCount_t<Float_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<float>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_SByte:
		{
			IntrusivePtr_t<SByte_t> tPtr = new SafeRefCount_t<SByte_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (sourceValue->Value() > INT8_MAX)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<int8_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Int16:
		{
			IntrusivePtr_t<Int16_t> tPtr = new SafeRefCount_t<Int16_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (sourceValue->Value() > INT16_MAX)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<int16_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Int32:
		{
			IntrusivePtr_t<Int32_t> tPtr = new SafeRefCount_t<Int32_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (sourceValue->Value() > INT32_MAX)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<int32_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Int64:
		{
			IntrusivePtr_t<Int64_t> tPtr = new SafeRefCount_t<Int64_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<int64_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_StatusCode:
		{
			IntrusivePtr_t<StatusCode_t> tPtr = new SafeRefCount_t<StatusCode_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			uint32_t u32 = sourceValue->Value();
			tPtr->Value().Value(u32);

			targetType = tPtr;
			break;
		}

	case  OpcUaId_String:
		{
			IntrusivePtr_t<String_t> tPtr = new SafeRefCount_t<String_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			char cstr[MAX_STR_LEN_FOR_64_BIT_INTEGER + 1];
			int32_t len = 0;
			uint32_t precision = 1;

			len = UASDK_unsigned_integer_to_string(sourceValue->Value(), precision, cstr, MAX_STR_LEN_FOR_64_BIT_INTEGER);
			if (len < 1)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			tPtr->Payload().Initialise(len);
			UASDK_memcpy(tPtr->Payload().Data(), cstr, len);

			targetType = tPtr;
			break;
		}

	case  OpcUaId_UInt16:
		{
			IntrusivePtr_t<UInt16_t> tPtr = new SafeRefCount_t<UInt16_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (sourceValue->Value() > UINT16_MAX)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<uint16_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_UInt32:
		{
			targetType = sourceValue;
			break;
		}

	case  OpcUaId_UInt64:
		{
			IntrusivePtr_t<UInt64_t> tPtr = new SafeRefCount_t<UInt64_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<uint64_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	default:
		return OpcUa_BadFilterOperandInvalid;
		break;
	}

	return status;
}

Status_t TypeConversion_t::ConvertUInt64To(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType)
{
	uint16_t targetNamespaceIndex;
	Status_t status = OpcUa_Good;

	IntrusivePtr_t<UInt64_t> sourceValue;
	sourceValue.reset(new SafeRefCount_t<UInt64_t>());
	if (!sourceValue.is_set())
	{
		return OpcUa_BadOutOfMemory;
	}

	status = sourceValue->CopyFrom(*sourceType);
	if (status.IsBad())
	{
		return status;
	}

	switch (targetType->TypeId(targetNamespaceIndex))
	{
	case  OpcUaId_Boolean:
		{
			IntrusivePtr_t<Boolean_t> tPtr = new SafeRefCount_t<Boolean_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			if (sourceValue->Value() > 0)
			{
				tPtr->Value(true);
			}
			else
			{
				tPtr->Value(false);
			}

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Byte:
		{
			IntrusivePtr_t<Byte_t> tPtr = new SafeRefCount_t<Byte_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (sourceValue->Value() > UINT8_MAX)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<uint8_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Double:
		{
			IntrusivePtr_t<Double_t> tPtr = new SafeRefCount_t<Double_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<double>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Float:
		{
			IntrusivePtr_t<Float_t> tPtr = new SafeRefCount_t<Float_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<float>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Int16:
		{
			IntrusivePtr_t<Int16_t> tPtr = new SafeRefCount_t<Int16_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (sourceValue->Value() > INT16_MAX)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<int16_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Int32:
		{
			IntrusivePtr_t<Int32_t> tPtr = new SafeRefCount_t<Int32_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (sourceValue->Value() > INT32_MAX)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<int32_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Int64:
		{
			IntrusivePtr_t<Int64_t> tPtr = new SafeRefCount_t<Int64_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (sourceValue->Value() > INT64_MAX)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<int64_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_SByte:
		{
			IntrusivePtr_t<SByte_t> tPtr = new SafeRefCount_t<SByte_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (sourceValue->Value() > INT8_MAX)
			{
				return OpcUa_BadFilterOperandInvalid;
			}
			//transfer value
			tPtr->Value(static_cast<int8_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_StatusCode:
		{
			IntrusivePtr_t<StatusCode_t> tPtr = new SafeRefCount_t<StatusCode_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (sourceValue->Value() > UINT32_MAX)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value() = static_cast<uint32_t>(sourceValue->Value());

			targetType = tPtr;
			break;
		}

	case  OpcUaId_String:
		{
			IntrusivePtr_t<String_t> tPtr = new SafeRefCount_t<String_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			char cstr[MAX_STR_LEN_FOR_64_BIT_INTEGER + 1];
			int32_t len = 0;
			uint32_t precision = 0;

			len = UASDK_unsigned_integer_to_string(sourceValue->Value(), precision, cstr, MAX_STR_LEN_FOR_64_BIT_INTEGER);
			if (len < 1)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			tPtr->Payload().Initialise(len);
			UASDK_memcpy(tPtr->Payload().Data(), cstr, len);

			targetType = tPtr;
			break;
		}

	case  OpcUaId_UInt16:
		{
			IntrusivePtr_t<UInt16_t> tPtr = new SafeRefCount_t<UInt16_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (sourceValue->Value() > UINT16_MAX)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<uint16_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_UInt32:
		{
			IntrusivePtr_t<UInt32_t> tPtr = new SafeRefCount_t<UInt32_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			if (sourceValue->Value() > UINT32_MAX)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			//transfer value
			tPtr->Value(static_cast<uint32_t>(sourceValue->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_UInt64:
		{
			targetType = sourceValue;
			break;
		}

	default:
		return OpcUa_BadFilterOperandInvalid;
		break;
	}

	return status;
}

Status_t TypeConversion_t::ConvertByteStringTo(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType)
{
	uint16_t targetNamespaceIndex;
	Status_t status = OpcUa_Good;

	IntrusivePtr_t<ByteString_t> sPtr;
	sPtr.reset(new SafeRefCount_t<ByteString_t>());
	if (!sPtr.is_set())
	{
		return OpcUa_BadOutOfMemory;
	}

	status = sPtr->CopyFrom(*sourceType);
	if (status.IsBad())
	{
		return status;
	}

	switch (targetType->TypeId(targetNamespaceIndex))
	{
	  case  OpcUaId_Guid:
			{
				IntrusivePtr_t<Guid_t> tPtr = new SafeRefCount_t<Guid_t>();
				if (!tPtr.is_set())
				{
					return OpcUa_BadOutOfMemory;
				}

				if (sPtr->Length() != Guid_t::GUID_LENGTH)
				{
					return OpcUa_BadFilterOperandInvalid;
				}

				//transfer value
				UASDK_memcpy(tPtr->Value(), sPtr->Data(), Guid_t::GUID_LENGTH);

				targetType = tPtr;
				break;
			}

		case  OpcUaId_ByteString:
			{
				targetType = sPtr;
				break;
			}

	  default:
			return OpcUa_BadFilterOperandInvalid;
			break;
	}

	return status;
}

Status_t TypeConversion_t::ConvertDateTimeTo(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType)
{
	uint16_t targetNamespaceIndex;
	Status_t status = OpcUa_Good;

	IntrusivePtr_t<DateTime_t> sPtr;
	sPtr.reset(new SafeRefCount_t<DateTime_t>());
	if (!sPtr.is_set())
	{
		return OpcUa_BadOutOfMemory;
	}

	status = sPtr->CopyFrom(*sourceType);
	if (status.IsBad())
	{
		return status;
	}

	switch (targetType->TypeId(targetNamespaceIndex))
	{
	case  OpcUaId_String:
		{
			IntrusivePtr_t<String_t> tPtr = new SafeRefCount_t<String_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			char cstr[MAX_STR_LEN_FOR_64_BIT_INTEGER + 1];
			int32_t len = 0;
			uint32_t precision = 1;

			len = UASDK_signed_integer_to_string(sPtr->Value(), precision, cstr, MAX_STR_LEN_FOR_64_BIT_INTEGER);
			if (len < 1)
			{
				return OpcUa_BadFilterOperandInvalid;
			}

			tPtr->Payload().Initialise(len);
			UASDK_memcpy(tPtr->Payload().Data(), cstr, len);

			targetType = tPtr;
			break;
		}

	case  OpcUaId_DateTime:
		{
			targetType = sPtr;
			break;
		}

	default:
		return OpcUa_BadFilterOperandInvalid;
		break;
	}

	return status;
}

Status_t TypeConversion_t::ConvertExpandedNodeIdTo(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType)
{
	uint16_t targetNamespaceIndex;
	Status_t status = OpcUa_Good;

	IntrusivePtr_t<ExpandedNodeId_t> sPtr;
	sPtr.reset(new SafeRefCount_t<ExpandedNodeId_t>());
	if (!sPtr.is_set())
	{
		return OpcUa_BadOutOfMemory;
	}

	status = sPtr->CopyFrom(*sourceType);
	if (status.IsBad())
	{
		return status;
	}

	switch (targetType->TypeId(targetNamespaceIndex))
	{
	case  OpcUaId_NodeId:
		{
			IntrusivePtr_t<NodeId_t> tPtr;

			//transfer value
			status = sPtr->Nodeid()->CopyToNodeId(tPtr);
			if (status.IsBad())
			{
				return status;
			}

			targetType = tPtr;
			break;
		}

	case  OpcUaId_String:
		{
			IntrusivePtr_t<String_t> tPtr;
			status = ConvertExpandedNodeidToString(sPtr, tPtr);
			if (status.IsBad())
			{
				return status;
			}

			targetType = tPtr;
			break;
		}

	case  OpcUaId_ExpandedNodeId:
		{
			targetType = sPtr;
			break;
		}

	default:
		return OpcUa_BadFilterOperandInvalid;
		break;
	}

	return status;
}

Status_t TypeConversion_t::ConvertGuidTo(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType)
{
	uint16_t targetNamespaceIndex;
	Status_t status = OpcUa_Good;

    IntrusivePtr_t<Guid_t> sPtr;
	sPtr.reset(new SafeRefCount_t<Guid_t>());
	if (!sPtr.is_set())
	{
		return OpcUa_BadOutOfMemory;
	}

	status = sPtr->CopyFrom(*sourceType);
	if (status.IsBad())
	{
		return status;
	}

	switch (targetType->TypeId(targetNamespaceIndex))
	{
	case  OpcUaId_ByteString:
		{
			IntrusivePtr_t<ByteString_t> tPtr = new SafeRefCount_t<ByteString_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			status = tPtr->Initialise(Guid_t::GUID_LENGTH);
			if (status.IsBad())
			{
				return status;
			}

			UASDK_memcpy(tPtr->Data(), sPtr->Value(), Guid_t::GUID_LENGTH);

			targetType = tPtr;
			break;
		}

	case  OpcUaId_String:
		{
			IntrusivePtr_t<String_t> tPtr = new SafeRefCount_t<String_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			status = ConvertGuidToString(sPtr, tPtr);
			if (status.IsBad())
			{
				return status;
			}

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Guid:
		{
			targetType = sPtr;
			break;
		}

	default:
		return OpcUa_BadFilterOperandInvalid;
		break;
	}

	return status;
}

Status_t TypeConversion_t::ConvertNodeIdTo(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType)
{
	uint16_t targetNamespaceIndex;
	Status_t status = OpcUa_Good;

    IntrusivePtr_t<NodeId_t> sPtr = RuntimeCast<NodeId_t*>(*sourceType);
	if (status.IsBad())
	{
		return status;
	}

	switch (targetType->TypeId(targetNamespaceIndex))
	{
	case  OpcUaId_ExpandedNodeId:
		{
			IntrusivePtr_t<ExpandedNodeId_t> tPtr = new SafeRefCount_t<ExpandedNodeId_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			sPtr->CopyToNodeId(tPtr->Nodeid());
			if (status.IsBad())
			{
				return status;
			}

			tPtr->NamespaceUri().Payload().Initialise(-1);
			tPtr->ServerIndex().Value(0);

			targetType = tPtr;
			break;
		}

	case  OpcUaId_String:
		{
			IntrusivePtr_t<String_t> tPtr;
			status = ConvertNodeIdToString(sPtr, tPtr);
			if (status.IsBad())
			{
				return status;
			}

			targetType = tPtr;
			break;
		}

	case  OpcUaId_NodeId:
		{
			targetType = sPtr;
			break;
		}

	default:
		return OpcUa_BadFilterOperandInvalid;
		break;
	}

	return status;
}

Status_t TypeConversion_t::ConvertStatusCodeTo(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType)
{
	uint16_t targetNamespaceIndex;
	Status_t status = OpcUa_Good;

	IntrusivePtr_t<StatusCode_t> suPtr;
	suPtr.reset(new SafeRefCount_t<StatusCode_t>());
	if (!suPtr.is_set())
	{
		return OpcUa_BadOutOfMemory;
	}

	status = suPtr->CopyFrom(*sourceType);
	if (status.IsBad())
	{
		return status;
	}

	IntrusivePtr_t<UInt32_t> sPtr;
	sPtr.reset(new SafeRefCount_t<UInt32_t>());
	if (!sPtr.is_set())
	{
		return OpcUa_BadOutOfMemory;
	}

	status = sPtr->CopyFrom(suPtr->Value());
	if (status.IsBad())
	{
		return status;
	}

	switch (targetType->TypeId(targetNamespaceIndex))
	{
	case  OpcUaId_Int32:
		{
			IntrusivePtr_t<Int32_t> tPtr = new SafeRefCount_t<Int32_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<int32_t>(sPtr->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_Int64:
		{
			IntrusivePtr_t<Int64_t> tPtr = new SafeRefCount_t<Int64_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<int64_t>(sPtr->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_UInt16:
		{
			IntrusivePtr_t<UInt16_t> tPtr = new SafeRefCount_t<UInt16_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			uint16_t u16 = (sPtr->Value() >> 16) & 0xffff;
			tPtr->Value(u16);

			targetType = tPtr;
			break;
		}

	case  OpcUaId_UInt32:
		{
			IntrusivePtr_t<UInt32_t> tPtr = new SafeRefCount_t<UInt32_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<uint32_t>(sPtr->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_UInt64:
		{
			IntrusivePtr_t<UInt64_t> tPtr = new SafeRefCount_t<UInt64_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->Value(static_cast<uint64_t>(sPtr->Value()));

			targetType = tPtr;
			break;
		}

	case  OpcUaId_StatusCode:
		{
			targetType = suPtr;
			break;
		}

	default:
		return OpcUa_BadFilterOperandInvalid;
		break;
	}

	return status;
}

Status_t TypeConversion_t::ConvertLocalizedTextTo(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType)
{
	uint16_t targetNamespaceIndex;
	Status_t status = OpcUa_Good;

	IntrusivePtr_t<LocalizedText_t> sPtr;
	sPtr.reset(new SafeRefCount_t<LocalizedText_t>());
	if (!sPtr.is_set())
	{
		return OpcUa_BadOutOfMemory;
	}

	status = sPtr->CopyFrom(*sourceType);
	if (status.IsBad())
	{
		return status;
	}

	switch (targetType->TypeId(targetNamespaceIndex))
	{
	case  OpcUaId_String:
		{
			IntrusivePtr_t<String_t> tPtr = new SafeRefCount_t<String_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->CopyFrom(sPtr->Text());

			targetType = tPtr;
			break;
		}

	case  OpcUaId_LocalizedText:
		{
			targetType = sPtr;
			break;
		}

	default:
		return OpcUa_BadFilterOperandInvalid;
		break;
	}

	return status;
}

Status_t TypeConversion_t::ConvertQualifiedNameTo(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType)
{
	uint16_t targetNamespaceIndex;
	Status_t status = OpcUa_Good;

	IntrusivePtr_t<QualifiedName_t> sPtr;
	sPtr.reset(new SafeRefCount_t<QualifiedName_t>());
	if (!sPtr.is_set())
	{
		return OpcUa_BadOutOfMemory;
	}

	status = sPtr->CopyFrom(*sourceType);
	if (status.IsBad())
	{
		return status;
	}

	switch (targetType->TypeId(targetNamespaceIndex))
	{
	case  OpcUaId_LocalizedText:
		{
			IntrusivePtr_t<LocalizedText_t> tPtr = new SafeRefCount_t<LocalizedText_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			IntrusivePtr_t<String_t> springptr = new SafeRefCount_t<String_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//set to a NuLL string
			springptr->Payload().Initialise(-1);

			//transfer value
			tPtr->Text().CopyFrom(sPtr->Name());
			tPtr->Locale().CopyFrom(*springptr);

			targetType = tPtr;
			break;
		}

	case  OpcUaId_String:
		{
			IntrusivePtr_t<String_t> tPtr = new SafeRefCount_t<String_t>();
			if (!tPtr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			//transfer value
			tPtr->CopyFrom(sPtr->Name());

			targetType = tPtr;
			break;
		}

	case  OpcUaId_QualifiedName:
		{
			targetType = sPtr;
			break;
		}

	default:
		return OpcUa_BadFilterOperandInvalid;
		break;
	}

	return status;
}

Status_t TypeConversion_t::ConvertXmlElementTo(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType)
{
	uint16_t targetNamespaceIndex;
	Status_t status = OpcUa_Good;

	IntrusivePtr_t<XmlElement_t> sPtr;
	sPtr.reset(new SafeRefCount_t<XmlElement_t>());
	if (!sPtr.is_set())
	{
		return OpcUa_BadOutOfMemory;
	}

	status = sPtr->CopyFrom(*sourceType);
	if (status.IsBad())
	{
		return status;
	}

	switch (targetType->TypeId(targetNamespaceIndex))
	{
	case  OpcUaId_XmlElement:
		{
			targetType = sPtr;
			break;
		}

	default:
		return OpcUa_BadFilterOperandInvalid;
		break;
	}

	return status;
}

// this function is called only if the data type of sourceType is different from the data type of targetType
Status_t TypeConversion_t::TypeConversionRule(IntrusivePtr_t<BaseDataType_t>& sourceType, IntrusivePtr_t<BaseDataType_t>& targetType)
{
	uint16_t sourceNamespaceIndex;
	Status_t status = OpcUa_Good;

	if (!sourceType.is_set())
	{
		return OpcUa_BadFilterOperandInvalid;
	}

	switch (sourceType->TypeId(sourceNamespaceIndex))
	{
	case  OpcUaId_Boolean:
		{
			status = ConvertBooleanTo(sourceType, targetType);
			if (status.IsBad())
			{
				return status;
			}
			break;
		}

	case  OpcUaId_Byte:
		{
			status = ConvertByteTo(sourceType, targetType);
			if (status.IsBad())
			{
				return status;
			}
			break;
		}

	case  OpcUaId_ByteString:
		{
			status = ConvertByteStringTo(sourceType, targetType);
			if (status.IsBad())
			{
				return status;
			}
			break;
		}

	case  OpcUaId_DateTime:
		{
			status = ConvertDateTimeTo(sourceType, targetType);
			if (status.IsBad())
			{
				return status;
			}
			break;
		}

	case  OpcUaId_Double:
		{
			status = ConvertDoubleTo(sourceType, targetType);
			if (status.IsBad())
			{
				return status;
			}
			break;
		}

	case  OpcUaId_ExpandedNodeId:
		{
			status = ConvertExpandedNodeIdTo(sourceType, targetType);
			if (status.IsBad())
			{
				return status;
			}
			break;
		}

	case  OpcUaId_Float:
		{
			status = ConvertFloatTo(sourceType, targetType);
			if (status.IsBad())
			{
				return status;
			}
			break;
		}

	case  OpcUaId_Guid:
		{
			status = ConvertGuidTo(sourceType, targetType);
			if (status.IsBad())
			{
				return status;
			}
			break;
		}

	case  OpcUaId_Int16:
		{
			status = ConvertInt16To(sourceType, targetType);
			if (status.IsBad())
			{
				return status;
			}
			break;
		}

	case  OpcUaId_Int32:
		{
			status = ConvertInt32To(sourceType, targetType);
			if (status.IsBad())
			{
				return status;
			}
			break;
		}

	case  OpcUaId_Int64:
		{
			status = ConvertInt64To(sourceType, targetType);
			if (status.IsBad())
			{
				return status;
			}
			break;
		}

	case  OpcUaId_NodeId:
		{
			status = ConvertNodeIdTo(sourceType, targetType);
			if (status.IsBad())
			{
				return status;
			}
			break;
		}

	case  OpcUaId_SByte:
		{
			status = ConvertSByteTo(sourceType, targetType);
			if (status.IsBad())
			{
				return status;
			}
			break;
		}

	case  OpcUaId_StatusCode:
		{
			status = ConvertStatusCodeTo(sourceType, targetType);
			if (status.IsBad())
			{
				return status;
			}
			break;
		}

	case  OpcUaId_String:
		{
			status = ConvertStringTo(sourceType, targetType);
			if (status.IsBad())
			{
				return status;
			}
			break;
		}

	case  OpcUaId_LocalizedText:
		{
			status = ConvertLocalizedTextTo(sourceType, targetType);
			if (status.IsBad())
			{
				return status;
			}
			break;
		}

	case  OpcUaId_QualifiedName:
		{
			status = ConvertQualifiedNameTo(sourceType, targetType);
			if (status.IsBad())
			{
				return status;
			}
			break;
		}

	case  OpcUaId_UInt16:
		{
			status = ConvertUInt16To(sourceType, targetType);
			if (status.IsBad())
			{
				return status;
			}
			break;
		}

	case  OpcUaId_UInt32:
		{
			status = ConvertUInt32To(sourceType, targetType);
			if (status.IsBad())
			{
				return status;
			}
			break;
		}

	case  OpcUaId_UInt64:
		{
			status = ConvertUInt64To(sourceType, targetType);
			if (status.IsBad())
			{
				return status;
			}
			break;
		}

	case  OpcUaId_XmlElement:
		{
			status = ConvertXmlElementTo(sourceType, targetType);
			if (status.IsBad())
			{
				return status;
			}
			break;
		}

	default:
		return OpcUa_BadFilterOperandInvalid;
		break;
	}

	return OpcUa_Good;
}

Status_t TypeConversion_t::IsValidPrecedenceType(IntrusivePtr_t<BaseDataType_t> operandValue)
{
	uint16_t namespaceIndex;
	Status_t status = OpcUa_Good;

	if (operandValue.is_set())
	{
		switch (operandValue->TypeId(namespaceIndex))
		{
		case  OpcUaId_Boolean:
		case  OpcUaId_Byte:
		case  OpcUaId_Double:
		case  OpcUaId_ExpandedNodeId:
		case  OpcUaId_Float:
		case  OpcUaId_Guid:
		case  OpcUaId_Int16:
		case  OpcUaId_Int32:
		case  OpcUaId_Int64:
		case  OpcUaId_NodeId:
		case  OpcUaId_SByte:
		case  OpcUaId_StatusCode:
		case  OpcUaId_String:
		case  OpcUaId_LocalizedText:
		case  OpcUaId_QualifiedName:
		case  OpcUaId_UInt16:
		case  OpcUaId_UInt32:
		case  OpcUaId_UInt64:
			break;

		default:
			status = OpcUa_BadFilterOperandInvalid;
			break;
		}
	}
	else
	{
		status = OpcUa_BadFilterOperandInvalid;
	}

	return status;
}

Status_t 	TypeConversion_t::UseTypePrecedenceConvertToOrFromBoolean(IntrusivePtr_t<BaseDataType_t>& aType,
																																		IntrusivePtr_t<BaseDataType_t>& bType,
																																		IntrusivePtr_t<BaseDataType_t>& dest,
																																		bool &convertedToFirstArgType,
																																		bool &firstArgConversionFail,
																																		bool &secondArgConversionFail)
{
  uint16_t bNamespaceIndex;
  Status_t status = OpcUa_Good;

  IntrusivePtr_t<Boolean_t> tptr;
  tptr.reset(new RefCount_t<Boolean_t>());
  if (!tptr.is_set())
  {
  	return OpcUa_BadOutOfMemory;
  }

  switch (bType->TypeId(bNamespaceIndex))
  {
	case OpcUaId_Boolean:
		{
			dest = bType;
			convertedToFirstArgType = true;
			break;
		}

	case  OpcUaId_String:
		{
			dest = tptr;

			status = TypeConversionRule(bType, dest);
			if (status.IsBad())
			{
				secondArgConversionFail = true;
				return status;
			}

			convertedToFirstArgType = true;
			break;
		}

	case  OpcUaId_SByte:
		{
			IntrusivePtr_t<SByte_t> ptr;
			ptr.reset(new RefCount_t<SByte_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_Byte:
		{
			IntrusivePtr_t<Byte_t> ptr;
			ptr.reset(new RefCount_t<Byte_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_Double:
		{
			IntrusivePtr_t<Double_t> ptr;
			ptr.reset(new RefCount_t<Double_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_Float:
		{
			IntrusivePtr_t<Float_t> ptr;
			ptr.reset(new RefCount_t<Float_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_Int64:
		{
			IntrusivePtr_t<Int64_t> ptr;
			ptr.reset(new RefCount_t<Int64_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_UInt64:
		{
			IntrusivePtr_t<UInt64_t> ptr;
			ptr.reset(new RefCount_t<UInt64_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_Int32:
		{
			IntrusivePtr_t<Int32_t> ptr;
			ptr.reset(new RefCount_t<Int32_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_UInt32:
		{
			IntrusivePtr_t<UInt32_t> ptr;
			ptr.reset(new RefCount_t<UInt32_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_Int16:
		{
			IntrusivePtr_t<Int16_t> ptr;
			ptr.reset(new RefCount_t<Int16_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_UInt16:
		{
			IntrusivePtr_t<UInt16_t> ptr;
			ptr.reset(new RefCount_t<UInt16_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_StatusCode:
		firstArgConversionFail = true;
		return OpcUa_BadFilterOperandInvalid;
		break;

	default:
		secondArgConversionFail = true;
		return OpcUa_BadFilterOperandInvalid;
		break;
  }

  return status;
}

Status_t TypeConversion_t::UseTypePrecedenceConvertToOrFromByte(IntrusivePtr_t<BaseDataType_t>& aType,
																																IntrusivePtr_t<BaseDataType_t>& bType,
																																IntrusivePtr_t<BaseDataType_t>& dest,
																																bool &convertedToFirstArgType,
																																bool &firstArgConversionFail,
																																bool &secondArgConversionFail)
{
  uint16_t bNamespaceIndex;
  Status_t status = OpcUa_Good;

  IntrusivePtr_t<Byte_t> tptr;
  tptr.reset(new RefCount_t<Byte_t>());
  if (!tptr.is_set())
  {
  	return OpcUa_BadOutOfMemory;
  }

  switch (bType->TypeId(bNamespaceIndex))
  {
	case OpcUaId_Byte:
	{
		dest = bType;
		convertedToFirstArgType = true;
		break;
	}
	case  OpcUaId_String:
	case  OpcUaId_Boolean:
		{
			dest = tptr;

			status = TypeConversionRule(bType, dest);
			if (status.IsBad())
			{
				secondArgConversionFail = true;
				return status;
			}

			convertedToFirstArgType = true;
			break;
		}

	case  OpcUaId_SByte:
		{
			IntrusivePtr_t<SByte_t> ptr;
			ptr.reset(new RefCount_t<SByte_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_Double:
		{
			IntrusivePtr_t<Double_t> ptr;
			ptr.reset(new RefCount_t<Double_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_Float:
		{
			IntrusivePtr_t<Float_t> ptr;
			ptr.reset(new RefCount_t<Float_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_Int64:
		{
			IntrusivePtr_t<Int64_t> ptr;
			ptr.reset(new RefCount_t<Int64_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_UInt64:
		{
			IntrusivePtr_t<UInt64_t> ptr;
			ptr.reset(new RefCount_t<UInt64_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_Int32:
		{
			IntrusivePtr_t<Int32_t> ptr;
			ptr.reset(new RefCount_t<Int32_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_UInt32:
		{
			IntrusivePtr_t<UInt32_t> ptr;
			ptr.reset(new RefCount_t<UInt32_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_Int16:
		{
			IntrusivePtr_t<Int16_t> ptr;
			ptr.reset(new RefCount_t<Int16_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_UInt16:
		{
			IntrusivePtr_t<UInt16_t> ptr;
			ptr.reset(new RefCount_t<UInt16_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_StatusCode:
		firstArgConversionFail = true;
		return OpcUa_BadFilterOperandInvalid;
		break;

	default:
		secondArgConversionFail = true;
		return OpcUa_BadFilterOperandInvalid;
		break;
  }

  return status;
}

Status_t  TypeConversion_t::UseTypePrecedenceConvertToOrFromSByte(IntrusivePtr_t<BaseDataType_t>& aType,
																																	IntrusivePtr_t<BaseDataType_t>& bType,
																																	IntrusivePtr_t<BaseDataType_t>& dest,
																																	bool &convertedToFirstArgType,
																																	bool &firstArgConversionFail,
																																	bool &secondArgConversionFail)
{
  uint16_t bNamespaceIndex;
  Status_t status = OpcUa_Good;

  IntrusivePtr_t<SByte_t> tptr;
  tptr.reset(new RefCount_t<SByte_t>());
  if (!tptr.is_set())
  {
  	return OpcUa_BadOutOfMemory;
  }

  switch (bType->TypeId(bNamespaceIndex))
  {
	case OpcUaId_SByte:
		{
			dest = bType;
			convertedToFirstArgType = true;
			break;
		}

	case  OpcUaId_String:
	case  OpcUaId_Boolean:
	case  OpcUaId_Byte:
		{
			dest = tptr;

			status = TypeConversionRule(bType, dest);
			if (status.IsBad())
			{
				secondArgConversionFail = true;
				return status;
			}

			convertedToFirstArgType = true;
			break;
		}

	case  OpcUaId_Double:
		{
			IntrusivePtr_t<Double_t> ptr;
			ptr.reset(new RefCount_t<Double_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_Float:
		{
			IntrusivePtr_t<Float_t> ptr;
			ptr.reset(new RefCount_t<Float_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_Int64:
		{
			IntrusivePtr_t<Int64_t> ptr;
			ptr.reset(new RefCount_t<Int64_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_UInt64:
		{
			IntrusivePtr_t<UInt64_t> ptr;
			ptr.reset(new RefCount_t<UInt64_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_Int32:
		{
			IntrusivePtr_t<Int32_t> ptr;
			ptr.reset(new RefCount_t<Int32_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_UInt32:
		{
			IntrusivePtr_t<UInt32_t> ptr;
			ptr.reset(new RefCount_t<UInt32_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_Int16:
		{
			IntrusivePtr_t<Int16_t> ptr;
			ptr.reset(new RefCount_t<Int16_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_UInt16:
		{
			IntrusivePtr_t<UInt16_t> ptr;
			ptr.reset(new RefCount_t<UInt16_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_StatusCode:
		firstArgConversionFail = true;
		return OpcUa_BadFilterOperandInvalid;
		break;

	default:
		secondArgConversionFail = true;
		return OpcUa_BadFilterOperandInvalid;
		break;
  }

  return status;
}

Status_t TypeConversion_t::UseTypePrecedenceConvertToOrFromUInt16(IntrusivePtr_t<BaseDataType_t>& aType,
																																	IntrusivePtr_t<BaseDataType_t>& bType,
																																	IntrusivePtr_t<BaseDataType_t>& dest,
																																	bool &convertedToFirstArgType,
																																	bool &firstArgConversionFail,
																																	bool &secondArgConversionFail)
{
  uint16_t bNamespaceIndex;
  Status_t status = OpcUa_Good;

  IntrusivePtr_t<UInt16_t> tptr;
  tptr.reset(new RefCount_t<UInt16_t>());
  if (!tptr.is_set())
  {
  	return OpcUa_BadOutOfMemory;
  }

  switch (bType->TypeId(bNamespaceIndex))
  {
	case OpcUaId_UInt16:
		{
			dest = bType;
			convertedToFirstArgType = true;
			break;
		}

	case  OpcUaId_String:
	case  OpcUaId_Boolean:
	case  OpcUaId_Byte:
	case  OpcUaId_SByte:
		{
			dest = tptr;

			status = TypeConversionRule(bType, dest);
			if (status.IsBad())
			{
				secondArgConversionFail = true;
				return status;
			}

			convertedToFirstArgType = true;
			break;
		}

	case  OpcUaId_Double:
		{
			IntrusivePtr_t<Double_t> ptr;
			ptr.reset(new RefCount_t<Double_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_Float:
		{
			IntrusivePtr_t<Float_t> ptr;
			ptr.reset(new RefCount_t<Float_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_Int64:
		{
			IntrusivePtr_t<Int64_t> ptr;
			ptr.reset(new RefCount_t<Int64_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_UInt64:
		{
			IntrusivePtr_t<UInt64_t> ptr;
			ptr.reset(new RefCount_t<UInt64_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_Int32:
		{
			IntrusivePtr_t<Int32_t> ptr;
			ptr.reset(new RefCount_t<Int32_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_UInt32:
		{
			IntrusivePtr_t<UInt32_t> ptr;
			ptr.reset(new RefCount_t<UInt32_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_Int16:
		{
			IntrusivePtr_t<Int16_t> ptr;
			ptr.reset(new RefCount_t<Int16_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_StatusCode:
		{
			IntrusivePtr_t<StatusCode_t> ptr;
			ptr.reset(new RefCount_t<StatusCode_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	default:
		secondArgConversionFail = true;
		return OpcUa_BadFilterOperandInvalid;
		break;
  }

  return status;
}

Status_t	TypeConversion_t::UseTypePrecedenceConvertToOrFromInt16(IntrusivePtr_t<BaseDataType_t>& aType,
																																	IntrusivePtr_t<BaseDataType_t>& bType,
																																	IntrusivePtr_t<BaseDataType_t>& dest,
																																	bool &convertedToFirstArgType,
																																	bool &firstArgConversionFail,
																																	bool &secondArgConversionFail)
{
  uint16_t bNamespaceIndex;
  Status_t status = OpcUa_Good;

  IntrusivePtr_t<Int16_t> tptr;
  tptr.reset(new RefCount_t<Int16_t>());
  if (!tptr.is_set())
  {
  	return OpcUa_BadOutOfMemory;
  }

  switch (bType->TypeId(bNamespaceIndex))
  {
	case OpcUaId_Int16:
		{
			dest = bType;
			convertedToFirstArgType = true;
			break;
		}

	case  OpcUaId_String:
	case  OpcUaId_Boolean:
	case  OpcUaId_Byte:
	case  OpcUaId_SByte:
	case  OpcUaId_UInt16:
		{
			dest = tptr;

			status = TypeConversionRule(bType, dest);
			if (status.IsBad())
			{
				secondArgConversionFail = true;
				return status;
			}

			convertedToFirstArgType = true;
			break;
		}

	case  OpcUaId_Double:
		{
			IntrusivePtr_t<Double_t> ptr;
			ptr.reset(new RefCount_t<Double_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_Float:
		{
			IntrusivePtr_t<Float_t> ptr;
			ptr.reset(new RefCount_t<Float_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_Int64:
		{
			IntrusivePtr_t<Int64_t> ptr;
			ptr.reset(new RefCount_t<Int64_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_UInt64:
		{
			IntrusivePtr_t<UInt64_t> ptr;
			ptr.reset(new RefCount_t<UInt64_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_Int32:
		{
			IntrusivePtr_t<Int32_t> ptr;
			ptr.reset(new RefCount_t<Int32_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_UInt32:
		{
			IntrusivePtr_t<UInt32_t> ptr;
			ptr.reset(new RefCount_t<UInt32_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_StatusCode:
		firstArgConversionFail = true;
		return OpcUa_BadFilterOperandInvalid;
		break;

	default:
		secondArgConversionFail = true;
		return OpcUa_BadFilterOperandInvalid;
		break;
  }

  return status;
}

Status_t TypeConversion_t::UseTypePrecedenceConvertToOrFromUInt32(IntrusivePtr_t<BaseDataType_t>& aType,
																																	IntrusivePtr_t<BaseDataType_t>& bType,
																																	IntrusivePtr_t<BaseDataType_t>& dest,
																																	bool &convertedToFirstArgType,
																																	bool &firstArgConversionFail,
																																	bool &secondArgConversionFail)
{
  uint16_t bNamespaceIndex;
  Status_t status = OpcUa_Good;

  IntrusivePtr_t<UInt32_t> tptr;
  tptr.reset(new RefCount_t<UInt32_t>());
  if (!tptr.is_set())
  {
  	return OpcUa_BadOutOfMemory;
  }

  switch (bType->TypeId(bNamespaceIndex))
  {
	case OpcUaId_UInt32:
		{
			dest = bType;
			convertedToFirstArgType = true;
			break;
		}

	case  OpcUaId_StatusCode:
	case  OpcUaId_String:
	case  OpcUaId_Boolean:
	case  OpcUaId_Byte:
	case  OpcUaId_Int16:
	case  OpcUaId_SByte:
	case  OpcUaId_UInt16:
		{
			dest = tptr;

			status = TypeConversionRule(bType, dest);
			if (status.IsBad())
			{
				secondArgConversionFail = true;
				return status;
			}

			convertedToFirstArgType = true;
			break;
		}

	case  OpcUaId_Int32:
		{
			IntrusivePtr_t<Int32_t> ptr;
			ptr.reset(new RefCount_t<Int32_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_UInt64:
		{
			IntrusivePtr_t<UInt64_t> ptr;
			ptr.reset(new RefCount_t<UInt64_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_Int64:
		{
			IntrusivePtr_t<Int64_t> ptr;
			ptr.reset(new RefCount_t<Int64_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_Float:
		{
			IntrusivePtr_t<Float_t> ptr;
			ptr.reset(new RefCount_t<Float_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_Double:
		{
			IntrusivePtr_t<Double_t> ptr;
			ptr.reset(new RefCount_t<Double_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	default:
		secondArgConversionFail = true;
		return OpcUa_BadFilterOperandInvalid;
		break;
  }

  return status;
}

Status_t  TypeConversion_t::UseTypePrecedenceConvertToOrFromInt32(IntrusivePtr_t<BaseDataType_t>& aType,
																																	IntrusivePtr_t<BaseDataType_t>& bType,
																																	IntrusivePtr_t<BaseDataType_t>& dest,
																																	bool &convertedToFirstArgType,
																																	bool &firstArgConversionFail,
																																	bool &secondArgConversionFail)
{
  uint16_t bNamespaceIndex;
  Status_t status = OpcUa_Good;

  IntrusivePtr_t<Int32_t> tptr;
  tptr.reset(new RefCount_t<Int32_t>());
  if (!tptr.is_set())
  {
  	return OpcUa_BadOutOfMemory;
  }

  switch (bType->TypeId(bNamespaceIndex))
  {
		case OpcUaId_Int32:
		{
			dest = bType;
			convertedToFirstArgType = true;
			break;
		}

	case  OpcUaId_StatusCode:
	case  OpcUaId_String:
	case  OpcUaId_Boolean:
	case  OpcUaId_Byte:
	case  OpcUaId_Int16:
	case  OpcUaId_SByte:
	case  OpcUaId_UInt16:
	case  OpcUaId_UInt32:
		{
			dest = tptr;

			status = TypeConversionRule(bType, dest);
			if (status.IsBad())
			{
				secondArgConversionFail = true;
				return status;
			}

			convertedToFirstArgType = true;
			break;
		}

	case  OpcUaId_UInt64:
		{
			IntrusivePtr_t<UInt64_t> ptr;
			ptr.reset(new RefCount_t<UInt64_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_Int64:
		{
			IntrusivePtr_t<Int64_t> ptr;
			ptr.reset(new RefCount_t<Int64_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_Float:
		{
			IntrusivePtr_t<Float_t> ptr;
			ptr.reset(new RefCount_t<Float_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
	}

	case  OpcUaId_Double:
		{
			IntrusivePtr_t<Double_t> ptr;
			ptr.reset(new RefCount_t<Double_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	default:
		secondArgConversionFail = true;
		return OpcUa_BadFilterOperandInvalid;
		break;
  }

  return status;
}

Status_t TypeConversion_t::UseTypePrecedenceConvertToOrFromUInt64(IntrusivePtr_t<BaseDataType_t>& aType,
																																	IntrusivePtr_t<BaseDataType_t>& bType,
																																	IntrusivePtr_t<BaseDataType_t>& dest,
																																	bool &convertedToFirstArgType,
																																	bool &firstArgConversionFail,
																																	bool &secondArgConversionFail)
{
  uint16_t bNamespaceIndex;
  Status_t status = OpcUa_Good;

  IntrusivePtr_t<UInt64_t> tptr;
  tptr.reset(new RefCount_t<UInt64_t>());
  if (!tptr.is_set())
  {
  	return OpcUa_BadOutOfMemory;
  }

  switch (bType->TypeId(bNamespaceIndex))
  {
	case OpcUaId_UInt64:
		{
			dest = bType;
			convertedToFirstArgType = true;
			break;
		}

	case  OpcUaId_StatusCode:
	case  OpcUaId_String:
	case  OpcUaId_Boolean:
	case  OpcUaId_Byte:
	case  OpcUaId_Int16:
	case  OpcUaId_Int32:
	case  OpcUaId_SByte:
	case  OpcUaId_UInt16:
	case  OpcUaId_UInt32:
		{
			dest = tptr;

			status = TypeConversionRule(bType, dest);
			if (status.IsBad())
			{
				secondArgConversionFail = true;
				return status;
			}

			convertedToFirstArgType = true;
			break;
		}

	case  OpcUaId_Int64:
		{
			IntrusivePtr_t<Int64_t> ptr;
			ptr.reset(new RefCount_t<Int64_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_Float:
		{
			IntrusivePtr_t<Float_t> ptr;
			ptr.reset(new RefCount_t<Float_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_Double:
		{
			IntrusivePtr_t<Double_t> ptr;
			ptr.reset(new RefCount_t<Double_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	default:
		secondArgConversionFail = true;
		return OpcUa_BadFilterOperandInvalid;
		break;
  }

  return status;
}

Status_t 	TypeConversion_t::UseTypePrecedenceConvertToOrFromInt64(IntrusivePtr_t<BaseDataType_t>& aType,
																																	IntrusivePtr_t<BaseDataType_t>& bType,
																																	IntrusivePtr_t<BaseDataType_t>& dest,
																																	bool &convertedToFirstArgType,
																																	bool &firstArgConversionFail,
																																	bool &secondArgConversionFail)
{
  uint16_t bNamespaceIndex;
  Status_t status = OpcUa_Good;

  IntrusivePtr_t<Int64_t> tptr;
  tptr.reset(new RefCount_t<Int64_t>());
  if (!tptr.is_set())
  {
  	return OpcUa_BadOutOfMemory;
  }

  switch (bType->TypeId(bNamespaceIndex))
  {
	case OpcUaId_Int64:
		{
			dest = bType;
			convertedToFirstArgType = true;
			break;
		}

	case  OpcUaId_StatusCode:
	case  OpcUaId_String:
	case  OpcUaId_Boolean:
	case  OpcUaId_Byte:
	case  OpcUaId_Int16:
	case  OpcUaId_Int32:
	case  OpcUaId_SByte:
	case  OpcUaId_UInt16:
	case  OpcUaId_UInt32:
	case  OpcUaId_UInt64:
		{
			dest = tptr;

			status = TypeConversionRule(bType, dest);
			if (status.IsBad())
			{
				secondArgConversionFail = true;
				return status;
			}

			convertedToFirstArgType = true;
			break;
		}

	case  OpcUaId_Float:
		{
			IntrusivePtr_t<Float_t> ptr;
			ptr.reset(new RefCount_t<Float_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_Double:
		{
			IntrusivePtr_t<Double_t> ptr;
			ptr.reset(new RefCount_t<Double_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	default:
		secondArgConversionFail = true;
		return OpcUa_BadFilterOperandInvalid;
		break;
  }

  return status;
}

Status_t  TypeConversion_t::UseTypePrecedenceConvertToOrFromFloat(IntrusivePtr_t<BaseDataType_t>& aType,
																																	IntrusivePtr_t<BaseDataType_t>& bType,
																																	IntrusivePtr_t<BaseDataType_t>& dest,
																																	bool &convertedToFirstArgType,
																																	bool &firstArgConversionFail,
																																	bool &secondArgConversionFail)
{
  uint16_t bNamespaceIndex;
  Status_t status = OpcUa_Good;

  IntrusivePtr_t<Float_t> tptr;
  tptr.reset(new RefCount_t<Float_t>());
  if (!tptr.is_set())
  {
  	return OpcUa_BadOutOfMemory;
  }

  switch (bType->TypeId(bNamespaceIndex))
  {
	case OpcUaId_Float:
		{
			dest = bType;
			convertedToFirstArgType = true;
			break;
		}

	case  OpcUaId_StatusCode:
	case  OpcUaId_String:
	case  OpcUaId_Boolean:
	case  OpcUaId_Byte:
	case  OpcUaId_Int16:
	case  OpcUaId_Int32:
	case  OpcUaId_Int64:
	case  OpcUaId_SByte:
	case  OpcUaId_UInt16:
	case  OpcUaId_UInt32:
	case  OpcUaId_UInt64:
		{
			dest = tptr;

			status = TypeConversionRule(bType, dest);
			if (status.IsBad())
			{
				secondArgConversionFail = true;
				return status;
			}

			convertedToFirstArgType = true;
			break;
		}

	case  OpcUaId_Double:
		{
			IntrusivePtr_t<Double_t> ptr;
			ptr.reset(new RefCount_t<Double_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	default:
		secondArgConversionFail = true;
		return OpcUa_BadFilterOperandInvalid;
		break;
  }

  return status;
}

Status_t TypeConversion_t::UseTypePrecedenceConvertToOrFromDouble(IntrusivePtr_t<BaseDataType_t>& bType,
																																	IntrusivePtr_t<BaseDataType_t>& dest,
																																	bool &convertedToFirstArgType,
																																	bool &secondArgConversionFail)
{
  uint16_t bNamespaceIndex;
  Status_t status = OpcUa_Good;

  IntrusivePtr_t<Double_t> tptr;
  tptr.reset(new RefCount_t<Double_t>());
  if (!tptr.is_set())
  {
  	return OpcUa_BadOutOfMemory;
  }

  switch (bType->TypeId(bNamespaceIndex))
  {
	case OpcUaId_Double:
		{
			dest = bType;
			convertedToFirstArgType = true;
			break;
		}

	case  OpcUaId_StatusCode:
	case  OpcUaId_String:
	case  OpcUaId_Boolean:
	case  OpcUaId_Byte:
	case  OpcUaId_Float:
	case  OpcUaId_Int16:
	case  OpcUaId_Int32:
	case  OpcUaId_Int64:
	case  OpcUaId_SByte:
	case  OpcUaId_UInt16:
	case  OpcUaId_UInt32:
	case  OpcUaId_UInt64:
		{
			dest = tptr;

			status = TypeConversionRule(bType, dest);
			if (status.IsBad())
			{
				secondArgConversionFail = true;
				return status;
			}

			convertedToFirstArgType = true;
			break;
		}

	default:
		secondArgConversionFail = true;
		return OpcUa_BadFilterOperandInvalid;
		break;
  }

  return status;
}

Status_t TypeConversion_t::UseTypePrecedenceConvertToOrFromStatusCode(IntrusivePtr_t<BaseDataType_t>& aType,
																																			IntrusivePtr_t<BaseDataType_t>& bType,
																																			IntrusivePtr_t<BaseDataType_t>& dest,
																																			bool &convertedToFirstArgType,
																																			bool &firstArgConversionFail,
																																			bool &secondArgConversionFail)
{
  uint16_t bNamespaceIndex;
  Status_t status = OpcUa_Good;

  IntrusivePtr_t<StatusCode_t> tptr;
  tptr.reset(new RefCount_t<StatusCode_t>());
  if (!tptr.is_set())
  {
  	return OpcUa_BadOutOfMemory;
  }

  switch (bType->TypeId(bNamespaceIndex))
  {
	case OpcUaId_StatusCode:
		{
			dest = bType;
			convertedToFirstArgType = true;
			break;
		}

	case  OpcUaId_UInt16:
		{
			dest = tptr;

			status = TypeConversionRule(bType, dest);
			if (status.IsBad())
			{
				secondArgConversionFail = true;
				return status;
			}

			convertedToFirstArgType = true;
			break;
		}

	case  OpcUaId_Int64:
		{
			IntrusivePtr_t<Int64_t> ptr;
			ptr.reset(new RefCount_t<Int64_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_UInt64:
		{
			IntrusivePtr_t<UInt64_t> ptr;
			ptr.reset(new RefCount_t<UInt64_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_Int32:
		{
			IntrusivePtr_t<Int32_t> ptr;
			ptr.reset(new RefCount_t<Int32_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_UInt32:
		{
			IntrusivePtr_t<UInt32_t> ptr;
			ptr.reset(new RefCount_t<UInt32_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_Guid:
	case  OpcUaId_String:
	case  OpcUaId_ExpandedNodeId:
	case  OpcUaId_NodeId:
	case  OpcUaId_LocalizedText:
	case  OpcUaId_QualifiedName:
		secondArgConversionFail = true;
		return OpcUa_BadFilterOperandInvalid;
		break;

	default:
		firstArgConversionFail = true;
		return OpcUa_BadFilterOperandInvalid;
		break;
  }

  return status;
}

Status_t TypeConversion_t::UseTypePrecedenceConvertToOrFromGuid(IntrusivePtr_t<BaseDataType_t>& bType,
																																IntrusivePtr_t<BaseDataType_t>& dest,
																																bool &convertedToFirstArgType,
																																bool &firstArgConversionFail,
																																bool &secondArgConversionFail)
{
  uint16_t bNamespaceIndex;
  Status_t status = OpcUa_Good;

  IntrusivePtr_t<Guid_t> tptr;
  tptr.reset(new RefCount_t<Guid_t>());
  if (!tptr.is_set())
  {
  	return OpcUa_BadOutOfMemory;
  }

  switch (bType->TypeId(bNamespaceIndex))
  {
	case OpcUaId_Guid:
		{
			dest = bType;
			convertedToFirstArgType = true;
			break;
		}

	case  OpcUaId_String:
		{
			dest = tptr;

			status = TypeConversionRule(bType, dest);
			if (status.IsBad())
			{
				secondArgConversionFail = true;
				return status;
			}

			convertedToFirstArgType = true;
			break;
		}

	case  OpcUaId_ExpandedNodeId:
	case  OpcUaId_NodeId:
	case  OpcUaId_LocalizedText:
	case  OpcUaId_QualifiedName:
		secondArgConversionFail = true;
		return OpcUa_BadFilterOperandInvalid;
		break;

	default:
		firstArgConversionFail = true;
		return OpcUa_BadFilterOperandInvalid;
		break;
  }

  return status;
}

Status_t TypeConversion_t::UseTypePrecedenceConvertToOrFromString(IntrusivePtr_t<BaseDataType_t>& aType,
																																	IntrusivePtr_t<BaseDataType_t>& bType,
																																	IntrusivePtr_t<BaseDataType_t>& dest,
																																	bool &convertedToFirstArgType,
																																	bool &firstArgConversionFail,
																																	bool &secondArgConversionFail)
{
  uint16_t bNamespaceIndex;
  Status_t status = OpcUa_Good;

  IntrusivePtr_t<String_t> tptr;
  tptr.reset(new RefCount_t<String_t>());
  if (!tptr.is_set())
  {
  	return OpcUa_BadOutOfMemory;
  }

  switch (bType->TypeId(bNamespaceIndex))
  {
	case OpcUaId_String:
		{
			dest = bType;
			convertedToFirstArgType = true;
			break;
		}

	case  OpcUaId_ExpandedNodeId:
	case  OpcUaId_NodeId:
	case  OpcUaId_LocalizedText:
	case  OpcUaId_QualifiedName:
		{
			dest = tptr;

			status = TypeConversionRule(bType, dest);
			if (status.IsBad())
			{
				secondArgConversionFail = true;
				return status;
			}

			convertedToFirstArgType = true;
			break;
		}

	case  OpcUaId_Guid:
		{
			IntrusivePtr_t<Guid_t> ptr;
			ptr.reset(new RefCount_t<Guid_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_Boolean:
		{
			IntrusivePtr_t<Boolean_t> ptr;
			ptr.reset(new RefCount_t<Boolean_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_SByte:
		{
			IntrusivePtr_t<SByte_t> ptr;
			ptr.reset(new RefCount_t<SByte_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_Byte:
		{
			IntrusivePtr_t<Byte_t> ptr;
			ptr.reset(new RefCount_t<Byte_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_Double:
		{
			IntrusivePtr_t<Double_t> ptr;
			ptr.reset(new RefCount_t<Double_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_Float:
		{
			IntrusivePtr_t<Float_t> ptr;
			ptr.reset(new RefCount_t<Float_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_Int64:
		{
			IntrusivePtr_t<Int64_t> ptr;
			ptr.reset(new RefCount_t<Int64_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_UInt64:
		{
			IntrusivePtr_t<UInt64_t> ptr;
			ptr.reset(new RefCount_t<UInt64_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_Int32:
		{
			IntrusivePtr_t<Int32_t> ptr;
			ptr.reset(new RefCount_t<Int32_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_UInt32:
		{
			IntrusivePtr_t<UInt32_t> ptr;
			ptr.reset(new RefCount_t<UInt32_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_Int16:
		{
			IntrusivePtr_t<Int16_t> ptr;
			ptr.reset(new RefCount_t<Int16_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_UInt16:
		{
			IntrusivePtr_t<UInt16_t> ptr;
			ptr.reset(new RefCount_t<UInt16_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	default:
		firstArgConversionFail = true;
		return OpcUa_BadFilterOperandInvalid;
		break;
  }

  return status;
}

Status_t TypeConversion_t::UseTypePrecedenceConvertToOrFromExpandedNodeid(IntrusivePtr_t<BaseDataType_t>& aType,
																																					IntrusivePtr_t<BaseDataType_t>& bType,
																																					IntrusivePtr_t<BaseDataType_t>& dest,
																																					bool &convertedToFirstArgType,
																																					bool &firstArgConversionFail,
																																					bool &secondArgConversionFail)
{
  uint16_t bNamespaceIndex;
  Status_t status = OpcUa_Good;

  IntrusivePtr_t<ExpandedNodeId_t> tptr;
  tptr.reset(new RefCount_t<ExpandedNodeId_t>());
  if (!tptr.is_set())
  {
  	return OpcUa_BadOutOfMemory;
  }

  tptr->Nodeid() = new RefCount_t<NodeIdNumeric_t>();
  if (!tptr->Nodeid().is_set())
  {
  	return OpcUa_BadOutOfMemory;
  }

  switch (bType->TypeId(bNamespaceIndex))
  {
	case OpcUaId_ExpandedNodeId:
		{
			dest = bType;
			convertedToFirstArgType = true;
			break;
		}

	case  OpcUaId_NodeId:
		{
			dest = tptr;

			status = TypeConversionRule(bType, dest);
			if (status.IsBad())
			{
				secondArgConversionFail = true;
				return status;
			}

			convertedToFirstArgType = true;
			break;
		}

	case  OpcUaId_String:
		{
			IntrusivePtr_t<String_t> ptr;
			ptr.reset(new RefCount_t<String_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_LocalizedText:
	case  OpcUaId_QualifiedName:
		secondArgConversionFail = true;
		return OpcUa_BadFilterOperandInvalid;
		break;

	default:
		firstArgConversionFail = true;
		return OpcUa_BadFilterOperandInvalid;
		break;
  }

  return status;
}

Status_t TypeConversion_t::UseTypePrecedenceConvertToOrFromNodeId(IntrusivePtr_t<BaseDataType_t>& aType,
																																	IntrusivePtr_t<BaseDataType_t>& bType,
																																	IntrusivePtr_t<BaseDataType_t>& dest,
																																	bool &convertedToFirstArgType,
																																	bool &firstArgConversionFail,
																																	bool &secondArgConversionFail)
{
  uint16_t bNamespaceIndex;
  Status_t status = OpcUa_Good;

  IntrusivePtr_t<ExpandedNodeId_t> tptr;
  tptr.reset(new RefCount_t<ExpandedNodeId_t>());
  if (!tptr.is_set())
  {
  	return OpcUa_BadOutOfMemory;
  }

  tptr->Nodeid() = new RefCount_t<NodeIdNumeric_t>();
  if (!tptr->Nodeid().is_set())
  {
  	return OpcUa_BadOutOfMemory;
  }

  switch (bType->TypeId(bNamespaceIndex))
  {
	case OpcUaId_NodeId:
		{
			dest = bType;
			convertedToFirstArgType = true;
			break;
		}

	case  OpcUaId_ExpandedNodeId:
		{
			dest = tptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_String:
		{
			IntrusivePtr_t<String_t> ptr;
			ptr.reset(new RefCount_t<String_t>());
			if (!ptr.is_set())
			{
				return OpcUa_BadOutOfMemory;
			}

			dest = ptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_LocalizedText:
	case  OpcUaId_QualifiedName:
		secondArgConversionFail = true;
		return OpcUa_BadFilterOperandInvalid;
		break;

	default:
		firstArgConversionFail = true;
		return OpcUa_BadFilterOperandInvalid;
		break;
  }

  return status;
}

Status_t TypeConversion_t::UseTypePrecedenceConvertToOrFromLocalizedText(IntrusivePtr_t<BaseDataType_t>& aType,
																																				IntrusivePtr_t<BaseDataType_t>& bType,
																																				IntrusivePtr_t<BaseDataType_t>& dest,
																																				bool &convertedToFirstArgType,
																																				bool &firstArgConversionFail,
																																				bool &secondArgConversionFail)
{
  uint16_t bNamespaceIndex;
  Status_t status = OpcUa_Good;

  IntrusivePtr_t<String_t> tptr;
  tptr.reset(new RefCount_t<String_t>());
  if (!tptr.is_set())
  {
  	return OpcUa_BadOutOfMemory;
  }

  switch (bType->TypeId(bNamespaceIndex))
  {
	case OpcUaId_LocalizedText:
		{
			dest = bType;
			convertedToFirstArgType = true;
			break;
		}

	case  OpcUaId_String:
		{
			dest = tptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	case  OpcUaId_QualifiedName:
		secondArgConversionFail = true;
		return OpcUa_BadFilterOperandInvalid;
		break;

	default:
		firstArgConversionFail = true;
		return OpcUa_BadFilterOperandInvalid;
		break;
  }

  return status;
}

Status_t 	TypeConversion_t::UseTypePrecedenceConvertToOrFromQualifiedName(IntrusivePtr_t<BaseDataType_t>& aType,
																																					IntrusivePtr_t<BaseDataType_t>& bType,
																																					IntrusivePtr_t<BaseDataType_t>& dest,
																																					bool &convertedToFirstArgType,
																																					bool &firstArgConversionFail)
{
  uint16_t bNamespaceIndex;
  Status_t status = OpcUa_Good;

  IntrusivePtr_t<String_t> tptr;
  tptr.reset(new RefCount_t<String_t>());
  if (!tptr.is_set())
  {
  	return OpcUa_BadOutOfMemory;
  }

  switch (bType->TypeId(bNamespaceIndex))
  {
	case OpcUaId_QualifiedName:
		{
			dest = bType;
			convertedToFirstArgType = true;
			break;
		}

	case  OpcUaId_String:
		{
			dest = tptr;

			status = TypeConversionRule(aType, dest);
			if (status.IsBad())
			{
				firstArgConversionFail = true;
				return status;
			}
			break;
		}

	default:
		firstArgConversionFail = true;
		return OpcUa_BadFilterOperandInvalid;
		break;
  }

  return status;
}

// The data type of 'aType' must be different from the data type of 'bType'
Status_t TypeConversion_t::TypePrecedenceRule(IntrusivePtr_t<BaseDataType_t>& aType,
																							IntrusivePtr_t<BaseDataType_t>& bType,
																							IntrusivePtr_t<BaseDataType_t>& dest,
																							bool &convertedToFirstArgType,
																							bool &firstArgConversionFail,
																							bool &secondArgConversionFail)
{
	uint16_t aNamespaceIndex;
	Status_t status = OpcUa_Good;

	if (!aType.is_set() || !bType.is_set())
	{
		return OpcUa_BadFilterOperandInvalid;
	}

	status = IsValidPrecedenceType(aType);
	if (status.IsBad())
	{
		return status;
	}

	status = IsValidPrecedenceType(bType);
	if (status.IsBad())
	{
		return status;
	}

	convertedToFirstArgType = false;
	firstArgConversionFail = false;
	secondArgConversionFail = false;
	switch (aType->TypeId(aNamespaceIndex))
	{
	case  OpcUaId_Boolean:
		status = UseTypePrecedenceConvertToOrFromBoolean(aType, bType, dest, convertedToFirstArgType, firstArgConversionFail, secondArgConversionFail);
		if (status.IsBad())
		{
			return status;
		}
		break;

	case  OpcUaId_Byte:
		status = UseTypePrecedenceConvertToOrFromByte(aType, bType, dest, convertedToFirstArgType, firstArgConversionFail, secondArgConversionFail);
		if (status.IsBad())
		{
			return status;
		}
		break;

	case  OpcUaId_SByte:
		status = UseTypePrecedenceConvertToOrFromSByte(aType, bType, dest, convertedToFirstArgType, firstArgConversionFail, secondArgConversionFail);
		if (status.IsBad())
		{
			return status;
		}
		break;

	case  OpcUaId_UInt16:
		status = UseTypePrecedenceConvertToOrFromUInt16(aType, bType, dest, convertedToFirstArgType, firstArgConversionFail, secondArgConversionFail);
		if (status.IsBad())
		{
			return status;
		}
		break;

	case  OpcUaId_Int16:
		status = UseTypePrecedenceConvertToOrFromInt16(aType, bType, dest, convertedToFirstArgType, firstArgConversionFail, secondArgConversionFail);
		if (status.IsBad())
		{
			return status;
		}
		break;

	case  OpcUaId_UInt32:
		status = UseTypePrecedenceConvertToOrFromUInt32(aType, bType, dest, convertedToFirstArgType, firstArgConversionFail, secondArgConversionFail);
		if (status.IsBad())
		{
			return status;
		}
		break;

	case  OpcUaId_Int32:
		status = UseTypePrecedenceConvertToOrFromInt32(aType, bType, dest, convertedToFirstArgType, firstArgConversionFail, secondArgConversionFail);
		if (status.IsBad())
		{
			return status;
		}
		break;

	case  OpcUaId_UInt64:
		status = UseTypePrecedenceConvertToOrFromUInt64(aType, bType, dest, convertedToFirstArgType, firstArgConversionFail, secondArgConversionFail);
		if (status.IsBad())
		{
			return status;
		}
		break;

	case  OpcUaId_Int64:
		status = UseTypePrecedenceConvertToOrFromInt64(aType, bType, dest, convertedToFirstArgType, firstArgConversionFail, secondArgConversionFail);
		if (status.IsBad())
		{
			return status;
		}
		break;

	case  OpcUaId_Float:
		status = UseTypePrecedenceConvertToOrFromFloat(aType, bType, dest, convertedToFirstArgType, firstArgConversionFail, secondArgConversionFail);
		if (status.IsBad())
		{
			return status;
		}
		break;

	case  OpcUaId_Double:
		status = UseTypePrecedenceConvertToOrFromDouble(bType, dest, convertedToFirstArgType, secondArgConversionFail);
		if (status.IsBad())
		{
			return status;
		}
		break;

	case  OpcUaId_StatusCode:
		status = UseTypePrecedenceConvertToOrFromStatusCode(aType, bType, dest, convertedToFirstArgType, firstArgConversionFail, secondArgConversionFail);
		if (status.IsBad())
		{
			return status;
		}
		break;

	case  OpcUaId_Guid:
		status = UseTypePrecedenceConvertToOrFromGuid(bType, dest, convertedToFirstArgType, firstArgConversionFail, secondArgConversionFail);
		if (status.IsBad())
		{
			return status;
		}
		break;

	case  OpcUaId_String:
		status = UseTypePrecedenceConvertToOrFromString(aType, bType, dest, convertedToFirstArgType, firstArgConversionFail, secondArgConversionFail);
		if (status.IsBad())
		{
			return status;
		}
		break;

	case  OpcUaId_ExpandedNodeId:
		status = UseTypePrecedenceConvertToOrFromExpandedNodeid(aType, bType, dest, convertedToFirstArgType, firstArgConversionFail, secondArgConversionFail);
		if (status.IsBad())
		{
			return status;
		}
		break;

	case  OpcUaId_NodeId:
		status = UseTypePrecedenceConvertToOrFromNodeId(aType, bType, dest, convertedToFirstArgType, firstArgConversionFail, secondArgConversionFail);
		if (status.IsBad())
		{
			return status;
		}
		break;

	case  OpcUaId_LocalizedText:
		status = UseTypePrecedenceConvertToOrFromLocalizedText(aType, bType, dest, convertedToFirstArgType, firstArgConversionFail, secondArgConversionFail);
		if (status.IsBad())
		{
			return status;
		}
		break;

	case  OpcUaId_QualifiedName:
		status = UseTypePrecedenceConvertToOrFromQualifiedName(aType, bType, dest, convertedToFirstArgType, firstArgConversionFail);
		if (status.IsBad())
		{
			return status;
		}
		break;

	default:
		firstArgConversionFail = true;
		return OpcUa_BadFilterOperandInvalid;
		break;
	}

	return OpcUa_Good;
}
	
//Bitwise Operators Related Conversion Methods

bool TypeConversion_t::IsIntegerType(uint32_t typeID)
{
	bool result = false;

	switch (typeID)
	{
		//As per Part 3 - Section 8.24, Integer ==> Int16, Int32, Int64
	case OpcUaId_Int16:
	case OpcUaId_Int32:
	case OpcUaId_Int64:
		result = true;
		break;

	default:
		break;
	}

	return result;
}

uint32_t TypeConversion_t::GetIntegerSizePriority(uint32_t typeID)
{
	uint32_t result = 0;

	switch (typeID)
	{
	case OpcUaId_Int16:
		result = 4;
		break;
	case OpcUaId_Int32:
		result = 6;
		break;
	case OpcUaId_Int64:
		result = 8;
		break;

	default:
		result = 0;
		break;
	}

	return result;
}

bool TypeConversion_t::CanConvertToIntegerType(uint32_t typeID)
{
	bool result = true;

	//Only Boolean, Float, Double, String, StatusCode can be converted to integer type
	switch (typeID)
	{
	case OpcUaId_Boolean:
	case OpcUaId_Float:
	case OpcUaId_Double:
	case OpcUaId_UInt64:
	case OpcUaId_UInt32:
	case OpcUaId_UInt16:
	case OpcUaId_SByte:
	case OpcUaId_Byte:
	case OpcUaId_String:
	case OpcUaId_StatusCode:
		result = true;
		break;
	default:
		result = false;
		break;
	}

	return result;
}

uint32_t TypeConversion_t::GetTargetTypeForNonIntegers(uint32_t typeID)
{
	uint32_t result = 0;

	//Only Boolean, Float, Double, String, StatusCode can be converted to integer type
	switch (typeID)
	{
	case OpcUaId_Boolean:
	case OpcUaId_SByte:
	case OpcUaId_Byte:
		result = OpcUaId_Int16;//Converting Byte, SByte, Boolean to Int16
		break;
	case OpcUaId_Float:
	case OpcUaId_Double:
	case OpcUaId_UInt64:
		result = OpcUaId_Int64;
		break;
	case OpcUaId_String:
		result = OpcUaId_Int64;//Converting String to Int64 which is the largest integer
		break;
	case OpcUaId_StatusCode:
	case OpcUaId_UInt32:
		result = OpcUaId_Int32;
		break;
	case OpcUaId_UInt16:
		result = OpcUaId_Int16;
		break;
	default:
		result = 0;
		break;
	}

	return result;
}

Status_t TypeConversion_t::ConvertToIntegerType(IntrusivePtr_t<BaseDataType_t>& source, IntrusivePtr_t<BaseDataType_t>& target, uint32_t targetType)
{
	Status_t status = OpcUa_Good;

	switch (targetType)
	{
	case OpcUaId_Int16:
		target = new SafeRefCount_t<Int16_t>();
		break;
	case OpcUaId_Int32:
		target = new SafeRefCount_t<Int32_t>();
		break;
	case OpcUaId_Int64:
		target = new SafeRefCount_t<Int64_t>();
		break;

	default:
		break;
	}

	if (!target.is_set())
	{
		status = OpcUa_BadOutOfMemory;
	}
	else
	{
		status = TypeConversionRule(source, target);
	}
	return status;
}

//Check and convert both inputs values to integer types or return error code.
Status_t TypeConversion_t::CheckAndConvertInputValuesToIntegerType(IntrusivePtr_t<BaseDataType_t>& value1, IntrusivePtr_t<BaseDataType_t>& value2, bool& isNULL)
{
	IntrusivePtr_t<BaseDataType_t> dest, destTemp;
	IntrusivePtr_t<BaseDataType_t> dest1, dest2;
	uint16_t namespaceIndex1 = 0;
	uint16_t namespaceIndex2 = 0;
	uint32_t typeId1 = 0, typeId2 = 0;
	Status_t status = OpcUa_Good;

	typeId1 = value1->TypeId(namespaceIndex1);
	typeId2 = value2->TypeId(namespaceIndex2);

	if (IsIntegerType(typeId1) && IsIntegerType(typeId2))//If both are integer type
	{
		if (typeId1 == typeId2)//Both are of same type.
		{
			//Return success. Both are of same integer types
			status = OpcUa_Good;
		}
		else
		{
			//Both are integers. Now, Convert both operands to same type as they are different
			if (GetIntegerSizePriority(typeId1) > GetIntegerSizePriority(typeId2))
			{
				status = ConvertToIntegerType(value2, dest, typeId1);

				if (status.IsGood())
				{
					status = dest->CopyTo(value2);
				}
			}
			else
			{
				status = ConvertToIntegerType(value1, dest, typeId2);

				if (status.IsGood())
				{
					status = dest->CopyTo(value1);
				}
			}
		}
	}
	else if (IsIntegerType(typeId1))//First operand is integer
	{
		if (CanConvertToIntegerType(typeId2))//Check if second operand can be converted to integer?
		{
			status = ConvertToIntegerType(value2, dest, typeId1);//Convert second operand to first operand type

			if (status.IsGood())
			{
				status = dest->CopyTo(value2);
			}
		}
		else
		{
			isNULL = true;//Conversion failed. Hence we need to return NULL in the out parameter
			status = OpcUa_BadFilterOperandInvalid;
		}
	}
	else if (IsIntegerType(typeId2))//Second operand is integer
	{
		if (CanConvertToIntegerType(typeId1))//Check if first operand can be converted to integer?
		{
			status = ConvertToIntegerType(value1, dest, typeId2);//Convert first operand to second operand type

			if (status.IsGood())
			{
				status = dest->CopyTo(value1);
			}
		}
		else
		{
			isNULL = true;//Conversion failed. Hence we need to return NULL in the out parameter
			status = OpcUa_BadFilterOperandInvalid;
		}
	}
	else//Both operands are non-integers
	{
		if (CanConvertToIntegerType(typeId1) && CanConvertToIntegerType(typeId2))//Check if both operands can be converted to integer?
		{
			uint32_t targetType1 = GetTargetTypeForNonIntegers(typeId1);
			uint32_t targetType2 = GetTargetTypeForNonIntegers(typeId2);

			status = ConvertToIntegerType(value1, dest1, targetType1);//Convert first operand to the target type

			if (status.IsGood())
			{
				status = ConvertToIntegerType(value2, dest2, targetType2);//Convert second operand to the target type
			}

			if (status.IsBad())
			{
				isNULL = true;//Conversion failed. Hence we need to return NULL in the out parameter
				status = OpcUa_BadFilterOperandInvalid;
			}
			else
			{
				//Here, both the operands are converted to integer types now.
				//Now, Convert both operands to same type if they are different
				if (dest1->TypeId(namespaceIndex1) != dest2->TypeId(namespaceIndex2))
				{
					//Compare the size of both operands and convert it to the type of larger integer
					if (GetIntegerSizePriority(dest1->TypeId(namespaceIndex1)) > GetIntegerSizePriority(dest2->TypeId(namespaceIndex2)))
					{
						status = ConvertToIntegerType(dest2, destTemp, dest1->TypeId(namespaceIndex1));

						if (status.IsGood())
						{
							status = destTemp->CopyTo(dest2);
						}
					}
					else
					{
						status = ConvertToIntegerType(dest1, destTemp, dest2->TypeId(namespaceIndex2));

						if (status.IsGood())
						{
							status = destTemp->CopyTo(dest1);
						}
					}

					if (status.IsGood())
					{
						//Overwrite value1 and value2 with dest1 and dest2 so that final operation can be done on value1 and value2 in one place itself
						status = dest1->CopyTo(value1);

						if (status.IsGood())
						{
							status = dest2->CopyTo(value2);
						}
					}
				}
				else
				{
					status = dest1->CopyTo(value1);

					if (status.IsGood())
					{
						status = dest2->CopyTo(value2);
					}
				}
			}
		}
		else
		{
			isNULL = true;//Conversion failed. Hence we need to return NULL in the out parameter
			status = OpcUa_BadFilterOperandInvalid;
		}
	}

	return status;
}

} // namespace uasdk

#endif // UASDK_INCLUDE_EVENTS


