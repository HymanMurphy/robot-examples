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

#include "cube_item_t.h"

#if ((UASDK_USE_HELPERS > 0) && (UASDK_USE_DATA_ACCESS_HELPERS > 0) && (UASDK_INCLUDE_ADDITIONAL_DA_TYPES > 0))

#include "opcua_string_t.h"
#include "opcua_data_value_t.h"
#include "opcua_array_ua_t.h"
#include "opcua_localized_text_t.h"
#include "opcua_boolean_t.h"

namespace uasdk
{
CubeItem_t::CubeItem_t()
{}

CubeItem_t::~CubeItem_t()
{
  if(deleteNode)
  {
    DeleteProperties(*this);
  }
}

Status_t CubeItem_t::CreateProperty(CubeItem_t& item,
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

  return DataItem_t::CreatePropertyAndAssignValue(item, propertyIdentifier, propertyName, propertyType, destinationValue, value, propertyNode);
}

IntrusivePtr_t<CubeItem_t> CubeItem_t::CreateCubeItem(IntrusivePtr_t<IVariableNode_t>& node_,
                                                            IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                            Status_t& result)
{
  IntrusivePtr_t<CubeItem_t> retVal;
  if(!node_.is_set() || !addressSpace_.is_set() || result.IsBad())
  {
    result = OpcUa_BadInvalidArgument;
    return retVal;
  }

  IntrusivePtr_t<CubeItem_t> yArrayItem(new SafeRefCount_t<CubeItem_t>());
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

IntrusivePtr_t<CubeItem_t> CubeItem_t::CreateCubeWithMandatoryProperty(IntrusivePtr_t<IVariableNode_t> node_,
                                                                       IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                       const MandatoryPropertyNumericIds_t& mandatoryPropertiesId,
                                                                       const MandatoryPropertyValues_t& propertyValues,
                                                                       Status_t& result)
{
  IntrusivePtr_t<CubeItem_t> empty;
  IntrusivePtr_t<CubeItem_t> cubeItem = CubeItem_t::CreateCubeItem(node_, addressSpace_, result);

  if(!cubeItem.is_set() || result.IsBad())
  {
    return empty;
  }

  result = ArrayItem_t::CreateArrayMandatoryProperty(*cubeItem, mandatoryPropertiesId.arrayItemPropertyNumericId, propertyValues.arrayItemProperty);
  if(result.IsBad())
  {
    return empty;
  }
  {
    IntrusivePtr_t<IVariableNode_t> propertyNode = cubeItem->XAxisDefinitionNode();
    result = CubeItem_t::CreateProperty(*cubeItem, mandatoryPropertiesId.xAxisInformationNumericId, BROWSE_NAME_X_AXIS_DEFINATION, OpcUaId_AxisInformation, propertyValues.xAxisInformation, propertyNode);
    if(result.IsBad())
    {
      return empty;
    }
  }
  {
    IntrusivePtr_t<IVariableNode_t> propertyNode = cubeItem->YAxisDefinitionNode();
    result = CubeItem_t::CreateProperty(*cubeItem, mandatoryPropertiesId.yAxisInformationNumericId, BROWSE_NAME_Y_AXIS_DEFINATION, OpcUaId_AxisInformation, propertyValues.yAxisInformation, propertyNode);
    if(result.IsBad())
    {
      return empty;
    }
  }
  {
     IntrusivePtr_t<IVariableNode_t> propertyNode = cubeItem->ZAxisDefinitionNode();
     result = CubeItem_t::CreateProperty(*cubeItem, mandatoryPropertiesId.zAxisInformationNumericId, BROWSE_NAME_Z_AXIS_DEFINATION, OpcUaId_AxisInformation, propertyValues.zAxisInformation, propertyNode);
     if(result.IsBad())
     {
       return empty;
     }
   }
  result = OpcUa_Good;
  return cubeItem;
}

IntrusivePtr_t<const AxisInformation_t> CubeItem_t::GetAxisInformationValue(IntrusivePtr_t<const IVariableNode_t>& propertyNode, Status_t& result)
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

void CubeItem_t::DeleteProperties(CubeItem_t& item)
{
  UASDK_RETURN_IF_NULL(item.addressSpace);

  {
    IntrusivePtr_t<IVariableNode_t> node_ = XAxisDefinitionNode();
    if(node_.is_set() && (node_->NodeId().is_set()))
    {
      item.addressSpace->RemoveNode( *(node_->NodeId()) );
    }
  }
  {
    IntrusivePtr_t<IVariableNode_t> node_ = YAxisDefinitionNode();
    if(node_.is_set() && (node_->NodeId().is_set()))
    {
      item.addressSpace->RemoveNode( *(node_->NodeId()) );
    }
  }
  {
    IntrusivePtr_t<IVariableNode_t> node_ = ZAxisDefinitionNode();
    if(node_.is_set() && (node_->NodeId().is_set()))
    {
      item.addressSpace->RemoveNode( *(node_->NodeId()) );
    }
  }
}

/*
 * Properties
 */

IntrusivePtr_t<IVariableNode_t> CubeItem_t::XAxisDefinitionNode(void)
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_X_AXIS_DEFINATION);
}

