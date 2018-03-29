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

#include "content_filter_element_bitwise_and_t.h"

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

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(ContentFilterElement_BitwiseAnd_t, ContentFilterElement_t);

ContentFilterElement_BitwiseAnd_t::ContentFilterElement_BitwiseAnd_t() : ContentFilterElement_t(FilterOperator_t::FILTER_OP_BITWISEAND)
{
}

ContentFilterElement_BitwiseAnd_t::~ContentFilterElement_BitwiseAnd_t()
{
}

uint32_t  ContentFilterElement_BitwiseAnd_t::MinimumOperandCount(void) const
{
	return 2;
}

uint32_t  ContentFilterElement_BitwiseAnd_t::MaximumOperandCount(void) const
{
	return 2;
}

Status_t ContentFilterElement_BitwiseAnd_t::ApplyFilterElement(const INode_t& node, IContentFilter_t* filter, IntrusivePtr_t<IAttributeAccess_t>& eventAttributes, IntrusivePtr_t<IServerConfiguration_t> configuration, IntrusivePtr_t<BaseDataType_t>& evaluationResult, IntrusivePtr_t<ContentFilterElementResult_t>& elementResult, bool diagnosticsRequested)
{
	bool isNULL = false;
	Status_t status = OpcUa_Good;

	status = CheckApplyFilterElementArguments(filter, eventAttributes, evaluationResult, elementResult, diagnosticsRequested);

	if (status.IsBad())
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

	status = CheckAndConvertInputValuesToIntegerType(value1, value2, isNULL);

	if (status.IsGood())
	{
		if (false == isNULL)//If it is NULL then do not assign anything to evaluationResult
		{
			//Perform Bitwise AND operation and set the output result
			status = PerformBitwiseAndOperation(value1, value2, evaluationResult);
		}
	}
	else //Fill the result if any failure occurred
	{
		elementResult->StatusCode() = status;
		elementResult->OperandStatusCodes()[0]->Value() = status.Value();
		elementResult->OperandStatusCodes()[1]->Value() = status.Value();
	}

	return status;
}

Status_t ContentFilterElement_BitwiseAnd_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
	return CopyToDestination(*this, destination);
}

Status_t ContentFilterElement_BitwiseAnd_t::CopyFrom(const BaseDataType_t& source)
{
	IntrusivePtr_t<const ContentFilterElement_BitwiseAnd_t> ptr = RuntimeCast<const ContentFilterElement_BitwiseAnd_t *>(source);
	if (!ptr.is_set())
	{
		return OpcUa_BadTypeMismatch;
	}

	return CopyFrom(*ptr);
}

Status_t ContentFilterElement_BitwiseAnd_t::CopyFrom(const ContentFilterElement_BitwiseAnd_t& source)
{
	Status_t status = FilterOperands().CopyFrom(source.FilterOperands());
	if (status.IsBad())
	{
		return status;
	}

	return OpcUa_Good;
}

Status_t ContentFilterElement_BitwiseAnd_t::PerformBitwiseAndOperation(IntrusivePtr_t<BaseDataType_t> value1, IntrusivePtr_t<BaseDataType_t> value2, IntrusivePtr_t<BaseDataType_t>& evaluationResult)
{
	//This method should be used when both value1 and value2 are of same type
	Status_t status = OpcUa_BadNothingToDo;
	uint16_t namespaceIndex = 0;
	IntrusivePtr_t<Int16_t> i16_1, i16_2, i16Result;
	IntrusivePtr_t<Int32_t> i32_1, i32_2, i32Result;
	IntrusivePtr_t<Int64_t> i64_1, i64_2, i64Result;

	switch (value1->TypeId(namespaceIndex))
	{
	case OpcUaId_Int16:
		{
			i16Result = new SafeRefCount_t<Int16_t>();
			if (i16Result.is_set())
			{
				i16_1 = RuntimeCast<Int16_t*>(*value1);
				i16_2 = RuntimeCast<Int16_t*>(*value2);

				if (i16_1.is_set() && i16_2.is_set())
				{
					i16Result->Value(i16_1->Value() & i16_2->Value());
					status = i16Result->CopyTo(evaluationResult);
				}
			}
		}
		break;
	case OpcUaId_Int32:
		{
			i32Result = new SafeRefCount_t<Int32_t>();
			if (i32Result.is_set())
			{
				i32_1 = RuntimeCast<Int32_t*>(*value1);
				i32_2 = RuntimeCast<Int32_t*>(*value2);

				if (i32_1.is_set() && i32_2.is_set())
				{
					i32Result->Value(i32_1->Value() & i32_2->Value());
					status = i32Result->CopyTo(evaluationResult);
				}
			}
		}
		break;
	case OpcUaId_Int64:
		{
			i64Result = new SafeRefCount_t<Int64_t>();
			if (i64Result.is_set())
			{
				i64_1 = RuntimeCast<Int64_t*>(*value1);
				i64_2 = RuntimeCast<Int64_t*>(*value2);

				if (i64_1.is_set() && i64_2.is_set())
				{
					i64Result->Value(i64_1->Value() & i64_2->Value());
					status = i64Result->CopyTo(evaluationResult);
				}
			}
		}
		break;
	default:
		status = OpcUa_BadNothingToDo;
		break;
	}

	return status;
}

} // namespace uasdk

#endif // UASDK_INCLUDE_EVENTS

