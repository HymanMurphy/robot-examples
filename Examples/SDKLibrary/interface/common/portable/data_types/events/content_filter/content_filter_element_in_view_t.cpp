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

#include "content_filter_element_in_view_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "opcua_boolean_t.h"
#include "opcua_node_id_numeric_t.h"
#include "iaddress_space_t.h"
#include "address_space_utilities_t.h"
#include "iview_node_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(ContentFilterElement_InView_t, ContentFilterElement_t);

ContentFilterElement_InView_t::ContentFilterElement_InView_t() : ContentFilterElement_t(FilterOperator_t::FILTER_OP_INVIEW)
{
}

ContentFilterElement_InView_t::~ContentFilterElement_InView_t()
{
}

uint32_t  ContentFilterElement_InView_t::MinimumOperandCount(void) const
{
	return 1;
}

uint32_t  ContentFilterElement_InView_t::MaximumOperandCount(void) const
{
	return 1;
}

Status_t ContentFilterElement_InView_t::ApplyFilterElement(const INode_t& node, IContentFilter_t* filter, IntrusivePtr_t<IAttributeAccess_t>& eventAttributes, IntrusivePtr_t<IServerConfiguration_t> configuration, IntrusivePtr_t<BaseDataType_t>& evaluationResult, IntrusivePtr_t<ContentFilterElementResult_t>& elementResult, bool diagnosticsRequested)
{
	IntrusivePtr_t<BaseDataType_t> dest;
	Status_t status = OpcUa_Good;

  if (!configuration.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }
	IntrusivePtr_t<IAddressSpace_t> addressSpace = configuration->AddressSpace();
  UASDK_RETURN_UNEXPECTED_IF_NULL(addressSpace);

	IntrusivePtr_t<Boolean_t> nodeInView = new SafeRefCount_t<Boolean_t>();
	if (!nodeInView.is_set())
	{
		status = OpcUa_BadOutOfMemory;
		elementResult->StatusCode() = status;
		elementResult->OperandStatusCodes()[0]->Value() = status.Value();
		return status;
	}

	//Initialize the target node not be in view
	nodeInView->Value(false);

	status = CheckApplyFilterElementArguments(filter, eventAttributes, evaluationResult, elementResult, diagnosticsRequested);
	if (status.IsBad())
	{
		nodeInView->CopyTo(evaluationResult);
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
		nodeInView->CopyTo(evaluationResult);
		status = OpcUa_BadOutOfMemory;
		elementResult->StatusCode() = status;
		elementResult->OperandStatusCodes()[0]->Value() = status.Value();
		return status;
	}

	status = nnodeidPtr->CopyTo(dest);
	if (status.IsBad())
	{
		nodeInView->CopyTo(evaluationResult);
		elementResult->StatusCode() = status;
		elementResult->OperandStatusCodes()[0]->Value() = status.Value();
		return status;
	}

	status = TypeConversionRule(operandValue, dest);
	if (status.IsBad())
	{
		nodeInView->CopyTo(evaluationResult);
		elementResult->StatusCode() = status;
		elementResult->OperandStatusCodes()[0]->Value() = status.Value();
		return status;
	}

	if (!addressSpace.is_set())
	{
		nodeInView->CopyTo(evaluationResult);
		status = OpcUa_BadUnexpectedError;
		elementResult->StatusCode() = status;
		return status;
	}

	IntrusivePtr_t<NodeId_t> nodeIdPtr = RuntimeCast<NodeId_t*>(*dest);
	IntrusivePtr_t<IViewNode_t> viewNode = addressSpace->FindViewNode(*nodeIdPtr, status);
	if (!viewNode.is_set() || status.IsBad())
	{
		nodeInView->CopyTo(evaluationResult);
		status = OpcUa_BadFilterOperandInvalid;
		elementResult->StatusCode() = status;
		elementResult->OperandStatusCodes()[0]->Value() = status.Value();
		return status;
	}

	if (status.IsBad())
	{
		nodeInView->CopyTo(evaluationResult);
		elementResult->StatusCode() = status;
		elementResult->OperandStatusCodes()[0]->Value() = status.Value();
		return status;
	}

	bool isInView = false;
	if (*viewNode->NodeId() == *node.NodeId())
	{
		isInView = true;
	}
	else
	{
		IntrusivePtr_t<const INode_t> currentNode = viewNode;
		IntrusivePtr_t<const INode_t> childNode;
		uint32_t subtypeRefIds[] = { OpcUaId_Organizes, OpcUaId_HasComponent, OpcUaId_HasProperty, OpcUaId_HasEventSource, OpcUaId_HasSubtype };

		//recursively iterate all child nodes of the "viewNode" with Hierarchical References till we found target "node".
		for (uint32_t i = 0; i < sizeof(subtypeRefIds) / 4; i++)
		{
			childNode = AddressSpaceUtilities_t::GetTarget(*currentNode, *addressSpace, subtypeRefIds[i], true);
			if (childNode.is_set())
			{
				if (*childNode->NodeId() == *node.NodeId())
				{
					isInView = true;
				}
				else
				{
					bool found = false;
					status = FindNodeInView(addressSpace, node, childNode, found);
					if (status.IsGood() && found)
					{
						isInView = true;
					}
				}
			}

			if (isInView)
			{
				break;
			}
		}
	}

	if (!isInView)
	{
		nodeInView->CopyTo(evaluationResult);
		status = OpcUa_BadFilterOperandInvalid;
		elementResult->StatusCode() = status;
		elementResult->OperandStatusCodes()[0]->Value() = status.Value();
		return status;
	}

	//If code gets here,  the target node should be in view
	nodeInView->Value(true);
	status = nodeInView->CopyTo(evaluationResult);

	return status;
}

