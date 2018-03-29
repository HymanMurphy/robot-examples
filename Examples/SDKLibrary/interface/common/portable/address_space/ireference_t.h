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

#ifndef _IREFERENCE_T_
#define _IREFERENCE_T_

#include "uasdk_includes.h"
#include "inode_t.h"

namespace uasdk
{

class IReferenceTypeNode_t;
class IAddressSpace_t;

/** \addtogroup grpAddressSpace
 *@{*/

/*****************************************************************************/
/** \brief Node Reference Interface
 *
 * A class that represents a node reference in the address space.
 * Implementations of this interface must be thread safe.
 *
 */
class IReference_t : public IRefCount_t
{
public:
  virtual ~IReference_t() {};

  /*****************************************************************************/
  /** Get the TypeId of the reference
   *
   * @return
   * The TypeId of the reference.
   */
  virtual IntrusivePtr_t<const NodeId_t> TypeId(void) const = 0;

  /*****************************************************************************/
  /** Get the ReferenceType node of the reference
   *
   * Get a pointer to the reference type if it is stored internally inside the
   * reference.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * ReferenceType of the reference. All references do not contain pointers to
   * their ReferenceType so the caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const IReferenceTypeNode_t> Type(void) const = 0;

  /*****************************************************************************/
  /** Get the ReferenceType node of the reference
    *
   * Get a pointer to the reference type if it is stored internally inside the
   * reference or else search the address space.
   *
   * @param[in] addressSpace
   * The address space to search if necessary
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * ReferenceType of the reference. All references do not contain pointers to
   * their ReferenceType so the caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const IReferenceTypeNode_t> Type(const IAddressSpace_t& addressSpace) const = 0;

  /*****************************************************************************/
  /** Get the ReferenceType node of the reference
   *
   * Get a pointer to the reference type if it is stored internally inside the
   * reference.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * ReferenceType of the reference. All references do not contain pointers to
   * their ReferenceType so the caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<IReferenceTypeNode_t> Type(void) = 0;

  /*****************************************************************************/
  /** Get the ReferenceType node of the reference
    *
   * Get a pointer to the reference type if it is stored internally inside the
   * reference or else search the address space.
   *
   * @param[in] addressSpace
   * The address space to search if necessary
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * ReferenceType of the reference. All references do not contain pointers to
   * their ReferenceType so the caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<IReferenceTypeNode_t> Type(IAddressSpace_t& addressSpace) = 0;

  /*****************************************************************************/
  /** Get the ReferenceType node of the reference
    *
   * Get a pointer to the reference type if it is stored internally inside the
   * reference or else search the address space. Filter the result based on
   * user visibility and transport layer security.
   *
   * @param[in] addressSpace
   * The address space to search if necessary
   *
   * @param[in] userPermissions
   * The user authenticator to authenticate for node visibility
   *
   * @param[in] transportLayerIsSecure
   * The transport layer is secure
   *
   * @param[in] result
   * The result of the operation. Can be ignored unless the returned pointer is
   * empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * ReferenceType of the reference. All references do not contain pointers to
   * their ReferenceType so the caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<IReferenceTypeNode_t> Type(IAddressSpace_t& addressSpace,
                                                    const IUserPermissions_t& userPermissions,
                                                   bool transportLayerIsSecure,
                                                   Status_t& result) = 0;

  /*****************************************************************************/
  /** Get the TargetNodeId of the reference
   *
   * @return
   * The TargetNodeId of the reference.
   */
  virtual IntrusivePtr_t<const NodeId_t> TargetNodeId(void) const = 0;

  /*****************************************************************************/
  /** Get the target node of the reference
   *
   * Get a pointer to the target node if it is stored internally inside the
   * reference or else search the address space.
   *
   * @param[in] addressSpace
   * The address space to search if necessary
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * target node of the reference. All references do not contain pointers to
   * their target node so the caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const INode_t> TargetNode(const IAddressSpace_t& addressSpace) const = 0;

  /*****************************************************************************/
  /** Get the target node of the reference
   *
   * Get a pointer to the target node if it is stored internally inside the
   * reference.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * target node of the reference. All references do not contain pointers to
   * their target node so the caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<INode_t> TargetNode(void) = 0;

  /*****************************************************************************/
  /** Get the target node of the reference
   *
   * Get a pointer to the target node if it is stored internally inside the
   * reference or else search the address space.
   *
   * @param[in] addressSpace
   * The address space to search if necessary
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * target node of the reference. All references do not contain pointers to
   * their target node so the caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<INode_t> TargetNode(IAddressSpace_t& addressSpace) = 0;

  /*****************************************************************************/
  /** Get the target node of the reference
   *
   * Get a pointer to the target node if it is stored internally inside the
   * reference or else search the address space. Filter the result based on
   * user visibility and transport layer security.
   *
   * @param[in] addressSpace
   * The address space to search if necessary
   *
   * @param[in] userPermissions
   * The user authenticator to authenticate for node visibility
   *
   * @param[in] transportLayerIsSecure
   * The transport layer is secure
   *
   * @param[in] result
   * The result of the operation. Can be ignored unless the returned pointer is
   * empty.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * target node of the reference. All references do not contain pointers to
   * their target node so the caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<INode_t> TargetNode(IAddressSpace_t& addressSpace,
                                             const IUserPermissions_t& userPermissions,
                                            bool transportLayerIsSecure,
                                            Status_t& result) = 0;

  /*****************************************************************************/
  /** Is the reference an inverse reference?
   *
   * @return
   * "true" if the reference is an inverse reference.
   */
  virtual bool IsInverse(void) const = 0;

  /*****************************************************************************/
  /** Is the reference an a specific view?
   *
   * @return
   * "true" if the reference is the view.
   */
  virtual bool IsInView(const NodeId_t& viewId) const = 0;

  /*****************************************************************************/
  /** Add the reference to a view
   *
   * Make the reference visible when browsing a view.
   *
   * @param[in] viewId
   * An intrusive reference counting Boost-style smart pointer to the node ID of
   * the view. The value provided must satisfy a number of rules.
   * 1) No non-const references to theNodeId_t must exist,
   *    i.e. it must be immutable (to ensure thread safety).
   * 2) The NodeId_t must have been created dynamically using a
   *    SafeRefCount_t (to ensure thread safety).
   * 3) The value pointer must be set.
   *
   * @return
   * The result of the operation.
   */
  virtual Status_t AddView(IntrusivePtr_t<const NodeId_t> viewId) = 0;

  /*****************************************************************************/
  /** Remove the reference to a view
   *
   * Make the reference invisible when browsing a view.
   *
   * @param[in] viewId
   * An intrusive reference counting Boost-style smart pointer to the node ID of
   * the view. The value provided must satisfy a number of rules.
   * 1) No non-const references to theNodeId_t must exist,
   *    i.e. it must be immutable (to ensure thread safety).
   * 2) The NodeId_t must have been created dynamically using a
   *    SafeRefCount_t (to ensure thread safety).
   * 3) The value pointer must be set.
   *
   * @return
   * The result of the operation.
   */
  virtual Status_t RemoveView(const NodeId_t& viewId) = 0;
};

/** @} */

}

#endif // _IREFERENCE_T_
