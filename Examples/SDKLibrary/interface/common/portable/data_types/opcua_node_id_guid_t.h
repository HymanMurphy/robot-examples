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

#ifndef _OPCUA_NODE_ID_GUID_T_
#define _OPCUA_NODE_ID_GUID_T_

#include "opcua_node_id_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief NodeIdGuid_t
 *
 * This class implements the Node ID GUID  data type
 *
 */
class NodeIdGuid_t : public NodeId_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(NodeIdGuid_t);
private:

  /*****************************************************************************/
  /* @var Guid_t identifier
   * Identifier
   */
  Guid_t identifier;

  /*****************************************************************************/
  /** Constructor for the class.
   *
   * @param[in] const uint8_t* data
   * Node ID value to be set
   */
  NodeIdGuid_t(NodeId_t const &);

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_NodeId;

  /*****************************************************************************/
  /** Default constructor for the class.
   *
   */
  NodeIdGuid_t();

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~NodeIdGuid_t();

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
   * @param[in] NodeIdGuid_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  bool operator==(NodeIdGuid_t const & obj) const;

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
   * @param[in] NodeIdGuid_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS NodeIdGuid_t object is greater than RHS NodeIdGuid_t object
   */
  bool operator>(NodeIdGuid_t const & obj) const;

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
   * @param[in] const NodeIdGuid_t& source
   *  NodeIdGuid_t source to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const NodeIdGuid_t& source);

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
  /** Copy to the Node ID
   *
   * @param[out] IntrusivePtr_t<NodeId_t>& destination
   * Destination data to copy to
   *
   * @return
   * Status of the operation
   */
  virtual Status_t CopyToNodeId(IntrusivePtr_t<NodeId_t>& destination) const;

  /*****************************************************************************/
  /** Get the Node ID Identifier Type
   *
   * @return
   * Returns the Node ID Identifier Type
   */
  virtual NodeIdIdentifierType_t NodeIdIdentiferType(void) const;

  /*****************************************************************************/
  /** Get the Identifier Base
   *
   * @return
   * Returns the Identifier Base.
   */
  const BaseDataType_t& IdentiferBase(void) const;

  /*****************************************************************************/
  /** Get the Identifier Base
   *
   * @return
   * Returns the Identifier Base.
   */
  BaseDataType_t& IdentiferBase(void);

  /*****************************************************************************/
  /** Get the Identifier
   *
   * @return
   * Returns the Identifier.
   */
  const Guid_t& Identifer(void) const;

  /*****************************************************************************/
  /** Get the Identifier
   *
   * @return
   * Returns the Identifier.
   */
  Guid_t& Identifer(void);

  /*****************************************************************************/
  /** Check if the GUID is null or not
   *
   * @return
   * Returns true if the GUID is null.
   */
  bool IsNull(void) const;

  /*****************************************************************************/
  /** Hash
   *
   * @return
   * Returns hash value
   */
  uint32_t Hash(void) const;

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

} //namespace uasdk

#endif // _OPCUA_NODE_ID_GUID_T_
