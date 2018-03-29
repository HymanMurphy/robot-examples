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

#ifndef _INODE_ATTRIBUTE_ABOUT_TO_BE_READ_LISTENER_T_
#define _INODE_ATTRIBUTE_ABOUT_TO_BE_READ_LISTENER_T_

#include "uasdk_includes.h"
#include "iref_count_t.h"
#include "attribute_id_mask_t.h"

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

/** \addtogroup grpAddressSpace
 *@{*/

class INodeAttributeAboutToBeReadListener_t : public IRefCount_t
{
public:
  virtual ~INodeAttributeAboutToBeReadListener_t() {};

  /*****************************************************************************/
  /** Attribute about to be read for a Object node
   *
   *  @param[in] node
   *  Node whose attribute about to be read
   *
   *  @param[in] attributeId
   *  Id of the attribute which is read
   *
   */
  virtual void NodeAttributeAboutToBeRead(const IObjectNode_t& node,
                                          AttributeId_t::Enum_t attributeId) = 0;

  /*****************************************************************************/
  /** Attribute about to be read for a Object Type node
   *
   *  @param[in] node
   *  Node whose attribute about to be read
   *
   *  @param[in] attributeId
   *  Id of the attribute which is read
   */
  virtual void NodeAttributeAboutToBeRead(const IObjectTypeNode_t& node,
                                          AttributeId_t::Enum_t attributeId) = 0;

  /*****************************************************************************/
  /** Attribute about to be read for a View node
   *
   *  @param[in] node
   *  Node whose attribute about to be read
   *
   *  @param[in] attributeId
   *  Id of the attribute which is read
   *
   */
  virtual void NodeAttributeAboutToBeRead(const IViewNode_t& node,
                                          AttributeId_t::Enum_t attributeId) = 0;

  /*****************************************************************************/
  /** Attribute about to be read for a Method node
   *
   *  @param[in] node
   *  Node whose attribute about to be read
   *
   *  @param[in] attributeId
   *  Id of the attribute which is read
   *
   */
  virtual void NodeAttributeAboutToBeRead(const IMethodNode_t& node,
                                          AttributeId_t::Enum_t attributeId) = 0;

  /*****************************************************************************/
  /** Attribute about to be read for a Variable node
   *
   *  @param[in] node
   *  Node whose attribute about to be read
   *
   *  @param[in] attributeId
   *  Id of the attribute which is read
   *
   */
  virtual void NodeAttributeAboutToBeRead(const IVariableNode_t& node,
                                          AttributeId_t::Enum_t attributeId) = 0;

  /*****************************************************************************/
  /** Attribute about to be read for a Variable Type node
   *
   *  @param[in] node
   *  Node whose attribute about to be read
   *
   *  @param[in] attributeId
   *  Id of the attribute which is read
   *
   */
  virtual void NodeAttributeAboutToBeRead(const IVariableTypeNode_t& node,
                                          AttributeId_t::Enum_t attributeId) = 0;

  /*****************************************************************************/
  /** Attribute about to be read for a Data Type node
   *
   *  @param[in] node
   *  Node whose attribute about to be read
   *
   *  @param[in] attributeId
   *  Id of the attribute which is read
   *
   */
  virtual void NodeAttributeAboutToBeRead(const IDataTypeNode_t& node,
                                          AttributeId_t::Enum_t attributeId) = 0;

  /*****************************************************************************/
  /** Attribute about to be read for a Reference Type node
   *
   *  @param[in] node
   *  Node whose attribute about to be read
   *
   *  @param[in] attributeId
   *  Id of the attribute which is read
   *
   */
  virtual void NodeAttributeAboutToBeRead(const IReferenceTypeNode_t& node,
                                          AttributeId_t::Enum_t attributeId) = 0;

  /*****************************************************************************/
  /** This function will return the the attribute id Mask
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

#endif // _INODE_ATTRIBUTE_ABOUT_TO_BE_READ_LISTENER_T_
