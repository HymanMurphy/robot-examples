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

#include "content_filter_element_of_type_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "opcua_node_id_numeric_t.h"
#include "opcua_boolean_t.h"
#include "address_space_utilities_t.h"
#include "iobject_type_node_t.h"
#include "ivariable_type_node_t.h"
#include "opcua_uint32_t.h"

namespace uasdk
{
  
UA_DEFINE_RUNTIME_TYPE(ContentFilterElement_OfType_t, ContentFilterElement_t);

ContentFilterElement_OfType_t::ContentFilterElement_OfType_t() : ContentFilterElement_t(FilterOperator_t::FILTER_OP_OFTYPE)
{
}

ContentFilterElement_OfType_t::~ContentFilterElement_OfType_t()
{
}

uint32_t  ContentFilterElement_OfType_t::MinimumOperandCount(void) const
{
	return 1;
}

uint32_t  ContentFilterElement_OfType_t::MaximumOperandCount(void) const
{
	return 1;
}

Status_t ContentFilterElement_OfType_t::ApplyFilterElement(const INode_t& node, IContentFilter_t* filter, IntrusivePtr_t<IAttributeAccess_t>& eventAttributes, IntrusivePtr_t<IServerConfiguration_t> configuration, IntrusivePtr_t<BaseDataType_t>& evaluationResult, IntrusivePtr_t<ContentFilterElementResult_t>& elementResult, bool diagnosticsRequested)
{
	IntrusivePtr_t<BaseDataType_t> dest;
	Status_t status = OpcUa_Good;

  if (!configuration.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

	IntrusivePtr_t<IAddressSpace_t> addressSpace = configuration->AddressSpace();
  UASDK_RETURN_UNEXPECTED_IF_NULL(addressSpace);

	IntrusivePtr_t<Boolean_t> nodeIsOfTypeOrSubtypeOfOperand  = new SafeRefCount_t<Boolean_t>();
	if (!nodeIsOfTypeOrSubtypeOfOperand.is_set())
	{
		status = OpcUa_BadOutOfMemory;
		elementResult->StatusCode() = status;
		elementResult->OperandStatusCodes()[0]->Value() = status.Value();
		return status;
	}

	//Initialize the target node not be oftype or subtype
	nodeIsOfTypeOrSubtypeOfOperand->Value(false);

	status = CheckApplyFilterElementArguments(filter, eventAttributes, evaluationResult, elementResult, diagnosticsRequested);
	if (status.IsBad())
	{
		nodeIsOfTypeOrSubtypeOfOperand->CopyTo(evaluationResult);
		return status;
	}

	IntrusivePtr_t<BaseDataType_t> operandValue;
	status = GetValidFilterOperandValue(0, node, filter, eventAttributes, configuration, operandValue, elementResult, diagnosticsRequested);

	if (status.IsBad())
	{
		return status;
	}

	IntrusivePtr_t<NodeIdNumeric_t> nnodeidPtr = new SafeRefCount_t<NodeIdNumeric_t>();
	if (!nnodeidPtr.is_set())
	{
		nodeIsOfTypeOrSubtypeOfOperand->CopyTo(evaluationResult);
		status = OpcUa_BadOutOfMemory;
		elementResult->StatusCode() = status;
		elementResult->OperandStatusCodes()[0]->Value() = status.Value();
		return status;
	}

	status = nnodeidPtr->CopyTo(dest);
	if (status.IsBad())
	{
		nodeIsOfTypeOrSubtypeOfOperand->CopyTo(evaluationResult);
		elementResult->StatusCode() = status;
		elementResult->OperandStatusCodes()[0]->Value() = status.Value();
		return status;
	}

	status = TypeConversionRule(operandValue, dest);
	if (status.IsBad())
	{
		nodeIsOfTypeOrSubtypeOfOperand->CopyTo(evaluationResult);
		elementResult->StatusCode() = status;
		elementResult->OperandStatusCodes()[0]->Value() = status.Value();
		return status;
	}

  status = nnodeidPtr->CopyFrom(*dest);
  if (status.IsBad())
  {
    nodeIsOfTypeOrSubtypeOfOperand->CopyTo(evaluationResult);
    elementResult->StatusCode() = status;
    elementResult->OperandStatusCodes()[0]->Value() = status.Value();
    return status;
  }

	if (!addressSpace.is_set())
	{
		nodeIsOfTypeOrSubtypeOfOperand->CopyTo(evaluationResult);
		status = OpcUa_BadUnexpectedError;
		elementResult->StatusCode() = status;
		return status;
	}

	IntrusivePtr_t<IObjectTypeNode_t> objectTypeNode = addressSpace->FindObjectTypeNode(*nnodeidPtr, status);
	if (!objectTypeNode.is_set() || status.IsBad())
	{
		IntrusivePtr_t<IVariableTypeNode_t> variableTypeNode = addressSpace->FindVariableTypeNode(*nnodeidPtr, status);
		if (!variableTypeNode.is_set() || status.IsBad())
		{
			nodeIsOfTypeOrSubtypeOfOperand->CopyTo(evaluationResult);
			status = OpcUa_BadFilterOperandInvalid;
			elementResult->StatusCode() = status;
			elementResult->OperandStatusCodes()[0]->Value() = status.Value();
			return status;
		}
	}

	if (status.IsBad())
	{
		nodeIsOfTypeOrSubtypeOfOperand->CopyTo(evaluationResult);
		evaluationResult = 0;
		elementResult->StatusCode() = status;
		elementResult->OperandStatusCodes()[0]->Value() = status.Value();
		return status;
	}

	//target node is of type of operand[0]
	IntrusivePtr_t<NodeId_t> typeNodeId;
	status = AddressSpaceUtilities_t::GetTypeDefinition(node, *addressSpace, typeNodeId);
	if (status.IsBad())
	{
		nodeIsOfTypeOrSubtypeOfOperand->CopyTo(evaluationResult);
		elementResult->StatusCode() = status;
		elementResult->OperandStatusCodes()[0]->Value() = status.Value();
		return status;
	}

	IntrusivePtr_t<NodeId_t> nodeId = RuntimeCast<NodeId_t*>(*dest);
	if (!(*typeNodeId == *nodeId))
	{
		//target node is a subtype of operand[0]
		bool isSubType = false;
		IntrusivePtr_t<const INode_t> parentNode;
		IntrusivePtr_t<const INode_t> currentNode = addressSpace->FindNode(*typeNodeId, status);
		if (!currentNode.is_set() || status.IsBad())
		{
			nodeIsOfTypeOrSubtypeOfOperand->CopyTo(evaluationResult);
			if (status.IsGood())
			{
				status = OpcUa_BadFilterOperandInvalid;
			}
			elementResult->StatusCode() = status;
			elementResult->OperandStatusCodes()[0]->Value() = status.Value();
			return status;
		}

		do
		{
			parentNode = AddressSpaceUtilities_t::GetTarget(*currentNode, *addressSpace, OpcUaId_HasSubtype, false);
			if (parentNode.is_set())
			{
				if (*parentNode->NodeId() == *nodeId)
				{
					isSubType = true;
					break;
				}
				else
				{
					currentNode = parentNode;
				}
			}
		} while (parentNode.is_set());

		if (!isSubType)
		{
			nodeIsOfTypeOrSubtypeOfOperand->CopyTo(evaluationResult);
			status = OpcUa_BadFilterOperandInvalid;
			elementResult->StatusCode() = status;
			elementResult->OperandStatusCodes()[0]->Value() = status.Value();
			return status;
		}
	}

	//If code gets here, target node should be oftype or subtype
	nodeIsOfTypeOrSubtypeOfOperand->Value(true);
	status = nodeIsOfTypeOrSubtypeOfOperand->CopyTo(evaluationResult);

	return status;
}

Status_t ContentFilterElement_OfType_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
	return CopyToDestination(*this, destination);
}

Status_t ContentFilterElement_OfType_t::CopyFrom(const BaseDataType_t& source)
{
	IntrusivePtr_t<const ContentFilterElement_OfType_t> ptr = RuntimeCast<const ContentFilterElement_OfType_t*>(source);
	if (!ptr.is_set())
	{
		return OpcUa_BadTypeMismatch;
	}

	return CopyFrom(*ptr);
}

Status_t ContentFilterElement_OfType_t::CopyFrom(const ContentFilterElement_OfType_t& source)
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

