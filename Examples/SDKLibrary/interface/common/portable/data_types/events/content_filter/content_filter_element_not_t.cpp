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

#include "content_filter_element_not_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "opcua_boolean_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(ContentFilterElement_Not_t, ContentFilterElement_t);

ContentFilterElement_Not_t::ContentFilterElement_Not_t() : ContentFilterElement_t(FilterOperator_t::FILTER_OP_NOT)
{
}

ContentFilterElement_Not_t::~ContentFilterElement_Not_t()
{
}

uint32_t  ContentFilterElement_Not_t::MinimumOperandCount(void) const
{
	return 1;
}

uint32_t  ContentFilterElement_Not_t::MaximumOperandCount(void) const
{
	return 1;
}

Status_t ContentFilterElement_Not_t::ApplyFilterElement(const INode_t& node, IContentFilter_t* filter, IntrusivePtr_t<IAttributeAccess_t>& eventAttributes, IntrusivePtr_t<IServerConfiguration_t> configuration, IntrusivePtr_t<BaseDataType_t>& evaluationResult, IntrusivePtr_t<ContentFilterElementResult_t>& elementResult, bool diagnosticsRequested)
{
	bool returnResult = true;//This value will be pushed to out parameter type
	bool isNULL = false;
  Status_t status = OpcUa_Good;
  uint16_t namespaceIndex = 0;

	status = CheckApplyFilterElementArguments(filter, eventAttributes, evaluationResult, elementResult, diagnosticsRequested);

	if (status.IsBad())
	{
		return status;
	}

	IntrusivePtr_t<BaseDataType_t> value;
	status = GetValidFilterOperandValue(0, node, filter, eventAttributes, configuration, value, elementResult, diagnosticsRequested);

	if (status.IsBad())
	{
		return status;
	}

  if(value.is_set())
  {
    if(value->TypeId(namespaceIndex) == OpcUaId_Boolean)
    {
      if(*value == (Boolean_t)false)
      {
        status = OpcUa_Good;//similar to bool true
				returnResult = true;
      }
      else
      {
				returnResult = false;
      }
    }
    else
    {
			IntrusivePtr_t<Boolean_t> destValue = new SafeRefCount_t<Boolean_t>();
			if (!destValue.is_set())
      {
				return OpcUa_BadOutOfMemory;
      }

			IntrusivePtr_t<BaseDataType_t> dest;
      status = destValue->CopyTo(dest);

      if (status.IsBad())
		  {
				return status;
		  }

			status = TypeConversionRule(value, dest);
			if (status.IsGood())
			{
				destValue->CopyFrom(*dest);
				if (*destValue == false)
				{
					status = OpcUa_Good;//similar to bool true
					returnResult = true;
				}
				else
				{
					returnResult = false;
				}
			}
			else
			{
				returnResult = false;
				isNULL = true;
			}
    }
  }
  else
  {
    status = OpcUa_BadOutOfMemory;
  }

	//Setting the out paramaters
	if (false == isNULL && status.IsGood())//If NOT Null then assign true/false, else return blank evaluationResult.
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
  if(status.IsBad())
  {
		elementResult->OperandStatusCodes()[0]->Value() = status.Value();
  }

  return status;
}

Status_t ContentFilterElement_Not_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
	return CopyToDestination(*this, destination);
}

Status_t ContentFilterElement_Not_t::CopyFrom(const BaseDataType_t& source)
{
	IntrusivePtr_t<const ContentFilterElement_Not_t> ptr = RuntimeCast<const ContentFilterElement_Not_t*>(source);
	if (!ptr.is_set())
	{
		return OpcUa_BadTypeMismatch;
	}

	return CopyFrom(*ptr);
}

Status_t ContentFilterElement_Not_t::CopyFrom(const ContentFilterElement_Not_t& source)
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

