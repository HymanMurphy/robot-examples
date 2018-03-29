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

#include "array_item_t.h"

#if ((UASDK_USE_HELPERS > 0) && (UASDK_USE_DATA_ACCESS_HELPERS > 0) && (UASDK_INCLUDE_ADDITIONAL_DA_TYPES > 0))

namespace uasdk
{

ArrayItem_t::ArrayItem_t()
{}

ArrayItem_t::~ArrayItem_t()
{
  if(deleteNode)
  {
    DeleteProperties(*this);
  }
}

bool ArrayItem_t::IsDataTypeValid(uint32_t datatype)
{
  if( datatype == OpcUaId_SByte || datatype == OpcUaId_Int16
      || datatype == OpcUaId_Int32 || datatype == OpcUaId_Int64
      || datatype == OpcUaId_Float  || datatype == OpcUaId_Double
      || datatype == OpcUaId_ComplexNumberType  || datatype == OpcUaId_DoubleComplexNumberType)
  {
    return true;
  }
  return false;
}

void ArrayItem_t::DeleteProperties(ArrayItem_t& item)
{
  UASDK_RETURN_IF_NULL(item.addressSpace);

  {
    IntrusivePtr_t<IVariableNode_t> node_ = InstrumentRangeNode();
    if(node_.is_set() && node_->NodeId().is_set())
    {
      item.addressSpace->RemoveNode( *(node_->NodeId()) );
    }
  }
  {
    IntrusivePtr_t<IVariableNode_t> node_ = EURangeNode();
    if(node_.is_set() && node_->NodeId().is_set())
    {
      item.addressSpace->RemoveNode( *(node_->NodeId()) );
    }
  }
  {
    IntrusivePtr_t<IVariableNode_t> node_ = EngineeringUnitsNode();
    if(node_.is_set() && node_->NodeId().is_set())
    {
      item.addressSpace->RemoveNode( *(node_->NodeId()) );
    }
  }
  {
    IntrusivePtr_t<IVariableNode_t> node_ = TitleNode();
    if(node_.is_set() && node_->NodeId().is_set())
    {
      item.addressSpace->RemoveNode( *(node_->NodeId()) );
    }
  }
  {
    IntrusivePtr_t<IVariableNode_t> node_ = AxisScaleTypeNode();
    if(node_.is_set() && node_->NodeId().is_set())
    {
      item.addressSpace->RemoveNode( *(node_->NodeId()) );
    }
  }
}

Status_t ArrayItem_t::CreateArrayMandatoryProperty(ArrayItem_t& item,
                                                   const MandatoryPropertyNumericIds_t& propertyIdentifier,
                                                   const MandatoryPropertyValues_t& value)
{
  Status_t status;

  {
    IntrusivePtr_t<Range_t> destinationValue(new SafeRefCount_t<Range_t>());
    if(!destinationValue.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }
    IntrusivePtr_t<IVariableNode_t> node_ = item.EURangeNode();
    status = DataItem_t::CreatePropertyAndAssignValue(item, propertyIdentifier.euRangeIdentifier, BROWSE_NAME_EU_RANGE, OpcUaId_Range, destinationValue, value.euRange, node_);
    if(status.IsBad())
    {
      return status;
    }
  }

  {
    IntrusivePtr_t<EUInformation_t > destinationValue(new SafeRefCount_t<EUInformation_t >());
    if(!destinationValue.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }
    IntrusivePtr_t<IVariableNode_t> node_ = item.EngineeringUnitsNode();
    status = DataItem_t::CreatePropertyAndAssignValue(item, propertyIdentifier.engineeringUnitsIdentifier, BROWSE_NAME_ENGINEERING_UNITS, OpcUaId_EUInformation, destinationValue, value.engineeringUnits, node_);
    if(status.IsBad())
    {
      return status;
    }
  }

  {
    IntrusivePtr_t<AxisScaleEnumeration_t> destinationValue(new SafeRefCount_t<AxisScaleEnumeration_t>());
    if(!destinationValue.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }
    IntrusivePtr_t<IVariableNode_t> node_ = item.AxisScaleTypeNode();
    status = DataItem_t::CreatePropertyAndAssignValue(item, propertyIdentifier.axisScaleTypeIdentifier, BROWSE_NAME_AXIS_SCALE_TYPE, OpcUaId_Range, destinationValue, value.axisScaleType, node_);
    if(status.IsBad())
    {
      return status;
    }
  }

  {
    IntrusivePtr_t<LocalizedText_t > destinationValue(new SafeRefCount_t<LocalizedText_t >());
    if(!destinationValue.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }
    IntrusivePtr_t<IVariableNode_t> node_ = item.TitleNode();
    status = DataItem_t::CreatePropertyAndAssignValue(item, propertyIdentifier.titleIdentifier, BROWSE_NAME_TITLE, OpcUaId_LocalizedText, destinationValue, value.title, node_);
    if(status.IsBad())
    {
      return status;
    }
  }

  return status;
}

/*
 * Public functions
 */
Status_t ArrayItem_t::CreateInstrumentRangeProperty(const Range_t& value)
{
  IntrusivePtr_t<Range_t> destinationValue(new SafeRefCount_t<Range_t>());
  if(!destinationValue.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  IntrusivePtr_t<IVariableNode_t> propertyNode = InstrumentRangeNode();

  return DataItem_t::CreatePropertyAndAssignValue(*this, 0, BROWSE_NAME_INSTRUMENT_RANGE, OpcUaId_Range, destinationValue, value, propertyNode);
}

Status_t ArrayItem_t::CreateInstrumentRangeProperty(uint32_t nodeIdentifier, const Range_t& value)
{
  IntrusivePtr_t<Range_t> destinationValue(new SafeRefCount_t<Range_t>());
  if(!destinationValue.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  IntrusivePtr_t<IVariableNode_t> propertyNode = InstrumentRangeNode();

  return DataItem_t::CreatePropertyAndAssignValue(*this, nodeIdentifier, BROWSE_NAME_INSTRUMENT_RANGE, OpcUaId_Range, destinationValue, value, propertyNode);
}

IntrusivePtr_t<IVariableNode_t> ArrayItem_t::InstrumentRangeNode(void)
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_INSTRUMENT_RANGE);
}

IntrusivePtr_t<const IVariableNode_t> ArrayItem_t::InstrumentRangeNode(void) const
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_INSTRUMENT_RANGE);
}

