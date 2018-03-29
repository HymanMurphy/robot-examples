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

#include "multi_state_discrete_t.h"

#if ((UASDK_USE_HELPERS > 0) && (UASDK_USE_DATA_ACCESS_HELPERS > 0))

#include "opcua_array_ua_t.h"
#include "opcua_localized_text_t.h"
#include "opcua_node_id_t.h"

namespace uasdk
{
/*
 * private functions
 */
bool MultiStateDiscrete_t::IsDataTypeValid(uint32_t datatype)
{
  if(datatype == OpcUaId_Byte
      || datatype == OpcUaId_UInt16
      || datatype == OpcUaId_UInt32
      || datatype == OpcUaId_UInt64)
  {
    return true;
  }

  return false;
}

Status_t MultiStateDiscrete_t::CreateEnumStringsProperty(MultiStateDiscrete_t& multiStateDiscrete,
                                                         uint32_t propertyIdentifier,
                                                         const ArrayUA_t<LocalizedText_t>& value,
                                                         IntrusivePtr_t<IVariableNode_t>& propertyNode)
{
  IntrusivePtr_t<ArrayUA_t<LocalizedText_t> > destinationVal(new SafeRefCount_t<ArrayUA_t<LocalizedText_t> >());
  if(!destinationVal.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  return DataItem_t::CreatePropertyAndAssignValue(multiStateDiscrete, propertyIdentifier, BROWSE_NAME_ENUM_STRINGS, OpcUaId_LocalizedText, destinationVal, value, propertyNode);
}

IntrusivePtr_t<MultiStateDiscrete_t> MultiStateDiscrete_t::CreateMultiStateDiscrete(IntrusivePtr_t<IVariableNode_t>& node_,
                                                                                    IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                                    Status_t& result)
{
  IntrusivePtr_t<MultiStateDiscrete_t> retVal;
  if(!node_.is_set() || !addressSpace_.is_set() || result.IsBad())
  {
    result = OpcUa_BadInvalidArgument;
    return retVal;
  }

  retVal.reset(new SafeRefCount_t<MultiStateDiscrete_t>());
  if(!retVal.is_set())
  {
    result = OpcUa_BadOutOfMemory;
    return retVal;
  }
  retVal->Initialize(node_, addressSpace_);

  result = OpcUa_Good;
  return retVal;
}

IntrusivePtr_t<MultiStateDiscrete_t> MultiStateDiscrete_t::CreateMultiStateDiscreteWithMandatoryProperty(IntrusivePtr_t<IVariableNode_t>& node_,
                                                                                                         IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                                                         uint32_t enumStringsIdentifier,
                                                                                                         const ArrayUA_t<LocalizedText_t>& enumStringsValue,
                                                                                                         Status_t& result)
{
  IntrusivePtr_t<MultiStateDiscrete_t> empty;
  IntrusivePtr_t<MultiStateDiscrete_t> multiStateDiscrete = MultiStateDiscrete_t::CreateMultiStateDiscrete(node_, addressSpace_, result);
  if(!multiStateDiscrete.is_set() || result.IsBad())
  {
    return empty;
  }

  //Add EnumStrings Property
  IntrusivePtr_t<IVariableNode_t> propertyNode  = multiStateDiscrete->EnumStringsNode();
  result = MultiStateDiscrete_t::CreateEnumStringsProperty(*multiStateDiscrete, enumStringsIdentifier, enumStringsValue, propertyNode);
  if(result.IsBad())
  {
    return empty;
  }

  result = OpcUa_Good;
  return multiStateDiscrete;
}

void MultiStateDiscrete_t::DeleteProperties(MultiStateDiscrete_t& multiStateDiscrete)
{
  UASDK_RETURN_IF_NULL(multiStateDiscrete.addressSpace);

  IntrusivePtr_t<IVariableNode_t> enumStrings = multiStateDiscrete.EnumStringsNode();

  if(enumStrings.is_set() && enumStrings->NodeId().is_set())
  {
    multiStateDiscrete.addressSpace->RemoveNode( *(enumStrings->NodeId()) );
  }
}

/*
 * protected functions
 */
MultiStateDiscrete_t::MultiStateDiscrete_t()
{}

/*
 * public functions
 */
MultiStateDiscrete_t::~MultiStateDiscrete_t()
{
  if(deleteNode)
  {
    DeleteProperties(*this);
  }
}

/*
 * Properties
 */
IntrusivePtr_t<IVariableNode_t> MultiStateDiscrete_t::EnumStringsNode(void)
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_ENUM_STRINGS);
}

IntrusivePtr_t<const IVariableNode_t> MultiStateDiscrete_t::EnumStringsNode(void) const
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return DataItem_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_ENUM_STRINGS);
}

IntrusivePtr_t<const ArrayUA_t<LocalizedText_t> > MultiStateDiscrete_t::GetEnumStringsValue(Status_t& result)
{
  IntrusivePtr_t<const ArrayUA_t<LocalizedText_t> > retVal;
  IntrusivePtr_t<const IVariableNode_t> propertyNode = EnumStringsNode();
  if(!propertyNode.is_set() || !propertyNode->Value().is_set() || !propertyNode->Value()->Value().is_set())
  {
    result = OpcUa_BadUnexpectedError;
    return retVal;
  }

  retVal = RuntimeCast< const ArrayUA_t<LocalizedText_t> * >(*( propertyNode->Value()->Value()) );
  if(!retVal.is_set())
  {
    result = OpcUa_BadUnexpectedError;
    return retVal;
  }

  result = OpcUa_Good;
  return retVal;
}

Status_t MultiStateDiscrete_t::SetEnumStringsValue(const ArrayUA_t<LocalizedText_t>& value)
{
  IntrusivePtr_t<IVariableNode_t> propertyNode = EnumStringsNode();
  return MultiStateDiscrete_t::CreateEnumStringsProperty(*this, 0, value, propertyNode);
}

/*
 * Wrapper creation
 */
IntrusivePtr_t<MultiStateDiscrete_t> MultiStateDiscrete_t::Get(const NodeId_t& nodeId,
                                                               IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                               Status_t& result)
{
  IntrusivePtr_t<MultiStateDiscrete_t> empty;
  if(!addressSpace_.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  IntrusivePtr_t<IVariableNode_t> multiStateDiscrete = addressSpace_->FindVariableNode(nodeId, result);
  if(result.IsBad() || !multiStateDiscrete.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  return Get(multiStateDiscrete, addressSpace_, result);
}

IntrusivePtr_t<MultiStateDiscrete_t> MultiStateDiscrete_t::Get(IntrusivePtr_t<IVariableNode_t>& node_,
                                                               IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                               Status_t& result)
{
  IntrusivePtr_t<MultiStateDiscrete_t> empty;

  if(!node_.is_set() || !addressSpace_.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  result = DataItem_t::CheckHasTypeDefinition(*node_, *addressSpace_, OpcUaId_MultiStateDiscreteType);
  if(result.IsBad())
  {
    return empty;
  }

  return MultiStateDiscrete_t::CreateMultiStateDiscrete(node_, addressSpace_, result);
}

} //namespace uasdk

#endif //UASDK_USE_DATA_ACCESS_HELPERS