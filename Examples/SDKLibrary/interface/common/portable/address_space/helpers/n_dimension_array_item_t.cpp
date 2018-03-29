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

#include "n_dimension_array_item_t.h"

#if ((UASDK_USE_HELPERS > 0) && (UASDK_USE_DATA_ACCESS_HELPERS > 0) && (UASDK_INCLUDE_ADDITIONAL_DA_TYPES > 0))

#include "opcua_string_t.h"
#include "opcua_data_value_t.h"
#include "opcua_array_ua_t.h"
#include "opcua_localized_text_t.h"
#include "opcua_boolean_t.h"

namespace uasdk
{
NDimensionArrayItem_t::NDimensionArrayItem_t()
{}

NDimensionArrayItem_t::~NDimensionArrayItem_t()
{
 if(deleteNode)
 {
   DeleteProperties(*this);
 }
}

Status_t NDimensionArrayItem_t::CreateProperty(NDimensionArrayItem_t& yArrayItem,
                                               uint32_t propertyIdentifier,
                                               const char* propertyName,
                                               uint32_t propertyType,
                                               const ArrayUA_t<AxisInformation_t>& value,
                                               IntrusivePtr_t<IVariableNode_t>& propertyNode)
{
  IntrusivePtr_t<ArrayUA_t<AxisInformation_t> > destinationValue(new SafeRefCount_t<ArrayUA_t<AxisInformation_t> >());
  if(!destinationValue.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  return DataItem_t::CreatePropertyAndAssignValue(yArrayItem, propertyIdentifier, propertyName, propertyType, destinationValue, value, propertyNode);
}

IntrusivePtr_t<NDimensionArrayItem_t> NDimensionArrayItem_t::CreateNDimensionArrayItem(IntrusivePtr_t<IVariableNode_t>& node_,
                                                                                       IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                                       Status_t& result)
{
  IntrusivePtr_t<NDimensionArrayItem_t> retVal;
  if(!node_.is_set() || !addressSpace_.is_set() || result.IsBad())
  {
    result = OpcUa_BadInvalidArgument;
    return retVal;
  }

  IntrusivePtr_t<NDimensionArrayItem_t> yArrayItem(new SafeRefCount_t<NDimensionArrayItem_t>());
  if(!yArrayItem.is_set())
  {
    result = OpcUa_BadOutOfMemory;
    return retVal;
  }
  yArrayItem->Initialize(node_, addressSpace_);

  retVal = yArrayItem;
  result = OpcUa_Good;

  return retVal;
}

IntrusivePtr_t<NDimensionArrayItem_t> NDimensionArrayItem_t::CreateNDimensionArrayWithMandatoryProperty(IntrusivePtr_t<IVariableNode_t> node_,
                                                                                                        IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                                                        const MandatoryPropertyNumericIds_t& mandatoryPropertiesId,
                                                                                                        const MandatoryPropertyValues_t& propertyValues,
                                                                                                        Status_t& result)
{
  IntrusivePtr_t<NDimensionArrayItem_t> empty;
  IntrusivePtr_t<NDimensionArrayItem_t> imageItem = NDimensionArrayItem_t::CreateNDimensionArrayItem(node_, addressSpace_, result);
  if(!imageItem.is_set() || result.IsBad())
  {
    return empty;
  }

  result = ArrayItem_t::CreateArrayMandatoryProperty(*imageItem, mandatoryPropertiesId.arrayItemPropertyNumericId, propertyValues.arrayItemProperty);
  if(result.IsBad())
  {
    return empty;
  }
  {
    IntrusivePtr_t<IVariableNode_t> propertyNode = imageItem->AxisDefinitionNode();
    result = NDimensionArrayItem_t::CreateProperty(*imageItem, mandatoryPropertiesId.axisInformationNumericId, BROWSE_NAME_AXIS_DEFINATION, OpcUaId_AxisInformation, propertyValues.axisInformation, propertyNode);
    if(result.IsBad())
    {
      return empty;
    }
  }

  result = OpcUa_Good;
  return imageItem;
}

IntrusivePtr_t<const ArrayUA_t<AxisInformation_t> > NDimensionArrayItem_t::GetAxisInformationValue(IntrusivePtr_t<const IVariableNode_t>& propertyNode, Status_t& result)
{
  IntrusivePtr_t<const ArrayUA_t<AxisInformation_t> > retVal;
  if(!propertyNode.is_set() || !propertyNode->Value().is_set() || !propertyNode->Value()->Value().is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return retVal;
  }

  retVal = RuntimeCast<const ArrayUA_t<AxisInformation_t> * >(*( propertyNode->Value()->Value()) );
  if(!retVal.is_set())
  {
    result = OpcUa_BadUnexpectedError;
    return retVal;
  }

  result = OpcUa_Good;
  return retVal;
}

void NDimensionArrayItem_t::DeleteProperties(NDimensionArrayItem_t& item)
{
  UASDK_RETURN_IF_NULL(item.addressSpace);

  {
    IntrusivePtr_t<IVariableNode_t> node_ = AxisDefinitionNode();
    if(node_.is_set() && node_->NodeId().is_set())
    {
      item.addressSpace->RemoveNode( *(node_->NodeId()) );
    }
  }
}

/*
 * Properties
 */
IntrusivePtr_t<IVariableNode_t> NDimensionArrayItem_t::AxisDefinitionNode(void)
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_AXIS_DEFINATION);
}

IntrusivePtr_t<const IVariableNode_t> NDimensionArrayItem_t::AxisDefinitionNode(void) const
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_AXIS_DEFINATION);
}

IntrusivePtr_t<const ArrayUA_t<AxisInformation_t> > NDimensionArrayItem_t::GetAxisDefinitionValue(Status_t& result)
{
  IntrusivePtr_t<const IVariableNode_t> propertyNode = AxisDefinitionNode();
  return GetAxisInformationValue(propertyNode, result);
}

Status_t NDimensionArrayItem_t::SetAxisDefinitionValue(const ArrayUA_t<AxisInformation_t>& value)
{
  IntrusivePtr_t<IVariableNode_t> propertyNode = AxisDefinitionNode();

  return NDimensionArrayItem_t::CreateProperty(*this, 0, BROWSE_NAME_AXIS_DEFINATION, OpcUaId_AxisInformation, value, propertyNode);
}

/*
 * Wrapper creation
 */
IntrusivePtr_t<NDimensionArrayItem_t> NDimensionArrayItem_t::Get(const NodeId_t& nodeId,
                                                                 IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                 Status_t& result)
{
  IntrusivePtr_t<NDimensionArrayItem_t> empty;

  if(!addressSpace_.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  IntrusivePtr_t<IVariableNode_t> yArrayItemNode = addressSpace_->FindVariableNode(nodeId, result);
  if(result.IsBad() || !yArrayItemNode.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  return Get(yArrayItemNode, addressSpace_, result);
}

IntrusivePtr_t<NDimensionArrayItem_t> NDimensionArrayItem_t::Get(IntrusivePtr_t<IVariableNode_t>& node_,
                                                                 IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                 Status_t& result)
{
  IntrusivePtr_t<NDimensionArrayItem_t> empty;
  if(!node_.is_set() || !addressSpace_.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  result = DataItem_t::CheckHasTypeDefinition(*node_, *addressSpace_, OpcUaId_NDimensionArrayItemType);
  if(result.IsBad())
  {
    return empty;
  }

  return NDimensionArrayItem_t::CreateNDimensionArrayItem(node_, addressSpace_, result);
}

} //namespace uasdk

#endif //UASDK_USE_DATA_ACCESS_HELPERS