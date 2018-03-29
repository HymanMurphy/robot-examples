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

#include "analog_item_t.h"

#if ((UASDK_USE_HELPERS > 0) && (UASDK_USE_DATA_ACCESS_HELPERS > 0))

#include "opcua_range_t.h"
#include "opcua_eu_information_t.h"
#include "utilities.h"

namespace uasdk
{

/*
 * Private Functions
 */

bool AnalogItem_t::IsDataTypeValid(uint32_t datatype)
{
  if(datatype == OpcUaId_Byte || datatype == OpcUaId_SByte
      || datatype == OpcUaId_UInt16 || datatype == OpcUaId_Int16
      || datatype == OpcUaId_UInt32 || datatype == OpcUaId_Int32
      || datatype == OpcUaId_UInt64 || datatype == OpcUaId_Int64
      || datatype == OpcUaId_Float  || datatype == OpcUaId_Double)
  {
    return true;
  }

  return false;
}

Status_t AnalogItem_t::CreateProperty(AnalogItem_t& analogItem,
                                      uint32_t propertyIdentifier,
                                      const char* propertyName,
                                      uint32_t propertyType,
                                      const BaseDataType_t& value,
                                      IntrusivePtr_t<IVariableNode_t>& propertyNode)
{
  IntrusivePtr_t<BaseDataType_t> destinationVal;

  switch(propertyType)
  {
    case OpcUaId_Range:
      destinationVal.reset(new SafeRefCount_t<Range_t>());
      break;

    case OpcUaId_EUInformation:
      destinationVal.reset(new SafeRefCount_t<EUInformation_t>());
      break;

    default:
      UASDK_RETURN_BAD_STATUS(OpcUa_BadNotSupported);
  }

  if(!destinationVal.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  return DataItem_t::CreatePropertyAndAssignValue(analogItem, propertyIdentifier, propertyName, propertyType, destinationVal, value, propertyNode);
}

Status_t AnalogItem_t::CreateEURangeProperty(AnalogItem_t& analogItem,
                                             uint32_t euRangeIdentifier,
                                             const Range_t& euRangeValue)
{
  IntrusivePtr_t<IVariableNode_t> propertyNode = analogItem.EURangeNode();
  return AnalogItem_t::CreateProperty(analogItem, euRangeIdentifier, BROWSE_NAME_EU_RANGE, OpcUaId_Range, euRangeValue, propertyNode);
}

IntrusivePtr_t<AnalogItem_t> AnalogItem_t::CreateAnalogItem(IntrusivePtr_t<IVariableNode_t>& node_,
                                                            IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                            Status_t& result)
{
  IntrusivePtr_t<AnalogItem_t> retVal;
  if(!node_.is_set() || !addressSpace_.is_set() || result.IsBad())
  {
    result = OpcUa_BadInvalidArgument;
    return retVal;
  }

  retVal.reset(new SafeRefCount_t<AnalogItem_t>());
  if(!retVal.is_set())
  {
    result = OpcUa_BadOutOfMemory;
    return retVal;
  }
  retVal->Initialize(node_, addressSpace_);

  result = OpcUa_Good;
  return retVal;
}

IntrusivePtr_t<AnalogItem_t> AnalogItem_t::CreateAnalogItemWithMandatoryProperty(IntrusivePtr_t<IVariableNode_t>& node_,
                                                                                 IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                                 uint32_t euRangeIdentifier,
                                                                                 const Range_t& euRangeValue,
                                                                                 Status_t& result)
{
  IntrusivePtr_t<AnalogItem_t> empty;
  IntrusivePtr_t<AnalogItem_t> analogItem = AnalogItem_t::CreateAnalogItem(node_, addressSpace_, result);
  if(!analogItem.is_set() || result.IsBad())
  {
    return empty;
  }

  //Add EURange Property
  result = AnalogItem_t::CreateEURangeProperty(*analogItem, euRangeIdentifier, euRangeValue);
  if(result.IsBad())
  {
    return empty;
  }

  result = OpcUa_Good;
  return analogItem;
}

template <typename T>
IntrusivePtr_t<const T> AnalogItem_t::GetPropertyValue(IntrusivePtr_t<const IVariableNode_t>& propertyNode, Status_t& result)
{
  IntrusivePtr_t<const T> retVal;
  if(!propertyNode.is_set() || !propertyNode->Value().is_set() || !propertyNode->Value()->Value().is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return retVal;
  }

  retVal = RuntimeCast<const T *>(*( propertyNode->Value()->Value()) );
  if(!retVal.is_set())
  {
    result = OpcUa_BadUnexpectedError;
    return retVal;
  }

  result = OpcUa_Good;
  return retVal;
}

void AnalogItem_t::DeleteProperties(AnalogItem_t& analogItem)
{
  UASDK_RETURN_IF_NULL(analogItem.addressSpace);

  //Deleting Properties
  IntrusivePtr_t<IVariableNode_t> instrumentRange = analogItem.InstrumentRangeNode();
  IntrusivePtr_t<IVariableNode_t> euRange = analogItem.EURangeNode();
  IntrusivePtr_t<IVariableNode_t> engineeringUnits = analogItem.EngineeringUnitsNode();

  if(instrumentRange.is_set() && instrumentRange->NodeId().is_set())
  {
    analogItem.addressSpace->RemoveNode( *(instrumentRange->NodeId()) );
  }
  if(euRange.is_set() && euRange->NodeId().is_set())
  {
    analogItem.addressSpace->RemoveNode( *(euRange->NodeId()) );
  }
  if(engineeringUnits.is_set() && engineeringUnits->NodeId().is_set())
  {
    analogItem.addressSpace->RemoveNode( *(engineeringUnits->NodeId()) );
  }
}

/*
 * protected functions
 */
AnalogItem_t::AnalogItem_t()
{}

/*
 * Public functions
 */
AnalogItem_t::~AnalogItem_t()
{
  if(deleteNode)
  {
    DeleteProperties(*this);
  }
}

/*
 * Properties
 */
IntrusivePtr_t<IVariableNode_t> AnalogItem_t::EURangeNode(void)
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_EU_RANGE);
}

