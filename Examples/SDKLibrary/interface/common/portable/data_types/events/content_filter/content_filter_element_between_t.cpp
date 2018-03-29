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

#include "content_filter_element_between_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "opcua_boolean_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(ContentFilterElement_Between_t, ContentFilterElement_t);

ContentFilterElement_Between_t::ContentFilterElement_Between_t() : ContentFilterElement_t(FilterOperator_t::FILTER_OP_BETWEEN)
{
}

ContentFilterElement_Between_t::~ContentFilterElement_Between_t()
{
}

uint32_t  ContentFilterElement_Between_t::MinimumOperandCount(void) const
{
	return 3;
}

uint32_t  ContentFilterElement_Between_t::MaximumOperandCount(void) const
{
	return 3;
}

Status_t ContentFilterElement_Between_t::ApplyFilterElement(const INode_t& node, IContentFilter_t* filter, IntrusivePtr_t<IAttributeAccess_t>& eventAttributes, IntrusivePtr_t<IServerConfiguration_t> configuration, IntrusivePtr_t<BaseDataType_t>& evaluationResult, IntrusivePtr_t<ContentFilterElementResult_t>& elementResult, bool diagnosticsRequested)
{
  IntrusivePtr_t<BaseDataType_t> dest;
  bool convertedToFirstArgType = false;
	bool returnResult = true;//This value will be pushed to out parameter type
  uint16_t namespaceIndex1 = 0;
  uint16_t namespaceIndex2 = 0;
  uint16_t namespaceIndex3 = 0;
  Status_t status = OpcUa_Good;

	status = CheckApplyFilterElementArguments(filter, eventAttributes, evaluationResult, elementResult, diagnosticsRequested);

	if (status.IsBad())
	{
		return status;
	}

	IntrusivePtr_t<BaseDataType_t> value, min, max;
	status = GetValidFilterOperandValue(0, node, filter, eventAttributes, configuration, value, elementResult, diagnosticsRequested);

	if (status.IsBad())
	{
		return status;
	}

	status = GetValidFilterOperandValue(1, node, filter, eventAttributes, configuration, min, elementResult, diagnosticsRequested);

	if (status.IsBad())
	{
		return status;
	}

	status = GetValidFilterOperandValue(2, node, filter, eventAttributes, configuration, max, elementResult, diagnosticsRequested);

	if (status.IsBad())
	{
		return status;
	}

  bool firstArgConversionFail;
  bool secondArgConversionFail;
  if(min->TypeId(namespaceIndex1) != max->TypeId(namespaceIndex2))
  {
    //different type case, convert into the same type first, then compare - try to convert min and max to same type
    status = TypePrecedenceRule(min,
    														max,
																dest,
																convertedToFirstArgType,
																firstArgConversionFail,
																secondArgConversionFail);

    if(status.IsGood())
    {
      if (convertedToFirstArgType)
      {
				//After min and max converted to same type then convert value to either min or max type
				dest->CopyTo(max);
        status = TypePrecedenceRule(min,
        														value,
																		dest,
																		convertedToFirstArgType,
																		firstArgConversionFail,
																		secondArgConversionFail);

				if (status.IsGood())
				{
					if (convertedToFirstArgType == false)//If min got converted to value type instead of value to min type then convert max also to value type
					{
						dest->CopyTo(min);
						status = TypePrecedenceRule(max,
																				value,
																				dest,
																				convertedToFirstArgType,
																				firstArgConversionFail,
																				secondArgConversionFail);
						if (status.IsBad())
						{
							if (firstArgConversionFail)
							{
								elementResult->OperandStatusCodes()[2]->Value() = status.Value();
							}

							if (secondArgConversionFail)
							{
								elementResult->OperandStatusCodes()[0]->Value() = status.Value();
							}
						}
						else
						{
							//value got converted to max type
							if (convertedToFirstArgType)
							{
								dest->CopyTo(value);
							}
							else//max got converted to value type
							{ 
								dest->CopyTo(max);
							}
						}
					}
					else
					{
						dest->CopyTo(value);//value got converted to min type
					}
				}
				else
				{
					if (firstArgConversionFail)
					{
						elementResult->OperandStatusCodes()[1]->Value() = status.Value();
					}

					if (secondArgConversionFail)
					{
						elementResult->OperandStatusCodes()[0]->Value() = status.Value();
					}
				}
      }
      else
      {
				//value could not be converted to min or max type. Try to convert max to value type
				dest->CopyTo(min);
        status = TypePrecedenceRule(max,
        														value,
																		dest,
																		convertedToFirstArgType,
																		firstArgConversionFail,
																		secondArgConversionFail);

			if (status.IsGood())
			{
				if (convertedToFirstArgType == false)//If max got converted to value type then convert min also to value type
				{
					//As max got converted to value type, need to convert min also to value type
					dest->CopyTo(max);
					status = TypePrecedenceRule(min,
																			value,
																			dest,
																			convertedToFirstArgType,
																			firstArgConversionFail,
																			secondArgConversionFail);

					if (status.IsBad())
					{
						if (firstArgConversionFail)
						{
							elementResult->OperandStatusCodes()[1]->Value() = status.Value();
						}

						if (secondArgConversionFail)
						{
							elementResult->OperandStatusCodes()[0]->Value() = status.Value();
						}
					}
					else
					{						
						if (convertedToFirstArgType)//value got converted to min type
						{
							dest->CopyTo(value);
						}
						else//min got converted to value type
						{
							dest->CopyTo(min);
						}
					}
				}
				else
				{
					dest->CopyTo(value);//value got converted to max type
				}
			}
			else
			{
				if (firstArgConversionFail)
				{
					elementResult->OperandStatusCodes()[2]->Value() = status.Value();
				}

				if (secondArgConversionFail)
				{
					elementResult->OperandStatusCodes()[0]->Value() = status.Value();
				}
			}
      }
    }
		else
		{
			if (firstArgConversionFail)
			{
				elementResult->OperandStatusCodes()[1]->Value() = status.Value();
			}

			if (secondArgConversionFail)
			{
				elementResult->OperandStatusCodes()[2]->Value() = status.Value();
			}
		}
  }
  else if(min->TypeId(namespaceIndex1) != value->TypeId(namespaceIndex3))//Check value is similar to min. At this point, min and max are of same type.
  {
		//Try to convert min and value to same type
    status = TypePrecedenceRule(min,
    														value,
																dest,
																convertedToFirstArgType,
																firstArgConversionFail,
																secondArgConversionFail);

		if (status.IsGood())
		{
			if (convertedToFirstArgType == false)//If min got converted to value type then convert max also to value type
			{
				//min got converted to value type. Hence convert max also to value type
				dest->CopyTo(min);
				status = TypePrecedenceRule(max,
																		value,
																		dest,
																		convertedToFirstArgType,
																		firstArgConversionFail,
																		secondArgConversionFail);

				if (status.IsBad())
				{
					if (firstArgConversionFail)
					{
						elementResult->OperandStatusCodes()[2]->Value() = status.Value();
					}

					if (secondArgConversionFail)
					{
						elementResult->OperandStatusCodes()[0]->Value() = status.Value();
					}
				}
				else
				{					
					if (convertedToFirstArgType)//value got converted to max type
					{
						dest->CopyTo(value);
					}
					else//max got converted to value type
					{
						dest->CopyTo(max);
					}
				}
			}
			else//value got converted to min type
			{
				dest->CopyTo(value);
			}
		}
		else
		{
			if (firstArgConversionFail)
			{
				elementResult->OperandStatusCodes()[1]->Value() = status.Value();
			}

			if (secondArgConversionFail)
			{
				elementResult->OperandStatusCodes()[0]->Value() = status.Value();
			}
		}
  }

	//All types should be same if we reached here and status is Good
  if(status.IsGood())
  {
		if((*value > *min || *value == *min) && 
			(*max > *value || *max == *value))
    {
      status = OpcUa_Good;
			returnResult = true;
    }
    else
    {
			returnResult = false;
    }
  }

	//Setting the out paramaters
	if (status.IsGood())
	{
		IntrusivePtr_t<Boolean_t> result = new SafeRefCount_t<Boolean_t>();
		if (!result.is_set())
		{
			status = OpcUa_BadOutOfMemory;
		}
		else
		{
			status = result->Value(returnResult);

			if (status.IsGood())
			{
				status = result->CopyTo(evaluationResult);
			}
		}
	}

	elementResult->StatusCode() = status;
  //Fill the result if any failure occurred after Type Conversion
  if(status.IsBad())
  {
		elementResult->OperandStatusCodes()[0]->Value() = status.Value();
		elementResult->OperandStatusCodes()[1]->Value() = status.Value();
		elementResult->OperandStatusCodes()[2]->Value() = status.Value();
  }

  return status;
}

Status_t ContentFilterElement_Between_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
	return CopyToDestination(*this, destination);
}

Status_t ContentFilterElement_Between_t::CopyFrom(const BaseDataType_t& source)
{
	IntrusivePtr_t<const ContentFilterElement_Between_t> ptr = RuntimeCast<const ContentFilterElement_Between_t *>(source);
	if (!ptr.is_set())
	{
		return OpcUa_BadTypeMismatch;
	}

	return CopyFrom(*ptr);
}

Status_t ContentFilterElement_Between_t::CopyFrom(const ContentFilterElement_Between_t& source)
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

