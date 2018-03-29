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

#include "uasdk_includes.h"

#if ((UASDK_INCLUDE_SERVER > 0) && (UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

#include "address_space_modeler_t.h"

#include "address_space_utilities_t.h"
#include "browse_names_t.h"

#include "opcua_boolean_t.h"
#include "opcua_uint64_t.h"
#include "opcua_sbyte_t.h"
#include "opcua_xml_element_t.h"
#include "opcua_float_t.h"
#include "opcua_duration_t.h"
#include "opcua_int16_t.h"
#include "opcua_byte_t.h"

namespace uasdk
{

/*
* Private function
*/
Status_t AddressSpaceModeler_t::AssignValue(const BaseDataType_t& sourceValue, IVariableNode_t& node)
{
  IntrusivePtr_t<DataValue_t> value;
  Status_t status = ReadValue(sourceValue, true, OpcUa_Good, value);
  if (status.IsBad() || !value.is_set())
  {
    return status;
  }

  return node.Value(value);
}

Status_t AddressSpaceModeler_t::AddArugmentsToMethod(const IMethodNode_t& methodNode, Method_t& method)
{
  Status_t status;

  const UInt32_t* methodId = RuntimeCast<const UInt32_t* >(methodNode.NodeId()->IdentiferBase());
  if (!methodId)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  IntrusivePtr_t<ArrayUA_t<Argument_t> > arguments = new SafeRefCount_t<ArrayUA_t<Argument_t> >();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(arguments);

  switch (methodId->Value())
  {
  case OpcUaId_ConditionType_AddComment:
  case OpcUaId_AcknowledgeableConditionType_Acknowledge:
  case OpcUaId_AcknowledgeableConditionType_Confirm:
  {
    if (!method.InputArguments().is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
    }

    //InputArguments property
    IntrusivePtr_t<Argument_t> arg1;
    status = method.CreateArgument(BROWSE_NAME_EVENT_ID, OpcUaId_ByteString, -1, arg1);
    if (status.IsBad() || !arg1.is_set())
    {
      UASDK_RETURN_BAD_STATUS(status.Value());
    }

    IntrusivePtr_t<Argument_t> arg2;
    status = method.CreateArgument(BROWSE_NAME_COMMENT, OpcUaId_LocalizedText, -1, arg2);
    if (status.IsBad() || !arg1.is_set())
    {
      UASDK_RETURN_BAD_STATUS(status.Value());
    }

    status = arguments->Initialise(2);
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

    (*arguments)[0] = arg1;
    (*arguments)[1] = arg2;
  }
  break;

  case OpcUaId_AlarmConditionType_ShelvingState_TimedShelve:
  {
    if (!method.InputArguments().is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
    }

    //InputArguments property
    IntrusivePtr_t<Argument_t> arg1;
    status = method.CreateArgument(BROWSE_NAME_SHELVING_TIME, OpcUaId_Duration, -1, arg1);
    if (status.IsBad() || !arg1.is_set())
    {
      UASDK_RETURN_BAD_STATUS(status.Value());
    }

    status = arguments->Initialise(1);
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

    (*arguments)[0] = arg1;

  }
  break;

  //NOTE: Please add method specific methods arguments logic here.
  default:
    return OpcUa_Good;
  }

  IntrusivePtr_t<DataValue_t> dataValue;
  status = ReadValue(*arguments, true, OpcUa_Good, dataValue);
  if (status.IsBad() || !dataValue.is_set())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
  method.InputArguments()->Value(dataValue);

  return status;
}

Status_t AddressSpaceModeler_t::CreateMap(IntrusivePtr_t<HelperBase_t> node, const INode_t& typeNode, IntrusiveList_t<NodeStandardIdMap_t>& list)
{
  UASDK_RETURN_UNEXPECTED_IF_NULL(node);
  IntrusivePtr_t<NodeStandardIdMap_t> map = new SafeRefCount_t<NodeStandardIdMap_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(map);

  map->node = node;
  const UInt32_t* standardId_ = RuntimeCast<const UInt32_t*>(typeNode.NodeId()->IdentiferBase());
  if (!standardId_)
  {
    return OpcUa_BadUnexpectedError;
  }
  map->standardId = standardId_->Value();

  return list.AddToTail(map);
}

uint32_t AddressSpaceModeler_t::GetStandardNodeId(const INode_t& node, IntrusiveList_t<NodeStandardIdMap_t>& list)
{
  if (!node.NodeId().is_set())
  {
    return 0;
  }

  uint32_t count = list.Count();
  for (uint32_t i = 0; i < count; i++)
  {
    IntrusivePtr_t<NodeStandardIdMap_t> node_ = list.GetAtIndex(i);
    UASDK_RETURN_UNEXPECTED_IF_NULL(node_);
    UASDK_RETURN_UNEXPECTED_IF_NULL(node_->node);
    UASDK_RETURN_UNEXPECTED_IF_NULL(node_->node->Node());
    UASDK_RETURN_UNEXPECTED_IF_NULL(node_->node->Node()->NodeId());

    if (*node_->node->Node()->NodeId() == *node.NodeId())
    {
      return node_->standardId;
    }
  }

  return 0;
}

IntrusivePtr_t<IVariableNode_t> AddressSpaceModeler_t::CreateVariable(IntrusivePtr_t<INode_t>& parentNode,
                                                                const IVariableNode_t& typeNode,
                                                                uint32_t dataType,
                                                                uint32_t hasTypeDefinitionId,
                                                                uint32_t referenceType,
                                                                bool assignReaderWriter,
																																IntrusivePtr_t<INodeValueAttributeReaderWriter_t> readerWriter,
                                                                Status_t& result)
{
  IntrusivePtr_t<IVariableNode_t> empty;
  if (!rootNodeId.is_set() || !typeNode.BrowseName().is_set() || !parentNode.is_set() || !parentNode->NodeId().is_set() || !parentNode->BrowseName().is_set()
		|| !addressSpace.is_set() || !readerWriter.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  IntrusivePtr_t<BaseDataVariable_t> variableNode;  
  uint16_t namespaceIndex = rootNodeId->NamespaceIndex().Value();

  String_t browseName;
  result = browseName.CopyFrom(typeNode.BrowseName()->Name());
  if (result.IsBad())
  {
    return empty;
  }

  String_t parentBrowseName_;
  result = AddressSpaceModeler_t::GetParentBrowseName(*rootNodeId, *parentNode, *addressSpace, parentBrowseName_);
  if (result.IsBad())
  {
    return empty;
  }

  String_t id;
  result = Utilities_t::ConcatenateInputStrings(parentBrowseName_, browseName, true, '/', id);
  if (result.IsBad())
  {
    return empty;
  }

  //Check if the node already present in the address space
  NodeIdString_t nodeId;
  nodeId.NamespaceIndex().Value(namespaceIndex);
  result = nodeId.Identifer().CopyFrom(id);
  if (result.IsBad())
  {
    return empty;
  }

  IntrusivePtr_t<INode_t> node = addressSpace->FindNode(nodeId, result);
  if (node.is_set() || result.IsGood())
  {
    result = OpcUa_BadNodeIdExists;
    return empty;
  }

  switch (dataType)
  {
  case OpcUaId_Boolean:
    variableNode = BaseDataVariable_t::CreateWithStringId<Boolean_t>(namespaceIndex, id, addressSpace, browseName, result);
    break;

  case OpcUaId_NodeId:
    variableNode = BaseDataVariable_t::CreateWithStringId<NodeId_t>(namespaceIndex, id, addressSpace, browseName, result);
    break;

  case OpcUaId_String:
    variableNode = BaseDataVariable_t::CreateWithStringId<String_t>(namespaceIndex, id, addressSpace, browseName, result);
    break;

  case OpcUaId_LocalizedText:
    variableNode = BaseDataVariable_t::CreateWithStringId<LocalizedText_t>(namespaceIndex, id, addressSpace, browseName, result);
    break;

  case OpcUaId_UtcTime:
    variableNode = BaseDataVariable_t::CreateWithStringId<UtcTime_t>(namespaceIndex, id, addressSpace, browseName, result);
    break;

  case OpcUaId_DateTime:
    variableNode = BaseDataVariable_t::CreateWithStringId<DateTime_t>(namespaceIndex, id, addressSpace, browseName, result);
    break;

  case OpcUaId_StatusCode:
    variableNode = BaseDataVariable_t::CreateWithStringId<StatusCode_t>(namespaceIndex, id, addressSpace, browseName, result);
    break;

  case OpcUaId_Byte:
    variableNode = BaseDataVariable_t::CreateWithStringId<Byte_t>(namespaceIndex, id, addressSpace, browseName, result);
    break;

  case OpcUaId_SByte:
    variableNode = BaseDataVariable_t::CreateWithStringId<SByte_t>(namespaceIndex, id, addressSpace, browseName, result);
    break;

  case OpcUaId_ByteString:
    variableNode = BaseDataVariable_t::CreateWithStringId<ByteString_t>(namespaceIndex, id, addressSpace, browseName, result);
    break;

  case OpcUaId_XmlElement:
    variableNode = BaseDataVariable_t::CreateWithStringId<XmlElement_t>(namespaceIndex, id, addressSpace, browseName, result);
    break;

  case OpcUaId_Double:
    variableNode = BaseDataVariable_t::CreateWithStringId<Double_t>(namespaceIndex, id, addressSpace, browseName, result);
    break;

  case OpcUaId_Float:
    variableNode = BaseDataVariable_t::CreateWithStringId<Float_t>(namespaceIndex, id, addressSpace, browseName, result);
    break;

  case OpcUaId_Int16:
    variableNode = BaseDataVariable_t::CreateWithStringId<Int16_t>(namespaceIndex, id, addressSpace, browseName, result);
    break;

  case OpcUaId_Int32:
    variableNode = BaseDataVariable_t::CreateWithStringId<Int32_t>(namespaceIndex, id, addressSpace, browseName, result);
    break;

  case OpcUaId_Int64:
    variableNode = BaseDataVariable_t::CreateWithStringId<Int64_t>(namespaceIndex, id, addressSpace, browseName, result);
    break;

  case OpcUaId_UInt16:
    variableNode = BaseDataVariable_t::CreateWithStringId<UInt16_t>(namespaceIndex, id, addressSpace, browseName, result);
    break;

  case OpcUaId_UInt32:
    variableNode = BaseDataVariable_t::CreateWithStringId<UInt32_t>(namespaceIndex, id, addressSpace, browseName, result);
    break;

  case OpcUaId_UInt64:
    variableNode = BaseDataVariable_t::CreateWithStringId<UInt64_t>(namespaceIndex, id, addressSpace, browseName, result);
    break;

  case OpcUaId_Guid:
    variableNode = BaseDataVariable_t::CreateWithStringId<Guid_t>(namespaceIndex, id, addressSpace, browseName, result);
    break;

  case OpcUaId_Duration:
    variableNode = BaseDataVariable_t::CreateWithStringId<Duration_t>(namespaceIndex, id, addressSpace, browseName, result);
    break;

  case OpcUaId_Argument:
    variableNode = BaseDataVariable_t::CreateWithStringId<Argument_t>(namespaceIndex, id, addressSpace, browseName, result);
    break;

  case OpcUaId_QualifiedName:
    variableNode = BaseDataVariable_t::CreateWithStringId<QualifiedName_t>(namespaceIndex, id, addressSpace, browseName, result);
    break;

    //NOTE: For different type please add the cases
  default:
    result = OpcUa_BadNotSupported;
    return empty;
  }

  if (!variableNode.is_set() || !variableNode->GetVariableNode().is_set() || result.IsBad())
  {
    return empty;
  }
  variableNode->Hide(false);
  variableNode->RemoveNodesOnDeletion(true);

  // Nodes should have the Has Type definition as PropertyType.
  // Node Generated via BaseDataVariable will have HasTypeDefinition as BaseDataVariable.
  // Hence remove all the reference for node and create the HasTypeDefinition as PropertyType
  IntrusivePtr_t<IVariableNode_t> variable = variableNode->GetVariableNode();
  if (!variable.is_set() || !variable->BrowseName().is_set())
  {
    result = OpcUa_BadUnexpectedError;
    return empty;
  }

  //BrowseName should have the namespace index as 0 for properties
  result = variable->BrowseName(typeNode.BrowseName());
  if (result.IsBad())
  {
    return empty;
  }

  if(assignReaderWriter)
  {
    variable->ValueAttributeReaderWriter(readerWriter);
  }
  else
  {    
    if (typeNode.Value().is_set() && typeNode.Value()->Value().is_set())
    {
      result = AssignValue(*typeNode.Value()->Value(), *variable);
    }   
  }
  if (result.IsBad())
  {
    return empty;
  }

  result = variable->ReferencesRemoveAllReferences();
  if (result.IsBad())
  {
    return empty;
  }

  result = AddressSpaceUtilities_t::CreateHasTypeDefintion(*addressSpace, variable, hasTypeDefinitionId);
  if (result.IsBad())
  {
    return empty;
  }

  result = AddressSpaceUtilities_t::CreateReference(*addressSpace, parentNode, variable, referenceType);
  if (result.IsBad())
  {
    return empty;
  }

  result = CreateMap(variableNode, typeNode, variablesMap);
  if (result.IsBad())
  {
    return empty;
  }

  return variable;
}

IntrusivePtr_t<Method_t> AddressSpaceModeler_t::CreateMethod(IntrusivePtr_t<INode_t>& conditionNode,
                                                       IntrusivePtr_t<IAddressSpace_t>& addressSpace,
                                                       const IMethodNode_t& typeNode,
                                                       uint32_t referenceType,
                                                       IntrusivePtr_t<INodeMethodHandler_t>& methodHandler,
                                                       Status_t& result)
{
  IntrusivePtr_t<Method_t> empty;
  if (!rootNodeId.is_set() || !conditionNode.is_set() || !conditionNode->BrowseName().is_set() || !addressSpace.is_set() || !typeNode.BrowseName().is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  uint16_t namespaceIndex = rootNodeId->NamespaceIndex().Value();
  String_t browseName_;
  result = browseName_.CopyFrom(typeNode.BrowseName()->Name());
  if (result.IsBad())
  {
    return empty;
  }

  String_t parentBrowseName_;
  result = AddressSpaceModeler_t::GetParentBrowseName(*rootNodeId, *conditionNode, *addressSpace, parentBrowseName_);
  if (result.IsBad())
  {
    return empty;
  }

  String_t id;
  result = Utilities_t::ConcatenateInputStrings(parentBrowseName_, browseName_, true, '/', id);
  if (result.IsBad())
  {
    return empty;
  }
  IntrusivePtr_t<Method_t> method = Method_t::CreateWithStringId(namespaceIndex, id, addressSpace, browseName_, true, result);
  if (!method.is_set() || !method->GetMethodNode().is_set() || result.IsBad())
  {
    return empty;
  }

  //BrowseName should have the namespace index as 0 for properties
  result = method->GetMethodNode()->BrowseName(typeNode.BrowseName());
  if (result.IsBad())
  {
    return empty;
  }

  method->Hide(false);
  method->RemoveNodesOnDeletion(true);
//  methods.AddToTail(method);
  
  IntrusivePtr_t<IMethodNode_t> methodNode = method->GetMethodNode();;
  methodNode->SetMethodHandler(methodHandler);

  result = AddressSpaceUtilities_t::CreateReference(*addressSpace, conditionNode, methodNode, referenceType);
  if (result.IsBad())
  {
    return empty;
  }
 
  result = CreateMap(method, typeNode, methodsMap);
  if (result.IsBad())
  {
    return empty;
  }

  return method;
}

IntrusivePtr_t<BaseObject_t> AddressSpaceModeler_t::CreateObject(IntrusivePtr_t<INode_t>& conditionNode,
  IntrusivePtr_t<IAddressSpace_t>& addressSpace,
  IntrusivePtr_t<const QualifiedName_t> browseName,
 /* const String_t& browseName,*/
  uint32_t referenceType,
  Status_t& result)
{
  IntrusivePtr_t<BaseObject_t> empty;
  if (!rootNodeId.is_set() || !conditionNode.is_set() || !conditionNode->BrowseName().is_set() || !addressSpace.is_set() || !browseName.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  uint16_t namespaceIndex = rootNodeId->NamespaceIndex().Value();
  String_t browseName_;
  result = browseName_.CopyFrom(browseName->Name());
  if (result.IsBad())
  {
    return empty;
  }

  String_t parentBrowseName_;
  result = AddressSpaceModeler_t::GetParentBrowseName(*rootNodeId, *conditionNode, *addressSpace, parentBrowseName_);
  if (result.IsBad())
  {
    return empty;
  }

  String_t id;
  result = Utilities_t::ConcatenateInputStrings(parentBrowseName_, browseName_, true, '/', id);
  if (result.IsBad())
  {
    return empty;
  }
  IntrusivePtr_t<BaseObject_t> object = BaseObject_t::CreateWithStringId(namespaceIndex, id, addressSpace, browseName_, true, result);
  if (!object.is_set() || !object->GetObjectNode().is_set() || result.IsBad())
  {
    return empty;
  }

  //BrowseName should have the namespace index as 0 for properties
  result = object->GetObjectNode()->BrowseName(browseName);
  if (result.IsBad())
  {
    return empty;
  }

  object->Hide(false);
  object->RemoveNodesOnDeletion(true);
  objects.AddToTail(object);

  result = AddressSpaceUtilities_t::CreateReference(*addressSpace, conditionNode, object->GetObjectNode(), referenceType);
  if (result.IsBad())
  {
    return empty;
  }

  return object;
}

/*
 * Public Fucntions
 */
AddressSpaceModeler_t::AddressSpaceModeler_t()
{}

AddressSpaceModeler_t::~AddressSpaceModeler_t()
{
  Clear();
}

Status_t AddressSpaceModeler_t::Initialise(IntrusivePtr_t<IAddressSpace_t>& addressSpace_, IntrusivePtr_t<NodeId_t> rootNodeId_)
{
  if (!addressSpace_.is_set() || !rootNodeId_.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }
  addressSpace = addressSpace_;
  rootNodeId = rootNodeId_;

  return OpcUa_Good;
}

void AddressSpaceModeler_t::Clear()
{
  objects.DeleteAll();
  variablesMap.DeleteAll();
  methodsMap.DeleteAll();
  addressSpace.reset();
  rootNodeId.reset();
}

uint32_t AddressSpaceModeler_t::GetStandardNodeId(const INode_t& node)
{
  uint32_t result = 0;
  switch (node.NodeClass())
  {
    case NodeClass_t::OPCUA_NODECLASS_VARIABLE:
      result = GetStandardNodeId(node, variablesMap);
      break;

    case NodeClass_t::OPCUA_NODECLASS_METHOD:
      result = GetStandardNodeId(node, methodsMap);
      break;

    default:
      break;
  }

  return result;
}

Status_t AddressSpaceModeler_t::GetMethodNodeIdFromStandardNodeId(uint32_t standardNodeId, IntrusivePtr_t<NodeId_t>& methodId)
{
  for (uint32_t i = 0; i < methodsMap.Count(); i++)
  {
    IntrusivePtr_t<NodeStandardIdMap_t> node_ = methodsMap.GetAtIndex(i);
    UASDK_RETURN_UNEXPECTED_IF_NULL(node_);
    UASDK_RETURN_UNEXPECTED_IF_NULL(node_->node);
    UASDK_RETURN_UNEXPECTED_IF_NULL(node_->node->Node());
    UASDK_RETURN_UNEXPECTED_IF_NULL(node_->node->Node()->NodeId());

    if (standardNodeId == node_->standardId)
    {
      node_->node->Node()->NodeId()->CopyToNodeId(methodId);
      return OpcUa_Good;
    }
  }
  return OpcUa_Good;
}

Status_t AddressSpaceModeler_t::InitialiseValue(uint32_t dataType, IntrusivePtr_t<BaseDataType_t>& value)
{
  switch (dataType)
  {
    case OpcUaId_Boolean:
    {
      IntrusivePtr_t<Boolean_t> value_ = new SafeRefCount_t<Boolean_t>();
      value = value_;
    }
    break;

    case OpcUaId_ByteString:
    {
      IntrusivePtr_t<ByteString_t> value_ = new SafeRefCount_t<ByteString_t>();
      value = value_;
    }
    break;

    case OpcUaId_NodeId:
    {
      IntrusivePtr_t<NodeIdNumeric_t> value_ = new SafeRefCount_t<NodeIdNumeric_t>();
      value = value_;
    }
    break;

    case OpcUaId_Guid:
    {
      IntrusivePtr_t<Guid_t> value_ = new SafeRefCount_t<Guid_t>();
      value = value_;
    }
    break;

    case OpcUaId_String:
    {
      IntrusivePtr_t<String_t> value_ = new SafeRefCount_t<String_t>();
      value = value_;
    }
    break;

    case OpcUaId_LocalizedText:
    {
      IntrusivePtr_t<LocalizedText_t> value_ = new SafeRefCount_t<LocalizedText_t>();
      value = value_;
    }
    break;

    case OpcUaId_UtcTime:
    case OpcUaId_DateTime:
    {
      IntrusivePtr_t<UtcTime_t> value_ = new SafeRefCount_t<UtcTime_t>();
      if (value_.is_set())
      {
        value_->Value(UASDK_datetime());
      }
      value = value_;
    }
    break;

    case OpcUaId_StatusCode:
    {
      IntrusivePtr_t<StatusCode_t> value_ = new SafeRefCount_t<StatusCode_t>();
      value = value_;
    }
    break;

    case OpcUaId_UInt16:
    {
      IntrusivePtr_t<UInt16_t> value_ = new SafeRefCount_t<UInt16_t>();
      value = value_;
    }
    break;

    case OpcUaId_UInt32:
    {
      IntrusivePtr_t<UInt32_t> value_ = new SafeRefCount_t<UInt32_t>();
      value = value_;
    }
    break;

    case OpcUaId_UInt64:
    {
      IntrusivePtr_t<UInt64_t> value_ = new SafeRefCount_t<UInt64_t>();
      value = value_;
    }
    break;

    case OpcUaId_Int16:
    {
      IntrusivePtr_t<Int16_t> value_ = new SafeRefCount_t<Int16_t>();
      value = value_;
    }
    break;

    case OpcUaId_Int32:
    {
      IntrusivePtr_t<Int32_t> value_ = new SafeRefCount_t<Int32_t>();
      value = value_;
    }
    break;

    case OpcUaId_Int64:
    {
      IntrusivePtr_t<Int64_t> value_ = new SafeRefCount_t<Int64_t>();
      value = value_;
    }
    break;

    case OpcUaId_Byte:
    {
      IntrusivePtr_t<Byte_t> value_ = new SafeRefCount_t<Byte_t>();
      value = value_;
    }
    break;

    case OpcUaId_SByte:
    {
      IntrusivePtr_t<SByte_t> value_ = new SafeRefCount_t<SByte_t>();
      value = value_;
    }
    break;

    case OpcUaId_Duration:
    {
      IntrusivePtr_t<Duration_t> value_ = new SafeRefCount_t<Duration_t>();
      value = value_;
    }
    break;

    case OpcUaId_XmlElement:
    {
      IntrusivePtr_t<XmlElement_t> value_ = new SafeRefCount_t<XmlElement_t>();
      value = value_;
    }
    break;

    case OpcUaId_Double:
    {
      IntrusivePtr_t<Double_t> value_ = new SafeRefCount_t<Double_t>();
      value = value_;
    }
    break;

    case OpcUaId_Float:
    {
      IntrusivePtr_t<Float_t> value_ = new SafeRefCount_t<Float_t>();
      value = value_;
    }
    break;

    case OpcUaId_QualifiedName:
    {
      IntrusivePtr_t<QualifiedName_t> value_ = new SafeRefCount_t<QualifiedName_t>();
      value = value_;
    }
    break;

    //NOTE: For different type please add the cases
    default:
      return OpcUa_Good;
  }

  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(value);

  return OpcUa_Good;
}

Status_t AddressSpaceModeler_t::ReadValue(const BaseDataType_t& value, bool setSourceTimestamp, uint32_t statusCode, IntrusivePtr_t<DataValue_t>& dataValue)
{
  dataValue.reset(new SafeRefCount_t<DataValue_t>());
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(dataValue);

  if (setSourceTimestamp)
  {
    IntrusivePtr_t<DateTime_t> dateTime(new SafeRefCount_t<DateTime_t>());
    UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(dateTime);

    dateTime->Value(UASDK_datetime());
    dataValue->SourceTimestamp() = dateTime;
  }

  IntrusivePtr_t<StatusCode_t> statusCode_ = new SafeRefCount_t<StatusCode_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(statusCode_);
  statusCode_->Value().Value(statusCode);

  dataValue->StatusCode() = statusCode_;

  return value.CopyTo(dataValue->Value());
}

Status_t AddressSpaceModeler_t::GetParentBrowseName(NodeId_t& rootNodeId_, INode_t& node_, IAddressSpace_t& addressSpace_, String_t& result)
{
  UASDK_RETURN_UNEXPECTED_IF_NULL(node_.NodeId());
  UASDK_RETURN_UNEXPECTED_IF_NULL(node_.BrowseName());

  Status_t status;
  if (rootNodeId_ != *node_.NodeId())
  {
    IntrusivePtr_t<INode_t> conditionNode_ = addressSpace_.FindNode(rootNodeId_, status);
    if (status.IsBad() || !conditionNode_.is_set() || !conditionNode_->BrowseName().is_set())
    {
      return status;
    }

    status = Utilities_t::ConcatenateInputStrings(conditionNode_->BrowseName()->Name(), node_.BrowseName()->Name(), true, '/', result);
  }
  else
  {
    status = result.CopyFrom(node_.BrowseName()->Name());
  }

  return status;
}

Status_t AddressSpaceModeler_t::AddNodesUsingTypeInformation(const NodeId_t&  typeId, const NodeId_t& parentNodeId, bool assignReaderWriter, IntrusivePtr_t<INodeValueAttributeReaderWriter_t>& readerWriter, IntrusivePtr_t<INodeMethodHandler_t>& methodHandler, NodeId_t& baseTypeId)
{
  UASDK_RETURN_UNEXPECTED_IF_NULL(addressSpace);
  UASDK_RETURN_UNEXPECTED_IF_NULL(readerWriter);

  Status_t status;
  IntrusivePtr_t<INode_t>  parentNode = addressSpace->FindNode(parentNodeId, status);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
  UASDK_RETURN_UNEXPECTED_IF_NULL(parentNode);
  
  IntrusivePtr_t<INode_t>  parentNodeType = addressSpace->FindNode(typeId, status);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
  UASDK_RETURN_UNEXPECTED_IF_NULL(parentNodeType);
 
  IntrusivePtr_t<const IIterator_t<IReference_t> > references = parentNodeType->ReferencesGetConstIterator(status);
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
      NodeIdNumeric_t hasTypeDefNodeID(0, OpcUaId_HasSubtype);
      if (reference->TypeId().is_set() && (*reference->TypeId() == hasTypeDefNodeID) && reference->IsInverse())
      {
        IntrusivePtr_t<const NodeId_t> typeId = reference->TargetNode()->NodeId();
        if (*typeId != baseTypeId)//Call recursive super types until baseTypeId
        {
          status = AddNodesUsingTypeInformation(*typeId, parentNodeId, assignReaderWriter, readerWriter, methodHandler, baseTypeId);
        }
      }

      //First handle only the forward references!
      if (reference->IsInverse())
      {
        continue;
      }

      if (reference->TypeId().is_set())
      {
        IntrusivePtr_t<const NodeIdNumeric_t> typeId = RuntimeCast<const NodeIdNumeric_t* > (*reference->TypeId());
        
        UASDK_RETURN_UNEXPECTED_IF_NULL(reference->TargetNode());
        switch (typeId->Identifer().Value())
        {
          case OpcUaId_HasProperty:
            {
              IntrusivePtr_t<const IVariableNode_t> typePropertyNode = RuntimeCast<const IVariableNode_t* > (*reference->TargetNode());
              UASDK_RETURN_UNEXPECTED_IF_NULL(typePropertyNode);
              UASDK_RETURN_UNEXPECTED_IF_NULL(typePropertyNode->BrowseName());
              UASDK_RETURN_UNEXPECTED_IF_NULL(typePropertyNode->DataType());

              const UInt32_t* dataType = RuntimeCast<const UInt32_t* > (typePropertyNode->DataType()->IdentiferBase());
              if (!dataType)
              {
                UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
              }

              IntrusivePtr_t<IVariableNode_t> variable = CreateVariable(parentNode, *typePropertyNode, dataType->Value(), OpcUaId_PropertyType, OpcUaId_HasProperty, assignReaderWriter, readerWriter, status);
              if (!variable.is_set() || status.IsBad())
              {
                if (status.Value() != OpcUa_BadNodeIdExists)
                {
                  UASDK_RETURN_BAD_STATUS(status.Value());
                }
                else
                {
                  continue;
                }
              }
            }
            break;

          case OpcUaId_HasComponent:
            {
              IntrusivePtr_t<INode_t> componentNode = reference->TargetNode();
              IntrusivePtr_t<NodeId_t> result;

              switch (componentNode->NodeClass())
              {
                case NodeClass_t::OPCUA_NODECLASS_OBJECT:
                  {
                    IntrusivePtr_t<const IObjectNode_t> typeObjectNode = RuntimeCast<const IObjectNode_t* > (*reference->TargetNode());
                    UASDK_RETURN_UNEXPECTED_IF_NULL(typeObjectNode);
                    UASDK_RETURN_UNEXPECTED_IF_NULL(typeObjectNode->BrowseName());
                    UASDK_RETURN_UNEXPECTED_IF_NULL(typeObjectNode->NodeId());
                    
                    IntrusivePtr_t<BaseObject_t> object = CreateObject(parentNode, addressSpace, typeObjectNode->BrowseName(), OpcUaId_HasComponent, status);
                    if (!object.is_set() || status.IsBad())
                    {
                      UASDK_RETURN_BAD_STATUS(status.Value());
                    }

                    UASDK_RETURN_UNEXPECTED_IF_NULL(object->Node());
                    UASDK_RETURN_UNEXPECTED_IF_NULL(object->Node()->NodeId());

                    //Now call recursive for properties
                    status = AddNodesUsingTypeInformation(*typeObjectNode->NodeId(), *object->Node()->NodeId(), true, readerWriter, methodHandler, baseTypeId);
                    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
                  }
                  break;

                case NodeClass_t::OPCUA_NODECLASS_VARIABLE:
                  {
                    IntrusivePtr_t<const IVariableNode_t> typeVariableNode = RuntimeCast< const IVariableNode_t* > (*reference->TargetNode());
                    UASDK_RETURN_UNEXPECTED_IF_NULL(typeVariableNode);
                    UASDK_RETURN_UNEXPECTED_IF_NULL(typeVariableNode->BrowseName());
                    UASDK_RETURN_UNEXPECTED_IF_NULL(typeVariableNode->DataType());
                    UASDK_RETURN_UNEXPECTED_IF_NULL(typeVariableNode->NodeId());

                    const  UInt32_t* dataType = RuntimeCast<const UInt32_t* > (typeVariableNode->DataType()->IdentiferBase());
                    if (!dataType)
                    {
                      UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
                    }

                    //Get Has Type definition
                    IntrusivePtr_t<NodeId_t> hasTypeDefinitionId;
                    status = AddressSpaceUtilities_t::GetTypeDefinition(*typeVariableNode, *addressSpace, hasTypeDefinitionId);
                    if (status.IsBad() || !hasTypeDefinitionId.is_set())
                    {
                      break;
                    }
                    const UInt32_t* hasTypeDefinition = RuntimeCast<const UInt32_t* > (hasTypeDefinitionId->IdentiferBase());
                    if (!hasTypeDefinition)
                    {
                      UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
                    }

                    IntrusivePtr_t<IVariableNode_t> variable = CreateVariable(parentNode, *typeVariableNode, dataType->Value(), hasTypeDefinition->Value(), OpcUaId_HasComponent, assignReaderWriter, readerWriter, status);       
                    if (!variable.is_set() || !variable->NodeId().is_set() || status.IsBad())
                    {
                      if (status.Value() != OpcUa_BadNodeIdExists)
                      {
                        UASDK_RETURN_BAD_STATUS(status.Value());
                      }
                      else
                      {
                        continue;
                      }
                    }

                    //Now call recursive for properties
                    status = AddNodesUsingTypeInformation(*typeVariableNode->NodeId(), *variable->NodeId(), true, readerWriter, methodHandler, baseTypeId);
                    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
                  }
                  break;

                case NodeClass_t::OPCUA_NODECLASS_METHOD:
                  {
                    IntrusivePtr_t<const IMethodNode_t> typeMethodNode = RuntimeCast< const IMethodNode_t*>(*reference->TargetNode());
                    UASDK_RETURN_UNEXPECTED_IF_NULL(typeMethodNode);
                    UASDK_RETURN_UNEXPECTED_IF_NULL(typeMethodNode->BrowseName());
                    UASDK_RETURN_UNEXPECTED_IF_NULL(typeMethodNode->NodeId());

                    IntrusivePtr_t<IReference_t> tempReference;
                    status = AddressSpaceUtilities_t::GetReference(*typeMethodNode, OpcUaId_HasModellingRule, true, tempReference);
                    //Do not create method if HasModellingRule is NOT there.
                    if (status.IsBad() || !tempReference.is_set())
                    {
                      continue;
                    }

                    IntrusivePtr_t<Method_t> method = CreateMethod(parentNode, addressSpace, *typeMethodNode, OpcUaId_HasComponent, methodHandler, status);
                    if (!method.is_set() || status.IsBad())
                    {
                      UASDK_RETURN_BAD_STATUS(status.Value());
                    }
                    UASDK_RETURN_UNEXPECTED_IF_NULL(method->GetMethodNode());
                    UASDK_RETURN_UNEXPECTED_IF_NULL(method->GetMethodNode()->NodeId());

                    //Now call recursive for properties
                    status = AddNodesUsingTypeInformation(*typeMethodNode->NodeId(), *method->GetMethodNode()->NodeId(), false, readerWriter, methodHandler, baseTypeId);
                    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

                    status = AddArugmentsToMethod(*typeMethodNode, *method);
                    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
                  }
                  break;

                default:
                  break;
               }
            }
            break;

          default:
            break;
        }
      }
    }
  } while (reference.is_set());

  return OpcUa_Good;
}

} // namespace uasdk

#endif  //((UASDK_INCLUDE_SERVER > 0) && (UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))