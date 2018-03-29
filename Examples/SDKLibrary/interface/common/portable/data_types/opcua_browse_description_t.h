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

#ifndef _OPCUA_BROWSE_DESCRIPTION_T_
#define _OPCUA_BROWSE_DESCRIPTION_T_


#include "opcua_node_id_t.h"
#include "opcua_bytestring_t.h"
#include "opcua_string_t.h"
#include "opcua_browse_direction_t.h"
#include "opcua_boolean_t.h"
#include "opcua_uint32_t.h"
#include "opcua_node_class_t.h"
#include "opcua_structure_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief BrowseDescription_t
 *
 * This class implements the Browse Description data type
 *
 */
class BrowseDescription_t : public Structure_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(BrowseDescription_t);
private:

  /*****************************************************************************/
  /* @var IntrusivePtr_t<NodeId_t>  viewId
   * View id
   */
  IntrusivePtr_t<NodeId_t>  nodeId;

  /*****************************************************************************/
  /* @var BrowseDirection_t browseDirection
   * Browse direction
   */
  BrowseDirection_t         browseDirection;

  /*****************************************************************************/
  /* @var IntrusivePtr_t<NodeId_t>  refTypeId
   * Reference ID
   */
  IntrusivePtr_t<NodeId_t>  refTypeId;

  /*****************************************************************************/
  /* @var Boolean_t includeSubtypes
   * Include Sub types
   */
  Boolean_t                 includeSubtypes;

  /*****************************************************************************/
  /* @var UInt32_t nodeclassMask
   * Node class Mask
   */
  UInt32_t                  nodeclassMask;

  /*****************************************************************************/
  /* @var UInt32_t resultMask
   * Result Mask
   */
  UInt32_t                  resultMask;

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_BrowseDescription;

  /*****************************************************************************/
  /* @var uint32_t RESULT_MASK_REF_TYPE
   * Result mask reference type
   */
  static const uint32_t RESULT_MASK_REF_TYPE      = (1<<0);

  /*****************************************************************************/
  /* @var uint32_t RESULT_MASK_IS_FORWARD
   * Result mask is forward
   */
  static const uint32_t RESULT_MASK_IS_FORWARD    = (1<<1);

  /*****************************************************************************/
  /* @var uint32_t RESULT_MASK_NODE_CLASS
   * Result Mask Node Class
   */
  static const uint32_t RESULT_MASK_NODE_CLASS    = (1<<2);

  /*****************************************************************************/
  /* @var uint32_t RESULT_MASK_BROWSE_NAME
   * Result Mask browse name
   */
  static const uint32_t RESULT_MASK_BROWSE_NAME   = (1<<3);

  /*****************************************************************************/
  /* @var uint32_t RESULT_MASK_DISPLAY_NAME
   * Result mask display name
   */
  static const uint32_t RESULT_MASK_DISPLAY_NAME  = (1<<4);

  /*****************************************************************************/
  /* @var uint32_t RESULT_MASK_TYPE_DEF
   * Result mask type def
   */
  static const uint32_t RESULT_MASK_TYPE_DEF      = (1<<5);

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~BrowseDescription_t();

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
   * @param[in] BrowseDescription_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  bool operator==(BrowseDescription_t const & obj) const;

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
   * @param[in] BrowseDescription_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the first byte that does not match
   * in both the class member variables have a greater value in lhs than in rhs as if evaluated
   * as unsigned char values; And a value of false indicates the opposite.
   */
  bool operator>(BrowseDescription_t const & obj) const;

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
   * @param[in] const BrowseDescription_t& source
   * Application Description to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const BrowseDescription_t& source);

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
  /** Get the Node id
   *
   * @return
   * Returns the Node id
   */
  IntrusivePtr_t<const NodeId_t> NodeId(void) const;

  /*****************************************************************************/
  /** Get the
   *
   * @return
   * Returns the
   */
  IntrusivePtr_t<NodeId_t>& NodeId(void);

  /*****************************************************************************/
  /** Get the browse direction
   *
   * @return
   * Returns the browse direction
   */
  const BrowseDirection_t& BrowseDirection(void) const;

  /*****************************************************************************/
  /** Get the browse direction
   *
   * @return
   * Returns the browse direction
   */
  BrowseDirection_t& BrowseDirection(void);

  /*****************************************************************************/
  /** Get the Reference type id
   *
   * @return
   * Returns the Reference type id
   */
  IntrusivePtr_t<const NodeId_t> RefTypeId(void) const;

  /*****************************************************************************/
  /** Get the Reference type id
   *
   * @return
   * Returns the Reference type id
   */
  IntrusivePtr_t<NodeId_t>& RefTypeId(void);

  /*****************************************************************************/
  /** Get the Include Sub types
   *
   * @return
   * Returns the Include Sub types
   */
  const Boolean_t& IncludeSubtypes(void) const;

  /*****************************************************************************/
  /** Get the Include Sub types
   *
   * @return
   * Returns the Include Sub types
   */
  Boolean_t& IncludeSubtypes(void);

  /*****************************************************************************/
  /** Get the Node class Mask
   *
   * @return
   * Returns the Node class Mask
   */
  const UInt32_t& NodeclassMask(void) const;

  /*****************************************************************************/
  /** Get the Node class Mask
   *
   * @return
   * Returns the Node class Mask
   */
  UInt32_t& NodeclassMask(void);

  /*****************************************************************************/
  /** Get the Result Mask
   *
   * @return
   * Returns the Result Mask
   */
  const UInt32_t& ResultMask(void) const;

  /*****************************************************************************/
  /** Get the Result Mask
   *
   * @return
   * Returns the Result Mask
   */
  UInt32_t& ResultMask(void);

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
   * @param[out] BrowseDescription_t& result
   * Decoded Application Description
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, BrowseDescription_t& result);

  /*****************************************************************************/
  /** Check the node class is set or cleared
   *
   * @param[in] NodeClass_t::Enum_t node_class
   * Node class to filter
   *
   * @return
   * Node class is set or cleared
   */
  bool FilterNodeClass(NodeClass_t::Enum_t node_class) const;

};

/** @} */

} // namespace uasdk
#endif // _OPCUA_BROWSE_DESCRIPTION_T_
