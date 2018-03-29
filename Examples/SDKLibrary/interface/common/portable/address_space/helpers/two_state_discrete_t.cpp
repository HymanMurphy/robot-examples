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

#include "two_state_discrete_t.h"

#if ((UASDK_USE_HELPERS > 0) && (UASDK_USE_DATA_ACCESS_HELPERS > 0))

#include "opcua_string_t.h"
#include "opcua_data_value_t.h"
#include "opcua_array_ua_t.h"
#include "opcua_localized_text_t.h"
#include "opcua_boolean_t.h"

namespace uasdk
{

/*
 * Private Functions
 */
Status_t TwoStateDiscrete_t::CreateProperty(TwoStateDiscrete_t& twoStateDiscrete,
                                            uint32_t propertyIdentifier,
                                            const char* propertyName,
                                            uint32_t propertyType,
                                            const LocalizedText_t& value,
                                            IntrusivePtr_t<IVariableNode_t>& propertyNode)
{
  IntrusivePtr_t<LocalizedText_t> destinationValue(new SafeRefCount_t<LocalizedText_t>());
  if(!destinationValue.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  return DataItem_t::CreatePropertyAndAssignValue(twoStateDiscrete, propertyIdentifier, propertyName, propertyType, destinationValue, value, propertyNode);
}

IntrusivePtr_t<TwoStateDiscrete_t> TwoStateDiscrete_t::CreateTwoStateDiscrete(IntrusivePtr_t<IVariableNode_t>& node_,
                                                                              IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                              Status_t& result)
{
  IntrusivePtr_t<TwoStateDiscrete_t> retVal;
  if(!node_.is_set() || !addressSpace_.is_set() || result.IsBad())
  {
    result = OpcUa_BadInvalidArgument;
    return retVal;
  }

  retVal.reset(new SafeRefCount_t<TwoStateDiscrete_t>());
  if(!retVal.is_set())
  {
    result = OpcUa_BadOutOfMemory;
    return retVal;
  }
  retVal->Initialize(node_, addressSpace_);

  result = OpcUa_Good;
  return retVal;
}

IntrusivePtr_t<TwoStateDiscrete_t> TwoStateDiscrete_t::CreateTwoStateDiscreteWithMandatoryProperty(IntrusivePtr_t<IVariableNode_t>& node_,
                                                                                                   IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                                                   const MandatoryPropertyNumericIds_t& ids,
                                                                                                   const MandatoryPropertyValues_t& values,
                                                                                                   Status_t& result)
{
  IntrusivePtr_t<TwoStateDiscrete_t> empty;
  IntrusivePtr_t<TwoStateDiscrete_t> twoStateDiscreteItem = TwoStateDiscrete_t::CreateTwoStateDiscrete(node_, addressSpace_, result);
  if(!twoStateDiscreteItem.is_set() || result.IsBad())
  {
    return empty;
  }

  //True State Property
  IntrusivePtr_t<IVariableNode_t> propertyNode = twoStateDiscreteItem->TrueStateNode();
  result = TwoStateDiscrete_t::CreateProperty(*twoStateDiscreteItem, ids.trueState, BROWSE_NAME_TRUESTATE, OpcUaId_LocalizedText, values.trueState, propertyNode);
  if(result.IsBad())
  {
    return empty;
  }

  //True State Property
  propertyNode = twoStateDiscreteItem->FalseStateNode();
  result = TwoStateDiscrete_t::CreateProperty(*twoStateDiscreteItem, ids.falseState, BROWSE_NAME_FALSESTATE, OpcUaId_LocalizedText, values.falseState, propertyNode);
  if(result.IsBad())
  {
    return empty;
  }

  result = OpcUa_Good;
  return twoStateDiscreteItem;
}

IntrusivePtr_t<const LocalizedText_t> TwoStateDiscrete_t::GetLocalizedTextValue(IntrusivePtr_t<const IVariableNode_t>& propertyNode, Status_t& result)
{
  IntrusivePtr_t<const LocalizedText_t> retVal;
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

void TwoStateDiscrete_t::DeleteProperties(TwoStateDiscrete_t& twoStateDiscreteItem)
{
  UASDK_RETURN_IF_NULL(twoStateDiscreteItem.addressSpace);

  //Deleting Properties
  IntrusivePtr_t<IVariableNode_t> trueStateNode = twoStateDiscreteItem.TrueStateNode();
  IntrusivePtr_t<IVariableNode_t> falseStateNode = twoStateDiscreteItem.FalseStateNode();

  if(trueStateNode.is_set() && trueStateNode->NodeId().is_set())
  {
    twoStateDiscreteItem.addressSpace->RemoveNode( *(trueStateNode->NodeId()) );
  }
  if(falseStateNode.is_set() && falseStateNode->NodeId().is_set())
  {
    twoStateDiscreteItem.addressSpace->RemoveNode( *(falseStateNode->NodeId()) );
  }
}

/*
 * protected function
 */
TwoStateDiscrete_t::TwoStateDiscrete_t()
{}

/*
 * public functions
 */
TwoStateDiscrete_t::~TwoStateDiscrete_t()
{
  if(deleteNode)
  {
    DeleteProperties(*this);
  }
}

/*
 * Properties
 */
IntrusivePtr_t<IVariableNode_t> TwoStateDiscrete_t::TrueStateNode(void)
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_TRUESTATE);
}

IntrusivePtr_t<const IVariableNode_t> TwoStateDiscrete_t::TrueStateNode(void) const
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_TRUESTATE);
}

