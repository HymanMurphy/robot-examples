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

#ifndef _IADDRESS_SPACE_T_
#define _IADDRESS_SPACE_T_

#include "uasdk_includes.h"
#include "inode_t.h"
#include "iview_node_t.h"
#include "imethod_node_t.h"
#include "iobject_node_t.h"
#include "iobject_type_node_t.h"
#include "ivariable_node_t.h"
#include "ivariable_type_node_t.h"
#include "ireference_t.h"
#include "ireference_type_node_t.h"
#include "idata_type_node_t.h"
#include "iaddress_space_listener_t.h"

namespace uasdk
{

class IUserPermissions_t;
class NodeId_t;
class IFile_t;
class IBuffer_t;
template<typename T> class IntrusiveList_t;

/** \addtogroup grpAddressSpace
 *@{*/

class IAddressSpace_t : public IRefCount_t
{
public:
  virtual ~IAddressSpace_t() {};

  /*****************************************************************************/
  /** Remove the node from the address space
   *
   * @param[in] nodeId
   * The node ID of the node to remove.
   *
   *  @return
   * returns the result of the operation..
   */
  virtual Status_t RemoveNode(const NodeId_t& nodeId) = 0;

  /*****************************************************************************/
  /** Find a node in the address space
   *
   *  This method does not filter for node visibility or transport layer security
   *  but it will not return hidden nodes.
   *
   * @param[in] nodeId
   * The node ID of the node to find.
   *
   * @param[out] result
   * The result of the operation. Can be ignored unless the returned pointer is empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const INode_t> FindNode(const NodeId_t& nodeId, Status_t& result) const = 0;

  /*****************************************************************************/
  /** Find a node in the address space
   *
   *  This method does not filter for node visibility or transport layer security
   *  but it will not return hidden nodes.
   *
   * @param[in] nodeId
   * The node ID of the node to find.
   *
   * @param[out] result
   * The result of the operation. Can be ignored unless the returned pointer is empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<INode_t> FindNode(const NodeId_t& nodeId, Status_t& result) = 0;

  /*****************************************************************************/
  /** Find a node in the address space
   *
   *  This method filters for node visibility and transport layer security
   *  and will not return hidden nodes.
   *
   * @param[in] nodeId
   * The node ID of the node to find.
   *
   * @param[in] userPermissions
   * The user authenticator to authenticate for node visibility
   *
   * @param[in] transportLayerIsSecure
   * The transport layer is secure
   *
   * @param[out] result
   * The result of the operation. Can be ignored unless the returned pointer is empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<INode_t> FindNode(const NodeId_t& nodeId,
                                           const IUserPermissions_t& userPermissions,
                                           bool transportLayerIsSecure,
                                           Status_t& result) = 0;

  /*****************************************************************************/
  /** Find a node in the address space
   *
   *  This method does not filter for node visibility or transport layer security
   *  but it will not return hidden nodes.
   *
   * @param[in] nodeId
   * The node ID of the node to find.
   *
   * @param[out] result
   * The result of the operation. Can be ignored unless the returned pointer is empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const IViewNode_t> FindViewNode(const NodeId_t& nodeId, Status_t& result) const = 0;

  /*****************************************************************************/
  /** Find a node in the address space
   *
   *  This method does not filter for node visibility or transport layer security
   *  but it will not return hidden nodes.
   *
   * @param[in] nodeId
   * The node ID of the node to find.
   *
   * @param[out] result
   * The result of the operation. Can be ignored unless the returned pointer is empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<IViewNode_t> FindViewNode(const NodeId_t& nodeId, Status_t& result) = 0;

  /*****************************************************************************/
  /** Find a node in the address space
   *
   *  This method filters for node visibility and transport layer security
   *  and will not return hidden nodes.
   *
   * @param[in] nodeId
   * The node ID of the node to find.
   *
   * @param[in] userPermissions
   * The user authenticator to authenticate for node visibility
   *
   * @param[in] transportLayerIsSecure
   * The transport layer is secure
   *
   * @param[out] result
   * The result of the operation. Can be ignored unless the returned pointer is empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<IViewNode_t> FindViewNode(const NodeId_t& nodeId,
                                                   const IUserPermissions_t& userPermissions,
                                                  bool transportLayerIsSecure,
                                                  Status_t& result) = 0;


  /*****************************************************************************/
  /** Find a node in the address space
   *
   *  This method does not filter for node visibility or transport layer security
   *  but it will not return hidden nodes.
   *
   * @param[in] nodeId
   * The node ID of the node to find.
   *
   * @param[out] result
   * The result of the operation. Can be ignored unless the returned pointer is empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const IObjectNode_t> FindObjectNode(const NodeId_t& nodeId, Status_t& result) const = 0;

  /*****************************************************************************/
  /** Find a node in the address space
   *
   *  This method does not filter for node visibility or transport layer security
   *  but it will not return hidden nodes.
   *
   * @param[in] nodeId
   * The node ID of the node to find.
   *
   * @param[out] result
   * The result of the operation. Can be ignored unless the returned pointer is empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<IObjectNode_t> FindObjectNode(const NodeId_t& nodeId, Status_t& result) = 0;

  /*****************************************************************************/
  /** Find a node in the address space
   *
   *  This method filters for node visibility and transport layer security
   *  and will not return hidden nodes.
   *
   * @param[in] nodeId
   * The node ID of the node to find.
   *
   * @param[in] userPermissions
   * The user authenticator to authenticate for node visibility
   *
   * @param[in] transportLayerIsSecure
   * The transport layer is secure
   *
   * @param[out] result
   * The result of the operation. Can be ignored unless the returned pointer is empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<IObjectNode_t> FindObjectNode(const NodeId_t& nodeId,
                                                       const IUserPermissions_t& userPermissions,
                                                      bool transportLayerIsSecure,
                                                      Status_t& result) = 0;

  /*****************************************************************************/
  /** Find a node in the address space
   *
   *  This method does not filter for node visibility or transport layer security
   *  but it will not return hidden nodes.
   *
   * @param[in] nodeId
   * The node ID of the node to find.
   *
   * @param[out] result
   * The result of the operation. Can be ignored unless the returned pointer is empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const IObjectTypeNode_t> FindObjectTypeNode(const NodeId_t& nodeId, Status_t& result) const = 0;

  /*****************************************************************************/
  /** Find a node in the address space
   *
   *  This method does not filter for node visibility or transport layer security
   *  but it will not return hidden nodes.
   *
   * @param[in] nodeId
   * The node ID of the node to find.
   *
   * @param[out] result
   * The result of the operation. Can be ignored unless the returned pointer is empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<IObjectTypeNode_t> FindObjectTypeNode(const NodeId_t& nodeId, Status_t& result) = 0;

  /*****************************************************************************/
  /** Find a node in the address space
   *
   *  This method filters for node visibility and transport layer security
   *  and will not return hidden nodes.
   *
   * @param[in] nodeId
   * The node ID of the node to find.
   *
   * @param[in] userPermissions
   * The user authenticator to authenticate for node visibility
   *
   * @param[in] transportLayerIsSecure
   * The transport layer is secure
   *
   * @param[out] result
   * The result of the operation. Can be ignored unless the returned pointer is empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<IObjectTypeNode_t> FindObjectTypeNode(const NodeId_t& nodeId,
                                                               const IUserPermissions_t& userPermissions,
                                                              bool transportLayerIsSecure,
                                                              Status_t& result) = 0;

  /*****************************************************************************/
  /** Find a node in the address space
   *
   *  This method does not filter for node visibility or transport layer security
   *  but it will not return hidden nodes.
   *
   * @param[in] nodeId
   * The node ID of the node to find.
   *
   * @param[out] result
   * The result of the operation. Can be ignored unless the returned pointer is empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const IVariableNode_t> FindVariableNode(const NodeId_t& nodeId, Status_t& result) const = 0;

  /*****************************************************************************/
  /** Find a node in the address space
   *
   *  This method does not filter for node visibility or transport layer security
   *  but it will not return hidden nodes.
   *
   * @param[in] nodeId
   * The node ID of the node to find.
   *
   * @param[out] result
   * The result of the operation. Can be ignored unless the returned pointer is empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<IVariableNode_t> FindVariableNode(const NodeId_t& nodeId, Status_t& result) = 0;

  /*****************************************************************************/
  /** Find a node in the address space
   *
   *  This method filters for node visibility and transport layer security
   *  and will not return hidden nodes.
   *
   * @param[in] nodeId
   * The node ID of the node to find.
   *
   * @param[in] userPermissions
   * The user authenticator to authenticate for node visibility
   *
   * @param[in] transportLayerIsSecure
   * The transport layer is secure
   *
   * @param[out] result
   * The result of the operation. Can be ignored unless the returned pointer is empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<IVariableNode_t> FindVariableNode(const NodeId_t& nodeId,
                                                           const IUserPermissions_t& userPermissions,
                                                          bool transportLayerIsSecure,
                                                          Status_t& result) = 0;

  /*****************************************************************************/
  /** Find a node in the address space
   *
   *  This method does not filter for node visibility or transport layer security
   *  but it will not return hidden nodes.
   *
   * @param[in] nodeId
   * The node ID of the node to find.
   *
   * @param[out] result
   * The result of the operation. Can be ignored unless the returned pointer is empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const IVariableTypeNode_t> FindVariableTypeNode(const NodeId_t& nodeId, Status_t& result) const = 0;

  /*****************************************************************************/
  /** Find a node in the address space
   *
   *  This method does not filter for node visibility or transport layer security
   *  but it will not return hidden nodes.
   *
   * @param[in] nodeId
   * The node ID of the node to find.
   *
   * @param[out] result
   * The result of the operation. Can be ignored unless the returned pointer is empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<IVariableTypeNode_t> FindVariableTypeNode(const NodeId_t& nodeId, Status_t& result) = 0;

  /*****************************************************************************/
  /** Find a node in the address space
   *
   *  This method filters for node visibility and transport layer security
   *  and will not return hidden nodes.
   *
   * @param[in] nodeId
   * The node ID of the node to find.
   *
   * @param[in] userPermissions
   * The user authenticator to authenticate for node visibility
   *
   * @param[in] transportLayerIsSecure
   * The transport layer is secure
   *
   * @param[out] result
   * The result of the operation. Can be ignored unless the returned pointer is empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<IVariableTypeNode_t> FindVariableTypeNode(const NodeId_t& nodeId,
                                                                   const IUserPermissions_t& userPermissions,
                                                                  bool transportLayerIsSecure,
                                                                  Status_t& result) = 0;

  /*****************************************************************************/
  /** Find a node in the address space
   *
   *  This method does not filter for node visibility or transport layer security
   *  but it will not return hidden nodes.
   *
   * @param[in] nodeId
   * The node ID of the node to find.
   *
   * @param[out] result
   * The result of the operation. Can be ignored unless the returned pointer is empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const IMethodNode_t> FindMethodNode(const NodeId_t& nodeId, Status_t& result) const = 0;

  /*****************************************************************************/
  /** Find a node in the address space
   *
   *  This method does not filter for node visibility or transport layer security
   *  but it will not return hidden nodes.
   *
   * @param[in] nodeId
   * The node ID of the node to find.
   *
   * @param[out] result
   * The result of the operation. Can be ignored unless the returned pointer is empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<IMethodNode_t> FindMethodNode(const NodeId_t& nodeId, Status_t& result) = 0;

  /*****************************************************************************/
  /** Find a node in the address space
   *
   *  This method filters for node visibility and transport layer security
   *  and will not return hidden nodes.
   *
   * @param[in] nodeId
   * The node ID of the node to find.
   *
   * @param[in] userPermissions
   * The user authenticator to authenticate for node visibility
   *
   * @param[in] transportLayerIsSecure
   * The transport layer is secure
   *
   * @param[out] result
   * The result of the operation. Can be ignored unless the returned pointer is empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<IMethodNode_t> FindMethodNode(const NodeId_t& nodeId,
                                                       const IUserPermissions_t& userPermissions,
                                                      bool transportLayerIsSecure,
                                                      Status_t& result) = 0;

  /*****************************************************************************/
  /** Find a node in the address space
   *
   *  This method does not filter for node visibility or transport layer security
   *  but it will not return hidden nodes.
   *
   * @param[in] nodeId
   * The node ID of the node to find.
   *
   * @param[out] result
   * The result of the operation. Can be ignored unless the returned pointer is empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const IDataTypeNode_t> FindDataTypeNode(const NodeId_t& nodeId, Status_t& result) const = 0;

  /*****************************************************************************/
  /** Find a node in the address space
   *
   *  This method does not filter for node visibility or transport layer security
   *  but it will not return hidden nodes.
   *
   * @param[in] nodeId
   * The node ID of the node to find.
   *
   * @param[out] result
   * The result of the operation. Can be ignored unless the returned pointer is empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<IDataTypeNode_t> FindDataTypeNode(const NodeId_t& nodeId, Status_t& result) = 0;

  /*****************************************************************************/
  /** Find a node in the address space
   *
   *  This method filters for node visibility and transport layer security
   *  and will not return hidden nodes.
   *
   * @param[in] nodeId
   * The node ID of the node to find.
   *
   * @param[in] userPermissions
   * The user authenticator to authenticate for node visibility
   *
   * @param[in] transportLayerIsSecure
   * The transport layer is secure
   *
   * @param[out] result
   * The result of the operation. Can be ignored unless the returned pointer is empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<IDataTypeNode_t> FindDataTypeNode(const NodeId_t& nodeId,
                                                           const IUserPermissions_t& userPermissions,
                                                          bool transportLayerIsSecure,
                                                          Status_t& result) = 0;

  /*****************************************************************************/
  /** Find a node in the address space
   *
   *  This method does not filter for node visibility or transport layer security
   *  but it will not return hidden nodes.
   *
   * @param[in] nodeId
   * The node ID of the node to find.
   *
   * @param[out] result
   * The result of the operation. Can be ignored unless the returned pointer is empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const IReferenceTypeNode_t> FindReferenceTypeNode(const NodeId_t& nodeId, Status_t& result) const = 0;

  /*****************************************************************************/
  /** Find a node in the address space
   *
   *  This method does not filter for node visibility or transport layer security
   *  but it will not return hidden nodes.
   *
   * @param[in] nodeId
   * The node ID of the node to find.
   *
   * @param[out] result
   * The result of the operation. Can be ignored unless the returned pointer is empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<IReferenceTypeNode_t> FindReferenceTypeNode(const NodeId_t& nodeId, Status_t& result) = 0;

  /*****************************************************************************/
  /** Find a node in the address space
   *
   *  This method filters for node visibility and transport layer security
   *  and will not return hidden nodes.
   *
   * @param[in] nodeId
   * The node ID of the node to find.
   *
   * @param[in] userPermissions
   * The user authenticator to authenticate for node visibility
   *
   * @param[in] transportLayerIsSecure
   * The transport layer is secure
   *
   * @param[out] result
   * The result of the operation. Can be ignored unless the returned pointer is empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<IReferenceTypeNode_t> FindReferenceTypeNode(const NodeId_t& nodeId,
                                                                     const IUserPermissions_t& userPermissions,
                                                            bool transportLayerIsSecure,
                                                            Status_t& result) = 0;

  /*****************************************************************************/
  /** Create a view node in the address space
   *
   *  This method creates a node in the address space with the provided node ID.
   *  It does not test for duplicate node IDs and if this is a concern the caller
   *  should first search the database to ensure that the node ID is unique.
   *  The node is initially hidden and must be marked as unhidden before address
   *  space searches will return the node.
   *
   * @param[in] nodeId
   * The node ID of the node to create.
   *
   * @param[out] result
   * The result of the operation. Can be ignored unless the returned pointer is empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<IViewNode_t> CreateView(IntrusivePtr_t<const NodeId_t> nodeId,
                                                Status_t& result) = 0;

  /*****************************************************************************/
  /** Create an object node in the address space
   *
   *  This method creates a node in the address space with the provided node ID.
   *  It does not test for duplicate node IDs and if this is a concern the caller
   *  should first search the database to ensure that the node ID is unique.
   *  The node is initially hidden and must be marked as unhidden before address
   *  space searches will return the node.
   *
   * @param[in] nodeId
   * The node ID of the node to create.
   *
   * @param[out] result
   * The result of the operation. Can be ignored unless the returned pointer is empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<IObjectNode_t> CreateObject(IntrusivePtr_t<const NodeId_t> nodeId,
                                                    Status_t& result) = 0;

  /*****************************************************************************/
  /** Create an object type node in the address space
   *
   *  This method creates a node in the address space with the provided node ID.
   *  It does not test for duplicate node IDs and if this is a concern the caller
   *  should first search the database to ensure that the node ID is unique.
   *  The node is initially hidden and must be marked as unhidden before address
   *  space searches will return the node.
   *
   * @param[in] nodeId
   * The node ID of the node to create.
   *
   * @param[out] result
   * The result of the operation. Can be ignored unless the returned pointer is empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<IObjectTypeNode_t> CreateObjectType(IntrusivePtr_t<const NodeId_t> nodeId,
                                                            Status_t& result) = 0;

  /*****************************************************************************/
  /** Create a variable node in the address space
   *
   *  This method creates a node in the address space with the provided node ID.
   *  It does not test for duplicate node IDs and if this is a concern the caller
   *  should first search the database to ensure that the node ID is unique.
   *  The node is initially hidden and must be marked as unhidden before address
   *  space searches will return the node.
   *
   * @param[in] nodeId
   * The node ID of the node to create.
   *
   * @param[out] result
   * The result of the operation. Can be ignored unless the returned pointer is empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<IVariableNode_t> CreateVariable(IntrusivePtr_t<const NodeId_t> nodeId,
                                                        Status_t& result) = 0;

  /*****************************************************************************/
  /** Create a variable type node in the address space
   *
   *  This method creates a node in the address space with the provided node ID.
   *  It does not test for duplicate node IDs and if this is a concern the caller
   *  should first search the database to ensure that the node ID is unique.
   *  The node is initially hidden and must be marked as unhidden before address
   *  space searches will return the node.
   *
   * @param[in] nodeId
   * The node ID of the node to create.
   *
   * @param[out] result
   * The result of the operation. Can be ignored unless the returned pointer is empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<IVariableTypeNode_t> CreateVariableType(IntrusivePtr_t<const NodeId_t> nodeId,
                                                                Status_t& result) = 0;

  /*****************************************************************************/
  /** Create a method node in the address space
   *
   *  This method creates a node in the address space with the provided node ID.
   *  It does not test for duplicate node IDs and if this is a concern the caller
   *  should first search the database to ensure that the node ID is unique.
   *  The node is initially hidden and must be marked as unhidden before address
   *  space searches will return the node.
   *
   * @param[in] nodeId
   * The node ID of the node to create.
   *
   * @param[out] result
   * The result of the operation. Can be ignored unless the returned pointer is empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<IMethodNode_t> CreateMethod(IntrusivePtr_t<const NodeId_t> nodeId,
                                                    Status_t& result) = 0;

  /*****************************************************************************/
  /** Create a data type node in the address space
   *
   *  This method creates a node in the address space with the provided node ID.
   *  It does not test for duplicate node IDs and if this is a concern the caller
   *  should first search the database to ensure that the node ID is unique.
   *  The node is initially hidden and must be marked as unhidden before address
   *  space searches will return the node.
   *
   * @param[in] nodeId
   * The node ID of the node to create.
   *
   * @param[out] result
   * The result of the operation. Can be ignored unless the returned pointer is empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<IDataTypeNode_t> CreateDataType(IntrusivePtr_t<const NodeId_t> nodeId,
                                                        Status_t& result) = 0;

  /*****************************************************************************/
  /** Create a reference type node in the address space
   *
   *  This method creates a node in the address space with the provided node ID.
   *  It does not test for duplicate node IDs and if this is a concern the caller
   *  should first search the database to ensure that the node ID is unique.
   *  The node is initially hidden and must be marked as unhidden before address
   *  space searches will return the node.
   *
   * @param[in] nodeId
   * The node ID of the node to create.
   *
   * @param[out] result
   * The result of the operation. Can be ignored unless the returned pointer is empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<IReferenceTypeNode_t> CreateReferenceType(IntrusivePtr_t<const NodeId_t> nodeId,
                                                                  Status_t& result) = 0;

  /*****************************************************************************/
  /** Address Space Listener Add
  *
  *  This method adds the address space listeners.
  *  when the node is created or node is deleted, respective listners will be called
  *
  * @param[in] addressSpaceListener_
  * An intrusive reference counting Boost-style smart pointer to the address space
  * listner object. The value provided must satisfy a number of rules.
  * 1) No non-const references to the NodeId_t must exist,
  *    i.e. it must be immutable (to ensure thread safety).
  * 2) The NodeId_t must have been created dynamically using a
  *    SafeRefCount_t (to ensure thread safety).
  * 3) The value pointer must be set.
  *
  * @return
  * returns the status of the operation.
  */
  virtual Status_t AddressSpaceListenerAdd(IntrusivePtr_t<IAddressSpaceListener_t> addressSpaceListener_) = 0;

