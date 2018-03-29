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

#include "multi_state_value_discrete_t.h"

#if ((UASDK_USE_HELPERS > 0) && (UASDK_USE_DATA_ACCESS_HELPERS > 0))

#include "opcua_array_ua_t.h"
#include "opcua_enum_value_type_t.h"
#include "opcua_diagnostic_info_t.h"
#include "value_as_text_value_attribute_reader_writer_t.h"

namespace uasdk
{
/*
 * private functions
 */
bool MultiStateValueDiscrete_t::IsDataTypeValid(uint32_t datatype)
{
  if(datatype == OpcUaId_Byte || datatype == OpcUaId_SByte
      || datatype == OpcUaId_UInt16 || datatype == OpcUaId_Int16
      || datatype == OpcUaId_UInt32 || datatype == OpcUaId_Int32
      || datatype == OpcUaId_UInt64 || datatype == OpcUaId_Int64)
  {
    return true;
  }

  return false;
}

Status_t MultiStateValueDiscrete_t::CreateValueAsTextProperty(IntrusivePtr_t<MultiStateValueDiscrete_t>& multiStateValueDiscrete,
                                                              uint32_t propertyIdentifier)
{
  //TODO - Needs testing!
  IntrusivePtr_t<IVariableNode_t> propertyNode = multiStateValueDiscrete->ValueAsTextNode();
  Status_t status = DataItem_t::CreateProperty(*multiStateValueDiscrete, propertyIdentifier,
                                               BROWSE_NAME_VALUE_AS_TEXT, OpcUaId_LocalizedText, propertyNode);
  if(status.IsBad() || !propertyNode.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  IntrusivePtr_t<ValueAsTextValueAttributeReaderWriter_t> valueAsTextReader(new SafeRefCount_t<ValueAsTextValueAttributeReaderWriter_t>());
  if(!valueAsTextReader.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  status = valueAsTextReader->Initialize(multiStateValueDiscrete);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  propertyNode->ValueAttributeReaderWriter(valueAsTextReader);

  return OpcUa_Good;
}

Status_t MultiStateValueDiscrete_t::CreateEnumValuesProperty(MultiStateValueDiscrete_t& multiStateValueDiscrete,
                                                             uint32_t propertyIdentifier,
                                                             const ArrayUA_t<EnumValueType_t>& value)
{
  IntrusivePtr_t<IVariableNode_t> propertyNode = multiStateValueDiscrete.EnumValuesNode();
  IntrusivePtr_t< ArrayUA_t<EnumValueType_t> > destinationVal(new SafeRefCount_t< ArrayUA_t<EnumValueType_t> >());
  if(!destinationVal.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  return DataItem_t::CreatePropertyAndAssignValue(multiStateValueDiscrete, propertyIdentifier, BROWSE_NAME_ENUM_VALUES,
                                                  OpcUaId_EnumValueType, destinationVal, value, propertyNode);
}

IntrusivePtr_t<MultiStateValueDiscrete_t>
MultiStateValueDiscrete_t::CreateMultiStateValueDiscrete(IntrusivePtr_t<IVariableNode_t>& node_,
                                                         IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                         Status_t& result)
{
  IntrusivePtr_t<MultiStateValueDiscrete_t> retVal;
  if(!node_.is_set() || !addressSpace_.is_set() || result.IsBad())
  {
    result = OpcUa_BadInvalidArgument;
    return retVal;
  }

  retVal.reset(new SafeRefCount_t<MultiStateValueDiscrete_t>());
  if(!retVal.is_set())
  {
    result = OpcUa_BadOutOfMemory;
    return retVal;
  }
  retVal->Initialize(node_, addressSpace_);

  result = OpcUa_Good;
  return retVal;
}

IntrusivePtr_t<MultiStateValueDiscrete_t>
MultiStateValueDiscrete_t::CreateMultiStateValueDiscreteWithMandatoryProperty(IntrusivePtr_t<IVariableNode_t>& node_,
                                                                              IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                              const MandatoryPropertyNumericIds_t& ids,
                                                                              const ArrayUA_t<EnumValueType_t>& value,
                                                                              Status_t& result)
{
  IntrusivePtr_t<MultiStateValueDiscrete_t> empty;
  IntrusivePtr_t<MultiStateValueDiscrete_t> multiStateValueDiscrete = MultiStateValueDiscrete_t::CreateMultiStateValueDiscrete(node_, addressSpace_, result);
  if(!multiStateValueDiscrete.is_set() || result.IsBad())
  {
    return empty;
  }

  //Add EnumValues Property
  result = MultiStateValueDiscrete_t::CreateEnumValuesProperty(*multiStateValueDiscrete, ids.enumValues, value);
  if(result.IsBad())
  {
    return empty;
  }

  //Add Value as text
  result = MultiStateValueDiscrete_t::CreateValueAsTextProperty(multiStateValueDiscrete, ids.valueAsText);
  if(result.IsBad())
  {
    return empty;
  }

  result = OpcUa_Good;
  return multiStateValueDiscrete;
}

void MultiStateValueDiscrete_t::DeleteProperties(MultiStateValueDiscrete_t& multiStateValueDiscrete)
{
  UASDK_RETURN_IF_NULL(multiStateValueDiscrete.addressSpace);

  IntrusivePtr_t<IVariableNode_t> enumValues = multiStateValueDiscrete.EnumValuesNode();
  IntrusivePtr_t<IVariableNode_t> valueAsText = multiStateValueDiscrete.ValueAsTextNode();

  if(enumValues.is_set() && enumValues->NodeId().is_set())
  {
    multiStateValueDiscrete.addressSpace->RemoveNode( *(enumValues->NodeId()) );
  }

  if(valueAsText.is_set() && valueAsText->NodeId().is_set())
  {
    multiStateValueDiscrete.addressSpace->RemoveNode( *(valueAsText->NodeId()) );
  }
}

/*
 * Protected functions
 */
MultiStateValueDiscrete_t::MultiStateValueDiscrete_t()
{}

/*
 * public function
 */
MultiStateValueDiscrete_t::~MultiStateValueDiscrete_t()
{
  if(deleteNode)
  {
    DeleteProperties(*this);
  }
}

/*
 * Properties
 */
IntrusivePtr_t<IVariableNode_t> MultiStateValueDiscrete_t::EnumValuesNode(void)
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_ENUM_VALUES);
}

IntrusivePtr_t<const IVariableNode_t> MultiStateValueDiscrete_t::EnumValuesNode(void) const
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_ENUM_VALUES);
}