IntrusivePtr_t<const IVariableNode_t> CubeItem_t::XAxisDefinitionNode(void) const
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_X_AXIS_DEFINATION);
}

IntrusivePtr_t<IVariableNode_t> CubeItem_t::YAxisDefinitionNode(void)
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_Y_AXIS_DEFINATION);
}

IntrusivePtr_t<const IVariableNode_t> CubeItem_t::YAxisDefinitionNode(void) const
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_Y_AXIS_DEFINATION);
}

IntrusivePtr_t<IVariableNode_t> CubeItem_t::ZAxisDefinitionNode(void)
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_Z_AXIS_DEFINATION);
}

IntrusivePtr_t<const IVariableNode_t> CubeItem_t::ZAxisDefinitionNode(void) const
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_Z_AXIS_DEFINATION);
}


IntrusivePtr_t<const AxisInformation_t> CubeItem_t::GetXAxisDefinitionValue(Status_t& result)
{
  IntrusivePtr_t<const IVariableNode_t> propertyNode = XAxisDefinitionNode();
  return GetAxisInformationValue(propertyNode, result);
}

Status_t CubeItem_t::SetXAxisDefinitionValue(const AxisInformation_t& value)
{
  IntrusivePtr_t<IVariableNode_t> propertyNode = XAxisDefinitionNode();
  return CubeItem_t::CreateProperty(*this, 0, BROWSE_NAME_X_AXIS_DEFINATION, OpcUaId_AxisInformation, value, propertyNode);
}


IntrusivePtr_t<const AxisInformation_t> CubeItem_t::GetYAxisDefinitionValue(Status_t& result)
{
  IntrusivePtr_t<const IVariableNode_t> propertyNode = YAxisDefinitionNode();
  return GetAxisInformationValue(propertyNode, result);
}

Status_t CubeItem_t::SetYAxisDefinitionValue(const AxisInformation_t& value)
{
  IntrusivePtr_t<IVariableNode_t> propertyNode = XAxisDefinitionNode();
  return CubeItem_t::CreateProperty(*this, 0, BROWSE_NAME_Y_AXIS_DEFINATION, OpcUaId_AxisInformation, value, propertyNode);
}


IntrusivePtr_t<const AxisInformation_t> CubeItem_t::GetZAxisDefinitionValue(Status_t& result)
{
  IntrusivePtr_t<const IVariableNode_t> propertyNode = XAxisDefinitionNode();
  return GetAxisInformationValue(propertyNode, result);
}

Status_t CubeItem_t::SetZAxisDefinitionValue(const AxisInformation_t& value)
{
  IntrusivePtr_t<IVariableNode_t> propertyNode = XAxisDefinitionNode();
  return CubeItem_t::CreateProperty(*this, 0, BROWSE_NAME_Z_AXIS_DEFINATION, OpcUaId_AxisInformation, value, propertyNode);
}

/*
 * Wrapper creation
 */
IntrusivePtr_t<CubeItem_t> CubeItem_t::Get(const NodeId_t& nodeId,
                                               IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                               Status_t& result)
{
  IntrusivePtr_t<CubeItem_t> empty;

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

IntrusivePtr_t<CubeItem_t> CubeItem_t::Get(IntrusivePtr_t<IVariableNode_t>& node_,
                                               IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                               Status_t& result)
{
  IntrusivePtr_t<CubeItem_t> empty;
  if(!node_.is_set() || !addressSpace_.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  result = DataItem_t::CheckHasTypeDefinition(*node_, *addressSpace_, OpcUaId_CubeItemType);
  if(result.IsBad())
  {
    return empty;
  }

  return CubeItem_t::CreateCubeItem(node_, addressSpace_, result);
}

} //namespace uasdk

#endif //UASDK_USE_DATA_ACCESS_HELPERS