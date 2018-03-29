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

#include "content_filter_element_related_to_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "opcua_node_id_numeric_t.h"
#include "opcua_expanded_node_id_t.h"
#include "opcua_boolean_t.h"
#include "address_space_utilities_t.h"
#include "opcua_array_ua_t.h"
#include "content_filter_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(ContentFilterElement_RelatedTo_t, ContentFilterElement_t);

ContentFilterElement_RelatedTo_t::ContentFilterElement_RelatedTo_t() : ContentFilterElement_t(FilterOperator_t::FILTER_OP_RELATEDTO), isElemRefOfRelatedTo(false)
{
}

ContentFilterElement_RelatedTo_t::~ContentFilterElement_RelatedTo_t()
{
}

uint32_t  ContentFilterElement_RelatedTo_t::MinimumOperandCount(void) const
{
	return 6;
}

uint32_t  ContentFilterElement_RelatedTo_t::MaximumOperandCount(void) const
{
	return 6;
}

Status_t ContentFilterElement_RelatedTo_t::ApplyFilterElement(const INode_t& node, IContentFilter_t* filter, IntrusivePtr_t<IAttributeAccess_t>& eventAttributes, IntrusivePtr_t<IServerConfiguration_t> configuration, IntrusivePtr_t<BaseDataType_t>& evaluationResult, IntrusivePtr_t<ContentFilterElementResult_t>& elementResult, bool diagnosticsRequested)
{
	uint32_t i;
	uint32_t hopNumber = 0;
	bool isNodeIdAndNotExpandedNodeId[3] = { true };
	bool resolvingOperandFails[4] = { false };
	//bool isElementReference[2] = { false };
	IntrusivePtr_t<BaseDataType_t> nodeIdList;
	IntrusivePtr_t<BaseDataType_t> dest, dest1, dest2;
	uint16_t namespaceIndex = 0;
	Status_t status = OpcUa_Good;

  if (!configuration.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

	IntrusivePtr_t<IAddressSpace_t> addressSpace = configuration->AddressSpace();
	if (!addressSpace.is_set())
	{
		status = OpcUa_BadNothingToDo;
		elementResult->StatusCode() = status;
		return status;
	}

	IntrusivePtr_t<Boolean_t> relatedToOperationResult = new SafeRefCount_t<Boolean_t>();
	if (!relatedToOperationResult.is_set())
	{
		status = OpcUa_BadOutOfMemory;
		elementResult->StatusCode() = status;
		return status;
	}

	//Initialize the "relatedTo" operation result to false
	relatedToOperationResult->Value(false);

	IntrusivePtr_t<ContentFilter_t> contentFilter = static_cast<ContentFilter_t*>(filter);
	if (!contentFilter.is_set())
	{
		status = OpcUa_BadInvalidArgument;
		elementResult->StatusCode() = status;
		return status;
	}

	status = CheckApplyFilterElementArguments(filter, eventAttributes, evaluationResult, elementResult, diagnosticsRequested);
	if (status.IsBad())
	{
		relatedToOperationResult->CopyTo(evaluationResult);
		return status;
	}

	IntrusivePtr_t<ArrayUA_t<FilterOperand_t> > filterOperands = new SafeRefCount_t<ArrayUA_t<FilterOperand_t> >();
	if (!filterOperands.is_set())
	{
		status = OpcUa_BadOutOfMemory;
		elementResult->StatusCode() = status;
		return status;
	}

	status = filterOperands->Initialise(MaximumOperandCount());
	if (status.IsBad())
	{
		relatedToOperationResult->CopyTo(evaluationResult);
		elementResult->StatusCode() = status;
		return status;
	}

	IntrusivePtr_t<ArrayUA_t<BaseDataType_t> > operandValues = new SafeRefCount_t<ArrayUA_t<BaseDataType_t> >();
	if (!operandValues.is_set())
	{
		status = OpcUa_BadOutOfMemory;
		elementResult->StatusCode() = status;
		return status;
	}

	status = operandValues->Initialise(MaximumOperandCount());
	if (status.IsBad())
	{
		relatedToOperationResult->CopyTo(evaluationResult);
		elementResult->StatusCode() = status;
		return status;
	}

	for (i = 0; i < MaximumOperandCount(); i++)
	{
		(*filterOperands)[i] = 0;
		(*operandValues)[i] = 0;

		status = GetValidFilterOperandValue(i, node, filter, eventAttributes, configuration, (*operandValues)[i], elementResult, diagnosticsRequested);

		if (status.IsBad())
		{
			relatedToOperationResult->CopyTo(evaluationResult);
			return status;
		}
	}

	IntrusivePtr_t<ArrayUA_t<NodeId_t> > nodeids = new SafeRefCount_t<ArrayUA_t<NodeId_t> >();
	if (!nodeids.is_set())
	{
		relatedToOperationResult->CopyTo(evaluationResult);
		status = OpcUa_BadOutOfMemory;
		elementResult->StatusCode() = status;
		return status;
	}

	status = nodeids->Initialise(3);
	if (status.IsBad())
	{
		relatedToOperationResult->CopyTo(evaluationResult);
		elementResult->StatusCode() = status;
		return status;
	}

	IntrusivePtr_t<ArrayUA_t<ExpandedNodeId_t> > expNNodeids = new SafeRefCount_t<ArrayUA_t<ExpandedNodeId_t> >();
	if (!expNNodeids.is_set())
	{
		relatedToOperationResult->CopyTo(evaluationResult);
		status = OpcUa_BadOutOfMemory;
		elementResult->StatusCode() = status;
		return status;
	}

	status = expNNodeids->Initialise(3);
	if (status.IsBad())
	{
		relatedToOperationResult->CopyTo(evaluationResult);
		elementResult->StatusCode() = status;
		return status;
	}

	for (i = 0; i < 3; i++)
	{
		IntrusivePtr_t<NodeIdNumeric_t> nnodeidPtr = new SafeRefCount_t<NodeIdNumeric_t>();
		if (!nnodeidPtr.is_set())
		{
			relatedToOperationResult->CopyTo(evaluationResult);
			status = OpcUa_BadOutOfMemory;
			elementResult->StatusCode() = status;
			return status;
		}

		//initialize both nodeId and expandedNodeid pointer first
		(*nodeids)[i] = nnodeidPtr;
		(*expNNodeids)[i]->Nodeid() = nnodeidPtr;

		if (((*operandValues)[i]->TypeId(namespaceIndex) != OpcUaId_NodeId)
			&& ((*operandValues)[i]->TypeId(namespaceIndex) != OpcUaId_ExpandedNodeId))
		{
			dest = (*nodeids)[i];
			status = TypeConversionRule((*operandValues)[i], dest);
			if (status.IsBad())
			{
				dest1 = (*expNNodeids)[i];
				status = TypeConversionRule((*operandValues)[i], dest1);
				if (status.IsBad())
				{
					resolvingOperandFails[i] = true;
					if (i < 2)
					{
						//operand[0] or operand[1] point to an element Reference
						//check element reference for operand[0] and operand[1]
						IntrusivePtr_t<UInt32_t> elementOperandIndex = new SafeRefCount_t<UInt32_t>();
						if (!elementOperandIndex.is_set())
						{
							relatedToOperationResult->CopyTo(evaluationResult);
							status = OpcUa_BadOutOfMemory;
							elementResult->StatusCode() = status;
							return status;
						}

						dest2 = elementOperandIndex;
						status = TypeConversionRule((*operandValues)[i], dest2);
						if (status.IsGood())
						{
							elementOperandIndex = RuntimeCast<UInt32_t*>(*dest2);

							//the referred to element should be another "RelatedTo" operator
							//(e.g. A is related to B is related to C),
							if ((elementOperandIndex->Value() <= (contentFilter->Elements().Size() - 1)) && (FilterOperator_t::FILTER_OP_RELATEDTO == contentFilter->Elements()[elementOperandIndex->Value()]->FilterOperator().Value()))
							{
								IntrusivePtr_t<ContentFilterElement_RelatedTo_t> relatedToPtr = RuntimeCast<ContentFilterElement_RelatedTo_t *>(*contentFilter->Elements()[elementOperandIndex->Value()]);
								if (!relatedToPtr.is_set())
								{
									relatedToOperationResult->CopyTo(evaluationResult);
									status = OpcUa_BadNothingToDo;
									elementResult->StatusCode() = status;
									elementResult->OperandStatusCodes()[i]->Value() = status.Value();
									return status;
								}

								relatedToPtr->IsElemRefOfRelatedTo(true);
								status = relatedToPtr->ApplyFilterElement(node, filter, eventAttributes, configuration, nodeIdList, elementResult, diagnosticsRequested);
								if (status.IsGood() && nodeIdList.is_set())
								{
									resolvingOperandFails[i] = false;
									//isElementReference[i] = true;

									//transfer "nodeIdList" to nodeid
									//(*nodeids)[i] = (*nodeIdList)[0];
									(*nodeids)[i] = RuntimeCast<NodeId_t*>(*nodeIdList);
									if (!(*nodeids)[i].is_set())
									{
										resolvingOperandFails[i] = true;
									}
								}
							}
						}
					}
				}
				else
				{
					(*expNNodeids)[i] = RuntimeCast<ExpandedNodeId_t *>(*dest1);
					isNodeIdAndNotExpandedNodeId[i] = false;
				}
			}
			else
			{
				(*nodeids)[i] = RuntimeCast<NodeId_t *>(*dest);
			}
		}
		else
		{
			if ((*operandValues)[i]->TypeId(namespaceIndex) == OpcUaId_NodeId)
			{
				(*nodeids)[i] = RuntimeCast<NodeId_t*>(*(*operandValues)[i]);
			}

			if ((*operandValues)[i]->TypeId(namespaceIndex) == OpcUaId_ExpandedNodeId)
			{
				(*expNNodeids)[i] = RuntimeCast<ExpandedNodeId_t*>(*(*operandValues)[i]);
				isNodeIdAndNotExpandedNodeId[i] = false;
			}
		}
	}

	// resolve operand[3] to number of hops (UInt32_t)
	IntrusivePtr_t<UInt32_t> numberOfHops = new SafeRefCount_t<UInt32_t>();
	if (!numberOfHops.is_set())
	{
		relatedToOperationResult->CopyTo(evaluationResult);
		status = OpcUa_BadOutOfMemory;
		elementResult->StatusCode() = status;
		return status;
	}

	dest = numberOfHops;
	status = TypeConversionRule((*operandValues)[3], dest);
	if (status.IsBad())
	{
		resolvingOperandFails[3] = true;
	}
	else
	{
		numberOfHops = RuntimeCast<UInt32_t*>(*dest);
		hopNumber = numberOfHops->Value();
	}

	//If none of the operands [0],[1],[2],[3] resolves to an appropriate value then the result of
	//this operation shall always be False (or an Empty set in the case of a nested RelatedTo operand).
	if (resolvingOperandFails[0] && resolvingOperandFails[1]
		&& resolvingOperandFails[2] && resolvingOperandFails[3])
	{
		relatedToOperationResult->CopyTo(evaluationResult);
		elementResult->StatusCode() = OpcUa_BadFilterOperandInvalid;
		elementResult->OperandStatusCodes()[0]->Value() = status.Value();
		elementResult->OperandStatusCodes()[1]->Value() = status.Value();
		elementResult->OperandStatusCodes()[2]->Value() = status.Value();
		elementResult->OperandStatusCodes()[3]->Value() = status.Value();
		return status;
	}

	if (!addressSpace.is_set())
	{
		relatedToOperationResult->CopyTo(evaluationResult);
		status = OpcUa_BadUnexpectedError;
		elementResult->StatusCode() = status;
		return status;
	}

	// check either operand[0] or operand[1] is an object type or variable type node.
	for (i = 0; i < 2; i++)
	{
		if (!resolvingOperandFails[i])
		{
			IntrusivePtr_t<IObjectTypeNode_t> objectTypeNode = addressSpace->FindObjectTypeNode(*(*nodeids)[i], status);
			if (!objectTypeNode.is_set() || status.IsBad())
			{
				IntrusivePtr_t<IVariableTypeNode_t> variableTypeNode = addressSpace->FindVariableTypeNode(*(*nodeids)[i], status);
				if (!variableTypeNode.is_set() || status.IsBad())
				{
					relatedToOperationResult->CopyTo(evaluationResult);
					elementResult->StatusCode() = OpcUa_BadFilterOperandInvalid;
					elementResult->OperandStatusCodes()[i]->Value() = status.Value();
					return status;
				}
			}
		}
	}

	if (!resolvingOperandFails[2])
	{
		// check that operand[2] is a reference type node.
		IntrusivePtr_t<IReferenceTypeNode_t> referenceTypeNode = addressSpace->FindReferenceTypeNode(*(*nodeids)[2], status);
		if (!referenceTypeNode.is_set() || referenceTypeNode->IsAbstract() || status.IsBad())
		{
			relatedToOperationResult->CopyTo(evaluationResult);
			if (status.IsGood())
			{
				status = OpcUa_BadFilterOperandInvalid;
			}

			elementResult->StatusCode() = status;
			elementResult->OperandStatusCodes()[2]->Value() = status.Value();
			return status;
		}
	}

	// operand[4]
	IntrusivePtr_t<Boolean_t> operand0And1SupportSubtypeOfTypeDef = new SafeRefCount_t<Boolean_t>();
	if (!operand0And1SupportSubtypeOfTypeDef.is_set())
	{
		relatedToOperationResult->CopyTo(evaluationResult);
		status = OpcUa_BadOutOfMemory;
		elementResult->StatusCode() = status;
		return status;
	}
	operand0And1SupportSubtypeOfTypeDef->Value(true);

	dest = operand0And1SupportSubtypeOfTypeDef;
	status = TypeConversionRule((*operandValues)[4], dest);
	if (status.IsBad())
	{
		operand0And1SupportSubtypeOfTypeDef->Value(false);
	}
	else
	{
		operand0And1SupportSubtypeOfTypeDef = RuntimeCast<Boolean_t*>(*dest);
	}

	// operand[5]
	IntrusivePtr_t<Boolean_t> operand2SupportSubtypeOfRefType = new SafeRefCount_t<Boolean_t>();
	if (!operand2SupportSubtypeOfRefType.is_set())
	{
		relatedToOperationResult->CopyTo(evaluationResult);
		status = OpcUa_BadOutOfMemory;
		elementResult->StatusCode() = status;
		return status;
	}
	operand2SupportSubtypeOfRefType->Value(true);

	dest = operand2SupportSubtypeOfRefType;
	status = TypeConversionRule((*operandValues)[5], dest);
	if (status.IsBad())
	{
		operand2SupportSubtypeOfRefType->Value(false);
	}
	else
	{
		operand2SupportSubtypeOfRefType = RuntimeCast<Boolean_t *>(*dest);
	}

	if (!resolvingOperandFails[0])
	{
		//target node is of type of operand[0]
		IntrusivePtr_t<NodeId_t> typeNodeId;
		status = AddressSpaceUtilities_t::GetTypeDefinition(node, *addressSpace, typeNodeId);
		if (status.IsBad())
		{
			relatedToOperationResult->CopyTo(evaluationResult);
			elementResult->StatusCode() = status;
			elementResult->OperandStatusCodes()[0]->Value() = status.Value();
			return status;
		}

		if (!((isNodeIdAndNotExpandedNodeId[0] && (*typeNodeId == *(*nodeids)[0])) || (!isNodeIdAndNotExpandedNodeId[0] && (*typeNodeId == *(*expNNodeids)[0]->Nodeid()))))
		{
			//support subtypes
			if (operand0And1SupportSubtypeOfTypeDef->Value())
			{
				//check subtypes of operand[0]
				bool isSubType = false;
				IntrusivePtr_t<const INode_t> parentNode;
				IntrusivePtr_t<const INode_t> currentNode = addressSpace->FindNode(*typeNodeId, status);
				if (!currentNode.is_set() || status.IsBad())
				{
					relatedToOperationResult->CopyTo(evaluationResult);
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
						if ((isNodeIdAndNotExpandedNodeId[0] && (*parentNode->NodeId() == *(*nodeids)[0])) || (!isNodeIdAndNotExpandedNodeId[0] && (*parentNode->NodeId() == *(*expNNodeids)[0]->Nodeid())))
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
					relatedToOperationResult->CopyTo(evaluationResult);
					status = OpcUa_BadFilterOperandInvalid;
					elementResult->StatusCode() = status;
					elementResult->OperandStatusCodes()[0]->Value() = status.Value();
					return status;
				}
			}
		}
	}

	if (!resolvingOperandFails[1] && !resolvingOperandFails[2] && !resolvingOperandFails[3])
	{
		//target node is related to a NodeId of the type defined in operand[1]
		//by the reference type defined in operand[2]
		IntrusivePtr_t<const INode_t> startNode = node;
		IntrusivePtr_t<const INode_t> startRefNode;
		if (hopNumber > 0)
		{
			IntrusivePtr_t<NodeIdNumeric_t> refNodeIdNumeric = RuntimeCast<NodeIdNumeric_t*>(*(*nodeids)[2]);
			if (!refNodeIdNumeric.is_set())
			{
				relatedToOperationResult->CopyTo(evaluationResult);
				status = OpcUa_BadFilterOperandInvalid;
				elementResult->StatusCode() = status;
				elementResult->OperandStatusCodes()[2]->Value() = status.Value();
				return status;
			}

			uint32_t refTypeId = refNodeIdNumeric->Identifer().Value();
			bool bRelatedTo = false;
			if (operand2SupportSubtypeOfRefType->Value())
			{
				startRefNode = addressSpace->FindNode(*(*nodeids)[2], status);
				if (!startRefNode.is_set() || status.IsBad())
				{
					relatedToOperationResult->CopyTo(evaluationResult);
					if (status.IsGood())
					{
						status = OpcUa_BadFilterOperandInvalid;
					}
					elementResult->StatusCode() = status;
					elementResult->OperandStatusCodes()[2]->Value() = status.Value();
					return status;
				}
			}

			while (!bRelatedTo)
			{
				i = hopNumber;
				bRelatedTo = true;
				while (i > 0)
				{
					IntrusivePtr_t<const INode_t> targetNode = AddressSpaceUtilities_t::GetTarget(*startNode, *addressSpace, refTypeId, true);
					if (!targetNode.is_set())
					{
						bRelatedTo = false;
						break;
					}

					i--;
					if (0 == i)
					{
						IntrusivePtr_t<NodeId_t> typeDefinedNodeId;
						status = AddressSpaceUtilities_t::GetTypeDefinition(*targetNode, *addressSpace, typeDefinedNodeId);
						if (status.IsBad())
						{
							bRelatedTo = false;
							break;
						}

						if (!((isNodeIdAndNotExpandedNodeId[1] && (*typeDefinedNodeId == *(*nodeids)[1]))
								|| (!isNodeIdAndNotExpandedNodeId[1] && (*typeDefinedNodeId == *(*expNNodeids)[1]->Nodeid()))))
						{
							//support subtypes
							if (operand0And1SupportSubtypeOfTypeDef->Value())
							{
								//check subtypes of operand[1]
								bool isSubType = false;
								IntrusivePtr_t<const INode_t> parentNode;
								IntrusivePtr_t<const INode_t> currentNode = addressSpace->FindNode(*typeDefinedNodeId, status);
								if (!currentNode.is_set() || status.IsBad())
								{
									bRelatedTo = false;
									break;
								}

								do
								{
									parentNode = AddressSpaceUtilities_t::GetTarget(*currentNode, *addressSpace, OpcUaId_HasSubtype, false);
									if (parentNode.is_set())
									{
										if ((isNodeIdAndNotExpandedNodeId[1] && (*parentNode->NodeId() == *(*nodeids)[1]))
												|| (!isNodeIdAndNotExpandedNodeId[1] && (*parentNode->NodeId() == (*(*expNNodeids)[1]->Nodeid()))))
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
									bRelatedTo = false;
									break;
								}
							}
						}
					}
					else
					{
						startNode = targetNode;
					}
				}

				if (!bRelatedTo)
				{
					if (operand2SupportSubtypeOfRefType->Value() == 0)
					{
						relatedToOperationResult->CopyTo(evaluationResult);
						if (status.IsGood())
						{
							status = OpcUa_BadFilterOperandInvalid;
						}
						elementResult->StatusCode() = status;
						elementResult->OperandStatusCodes()[1]->Value() = status.Value();
						elementResult->OperandStatusCodes()[2]->Value() = status.Value();
						return status;
					}
					else
					{
						//check subtypes of operand[2]
						IntrusivePtr_t<const INode_t> childRefNode = AddressSpaceUtilities_t::GetTarget(*startRefNode, *addressSpace, OpcUaId_HasSubtype, true);
						if (childRefNode.is_set())
						{
							IntrusivePtr_t<const NodeIdNumeric_t> childRefNodeIdNumeric = RuntimeCast<const NodeIdNumeric_t *>(*childRefNode->NodeId());
							if (!childRefNodeIdNumeric.is_set())
							{
								relatedToOperationResult->CopyTo(evaluationResult);
								status = OpcUa_BadFilterOperandInvalid;
								elementResult->StatusCode() = status;
								elementResult->OperandStatusCodes()[1]->Value() = status.Value();
								elementResult->OperandStatusCodes()[2]->Value() = status.Value();
								return status;
							}

							refTypeId = childRefNodeIdNumeric->Identifer().Value();
							startRefNode = childRefNode;
						}
						else
						{
							relatedToOperationResult->CopyTo(evaluationResult);
							status = OpcUa_BadFilterOperandInvalid;
							elementResult->StatusCode() = status;
							elementResult->OperandStatusCodes()[1]->Value() = status.Value();
							elementResult->OperandStatusCodes()[2]->Value() = status.Value();
							return status;
						}
					}
				}
			}
		}
		else
		{
			//hop number is equal to 0, logical ends without "RelatedTo" relationship
		}
	}

	//If code gets here, the "relatedTo" operation succeeds, so set to true
	relatedToOperationResult->Value(true);
	status = relatedToOperationResult->CopyTo(evaluationResult);

	return status;
}

Status_t ContentFilterElement_RelatedTo_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
	return CopyToDestination(*this, destination);
}

Status_t ContentFilterElement_RelatedTo_t::CopyFrom(const BaseDataType_t& source)
{
	IntrusivePtr_t<const ContentFilterElement_RelatedTo_t> ptr = RuntimeCast<const ContentFilterElement_RelatedTo_t*>(source);
	if (!ptr.is_set())
	{
		return OpcUa_BadTypeMismatch;
	}

	return CopyFrom(*ptr);
}

Status_t ContentFilterElement_RelatedTo_t::CopyFrom(const ContentFilterElement_RelatedTo_t& source)
{
	Status_t status = FilterOperands().CopyFrom(source.FilterOperands());
	if (status.IsBad())
	{
		return status;
	}

	return OpcUa_Good;
}

void ContentFilterElement_RelatedTo_t::IsElemRefOfRelatedTo(bool flag)
{ 
	isElemRefOfRelatedTo = flag; 
}

} // namespace uasdk

#endif // UASDK_INCLUDE_EVENTS