IntrusivePtr_t<const ArrayUA_t<EnumValueType_t> > MultiStateValueDiscrete_t::GetEnumValuesValue(Status_t& result)
{
  IntrusivePtr_t<const ArrayUA_t<EnumValueType_t> > retVal;
  IntrusivePtr_t<const IVariableNode_t> propertyNode = EnumValuesNode();
  if(!propertyNode.is_set() || !propertyNode->Value().is_set() || !propertyNode->Value()->Value().is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return retVal;
  }

  retVal = RuntimeCast<const ArrayUA_t<EnumValueType_t> *>(*( propertyNode->Value()->Value()) );
  if(!retVal.is_set())
  {
    result = OpcUa_BadUnexpectedError;
    return retVal;
  }

  result = OpcUa_Good;
  return retVal;
}

Status_t MultiStateValueDiscrete_t::SetEnumValuesValue(const ArrayUA_t<EnumValueType_t>& value)
{
  return MultiStateValueDiscrete_t::CreateEnumValuesProperty(*this, 0, value);
}

IntrusivePtr_t<IVariableNode_t> MultiStateValueDiscrete_t::ValueAsTextNode(void)
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_VALUE_AS_TEXT);
}

IntrusivePtr_t<const IVariableNode_t> MultiStateValueDiscrete_t::ValueAsTextNode(void) const
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_VALUE_AS_TEXT);
}

IntrusivePtr_t<const LocalizedText_t> MultiStateValueDiscrete_t::GetValueAsTextValue(Status_t& result)
{
  //TODO - needs Testing!
  IntrusivePtr_t<const LocalizedText_t> empty;
  IntrusivePtr_t<const IVariableNode_t> propertyNode = ValueAsTextNode();
  if(!propertyNode.is_set())
  {
    result = OpcUa_BadUnexpectedError;
    return empty;
  }

  TimestampsToReturn_t::Enum_t timestampsToReturn = TimestampsToReturn_t::RETURN_SOURCE;
  ArrayUA_t<String_t> locales;
  Array_t<IndexRange_t> indexRange;
  IntrusivePtr_t<DataValue_t> dataValue;
  IntrusivePtr_t<DiagnosticInfo_t> diagInfo;

  result = propertyNode->ReadValue(0, timestampsToReturn, locales, indexRange, 0, 0, dataValue, diagInfo);
  if(result.IsBad() || !dataValue.is_set() || !dataValue->Value().is_set())
  {
    result = OpcUa_BadUnexpectedError;
    return empty;
  }

  IntrusivePtr_t<const LocalizedText_t> retVal = RuntimeCast<const LocalizedText_t *>( *(dataValue->Value()) );
  if(!retVal.is_set())
  {
    result = OpcUa_BadTypeMismatch;
    return empty;
  }

  result = OpcUa_Good;
  return retVal;
}

/*
 * Wrapper creation
 */
IntrusivePtr_t<MultiStateValueDiscrete_t> MultiStateValueDiscrete_t::Get(const NodeId_t& nodeId,
                                                                         IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                         Status_t& result)
{
  IntrusivePtr_t<MultiStateValueDiscrete_t> empty;
  if(!addressSpace_.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  IntrusivePtr_t<IVariableNode_t> multiStateValueDiscrete = addressSpace_->FindVariableNode(nodeId, result);
  if(result.IsBad() || !multiStateValueDiscrete.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  return Get(multiStateValueDiscrete, addressSpace_, result);
}

IntrusivePtr_t<MultiStateValueDiscrete_t> MultiStateValueDiscrete_t::Get(IntrusivePtr_t<IVariableNode_t>& node_,
                                                                         IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                         Status_t& result)
{
  IntrusivePtr_t<MultiStateValueDiscrete_t> empty;
  if(!node_.is_set() || !addressSpace_.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  result = DataItem_t::CheckHasTypeDefinition(*node_, *addressSpace_, OpcUaId_MultiStateValueDiscreteType);
  if(result.IsBad())
  {
    return empty;
  }

  return MultiStateValueDiscrete_t::CreateMultiStateValueDiscrete(node_, addressSpace_, result);
}

} //namespace uasdk

#endif //UASDK_USE_DATA_ACCESS_HELPERS
