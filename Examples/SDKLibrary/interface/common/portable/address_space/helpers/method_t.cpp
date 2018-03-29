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

#include "method_t.h"

#if ((UASDK_USE_HELPERS > 0) && (UASDK_INCLUDE_METHOD_SERVICE_SET > 0))

#include "address_space_utilities_t.h"
#include "opcua_node_id_numeric_t.h"
#include "browse_names_t.h"

namespace uasdk
{
/*
*
*/
IntrusivePtr_t<Method_t> Method_t::CreateMethod(IntrusivePtr_t<IMethodNode_t>& node_, IntrusivePtr_t<IAddressSpace_t>& addressSpace_, Status_t& result)
{
  IntrusivePtr_t<Method_t> retVal;
  if (!node_.is_set() || !addressSpace_.is_set() || result.IsBad())
  {
    result = OpcUa_BadInvalidArgument;
    return retVal;
  }

  retVal.reset(new SafeRefCount_t<Method_t>());
  if (!retVal.is_set())
  {
    result = OpcUa_BadOutOfMemory;
    return retVal;
  }

  retVal->Initialize(node_, addressSpace_);
  result = OpcUa_Good;

  return retVal;
}

IntrusivePtr_t<Method_t> Method_t::CreateMethod(IntrusivePtr_t<const NodeId_t>& nodeId,
                                                const String_t& browseName,
                                                IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                bool executable,
                                                Status_t& result)
{
  IntrusivePtr_t<Method_t> empty;

  IntrusivePtr_t<IMethodNode_t> methodNode = HelperBase_t::CreateMethod(nodeId, addressSpace_, browseName, executable, result);
  if (result.IsBad() || !methodNode.is_set())
  {
    return empty;
  }

  return Method_t::CreateMethod(methodNode, addressSpace_, result);
}

void Method_t::DeleteProperties(Method_t& method)
{
  UASDK_RETURN_IF_NULL(method.addressSpace);

  IntrusivePtr_t<IVariableNode_t> inputArguments = method.InputArguments();
  IntrusivePtr_t<IVariableNode_t> outputArguments = method.OutputArguments();

  if (inputArguments.is_set() && inputArguments->NodeId().is_set())
  {
    method.addressSpace->RemoveNode(*(inputArguments->NodeId()));
  }
  if (outputArguments.is_set() && outputArguments->NodeId().is_set())
  {
    method.addressSpace->RemoveNode(*(outputArguments->NodeId()));
  }
}

/*
* Protected functions
*/
Method_t::Method_t()
{}

/*
* public functions
*/

Method_t::~Method_t()
{
  if (deleteNode)
  {
    DeleteProperties(*this);
  }
}

IntrusivePtr_t<IVariableNode_t> Method_t::InputArguments(void)
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return HelperBase_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_INPUT_ARGUMENTS);
}

IntrusivePtr_t<const IVariableNode_t> Method_t::InputArguments(void) const
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return HelperBase_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_INPUT_ARGUMENTS);
}

IntrusivePtr_t<IVariableNode_t> Method_t::OutputArguments(void)
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return HelperBase_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_OUTPUT_ARGUMENTS);
}

IntrusivePtr_t<const IVariableNode_t> Method_t::OutputArguments(void) const
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return HelperBase_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_OUTPUT_ARGUMENTS);
}


IntrusivePtr_t<IMethodNode_t> Method_t::GetMethodNode(void)
{
  IntrusivePtr_t<IMethodNode_t> node_;
  if (!node.is_set())
  {
    return node_;
  }

  node_ = AddressSpaceUtilities_t::NodeDownCast<IMethodNode_t>(*node);
  if (!node_.is_set())
  {
    return node_;
  }

  return node_;
}

IntrusivePtr_t<const IMethodNode_t> Method_t::GetMethodNode(void) const
{
  IntrusivePtr_t<IMethodNode_t> node_;
  if (!node.is_set())
  {
    return node_;
  }

  node_ = AddressSpaceUtilities_t::NodeDownCast<IMethodNode_t>(*node);
  if (!node_.is_set())
  {
    return node_;
  }

  return node_;
}

Status_t Method_t::AddArrayDimensions(ArrayUA_t<UInt32_t>& arrayDimensions, IntrusivePtr_t<Argument_t>& result)
{
  if (!result.is_set())
  {
    return OpcUa_BadInvalidArgument;
  }

  return result->ArrayDimensions().CopyFrom(arrayDimensions);
}

Status_t Method_t::AddDescription(LocalizedText_t& description, IntrusivePtr_t<Argument_t>& result)
{
  if (!result.is_set())
  {
    return OpcUa_BadInvalidArgument;
  }

  return result->Description().CopyFrom(description);
}

Status_t Method_t::CreateArgument(const char* name_, uint32_t dataType_, int32_t valueRank_, IntrusivePtr_t<Argument_t>& result)
{
  if (!name_)
  {
    return OpcUa_BadInvalidArgument;
  }

  IntrusivePtr_t<Argument_t> argument = new SafeRefCount_t<Argument_t>();
  if (!argument.is_set())
  {
    return OpcUa_BadOutOfMemory;
  }

  String_t name;
  Status_t status = argument->Name().CopyFrom(name_);
  if (status.IsBad())
  {
    return status;
  }

  NodeIdNumeric_t dataType(0, dataType_);
  status = dataType.CopyToNodeId(argument->DataType());
  if (status.IsBad())
  {
    return status;
  }

  argument->ValueRank().Value(valueRank_);

  result = argument;
  return OpcUa_Good;
}

