/** @file */

/**
 * \defgroup grpAddressSpace Address Space Interfaces
 */

/*****************************************************************************/
/** \file inode_t.h
 *  \brief Address Space Node Interface
 *
 */

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

#ifndef _INODE_T_
#define _INODE_T_

#include "uasdk_includes.h"
#include "opcua_node_class_t.h"
#include "iref_count_t.h"
#include "opcua_timestamps_to_return_t.h"
#include "iiterator_t.h"
#include "opcua_iruntime_type_t.h"

namespace uasdk
{

class QualifiedName_t;
class INodeAttributeAboutToBeReadListener_t;
class INodeAttributeChangedListener_t;
class IUserPermissions_t;
class ILocalizableText_t;
class IReferences_t;
class INodeVisitor_t;
class INodeApplicationContext_t;
class NodeId_t;
class LocalizedText_t;
class DataValue_t;
class WriteMask_t;
class IReference_t;
class IReferenceTypeNode_t;
class INodeReferencesChangedListener_t;
template<typename T> class ArrayUA_t;

/** \addtogroup grpAddressSpace
 *@{*/

/*****************************************************************************/
/** \brief Node Interface
 *
 * A class that represents a node in the address space. Implementations of this
 * interface must be thread safe.
 *
 */

class INode_t : public IRefCount_t, public IRuntimeType_t
{
public:

  UA_DECLARE_RUNTIME_TYPE(INode_t);

  virtual ~INode_t() {}

  /*****************************************************************************/
  /** Get the NodeId attribute of the node
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the NodeId
   * of the node. All nodes have a NodeId however the caller must test the
   * pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const NodeId_t> NodeId(void) const = 0;

  /*****************************************************************************/
  /** Get the NodeClass attribute of the node
   *
   * @return
   *The NodeClass of the node.
   */
  virtual NodeClass_t::Enum_t NodeClass(void) const = 0;

  /*****************************************************************************/
  /** Get the BrowseName attribute of the node
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the BrowseName
   * of the node. All nodes have a BrowseName however the caller must test the
   * pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const QualifiedName_t> BrowseName(void) const = 0;

  /*****************************************************************************/
  /** Set the BrowseName attribute of the node
   *
   * @param[in] value
   * An intrusive reference counting Boost-style smart pointer to the BrowseName
   * of the node. The value provided must satisfy a number of rules.
   * 1) No non-const references to the QualifiedName_t must exist, i.e. it must
   *    be immutable (to ensure thread safety).
   * 2) The QualifiedName_t must have been created dynamically using a
   *    SafeRefCount_t (to ensure thread safety).
   * 3) The value must be set (i.e. pointing to an actual object) as all nodes
   *    require a BrowseName.
   *
   * @return
   * The result of the operation.
   */
  virtual Status_t BrowseName(IntrusivePtr_t<const QualifiedName_t> value) = 0;

  /*****************************************************************************/
  /** Get the DisplayName attribute of the node
   *
   * @param[in] locales
   * The locales of interest in priority order. The
   * ILocalizableText_t DisplayName member variable of the node uses these
   * locales to determine the appropriate LocalizedText_t to return.
   *
   * @param[out] result
   * The result of the operation. This can be ignored unless the returned
   * pointer is not set.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the DisplayName
   * of the node. All nodes have a DisplayName however the caller must test the
   * pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const LocalizedText_t> DisplayName(const ArrayUA_t<String_t>& locales, Status_t& result) const = 0;

  /*****************************************************************************/
  /** Set the DisplayName attribute of the node
   *
   * @param[in] value
   * An intrusive reference counting Boost-style smart pointer to the DisplayName
   * of the node. The value provided must satisfy a number of rules.
   * 1) No non-const references to the ILocalizableText_t must exist, i.e. it must
   *    be immutable (to ensure thread safety).
   * 2) The ILocalizableText_t must have been created dynamically using a
   *    SafeRefCount_t (to ensure thread safety).
   * 3) The value must be set (i.e. pointing to an actual object) as all nodes
   *    require a DisplayName.
   *
   * @return
   * The result of the operation.
   */
  virtual Status_t DisplayName(IntrusivePtr_t<const ILocalizableText_t> value) = 0;

