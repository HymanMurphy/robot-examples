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

#include "filter_operand_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "filter_operand_t.h"
#include "element_operand_t.h"
#include "literal_operand_t.h"
#include "attribute_operand_t.h"
#include "simple_attribute_operand_t.h"
#include "ua_binary_codec_t.h"

namespace uasdk
{
  
UA_DEFINE_RUNTIME_TYPE(FilterOperand_t, Structure_t);

uint32_t FilterOperand_t::filterOperandId_encoding_defaultBinary = OpcUaId_ElementOperand_Encoding_DefaultBinary;

FilterOperand_t::FilterOperand_t()
{
}

FilterOperand_t::~FilterOperand_t()
{
}

void FilterOperand_t::FilterOperandId_encoding_defaultBinary(uint32_t filterOperandId_encoding_defaultBinary_)
{ 
	filterOperandId_encoding_defaultBinary = filterOperandId_encoding_defaultBinary_; 
}

Status_t FilterOperand_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, IntrusivePtr_t<FilterOperand_t>& result/*, const uint32_t typeId*/)
{
  Status_t status = OpcUa_Good;

	switch (filterOperandId_encoding_defaultBinary)
	{
	case OpcUaId_ElementOperand_Encoding_DefaultBinary:
	{
		IntrusivePtr_t<ElementOperand_t> temp;
		temp.reset(new RefCount_t<ElementOperand_t>());
		if (!temp.is_set())
		{
			return OpcUa_BadOutOfMemory;
		}
		status = ElementOperand_t::Decode(buffer, decoder, temp);
		if (status.IsGood())
		{
			result = temp;
		}
	}
	break;

	case OpcUaId_LiteralOperand_Encoding_DefaultBinary:
	{
		IntrusivePtr_t<LiteralOperand_t> temp;
		temp.reset(new RefCount_t<LiteralOperand_t>());
		if (!temp.is_set())
		{
			return OpcUa_BadOutOfMemory;
		}
		status = LiteralOperand_t::Decode(buffer, decoder, temp);
		if (status.IsGood())
		{
			result = temp;
		}
	}
	break;

	case OpcUaId_AttributeOperand_Encoding_DefaultBinary:
	{
		IntrusivePtr_t<AttributeOperand_t> temp;
		temp.reset(new RefCount_t<AttributeOperand_t>());
		if (!temp.is_set())
		{
			return OpcUa_BadOutOfMemory;
		}
		status = AttributeOperand_t::Decode(buffer, decoder, temp);
		if (status.IsGood())
		{
			result = temp;
		}
	}
	break;

	case OpcUaId_SimpleAttributeOperand_Encoding_DefaultBinary:
	{
		IntrusivePtr_t<SimpleAttributeOperand_t> temp;
		temp.reset(new RefCount_t<SimpleAttributeOperand_t>());
		if (!temp.is_set())
		{
			return OpcUa_BadOutOfMemory;
		}
		status = SimpleAttributeOperand_t::Decode(buffer, decoder, temp);
		if (status.IsGood())
		{
			result = temp;
		}
	}
	break;

	default:
		//LOG_INFO;
		break;
	}

  return OpcUa_Good;
}
	
} // namespace uasdk

#endif // UASDK_INCLUDE_EVENTS

