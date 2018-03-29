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

#ifndef _OPCUA_EXPANDED_NODE_ID_T_
#define _OPCUA_EXPANDED_NODE_ID_T_

#include "opcua_node_id_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief ExpandedNodeId_t
 *
 * This class implements the Expanded Node id data type
 *
 */
class ExpandedNodeId_t : public BaseDataType_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(ExpandedNodeId_t);

private:

  /*****************************************************************************/
  /* @var IntrusivePtr_t<NodeId_t> nodeid
   * An intrusive reference counting Boost-style smart pointer to the Node id.
   */
  IntrusivePtr_t<NodeId_t>  nodeid;

  /*****************************************************************************/
  /* @var String_t namespaceUri
   * Namespace URI
   */
  String_t                  namespaceUri;

  /*****************************************************************************/
  /* @var UInt64_t serverIndex
   * Server Index
   */
  UInt32_t                  serverIndex;

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_ExpandedNodeId;

  /*****************************************************************************/
  /** Default constructor for the class.
   *
   */
  ExpandedNodeId_t();

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~ExpandedNodeId_t();

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
   * @param[in] ExpandedNodeId_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  bool operator==(ExpandedNodeId_t const & obj) const;

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
   * @param[in] ExpandedNodeId_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS ExpandedNodeId_t object is greater than RHS ExpandedNodeId_t object
   */
  bool operator>(ExpandedNodeId_t const & obj) const;

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
   * @param[in] const ExpandedNodeId_t& source
   *  ExpandedNodeId_t source to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const ExpandedNodeId_t& source);

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
  /** Get the Node id
   *
   * @return
   * Returns the Node id
   */
  IntrusivePtr_t<const NodeId_t> Nodeid(void) const;

  /*****************************************************************************/
  /** Get the Node id
   *
   * @return
   * Returns the Node id
   */
  IntrusivePtr_t<NodeId_t>& Nodeid(void);

  /*****************************************************************************/
  /** Get the Name space URI
   *
   * @return
   * Returns the Name space URI
   */
  const String_t& NamespaceUri(void) const;

  /*****************************************************************************/
  /** Get the Name space URI
   *
   * @return
   * Returns the Name space URI
   */
  String_t& NamespaceUri(void);

  /*****************************************************************************/
  /** Get the Server index
   *
   * @return
   * Returns the Server index
   */
  const UInt32_t& ServerIndex(void) const;

  /*****************************************************************************/
  /** Get the Server index
   *
   * @return
   * Returns the Server index
   */
  UInt32_t& ServerIndex(void);

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
   * @param[out] ExpandedNodeId_t& result
   * Decoded ExpandedNodeId_t object object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, ExpandedNodeId_t& result);
};

/** @} */

} // namespace uasdk
#endif // _OPCUA_EXPANDED_NODE_ID_T_
