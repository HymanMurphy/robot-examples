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

#include "simple_attribute_operand_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "iaddress_space_t.h"
#include "address_space_utilities_t.h"
#include "attribute_id_mask_t.h"
#include "iobject_node_t.h"
#include "ivariable_node_t.h"
#include "safe_ref_count_t.h"
#include "opcua_node_id_t.h"
#include "inode_t.h"
#include "utilities.h"

namespace uasdk
{
  
UA_DEFINE_RUNTIME_TYPE(SimpleAttributeOperand_t, FilterOperand_t);

SimpleAttributeOperand_t::SimpleAttributeOperand_t()
{
}

SimpleAttributeOperand_t::SimpleAttributeOperand_t(
													 IntrusivePtr_t<NodeId_t> typeId_,
                           ArrayUA_t<QualifiedName_t> browsePath_,
                           IntegerId_t attributeId_,
                           String_t indexRange_) : attributeId(attributeId_)
{
  if (typeId_.is_set())
  {
		typeId = typeId_;
  }

  browsePath.CopyFrom(browsePath_);
  indexRange.CopyFrom(indexRange_);
}

SimpleAttributeOperand_t::~SimpleAttributeOperand_t()
{
}

bool SimpleAttributeOperand_t::operator==(BaseDataType_t const & obj) const
{
	return OperatorEqualTo(*this, obj);
}

bool SimpleAttributeOperand_t::operator==(SimpleAttributeOperand_t const & obj) const
{
  return (
    (typeId == obj.typeId)
    &&(browsePath == obj.browsePath)
    &&(attributeId == obj.attributeId)
    &&(indexRange == obj.indexRange));
}

bool SimpleAttributeOperand_t::operator>(BaseDataType_t const & obj) const
{
	return OperatorGreaterThan(*this, obj);
}

bool SimpleAttributeOperand_t::operator>(SimpleAttributeOperand_t const & obj) const
{
  return (
    (typeId > obj.typeId)
    &&(browsePath > obj.browsePath)
    &&(attributeId > obj.attributeId)
    &&(indexRange > obj.indexRange));
}

Status_t SimpleAttributeOperand_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
	return CopyToDestination(*this, destination);
}

Status_t SimpleAttributeOperand_t::CopyFrom(const BaseDataType_t& source)
{
  IntrusivePtr_t<const SimpleAttributeOperand_t> ptr = RuntimeCast<const SimpleAttributeOperand_t *>(source);
  if (!ptr.is_set())
  {
    return OpcUa_BadTypeMismatch;
  }

  return CopyFrom(*ptr);
}

Status_t SimpleAttributeOperand_t::CopyFrom(const SimpleAttributeOperand_t& source)
{
  if((!source.typeId.is_set()))
  {
    return OpcUa_BadUnexpectedError;
  }

  Status_t status = source.typeId->CopyToNodeId(typeId);
  if (status.IsBad())
  {
    return status;
  }

  status = browsePath.CopyFrom(source.browsePath);
  if (status.IsBad())
  {
    return status;
  }

  status = attributeId.CopyFrom(source.attributeId);
  if (status.IsBad())
  {
    return status;
  }

  status = indexRange.CopyFrom(source.indexRange);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

uint32_t SimpleAttributeOperand_t::TypeId(uint16_t& namespaceIndex)  const
{
	namespaceIndex = 0; return TYPE_ID;
}

IntrusivePtr_t<const NodeId_t> SimpleAttributeOperand_t::TypeId() const
{ 
	return typeId; 
}

IntrusivePtr_t<NodeId_t>& SimpleAttributeOperand_t::TypeId() 
{ 
	return typeId; 
}

const ArrayUA_t<QualifiedName_t>& SimpleAttributeOperand_t::BrowsePath() const 
{ 
	return browsePath;
}

ArrayUA_t<QualifiedName_t>& SimpleAttributeOperand_t::BrowsePath()
{ 
	return browsePath;
}

const IntegerId_t& SimpleAttributeOperand_t::AttributeId() const 
{ 
	return attributeId;
}

IntegerId_t& SimpleAttributeOperand_t::AttributeId() 
{ 
	return attributeId;
}

const String_t& SimpleAttributeOperand_t::IndexRange() const 
{ 
	return indexRange; 
}

String_t& SimpleAttributeOperand_t::IndexRange() 
{ 
	return indexRange; 
}

uint32_t SimpleAttributeOperand_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
	namespaceIndex = 0; return OpcUaId_SimpleAttributeOperand_Encoding_DefaultBinary;
}

