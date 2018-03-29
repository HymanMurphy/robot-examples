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

#include "content_filter_element_greater_than_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "opcua_boolean_t.h"

namespace uasdk
{
  
UA_DEFINE_RUNTIME_TYPE(ContentFilterElement_GreaterThan_t, ContentFilterElement_t);

ContentFilterElement_GreaterThan_t::ContentFilterElement_GreaterThan_t() : ContentFilterElement_t(FilterOperator_t::FILTER_OP_GREATERTHAN)
{
}

ContentFilterElement_GreaterThan_t::~ContentFilterElement_GreaterThan_t()
{
}

uint32_t  ContentFilterElement_GreaterThan_t::MinimumOperandCount(void) const
{
	return 2;
}

uint32_t  ContentFilterElement_GreaterThan_t::MaximumOperandCount(void) const
{
	return 2;
}

Status_t ContentFilterElement_GreaterThan_t::ApplyFilterElement(const INode_t& node, IContentFilter_t* filter, IntrusivePtr_t<IAttributeAccess_t>& eventAttributes, IntrusivePtr_t<IServerConfiguration_t> configuration, IntrusivePtr_t<BaseDataType_t>& evaluationResult, IntrusivePtr_t<ContentFilterElementResult_t>& elementResult, bool diagnosticsRequested)
{
  IntrusivePtr_t<BaseDataType_t> dest;
  bool convertedToFirstArgType = false;
  uint16_t namespaceIndex1 = 0;
  uint16_t namespaceIndex2 = 0;
	bool returnResult = true;//This value will be pushed to out parameter type
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

  if(value1->TypeId(namespaceIndex1) != value2->TypeId(namespaceIndex2))
  {
		bool firstArgConversionFail;
    bool secondArgConversionFail;

    //different type case, convert into the same type first, then compare
    status = TypePrecedenceRule(value1,
    														value2,
																dest,
																convertedToFirstArgType,
																firstArgConversionFail,
																secondArgConversionFail);


    if(status.IsGood())
    {
      if (convertedToFirstArgType)
      {
        if(!(*value1 > *dest))
        {
					returnResult = false;
        }
      }
      else
      {
        if(!(*dest > *value2))
        {
					returnResult = false;
        }
      }
    }
		else
		{
			if (firstArgConversionFail)
			{
				elementResult->OperandStatusCodes()[0]->Value() = status.Value();
			}

			if (secondArgConversionFail)
			{
				elementResult->OperandStatusCodes()[1]->Value() = status.Value();
			}
		}
  }
  else
  {
    if(!(*value1 > *value2))
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

  //Fill the result if any failure occurred after Type Conversion
  if(status.IsBad())
  {
		elementResult->StatusCode() = status;
		elementResult->OperandStatusCodes()[0]->Value() = status.Value();
		elementResult->OperandStatusCodes()[1]->Value() = status.Value();
  }

  return status;
}

Status_t ContentFilterElement_GreaterThan_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
	return CopyToDestination(*this, destination);
}

Status_t ContentFilterElement_GreaterThan_t::CopyFrom(const BaseDataType_t& source)
{
	IntrusivePtr_t<const ContentFilterElement_GreaterThan_t> ptr = RuntimeCast<const ContentFilterElement_GreaterThan_t*>(source);
	if (!ptr.is_set())
	{
		return OpcUa_BadTypeMismatch;
	}

	return CopyFrom(*ptr);
}

Status_t ContentFilterElement_GreaterThan_t::CopyFrom(const ContentFilterElement_GreaterThan_t& source)
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

