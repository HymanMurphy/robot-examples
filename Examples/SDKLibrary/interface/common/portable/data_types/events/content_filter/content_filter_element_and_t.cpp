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

#include "content_filter_element_and_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "opcua_boolean_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(ContentFilterElement_And_t, ContentFilterElement_t);

ContentFilterElement_And_t::ContentFilterElement_And_t() : ContentFilterElement_t(FilterOperator_t::FILTER_OP_AND)
{
}

ContentFilterElement_And_t::~ContentFilterElement_And_t()
{
}

uint32_t  ContentFilterElement_And_t::MinimumOperandCount(void) const
{
	return 2;
}

uint32_t  ContentFilterElement_And_t::MaximumOperandCount(void) const
{
	return 2;
}

Status_t ContentFilterElement_And_t::ApplyFilterElement(const INode_t& node, IContentFilter_t* filter, IntrusivePtr_t<IAttributeAccess_t>& eventAttributes, IntrusivePtr_t<IServerConfiguration_t> configuration, IntrusivePtr_t<BaseDataType_t>& evaluationResult, IntrusivePtr_t<ContentFilterElementResult_t>& elementResult, bool diagnosticsRequested)
{
	IntrusivePtr_t<BaseDataType_t> dest;
	uint16_t namespaceIndex1 = 0;
	uint16_t namespaceIndex2 = 0;
	Status_t status = OpcUa_Good;
	
	status = CheckApplyFilterElementArguments(filter, eventAttributes, evaluationResult, elementResult, diagnosticsRequested);

	if(status.IsBad())
	{
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

	IntrusivePtr_t<Boolean_t> tempValue = new SafeRefCount_t<Boolean_t>();
	if (!tempValue.is_set())
	{
		status = OpcUa_BadOutOfMemory;
		elementResult->StatusCode() = status;
		elementResult->OperandStatusCodes()[0]->Value() = status.Value();
		elementResult->OperandStatusCodes()[1]->Value() = status.Value();
		return status;
	}

	tempValue->Value(true);
	status = tempValue->CopyTo(dest);
	if (status.IsBad())
	{
	  elementResult->StatusCode() = status;
	  elementResult->OperandStatusCodes()[0]->Value() = status.Value();
	  elementResult->OperandStatusCodes()[1]->Value() = status.Value();
	  return status;
	}

	LogicalTrueTableValue_t aValue = LOGIC_TRUE;
	LogicalTrueTableValue_t bValue = LOGIC_TRUE;
	IntrusivePtr_t<BaseDataType_t> value = tempValue;

	if (value.is_set())
	{
		if (value1->TypeId(namespaceIndex1) != OpcUaId_Boolean)
		{
			status = TypeConversionRule(value1, dest);

			if (status.IsBad())
			{
				aValue = LOGIC_NULL;
			}

			if (LOGIC_NULL != aValue)
			{
				aValue = (*dest == *value) ? LOGIC_TRUE : LOGIC_FALSE;
			}
		}
		else
		{
			aValue = (*value1 == *value) ? LOGIC_TRUE : LOGIC_FALSE;
		}

		if (value2->TypeId(namespaceIndex2) != OpcUaId_Boolean)
		{
			status = TypeConversionRule(value2, dest);

			if (status.IsBad())
			{
				bValue = LOGIC_NULL;
			}

			if (LOGIC_NULL != bValue)
			{
				bValue = (*dest == *value) ? LOGIC_TRUE : LOGIC_FALSE;
			}
		}
		else
		{
			bValue = (*value2 == *value) ? LOGIC_TRUE : LOGIC_FALSE;
		}
	}
	else
	{
		aValue = bValue = LOGIC_NULL;
	}

	LogicalTrueTableValue_t rValue = LogicalAndTruthTable(aValue, bValue);

	//By default, the evaluated value is already null.
	if(rValue != LOGIC_NULL && status.IsGood())//If the rValue is NULL, then leave evaluationResult as blank as the result is NULL
	{
		IntrusivePtr_t<Boolean_t> result = new SafeRefCount_t<Boolean_t>();
		if (!result.is_set())
		{
			status = OpcUa_BadOutOfMemory;
		}
		else
		{
			status = result->Value(rValue == LOGIC_TRUE ? true : false);

			if (status.IsGood())
			{
				status = result->CopyTo(evaluationResult);
			}
		}
	}

	//Fill the result if any failure occurred after Type Conversion
	if (status.IsBad())
	{
	  elementResult->StatusCode() = status;
	}

	return status;
}

Status_t ContentFilterElement_And_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
	return CopyToDestination(*this, destination);
}

Status_t ContentFilterElement_And_t::CopyFrom(const BaseDataType_t& source)
{
	IntrusivePtr_t<const ContentFilterElement_And_t> ptr = RuntimeCast<const ContentFilterElement_And_t*>(source);
	if (!ptr.is_set())
	{
		return OpcUa_BadTypeMismatch;
	}

	return CopyFrom(*ptr);
}

Status_t ContentFilterElement_And_t::CopyFrom(const ContentFilterElement_And_t& source)
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

