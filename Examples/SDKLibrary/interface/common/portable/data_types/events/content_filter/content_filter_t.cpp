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

#include "content_filter_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "content_filter_element_result_t.h"
#include "opcua_boolean_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(ContentFilter_t, Structure_t);

ContentFilter_t::ContentFilter_t()
{
}

ContentFilter_t::ContentFilter_t(ArrayUA_t<ContentFilterElement_t> elements_)
{
  elements.CopyFrom(elements_);
}

ContentFilter_t::~ContentFilter_t()
{
}

bool ContentFilter_t::operator==(BaseDataType_t const & obj) const
{
	return OperatorEqualTo(*this, obj);
}

bool ContentFilter_t::operator==(ContentFilter_t const & obj) const
{
  return (elements == obj.elements);
}

bool ContentFilter_t::operator>(BaseDataType_t const & obj) const
{
	return OperatorGreaterThan(*this, obj);
}

bool ContentFilter_t::operator>(ContentFilter_t const & obj) const
{
  return (elements > obj.elements);
}

Status_t ContentFilter_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
	return CopyToDestination(*this, destination);
}

Status_t ContentFilter_t::CopyFrom(const BaseDataType_t& source)
{
  IntrusivePtr_t<const ContentFilter_t> ptr = RuntimeCast<const ContentFilter_t*>(source);
  if (!ptr.is_set())
  {
    return OpcUa_BadTypeMismatch;
  }

  return CopyFrom(*ptr);
}

Status_t ContentFilter_t::CopyFrom(const ContentFilter_t& source)
{
  Status_t status = elements.CopyFrom(source.elements);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

uint32_t ContentFilter_t::TypeId(uint16_t& namespaceIndex)  const
{
	namespaceIndex = 0; return TYPE_ID;
}

uint32_t ContentFilter_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
	namespaceIndex = 0; return OpcUaId_ContentFilter_Encoding_DefaultBinary;
}

const ArrayUA_t<ContentFilterElement_t>& ContentFilter_t::Elements(void) const 
{ 
	return elements; 
}

ArrayUA_t<ContentFilterElement_t>& ContentFilter_t::Elements(void) 
{ 
	return elements;
}