Status_t ContentFilterElement_InView_t::FindNodeInView(IntrusivePtr_t<IAddressSpace_t> addressSpace, const INode_t& targetNode, IntrusivePtr_t<const INode_t> &parentNode, bool &found)
{
   uint32_t i;
   Status_t status = OpcUa_Good;
   uint32_t subtypeRefIds[] = {OpcUaId_Organizes, OpcUaId_HasComponent, OpcUaId_HasProperty, OpcUaId_HasEventSource, OpcUaId_HasSubtype};

   if (!addressSpace.is_set() || !parentNode.is_set() || found)
   {
	  return OpcUa_BadFilterOperandInvalid;
   }

   bool isInView = false;
   for (i = 0; i < sizeof(subtypeRefIds)/4; i++)
   {
		IntrusivePtr_t<const INode_t> childNode = AddressSpaceUtilities_t::GetTarget(*parentNode, *addressSpace, subtypeRefIds[i], true);
		if (childNode.is_set())
		{
		  if (*childNode->NodeId() == *targetNode.NodeId())
		  {
			isInView = true;
			break;
		  }
		  else
		  {
			  bool founded = false;
			  status = FindNodeInView(addressSpace, targetNode, childNode, founded);
			  if (status.IsGood() && founded)
			  {
				 isInView = true;
			  }
		  }
		}

		if (isInView)
		{
			found = true;
			break;
		}
   }

  return status;
}

Status_t ContentFilterElement_InView_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
	return CopyToDestination(*this, destination);
}

Status_t ContentFilterElement_InView_t::CopyFrom(const BaseDataType_t& source)
{
	IntrusivePtr_t<const ContentFilterElement_InView_t> ptr = RuntimeCast<const ContentFilterElement_InView_t*>(source);
	if (!ptr.is_set())
	{
		return OpcUa_BadTypeMismatch;
	}

	return CopyFrom(*ptr);
}

Status_t ContentFilterElement_InView_t::CopyFrom(const ContentFilterElement_InView_t& source)
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
