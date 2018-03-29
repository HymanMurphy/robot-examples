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

#ifndef _OPCUA_NODE_CLASS_T_
#define _OPCUA_NODE_CLASS_T_


#include "opcua_enumeration_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief NodeClass_t
 *
 * This class implements the Node ID data type
 */
class NodeClass_t : public Enumeration_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(NodeClass_t);

  /*****************************************************************************/
  /** \brief Enumeration of Node class types
   */
  typedef enum 
  {
    OPCUA_NODECLASS_INVALID         = 0,
    OPCUA_NODECLASS_OBJECT          = 1,
    OPCUA_NODECLASS_VARIABLE        = 2,
    OPCUA_NODECLASS_METHOD          = 4,
    OPCUA_NODECLASS_OBJECT_TYPE     = 8,
    OPCUA_NODECLASS_VARIABLE_TYPE   = 16,
    OPCUA_NODECLASS_REFERENCE_TYPE  = 32,
    OPCUA_NODECLASS_DATA_TYPE       = 64,
    OPCUA_NODECLASS_VIEW            = 128,
    OPCUA_NODECLASS_END
  } Enum_t;

private:

  /*****************************************************************************/
  /* @var Enum_t value
   * Node class value
   */
  Enum_t value;


  /*****************************************************************************/
  /* This function used to write the integer value to Enum type
   *
   * Integer value for the enumeration
   *
   * @return
   * Status of the operation
   */
  virtual Status_t WriteIntToValue(int32_t newValue);

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_NodeClass;

  /*****************************************************************************/
  /** Default constructor for the class.
   *
   */
  NodeClass_t();

  /*****************************************************************************/
  /** Constructor for the class.
   *
   * @param[in] Enum_t value
   * Node class value to be set
   *
   */
  NodeClass_t(Enum_t value);

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~NodeClass_t();

  /*****************************************************************************/
  /** = operator overloading
   *
   * @param[in] NodeClass_t const & rhs
   * Object to be assigned
   *
   * @return
   * NodeClass_t object assigned
   */
  NodeClass_t& operator=(NodeClass_t const & rhs);

  /*****************************************************************************/
  /** = operator overloading
   *
   * @param[in] Enum_t const & rhs
   * Object to be assigned
   *
   * @return
   * NodeClass_t object assigned
   */
  NodeClass_t& operator=(Enum_t const & rhs);

  /*****************************************************************************/
  /** == operator overloading
   *
   * @param[in] BaseDataType_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  virtual bool operator==(BaseDataType_t const & obj) const;

  /*****************************************************************************/
  /** == operator overloading
   *
   * @param[in] NodeClass_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  bool operator==(NodeClass_t const & obj) const;

  /*****************************************************************************/
  /** > operator overloading
   *
   * @param[in] BaseDataType_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If grater than RHS
   * False - If less than RHS
   */
  virtual bool operator>(BaseDataType_t const & obj) const;

  /*****************************************************************************/
  /** > operator overloading
   *
   * @param[in] NodeClass_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS NodeClass_t object is greater than RHS NodeClass_t object
   */
  bool operator>(NodeClass_t const & obj) const;

  /*****************************************************************************/
  /** Copy to the destination
   *
   * @param[out] IntrusivePtr_t<BaseDataType_t>& destination
   * Destination data to copy to
   *
   * @return
   * Status of the operation
   */
  virtual Status_t CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const;

  /*****************************************************************************/
  /** Copy from the source
   *
   * @param[in] const BaseDataType_t& source
   * Source data type
   *
   * @return
   * Status of the operation
   */
  virtual Status_t CopyFrom(const BaseDataType_t& source);

  /*****************************************************************************/
  /** Copy from the source
   *
   * @param[in] const NodeClass_t& source
   *  Node class  source object to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const NodeClass_t& source);

  /*****************************************************************************/
  /** Get the Type ID
   *
   * @param[in] uint16_t& namespaceIndex
   * Name space index
   *
   * @return
   * Returns the Type ID
   */
  virtual uint32_t TypeId(uint16_t& namespaceIndex) const;

  /*****************************************************************************/
  /** Get the node class value
   *
   * @return
   * Returns the node class value
   */
  const NodeClass_t::Enum_t& Value(void) const;

  /*****************************************************************************/
  /** Get the node class value
   *
   * @return
   * Returns the node class value
   */
  NodeClass_t::Enum_t& Value(void);

  /*****************************************************************************/
  /** Encode the buffer
   *
   * @param[in] ICodec_t& encoder
   * Reference to the encoder object
   *
   * @param[out] IBuffer_t& buffer
   * Encode buffer
   *
   * @return
   * Returns status of the operation
   */
  Status_t Encode(ICodec_t& encoder, IBuffer_t& buffer) const;
};

/** @} */

} // namespace uasdk
#endif // _OPCUA_NODE_CLASS_T_
