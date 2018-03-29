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

#include "y_array_item_t.h"

#if ((UASDK_USE_HELPERS > 0) && (UASDK_USE_DATA_ACCESS_HELPERS > 0) && (UASDK_INCLUDE_ADDITIONAL_DA_TYPES > 0))

#include "opcua_axis_information_t.h"
#include "opcua_string_t.h"
#include "opcua_data_value_t.h"
#include "opcua_array_ua_t.h"
#include "opcua_localized_text_t.h"
#include "opcua_boolean_t.h"

namespace uasdk
{

YArrayItem_t::YArrayItem_t()
{}

YArrayItem_t::~YArrayItem_t()
{
  if(deleteNode)
  {
    DeleteProperties(*this);
  }
}

Status_t YArrayItem_t::CreateProperty(YArrayItem_t& item,
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

IntrusivePtr_t<YArrayItem_t> YArrayItem_t::CreateYArrayItem(IntrusivePtr_t<IVariableNode_t>& node_,
                                                            IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                            Status_t& result)
{
  IntrusivePtr_t<YArrayItem_t> retVal;
  if(!node_.is_set() || !addressSpace_.is_set() || result.IsBad())
  {
    result = OpcUa_BadInvalidArgument;
    return retVal;
  }

  //Setting Array Dimension as 0
  IntrusivePtr_t<UInt32_t> dimension_(new SafeRefCount_t<UInt32_t>());
  if(!dimension_.is_set())
  {
    result = OpcUa_BadOutOfMemory;
    return retVal;
  }
  dimension_->Value(0);

  IntrusivePtr_t<ArrayUA_t<UInt32_t> > arrayDimension(new SafeRefCount_t<ArrayUA_t<UInt32_t> >());
  if(!arrayDimension.is_set())
  {
    result = OpcUa_BadOutOfMemory;
    return retVal;
  }
  result = arrayDimension->Initialise(1);
  if(result.IsBad())
  {
    return retVal;
  }
  (*arrayDimension)[0] = dimension_;

  IntrusivePtr_t<const ArrayUA_t<UInt32_t> > arrayDimension_ = arrayDimension;
  node_->ArrayDimensions(arrayDimension_);

  IntrusivePtr_t<YArrayItem_t> item(new SafeRefCount_t<YArrayItem_t>());
  if(!item.is_set())
  {
    result = OpcUa_BadOutOfMemory;
    return retVal;
  }
  item->Initialize(node_, addressSpace_);

  retVal = item;
  result = OpcUa_Good;

  return retVal;
}

IntrusivePtr_t<YArrayItem_t> YArrayItem_t::CreateYArrayWithMandatoryProperty(IntrusivePtr_t<IVariableNode_t> node_,
                                                                             IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                             const MandatoryPropertyNumericIds_t& mandatoryPropertiesId,
                                                                             const MandatoryPropertyValues_t& propertyValues,
                                                                             Status_t& result)
{
  IntrusivePtr_t<YArrayItem_t> empty;
  IntrusivePtr_t<YArrayItem_t> item = YArrayItem_t::CreateYArrayItem(node_, addressSpace_, result);
  if(!item.is_set() || result.IsBad())
  {
    return empty;
  }

  result = ArrayItem_t::CreateArrayMandatoryProperty(*item, mandatoryPropertiesId.arrayItemPropertyNumericId, propertyValues.arrayItemProperty);
  if(result.IsBad())
  {
    return empty;
  }

  IntrusivePtr_t<IVariableNode_t> propertyNode = item->XAxisDefinitionNode();
  result = YArrayItem_t::CreateProperty(*item, mandatoryPropertiesId.axisInformationId, BROWSE_NAME_X_AXIS_DEFINATION, OpcUaId_AxisInformation, propertyValues.axisInformation, propertyNode);
  if(result.IsBad())
  {
    return empty;
  }

  result = OpcUa_Good;
  return item;
}

IntrusivePtr_t<const AxisInformation_t> YArrayItem_t::GetAxisInformationValue(IntrusivePtr_t<const IVariableNode_t>& propertyNode, Status_t& result)
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

void YArrayItem_t::DeleteProperties(YArrayItem_t& item)
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
IntrusivePtr_t<IVariableNode_t> YArrayItem_t::XAxisDefinitionNode(void)
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_X_AXIS_DEFINATION);
}

IntrusivePtr_t<const IVariableNode_t> YArrayItem_t::XAxisDefinitionNode(void) const
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_X_AXIS_DEFINATION);
}

IntrusivePtr_t<const AxisInformation_t> YArrayItem_t::GetXAxisDefinitionValue(Status_t& result)
{
  IntrusivePtr_t<const IVariableNode_t> propertyNode = XAxisDefinitionNode();
  return GetAxisInformationValue(propertyNode, result);
}

Status_t YArrayItem_t::SetXAxisDefinitionValue(const AxisInformation_t& value)
{
  IntrusivePtr_t<IVariableNode_t> propertyNode = XAxisDefinitionNode();
  return YArrayItem_t::CreateProperty(*this, 0, BROWSE_NAME_X_AXIS_DEFINATION, OpcUaId_AxisInformation, value, propertyNode);
}

/*
 * Wrapper creation
 */
IntrusivePtr_t<YArrayItem_t> YArrayItem_t::Get(const NodeId_t& nodeId,
                                               IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                               Status_t& result)
{
  IntrusivePtr_t<YArrayItem_t> empty;

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

IntrusivePtr_t<YArrayItem_t> YArrayItem_t::Get(IntrusivePtr_t<IVariableNode_t>& node_,
                                               IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                               Status_t& result)
{
  IntrusivePtr_t<YArrayItem_t> empty;
  if(!node_.is_set() || !addressSpace_.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  result = DataItem_t::CheckHasTypeDefinition(*node_, *addressSpace_, OpcUaId_YArrayItemType);
  if(result.IsBad())
  {
    return empty;
  }

  return YArrayItem_t::CreateYArrayItem(node_, addressSpace_, result);
}

} //namespace uasdk

#endif //UASDK_USE_DATA_ACCESS_HELPERS