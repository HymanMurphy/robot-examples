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

#ifndef _INODE_ATTRIBUTE_CHANGED_LISTENER_T_
#define _INODE_ATTRIBUTE_CHANGED_LISTENER_T_

#include "uasdk_includes.h"

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
class AttributeIdMask_t;

/** \addtogroup grpAddressSpace
 *@{*/
class INodeAttributeChangedListener_t : public IRefCount_t
{
public:
  virtual ~INodeAttributeChangedListener_t() {};

  /*****************************************************************************/
  /** Attribute changed Listener for Object Node
   *
   *  @param[in] node
   *  Node whose attribute has been changed
   *
   *  @param[in] attributeId
   *  Id of the attribute which is changed
   *
   */
  virtual void NodeAttributeChanged(IObjectNode_t& node,
                                    AttributeId_t::Enum_t attributeId) = 0;

  /*****************************************************************************/
  /** Attribute changed Listener for Object Type Node
   *
   *  @param[in] node
   *  Node whose attribute has been changed
   *
   *  @param[in] attributeId
   *  Id of the attribute which is changed
   *
   */
  virtual void NodeAttributeChanged(IObjectTypeNode_t& node,
                                    AttributeId_t::Enum_t attributeId) = 0;

  /*****************************************************************************/
  /** Attribute changed Listener for View Node
   *
   *  @param[in] node
   *  Node whose attribute has been changed
   *
   *  @param[in] attributeId
   *  Id of the attribute which is changed
   *
   */
  virtual void NodeAttributeChanged(IViewNode_t& node,
                                    AttributeId_t::Enum_t attributeId) = 0;

  /*****************************************************************************/
  /** Attribute changed Listener for Method Node
   *
   *  @param[in] node
   *  Node whose attribute has been changed
   *
   *  @param[in] attributeId
   *  Id of the attribute which is changed
   *
   */
  virtual void NodeAttributeChanged(IMethodNode_t& node,
                                    AttributeId_t::Enum_t attributeId) = 0;

  /*****************************************************************************/
  /** Attribute changed Listener for Variable Node
   *
   *  @param[in] node
   *  Node whose attribute has been changed
   *
   *  @param[in] attributeId
   *  Id of the attribute which is changed
   *
   */
  virtual void NodeAttributeChanged(IVariableNode_t& node,
                                    AttributeId_t::Enum_t attributeId) = 0;

  /*****************************************************************************/
  /** Attribute changed Listener for Variable Type Node
   *
   *  @param[in] node
   *  Node whose attribute has been changed
   *
   *  @param[in] attributeId
   *  Id of the attribute which is changed
   *
   */
  virtual void NodeAttributeChanged(IVariableTypeNode_t& node,
                                    AttributeId_t::Enum_t attributeId) = 0;

  /*****************************************************************************/
  /** Attribute changed Listener for Data Type Node
   *
   *  @param[in] node
   *  Node whose attribute has been changed
   *
   *  @param[in] attributeId
   *  Id of the attribute which is changed
   *
   */
  virtual void NodeAttributeChanged(IDataTypeNode_t& node,
                                    AttributeId_t::Enum_t attributeId) = 0;

  /*****************************************************************************/
  /** Attribute changed Listener for Reference Type Node
   *
   *  @param[in] node
   *  Node whose attribute has been changed
   *
   *  @param[in] attributeId
   *  Id of the attribute which is changed
   *
   */
  virtual void NodeAttributeChanged(IReferenceTypeNode_t& node,
                                    AttributeId_t::Enum_t attributeId) = 0;

  /*****************************************************************************/
  /** This function will return the the attribute Mask ID
   *
   *  @param[in] node
   *  Node whose attribute id mask is required
   *
   *  @return
   *  Attribute Mask ID
   */
  virtual AttributeIdMask_t AttributeMask(const INode_t& node) const = 0;
};

/** @} */
}

#endif // _INODE_ATTRIBUTE_CHANGED_LISTENER_T_
