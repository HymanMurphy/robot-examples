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

#ifndef _OPCUA_BYTESTRING_T_
#define _OPCUA_BYTESTRING_T_

#include "opcua_identifiers.h"
#include "opcua_base_data_type_t.h"
#include "uasdk_includes.h"
#include "scoped_ptr_t.h"
#include "array_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief ArrayUA_t
 *
 * This class implements the Byte String data type
 *
 */
class ByteString_t : public BaseDataType_t
{
public: 
  UA_DECLARE_RUNTIME_TYPE(ByteString_t);
private:

  /*****************************************************************************/
  /* @var Array_t<uint8_t> data
   * Charector Array to store the string
   */
  Array_t<uint8_t> data;

  ByteString_t& operator=(ByteString_t const &);
  ByteString_t(ByteString_t const &);

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_ByteString;

  /*****************************************************************************/
  /** Default constructor for the class.
   *
   */
  ByteString_t();

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~ByteString_t();

  /*****************************************************************************/
  /** Initialize the byte string
   *
   * @param[in] uint32_t length
   * Length of an byte string
   *
   */
  Status_t Initialise(int32_t length);

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
   * @param[in] ByteString_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the object's byte strings are same
   * False - If the both the object's byte strings are not same
   */
  bool operator==(ByteString_t const & obj) const;

  /*****************************************************************************/
  /** != operator overloading
   *
   * @param[in] ByteString_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the object's byte strings are not same
   * False - If the both the object's byte strings are same
   */
  bool operator!=(ByteString_t const & obj) const;

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
   * @param[in] ByteString_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the first byte that does not match
   * in both the array members have a greater value in lhs than in rhs as if evaluated
   * as unsigned char values; And a value of false indicates the opposite.
   */
  bool operator>(ByteString_t const & obj) const;

  /*****************************************************************************/
  /** Copy to the destination
   *
   * @param[in] IntrusivePtr_t<BaseDataType_t>& destination
   * Destination data type
   *
   * @return
   * Status of the operation
   */
  virtual Status_t CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const;

  /*****************************************************************************/
  /** Copy from the source
   *
   * @param[in] const uint8_t* source
   * Pointer to the source charector array
   *
   * @param[in] int32_t length
   * Length of the data
   *
   * @return
   * Status of the operation
   */
  virtual Status_t CopyFrom(const uint8_t* source, int32_t length);

  /*****************************************************************************/
  /** Copy from the byte Array
   *
   * @param[in] const BaseDataType_t& source
   * Source data type
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFromByteArray(const BaseDataType_t& source);

  /*****************************************************************************/
  /** Copy from the source
   *
   * @param[in] const BaseDataType_t& source
   * Source data type
   *
   * @param[in] uint32_t start
   * Starting index of an array
   *
   * @param[in] uint32_t end
   * Ending index of an array
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFromByteArray(const BaseDataType_t& source, uint32_t start, uint32_t end);

  /*****************************************************************************/
  /** Copy from the source
   *
   * @param[in] const ByteString_t& source
   *  Source Byte String to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const ByteString_t& source);

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
  /** Write the subset of array elements to destination array
   *
   * @param[in] const Array_t<IndexRange_t>& indexRanges
   *  Array index range to copy the data from
   *
   * @param[in] IntrusivePtr_t<BaseDataType_t>& destination
   *  Destination array
   *
   * @return
   * Status of the operation
   */
  virtual Status_t WriteSubsetTo(const Array_t<IndexRange_t>& indexRange, IntrusivePtr_t<BaseDataType_t>& destination) const;

  /*****************************************************************************/
  /** Write the subset of array elements from the source array
   *
   * @param[in] const Array_t<IndexRange_t>& indexRanges
   *  Array index range
   *
   * @param[in] const BaseDataType_t& source
   *  Source array
   *
   * @return
   * Status of the operation
   */
  virtual Status_t WriteSubsetFrom(const Array_t<IndexRange_t>& indexRange, const BaseDataType_t& source);

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
  /** Get the length of the byte string
   *
   * @return
   * Returns the length of the byte string
   */
  int32_t Length(void) const;

  /*****************************************************************************/
  /** Get the byte string data
   *
   * @return
   * Returns the pointer to the byte string data
   */
  const uint8_t* Data(void) const;

  /*****************************************************************************/
  /** Get the byte string data
   *
   * @return
   * Returns the pointer to the byte string data
   */
  uint8_t* Data(void);

  /*****************************************************************************/
  /** Check if the byte string is null or not
   *
   * @return
   * True - If the byte string has no element and stores null
   * False - If the byte string is not null
   */
  bool IsNull(void) const;

  /*****************************************************************************/
  /** Convert to legacy byte string object
   *
   * @return
   * Legacy byte string object
   */
  const UA_Byte_string_t ToLegacy(void) const;

  /*****************************************************************************/
  /** Convert to legacy byte string object
   *
   * @return
   * Legacy byte string object
   */
  UA_Byte_string_t ToLegacy(void);

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
  virtual Status_t Encode(ICodec_t& encoder, IBuffer_t& buffer) const;

  /*****************************************************************************/
  /** Decode the buffer
   *
   * @param[in] const IBuffer_t& buffer
   * Decode buffer
   *
   * @param[in] ICodec_t& decoder
   * Reference to the decoder object
   *
   * @param[out] ByteString_t& result
   * Decoded byte string object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, ByteString_t& result);

};

/** @} */

} // namespace uasdk
#endif // _OPCUA_BYTESTRING_T_
