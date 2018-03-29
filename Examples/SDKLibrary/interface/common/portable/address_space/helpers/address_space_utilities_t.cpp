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

#include "address_space_utilities_t.h"
#include "opcua_node_id_numeric_t.h"
#include "ireference_t.h"
#include "iaddress_space_t.h"
#include "opcua_data_value_t.h"
#include "opcua_node_id_t.h"
#include "opcua_expanded_node_id_t.h"
#include "opcua_qualified_name_t.h"
#include "opcua_localized_text_t.h"
#include "opcua_byte_t.h"
#include "opcua_sbyte_t.h"
#include "opcua_int16_t.h"
#include "opcua_int32_t.h"
#include "opcua_int64_t.h"
#include "opcua_uint16_t.h"
#include "opcua_uint32_t.h"
#include "opcua_uint64_t.h"
#include "opcua_double_t.h"
#include "opcua_float_t.h"
#include "opcua_xv_type_t.h"
#include "opcua_boolean_t.h"
#include "write_mask_t.h"
#include "event_notifier_t.h"
#include "opcua_diagnostic_info_t.h"
#include "access_level_t.h"
#include "opcua_duration_t.h"
#include "opcua_array_ua_t.h"
#include "opcua_qualified_name_t.h"
#include "safe_ref_count_t.h"
#include "opcua_node_id_string_t.h"
#include "opcua_node_id_guid_t.h"
#include "opcua_node_id_opaque_t.h"
#include "opcua_range_t.h"
#include "localizable_text_stored_t.h"
#include "idata_type_node_t.h"
#include "imethod_node_t.h"

