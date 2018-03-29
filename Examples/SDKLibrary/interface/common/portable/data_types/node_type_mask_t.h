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

#ifndef _OPCUA_NODECLASS_MASK_T_H_
#define _OPCUA_NODECLASS_MASK_T_H_

#include "uasdk_includes.h"
#include "opcua_uint32_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief NodeTypeMask_t
*
* This class implements the Node Class Mask
*
*/
class NodeTypeMask_t : public UInt32_t
{
private:
  /*****************************************************************************/
  /** Set or Clear
  *
  * @param[in] bool val
  * Set or clear
  *
  * @param[in] uint32_t bit
  * Attribute ID to set or clear
  */
  void SetOrClear(bool val, uint32_t bit)
  {
    if (bit < NodeClass_t::OPCUA_NODECLASS_END)
    {
      if (val)
      {
        value |= bit;
      }
      else
      {
        value &= ~bit;
      }
    }
  }
public:
  /*****************************************************************************/
  /** default constructor for the class.
  *
  */
  NodeTypeMask_t() {}

  /*****************************************************************************/
  /** constructor for the class.
  *
  * @param[in] uint8_t val
  * Node Class
  *
  */
  NodeTypeMask_t(uint32_t val) : UInt32_t(val) {}

  /*****************************************************************************/
  /** Copy constructor
  *
  * @param[in] NodeTypeMask_t const & other
  * Object to be copied from
  */
  NodeTypeMask_t(NodeTypeMask_t const & other) : UInt32_t() { value = other.value; }

  /*****************************************************************************/
  /** Destructor for the class.
  *
  */
  virtual ~NodeTypeMask_t() {}

  /*****************************************************************************/
  /** Get the Object Node bit from Node Class
  *
  * @return
  * Returns the Object Node bit from the Node Class
  */
  bool ObjectNode(void) const
  {
    return (value & NodeClass_t::OPCUA_NODECLASS_OBJECT) != 0;
  }

  /*****************************************************************************/
  /** Set the Object Node bit from the Node Class
  *
  * @param[in] bool val
  * The Object Node bit from the Node Class to set or clear
  */
  void ObjectNode(bool val)
  {
    SetOrClear(val, NodeClass_t::OPCUA_NODECLASS_OBJECT);
  }

  /*****************************************************************************/
  /** Get the ObjectType Node bit from the Node Class
  *
  * @return
  * Returns the ObjectType Node bit from the Node Class
  */
  bool ObjectTypeNode(void) const
  {
    return (value & NodeClass_t::OPCUA_NODECLASS_OBJECT_TYPE) != 0;
  }

  /*****************************************************************************/
  /** Set the ObjectType Node bit from the Node Class
  *
  * @param[in] bool val
  * The ObjectType Node bit from the Node Class to set or clear
  */
  void ObjectTypeNode(bool val)
  {
    SetOrClear(val, NodeClass_t::OPCUA_NODECLASS_OBJECT_TYPE);
  }

  /*****************************************************************************/
  /** Get the View Node bit from the Node Class
  *
  * @return
  * Returns the View Node bit from the Node Class
  */
  bool ViewNode(void) const
  {
    return (value & NodeClass_t::OPCUA_NODECLASS_VIEW) != 0;
  }

  /*****************************************************************************/
  /** Set the View Node bit from the Node Class
  *
  * @param[in] bool val
  * The View Node bit from the Node Class to set or clear
  */
  void ViewNode(bool val)
  {
    SetOrClear(val, NodeClass_t::OPCUA_NODECLASS_VIEW);
  }

  /*****************************************************************************/
  /** Get the Method Node bit from the Node Class
  *
  * @return
  * Returns the Method Node bit from the Node Class
  */
  bool MethodNode(void) const
  {
    return (value & NodeClass_t::OPCUA_NODECLASS_METHOD) != 0;
  }

  /*****************************************************************************/
  /** Set the Method Node bit from the Node Class
  *
  * @param[in] bool val
  * The Method Node bit from the Node Class to set or clear
  */
  void MethodNode(bool val)
  {
    SetOrClear(val, NodeClass_t::OPCUA_NODECLASS_METHOD);
  }

  /*****************************************************************************/
  /** Get the DataType Node bit from the Node Class
  *
  * @return
  * Returns the DataType Node bit from the Node Class
  */
  bool DataTypeNode(void) const
  {
    return (value & NodeClass_t::OPCUA_NODECLASS_DATA_TYPE) != 0;
  }

  /*****************************************************************************/
  /** Set the DataType Node bit from the Node Class
  *
  * @param[in] bool val
  * The DataType Node bit from the Node Class to set or clear
  */
  void DataTypeNode(bool val)
  {
    SetOrClear(val, NodeClass_t::OPCUA_NODECLASS_DATA_TYPE);
  }

  /*****************************************************************************/
  /** Get the Variable Node bit from the Node Class
  *
  * @return
  * Returns the Variable Node bit from the Node Class
  */
  bool VariableNode(void) const
  {
    return (value & NodeClass_t::OPCUA_NODECLASS_VARIABLE) != 0;
  }

  /*****************************************************************************/
  /** Set the Variable Node bit from the Node Class
  *
  * @param[in] bool val
  * The Variable Node bit from the Node Class to set or clear
  */
  void VariableNode(bool val)
  {
    SetOrClear(val, NodeClass_t::OPCUA_NODECLASS_VARIABLE);
  }

  /*****************************************************************************/
  /** Get the VariableType Node bit from the Node Class
  *
  * @return
  * Returns the VariableType Node bit from the Node Class
  */
  bool VariableTypeNode(void) const
  {
    return (value & NodeClass_t::OPCUA_NODECLASS_VARIABLE_TYPE) != 0;
  }

  /*****************************************************************************/
  /** Set the VariableType Node bit from the Node Class
  *
  * @param[in] bool val
  * The VariableType Node bit from the Node Class to set or clear
  */
  void VariableTypeNode(bool val)
  {
    SetOrClear(val, NodeClass_t::OPCUA_NODECLASS_VARIABLE_TYPE);
  }

  /*****************************************************************************/
  /** Get the ReferenceType Node bit from the Node Class
  *
  * @return
  * Returns the ReferenceType Node bit from the Node Class
  */
  bool ReferenceTypeNode(void) const
  {
    return (value & NodeClass_t::OPCUA_NODECLASS_REFERENCE_TYPE) != 0;
  }

  /*****************************************************************************/
  /** Set the ReferenceType Node bit from the Node Class
  *
  * @param[in] bool val
  * The ReferenceType Node bit from the Node Class to set or clear
  */
  void ReferenceTypeNode(bool val)
  {
    SetOrClear(val, NodeClass_t::OPCUA_NODECLASS_REFERENCE_TYPE);
  }

  /*****************************************************************************/
  /** Check if the Node Class bit is set or not
  *
  * @param[in] NodeClass_t::Enum_t nodeType
  * Node Class bit to check
  *
  * @return
  * True - If the Node Class bit requested is set
  * False -  If the Node Class bit requested is cleared
  *
  */
  bool IsSet(NodeClass_t::Enum_t nodeType_)
  {
    return (value & nodeType_) != 0;
  }

};

/** @} */

} // namespace uasdk

#endif // _OPCUA_NODECLASS_MASK_T_H_