  /*****************************************************************************/
  /** Get the Description attribute of the node
   *
   * @param[in] locales
   * The locales of interest in priority order. The
   * ILocalizableText_t Description member variable of the node uses these
   * locales to determine the appropriate LocalizedText_t to return.
   *
   * @param[out] result
   * The result of the operation. This can be ignored unless the returned
   * pointer is not set.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the Description
   * of the node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const LocalizedText_t> Description(const ArrayUA_t<String_t>& locales, Status_t& result) const = 0;

  /*****************************************************************************/
  /** Set the Description attribute of the node
   *
   * @param[in] value
   * An intrusive reference counting Boost-style smart pointer to the Description
   * of the node. The value provided must satisfy a number of rules.
   * 1) If set, no non-const references to the ILocalizableText_t must exist,
   *    i.e. it must be immutable (to ensure thread safety).
   * 2) If set, the ILocalizableText_t must have been created dynamically using a
   *    SafeRefCount_t (to ensure thread safety).
   * 3) The value pointer can be set or empty. Passing an empty pointer to the
   *    method removes the Description attribute from the node.
   *
   * @return
   * The result of the operation.
   */
  virtual Status_t Description(IntrusivePtr_t<const ILocalizableText_t> value) = 0;

  /*****************************************************************************/
  /** Get the WriteMask attribute of the node
   *
   * @return
   * The WriteMask of the node.
   */
  virtual WriteMask_t WriteMask(void) const = 0;

  /*****************************************************************************/
  /** Set the WriteMask attribute of the node
   *
   * @param[in] value
   * The required WriteMask of the node.
   *
   * @return
   * The result of the operation.
   */
  virtual Status_t WriteMask(WriteMask_t value) = 0;

  /*****************************************************************************/
  /** Get the UserWriteMask attribute of the node
   *
   * @param[in] userPermissions
   * An object used to identify a specific user and authenticate that user's
   * access permissions.
   *
   * @return
   * The UserWriteMask of the node.
   */
  virtual WriteMask_t UserWriteMask(const IUserPermissions_t& userPermissions) const = 0;

  /*****************************************************************************/
  /** Set the UserWriteMask attribute of the node
   *
   * @param[in] value
   * The required UserWriteMask of the node
   *
   * @param[in] userPermissions
   * An object used to identify a specific user and authenticate that user's
   * access permissions.
   *
   * @return
   * The result of the operation.
   */
  virtual Status_t UserWriteMask(WriteMask_t value, IUserPermissions_t& userPermissions) = 0;

  /*****************************************************************************/
  /** Get the Alias NodeId of the node
   *
   *  For servers that use string based node IDs the RegisterNodes service may
   *  create alias NodeIds to speed up node lookup. If an alias exists for a node
   *  it can be obtained via this method.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the Alias
   * of the node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const NodeId_t> Alias(void) const = 0;

  /*****************************************************************************/
  /** Set the Alias NodeId of the node
   *
   *  For servers that use string based node IDs the RegisterNodes service may
   *  create alias NodeIds to speed up node lookup. This method exists to allow the
   *  address space containing the node to register an alias with the node. This method
   *  should only be called by the address space as adding an alias is a two step
   *  process; adding the alias to the node and inserting the key of the alias in
   *  the database of the address space. To add an alias to a node call the relevant
   *  method on the address space object which will internally call this method.
   *
   * @param[in] value
   * An intrusive reference counting Boost-style smart pointer to the Alias NodeId
   * of the node. The value provided must satisfy a number of rules.
   * 1) If set, no non-const references to the NodeId_t must exist,
   *    i.e. it must be immutable (to ensure thread safety).
   * 2) If set, the NodeId_t must have been created dynamically using a
   *    SafeRefCount_t (to ensure thread safety).
   * 3) The value pointer can be set or empty. Passing an empty pointer to the
   *    method removes the Alias from the node (but not from the address space database).
   *
   * @return
   * The result of the operation.
   */
  virtual Status_t Alias(IntrusivePtr_t<const NodeId_t>& value) = 0;