Status_t ContentFilter_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = elements.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t ContentFilter_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, ContentFilter_t& result)
{
  Status_t status = ArrayUA_t<ContentFilterElement_t>::Decode(buffer, decoder, result.Elements());
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t ContentFilter_t::ApplyFilter(const INode_t& node, IntrusivePtr_t<IAttributeAccess_t>& eventAttributes, IntrusivePtr_t<IServerConfiguration_t> configuration, IntrusivePtr_t<ContentFilterResult_t>& resultStructure, IntrusivePtr_t<BaseDataType_t> &evaluatedResult, bool diagnosticsRequested)
{
  Status_t status = OpcUa_Good;
	uint32_t elementsCount = 0;

  if(Elements().Size() < 1)
  {
		return OpcUa_Good;//If no elements then it should return Good as whereClause is not mandatory
  }

  if(resultStructure.is_set() || evaluatedResult.is_set() || !eventAttributes.is_set())
  {
		UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  resultStructure = new RefCount_t<ContentFilterResult_t>();
  if(!resultStructure.is_set())
  {
		UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }  
  
  resultStructure->StatusCode() = status;
	elementsCount = Elements().Size();
  status = resultStructure->ElementResults().Initialise(elementsCount);
  if(status.IsGood())
  {
    if(diagnosticsRequested == true)
    {
      status = resultStructure->ElementDiagnosticInfos().Initialise(elementsCount);
    }
  }  

	if (status.IsGood())
	{
		status = EvaluateFilterElement(0, node, eventAttributes, configuration, evaluatedResult, resultStructure->ElementResults()[0], diagnosticsRequested);//Start with 0th element
	}
  
  return status;
}

Status_t ContentFilter_t::EvaluateFilterElement(uint32_t element, const INode_t& node, IntrusivePtr_t<IAttributeAccess_t>& eventAttributes, IntrusivePtr_t<IServerConfiguration_t> configuration, IntrusivePtr_t<BaseDataType_t> &evaluatedResult, IntrusivePtr_t<ContentFilterElementResult_t>& elementResult, bool diagnosticsRequested)
{
  if (element >= Elements().Count())
  {
    return OpcUa_BadInvalidArgument;
  }
	
  return Elements()[element]->ApplyFilterElement(node, (IContentFilter_t*)this, eventAttributes, configuration, evaluatedResult, elementResult, diagnosticsRequested);
}

Status_t ContentFilter_t::Validate(IntrusivePtr_t<IServerConfiguration_t> configuration, IntrusivePtr_t<ContentFilterResult_t>& contentFilterResult)
{
  if (!configuration.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

	Status_t status = OpcUa_Good;
	uint16_t namespaceIndex = 0;
	bool error = false;

	if (Elements().Size() < 1)
	{
		return status;
	}

	//Clear the previous result		
	contentFilterResult.reset(new RefCount_t<ContentFilterResult_t>());
	if (!contentFilterResult.is_set())
	{
		UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
	}

	uint32_t elementsCount = Elements().Size();
	status = contentFilterResult->ElementResults().Initialise(elementsCount);
	if (status.IsGood())
	{
		status = contentFilterResult->ElementDiagnosticInfos().Initialise(elementsCount);
	}

	if (status.IsBad())
	{
		return status;
	}

	for (uint32_t i = 0; i < elementsCount; ++i)
	{
		if (Elements()[i].is_set())
		{
			//Setup the results
			contentFilterResult->ElementResults()[i] = new RefCount_t<ContentFilterElementResult_t>();
			if (!contentFilterResult->ElementResults()[i].is_set())
			{
				UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
			}

			contentFilterResult->ElementDiagnosticInfos()[i] = new RefCount_t<DiagnosticInfo_t>();
			if (!contentFilterResult->ElementDiagnosticInfos()[i].is_set())
			{
				UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
			}

			uint32_t operandsCount = Elements()[i]->FilterOperands().Size();
			contentFilterResult->ElementResults()[i]->OperandStatusCodes().Initialise(operandsCount);

			uint32_t maxOperandCount = Elements()[i]->MaximumOperandCount();
			if (Elements()[i]->FilterOperator().Value() == FilterOperator_t::FILTER_OP_INLIST)
			{
				maxOperandCount = configuration->MaxOperandsInListOperator();
			}

			if (operandsCount < Elements()[i]->MinimumOperandCount() ||
				operandsCount > maxOperandCount)
			{
				status = OpcUa_BadFilterOperandCountMismatch;
				contentFilterResult->ElementResults()[i]->StatusCode() = status;
				error = true;
			}
			else
			{
				for (uint32_t j = 0; j < operandsCount; j++)
				{
					if (Elements()[i]->FilterOperands()[j].is_set())
					{
						contentFilterResult->ElementResults()[i]->OperandStatusCodes()[j] = new RefCount_t<StatusCode_t>();
						if (!contentFilterResult->ElementResults()[i]->OperandStatusCodes()[j].is_set())
						{
							UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
						}

						if (Elements()[i]->FilterOperands()[j]->TypeId(namespaceIndex) == OpcUaId_LiteralOperand ||
								Elements()[i]->FilterOperands()[j]->TypeId(namespaceIndex) == OpcUaId_ElementOperand ||
								Elements()[i]->FilterOperands()[j]->TypeId(namespaceIndex) == OpcUaId_SimpleAttributeOperand ||
								Elements()[i]->FilterOperands()[j]->TypeId(namespaceIndex) == OpcUaId_AttributeOperand)
						{
							if (Elements()[i]->FilterOperands()[j]->Payload().is_set())
							{
								IntrusivePtr_t<FilterOperand_t> filterOperand = RuntimeCast<FilterOperand_t*>(*Elements()[i]->FilterOperands()[j]->Payload());

								//We can check only till this point. To GetValue() and further validate the values, we need to access address space but
								//during validation it is not known what node will be passed into the filter at run-time.
								if (!filterOperand.is_set())
								{
									status = OpcUa_BadFilterOperandInvalid;
									error = true;
								}
							}
							else
							{
								status = OpcUa_BadFilterOperandInvalid;
								error = true;
							}
						}
						else
						{
							status = OpcUa_BadFilterOperandInvalid;
							error = true;
						}
					}
					else
					{
						status = OpcUa_BadFilterOperandInvalid;
						error = true;
					}
					contentFilterResult->ElementResults()[i]->StatusCode() = status;
					contentFilterResult->ElementResults()[i]->OperandStatusCodes()[j]->Value() = status.Value();
				}
			}
		}
		else
		{
			error = true;
		}
	}	

	//Setting the Global Error Code
	if (error)
	{
		status = OpcUa_BadContentFilterInvalid;
		contentFilterResult->StatusCode() = status.Value();
	}

	return status;
}

Status_t ContentFilter_t::Elements(ArrayUA_t<ContentFilterElement_t>& elements_)
{
  Status_t status = elements.CopyFrom(elements_);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

} // namespace uasdk

#endif // UASDK_INCLUDE_EVENTS