IntrusivePtr_t<const IVariableNode_t> AnalogItem_t::EURangeNode(void) const
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_EU_RANGE);
}

IntrusivePtr_t<const Range_t> AnalogItem_t::GetEURangeValue(Status_t& result)
{
  IntrusivePtr_t<const IVariableNode_t> propertyNode = EURangeNode();
  return AnalogItem_t::GetPropertyValue<Range_t>(propertyNode, result);
}

Status_t AnalogItem_t::SetEURangeValue(const Range_t& value)
{
  return AnalogItem_t::CreateEURangeProperty(*this, 0, value);
}

Status_t AnalogItem_t::CreateInstrumentRangeProperty(const Range_t& value)
{
  IntrusivePtr_t<IVariableNode_t> propertyNode = InstrumentRangeNode();
  return AnalogItem_t::CreateProperty(*this, 0, BROWSE_NAME_INSTRUMENT_RANGE, OpcUaId_Range, value, propertyNode);
}

Status_t AnalogItem_t::CreateInstrumentRangeProperty(uint32_t nodeIdentifier, const Range_t& value)
{
  IntrusivePtr_t<IVariableNode_t> propertyNode = InstrumentRangeNode();
  return AnalogItem_t::CreateProperty(*this, nodeIdentifier, BROWSE_NAME_INSTRUMENT_RANGE, OpcUaId_Range, value, propertyNode);
}

IntrusivePtr_t<IVariableNode_t> AnalogItem_t::InstrumentRangeNode(void)
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_INSTRUMENT_RANGE);
}

IntrusivePtr_t<const IVariableNode_t> AnalogItem_t::InstrumentRangeNode(void) const
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_INSTRUMENT_RANGE);
}

IntrusivePtr_t<const Range_t> AnalogItem_t::GetInstrumentRangeValue(Status_t& result)
{
  IntrusivePtr_t<const IVariableNode_t> propertyNode = InstrumentRangeNode();
  return AnalogItem_t::GetPropertyValue<Range_t>(propertyNode, result);
}

Status_t AnalogItem_t::SetInstrumentRangeValue(const Range_t& value)
{
  return CreateInstrumentRangeProperty(value);
}

Status_t AnalogItem_t::CreateEngineeringUnitsProperty(const EUInformation_t& value)
{
  IntrusivePtr_t<IVariableNode_t> propertyNode = EngineeringUnitsNode();
  return AnalogItem_t::CreateProperty(*this, 0, BROWSE_NAME_ENGINEERING_UNITS, OpcUaId_EUInformation, value, propertyNode);
}

Status_t AnalogItem_t::CreateEngineeringUnitsProperty(uint32_t nodeIdentifier, const EUInformation_t& value)
{
  IntrusivePtr_t<IVariableNode_t> propertyNode = EngineeringUnitsNode();
  return AnalogItem_t::CreateProperty(*this, nodeIdentifier, BROWSE_NAME_ENGINEERING_UNITS, OpcUaId_EUInformation, value, propertyNode);
}

IntrusivePtr_t<IVariableNode_t> AnalogItem_t::EngineeringUnitsNode(void)
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_ENGINEERING_UNITS);
}
IntrusivePtr_t<const IVariableNode_t> AnalogItem_t::EngineeringUnitsNode(void) const
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_ENGINEERING_UNITS);
}

IntrusivePtr_t<const EUInformation_t> AnalogItem_t::GetEngineeringUnitsValue(Status_t& result)
{
  IntrusivePtr_t<const IVariableNode_t> propertyNode = EngineeringUnitsNode();
  return AnalogItem_t::GetPropertyValue<EUInformation_t>(propertyNode, result);
}

Status_t AnalogItem_t::SetEngineeringUnitsValue(const EUInformation_t& value)
{
  return CreateEngineeringUnitsProperty(value);
}

/*
* Wrapper creation
*/
IntrusivePtr_t<AnalogItem_t> AnalogItem_t::Get(const NodeId_t& nodeId,
                                               IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                               Status_t& result)
{
  IntrusivePtr_t<AnalogItem_t> empty;
  if(!addressSpace_.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  IntrusivePtr_t<IVariableNode_t> anlogItemNode = addressSpace_->FindVariableNode(nodeId, result);
  if(result.IsBad() || !anlogItemNode.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  return Get(anlogItemNode, addressSpace_, result);
}

IntrusivePtr_t<AnalogItem_t> AnalogItem_t::Get(IntrusivePtr_t<IVariableNode_t>& node_,
                                               IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                               Status_t& result)
{
  IntrusivePtr_t<AnalogItem_t> empty;

  if(!node_.is_set() || !addressSpace_.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  result = DataItem_t::CheckHasTypeDefinition(*node_, *addressSpace_, OpcUaId_AnalogItemType);
  if(result.IsBad())
  {
    return empty;
  }

  return AnalogItem_t::CreateAnalogItem(node_, addressSpace_, result);
}

}

#endif //UASDK_USE_DATA_ACCESS_HELPERS