  /*****************************************************************************/
  /** Is the node hidden?
   *
   *  When a node is created it is initially hidden. This prevents address space
   *  users from interacting with the node until it has been fully initialised.
   *  After the node creator has configured the node it should unhide the node to
   *  make it accessible via the address space object.
   *
   * @return
   * The WriteMask of the node.
   */
  virtual bool Hide(void) const = 0;

  /*****************************************************************************/
  /** Hide or unhide the node
   *
   *  When a node is created it is initially hidden. This prevents address space
   *  users from interacting with the node until it has been fully initialised.
   *  After the node creator has configured the node it should unhide the node to
   *  make it accessible via the address space object.
   *
   * @param[in] value
   * "true" hides the node whereas "false" unhides the node.
   *
   * @return
   * The result of the operation.
   */
  virtual Status_t Hide(bool value) = 0;

  /*****************************************************************************/
  /** Is the node accessible over an insecure network connection?
   *
   *  Some nodes should only be accessed by a Client over a secure connection.
   *  A Service interacting with a node should verify that the transport level
   *  connection is sufficiently secure by calling this method to see if the node
   *  requires a secure transport.
   *
   * @return
   * "true" if the node requires a secure transport.
   */
  virtual bool RequiresSecureTransportLayer(void) const = 0;

  /*****************************************************************************/
  /** Configure the node to require a secure network connection
   *
   *  Some nodes should only be accessed by a Client over a secure connection.
   *  A Service interacting with a node should verify that the transport level
   *  connection is sufficiently secure. Call this method to set whether or not
   *  the node requires a secure connection.
   *
   * @param[in] value
   * "true" requires a secure connection whereas "false" does not.
   *
   * @return
   * The result of the operation.
   */
  virtual Status_t RequiresSecureTransportLayer(bool value) = 0;

  /*****************************************************************************/
  /** Get the ApplicationContextHandle of the node
   *
   *  The ApplicationContextHandle allows the application developer to insert
   *  arbitrary, application specific data into the node for easy retrieval on
   *  demand.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * ApplicationContextHandle of the node. The caller must test the pointer
   * before dereferencing it.
   */
  virtual IntrusivePtr_t<INodeApplicationContext_t> ApplicationContextHandle(void) const = 0;

  /*****************************************************************************/
  /** Set the ApplicationContextHandle of the node
   *
   *  The ApplicationContextHandle allows the application developer to insert
   *  arbitrary, application specific data into the node for easy retrieval on
   *  demand.
   *
   * @param[in] value
   * An intrusive reference counting Boost-style smart pointer to the
   * ApplicationContextHandle of the node.
   * The value provided must satisfy a number of rules.
   * 1) If set, no non-const references to the INodeApplicationContext_t must exist,
   *    i.e. it must be immutable (to ensure thread safety).
   * 2) If set, the INodeApplicationContext_t must have been created dynamically using a
   *    SafeRefCount_t (to ensure thread safety).
   * 3) The value pointer can be set or empty. Passing an empty pointer to the
   *    method removes the ApplicationContextHandle from the node.
   *
   * @return
   * The result of the operation.
   */
  virtual Status_t ApplicationContextHandle(IntrusivePtr_t<INodeApplicationContext_t> value) = 0;

  /*****************************************************************************/
  /** Is the node visible to a specific user?
   *
   * @param[in] userPermissions
   * An object used to identify a specific user and authenticate that user's
   * access permissions.
   *
   * @return
   * "true" if the node is visible to the user.
   */
  virtual bool IsVisible(const IUserPermissions_t& userPermissions) const = 0;

  /*****************************************************************************/
  /** This function used to check  Is the nodes are deleted are not
   *
   * @return
   * returns true if node is deleted
   *
   */
  virtual bool IsDeleted(void) const = 0;

