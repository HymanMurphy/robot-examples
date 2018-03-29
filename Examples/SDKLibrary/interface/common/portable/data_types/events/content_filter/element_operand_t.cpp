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

#include "element_operand_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

namespace uasdk
{
  
UA_DEFINE_RUNTIME_TYPE(ElementOperand_t, FilterOperand_t);

ElementOperand_t::ElementOperand_t():index(0)
{
}

ElementOperand_t::~ElementOperand_t()
{
}

bool ElementOperand_t::operator==(BaseDataType_t const & obj) const
{
	return OperatorEqualTo(*this, obj);
}

bool ElementOperand_t::operator==(ElementOperand_t const & obj) const
{
  return (
    (index == obj.index));
}

bool ElementOperand_t::operator>(BaseDataType_t const & obj) const
{
	return OperatorGreaterThan(*this, obj);
}

bool ElementOperand_t::operator>(ElementOperand_t const & obj) const
{
  return (
    (index > obj.index));
}

Status_t ElementOperand_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
	return CopyToDestination(*this, destination);
}

Status_t ElementOperand_t::CopyFrom(const BaseDataType_t& source)
{
  IntrusivePtr_t<const ElementOperand_t> ptr = RuntimeCast<const ElementOperand_t*>(source);
  if (!ptr.is_set())
  {
    return OpcUa_BadTypeMismatch;
  }

  return CopyFrom(*ptr);
}

Status_t ElementOperand_t::CopyFrom(const ElementOperand_t& source)
{
  index = source.index;
  return OpcUa_Good;
}

uint32_t ElementOperand_t::TypeId(uint16_t& namespaceIndex)  const
{
	namespaceIndex = 0; return TYPE_ID;
}

const UInt32_t& ElementOperand_t::Index() const
{
	return index; 
}

UInt32_t& ElementOperand_t::Index()
{ 
	return index; 
}

uint32_t ElementOperand_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
	namespaceIndex = 0; return OpcUaId_ElementOperand_Encoding_DefaultBinary;
}

Status_t ElementOperand_t::GetValue(const INode_t& node, IContentFilter_t* filter, IntrusivePtr_t<IAttributeAccess_t>& eventAttributes, IntrusivePtr_t<IServerConfiguration_t> configuration, IntrusivePtr_t<BaseDataType_t>& value, IntrusivePtr_t<ContentFilterElementResult_t>& elementResult, bool diagnosticsRequested)
{
	Status_t status = OpcUa_Good;

	if (NULL == filter || value.is_set())
	{
		status = OpcUa_BadInvalidArgument;
	}
	else
	{
		status = filter->EvaluateFilterElement(Index().Value(), node, eventAttributes, configuration, value, elementResult, diagnosticsRequested);
	}
	
	return status;
}

Status_t ElementOperand_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = index.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t ElementOperand_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, IntrusivePtr_t<ElementOperand_t>& result)
{
	if (!result.is_set())
	{
		result = new SafeRefCount_t<ElementOperand_t>();
		if (!result.is_set())
		{
			return OpcUa_BadOutOfMemory;
		}
	}

  Status_t status = UInt32_t::Decode(buffer, decoder, result->Index());
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t ElementOperand_t::Index(UInt32_t& index_)
{ 
	index = index_; return OpcUa_Good;
}

} // namespace uasdk

#endif // UASDK_INCLUDE_EVENTS