  /*****************************************************************************/
  /** Address Space Listener Remove
  *
  *  This method remove the address space listeners.
  *  When the node is created or node is deleted, respective listners will be called
  *
  * @param[in] addressSpaceListener_
  * An intrusive reference counting Boost-style smart pointer to the address space
  * listner object. The value provided must satisfy a number of rules.
  * 1) No non-const references to the NodeId_t must exist,
  *    i.e. it must be immutable (to ensure thread safety).
  * 2) The NodeId_t must have been created dynamically using a
  *    SafeRefCount_t (to ensure thread safety).
  * 3) The value pointer must be set.
  *
  * @return
  * returns the status of the operation.
  */
  virtual Status_t AddressSpaceListenerRemove(IntrusivePtr_t<IAddressSpaceListener_t> addressSpaceListener_) = 0;

  /*****************************************************************************/
  /** Add a node alias
   *
   *  For servers that use string based node IDs the RegisterNodes service may
   *  create alias NodeIds to speed up node lookup. This method adds the
   *  alias to the provided node.
   *
   * @param[in] value
   * An intrusive reference counting Boost-style smart pointer to the Alias NodeId
   * of the node. The value provided must satisfy a number of rules.
   * 1) No non-const references to the NodeId_t must exist,
   *    i.e. it must be immutable (to ensure thread safety).
   * 2) The NodeId_t must have been created dynamically using a
   *    SafeRefCount_t (to ensure thread safety).
   * 3) The value pointer must be set.
   *
   * @return
   * returns the status of the operation.
   */
  virtual Status_t AddNodeAlias(const NodeId_t& nodeId, IntrusivePtr_t<const NodeId_t> alias) = 0;

  /*****************************************************************************/
  /** Remove a node alias
   *
   *  For servers that use string based node IDs the RegisterNodes service may
   *  create alias NodeIds to speed up node lookup. This method removes the
   *  alias from the provided node.
   *
   * @param[in] nodeId
   * The node ID of the alias to remove.
   *
   * @return
   * returns the status of the operation.
   */
  virtual Status_t RemoveNodeAlias(const NodeId_t& alias) = 0;

  virtual Status_t ExportNodesToByteArray(
    const IntrusiveList_t<const INode_t>& nodes,
    bool serialiseDisplayNames, 
    IBuffer_t& dataBuffer) const = 0;

  virtual Status_t ImportNodesFromByteArray(IntrusivePtr_t<const IBuffer_t> data) = 0;
};

/** @} */

}

#endif // _IADDRESS_SPACE_T_
