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

#include "content_filter_element_in_list_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "opcua_boolean_t.h"
#include "uaserver_t.h"

namespace uasdk
{
  
UA_DEFINE_RUNTIME_TYPE(ContentFilterElement_InList_t, ContentFilterElement_t);

ContentFilterElement_InList_t::ContentFilterElement_InList_t() : ContentFilterElement_t(FilterOperator_t::FILTER_OP_INLIST)
{
}

ContentFilterElement_InList_t::~ContentFilterElement_InList_t()
{
}

uint32_t  ContentFilterElement_InList_t::MinimumOperandCount(void) const
{
	return 2;
}

uint32_t  ContentFilterElement_InList_t::MaximumOperandCount(void) const
{
	if (serverConfiguration.is_set())
	{
		return serverConfiguration->MaxOperandsInListOperator();
	}
	else
	{
		return 10;
	}
}

Status_t ContentFilterElement_InList_t::ApplyFilterElement(const INode_t& node, IContentFilter_t* filter, IntrusivePtr_t<IAttributeAccess_t>& eventAttributes, IntrusivePtr_t<IServerConfiguration_t> configuration, IntrusivePtr_t<BaseDataType_t>& evaluationResult, IntrusivePtr_t<ContentFilterElementResult_t>& elementResult, bool diagnosticsRequested)
{
	bool returnResult = true;//This value will be pushed to out parameter type
  Status_t status = OpcUa_Good;

	if (!configuration.is_set())
	{
		status = OpcUa_BadNothingToDo;
		elementResult->StatusCode() = status;
		return status;
	}

	serverConfiguration = configuration;

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
		bool firstArgConversionFail;
    bool secondArgConversionFail;

    IntrusivePtr_t<BaseDataType_t> dest;
    bool convertedToFirstArgType = false;

    bool foundElement = false;

		for (uint32_t index = 1; index < FilterOperands().Count(); index++)
		{
			IntrusivePtr_t<BaseDataType_t> temp;
			status = GetValidFilterOperandValue(index, node, filter, eventAttributes, configuration, temp, elementResult, diagnosticsRequested);

			if (status.IsGood())
			{
				status = TypePrecedenceRule(value,
																		temp,
																		dest,
																		convertedToFirstArgType,
																		firstArgConversionFail,
																		secondArgConversionFail);

				if (status.IsGood())
				{
					if (convertedToFirstArgType)
					{
						if (*value == *dest)
						{
							foundElement = true;
							break;
						}
					}
					else
					{
						if (*temp == *dest)
						{
							foundElement = true;
							break;
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
						elementResult->OperandStatusCodes()[index]->Value() = status.Value();
					}
				}
			}
		}

    if(foundElement)
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
    status = OpcUa_BadOutOfMemory;
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
  if(status.IsBad())
  {
		elementResult->OperandStatusCodes()[0]->Value() = status.Value();
  }

  return status;
}
Status_t ContentFilterElement_InList_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
	return CopyToDestination(*this, destination);
}

Status_t ContentFilterElement_InList_t::CopyFrom(const BaseDataType_t& source)
{
	IntrusivePtr_t<const ContentFilterElement_InList_t> ptr = RuntimeCast<const ContentFilterElement_InList_t*>(source);
	if (!ptr.is_set())
	{
		return OpcUa_BadTypeMismatch;
	}

	return CopyFrom(*ptr);
}

Status_t ContentFilterElement_InList_t::CopyFrom(const ContentFilterElement_InList_t& source)
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

