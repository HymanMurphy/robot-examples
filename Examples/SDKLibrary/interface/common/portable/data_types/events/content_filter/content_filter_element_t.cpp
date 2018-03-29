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

#include "content_filter_element_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "element_operand_t.h"
#include "literal_operand_t.h"
#include "simple_attribute_operand_t.h"
#include "content_filter_element_and_t.h"
#include "content_filter_element_between_t.h"
#include "content_filter_element_bitwise_and_t.h"
#include "content_filter_element_bitwise_or_t.h"
#include "content_filter_element_cast_t.h"
#include "content_filter_element_equals_t.h"
#include "content_filter_element_greater_than_t.h"
#include "content_filter_element_greater_than_or_equal_t.h"
#include "content_filter_element_in_list_t.h"
#include "content_filter_element_in_view_t.h"
#include "content_filter_element_is_null_t.h"
#include "content_filter_element_less_than_t.h"
#include "content_filter_element_less_than_or_equal_t.h"
#include "content_filter_element_like_t.h"
#include "content_filter_element_not_t.h"
#include "content_filter_element_of_type_t.h"
#include "content_filter_element_or_t.h"
#include "content_filter_element_related_to_t.h"
#include "opcua_boolean_t.h"
#include "opcua_byte_t.h"
#include "opcua_int16_t.h"
#include "opcua_int32_t.h"
#include "opcua_int64_t.h"
#include "opcua_sbyte_t.h"
#include "opcua_uint16_t.h"
#include "opcua_uint32_t.h"
#include "opcua_uint64_t.h"
#include "safe_ref_count_t.h"
#include "opcua_datatype_utilities_t.h"
#include "ua_binary_codec_t.h"
#include "idata_type_node_t.h"

namespace uasdk
{
  
UA_DEFINE_RUNTIME_TYPE(ContentFilterElement_t, Structure_t);

ContentFilterElement_t::ContentFilterElement_t() : filterOperator(FilterOperator_t::FILTER_OP_END)
{
}

ContentFilterElement_t::ContentFilterElement_t(FilterOperator_t::Enum_t operatorType) : filterOperator(operatorType)
{
}

ContentFilterElement_t::~ContentFilterElement_t()
{
}

bool ContentFilterElement_t::operator==(BaseDataType_t const & obj) const
{
	return OperatorEqualTo(*this, obj);
}

bool ContentFilterElement_t::operator==(ContentFilterElement_t const & obj) const
{
  return (
    (FilterOperator() == obj.FilterOperator())
    &&(FilterOperands() == obj.FilterOperands()));
}

bool ContentFilterElement_t::operator>(BaseDataType_t const & obj) const
{
	return OperatorGreaterThan(*this, obj);
}

bool ContentFilterElement_t::operator>(ContentFilterElement_t const & obj) const
{
  return (
    (FilterOperator() > obj.FilterOperator())
    &&(FilterOperands() > obj.FilterOperands()));
}

uint32_t ContentFilterElement_t::TypeId(uint16_t& namespaceIndex)  const
{
	namespaceIndex = 0; return TYPE_ID;
}

uint32_t ContentFilterElement_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
	namespaceIndex = 0; return OpcUaId_ContentFilterElement_Encoding_DefaultBinary;
}

const ArrayUA_t<ExtensibleParameter_t>& ContentFilterElement_t::FilterOperands(void) const 
{ 
	return filterOperands;
}

ArrayUA_t<ExtensibleParameter_t>& ContentFilterElement_t::FilterOperands(void)
{ 
	return filterOperands; 
}

const FilterOperator_t& ContentFilterElement_t::FilterOperator() const
{
	return filterOperator;
}

FilterOperator_t& ContentFilterElement_t::FilterOperator()
{
	return filterOperator;
}

