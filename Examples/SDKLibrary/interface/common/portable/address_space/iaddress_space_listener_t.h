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

#ifndef _IADDRESS_SPACE_LISTENER_T_H_
#define _IADDRESS_SPACE_LISTENER_T_H_

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
class NodeTypeMask_t;

/** \addtogroup grpAddressSpace
 *@{*/
 
class IAddressSpaceListener_t : public IRefCount_t
{
public:

  virtual ~IAddressSpaceListener_t() {};

  /*****************************************************************************/
  /** Node Created Listener for Object Node
   *
   *  @param[in] node
   *  Node which is created.
   */
  virtual void NodeCreated(const IObjectNode_t& node_) = 0;

  /*****************************************************************************/
  /** Node Created Listener for ObjectType Node
   *
   *  @param[in] node
   *  Node which is created.
   */
  virtual void NodeCreated(const IObjectTypeNode_t& node_) = 0;

  /*****************************************************************************/
  /** Node Created Listener for View Node
   *
   *  @param[in] node
   *  Node which is created.
   */
  virtual void NodeCreated(const IViewNode_t& node_) = 0;

  /*****************************************************************************/
  /** Node Created Listener for Method Node
   *
   *  @param[in] node
   *  Node which is created.
   */
  virtual void NodeCreated(const IMethodNode_t& node_) = 0;

  /*****************************************************************************/
  /** Node Created Listener for Variable Node
   *
   *  @param[in] node
   *  Node which is created.
   */
  virtual void NodeCreated(const IVariableNode_t& node_) = 0;

  /*****************************************************************************/
  /** Node Created Listener for VariableType Node
   *
   *  @param[in] node
   *  Node which is created.
   */
  virtual void NodeCreated(const IVariableTypeNode_t& node_) = 0;

  /*****************************************************************************/
  /** Node Created Listener for DataType Node
   *
   *  @param[in] node
   *  Node which is created.
   */
  virtual void NodeCreated(const IDataTypeNode_t& node_) = 0;

  /*****************************************************************************/
  /** Node Created Listener for ReferenceType Node
   *
   *  @param[in] node
   *  Node which is created.
   */
  virtual void NodeCreated(const IReferenceTypeNode_t& node_) = 0;

  /*****************************************************************************/
  /** Node Deleted Listener
   *
   *  @param[in] node
   *  Node which will be deleted.
   */
  virtual void NodeDeleted(const INode_t& node_) = 0;

  /*****************************************************************************/
  /** Node Type Mask for the listener
  *
  *  @return
  *  NodeTypeMask object.
  */
  virtual NodeTypeMask_t NodeTypeMask(const INode_t& node_) = 0;
};

/** @} */

} //namespace uasdk

#endif  //_IADDRESS_SPACE_LISTENER_T_H_