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

#ifndef _INODE_REFERENCES_CHANGED_LISTENER_T_
#define _INODE_REFERENCES_CHANGED_LISTENER_T_

#include "uasdk_includes.h"
#include "iref_count_t.h"

namespace uasdk
{

class IObjectNode_t;
class IObjectTypeNode_t;
class IViewNode_t;
class IMethodNode_t;
class IVariableNode_t;
class IVariableTypeNode_t;
class IDataTypeNode_t;
class IReferenceTypeNode_t;
class INode_t;
class IReference_t;

/** \addtogroup grpAddressSpace
 *@{*/

class INodeReferencesChangedListener_t : public IRefCount_t
{
public:
  virtual ~INodeReferencesChangedListener_t() {};

  /*****************************************************************************/
  /** Reference Added Listener for Object Node
   *
   *  @param[in] node
   *  Node whose reference has been changed
   *
   *  @param[in] reference
   *  reference which is added for the Object node
   *
   */
  virtual void NodeReferenceAdded(IObjectNode_t& node,
                                  IReference_t& reference) = 0;

  /*****************************************************************************/
  /** Reference Added Listener for Object Type Node
   *
   *  @param[in] node
   *  Node whose reference has been changed
   *
   *  @param[in] reference
   *  reference which is added for the Object Type node
   *
   */
  virtual void NodeReferenceAdded(IObjectTypeNode_t& node,
                                  IReference_t& reference) = 0;

  /*****************************************************************************/
  /** Reference Added Listener for View Node
   *
   *  @param[in] node
   *  Node whose reference has been changed
   *
   *  @param[in] reference
   *  reference which is added for the view node
   *
   */
  virtual void NodeReferenceAdded(IViewNode_t& node,
                                  IReference_t& reference) = 0;

  /*****************************************************************************/
  /** Reference Added Listener for Method Node
   *
   *  @param[in] node
   *  Node whose reference has been changed
   *
   *  @param[in] reference
   *  reference which is added for the Method node
   *
   */
  virtual void NodeReferenceAdded(IMethodNode_t& node,
                                  IReference_t& reference) = 0;

  /*****************************************************************************/
  /** Reference Added Listener for Variable Node
   *
   *  @param[in] node
   *  Node whose reference has been changed
   *
   *  @param[in] reference
   *  reference which is added for the Variable node
   *
   */
  virtual void NodeReferenceAdded(IVariableNode_t& node,
                                  IReference_t& reference) = 0;

  /*****************************************************************************/
  /** Reference Added Listener for Variable Type Node
   *
   *  @param[in] node
   *  Node whose reference has been changed
   *
   *  @param[in] reference
   *  reference which is added for the Variable Type node
   *
   */
  virtual void NodeReferenceAdded(IVariableTypeNode_t& node,
                                  IReference_t& reference) = 0;

  /*****************************************************************************/
  /** Reference Added Listener for Data Type Node
   *
   *  @param[in] node
   *  Node whose reference has been changed
   *
   *  @param[in] reference
   *  reference which is added for the Data Type node
   *
   */
  virtual void NodeReferenceAdded(IDataTypeNode_t& node,
                                  IReference_t& reference) = 0;

  /*****************************************************************************/
  /** Reference Added Listener for Reference Type Node
   *
   *  @param[in] node
   *  Node whose reference has been changed
   *
   *  @param[in] reference
   *  reference which is added for the Reference Type node
   *
   */
  virtual void NodeReferenceAdded(IReferenceTypeNode_t& node,
                                  IReference_t& reference) = 0;

  /*****************************************************************************/
  /** Reference Removed Listener for Object Node
   *
   *  @param[in] node
   *  Node whose reference has been changed
   *
   *  @param[in] reference
   *  reference which is removed for the Object node
   *
   */
  virtual void NodeReferenceRemoved(IObjectNode_t& node,
                                  IReference_t& reference) = 0;

  /*****************************************************************************/
  /** Reference Removed Listener for Object Type Node
   *
   *  @param[in] node
   *  Node whose reference has been changed
   *
   *  @param[in] reference
   *  reference which is removed for the Object Type node
   *
   */
  virtual void NodeReferenceRemoved(IObjectTypeNode_t& node,
                                  IReference_t& reference) = 0;

  /*****************************************************************************/
  /** Reference removed Listener for View Node
   *
   *  @param[in] node
   *  Node whose reference has been changed
   *
   *  @param[in] reference
   *  reference which is removed for the view node
   */
  virtual void NodeReferenceRemoved(IViewNode_t& node,
                                  IReference_t& reference) = 0;

  /*****************************************************************************/
  /** Reference removed Listener for Method Node
   *
   *  @param[in] node
   *  Node whose reference has been changed
   *
   *  @param[in] reference
   *  reference which is removed for the Method node
   */
  virtual void NodeReferenceRemoved(IMethodNode_t& node,
                                  IReference_t& reference) = 0;

  /*****************************************************************************/
  /** Reference removed Listener for Variable Node
   *
   *  @param[in] node
   *  Node whose reference has been changed
   *
   *  @param[in] reference
   *  reference which is removed for the Variable node
   */
  virtual void NodeReferenceRemoved(IVariableNode_t& node,
                                  IReference_t& reference) = 0;

  /*****************************************************************************/
  /** Reference removed Listener for Variable Type Node
   *
   *  @param[in] node
   *  Node whose reference has been changed
   *
   *  @param[in] reference
   *  reference which is removed for the Variable Type node
   */
  virtual void NodeReferenceRemoved(IVariableTypeNode_t& node,
                                  IReference_t& reference) = 0;

  /*****************************************************************************/
  /** Reference removed Listener for Data Type Node
   *
   *  @param[in] node
   *  Node whose reference has been changed
   *
   *  @param[in] reference
   *  reference which is removed for the Data Type node
   */
  virtual void NodeReferenceRemoved(IDataTypeNode_t& node,
                                  IReference_t& reference) = 0;

  /*****************************************************************************/
  /** Reference removed Listener for Reference Type Node
   *
   *  @param[in] node
   *  Node whose reference has been changed
   *
   *  @param[in] reference
   *  reference which is removed for the Reference Type node
   */
  virtual void NodeReferenceRemoved(IReferenceTypeNode_t& node,
                                  IReference_t& reference) = 0;

};

/** @} */


}

#endif // _INODE_REFERENCES_CHANGED_LISTENER_T_