Status_t SimpleAttributeOperand_t::GetValue(const INode_t& node, IContentFilter_t* filter, IntrusivePtr_t<IAttributeAccess_t>& eventAttributes, IntrusivePtr_t<IServerConfiguration_t> configuration, IntrusivePtr_t<BaseDataType_t>& value, IntrusivePtr_t<ContentFilterElementResult_t>& elementResult, bool diagnosticsRequested)
{
	UASDK_UNUSED(node);
	UASDK_UNUSED(elementResult);
	UASDK_UNUSED(diagnosticsRequested);

	Status_t status = OpcUa_Good;
	uint16_t namespaceIndex = 0;
	

	if (NULL == filter || value.is_set() || !typeId.is_set() || !eventAttributes.is_set() || Validate().IsBad() || !configuration.is_set())
	{
		return OpcUa_BadInvalidArgument;
	}

  IntrusivePtr_t<IAddressSpace_t> addressSpace = configuration->AddressSpace();
  UASDK_RETURN_UNEXPECTED_IF_NULL(addressSpace);

	//Check if the input is of correct typeId
	UInt32_t* typeID = RuntimeCast<UInt32_t*>(typeId->IdentiferBase());
	if (!typeID)
	{
		return OpcUa_BadFilterOperandInvalid;
	}

	if (!eventAttributes->IsOfType(typeID->Value(), namespaceIndex))
	{
		return OpcUa_BadFilterOperandInvalid;
	}

	value = eventAttributes->AttributeValue(typeID->Value(), browsePath, attributeId.Value(), indexRange, status);

	return status;
}

Status_t SimpleAttributeOperand_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = OpcUa_Good;

  if (!typeId.is_set())
  {
    return OpcUa_BadEncodingError;
  }

  status = typeId->Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = browsePath.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = attributeId.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = indexRange.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t SimpleAttributeOperand_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, IntrusivePtr_t<SimpleAttributeOperand_t>& result)
{
	if (!result.is_set())
	{
		result = new SafeRefCount_t<SimpleAttributeOperand_t>();
		if (!result.is_set())
		{
			return OpcUa_BadOutOfMemory;
		}
	}
	
	Status_t status = NodeId_t::Decode(buffer, decoder, result->TypeId());
  if (status.IsBad())
  {
    return status;
  }

  status = ArrayUA_t<QualifiedName_t>::Decode(buffer, decoder, result->BrowsePath());
  if (status.IsBad())
  {
    return status;
  }

  status = IntegerId_t::Decode(buffer, decoder, result->AttributeId());
  if (status.IsBad())
  {
    return status;
  }

  status = String_t::Decode(buffer, decoder, result->IndexRange());
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t SimpleAttributeOperand_t::TypeId(IntrusivePtr_t<NodeId_t>& id)
{ 
	if (id.is_set())
	{
	  typeId = id;
	  return OpcUa_Good;
	}
	else
	{
	  return OpcUa_BadInvalidArgument;
	}
}

Status_t SimpleAttributeOperand_t::BrowsePath(ArrayUA_t<QualifiedName_t>& path)
{
  Status_t status = browsePath.CopyFrom(path);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t SimpleAttributeOperand_t::AttributeId(IntegerId_t& attrId)
{ 
	attributeId = attrId;
	return OpcUa_Good; 
}

Status_t SimpleAttributeOperand_t::IndexRange(String_t& range)
{
  Status_t status = indexRange.CopyFrom(range);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t SimpleAttributeOperand_t::Validate()
{
	Status_t status = OpcUa_Good;

	if (!(attributeId > AttributeId_t::ATTRIBUTE_ID_INVALID) ||
		attributeId > AttributeId_t::ATTRIBUTE_ID_END)
	{
		UASDK_RETURN_BAD_STATUS(OpcUa_BadAttributeIdInvalid);//SimpleAttributeOperand does not specify a valid AttributeId
	}

	if (!indexRange.IsNull())
	{
		IntrusivePtr_t<ArrayRef_t<IndexRange_t> > tempIndexRange = new SafeRefCount_t<ArrayRef_t<IndexRange_t> >();
		if (!tempIndexRange.is_set())
		{
			UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
		}

		status = Utilities_t::ValidateIndexRange(IndexRange(), *tempIndexRange);
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

		if (!(attributeId == AttributeId_t::ATTRIBUTE_ID_VALUE))
		{			
			UASDK_RETURN_BAD_STATUS(OpcUa_BadIndexRangeInvalid);//SimpleAttributeOperand specifies an IndexRange for an Attribute other than Value
		}
	}

	return status;
}
	
} // namespace uasdk

#endif // UASDK_INCLUDE_EVENTS