IntrusivePtr_t<const Range_t> ArrayItem_t::GetInstrumentRangeValue(Status_t& result)
{
  IntrusivePtr_t<const Range_t> retVal;
  IntrusivePtr_t<const IVariableNode_t> propertyNode = InstrumentRangeNode();
  if(!propertyNode.is_set() || !propertyNode->Value().is_set() || !propertyNode->Value()->Value().is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return retVal;
  }

  retVal = RuntimeCast<const Range_t *>(*( propertyNode->Value()->Value()) );
  if(!retVal.is_set())
  {
    result = OpcUa_BadUnexpectedError;
    return retVal;
  }

  result = OpcUa_Good;
  return retVal;
}

Status_t ArrayItem_t::SetInstrumentRangeValue(const Range_t& value)
{
  return CreateInstrumentRangeProperty(value);
}

IntrusivePtr_t<IVariableNode_t> ArrayItem_t::EURangeNode(void)
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_EU_RANGE);
}

IntrusivePtr_t<const IVariableNode_t> ArrayItem_t::EURangeNode(void) const
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_EU_RANGE);
}

IntrusivePtr_t<const Range_t> ArrayItem_t::GetEURangeValue(Status_t& result)
{
  IntrusivePtr_t<const Range_t> retVal;
  IntrusivePtr_t<const IVariableNode_t> propertyNode = EURangeNode();
  if(!propertyNode.is_set() || !propertyNode->Value().is_set() || !propertyNode->Value()->Value().is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return retVal;
  }

  retVal = RuntimeCast<const Range_t *>(*( propertyNode->Value()->Value()) );
  if(!retVal.is_set())
  {
    result = OpcUa_BadUnexpectedError;
    return retVal;
  }

  result = OpcUa_Good;
  return retVal;
}

Status_t ArrayItem_t::SetEURangeValue(const Range_t& value)
{
  IntrusivePtr_t<Range_t> destinationValue(new SafeRefCount_t<Range_t>());
  if(!destinationValue.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  IntrusivePtr_t<IVariableNode_t> propertyNode = EURangeNode();

  return DataItem_t::CreatePropertyAndAssignValue(*this, 0, BROWSE_NAME_EU_RANGE, OpcUaId_Range, destinationValue, value, propertyNode);
}

IntrusivePtr_t<IVariableNode_t> ArrayItem_t::EngineeringUnitsNode(void)
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_ENGINEERING_UNITS);
}

IntrusivePtr_t<const IVariableNode_t> ArrayItem_t::EngineeringUnitsNode(void) const
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_ENGINEERING_UNITS);
}