Status_t ContentFilterElement_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = FilterOperator().Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = filterOperands.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t ContentFilterElement_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, IntrusivePtr_t<ContentFilterElement_t>&result)
{  
  FilterOperator_t filterOperator;
  Status_t status;
  
  if (result.is_set())
  {
	  status = OpcUa_BadInvalidArgument;
	  return status;
  }
  
  status = FilterOperator_t::Decode(buffer, decoder, filterOperator);
  if (status.IsBad())
  {
    return status;
  }

  switch (filterOperator.Value())
  {
  case FilterOperator_t::FILTER_OP_AND:
	  result = new RefCount_t<ContentFilterElement_And_t>();
	  break;
  case FilterOperator_t::FILTER_OP_BETWEEN:
	  result = new RefCount_t<ContentFilterElement_Between_t>();
	  break;
  case FilterOperator_t::FILTER_OP_BITWISEAND:
	  result = new RefCount_t<ContentFilterElement_BitwiseAnd_t>();
	  break;
  case FilterOperator_t::FILTER_OP_BITWISEOR:
	  result = new RefCount_t<ContentFilterElement_BitwiseOr_t>();
	  break;
  case FilterOperator_t::FILTER_OP_CAST:
	  result = new RefCount_t<ContentFilterElement_Cast_t>();
	  break;
  case FilterOperator_t::FILTER_OP_EQUAL:
	  result = new RefCount_t<ContentFilterElement_Equals_t>();
	  break;
  case FilterOperator_t::FILTER_OP_GREATERTHAN:
	  result = new RefCount_t<ContentFilterElement_GreaterThan_t>();
	  break;
  case FilterOperator_t::FILTER_OP_GREATERTHANOREQUAL:
	  result = new RefCount_t<ContentFilterElement_GreaterThanOrEqual_t>();
	  break;
  case FilterOperator_t::FILTER_OP_INLIST:
	  result = new RefCount_t<ContentFilterElement_InList_t>();
	  break;
  case FilterOperator_t::FILTER_OP_INVIEW:
	  result = new RefCount_t<ContentFilterElement_InView_t>();
	  break;
  case FilterOperator_t::FILTER_OP_ISNULL:
	  result = new RefCount_t<ContentFilterElement_IsNull_t>();
	  break;
  case FilterOperator_t::FILTER_OP_LESSTHAN:
	  result = new RefCount_t<ContentFilterElement_LessThan_t>();
	  break;
  case FilterOperator_t::FILTER_OP_LESSTHANOREQUAL:
	  result = new RefCount_t<ContentFilterElement_LessThanOrEqual_t>();
	  break;
  case FilterOperator_t::FILTER_OP_LIKE:
	  result = new RefCount_t<ContentFilterElement_Like_t>();
	  break;
  case FilterOperator_t::FILTER_OP_NOT:
	  result = new RefCount_t<ContentFilterElement_Not_t>();
	  break;
  case FilterOperator_t::FILTER_OP_OFTYPE:
	  result = new RefCount_t<ContentFilterElement_OfType_t>();
	  break;
  case FilterOperator_t::FILTER_OP_OR:
	  result = new RefCount_t<ContentFilterElement_Or_t>();
	  break;
  case FilterOperator_t::FILTER_OP_RELATEDTO:
	  result = new RefCount_t<ContentFilterElement_RelatedTo_t>();
	  break;
  
  default:
	  return OpcUa_BadFilterOperatorInvalid;
  }

  if (!result.is_set())
  {
	  return OpcUa_BadOutOfMemory;
  }
  
  status = ArrayUA_t<ExtensibleParameter_t>::Decode(buffer, decoder, result->FilterOperands());
  if (status.IsBad())
  {
    return status;
  }

  if (result->FilterOperands().Size() < result->MinimumOperandCount())
  {
	  return OpcUa_BadFilterOperandCountMismatch;
  }

  return OpcUa_Good;
}

