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

#ifndef _OPCUA_ARGUMENT_T_
#define _OPCUA_ARGUMENT_T_

#include "opcua_structure_t.h"
#include "opcua_node_id_t.h"
#include "opcua_string_t.h"
#include "opcua_int32_t.h"
#include "opcua_uint32_t.h"
#include "opcua_array_ua_t.h"
#include "opcua_localized_text_t.h"

#if (UASDK_INCLUDE_METHOD_SERVICE_SET > 0)

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief Argument_t
 *
 * This class implements the Argument  data type
 *
 */
class Argument_t : public Structure_t

{
public:
  UA_DECLARE_RUNTIME_TYPE(Argument_t);

private:

  /*****************************************************************************/
  /* @var String_t name
   * Argument Name
   */
  String_t                      name;

  /*****************************************************************************/
  /* @var IntrusivePtr_t<NodeId_t> dataType;
   * Argument data type
   */
  IntrusivePtr_t<NodeId_t>      dataType;

  /*****************************************************************************/
  /* @var Int32_t valueRank
   * value Rank
   */
  Int32_t                       valueRank;

  /*****************************************************************************/
  /* @var ArrayUA_t<UInt32_t> arrayDimensions
   * Array Dimensions
   */
  ArrayUA_t<UInt32_t>           arrayDimensions;

  /*****************************************************************************/
  /* @var String_t LocalizedText_t description
   * Argument Description
   */
  LocalizedText_t               description;

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_Argument;

  /*****************************************************************************/
  /** Default constructor for the class.
   *
   */
  Argument_t();

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~Argument_t();

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
   * @param[in] Argument_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  bool operator==(Argument_t const & obj) const;

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
   * @param[in] AnonymousIdentityToken_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the first byte that does not match
   * in both the class member variables have a greater value in lhs than in rhs as if evaluated
   * as unsigned char values; And a value of false indicates the opposite.
   */
  bool operator>(Argument_t const & obj) const;

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
   * @param[in] const Argument_t& source
   *  Argument source to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const Argument_t& source);

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
  /** Get the argument Name
   *
   * @return
   * Returns the argument Name
   */
  const String_t& Name(void) const;

  /*****************************************************************************/
  /** Get the argument Name
   *
   * @return
   * Returns the argument Name
   */
  String_t& Name(void);

  /*****************************************************************************/
  /** Get the Data Type
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node id. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const NodeId_t> DataType(void) const;

  /*****************************************************************************/
  /** Get the data type
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node id. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<NodeId_t>& DataType(void);

  /*****************************************************************************/
  /** Get the argument Value Rank
   *
   * @return
   * Returns the argument Value Rank
   */
  const Int32_t& ValueRank(void) const;

  /*****************************************************************************/
  /** Get the argument Value Rank
   *
   * @return
   * Returns the argument Value Rank
   */
  Int32_t& ValueRank(void);

  /*****************************************************************************/
  /** Get the Array Dimensions
   *
   * @return
   * Returns the Array Dimensions
   */
  const ArrayUA_t<UInt32_t>& ArrayDimensions(void) const;

  /*****************************************************************************/
  /** Get the Array Dimensions
   *
   * @return
   * Returns the Array Dimensions
   */
  ArrayUA_t<UInt32_t>& ArrayDimensions(void);

  /*****************************************************************************/
  /** Get the argument Description
   *
   * @return
   * Returns the argument Description
   */
  const LocalizedText_t& Description(void) const;

  /*****************************************************************************/
  /** Get the argument Description
   *
   * @return
   * Returns the argument Description
   */
  LocalizedText_t& Description(void);

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
   * @param[out] Argument_t& result
   * Decoded argument object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, Argument_t& result);

};

/** @} */

} // namespace uasdk

#endif

#endif // _OPCUA_ARGUMENT_T_
