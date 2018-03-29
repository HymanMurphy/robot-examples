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

#ifndef _OPCUA_REFERENCE_DESCRIPTION_T_
#define _OPCUA_REFERENCE_DESCRIPTION_T_

#include "opcua_structure_t.h"
#include "opcua_node_id_t.h"
#include "opcua_boolean_t.h"
#include "opcua_expanded_node_id_t.h"
#include "opcua_qualified_name_t.h"
#include "opcua_localized_text_t.h"
#include "opcua_node_class_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief ReferenceDescription_t
 *
 * This class implements the Reference Description data type
 *
 */
class ReferenceDescription_t : public Structure_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(ReferenceDescription_t);
private:

  /*****************************************************************************/
  /* @var IntrusivePtr_t<NodeId_t> refTypeId
   * An intrusive reference counting Boost-style smart pointer to the Reference type ID
   */
  IntrusivePtr_t<NodeId_t>      refTypeId;

  /*****************************************************************************/
  /* @var Boolean_t isForward
   * Is forward
   */
  Boolean_t                     isForward;

  /*****************************************************************************/
  /* @var ExpandedNodeId_t nodeId
   * Node id
   */
  ExpandedNodeId_t              nodeId;

  /*****************************************************************************/
  /* @var QualifiedName_t browseName
   * Brows name
   */
  QualifiedName_t               browseName;

  /*****************************************************************************/
  /* @var LocalizedText_t displayName
   * display name
   */
  LocalizedText_t               displayName;

  /*****************************************************************************/
  /* @var NodeClass_t nodeclass
   * Node class
   */
  NodeClass_t                   nodeclass;

  /*****************************************************************************/
  /* @var ExpandedNodeId_t typeDefinition
   * Type definition
   */
  ExpandedNodeId_t              typeDefinition;

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_ReferenceDescription;

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~ReferenceDescription_t();

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
  /** = operator overloading
   *
   * @param[in] const ReferenceDescription_t& obj
   * Object to be assigned
   *
   * @return
   * Reference to the Reference Description object assigned
   */
  bool operator==(ReferenceDescription_t const & obj) const;

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
   * @param[in] ReferenceDescription_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS ReferenceDescription_t object is greater than RHS ReferenceDescription_t object
   */
  bool operator>(ReferenceDescription_t const & obj) const;

  /*****************************************************************************/
  /** Copy to the destination
   *
   * @param[out] IntrusivePtr_t<BaseDataType_t>& destination
   * Destination data type
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
   * @param[in] const ReferenceDescription_t& source
   *  Reference Description source to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const ReferenceDescription_t& source);

  /*****************************************************************************/
  /** Get the Type ID
   *
   * @param[in] uint16_t& namespaceIndex
   * Reference to the name space index
   *
   * @return
   * Returns the Type ID
   */
  virtual uint32_t TypeId(uint16_t& namespaceIndex) const;

  /*****************************************************************************/
  /** Get the Binary Encoding Id
   *
   * @param[in] uint16_t& namespaceIndex
   * Reference to the name space index
   *
   * @return
   * Returns the Binary Encoding Id
   */
  virtual uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const;

  /*****************************************************************************/
  /** Get the Reference type ID.
   *
   * @return
   * Returns the Reference type ID. An intrusive reference counting Boost-style
   * smart pointer to the Reference type ID. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const NodeId_t> RefTypeId(void) const;

  /*****************************************************************************/
  /** Get the Reference type ID.
   *
   * @return
   * Returns the Reference type ID. An intrusive reference counting Boost-style
   * smart pointer to the Reference type ID. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<NodeId_t>& RefTypeId(void);

  /*****************************************************************************/
  /** Get the "is forward flag"
   *
   * @return
   * Return true if forward
   */
  const Boolean_t& IsForward(void) const;

  /*****************************************************************************/
  /** Get the "is forward flag"
   *
   * @return
   * Return true if forward
   */
  Boolean_t& IsForward(void);

  /*****************************************************************************/
  /** Get the node ID
   *
   * @return
   * Return the node ID
   */
  const ExpandedNodeId_t& NodeId(void) const;

  /*****************************************************************************/
  /** Get the node ID
   *
   * @return
   * Return the node ID
   */
  ExpandedNodeId_t& NodeId(void);

  /*****************************************************************************/
  /** Get the Browse Name
   *
   * @return
   * Return the Browse Name
   */
  const QualifiedName_t& BrowseName(void) const;

  /*****************************************************************************/
  /** Get the Browse Name
   *
   * @return
   * Return the Browse Name
   */
  QualifiedName_t& BrowseName(void);

  /*****************************************************************************/
  /** Get the Display Name
   *
   * @return
   * Return the Display Name
   */
  const LocalizedText_t& DisplayName(void) const;

  /*****************************************************************************/
  /** Get the Display Name
   *
   * @return
   * Return the Display Name
   */
  LocalizedText_t& DisplayName(void);

  /*****************************************************************************/
  /** Get the Node class
   *
   * @return
   * Return the Node class
   */
  const NodeClass_t& Nodeclass(void) const;

  /*****************************************************************************/
  /** Get the Node class
   *
   * @return
   * Return the Node class
   */
  NodeClass_t& Nodeclass(void);

  /*****************************************************************************/
  /** Get the Type Definition
   *
   * @return
   * Return the Type Definition
   */
  const ExpandedNodeId_t& TypeDefinition(void) const;

  /*****************************************************************************/
  /** Get the Type Definition
   *
   * @return
   * Return the Type Definition
   */
  ExpandedNodeId_t& TypeDefinition(void);

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

  /*****************************************************************************/
  /** Decode the buffer
   *
   * @param[in] const IBuffer_t& buffer
   * Decode buffer
   *
   * @param[in] ICodec_t& decoder
   * Reference to the decoder object
   *
   * @param[out] ReferenceDescription_t& result
   * Decoded Reference Description object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, ReferenceDescription_t& result);
};

/** @} */

} // namespace uasdk

#endif // _OPCUA_REFERENCE_DESCRIPTION_T_