Status_t ContentFilterElement_t::ValidateFilterOperandType(IntrusivePtr_t<BaseDataType_t> operandValue)
{
  uint16_t namespaceIndex;
  Status_t status = OpcUa_Good;

	if (operandValue.is_set())
	{
		switch (operandValue->TypeId(namespaceIndex))
		{
		case  OpcUaId_Boolean:
		case  OpcUaId_Byte:
		case  OpcUaId_ByteString:
		case  OpcUaId_DateTime:
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
		case  OpcUaId_XmlElement:
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

Status_t ContentFilterElement_t::FilterOperands(ArrayUA_t<ExtensibleParameter_t>& filterOperands_)
{
  Status_t status = filterOperands.CopyFrom(filterOperands_);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t ContentFilterElement_t::GetValidFilterOperandValue(uint32_t operandIndex, const INode_t& node, IContentFilter_t* filter, IntrusivePtr_t<IAttributeAccess_t>& eventAttributes, IntrusivePtr_t<IServerConfiguration_t> configuration, IntrusivePtr_t<BaseDataType_t>& value, IntrusivePtr_t<ContentFilterElementResult_t>& elementResult, bool diagnosticsRequested)
{
	Status_t status = OpcUa_Good;

	IntrusivePtr_t<FilterOperand_t> operand = RuntimeCast<FilterOperand_t*>(*(FilterOperands()[operandIndex]->Payload()));
	if (!operand.is_set())
	{
		status = OpcUa_BadFilterOperandInvalid;
		elementResult->StatusCode() = status;
		elementResult->OperandStatusCodes()[operandIndex]->Value() = status.Value();		
	}
	else
	{
		status = operand->GetValue(node, filter, eventAttributes, configuration, value, elementResult, diagnosticsRequested);
		if (status.IsBad())
		{
			elementResult->StatusCode() = status;
			elementResult->OperandStatusCodes()[operandIndex]->Value() = status.Value();
		}
		else
		{
			if (value.is_set())
			{
				status = ValidateFilterOperandType(value);//Validate the operand value type after getting the value successfully
			}

			if (status.IsBad())
			{
				elementResult->StatusCode() = status;
				elementResult->OperandStatusCodes()[operandIndex]->Value() = status.Value();
			}
		}
	}
	return status;
}

LogicalTrueTableValue_t ContentFilterElement_t::LogicalAndTruthTable(LogicalTrueTableValue_t &aValue, LogicalTrueTableValue_t &bValue)
{
	LogicalTrueTableValue_t result = LOGIC_NULL;
	switch (aValue)
	{
	case LOGIC_NULL:
		switch (bValue)
		{
		case LOGIC_NULL:
		case LOGIC_TRUE:
			break;

		case LOGIC_FALSE:
			result = LOGIC_FALSE;
			break;
		}
		break;

	case LOGIC_FALSE:
		result = LOGIC_FALSE;
		break;

	case LOGIC_TRUE:
		switch (bValue)
		{
		case LOGIC_NULL:
			break;

		case LOGIC_FALSE:
			result = LOGIC_FALSE;
			break;

		case LOGIC_TRUE:
			result = LOGIC_TRUE;
			break;
		}
		break;
	}

	return result;
}

LogicalTrueTableValue_t ContentFilterElement_t::LogicalOrTruthTable(LogicalTrueTableValue_t &aValue, LogicalTrueTableValue_t &bValue)
{
	LogicalTrueTableValue_t result = LOGIC_NULL;
	switch (aValue)
	{
	case LOGIC_NULL:
		switch (bValue)
		{
		case LOGIC_NULL:
		case LOGIC_FALSE:
			break;

		case LOGIC_TRUE:
			result = LOGIC_TRUE;
			break;
		}
		break;

	case LOGIC_FALSE:
		switch (bValue)
		{
		case LOGIC_NULL:
			break;

		case LOGIC_FALSE:
			result = LOGIC_FALSE;
			break;

		case LOGIC_TRUE:
			result = LOGIC_TRUE;
			break;
		}
		break;

	case LOGIC_TRUE:
		result = LOGIC_TRUE;
		break;
	}

	return result;
}

Status_t ContentFilterElement_t::CheckApplyFilterElementArguments(
												IContentFilter_t *filter,
												IntrusivePtr_t<IAttributeAccess_t>& eventAttributes,
												IntrusivePtr_t<BaseDataType_t>& evaluationResult,
												IntrusivePtr_t<ContentFilterElementResult_t>& elementResult,
												bool diagnosticsRequested)
{
	UASDK_UNUSED(eventAttributes);

	Status_t status = OpcUa_Good;

	if (evaluationResult.is_set() || filter == NULL)
	{
		status = OpcUa_BadInvalidArgument;
	}
	else  if (FilterOperands().Size() < MinimumOperandCount() ||
						FilterOperands().Size() > MaximumOperandCount())
	{
		// Part4/7.4.2 Table 113 says that operand count mismatch is for
		// less than the correct number of operands only.
		// However Part4/Section 7.4.1 says that too many operands is an error as well
		// It doesn't say which error, or where that error is encounterd.
		// This still makes the most sense.

		status = OpcUa_BadFilterOperandCountMismatch;
	}

	if (status.IsGood())
	{
		elementResult.reset(new RefCount_t<ContentFilterElementResult_t>());
    UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(elementResult);

		//Set up the results properly
		elementResult->OperandStatusCodes().Initialise(FilterOperands().Size());

		if (diagnosticsRequested)
		{
			elementResult->OperandDiagnosticInfos().Initialise(FilterOperands().Size());
		}		

		for (uint32_t i = 0; i < FilterOperands().Size(); ++i)
		{
			elementResult->OperandStatusCodes()[i] = new RefCount_t<StatusCode_t>();
			if (diagnosticsRequested)
			{
				elementResult->OperandDiagnosticInfos()[i] = new RefCount_t<DiagnosticInfo_t>();
			}

			if (!FilterOperands()[i].is_set() || !FilterOperands()[i]->Payload().is_set())
			{
				status = OpcUa_BadFilterElementInvalid;
				elementResult->StatusCode() = OpcUa_BadFilterElementInvalid;
				elementResult->OperandStatusCodes()[i]->Value() = OpcUa_BadFilterOperandInvalid;
			}
			else
			{
				//Default to good until a later problem found.
				elementResult->OperandStatusCodes()[i]->Value() = OpcUa_Good;
			}
		}
		elementResult->StatusCode() = status;
	}

	return status;
}

} // namespace uasdk

#endif // UASDK_INCLUDE_EVENTS