  /*****************************************************************************/
  /** Set the attribute about to be read listener of the node
   *
   *  The owner of a node may wish to update a node attribute if the attribute
   *  can occasionally change. If the owner of the node registers this listener
   *  then the node will call the listener when a node attribute is being read
   *  to allow the owner to modify the attribute prior to the read completing.
   *  The listener can specify the node attributes he is interested in and he
   *  will only be called for those specific attributes.
   *  Only a single attribute about to be read listener can be registered at any
   *  given time. Any software component registering a listener with the
   *  node is responsible for removing the listener if required.
   *
   * @param[in] value
   * An intrusive reference counting Boost-style smart pointer to the listener
   * of the node. The value provided must satisfy a number of rules.
   * 1) If set, the INodeAttributeAboutToBeReadListener_t must have been created
   *    dynamically using a SafeRefCount_t (to ensure thread safety).
   * 2) The value pointer can be set or empty. Passing an empty pointer to this
   *    function removes the listener from the node.
   *
   * @return
   * The result of the operation.
   */
  virtual Status_t SetAttributeAboutToBeReadListener(IntrusivePtr_t<INodeAttributeAboutToBeReadListener_t> value) = 0;

  /*****************************************************************************/
  /** Adds an attribute changed listener to the node
   *
   *  Any software component with a non-const reference to a node may register
   *  an attribute changed listener with the node. The listener can specify the
   *  node attributes he is interested in and he will only be called when those
   *  specific attributes change. Any software component registering a listener
   *  with the node is responsible for removing the listener if required.
   *  There can be multiple attribute changed listeners registered at any given
   *  time.
   *
   * Limitations:
   *  If the changed listener is created for value attribute of a node and if
   *  Node value is recieved with the help of ValueAttributeReaderWriter then
   *  Changed listener will not provide the call to application layer.
   *
   * @param[in] value
   * An intrusive reference counting Boost-style smart pointer to the listener.
   * The value provided must satisfy a number of rules.
   * 1) If set, the INodeAttributeChangedListener_t must have been created
   *    dynamically using a SafeRefCount_t (to ensure thread safety).
   * 2) The value pointer can be set or empty. Passing an empty pointer to this
   *    function removes the listener from the node.
   *
   * @return
   * The result of the operation.
   */
  virtual Status_t AttributeChangedListenerAdd(IntrusivePtr_t<INodeAttributeChangedListener_t> value) = 0;

  /*****************************************************************************/
  /** Removes an attribute changed listener from the node
   *
   *  Any software component with a non-const reference to a node may register
   *  an attribute changed listener with the node. The listener can specify the
   *  node attributes he is interested in and he will only be called when those
   *  specific attributes change. Any software component registering a listener
   *  with the node is responsible for removing the listener if required.
   *  There can be multiple attribute changed listeners registered at any given
   *  time.
   *
   * @param[in] value
   * An intrusive reference counting Boost-style smart pointer to the listener.
   * The value provided must satisfy a number of rules.
   * 1) If set, the INodeAttributeChangedListener_t must have been created
   *    dynamically using a SafeRefCount_t (to ensure thread safety).
   * 2) The value pointer must be set.
   */
  virtual Status_t AttributeChangedListenerRemove(IntrusivePtr_t<INodeAttributeChangedListener_t> value) = 0;

  /*****************************************************************************/
  /** Get a const iterator for the node references
   *
   * @param[out] result
   * The result of the operation. Can be ignored unless the returned pointer is
   * empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the iterator.
   * The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const IIterator_t<IReference_t> > ReferencesGetConstIterator(Status_t& result) const = 0;

  /*****************************************************************************/
  /** Get a mutable iterator for the node references
   *
   * @param[out] result
   * The result of the operation. Can be ignored unless the returned pointer is
   * empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the iterator.
   * The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<IIterator_t<IReference_t> > ReferencesGetMutableIterator(Status_t& result) = 0;

  /*****************************************************************************/
  /** Remove all references from the node
   *
   *  The node references use a copy-on-write implementation so removing
   *  references does not invalidate existing iterators.
   *
   * @return
   * The result of the operation.
   */
  virtual Status_t ReferencesRemoveAllReferences(void) = 0;

  /*****************************************************************************/
  /** Remove a reference from the node
   *
   *  The node references use a copy-on-write implementation so removing
   *  references does not invalidate existing iterators.
   *
   * @param[in] value
   * The reference to be removed. Must be the exact same object as is present in
   * the list as a pointer comparison is made to identify it.
   *
   * @return
   * The result of the operation.
   */
  virtual Status_t ReferencesRemoveReference(IReference_t& reference) = 0;

