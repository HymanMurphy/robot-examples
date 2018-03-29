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

#include "xy_array_item_t.h"

#if ((UASDK_USE_HELPERS > 0) && (UASDK_USE_DATA_ACCESS_HELPERS > 0) && (UASDK_INCLUDE_ADDITIONAL_DA_TYPES > 0))

#include "opcua_axis_information_t.h"
#include "opcua_string_t.h"
#include "opcua_data_value_t.h"
#include "opcua_array_ua_t.h"
#include "opcua_localized_text_t.h"
#include "opcua_boolean_t.h"

namespace uasdk
{

XYArrayItem_t::XYArrayItem_t()
{}

XYArrayItem_t::~XYArrayItem_t()
{
  if(deleteNode)
  {
    DeleteProperties(*this);
  }
}

Status_t XYArrayItem_t::CreateProperty(XYArrayItem_t& yArrayItem,
                                      uint32_t propertyIdentifier,
                                      const char* propertyName,
                                      uint32_t propertyType,
                                      const AxisInformation_t& value,
                                      IntrusivePtr_t<IVariableNode_t>& propertyNode)
{
  IntrusivePtr_t<AxisInformation_t> destinationValue(new SafeRefCount_t<AxisInformation_t>());
  if(!destinationValue.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  return DataItem_t::CreatePropertyAndAssignValue(yArrayItem, propertyIdentifier, propertyName, propertyType, destinationValue, value, propertyNode);
}

IntrusivePtr_t<XYArrayItem_t> XYArrayItem_t::CreateXYArrayItem(IntrusivePtr_t<IVariableNode_t>& node_,
                                                               IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                               Status_t& result)
{
  IntrusivePtr_t<XYArrayItem_t> retVal;
  if(!node_.is_set() || !addressSpace_.is_set() || result.IsBad())
  {
    result = OpcUa_BadInvalidArgument;
    return retVal;
  }

  IntrusivePtr_t<XYArrayItem_t> yArrayItem(new SafeRefCount_t<XYArrayItem_t>());
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

IntrusivePtr_t<XYArrayItem_t> XYArrayItem_t::CreateXYArrayWithMandatoryProperty(IntrusivePtr_t<IVariableNode_t> node_,
                                                                                IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                                const MandatoryPropertyNumericIds_t& mandatoryPropertiesId,
                                                                                const MandatoryPropertyValues_t& propertyValues,
                                                                                Status_t& result)
{
  IntrusivePtr_t<XYArrayItem_t> empty;
  IntrusivePtr_t<XYArrayItem_t> xyArrayItem = XYArrayItem_t::CreateXYArrayItem(node_, addressSpace_, result);
  if(!xyArrayItem.is_set() || result.IsBad())
  {
    return empty;
  }

  result = ArrayItem_t::CreateArrayMandatoryProperty(*xyArrayItem, mandatoryPropertiesId.arrayItemPropertyNumericId, propertyValues.arrayItemProperty);
  if(result.IsBad())
  {
    return empty;
  }

  IntrusivePtr_t<IVariableNode_t> propertyNode = xyArrayItem->XAxisDefinitionNode();
  result = XYArrayItem_t::CreateProperty(*xyArrayItem, mandatoryPropertiesId.axisInformationId, BROWSE_NAME_X_AXIS_DEFINATION, OpcUaId_AxisInformation, propertyValues.axisInformation, propertyNode);
  if(result.IsBad())
  {
    return empty;
  }

  result = OpcUa_Good;
  return xyArrayItem;
}

IntrusivePtr_t<const AxisInformation_t> XYArrayItem_t::GetAxisInformationValue(IntrusivePtr_t<const IVariableNode_t>& propertyNode, Status_t& result)
{
  IntrusivePtr_t<const AxisInformation_t> retVal;
  if(!propertyNode.is_set() || !propertyNode->Value().is_set() || !propertyNode->Value()->Value().is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return retVal;
  }

  retVal = RuntimeCast<const AxisInformation_t *>(*( propertyNode->Value()->Value()) );
  if(!retVal.is_set())
  {
    result = OpcUa_BadUnexpectedError;
    return retVal;
  }

  result = OpcUa_Good;
  return retVal;
}

void XYArrayItem_t::DeleteProperties(XYArrayItem_t& item)
{
  UASDK_RETURN_IF_NULL(item.addressSpace);

  {
    IntrusivePtr_t<IVariableNode_t> node_ = XAxisDefinitionNode();
    if(node_.is_set() && node_->NodeId().is_set())
    {
      item.addressSpace->RemoveNode( *(node_->NodeId()) );
    }
  }
}

/*
 * Properties
 */
IntrusivePtr_t<IVariableNode_t> XYArrayItem_t::XAxisDefinitionNode(void)
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_X_AXIS_DEFINATION);
}

IntrusivePtr_t<const IVariableNode_t> XYArrayItem_t::XAxisDefinitionNode(void) const
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_X_AXIS_DEFINATION);
}

IntrusivePtr_t<const AxisInformation_t> XYArrayItem_t::GetXAxisDefinitionValue(Status_t& result)
{
  IntrusivePtr_t<const IVariableNode_t> propertyNode = XAxisDefinitionNode();
  return GetAxisInformationValue(propertyNode, result);
}

Status_t XYArrayItem_t::SetXAxisDefinitionValue(const AxisInformation_t& value)
{
  IntrusivePtr_t<IVariableNode_t> propertyNode = XAxisDefinitionNode();
  return XYArrayItem_t::CreateProperty(*this, 0, BROWSE_NAME_X_AXIS_DEFINATION, OpcUaId_AxisInformation, value, propertyNode);
}

/*
 * Wrapper creation
 */
IntrusivePtr_t<XYArrayItem_t> XYArrayItem_t::Get(const NodeId_t& nodeId,
                                                 IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                 Status_t& result)
{
  IntrusivePtr_t<XYArrayItem_t> empty;

  if(!addressSpace_.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  IntrusivePtr_t<IVariableNode_t> itemNode = addressSpace_->FindVariableNode(nodeId, result);
  if(result.IsBad() || !itemNode.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  return Get(itemNode, addressSpace_, result);
}

IntrusivePtr_t<XYArrayItem_t> XYArrayItem_t::Get(IntrusivePtr_t<IVariableNode_t>& node_,
                                                 IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                 Status_t& result)
{
  IntrusivePtr_t<XYArrayItem_t> empty;
  if(!node_.is_set() || !addressSpace_.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  result = DataItem_t::CheckHasTypeDefinition(*node_, *addressSpace_, OpcUaId_XYArrayItemType);
  if(result.IsBad())
  {
    return empty;
  }

  return XYArrayItem_t::CreateXYArrayItem(node_, addressSpace_, result);
}

} //namespace uasdk

#endif //UASDK_USE_DATA_ACCESS_HELPERS