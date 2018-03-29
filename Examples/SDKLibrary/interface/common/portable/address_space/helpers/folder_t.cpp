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

#include "folder_t.h"

#if (UASDK_USE_HELPERS > 0)

#include "address_space_utilities_t.h"
#include "opcua_node_id_numeric_t.h"

namespace uasdk
{
/*
*
*/
IntrusivePtr_t<Folder_t> Folder_t::CreateFolderObject(IntrusivePtr_t<IObjectNode_t>& node_, IntrusivePtr_t<IAddressSpace_t>& addressSpace_, Status_t& result)
{
  IntrusivePtr_t<Folder_t> retVal;
  if (!node_.is_set() || !addressSpace_.is_set() || result.IsBad())
  {
    result = OpcUa_BadInvalidArgument;
    return retVal;
  }

  retVal.reset(new SafeRefCount_t<Folder_t>());
  if (!retVal.is_set())
  {
    result = OpcUa_BadOutOfMemory;
    return retVal;
  }

  retVal->Initialize(node_, addressSpace_);
  result = OpcUa_Good;

  return retVal;
}

IntrusivePtr_t<Folder_t> Folder_t::CreateFolderObject(IntrusivePtr_t<const NodeId_t>& nodeId,
                                                                  const String_t& browseName,
                                                                  IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                  Status_t& result)
{
  IntrusivePtr_t<Folder_t> empty;

  IntrusivePtr_t<IObjectNode_t> folderNode = HelperBase_t::Create(nodeId, addressSpace_, browseName, OpcUaId_FolderType, result);
  if (result.IsBad() || !folderNode.is_set())
  {
    return empty;
  }

  return Folder_t::CreateFolderObject(folderNode, addressSpace_, result);
}

/*
* Protected functions
*/
Folder_t::Folder_t()
{}

/*
* public functions
*/

Folder_t::~Folder_t()
{}

IntrusivePtr_t<IObjectNode_t> Folder_t::GetObjectNode(void)
{
  IntrusivePtr_t<IObjectNode_t> node_;
  if (!node.is_set())
  {
    return node_;
  }

  node_ = AddressSpaceUtilities_t::NodeDownCast<IObjectNode_t>(*node);
  if (!node_.is_set())
  {
    return node_;
  }

  return node_;
}

IntrusivePtr_t<const IObjectNode_t> Folder_t::GetObjectNode(void) const
{
  IntrusivePtr_t<IObjectNode_t> node_;
  if (!node.is_set())
  {
    return node_;
  }

  node_ = AddressSpaceUtilities_t::NodeDownCast<IObjectNode_t>(*node);
  if (!node_.is_set())
  {
    return node_;
  }

  return node_;
}

IntrusivePtr_t<Folder_t> Folder_t::Get(const NodeId_t& nodeId,
                                       IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                       Status_t& result)
{
  IntrusivePtr_t<Folder_t> empty;
  if (!addressSpace_.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  IntrusivePtr_t<IObjectNode_t> fileObjectNode = addressSpace_->FindObjectNode(nodeId, result);
  if (result.IsBad() || !fileObjectNode.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  return Get(fileObjectNode, addressSpace_, result);
}

IntrusivePtr_t<Folder_t> Folder_t::Get(IntrusivePtr_t<IObjectNode_t>& node,
                                       IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                       Status_t& result)
{
  IntrusivePtr_t<Folder_t> empty;
  if (!node.is_set() || !addressSpace_.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  result = HelperBase_t::CheckHasTypeDefinition(*node, *addressSpace_, OpcUaId_FolderType);
  if (result.IsBad())
  {
    return empty;
  }

  return Folder_t::CreateFolderObject(node, addressSpace_, result);
}

IntrusivePtr_t<Folder_t> Folder_t::CreateWithNumericId(uint16_t namespaceIndex,
                                                       uint32_t nodeIdentifier,
                                                       IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                       const String_t& browseName,
                                                       Status_t& result)
{
  IntrusivePtr_t<Folder_t> empty;

  IntrusivePtr_t<const NodeId_t> nodeId;
  result = AddressSpaceUtilities_t::GenerateNumericNodeId(namespaceIndex, nodeIdentifier, nodeId);
  if (result.IsBad())
  {
    return empty;
  }
  
  return CreateFolderObject(nodeId, browseName, addressSpace_, result);
}

IntrusivePtr_t<Folder_t> Folder_t::CreateWithStringId(uint16_t namespaceIndex,
                                                      const String_t& nodeIdentifier,
                                                      IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                      const String_t& browseName,
                                                      Status_t& result)
{
  IntrusivePtr_t<Folder_t> empty;

  IntrusivePtr_t<const NodeId_t> nodeId;
  result = AddressSpaceUtilities_t::GenerateStringNodeId(namespaceIndex, nodeIdentifier, nodeId);
  if (result.IsBad())
  {
    return empty;
  }

  return CreateFolderObject(nodeId, browseName, addressSpace_, result);
}

IntrusivePtr_t<Folder_t> Folder_t::CreateWithGuidId(uint16_t namespaceIndex,
                                                    const Guid_t& nodeIdentifier,
                                                    IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                    const String_t& browseName,
                                                    Status_t& result)
{
  IntrusivePtr_t<Folder_t> empty;

  IntrusivePtr_t<const NodeId_t> nodeId;
  result = AddressSpaceUtilities_t::GenerateGuidNodeId(namespaceIndex, nodeIdentifier, nodeId);
  if (result.IsBad())
  {
    return empty;
  }

  return CreateFolderObject(nodeId, browseName, addressSpace_, result);
}

IntrusivePtr_t<Folder_t> Folder_t::CreateWithOpaqueId(uint16_t namespaceIndex,
                                                      const ByteString_t& nodeIdentifier,
                                                      IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                      const String_t& browseName,
                                                      Status_t& result)
{
  IntrusivePtr_t<Folder_t> empty;

  IntrusivePtr_t<const NodeId_t> nodeId;
  result = AddressSpaceUtilities_t::GenerateOpaqueNodeId(namespaceIndex, nodeIdentifier, nodeId);
  if (result.IsBad())
  {
    return empty;
  }

  return CreateFolderObject(nodeId, browseName, addressSpace_, result);
}

}

#endif  //UASDK_USE_FILE_TRANSFER_HELPERS