Status_t Method_t::CreateInputArguments(ArrayUA_t<Argument_t>& value)
{
  return CreateInputArguments(0, value);
}

Status_t Method_t::CreateInputArguments(uint32_t identifier, ArrayUA_t<Argument_t>& value)
{
  IntrusivePtr_t<ArrayUA_t<Argument_t> > val(new SafeRefCount_t<ArrayUA_t<Argument_t> >());
  if (!val.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  IntrusivePtr_t<IVariableNode_t> propertyNode = InputArguments();
  return HelperBase_t::CreatePropertyAndAssignValue(*this, identifier, BROWSE_NAME_INPUT_ARGUMENTS, OpcUaId_Argument, val, value, propertyNode);
}

Status_t Method_t::CreateOutputArguments(ArrayUA_t<Argument_t>& value)
{
  return CreateOutputArguments(0, value);
}

Status_t Method_t::CreateOutputArguments(uint32_t identifier, ArrayUA_t<Argument_t>& value)
{
  IntrusivePtr_t<ArrayUA_t<Argument_t> > val(new SafeRefCount_t<ArrayUA_t<Argument_t> >());
  if (!val.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  IntrusivePtr_t<IVariableNode_t> propertyNode = OutputArguments();
  return HelperBase_t::CreatePropertyAndAssignValue(*this, identifier, BROWSE_NAME_OUTPUT_ARGUMENTS, OpcUaId_Argument, val, value, propertyNode);
}

/*
* Wrapper creation
*/
IntrusivePtr_t<Method_t> Method_t::Get(const NodeId_t& nodeId,
  IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
  Status_t& result)
{
  IntrusivePtr_t<Method_t> empty;
  if (!addressSpace_.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  IntrusivePtr_t<IMethodNode_t> method = addressSpace_->FindMethodNode(nodeId, result);
  if (result.IsBad() || !method.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  return Method_t::Get(method, addressSpace_, result);
}

IntrusivePtr_t<Method_t> Method_t::Get(IntrusivePtr_t<IMethodNode_t>& node,
  IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
  Status_t& result)
{
  IntrusivePtr_t<Method_t> empty;
  if (!node.is_set() || !addressSpace_.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }  

  return Method_t::CreateMethod(node, addressSpace_, result);
}

IntrusivePtr_t<Method_t> Method_t::CreateWithNumericId(uint16_t namespaceIndex,
                                                       uint32_t nodeIdentifier,
                                                       IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                       const String_t& browseName,
                                                       bool executable,
                                                       Status_t& result)
{
  IntrusivePtr_t<Method_t> empty;

  IntrusivePtr_t<const NodeId_t> nodeId;
  result = AddressSpaceUtilities_t::GenerateNumericNodeId(namespaceIndex, nodeIdentifier, nodeId);
  if (result.IsBad())
  {
    return empty;
  }
  
  return CreateMethod(nodeId, browseName, addressSpace_, executable, result);
}

IntrusivePtr_t<Method_t> Method_t::CreateWithStringId(uint16_t namespaceIndex,
                                                      const String_t& nodeIdentifier,
                                                      IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                      const String_t& browseName,
                                                      bool executable,
                                                      Status_t& result)
{
  IntrusivePtr_t<Method_t> empty;

  IntrusivePtr_t<const NodeId_t> nodeId;
  result = AddressSpaceUtilities_t::GenerateStringNodeId(namespaceIndex, nodeIdentifier, nodeId);
  if (result.IsBad())
  {
    return empty;
  }

  return CreateMethod(nodeId, browseName, addressSpace_, executable, result);
}

IntrusivePtr_t<Method_t> Method_t::CreateWithGuidId(uint16_t namespaceIndex,
                                                            const Guid_t& nodeIdentifier,
                                                            IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                            const String_t& browseName,
                                                            bool executable,
                                                            Status_t& result)
{
  IntrusivePtr_t<Method_t> empty;

  IntrusivePtr_t<const NodeId_t> nodeId;
  result = AddressSpaceUtilities_t::GenerateGuidNodeId(namespaceIndex, nodeIdentifier, nodeId);
  if (result.IsBad())
  {
    return empty;
  }

  return CreateMethod(nodeId, browseName, addressSpace_, executable, result);
}

IntrusivePtr_t<Method_t> Method_t::CreateWithOpaqueId(uint16_t namespaceIndex,
                                                              const ByteString_t& nodeIdentifier,
                                                              IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                              const String_t& browseName,
                                                              bool executable,
                                                              Status_t& result)
{
  IntrusivePtr_t<Method_t> empty;

  IntrusivePtr_t<const NodeId_t> nodeId;
  result = AddressSpaceUtilities_t::GenerateOpaqueNodeId(namespaceIndex, nodeIdentifier, nodeId);
  if (result.IsBad())
  {
    return empty;
  }

  return CreateMethod(nodeId, browseName, addressSpace_, executable, result);
}

}

#endif  //((UASDK_USE_HELPERS > 0) && (UASDK_INCLUDE_METHOD_SERVICE_SET > 0))