  /*****************************************************************************/
  /** Adds a references changed listener to the node
   *
   *  Any software component with a non-const reference to a node may register
   *  a references changed listener with the node. Any software component
   *  registering a listener with the node is responsible for removing the
   *  listener if required. There can be multiple references changed listeners
   *  registered at any given time.
   *
   * @param[in] value
   * An intrusive reference counting Boost-style smart pointer to the listener.
   * The value provided must satisfy a number of rules.
   * 1) If set, the INodeReferencesChangedListener_t must have been created
   *    dynamically using a SafeRefCount_t (to ensure thread safety).
   * 2) The value pointer can be set or empty. Passing an empty pointer to this
   *    function removes the listener from the node.
   *
   * @return
   * The result of the operation.
   */
  virtual Status_t ReferencesChangedListenerAdd(IntrusivePtr_t<INodeReferencesChangedListener_t> value) = 0;

  /*****************************************************************************/
  /** Removes a references changed listener from the node
   *
   *  Any software component with a non-const reference to a node may register
   *  a references changed listener with the node. Any software component
   *  registering a listener with the node is responsible for removing the
   *  listener if required. There can be multiple references changed listeners
   *  registered at any given time.
   *
   * @param[in] value
   * An intrusive reference counting Boost-style smart pointer to the listener.
   * The value provided must satisfy a number of rules.
   * 1) If set, the INodeReferencesChangedListener_t must have been created
   *    dynamically using a SafeRefCount_t (to ensure thread safety).
   * 2) The value pointer can be set or empty. Passing an empty pointer to this
   *    function removes the listener from the node.
   *
   * @return
   * The result of the operation.
   */
  virtual Status_t ReferencesChangedListenerRemove(IntrusivePtr_t<INodeReferencesChangedListener_t> value) = 0;

  /*****************************************************************************/
  /** Create and add a reference in the node
   *
   *  The node references use a copy-on-write implementation so creating and
   *  adding references does not invalidate existing iterators.
   *  Prefer this overload for optimal address space browse performance as no
   *  address space searches are required to follow references.
   *
   * @param[in] type
   * An intrusive reference counting Boost-style smart pointer to the reference
   * type node. This pointer must be set.
   *
   * @param[in] targetNode
   * An intrusive reference counting Boost-style smart pointer to the target
   * node. This pointer must be set.
   *
   * @param[in] isInverse
   * Create an inverse reference. Setting this to "true" for reference types
   * that are symmetric is invalid.
   *
   * @param[out] result
   * The result of the operation. Can be ignored unless the returned pointer is empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the reference.
   * The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<IReference_t> ReferencesCreateReference(IntrusivePtr_t<IReferenceTypeNode_t>& type,
                                                      IntrusivePtr_t<INode_t>& targetNode,
                                                      bool isInverse,
                                                      Status_t& result) = 0;

  /*****************************************************************************/
  /** Create and add a reference in the node
   *
   *  The node references use a copy-on-write implementation so creating and
   *  adding references does not invalidate existing iterators.
   *  This is not the best overload for optimal address space browse performance
   *  as address space searches are required to follow all references.
   *
   * @param[in] typeId
   * An intrusive reference counting Boost-style smart pointer to the node ID of
   * the reference type node. This pointer must be set.
   *
   * @param[in] targetNodeId
   * An intrusive reference counting Boost-style smart pointer to the node ID
   * of the target node. This pointer must be set.
   *
   * @param[in] isInverse
   * Create an inverse reference. Setting this to "true" for reference types
   * that are symmetric is invalid.
   *
   * @param[out] result
   * The result of the operation. Can be ignored unless the returned pointer is empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the reference.
   * The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<IReference_t> ReferencesCreateReference(IntrusivePtr_t<const NodeId_t> typeId,
                                                      IntrusivePtr_t<const NodeId_t> targetNodeId,
                                                      bool isInverse,
                                                      Status_t& result) = 0;

};

/** @} */

}

#endif // _INODE_T_