IntrusivePtr_t<const EUInformation_t> ArrayItem_t::GetEngineeringUnitsValue(Status_t& result)
{
  IntrusivePtr_t<const EUInformation_t> retVal;
  IntrusivePtr_t<const IVariableNode_t> propertyNode = InstrumentRangeNode();
  if(!propertyNode.is_set() || !propertyNode->Value().is_set() || !propertyNode->Value()->Value().is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return retVal;
  }

  retVal = RuntimeCast< const EUInformation_t * >(*( propertyNode->Value()->Value()) );
  if(!retVal.is_set())
  {
    result = OpcUa_BadUnexpectedError;
    return retVal;
  }

  result = OpcUa_Good;
  return retVal;
}

Status_t ArrayItem_t::SetEngineeringUnitsValue(const EUInformation_t& value)
{
  IntrusivePtr_t<EUInformation_t> destinationValue(new SafeRefCount_t<EUInformation_t>());
  if(!destinationValue.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  IntrusivePtr_t<IVariableNode_t> propertyNode = EngineeringUnitsNode();

  return DataItem_t::CreatePropertyAndAssignValue(*this, 0, BROWSE_NAME_ENGINEERING_UNITS, OpcUaId_EUInformation, destinationValue, value, propertyNode);
}

IntrusivePtr_t<IVariableNode_t> ArrayItem_t::TitleNode(void)
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_TITLE);
}

IntrusivePtr_t<const IVariableNode_t> ArrayItem_t::TitleNode(void) const
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_TITLE);
}

IntrusivePtr_t<const LocalizedText_t> ArrayItem_t::GetTitleValue(Status_t& result)
{
  IntrusivePtr_t<const LocalizedText_t> retVal;
  IntrusivePtr_t<const IVariableNode_t> propertyNode = InstrumentRangeNode();
  if(!propertyNode.is_set() || !propertyNode->Value().is_set() || !propertyNode->Value()->Value().is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return retVal;
  }

  retVal = RuntimeCast<const LocalizedText_t *>(*( propertyNode->Value()->Value()) );
  if(!retVal.is_set())
  {
    result = OpcUa_BadUnexpectedError;
    return retVal;
  }

  result = OpcUa_Good;
  return retVal;
}

Status_t ArrayItem_t::SetTitleValue(const LocalizedText_t& value)
{
  IntrusivePtr_t<LocalizedText_t> destinationValue(new SafeRefCount_t<LocalizedText_t>());
  if(!destinationValue.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  IntrusivePtr_t<IVariableNode_t> propertyNode = TitleNode();

  return DataItem_t::CreatePropertyAndAssignValue(*this, 0, BROWSE_NAME_TITLE, OpcUaId_LocalizedText, destinationValue, value, propertyNode);
}

IntrusivePtr_t<IVariableNode_t> ArrayItem_t::AxisScaleTypeNode(void)
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_AXIS_SCALE_TYPE);
}

IntrusivePtr_t<const IVariableNode_t> ArrayItem_t::AxisScaleTypeNode(void) const
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_AXIS_SCALE_TYPE);
}

IntrusivePtr_t<const AxisScaleEnumeration_t> ArrayItem_t::GetAxisScaleTypeValue(Status_t& result)
{
  IntrusivePtr_t<const AxisScaleEnumeration_t> retVal;
  IntrusivePtr_t<const IVariableNode_t> propertyNode = InstrumentRangeNode();
  if(!propertyNode.is_set() || !propertyNode->Value().is_set() || !propertyNode->Value()->Value().is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return retVal;
  }

  retVal = RuntimeCast<const AxisScaleEnumeration_t *>(*( propertyNode->Value()->Value()) );
  if(!retVal.is_set())
  {
    result = OpcUa_BadUnexpectedError;
    return retVal;
  }

  result = OpcUa_Good;
  return retVal;
}

Status_t ArrayItem_t::SetAxisScaleTypeValue(const AxisScaleEnumeration_t& value)
{
  IntrusivePtr_t<AxisScaleEnumeration_t> destinationValue(new SafeRefCount_t<AxisScaleEnumeration_t>());
  if(!destinationValue.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  IntrusivePtr_t<IVariableNode_t> propertyNode = AxisScaleTypeNode();

  return DataItem_t::CreatePropertyAndAssignValue(*this, 0, BROWSE_NAME_AXIS_SCALE_TYPE, OpcUaId_AxisScaleEnumeration, destinationValue, value, propertyNode);
}

} //namespace uasdk

#endif //UASDK_USE_DATA_ACCESS_HELPERS