IntrusivePtr_t<const LocalizedText_t> TwoStateDiscrete_t::GetTrueStateValue(Status_t& result)
{
  IntrusivePtr_t<const IVariableNode_t> propertyNode = TrueStateNode();
  return TwoStateDiscrete_t::GetLocalizedTextValue(propertyNode, result);
}

Status_t TwoStateDiscrete_t::SetTrueStateValue(const LocalizedText_t& value)
{
  IntrusivePtr_t<IVariableNode_t> propertyNode = TrueStateNode();
  return TwoStateDiscrete_t::CreateProperty(*this, 0, BROWSE_NAME_TRUESTATE, OpcUaId_LocalizedText, value, propertyNode);
}

IntrusivePtr_t<IVariableNode_t> TwoStateDiscrete_t::FalseStateNode(void)
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_FALSESTATE);
}

IntrusivePtr_t<const IVariableNode_t> TwoStateDiscrete_t::FalseStateNode(void) const
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_FALSESTATE);
}

IntrusivePtr_t<const LocalizedText_t> TwoStateDiscrete_t::GetFalseStateValue(Status_t& result)
{
  IntrusivePtr_t<const IVariableNode_t> propertyNode = FalseStateNode();
  return TwoStateDiscrete_t::GetLocalizedTextValue(propertyNode, result);
}

Status_t TwoStateDiscrete_t::SetFalseStateValue(const LocalizedText_t& value)
{
  IntrusivePtr_t<IVariableNode_t> propertyNode = FalseStateNode();
  return TwoStateDiscrete_t::CreateProperty(*this, 0, BROWSE_NAME_FALSESTATE, OpcUaId_LocalizedText, value, propertyNode);
}

/*
 * Wrapper creation
 */