namespace uasdk
{
/*
 * Private function defintion
 */
template<typename T>
bool AddressSpaceUtilities_t::IsInRange(const Range_t& range, const BaseDataType_t& value, Status_t& result)
{
  double valueToWrite;

  if (value.IsArray())
  {
    const ArrayUA_t<T>* temp = RuntimeCast<const ArrayUA_t<T>* >(value);
    if (!temp)
    {
      result = OpcUa_BadTypeMismatch;
      LOG_WARNING_WITH_LOCATION(result.Value());
      return false;
    }

    uint32_t count = temp->Count();
    for (uint32_t i = 0; i < count; i++)
    {
      IntrusivePtr_t<T> val = (*temp)[i];
      if (!val.is_set())
      {
        result = OpcUa_BadUnexpectedError;
        LOG_WARNING_WITH_LOCATION(result.Value());
        return false;
      }
      valueToWrite = (double)(val->Value());
      if (valueToWrite < range.Low().Value() || valueToWrite > range.High().Value())
      {
        result = OpcUa_BadOutOfRange;
        LOG_WARNING_WITH_LOCATION(result.Value());
        return false;
      }
    }
  }
  else
  {
    const T* temp = RuntimeCast<const T*>(value);
    if (!temp)
    {
      result = OpcUa_BadUnexpectedError;
      LOG_WARNING_WITH_LOCATION(result.Value());
      return false;
    }

    valueToWrite = (double)(temp->Value());
    if (valueToWrite < range.Low().Value() || valueToWrite > range.High().Value())
    {
      result = OpcUa_BadOutOfRange;
      LOG_WARNING_WITH_LOCATION(result.Value());
      return false;
    }
  }

  result = OpcUa_Good;
  return true;
}

/*
 *  public functions
 */
Status_t AddressSpaceUtilities_t::GenerateNumericNodeId(const uint16_t namespaceIndex, const uint32_t nodeIdentifier, IntrusivePtr_t<const NodeId_t>& result)
{
  IntrusivePtr_t<NodeIdNumeric_t> temp(new SafeRefCount_t<NodeIdNumeric_t>());
  if (!temp.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  temp->NamespaceIndex().Value(namespaceIndex);
  Status_t status = temp->Identifer().CopyFrom(nodeIdentifier);
  if (status.IsBad())
  {
    return status;
  }

  result = temp;
  return OpcUa_Good;
}

uint32_t AddressSpaceUtilities_t::GenerateUniqueNumericIdentifier(const uint16_t namespaceIndex, IntrusivePtr_t<IAddressSpace_t>& addressSpace)
{
	uint32_t id_ = 0;
	while (!id_)
	{
		id_ = UASDK_pseudeo_random_number();

		Status_t status;
		NodeIdNumeric_t numericId_(namespaceIndex, id_);
		IntrusivePtr_t<INode_t> temp = addressSpace->FindNode(numericId_, status);
		if (temp.is_set() || (status.Value() == OpcUa_BadNodeIdExists))
		{
			id_ = 0;
		}
	}

	return id_;
}

Status_t AddressSpaceUtilities_t::GenerateStringNodeId(const uint16_t namespaceIndex, const String_t& nodeIdentifier, IntrusivePtr_t<const NodeId_t>& result)
{
  IntrusivePtr_t<NodeIdString_t> temp(new SafeRefCount_t<NodeIdString_t>());
  if (!temp.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  temp->NamespaceIndex().Value(namespaceIndex);
  Status_t status = temp->Identifer().CopyFrom(nodeIdentifier);
  if (status.IsBad())
  {
    return status;
  }

  result = temp;
  return OpcUa_Good;
}

Status_t AddressSpaceUtilities_t::GenerateGuidNodeId(const uint16_t namespaceIndex, IntrusivePtr_t<const NodeId_t>& result)
{
  Guid_t id;
  Status_t status = id.Initialise();
  if (status.IsBad())
  {
    return status;
  }

  return GenerateGuidNodeId(namespaceIndex, id, result);
}

Status_t AddressSpaceUtilities_t::GenerateGuidNodeId(const uint16_t namespaceIndex, const uint8_t* id_, IntrusivePtr_t<const NodeId_t>& result)
{
  Guid_t id;
  Status_t status = id.CopyFrom(id_);
  if (status.IsBad())
  {
    return status;
  }

  return GenerateGuidNodeId(namespaceIndex, id, result);
}

Status_t AddressSpaceUtilities_t::GenerateGuidNodeId(const uint16_t namespaceIndex, const Guid_t& guid, IntrusivePtr_t<const NodeId_t>& result)
{
  IntrusivePtr_t<NodeIdGuid_t> temp(new SafeRefCount_t<NodeIdGuid_t>());
  if (!temp.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  temp->NamespaceIndex().Value(namespaceIndex);
  Status_t status = temp->Identifer().CopyFrom(guid);
  if (status.IsBad())
  {
    return status;
  }

  result = temp;
  return OpcUa_Good;
}

Status_t AddressSpaceUtilities_t::GenerateUniqueGuidIdentifier(const uint16_t namespaceIndex, IntrusivePtr_t<IAddressSpace_t>& addressSpace, Guid_t& guid)
{
  UASDK_UNUSED(namespaceIndex);
  UASDK_UNUSED(addressSpace);

	Status_t status;

	guid.Initialise();

	return status;
}

Status_t AddressSpaceUtilities_t::GenerateOpaqueNodeId(const uint16_t namespaceIndex, IntrusivePtr_t<const NodeId_t>& result)
{
  Guid_t id;
  Status_t status = id.Initialise();
  if (status.IsBad())
  {
    return status;
  }

  ByteString_t temp;
  status = temp.CopyFrom(id.Value(), id.GUID_LENGTH);
  if (status.IsBad())
  {
    return status;
  }

  return GenerateOpaqueNodeId(namespaceIndex, temp, result);
}

Status_t AddressSpaceUtilities_t::GenerateOpaqueNodeId(const uint16_t namespaceIndex, const ByteString_t& id_, IntrusivePtr_t<const NodeId_t>& result)
{
  IntrusivePtr_t<NodeIdOpaque_t> temp(new SafeRefCount_t<NodeIdOpaque_t>());
  if (!temp.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  temp->NamespaceIndex().Value(namespaceIndex);
  Status_t status = temp->Identifer().CopyFrom(id_);
  if (status.IsBad())
  {
    return status;
  }

  result = temp;
  return OpcUa_Good;
}

Status_t AddressSpaceUtilities_t::CreateHasTypeDefintion(IAddressSpace_t& addressSpace, IntrusivePtr_t<INode_t> node, uint32_t hasTypeDefinitionId)
{
  if (!node.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  Status_t status;
  NodeIdNumeric_t variableTypeNodeId(0, hasTypeDefinitionId);
  IntrusivePtr_t<INode_t> target = addressSpace.FindNode(variableTypeNodeId, status);
  if (status.IsBad() && (status.Value() != OpcUa_BadNodeIdUnknown) )
  {
    return status;
  }

  if (target.is_set())
  {
    status = CreateReference(addressSpace, node, target, OpcUaId_HasTypeDefinition);
  }
  else
  {
    //In this case create slow forward reference only
    NodeIdNumeric_t referenceTypeNodeId(0, OpcUaId_HasTypeDefinition);
    IntrusivePtr_t<IReferenceTypeNode_t> referenceType = addressSpace.FindReferenceTypeNode(referenceTypeNodeId, status);
    if (status.IsBad() || !referenceType.is_set())
    {
      return status;
    }

    IntrusivePtr_t<NodeIdNumeric_t> slowTargetId(new SafeRefCount_t<NodeIdNumeric_t>());
    if (!slowTargetId.is_set())
    {
      return OpcUa_BadOutOfMemory;
    }
    slowTargetId->NamespaceIndex().Value(0);
    slowTargetId->Identifer().Value(hasTypeDefinitionId);

    IntrusivePtr_t<IReference_t> ref = node->ReferencesCreateReference(referenceType->NodeId(), slowTargetId, false, status);
    if (status.IsBad() || !ref.is_set())
    {
      return status;
    }
  }

  return status;
}

Status_t AddressSpaceUtilities_t::CreateReference(IAddressSpace_t& addressSpace,
                                                  IntrusivePtr_t<INode_t> sourceNode,
                                                  IntrusivePtr_t<INode_t> targetNode,
                                                  uint32_t referenceTypeId)
{
  IntrusivePtr_t<const NodeId_t> empty;
  return CreateReference(addressSpace, sourceNode, targetNode, referenceTypeId, empty);
}

Status_t AddressSpaceUtilities_t::CreateReference(IAddressSpace_t& addressSpace,
                                                  IntrusivePtr_t<INode_t> sourceNode,
                                                  IntrusivePtr_t<INode_t> targetNode,
                                                  uint32_t referenceTypeId,
                                                  IntrusivePtr_t<const NodeId_t>& viewId)
{
  if (!sourceNode.is_set() || !targetNode.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  //Create reference
  Status_t status;
  NodeIdNumeric_t referenceTypeNodeId(0, referenceTypeId);
  IntrusivePtr_t<IReferenceTypeNode_t> referenceType = addressSpace.FindReferenceTypeNode(referenceTypeNodeId, status);
  if (status.IsBad() || !referenceType.is_set())
  {
    return status;
  }

  //Forward Reference
  IntrusivePtr_t<INode_t> target = targetNode;
  IntrusivePtr_t<INode_t> source = sourceNode;

  IntrusivePtr_t<IReference_t> ref = sourceNode->ReferencesCreateReference(referenceType, target, false, status);
  if (status.IsBad() || !ref.is_set())
  {
    return status;
  }
  if (viewId.is_set())
  {
    status = ref->AddView(viewId);
    if (status.IsBad())
    {
      return status;
    }
  }

  //Inverse Reference
  ref = targetNode->ReferencesCreateReference(referenceType, source, true, status);
  if (status.IsBad() || !ref.is_set())
  {
    if (status == OpcUa_BadNotSupported)
    {
      return OpcUa_Good;
    }
    else
    {
      return status;
    }
  }
  if (viewId.is_set())
  {
    return ref->AddView(viewId);
  }

  return OpcUa_Good;
}

Status_t AddressSpaceUtilities_t::CreateSlowReference(IAddressSpace_t& addressSpace,
  IntrusivePtr_t<const NodeId_t> sourceNodeId,
  IntrusivePtr_t<const NodeId_t> targetNodeId,
  uint32_t referenceTypeId)
{
  IntrusivePtr_t<const NodeId_t> empty;
  return CreateSlowReference(addressSpace, sourceNodeId, targetNodeId, referenceTypeId, empty);
}

Status_t AddressSpaceUtilities_t::CreateSlowReference(IAddressSpace_t& addressSpace,
  IntrusivePtr_t<const NodeId_t> sourceNodeId,
  IntrusivePtr_t<const NodeId_t> targetNodeId,
  uint32_t referenceTypeId,
  IntrusivePtr_t<const NodeId_t>& viewId)
{
  if (!sourceNodeId.is_set() || !targetNodeId.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  //Create reference
  Status_t status;
  NodeIdNumeric_t referenceTypeNodeId(0, referenceTypeId);
  IntrusivePtr_t<IReferenceTypeNode_t> referenceType = addressSpace.FindReferenceTypeNode(referenceTypeNodeId, status);
  if (status.IsBad() || !referenceType.is_set())
  {
    return status;
  }

  //Forward Reference
  IntrusivePtr_t<INode_t> target = addressSpace.FindNode(*targetNodeId, status);
  if (status.IsBad() || !target.is_set())
  {
    return status;
  }

  IntrusivePtr_t<INode_t> source = addressSpace.FindNode(*sourceNodeId, status);
  if (status.IsBad() || !source.is_set())
  {
    return status;
  }

  IntrusivePtr_t<IReference_t> ref = source->ReferencesCreateReference(referenceType->NodeId(), target->NodeId(), false, status);
  if (status.IsBad() || !ref.is_set())
  {
    return status;
  }
  if (viewId.is_set())
  {
    status = ref->AddView(viewId);
    if (status.IsBad())
    {
      return status;
    }
  }

  //Inverse Reference
  ref = target->ReferencesCreateReference(referenceType->NodeId(), source->NodeId(), true, status);
  if (status.IsBad() || !ref.is_set())
  {
    return status;
  }
  if (viewId.is_set())
  {
    return ref->AddView(viewId);
  }

  return OpcUa_Good;
}

Status_t AddressSpaceUtilities_t::GetTypeDefinition(const INode_t& node, const IAddressSpace_t& addressSpace, IntrusivePtr_t<NodeId_t>& result)
{
  UASDK_UNUSED(addressSpace);

  Status_t status;
  IntrusivePtr_t<const IIterator_t<IReference_t> > references = node.ReferencesGetConstIterator(status);
  if (!references.is_set())
  {
    return status;
  }

  IntrusivePtr_t<IReference_t> reference;

  do
  {
    reference = references->Next();
    if (reference.is_set())
    {
      NodeIdNumeric_t hasTypeDefNodeID(0, OpcUaId_HasTypeDefinition);
      if (reference->TypeId().is_set() && (*reference->TypeId() == hasTypeDefNodeID) && !reference->IsInverse())
      {
        if (!reference->TargetNodeId().is_set())
        {
          return OpcUa_BadUnexpectedError;
        }
        status = reference->TargetNodeId()->CopyToNodeId(result);
        return status;
      }
    }
  } while (reference.is_set());

  UASDK_RETURN_BAD_STATUS(OpcUa_BadNotFound);
}

IntrusivePtr_t<const INode_t> AddressSpaceUtilities_t::GetTarget(const INode_t& node, const IAddressSpace_t& addressSpace, uint32_t referenceTypeId)
{
  return GetTarget(node, addressSpace, referenceTypeId, true);
}

IntrusivePtr_t<const INode_t> AddressSpaceUtilities_t::GetTarget(const INode_t& node, const IAddressSpace_t& addressSpace,
                                                 uint32_t referenceTypeId, bool isForward)
{
  IntrusivePtr_t<const INode_t> result;
  Status_t status;
  IntrusivePtr_t<const IIterator_t<IReference_t> > references = node.ReferencesGetConstIterator(status);
  if (!references.is_set() || status.IsBad())
  {
    return result;
  }

  IntrusivePtr_t<IReference_t> reference;

  do
  {
    reference = references->Next();
    if (reference.is_set())
    {
      NodeIdNumeric_t refType(0, referenceTypeId);
      if (reference->TypeId().is_set() && (*reference->TypeId() == refType) && (isForward == !reference->IsInverse()))
      {
        return reference->TargetNode(addressSpace);
      }
    }
  } while (reference.is_set());

  return result;
}

IntrusivePtr_t<INode_t> AddressSpaceUtilities_t::GetTarget(const INode_t& node, IAddressSpace_t& addressSpace,
  uint32_t referenceTypeId, bool isForward)
{
  IntrusivePtr_t<INode_t> result;
  Status_t status;
  IntrusivePtr_t<const IIterator_t<IReference_t> > references = node.ReferencesGetConstIterator(status);
  if (!references.is_set() || status.IsBad())
  {
    return result;
  }

  IntrusivePtr_t<IReference_t> reference;

  do
  {
    reference = references->Next();
    if (reference.is_set())
    {
      NodeIdNumeric_t refType(0, referenceTypeId);
      if (reference->TypeId().is_set() && (*reference->TypeId() == refType) && (isForward == !reference->IsInverse()))
      {
        return reference->TargetNode(addressSpace);
      }
    }
  } while (reference.is_set());

  return result;
}

Status_t AddressSpaceUtilities_t::GetTargets(const INode_t& node, const IAddressSpace_t& addressSpace, uint32_t referenceTypeId, IntrusiveList_t<const INode_t>& listOfTargetNodes)
{
  return GetTargets(node, addressSpace, referenceTypeId, true, listOfTargetNodes);
}

Status_t AddressSpaceUtilities_t::GetTargets(const INode_t& node, const IAddressSpace_t& addressSpace,
  uint32_t referenceTypeId, bool isForward, IntrusiveList_t<const INode_t>& listOfTargetNodes)
{
  IntrusiveList_t<const INode_t> result;
  Status_t status;
  IntrusivePtr_t<const IIterator_t<IReference_t> > references = node.ReferencesGetConstIterator(status);
  if (!references.is_set() || status.IsBad())
  {
    return status;
  }

  IntrusivePtr_t<IReference_t> reference;

  do
  {
    reference = references->Next();
    if (reference.is_set())
    {
      NodeIdNumeric_t refType(0, referenceTypeId);
      if (reference->TypeId().is_set() && (*reference->TypeId() == refType) && (isForward == !reference->IsInverse()))
      {
        if (reference->TargetNode(addressSpace).is_set())
        {
          status = listOfTargetNodes.AddToTail(*reference->TargetNode(addressSpace));
          UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
        }
      }
    }
  } while (reference.is_set());

  return status;
}

Status_t AddressSpaceUtilities_t::RemoveAllInverseReferences(IntrusivePtr_t<INode_t> node, IAddressSpace_t& addressSpace)
{
  UASDK_UNUSED(addressSpace);
  Status_t status;
  if(!node.is_set() || !node->NodeId().is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  IntrusivePtr_t<const IIterator_t<IReference_t> > refIterator = node->ReferencesGetConstIterator(status);
  if(!refIterator.is_set() || status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
  }

  IntrusivePtr_t<IReference_t> ref = refIterator->First();
  while(ref.is_set())
  {
    IntrusivePtr_t<INode_t> targetNode = ref->TargetNode();
    if(!targetNode.is_set())
    {
      ref = refIterator->Next();
      continue;
    }

    IntrusivePtr_t<IIterator_t<IReference_t> > targetRefIterator = targetNode->ReferencesGetMutableIterator(status);
    if(!refIterator.is_set() || status.IsBad())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
    }

    IntrusivePtr_t<IReference_t> targetRef = targetRefIterator->First();
    while(targetRef.is_set())
    {
      IntrusivePtr_t<IReferenceTypeNode_t> sourceRefType = ref->Type();
      IntrusivePtr_t<IReferenceTypeNode_t> targetRefType = targetRef->Type();

      if(targetRef->TargetNode().is_set() && (targetRef->TargetNode() == node) )
      {
        if(sourceRefType.is_set() && targetRefType.is_set() && (sourceRefType == targetRefType) )
        {
          status = targetRefIterator->RemoveCurrent();
        }
        else if(ref->TypeId() == targetRef->TypeId())
        {
          status = targetRefIterator->RemoveCurrent();
        }
        if(status.IsGood())
        {
          break;
        }
      }
      else if( node->NodeId().is_set() && targetRef->TargetNodeId().is_set() && (*targetRef->TargetNodeId() == *(node->NodeId()) ) )
      {
        if(sourceRefType.is_set() && targetRefType.is_set() && (sourceRefType == targetRefType) )
        {
          status = targetRefIterator->RemoveCurrent();
        }
        else if(ref->TypeId() == targetRef->TypeId())
        {
          status = targetRefIterator->RemoveCurrent();
        }
        if(status.IsGood())
        {
          break;
        }
      }

      targetRef = targetRefIterator->Next();
    }

    ref = refIterator->Next();
  }

  return status;
}

bool AddressSpaceUtilities_t::IsMethodAComponentOfObject(const IMethodNode_t& method, const INode_t& object, const IAddressSpace_t& addressSpace)
{
  UASDK_UNUSED(addressSpace);
  IntrusivePtr_t<const INode_t> result;
  Status_t status;
  IntrusivePtr_t<const NodeId_t> targetId = method.NodeId();
  if (!targetId.is_set())
  {
    return false;
  }

  IntrusivePtr_t<const IIterator_t<IReference_t> > references = object.ReferencesGetConstIterator(status);
  if (!references.is_set())
  {
    return false;
  }

  IntrusivePtr_t<IReference_t> reference;
  do
  {
    reference = references->Next();
    if (reference.is_set())
    {
      NodeIdNumeric_t refType(0, OpcUaId_HasComponent);
      if (reference->TypeId().is_set() && (*reference->TypeId() == refType) && !(reference->IsInverse())
        && reference->TargetNodeId().is_set() && (*reference->TargetNodeId() == *targetId))
      {
        return true;
      }
    }
  } while (reference.is_set());

  return false;
}

bool AddressSpaceUtilities_t::IsMethodAComponentOfObjectOrParent(const IMethodNode_t& method, const INode_t& object, const IAddressSpace_t& addressSpace, bool loopParent, uint32_t parentId)
{
  UASDK_UNUSED(addressSpace);
  IntrusivePtr_t<const INode_t> result;
  Status_t status;
  IntrusivePtr_t<const NodeId_t> targetId = method.NodeId();
  if (!targetId.is_set())
  {
    return false;
  }

  IntrusivePtr_t<const IIterator_t<IReference_t> > references = object.ReferencesGetConstIterator(status);
  if (!references.is_set())
  {
    return false;
  }

  IntrusivePtr_t<IReference_t> reference;
  NodeIdNumeric_t baseEventTypeId(0, parentId);
  IntrusivePtr_t<const NodeId_t> conditionTypeId = object.NodeId();

  do
  {
    do
    {
      reference = references->Next();
      if (reference.is_set())
      {
        NodeIdNumeric_t refType(0, OpcUaId_HasComponent);
        if (reference->TypeId().is_set() && (*reference->TypeId() == refType) && !(reference->IsInverse())
          && reference->TargetNodeId().is_set() && (*reference->TargetNodeId() == *targetId))
        {
          return true;
        }
      }
    } while (reference.is_set());

    if (!loopParent)
    {
      return false;
    }

    if (!conditionTypeId.is_set())
    {
      return false;
    }

    IntrusivePtr_t<const INode_t> conditionTypeNode = addressSpace.FindNode(*conditionTypeId, status);
    if (status.IsBad() || !conditionTypeNode.is_set())
    {
      return false;
    }

    IntrusivePtr_t<const INode_t> superType = GetTarget(*conditionTypeNode, addressSpace, OpcUaId_HasSubtype, false);
    if (!superType.is_set())
    {
      return false;
    }
    conditionTypeId = superType->NodeId();

    references = superType->ReferencesGetConstIterator(status);
    if (status.IsBad())
    {
      return false;
    }

  } while (conditionTypeId.is_set() && (*conditionTypeId != baseEventTypeId));

  return false;
}

#if (UASDK_INCLUDE_METHOD_SERVICE_SET > 0)

uasdk::Status_t AddressSpaceUtilities_t::ValidateInputArguments(
  const ArrayUA_t<BaseDataType_t>& inputArguments,
  const IMethodNode_t& method,
  const IAddressSpace_t& addressSpace,
  ArrayUA_t<StatusCode_t>& inputArgumentResults)
{
  Status_t callOperationResult = OpcUa_Good;

  IntrusivePtr_t<const IVariableNode_t> inputArgumentsNode;
  String_t browseName;
  Status_t status = browseName.CopyFrom("InputArguments");
  if (status.IsBad())
  {
    return status;
  }
  status = AddressSpaceUtilities_t::GetProperty(
    method,
    addressSpace,
    browseName,
    inputArgumentsNode);
  if (status.IsBad() || !inputArgumentsNode.is_set())
  {
    if( (status.Value() == OpcUa_BadNotFound) && (inputArguments.Size() == 0) )
    {
      return OpcUa_Good;
    }
    else
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
    }
  }

  IntrusivePtr_t<const DataValue_t> inputArgs = inputArgumentsNode->Value();
  if (!inputArgs.is_set() || !inputArgs->Value().is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  const ArrayUA_t<Argument_t>* args = RuntimeCast<const ArrayUA_t<Argument_t>* >(*inputArgs->Value());
  if (args == 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  if (args->Count() > inputArguments.Count())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadArgumentsMissing);
  }
  else if (args->Count() < inputArguments.Count())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  uint32_t count = args->Count();

  status = inputArgumentResults.Initialise(count);
  if (status.IsBad())
  {
    return status;
  }

  for (uint32_t i = 0; i < count; i++)
  {
    IntrusivePtr_t<Argument_t> argument = (*args)[i];
    IntrusivePtr_t<BaseDataType_t> inputArgument = inputArguments[i];

    if (!argument.is_set() || !inputArgument.is_set())
    {
      inputArgumentResults.DeleteAll();
      UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
    }

    IntrusivePtr_t<StatusCode_t> result = new SafeRefCount_t<StatusCode_t>();
    if (!result.is_set())
    {
      inputArgumentResults.DeleteAll();
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }

    inputArgumentResults[i] = result;

    IntrusivePtr_t<NodeId_t> dataType = argument->DataType();
    uint16_t namespaceIndex = 0;
    uint32_t identifier = inputArgument->TypeId(namespaceIndex);
    NodeIdNumeric_t inputArgDataType(namespaceIndex, identifier);

    if ((!argument->DataType().is_set())
      || (*dataType != inputArgDataType)
      || ((argument->ValueRank().Value() >= 0) && (!inputArgument->IsArray()))
      || ((argument->ValueRank().Value() == -1) && (inputArgument->IsArray())))
    {
      callOperationResult = OpcUa_BadInvalidArgument;
      *inputArgumentResults[i] = callOperationResult;
    }
  }
  return callOperationResult;
}
#endif

bool AddressSpaceUtilities_t::IsAaChildOfB(const NodeId_t& refTypeA, const NodeId_t& refTypeB, const IAddressSpace_t& addressSpace)
{
  if (refTypeA == refTypeB)
  {
	return true;
  }

  NodeIdNumeric_t baseType(0, ref_type_References);
  if (refTypeA == baseType)
  {
    return true;
  }

  Status_t status;
  IntrusivePtr_t<const INode_t> currentNode = addressSpace.FindNode(refTypeA, status);
  if (!currentNode.is_set())
  {
    return false;
  }

  IntrusivePtr_t<const INode_t> parentNode;
  do
  {
    parentNode = GetTarget(*currentNode, addressSpace, OpcUaId_HasSubtype, false);
    if (parentNode.is_set())
    {
      if (*parentNode->NodeId() == refTypeB)
      {
        return true;
      }
      else
      {
        currentNode = parentNode;
      }
    }
  } while(parentNode.is_set());
  return false;
}

Status_t AddressSpaceUtilities_t::GetProperty(const INode_t& node,
                                              const IAddressSpace_t& addressSpace,
                                              const String_t& browseName,
                                              IntrusivePtr_t<const IVariableNode_t>& result)
{
  IntrusivePtr_t<const INode_t> propertyNode;
	Status_t status = GetNodeWithReferenceType(node, addressSpace, browseName, OpcUaId_HasProperty, propertyNode);
  if (status.IsBad() || !propertyNode.is_set())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  result = NodeDownCast<const IVariableNode_t>(*propertyNode);
  return OpcUa_Good;
}

Status_t AddressSpaceUtilities_t::GetProperty(const INode_t& node,
	IAddressSpace_t& addressSpace,
	const String_t& browseName,
	IntrusivePtr_t<IVariableNode_t>& result)
{
  IntrusivePtr_t<INode_t> propertyNode;
  Status_t status = GetNodeWithReferenceType(node, addressSpace, browseName, OpcUaId_HasProperty, propertyNode);
  if (status.IsBad() || !propertyNode.is_set())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  result = NodeDownCast<IVariableNode_t>(*propertyNode);
  return OpcUa_Good;
}

Status_t AddressSpaceUtilities_t::GetNodeWithReferenceType(const INode_t& node, const IAddressSpace_t& addressSpace, const String_t& browseName, uint32_t referenceType, IntrusivePtr_t<const INode_t>& result)
{
	Status_t status;
	IntrusivePtr_t<const IIterator_t<IReference_t> > references = node.ReferencesGetConstIterator(status);
	if (!references.is_set())
	{
		return status;
	}

	IntrusivePtr_t<IReference_t> reference;

	do
	{
		reference = references->Next();
		if (reference.is_set())
		{
			NodeIdNumeric_t refType(0, referenceType);
			if (reference->TypeId().is_set() && (*reference->TypeId() == refType) && !reference->IsInverse())
			{
				//Check browse name
				IntrusivePtr_t<const INode_t> target = reference->TargetNode(addressSpace);
				if (target.is_set() && (target->BrowseName()->Name() == browseName))
				{
					result = target;
					if (result.is_set())
					{
						return OpcUa_Good;
					}
					else
					{
						UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
					}
				}
			}
		}
	} while (reference.is_set());

	return OpcUa_BadNotFound;
}

Status_t AddressSpaceUtilities_t::GetNodeWithReferenceType(const INode_t& node, IAddressSpace_t& addressSpace, const String_t& browseName, uint32_t referenceType, IntrusivePtr_t<INode_t>& result)
{
	Status_t status;
	IntrusivePtr_t<const IIterator_t<IReference_t> > references = node.ReferencesGetConstIterator(status);
	if (!references.is_set())
	{
		return status;
	}

	IntrusivePtr_t<IReference_t> reference;

	do
	{
		reference = references->Next();
		if (reference.is_set())
		{
			NodeIdNumeric_t refType(0, referenceType);
			if (reference->TypeId().is_set() && (*reference->TypeId() == refType) && !reference->IsInverse())
			{
				//Check browse name
				IntrusivePtr_t<INode_t> target = reference->TargetNode(addressSpace);
				if (target.is_set() && (target->BrowseName()->Name() == browseName))
				{
					result = NodeDownCast<IVariableNode_t>(*target);
					if (result.is_set())
					{
						return OpcUa_Good;
					}
					else
					{
						UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
					}
				}
			}
		}
	} while (reference.is_set());

	return OpcUa_BadNotFound;
}

Status_t AddressSpaceUtilities_t::GetReference(const INode_t& node, uint32_t referenceType, bool forwardReference, IntrusivePtr_t<const IReference_t>& result)
{
  Status_t status;
  IntrusivePtr_t<const IIterator_t<IReference_t> > references = node.ReferencesGetConstIterator(status);
  if (!references.is_set())
  {
    return status;
  }

  IntrusivePtr_t<IReference_t> reference;

  do
  {
    reference = references->Next();
    if (reference.is_set())
    {
      NodeIdNumeric_t refType(0, referenceType);
      if (reference->TypeId().is_set() && (*reference->TypeId() == refType) && (reference->IsInverse() == !forwardReference))
      {
        result = reference;
        return OpcUa_Good;
      }
    }
  } while (reference.is_set());

  return OpcUa_BadNotFound;
}

Status_t AddressSpaceUtilities_t::GetReference(const INode_t& node, uint32_t referenceType, bool forwardReference, IntrusivePtr_t<IReference_t>& result)
{
  Status_t status;
  IntrusivePtr_t<const IIterator_t<IReference_t> > references = node.ReferencesGetConstIterator(status);
  if (!references.is_set())
  {
    return status;
  }

  IntrusivePtr_t<IReference_t> reference;

  do
  {
    reference = references->Next();
    if (reference.is_set())
    {
      NodeIdNumeric_t refType(0, referenceType);
      if (reference->TypeId().is_set() && (*reference->TypeId() == refType) && (reference->IsInverse() == !forwardReference))
      {
        result = reference;
        return OpcUa_Good;
      }
    }
  } while (reference.is_set());

  return OpcUa_BadNotFound;
}

Status_t AddressSpaceUtilities_t::RangeCheck(const Range_t& range, const BaseDataType_t& value)
{
  bool inRange = false;
  Status_t status;
  uint16_t namespaceIndex = 0;
  uint32_t typeId = value.TypeId(namespaceIndex);
  switch (typeId)
  {
    case OpcUaId_Byte:
      inRange = IsInRange<Byte_t>(range, value, status);
      break;

    case OpcUaId_SByte:
      inRange = IsInRange<SByte_t>(range, value, status);
      break;

    case OpcUaId_Int16:
      inRange = IsInRange<Int16_t>(range, value, status);
      break;

    case OpcUaId_UInt16:
      inRange = IsInRange<UInt16_t>(range, value, status);
      break;

    case OpcUaId_Int32:
      inRange = IsInRange<Int32_t>(range, value, status);
      break;

    case OpcUaId_UInt32:
      inRange = IsInRange<UInt32_t>(range, value, status);
      break;

    case OpcUaId_Int64:
      inRange = IsInRange<Int64_t>(range, value, status);
      break;

    case OpcUaId_UInt64:
      inRange = IsInRange<UInt64_t>(range, value, status);
      break;

    case OpcUaId_Double:
      inRange = IsInRange<Double_t>(range, value, status);
      break;

    case OpcUaId_Float:
      inRange = IsInRange<Float_t>(range, value, status);
      break;

#if (UASDK_INCLUDE_ADDITIONAL_DA_TYPES > 0)
    case OpcUaId_XVType:
      {
        if(value.IsArray())
        {
          //Array of structure write operation is not supported for now
          UASDK_RETURN_BAD_STATUS(OpcUa_BadNotSupported);
        }
        else
        {
          const XVType_t* xvTypeValue = RuntimeCast<const XVType_t*>(value);
          if(!xvTypeValue)
          {
            UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
          }

          inRange = IsInRange<Float_t>(range, xvTypeValue->Value(), status);
        }
      }
      break;

    case OpcUaId_ComplexNumberType:
      //TODO - If ComplexNumberType need to be checked for Range, then Application developer has to implement the logic here
      break;

    case OpcUaId_DoubleComplexNumberType:
      //TODO - If DoubleComplexNumberType need to be checked for Range, then Application developer has to implement the logic here
      break;
#endif

    default:
      UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  if (status.IsBad() || (inRange != true))
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  return OpcUa_Good;
}

bool AddressSpaceUtilities_t::IsAttributePresent(AttributeId_t::Enum_t attributeId, NodeClass_t::Enum_t nodeClass)
{
  switch (attributeId)
  {
    case AttributeId_t::ATTRIBUTE_ID_NODEID:
    case AttributeId_t::ATTRIBUTE_ID_NODECLASS:
    case AttributeId_t::ATTRIBUTE_ID_BROWSENAME:
    case AttributeId_t::ATTRIBUTE_ID_DISPLAYNAME:
    case AttributeId_t::ATTRIBUTE_ID_DESCRIPTION:
    case AttributeId_t::ATTRIBUTE_ID_WRITEMASK:
    case AttributeId_t::ATTRIBUTE_ID_USERWRITEMASK:
      return true;

    case AttributeId_t::ATTRIBUTE_ID_ISABSTRACT:
    {
      switch (nodeClass)
      {
      case NodeClass_t::OPCUA_NODECLASS_REFERENCE_TYPE:
      case NodeClass_t::OPCUA_NODECLASS_OBJECT_TYPE:
      case NodeClass_t::OPCUA_NODECLASS_VARIABLE_TYPE:
        return true;

      default:
        return false;
      }
    }
    break;

    case AttributeId_t::ATTRIBUTE_ID_SYMMETRIC:
    case AttributeId_t::ATTRIBUTE_ID_INVERSENAME:
      switch (nodeClass)
      {
      case NodeClass_t::OPCUA_NODECLASS_REFERENCE_TYPE:
        return true;

      default:
        return false;
      }
      break;

    case AttributeId_t::ATTRIBUTE_ID_CONTAINSNOLOOPS:
      switch (nodeClass)
      {
      case NodeClass_t::OPCUA_NODECLASS_VIEW:
        return true;

      default:
        return false;
      }
      break;

    case AttributeId_t::ATTRIBUTE_ID_EVENTNOTIFIER:
      switch (nodeClass)
      {
      case NodeClass_t::OPCUA_NODECLASS_VIEW:
      case NodeClass_t::OPCUA_NODECLASS_OBJECT:
        return true;

      default:
        return false;
      }
      break;

    case AttributeId_t::ATTRIBUTE_ID_VALUE:
    case AttributeId_t::ATTRIBUTE_ID_DATATYPE:
    case AttributeId_t::ATTRIBUTE_ID_VALUERANK:
    case AttributeId_t::ATTRIBUTE_ID_ARRAYDIMENSIONS:
      switch (nodeClass)
      {
      case NodeClass_t::OPCUA_NODECLASS_VARIABLE:
      case NodeClass_t::OPCUA_NODECLASS_VARIABLE_TYPE:
        return true;

      default:
        return false;
      }
      break;

      case AttributeId_t::ATTRIBUTE_ID_ACCESSLEVEL:
      case AttributeId_t::ATTRIBUTE_ID_USERACCESSLEVEL:
      case AttributeId_t::ATTRIBUTE_ID_MINIMUMSAMPLINGINTERVAL:
      case AttributeId_t::ATTRIBUTE_ID_HISTORIZING:
        switch (nodeClass)
        {
        case NodeClass_t::OPCUA_NODECLASS_VARIABLE:
          return true;

        default:
          return false;
        }
        break;

    case AttributeId_t::ATTRIBUTE_ID_EXECUTABLE:
    case AttributeId_t::ATTRIBUTE_ID_USEREXECUTABLE:
      switch (nodeClass)
      {
      case NodeClass_t::OPCUA_NODECLASS_METHOD:
        return true;

      default:
        return false;
      }
      break;

    default:
      return false;
  }
}

Status_t AddressSpaceUtilities_t::ReadNodeAttributeSynchronously(const INode_t& node,
                                                                 AttributeId_t::Enum_t attributeId,
                                                                 const IUserPermissions_t& userPermissions,
                                                                 const ArrayUA_t<String_t>& locales,
                                                                 uint32_t maxAge,
                                                                 uint32_t timeoutHint,
                                                                 TimestampsToReturn_t::Enum_t timestamps,
                                                                 const Array_t<IndexRange_t>& indexRange,
                                                                 DataValue_t& result)
{
  Status_t status;

  switch (attributeId)
  {
    case AttributeId_t::ATTRIBUTE_ID_NODEID:
      return node.NodeId()->CopyTo(result.Value());

    case AttributeId_t::ATTRIBUTE_ID_NODECLASS:
    {
      IntrusivePtr_t<NodeClass_t> temp = new SafeRefCount_t<NodeClass_t>();
      if (!temp.is_set())
      {
        UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
      }
      *temp = node.NodeClass();
      result.Value() = temp;
      return OpcUa_Good;
    }

    case AttributeId_t::ATTRIBUTE_ID_BROWSENAME:
    {
      IntrusivePtr_t<const QualifiedName_t> temp = node.BrowseName();
      if (!temp.is_set())
      {
        UASDK_RETURN_BAD_STATUS(OpcUa_BadNotReadable);
      }
      return temp->CopyTo(result.Value());
    }

    case AttributeId_t::ATTRIBUTE_ID_DISPLAYNAME:
    {
      IntrusivePtr_t<const LocalizedText_t> temp = node.DisplayName(locales, status);
      if (!temp.is_set())
      {
        UASDK_RETURN_BAD_STATUS(OpcUa_BadNotReadable);
      }
      return temp->CopyTo(result.Value());
    }

    case AttributeId_t::ATTRIBUTE_ID_DESCRIPTION:
    {
      IntrusivePtr_t<const LocalizedText_t> temp = node.Description(locales, status);
      if (!temp.is_set())
      {
        IntrusivePtr_t<LocalizedText_t> temp = new SafeRefCount_t<LocalizedText_t>();
        result.Value() = temp;
        return OpcUa_Good;
      }
      return temp->CopyTo(result.Value());
    }

    case AttributeId_t::ATTRIBUTE_ID_WRITEMASK:
    {
      IntrusivePtr_t<WriteMask_t> temp = new SafeRefCount_t<WriteMask_t>();
      if (!temp.is_set())
      {
        UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
      }
      *temp = node.WriteMask();
      result.Value() = temp;
      return OpcUa_Good;
    }

    case AttributeId_t::ATTRIBUTE_ID_USERWRITEMASK:
    {
      IntrusivePtr_t<WriteMask_t> temp = new SafeRefCount_t<WriteMask_t>();
      if (!temp.is_set())
      {
        UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
      }
      *temp = node.UserWriteMask(userPermissions);
      result.Value() = temp;
      return OpcUa_Good;
    }

    default:
      break;
  }

  switch (node.NodeClass())
  {
    case NodeClass_t::OPCUA_NODECLASS_DATA_TYPE:
      {
        IntrusivePtr_t<const IDataTypeNode_t> concreteNode = AddressSpaceUtilities_t::NodeDownCast<IDataTypeNode_t>(node);
        if (!concreteNode.is_set())
        {
          UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
        }

        switch (attributeId)
        {
          case AttributeId_t::ATTRIBUTE_ID_ISABSTRACT:
          {
            IntrusivePtr_t<Boolean_t> temp = new SafeRefCount_t<Boolean_t>();
            if (!temp.is_set())
            {
              UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
            }
            *temp = concreteNode->IsAbstract();
            result.Value() = temp;
            return OpcUa_Good;
          }

          default:
            break;
        }
      }
      break;

    case NodeClass_t::OPCUA_NODECLASS_METHOD:
      {
        IntrusivePtr_t<const IMethodNode_t> concreteNode = AddressSpaceUtilities_t::NodeDownCast<IMethodNode_t>(node);
        if (!concreteNode.is_set())
        {
          UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
        }

        switch (attributeId)
        {
          case AttributeId_t::ATTRIBUTE_ID_EXECUTABLE:
          {
            IntrusivePtr_t<Boolean_t> temp = new SafeRefCount_t<Boolean_t>();
            if (!temp.is_set())
            {
              UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
            }
            *temp = concreteNode->Executable();
            result.Value() = temp;
            return OpcUa_Good;
          }

          case AttributeId_t::ATTRIBUTE_ID_USEREXECUTABLE:
          {
            IntrusivePtr_t<Boolean_t> temp = new SafeRefCount_t<Boolean_t>();
            if (!temp.is_set())
            {
              UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
            }
            *temp = concreteNode->UserExecutable(userPermissions);
            result.Value() = temp;
            return OpcUa_Good;
          }

          default:
            break;
        }
      }
      break;

    case NodeClass_t::OPCUA_NODECLASS_OBJECT:
      {
        IntrusivePtr_t<const IObjectNode_t> concreteNode = AddressSpaceUtilities_t::NodeDownCast<IObjectNode_t>(node);
        if (!concreteNode.is_set())
        {
          UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
        }

        switch (attributeId)
        {
          case AttributeId_t::ATTRIBUTE_ID_EVENTNOTIFIER:
          {
            IntrusivePtr_t<Byte_t> temp = new SafeRefCount_t<Byte_t>();
            if (!temp.is_set())
            {
              UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
            }
            *temp = concreteNode->EventNotifier();
            result.Value() = temp;
            return OpcUa_Good;
          }

          default:
            break;
        }
      }
      break;

    case NodeClass_t::OPCUA_NODECLASS_OBJECT_TYPE:
      {
        IntrusivePtr_t<const IObjectTypeNode_t> concreteNode = AddressSpaceUtilities_t::NodeDownCast<IObjectTypeNode_t>(node);
        if (!concreteNode.is_set())
        {
          UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
        }

        switch (attributeId)
        {
          case AttributeId_t::ATTRIBUTE_ID_ISABSTRACT:
          {
            IntrusivePtr_t<Boolean_t> temp = new SafeRefCount_t<Boolean_t>();
            if (!temp.is_set())
            {
              UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
            }
            *temp = concreteNode->IsAbstract();
            result.Value() = temp;
            return OpcUa_Good;
          }

          default:
            break;
        }
      }
      break;

    case NodeClass_t::OPCUA_NODECLASS_REFERENCE_TYPE:
      {
        IntrusivePtr_t<const IReferenceTypeNode_t> concreteNode = AddressSpaceUtilities_t::NodeDownCast<IReferenceTypeNode_t>(node);
        if (!concreteNode.is_set())
        {
          UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
        }

        switch (attributeId)
        {
          case AttributeId_t::ATTRIBUTE_ID_ISABSTRACT:
          {
            IntrusivePtr_t<Boolean_t> temp = new SafeRefCount_t<Boolean_t>();
            if (!temp.is_set())
            {
              UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
            }
            *temp = concreteNode->IsAbstract();
            result.Value() = temp;
            return OpcUa_Good;
          }

          case AttributeId_t::ATTRIBUTE_ID_SYMMETRIC:
          {
            IntrusivePtr_t<Boolean_t> temp = new SafeRefCount_t<Boolean_t>();
            if (!temp.is_set())
            {
              UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
            }
            *temp = concreteNode->Symmetric();
            result.Value() = temp;
            return OpcUa_Good;
          }

          case AttributeId_t::ATTRIBUTE_ID_INVERSENAME:
          {
            IntrusivePtr_t<const LocalizedText_t> temp = concreteNode->InverseName(locales, status);
            if (!temp.is_set())
            {
              UASDK_RETURN_BAD_STATUS(OpcUa_BadNotReadable);
            }
            return temp->CopyTo(result.Value());
          }

          default:
            break;
        }
      }
      break;

    case NodeClass_t::OPCUA_NODECLASS_VARIABLE:
      {
        IntrusivePtr_t<const IVariableNode_t> concreteNode = AddressSpaceUtilities_t::NodeDownCast<IVariableNode_t>(node);
        if (!concreteNode.is_set())
        {
          UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
        }

        switch (attributeId)
        {
          case AttributeId_t::ATTRIBUTE_ID_VALUE:
          {
            bool readFromReaderWriter = false;
            IntrusivePtr_t<const DataValue_t> val = concreteNode->Value();
            if (!val.is_set())
            {
              if(!concreteNode->CanReadValueSynchronously())
              {
                UASDK_RETURN_BAD_STATUS(OpcUa_BadNotReadable);
              }

              IntrusivePtr_t<DataValue_t> temp;
              IntrusivePtr_t<DiagnosticInfo_t> diagnosticInfo;
              status = concreteNode->ReadValue(maxAge, timestamps, locales, indexRange, 0, timeoutHint, temp, diagnosticInfo);
              if(status.IsBad() || !temp.is_set())
              {
                return status;
              }

              val = temp;
              readFromReaderWriter = true;
            }

            if(!val->Value().is_set())
            {
              UASDK_RETURN_BAD_STATUS(OpcUa_BadNotReadable);
            }

            IntrusivePtr_t<DateTime_t> serverTimestamp = result.ServerTimestamp();

            if(!readFromReaderWriter && !indexRange.IsEmpty())
            {
              IntrusivePtr_t<BaseDataType_t> temp;
              status = val->WriteSubsetTo(indexRange, temp);
              if (status == OpcUa_BadIndexRangeNoData)
              {
                if (!result.StatusCode().is_set())
                {
                  result.StatusCode() = new SafeRefCount_t<StatusCode_t>();
                  if (!result.StatusCode().is_set())
                  {
                    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
                  }
                }
                *result.StatusCode() = status;
                return OpcUa_Good;
              }
              else if (status.IsBad())
              {
                return status;
              }
              status = result.CopyFrom(*temp);
              if (status.IsBad())
              {
                return status;
              }
            }
            else
            {
              status = result.CopyFrom(*val);
            }
            if (status.IsBad())
            {
              return status;
            }

            if( ((timestamps == TimestampsToReturn_t::RETURN_NEITHER) || (timestamps == TimestampsToReturn_t::RETURN_SERVER)) && result.SourceTimestamp().is_set())
            {
              IntrusivePtr_t<DateTime_t> empty;
              result.SourceTimestamp() = empty;
            }

            result.ServerTimestamp() = serverTimestamp;

            return OpcUa_Good;
          }

          case AttributeId_t::ATTRIBUTE_ID_DATATYPE:
          {
            IntrusivePtr_t<const NodeId_t> temp = concreteNode->DataType();
            if (!temp.is_set())
            {
              UASDK_RETURN_BAD_STATUS(OpcUa_BadNotReadable);
            }
            return temp->CopyTo(result.Value());
          }

          case AttributeId_t::ATTRIBUTE_ID_VALUERANK:
          {
            IntrusivePtr_t<Int32_t> temp = new SafeRefCount_t<Int32_t>();
            if (!temp.is_set())
            {
              UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
            }
            *temp = concreteNode->ValueRank();
            result.Value() = temp;
            return OpcUa_Good;
          }

          case AttributeId_t::ATTRIBUTE_ID_ARRAYDIMENSIONS:
            if (!indexRange.IsEmpty() && concreteNode->ArrayDimensions().is_set())
            {
              IntrusivePtr_t<BaseDataType_t> temp;
              IntrusivePtr_t<const DateTime_t> serverTimestamp = result.ServerTimestamp();

              if(!indexRange.IsEmpty())
              {
                status = concreteNode->ArrayDimensions()->WriteSubsetTo(indexRange, temp);
              }
              else
              {
                status = concreteNode->ArrayDimensions()->CopyTo(temp);
              }

              if (status.IsGood())
              {
                result.Value() = temp;
              }
            }
            else
            {
              IntrusivePtr_t<const ArrayUA_t<UInt32_t> > temp = concreteNode->ArrayDimensions();
              if (!temp.is_set())
              {
                IntrusivePtr_t< ArrayUA_t<UInt32_t> > ptr (new SafeRefCount_t<ArrayUA_t<UInt32_t> >());
                result.Value() = ptr;
                return OpcUa_Good;
              }
              return temp->CopyTo(result.Value());
            }
            return OpcUa_Good;

          case AttributeId_t::ATTRIBUTE_ID_ACCESSLEVEL:
          {
            IntrusivePtr_t<AccessLevel_t> temp = new SafeRefCount_t<AccessLevel_t>();
            if (!temp.is_set())
            {
              UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
            }
            *temp = concreteNode->AccessLevel();
            result.Value() = temp;
            return OpcUa_Good;
          }

          case AttributeId_t::ATTRIBUTE_ID_USERACCESSLEVEL:
          {
            IntrusivePtr_t<AccessLevel_t> temp = new SafeRefCount_t<AccessLevel_t>();
            if (!temp.is_set())
            {
              UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
            }
            *temp = concreteNode->UserAccessLevel(userPermissions);
            result.Value() = temp;
            return OpcUa_Good;
          }

          case AttributeId_t::ATTRIBUTE_ID_MINIMUMSAMPLINGINTERVAL:
          {
            IntrusivePtr_t<Duration_t> temp = new SafeRefCount_t<Duration_t>();
            if (!temp.is_set())
            {
              UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
            }
            *temp = concreteNode->MinimumSamplingInterval();
            result.Value() = temp;
            return OpcUa_Good;
          }

          case AttributeId_t::ATTRIBUTE_ID_HISTORIZING:
          {
            IntrusivePtr_t<Boolean_t> temp = new SafeRefCount_t<Boolean_t>();
            if (!temp.is_set())
            {
              UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
            }
            *temp = concreteNode->Historizing();
            result.Value() = temp;
            return OpcUa_Good;
          }

          default:
            break;
        }
      }
      break;

    case NodeClass_t::OPCUA_NODECLASS_VARIABLE_TYPE:
      {
        IntrusivePtr_t<const IVariableTypeNode_t> concreteNode = AddressSpaceUtilities_t::NodeDownCast<IVariableTypeNode_t>(node);
        if (!concreteNode.is_set())
        {
          UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
        }

        switch (attributeId)
        {
          case AttributeId_t::ATTRIBUTE_ID_VALUE:
          {
            if (!concreteNode->Value().is_set())
            {
              UASDK_RETURN_BAD_STATUS(OpcUa_BadNotReadable);
            }
            IntrusivePtr_t<DateTime_t> serverTimestamp = result.ServerTimestamp();

            if(!indexRange.IsEmpty())
            {
              IntrusivePtr_t<BaseDataType_t> temp;
              status = concreteNode->Value()->WriteSubsetTo(indexRange, temp);
              if (status.IsBad())
              {
                return status;
              }
              status = result.CopyFrom(*temp);
              if (status.IsBad())
              {
                return status;
              }
            }
            else
            {
              status = result.CopyFrom(*concreteNode->Value());
            }
            if (status.IsBad())
            {
              return status;
            }
            result.ServerTimestamp() = serverTimestamp;
            return OpcUa_Good;
          }
            break;

          case AttributeId_t::ATTRIBUTE_ID_DATATYPE:
          {
            IntrusivePtr_t<const NodeId_t> temp = concreteNode->DataType();
            if (!temp.is_set())
            {
              UASDK_RETURN_BAD_STATUS(OpcUa_BadNotReadable);
            }
            return temp->CopyTo(result.Value());
          }

          case AttributeId_t::ATTRIBUTE_ID_VALUERANK:
          {
            IntrusivePtr_t<Int32_t> temp = new SafeRefCount_t<Int32_t>();
            if (!temp.is_set())
            {
              UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
            }
            *temp = concreteNode->ValueRank();
            result.Value() = temp;
            return OpcUa_Good;
          }

          case AttributeId_t::ATTRIBUTE_ID_ARRAYDIMENSIONS:
            if (!indexRange.IsEmpty() && concreteNode->ArrayDimensions().is_set())
            {
              IntrusivePtr_t<BaseDataType_t> temp;

              if(!indexRange.IsEmpty())
              {
                status = concreteNode->ArrayDimensions()->WriteSubsetTo(indexRange, temp);
              }
              else
              {
                status = concreteNode->ArrayDimensions()->CopyTo(temp);
              }

              if (status.IsGood())
              {
                result.Value() = temp;
              }
            }
            else
            {
              IntrusivePtr_t<const ArrayUA_t<UInt32_t> > temp = concreteNode->ArrayDimensions();
              if (!temp.is_set())
              {
                IntrusivePtr_t< ArrayUA_t<UInt32_t> > ptr (new SafeRefCount_t<ArrayUA_t<UInt32_t> >());
                result.Value() = ptr;
                return OpcUa_Good;
              }
              return temp->CopyTo(result.Value());
            }
            return OpcUa_Good;

          case AttributeId_t::ATTRIBUTE_ID_ISABSTRACT:
          {
            IntrusivePtr_t<Boolean_t> temp = new SafeRefCount_t<Boolean_t>();
            if (!temp.is_set())
            {
              UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
            }
            *temp = concreteNode->IsAbstract();
            result.Value() = temp;
            return OpcUa_Good;
          }

          default:
            break;
        }
      }
      break;

    case NodeClass_t::OPCUA_NODECLASS_VIEW:
      {
        IntrusivePtr_t<const IViewNode_t> concreteNode = AddressSpaceUtilities_t::NodeDownCast<IViewNode_t>(node);
        if (!concreteNode.is_set())
        {
          UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
        }

        switch (attributeId)
        {
          case AttributeId_t::ATTRIBUTE_ID_CONTAINSNOLOOPS:
          {
            IntrusivePtr_t<Boolean_t> temp = new SafeRefCount_t<Boolean_t>();
            if (!temp.is_set())
            {
              UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
            }
            *temp = concreteNode->ContainsNoLoops();
            result.Value() = temp;
            return OpcUa_Good;
          }

          case AttributeId_t::ATTRIBUTE_ID_EVENTNOTIFIER:
          {
            IntrusivePtr_t<Byte_t> temp = new SafeRefCount_t<Byte_t>();
            if (!temp.is_set())
            {
              UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
            }
            *temp = concreteNode->EventNotifier();
            result.Value() = temp;
            return OpcUa_Good;
          }

          default:
            break;
        }
      }
      break;

    default:
      break;
  }

  UASDK_RETURN_BAD_STATUS(OpcUa_BadAttributeIdInvalid);
}

}

