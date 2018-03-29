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

#ifndef _OPCUA_WRITE_VALUE_T_
#define _OPCUA_WRITE_VALUE_T_

#include "opcua_structure_t.h"
#include "opcua_string_t.h"
#include "opcua_data_value_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief WriteValue_t
 *
 * This class implements the Write value data type
 *
 */
class WriteValue_t : public Structure_t
{
private:

  /*****************************************************************************/
  /* @var IntrusivePtr_t<NodeId_t> nodeId
   * An intrusive reference counting Boost-style smart pointer to the node ID
   */
  IntrusivePtr_t<NodeId_t>      nodeId;

  /*****************************************************************************/
  /* @var IntegerId_t attributeId
   * Attribute ID
   */
  IntegerId_t                   attributeId;

  /*****************************************************************************/
  /* @var String_t indexRange
   * Index Range
   */
  String_t                      indexRange;

  /*****************************************************************************/
  /* @var IntrusivePtr_t<DataValue_t> dataValue
   * Data Value
   */
  IntrusivePtr_t<DataValue_t>   dataValue;

public:
  UA_DECLARE_RUNTIME_TYPE(WriteValue_t);

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_WriteValue;

  /*****************************************************************************/
  /** Constructor for the class.
   *
   */
  WriteValue_t();

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~WriteValue_t();

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
   * @param[in] WriteValue_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  bool operator==(WriteValue_t const & obj) const;

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
   * @param[in] WriteValue_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS WriteValue_t object is greater than RHS WriteValue_t object
   */
  bool operator>(WriteValue_t const & obj) const;

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
   * @param[in] const WriteValue_t& source
   *  write value source to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const WriteValue_t& source);

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
  /** Get the Node ID.
   *
   * @return
   * Returns the node id. An intrusive reference counting Boost-style
   * smart pointer to the node id. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const NodeId_t> NodeId(void) const;

  /*****************************************************************************/
  /** Get the Node ID.
   *
   * @return
   * Returns the node id. An intrusive reference counting Boost-style
   * smart pointer to the node id. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<NodeId_t>& NodeId(void);

  /*****************************************************************************/
  /** Get the target attribute id
   *
   * @return
   * Returns the attribute id
   */
  const IntegerId_t& AttributeId(void) const;

  /*****************************************************************************/
  /** Get the target attribute id
   *
   * @return
   * Returns the attribute id
   */
  IntegerId_t& AttributeId(void);

  /*****************************************************************************/
  /** Get the index range
   *
   * @return
   * Returns the index range
   */
  const String_t& IndexRange(void) const;

  /*****************************************************************************/
  /** Get the index range
   *
   * @return
   * Returns the index range
   */
  String_t& IndexRange(void);

  /*****************************************************************************/
  /** Get the Data value
   *
   * @return
   * Returns the data value. An intrusive reference counting Boost-style
   * smart pointer to the data value. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const DataValue_t> DataValue(void) const;

  /*****************************************************************************/
  /** Get the Data value
   *
   * @return
   * Returns the data value. An intrusive reference counting Boost-style
   * smart pointer to the data value. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<DataValue_t>& DataValue(void);

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
   * @param[out] WriteValue_t& result
   * Decoded Write value object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, WriteValue_t& result);
};

/** @} */

} // namespace uasdk
#endif // _OPCUA_WRITE_VALUE_T_
