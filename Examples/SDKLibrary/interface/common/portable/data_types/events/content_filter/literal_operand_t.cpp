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

#include "literal_operand_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "opcua_boolean_t.h"
#include "icodec_t.h"

namespace uasdk
{
  
UA_DEFINE_RUNTIME_TYPE(LiteralOperand_t, FilterOperand_t);

LiteralOperand_t::LiteralOperand_t()
{
  IntrusivePtr_t<Boolean_t> bPtr = new SafeRefCount_t<Boolean_t>();
	if (bPtr.is_set())
	{
		bPtr->Value(bool(false));
		bPtr->CopyTo(value);
	}
}

LiteralOperand_t::LiteralOperand_t(IntrusivePtr_t<BaseDataType_t> value_)
{
	if (value_.is_set())
	{
		value = value_;
	}
	else
	{
		IntrusivePtr_t<Boolean_t> bPtr = new SafeRefCount_t<Boolean_t>();
		if (bPtr.is_set())
		{
			bPtr->Value(bool(false));
			bPtr->CopyTo(value);
		}
	}
}

LiteralOperand_t::~LiteralOperand_t()
{
}

bool LiteralOperand_t::operator==(BaseDataType_t const & obj) const
{
	return OperatorEqualTo(*this, obj);
}

bool LiteralOperand_t::operator==(LiteralOperand_t const & obj) const
{
  return (
    (value == obj.value));
}

bool LiteralOperand_t::operator>(LiteralOperand_t const & obj) const
{
  return (
    (value > obj.value));
}

bool LiteralOperand_t::operator>(BaseDataType_t const & obj) const
{
	return OperatorGreaterThan(*this, obj);
}

Status_t LiteralOperand_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
	return CopyToDestination(*this, destination);
}

Status_t LiteralOperand_t::CopyFrom(const BaseDataType_t& source)
{
  IntrusivePtr_t<const LiteralOperand_t> ptr = RuntimeCast<const LiteralOperand_t*>(source);
  if (!ptr.is_set())
  {
    return OpcUa_BadTypeMismatch;
  }

  return CopyFrom(*ptr);
}

Status_t LiteralOperand_t::CopyFrom(const LiteralOperand_t& source)
{
  value = source.value;
  return OpcUa_Good;
}

uint32_t LiteralOperand_t::TypeId(uint16_t& namespaceIndex)  const
{
	namespaceIndex = 0; return TYPE_ID;
}

IntrusivePtr_t<const BaseDataType_t> LiteralOperand_t::Value(void) const
{ 
	return value; 
}

IntrusivePtr_t<BaseDataType_t>& LiteralOperand_t::Value(void)
{ 
	return value; 
}

uint32_t LiteralOperand_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
	namespaceIndex = 0; return OpcUaId_LiteralOperand_Encoding_DefaultBinary;
}

Status_t LiteralOperand_t::GetValue(const INode_t& node, IContentFilter_t* filter, IntrusivePtr_t<IAttributeAccess_t>& eventAttributes, IntrusivePtr_t<IServerConfiguration_t> configuration, IntrusivePtr_t<BaseDataType_t>& value, IntrusivePtr_t<ContentFilterElementResult_t>& elementResult, bool diagnosticsRequested)
{
	UASDK_UNUSED(node);
	UASDK_UNUSED(filter);
	UASDK_UNUSED(eventAttributes);
	UASDK_UNUSED(configuration);
	UASDK_UNUSED(elementResult);
	UASDK_UNUSED(diagnosticsRequested);

	Status_t status = OpcUa_Good;
	if (value.is_set())
	{
		status = OpcUa_BadInvalidArgument;
	}
	else
	{
		value = Value();
	}

	return status;
}

Status_t LiteralOperand_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
	Status_t status = encoder.EncodeVariant(value, buffer);
	if (status.IsBad())
	{
		return status;
	}

  return OpcUa_Good;
}

Status_t LiteralOperand_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, IntrusivePtr_t<LiteralOperand_t>& result)
{
	if (!result.is_set())
	{
		result = new SafeRefCount_t<LiteralOperand_t>();
		if (!result.is_set())
		{
			return OpcUa_BadOutOfMemory;
		}
	}

  Status_t status = BaseDataType_t::Decode(buffer, decoder, result->Value());
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t LiteralOperand_t::Value(IntrusivePtr_t<BaseDataType_t>& value_)
{ 
	if (value_.is_set())
	{
	  value = value_;
	  return OpcUa_Good;
	}
	else
	{
	  return OpcUa_BadInvalidArgument;
	}
}
	
} // namespace uasdk

#endif // UASDK_INCLUDE_EVENTS


