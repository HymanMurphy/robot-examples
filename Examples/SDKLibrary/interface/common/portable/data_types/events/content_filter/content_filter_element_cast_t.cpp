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

#include "content_filter_element_cast_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "opcua_node_id_numeric_t.h"
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
#include "opcua_node_id_t.h"
#include "opcua_expanded_node_id_t.h"
#include "opcua_localized_text_t.h"
#include "opcua_qualified_name_t.h"
#include "opcua_xml_element_t.h"
#include "idata_type_node_t.h"

namespace uasdk
{
  
UA_DEFINE_RUNTIME_TYPE(ContentFilterElement_Cast_t, ContentFilterElement_t);

ContentFilterElement_Cast_t::ContentFilterElement_Cast_t() : ContentFilterElement_t(FilterOperator_t::FILTER_OP_CAST)
{
}

ContentFilterElement_Cast_t::~ContentFilterElement_Cast_t()
{
}

uint32_t  ContentFilterElement_Cast_t::MinimumOperandCount(void) const
{
	return 2;
}

uint32_t  ContentFilterElement_Cast_t::MaximumOperandCount(void) const
{
	return 2;
}

Status_t ContentFilterElement_Cast_t::ApplyFilterElement(const INode_t& node, IContentFilter_t* filter, IntrusivePtr_t<IAttributeAccess_t>& eventAttributes, IntrusivePtr_t<IServerConfiguration_t> configuration, IntrusivePtr_t<BaseDataType_t>& evaluationResult, IntrusivePtr_t<ContentFilterElementResult_t>& elementResult, bool diagnosticsRequested)
{
	bool isNodeIdAndNotExpandedNodeId = true;
	IntrusivePtr_t<BaseDataType_t> dest;
	Status_t status = OpcUa_Good;	

	status = CheckApplyFilterElementArguments(filter, eventAttributes, evaluationResult, elementResult, diagnosticsRequested);

	if (status.IsBad())
	{
		return status;
	}

	if (!configuration.is_set())
	{
		status = OpcUa_BadInvalidArgument;
		elementResult->StatusCode() = status;
		elementResult->OperandStatusCodes()[0]->Value() = status.Value();
		elementResult->OperandStatusCodes()[1]->Value() = status.Value();
		return status;
	}

	IntrusivePtr_t<IAddressSpace_t> addressSpace = configuration->AddressSpace();
	if (!addressSpace.is_set())
	{
		status = OpcUa_BadInvalidArgument;
		elementResult->StatusCode() = status;
		elementResult->OperandStatusCodes()[0]->Value() = status.Value();
		elementResult->OperandStatusCodes()[1]->Value() = status.Value();
		return status;
	}

	IntrusivePtr_t<BaseDataType_t> value1, value2;
	status = GetValidFilterOperandValue(0, node, filter, eventAttributes, configuration, value1, elementResult, diagnosticsRequested);

	if (status.IsBad())
	{
		return status;
	}

	status = GetValidFilterOperandValue(1, node, filter, eventAttributes, configuration, value2, elementResult, diagnosticsRequested);

	if (status.IsBad())
	{
		return status;
	}

	IntrusivePtr_t<NodeIdNumeric_t> nnodidptr = new SafeRefCount_t<NodeIdNumeric_t>();
	if (!nnodidptr.is_set())
	{
		status = OpcUa_BadOutOfMemory;
		elementResult->StatusCode() = status;
		return status;
	}

	status = nnodidptr->CopyTo(dest);
	if (status.IsBad())
	{
		elementResult->StatusCode() = status;
		elementResult->OperandStatusCodes()[1]->Value() = status.Value();
		return status;
	}

	IntrusivePtr_t<ExpandedNodeId_t> expNNodeid;
	IntrusivePtr_t<NodeIdNumeric_t> nnodidptr1;
	uint16_t namespaceIndex = 0;
	if (value2->TypeId(namespaceIndex) != OpcUaId_NodeId && value2->TypeId(namespaceIndex) != OpcUaId_ExpandedNodeId)
	{
		status = TypeConversionRule(value2, dest);//Try to Convert to NodeIdNumeric_t

		if (status.IsBad())//If cannot be converted to NodeIdNumeric_t, then try to convert to ExpandedNodeId_t
		{
			expNNodeid = new SafeRefCount_t<ExpandedNodeId_t>();
			if (!expNNodeid.is_set())
			{
				status = OpcUa_BadOutOfMemory;
				elementResult->StatusCode() = status;
				return status;
			}

			expNNodeid->Nodeid() = new RefCount_t<NodeIdNumeric_t>();

			if (!expNNodeid->Nodeid().is_set())
			{
				status = OpcUa_BadOutOfMemory;
				elementResult->StatusCode() = status;
				return status;
			}

			status = expNNodeid->CopyTo(dest);
			if (status.IsBad())
			{
				elementResult->StatusCode() = status;
				elementResult->OperandStatusCodes()[1]->Value() = status.Value();
				return status;
			}

			status = TypeConversionRule(value2, dest);
			if (status.IsBad())
			{
				elementResult->StatusCode() = status;
				elementResult->OperandStatusCodes()[1]->Value() = status.Value();
				return status;
			}

			expNNodeid = RuntimeCast<ExpandedNodeId_t*>(*dest);
			if (expNNodeid.is_set())
			{
				nnodidptr1 = RuntimeCast<NodeIdNumeric_t*>(*expNNodeid->Nodeid());

				if (!nnodidptr1.is_set())
				{
					status = OpcUa_BadNothingToDo;
				}
			}
			else
			{
				status = OpcUa_BadNothingToDo;
			}

			isNodeIdAndNotExpandedNodeId = false;
		}
		else
		{
			nnodidptr = RuntimeCast<NodeIdNumeric_t*>(*dest);

			if (!nnodidptr.is_set())
			{
				status = OpcUa_BadNothingToDo;
			}
		}

	}
	else if (value2->TypeId(namespaceIndex) == OpcUaId_NodeId)
	{
		nnodidptr = RuntimeCast<NodeIdNumeric_t*>(*value2);

		if (!nnodidptr.is_set())
		{
			status = OpcUa_BadNothingToDo;
		}
	}
	else if (value2->TypeId(namespaceIndex) == OpcUaId_ExpandedNodeId)
	{
		expNNodeid = RuntimeCast<ExpandedNodeId_t*>(*value2);
		if (expNNodeid.is_set())
		{
			nnodidptr1 = RuntimeCast<NodeIdNumeric_t*>(*expNNodeid->Nodeid());

			if (!nnodidptr1.is_set())
			{
				status = OpcUa_BadNothingToDo;
			}
		}
		else
		{
			status = OpcUa_BadNothingToDo;
		}
		isNodeIdAndNotExpandedNodeId = false;
	}

	if (status.IsBad())//If Operand[1] cannot be converted to NodeId_t or ExpandedNodeId_t then return Bad status.
	{
		status = OpcUa_BadFilterOperandInvalid;
		elementResult->StatusCode() = status;
		elementResult->OperandStatusCodes()[1]->Value() = status.Value();
		return status;
	}

	//verify that the node with nnodidptr does exist
	IntrusivePtr_t<NodeId_t> nodeId = isNodeIdAndNotExpandedNodeId ? (IntrusivePtr_t<NodeId_t>)nnodidptr : expNNodeid->Nodeid();
	IntrusivePtr_t<const INode_t> nodePtr = addressSpace->FindDataTypeNode(*nodeId, status);
	if (!nodePtr.is_set() || status.IsBad())
	{
		elementResult->StatusCode() = status;
		elementResult->OperandStatusCodes()[1]->Value() = status.Value();
		return status;
	}

	uint32_t typeId = isNodeIdAndNotExpandedNodeId ? nnodidptr->Identifer().Value() : nnodidptr1->Identifer().Value();
	switch (typeId)
	{
	case  OpcUaId_Boolean:
		{
			IntrusivePtr_t<Boolean_t> tPtr = new SafeRefCount_t<Boolean_t>();
			if (!tPtr.is_set())
			{
				status = OpcUa_BadOutOfMemory;
				elementResult->StatusCode() = status;
				return status;
			}

			status = tPtr->CopyTo(evaluationResult);
			if (status.IsBad())
			{
				evaluationResult = 0;
				elementResult->StatusCode() = status;
				return status;
			}
		}
		break;

	case  OpcUaId_Byte:
		{
			IntrusivePtr_t<Byte_t> tPtr = new SafeRefCount_t<Byte_t>();
			if (!tPtr.is_set())
			{
				status = OpcUa_BadOutOfMemory;
				elementResult->StatusCode() = status;
				return status;
			}

			status = tPtr->CopyTo(evaluationResult);
			if (status.IsBad())
			{
				evaluationResult = 0;
				elementResult->StatusCode() = status;
				return status;
			}
		}
		break;

	case  OpcUaId_ByteString:
		{
			IntrusivePtr_t<ByteString_t> tPtr = new SafeRefCount_t<ByteString_t>();
			if (!tPtr.is_set())
			{
				status = OpcUa_BadOutOfMemory;
				elementResult->StatusCode() = status;
				return status;
			}

			status = tPtr->CopyTo(evaluationResult);
			if (status.IsBad())
			{
				evaluationResult = 0;
				elementResult->StatusCode() = status;
				return status;
			}
		}
		break;

	case  OpcUaId_DateTime:
		{
			IntrusivePtr_t<DateTime_t> tPtr = new SafeRefCount_t<DateTime_t>();
			if (!tPtr.is_set())
			{
				status = OpcUa_BadOutOfMemory;
				elementResult->StatusCode() = status;
				return status;
			}

			status = tPtr->CopyTo(evaluationResult);
			if (status.IsBad())
			{
				evaluationResult = 0;
				elementResult->StatusCode() = status;
				return status;
			}
		}
		break;

	case  OpcUaId_Double:
		{
			IntrusivePtr_t<Double_t> tPtr = new SafeRefCount_t<Double_t>();
			if (!tPtr.is_set())
			{
				status = OpcUa_BadOutOfMemory;
				elementResult->StatusCode() = status;
				return status;
			}

			status = tPtr->CopyTo(evaluationResult);
			if (status.IsBad())
			{
				evaluationResult = 0;
				elementResult->StatusCode() = status;
				return status;
			}
		}
		break;

	case  OpcUaId_ExpandedNodeId:
		{
			IntrusivePtr_t<ExpandedNodeId_t> tPtr = new SafeRefCount_t<ExpandedNodeId_t>();
			if (!tPtr.is_set())
			{
				status = OpcUa_BadOutOfMemory;
				elementResult->StatusCode() = status;
				return status;
			}

			tPtr->Nodeid() = new RefCount_t<NodeIdNumeric_t>();//Note - This is done since the below tPtr->CopyTo will fail since NodeId is NULL

			if (!tPtr->Nodeid().is_set())
			{
				status = OpcUa_BadOutOfMemory;
				elementResult->StatusCode() = status;
				return status;
			}

			status = tPtr->CopyTo(evaluationResult);
			if (status.IsBad())
			{
				evaluationResult = 0;
				elementResult->StatusCode() = status;
				return status;
			}
		}
		break;

	case  OpcUaId_Float:
		{
			IntrusivePtr_t<Float_t> tPtr = new SafeRefCount_t<Float_t>();
			if (!tPtr.is_set())
			{
				status = OpcUa_BadOutOfMemory;
				elementResult->StatusCode() = status;
				return status;
			}

			status = tPtr->CopyTo(evaluationResult);
			if (status.IsBad())
			{
				evaluationResult = 0;
				elementResult->StatusCode() = status;
				return status;
			}
		}
		break;

	case  OpcUaId_Guid:
		{
			IntrusivePtr_t<Guid_t> tPtr = new SafeRefCount_t<Guid_t>();
			if (!tPtr.is_set())
			{
				status = OpcUa_BadOutOfMemory;
				elementResult->StatusCode() = status;
				return status;
			}

			status = tPtr->CopyTo(evaluationResult);
			if (status.IsBad())
			{
				evaluationResult = 0;
				elementResult->StatusCode() = status;
				return status;
			}
		}
		break;

	case  OpcUaId_Int16:
		{
			IntrusivePtr_t<Int16_t> tPtr = new SafeRefCount_t<Int16_t>();
			if (!tPtr.is_set())
			{
				status = OpcUa_BadOutOfMemory;
				elementResult->StatusCode() = status;
				return status;
			}

			status = tPtr->CopyTo(evaluationResult);
			if (status.IsBad())
			{
				evaluationResult = 0;
				elementResult->StatusCode() = status;
				return status;
			}
		}
		break;

	case  OpcUaId_Int32:
		{
			IntrusivePtr_t<Int32_t> tPtr = new SafeRefCount_t<Int32_t>();
			if (!tPtr.is_set())
			{
				status = OpcUa_BadOutOfMemory;
				elementResult->StatusCode() = status;
				return status;
			}

			status = tPtr->CopyTo(evaluationResult);
			if (status.IsBad())
			{
				evaluationResult = 0;
				elementResult->StatusCode() = status;
				return status;
			}
		}
		break;

	case  OpcUaId_Int64:
		{
			IntrusivePtr_t<Int64_t> tPtr = new SafeRefCount_t<Int64_t>();
			if (!tPtr.is_set())
			{
				status = OpcUa_BadOutOfMemory;
				elementResult->StatusCode() = status;
				return status;
			}

			status = tPtr->CopyTo(evaluationResult);
			if (status.IsBad())
			{
				evaluationResult = 0;
				elementResult->StatusCode() = status;
				return status;
			}
		}
		break;

	case  OpcUaId_NodeId:
		{
			IntrusivePtr_t<NodeIdNumeric_t> tPtr = new SafeRefCount_t<NodeIdNumeric_t>();
			if (!tPtr.is_set())
			{
				status = OpcUa_BadOutOfMemory;
				elementResult->StatusCode() = status;
				return status;
			}

			status = tPtr->CopyTo(evaluationResult);
			if (status.IsBad())
			{
				evaluationResult = 0;
				elementResult->StatusCode() = status;
				return status;
			}
		}
		break;

	case  OpcUaId_SByte:
		{
			IntrusivePtr_t<SByte_t> tPtr = new SafeRefCount_t<SByte_t>();
			if (!tPtr.is_set())
			{
				status = OpcUa_BadOutOfMemory;
				elementResult->StatusCode() = status;
				return status;
			}

			status = tPtr->CopyTo(evaluationResult);
			if (status.IsBad())
			{
				evaluationResult = 0;
				elementResult->StatusCode() = status;
				return status;
			}
		}
		break;

	case  OpcUaId_StatusCode:
		{
			IntrusivePtr_t<StatusCode_t> tPtr = new SafeRefCount_t<StatusCode_t>();
			if (!tPtr.is_set())
			{
				status = OpcUa_BadOutOfMemory;
				elementResult->StatusCode() = status;
				return status;
			}

			status = tPtr->CopyTo(evaluationResult);
			if (status.IsBad())
			{
				evaluationResult = 0;
				elementResult->StatusCode() = status;
				return status;
			}
		}
		break;

	case  OpcUaId_String:
		{
			IntrusivePtr_t<String_t> tPtr = new SafeRefCount_t<String_t>();
			if (!tPtr.is_set())
			{
				status = OpcUa_BadOutOfMemory;
				elementResult->StatusCode() = status;
				return status;
			}

			status = tPtr->CopyTo(evaluationResult);
			if (status.IsBad())
			{
				evaluationResult = 0;
				elementResult->StatusCode() = status;
				return status;
			}
		}
		break;

	case  OpcUaId_LocalizedText:
		{
			IntrusivePtr_t<LocalizedText_t> tPtr = new SafeRefCount_t<LocalizedText_t>();
			if (!tPtr.is_set())
			{
				status = OpcUa_BadOutOfMemory;
				elementResult->StatusCode() = status;
				return status;
			}

			status = tPtr->CopyTo(evaluationResult);
			if (status.IsBad())
			{
				evaluationResult = 0;
				elementResult->StatusCode() = status;
				return status;
			}
		}
		break;

	case  OpcUaId_QualifiedName:
		{
			IntrusivePtr_t<QualifiedName_t> tPtr = new SafeRefCount_t<QualifiedName_t>();
			if (!tPtr.is_set())
			{
				status = OpcUa_BadOutOfMemory;
				elementResult->StatusCode() = status;
				return status;
			}

			status = tPtr->CopyTo(evaluationResult);
			if (status.IsBad())
			{
				evaluationResult = 0;
				elementResult->StatusCode() = status;
				return status;
			}
		}
		break;

	case  OpcUaId_UInt16:
		{
			IntrusivePtr_t<UInt16_t> tPtr = new SafeRefCount_t<UInt16_t>();
			if (!tPtr.is_set())
			{
				status = OpcUa_BadOutOfMemory;
				elementResult->StatusCode() = status;
				return status;
			}

			status = tPtr->CopyTo(evaluationResult);
			if (status.IsBad())
			{
				evaluationResult = 0;
				elementResult->StatusCode() = status;
				return status;
			}
		}
		break;

	case  OpcUaId_UInt32:
		{
			IntrusivePtr_t<UInt32_t> tPtr = new SafeRefCount_t<UInt32_t>();
			if (!tPtr.is_set())
			{
				status = OpcUa_BadOutOfMemory;
				elementResult->StatusCode() = status;
				return status;
			}

			status = tPtr->CopyTo(evaluationResult);
			if (status.IsBad())
			{
				evaluationResult = 0;
				elementResult->StatusCode() = status;
				return status;
			}
		}
		break;

	case  OpcUaId_UInt64:
		{
			IntrusivePtr_t<UInt64_t> tPtr = new SafeRefCount_t<UInt64_t>();
			if (!tPtr.is_set())
			{
				status = OpcUa_BadOutOfMemory;
				elementResult->StatusCode() = status;
				return status;
			}

			status = tPtr->CopyTo(evaluationResult);
			if (status.IsBad())
			{
				evaluationResult = 0;
				elementResult->StatusCode() = status;
				return status;
			}
		}
		break;

	case  OpcUaId_XmlElement:
		{
			IntrusivePtr_t<XmlElement_t> tPtr = new SafeRefCount_t<XmlElement_t>();
			if (!tPtr.is_set())
			{
				status = OpcUa_BadOutOfMemory;
				elementResult->StatusCode() = status;
				return status;
			}

			status = tPtr->CopyTo(evaluationResult);
			if (status.IsBad())
			{
				evaluationResult = 0;
				elementResult->StatusCode() = status;
				return status;
			}
		}
		break;

	default:
		status = OpcUa_BadFilterOperandInvalid;
		elementResult->StatusCode() = status;
		elementResult->OperandStatusCodes()[1]->Value() = status.Value();
		return status;
		break;
	}

	status = TypeConversionRule(value1, evaluationResult);
	if (status.IsBad())
	{
		evaluationResult = 0;
		elementResult->StatusCode() = status;
		elementResult->OperandStatusCodes()[0]->Value() = status.Value();
		return status;
	}

	return status;
}

Status_t ContentFilterElement_Cast_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
	return CopyToDestination(*this, destination);
}

Status_t ContentFilterElement_Cast_t::CopyFrom(const BaseDataType_t& source)
{
	IntrusivePtr_t<const ContentFilterElement_Cast_t> ptr = RuntimeCast<const ContentFilterElement_Cast_t*>(source);
	if (!ptr.is_set())
	{
		return OpcUa_BadTypeMismatch;
	}

	return CopyFrom(*ptr);
}

Status_t ContentFilterElement_Cast_t::CopyFrom(const ContentFilterElement_Cast_t& source)
{
	Status_t status = FilterOperands().CopyFrom(source.FilterOperands());
	if (status.IsBad())
	{
		return status;
	}

	return OpcUa_Good;
}

} // namespace uasdk


#endif // UASDK_INCLUDE_EVENTS