IntrusivePtr_t<TwoStateDiscrete_t> TwoStateDiscrete_t::Get(const NodeId_t& nodeId,
                                                           IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                           Status_t& result)
{
  IntrusivePtr_t<TwoStateDiscrete_t> empty;

  if(!addressSpace_.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  IntrusivePtr_t<IVariableNode_t> twoStateDiscreteNode = addressSpace_->FindVariableNode(nodeId, result);
  if(result.IsBad() || !twoStateDiscreteNode.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  return Get(twoStateDiscreteNode, addressSpace_, result);
}

IntrusivePtr_t<TwoStateDiscrete_t> TwoStateDiscrete_t::Get(IntrusivePtr_t<IVariableNode_t>& node_,
                                                           IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                           Status_t& result)
{
  IntrusivePtr_t<TwoStateDiscrete_t> empty;
  if(!node_.is_set() || !addressSpace_.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  result = DataItem_t::CheckHasTypeDefinition(*node_, *addressSpace_, OpcUaId_TwoStateDiscreteType);
  if(result.IsBad())
  {
    return empty;
  }

  return TwoStateDiscrete_t::CreateTwoStateDiscrete(node_, addressSpace_, result);
}

IntrusivePtr_t<TwoStateDiscrete_t> TwoStateDiscrete_t::CreateWithNumericId(uint16_t namespaceIndex,
                                                                           uint32_t nodeIdentifier,
                                                                           IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                           const String_t& browseName,
                                                                           const MandatoryPropertyNumericIds_t& propertyIdentifier,
                                                                           const MandatoryPropertyValues_t& propertyValue,
                                                                           Status_t& result)
{
  IntrusivePtr_t<IVariableNode_t> node_ = BaseDataVariable_t::CreateWithNumericId(namespaceIndex, nodeIdentifier, OpcUaId_Boolean,
                                                                                  addressSpace_, browseName, OpcUaId_TwoStateDiscreteType, -2, result);

  return TwoStateDiscrete_t::CreateTwoStateDiscreteWithMandatoryProperty(node_, addressSpace_, propertyIdentifier, propertyValue, result);
}

IntrusivePtr_t<TwoStateDiscrete_t> TwoStateDiscrete_t::CreateWithStringId(uint16_t namespaceIndex,
                                                                          const String_t& nodeIdentifier,
                                                                          IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                          const String_t& browseName,
                                                                          const MandatoryPropertyValues_t& propertyValue,
                                                                          Status_t& result)
{
  IntrusivePtr_t<IVariableNode_t> node_ = BaseDataVariable_t::CreateWithStringId(namespaceIndex, nodeIdentifier, OpcUaId_Boolean,
                                                                                 addressSpace_, browseName, OpcUaId_TwoStateDiscreteType, -2, result);

  MandatoryPropertyNumericIds_t empty = {0, 0};
  return TwoStateDiscrete_t::CreateTwoStateDiscreteWithMandatoryProperty(node_, addressSpace_, empty, propertyValue, result);
}

IntrusivePtr_t<TwoStateDiscrete_t> TwoStateDiscrete_t::CreateWithGuidId(uint16_t namespaceIndex,
                                                                        const Guid_t& nodeIdentifier,
                                                                        IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                        const String_t& browseName,
                                                                        const MandatoryPropertyValues_t& propertyValue,
                                                                        Status_t& result)
{
  IntrusivePtr_t<IVariableNode_t> node_ = BaseDataVariable_t::CreateWithGuidId(namespaceIndex, nodeIdentifier, OpcUaId_Boolean, addressSpace_,
                                                                               browseName, OpcUaId_TwoStateDiscreteType, -2, result);

  MandatoryPropertyNumericIds_t empty = {0, 0};
  return TwoStateDiscrete_t::CreateTwoStateDiscreteWithMandatoryProperty(node_, addressSpace_, empty, propertyValue, result);
}

IntrusivePtr_t<TwoStateDiscrete_t> TwoStateDiscrete_t::CreateWithOpaqueId(uint16_t namespaceIndex,
                                                                          const ByteString_t& nodeIdentifier,
                                                                          IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                          const String_t& browseName,
                                                                          const MandatoryPropertyValues_t& propertyValue,
                                                                          Status_t& result)
{
  IntrusivePtr_t<IVariableNode_t> node_ = BaseDataVariable_t::CreateWithOpaqueId(namespaceIndex, nodeIdentifier, OpcUaId_Boolean, addressSpace_,
                                                                                 browseName, OpcUaId_TwoStateDiscreteType, -2, result);

  MandatoryPropertyNumericIds_t empty = {0, 0};
  return TwoStateDiscrete_t::CreateTwoStateDiscreteWithMandatoryProperty(node_, addressSpace_, empty, propertyValue, result);
}

} //namespace uasdk

#endif //UASDK_USE_DATA_ACCESS_HELPERS