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

#ifndef _OPCUA_ARRAY_UA_T_
#define _OPCUA_ARRAY_UA_T_

#include "opcua_array_ua_base_t.h"
#include "intrusive_list_t.h"
#include "intrusive_ptr_t.h"
#include "scoped_ptr_t.h"
#include "array_t.h"
#include "opcua_bytestring_t.h"
#include "opcua_datatype_utilities_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief ArrayUA_t
 *
 * This class implements the Array  data type
 *
 */
template<typename T>
class ArrayUA_t : public ArrayUA_Base_t
{
private:

  /*****************************************************************************/
  /* @var Array_t<IntrusivePtr_t<T> > payload
   * Array to store the payload
   */
  Array_t<IntrusivePtr_t<T> >          payload;

  /*****************************************************************************/
  /* @var IntrusivePtr_t<ArrayUA_t<Int32_t> >  dimensions
   * Array dimnesions
   */
  IntrusivePtr_t<ArrayUA_t<Int32_t> >  dimensions;

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  UA_DEFINE_RUNTIME_TYPE_TMPL(ArrayUA_t, ArrayUA_Base_t);
  
  static const uint32_t TYPE_ID = T::TYPE_ID;

  /*****************************************************************************/
  /** Default constructor for the class.
   *
   */
  ArrayUA_t() {}

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~ArrayUA_t()
  { }

  /*****************************************************************************/
  /** Initialize the array
   *
   * @param[in] uint32_t size
   * Size of an array
   *
   */
  Status_t Initialise(uint32_t size);

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
  virtual bool operator==(BaseDataType_t const & obj) const
  {
    return OperatorEqualTo(*this, obj);
  }

  /*****************************************************************************/
  /** == operator overloading
   *
   * @param[in] ArrayUA_t<T> const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  bool operator==(ArrayUA_t<T> const & obj) const;

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
  virtual bool operator>(BaseDataType_t const & obj) const
  {
    return OperatorGreaterThan(*this, obj);
  }

  /*****************************************************************************/
  /** > operator overloading
   *
   * @param[in] ArrayUA_t<T> const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the first byte that does not match
   * in both the array members have a greater value in lhs than in rhs as if evaluated
   * as unsigned char values; And a value of false indicates the opposite.
   */
  bool operator>(ArrayUA_t<T> const & obj) const;

  /*****************************************************************************/
  /** [] operator overloading
   *
   * @param[in] uint32_t i
   * index of the payload to access
   *
   * @return
   * Returns the payload at index i. An intrusive reference counting Boost-style
   * smart pointer to the node id.
   * The caller must test the pointer before dereferencing it.
   */
  const IntrusivePtr_t<T>& operator[](uint32_t i) const;

  /*****************************************************************************/
  /** [] operator overloading
   *
   * @param[in] uint32_t i
   * index of the payload to access
   *
   * @return
   * Returns the payload at index i. An intrusive reference counting Boost-style
   * smart pointer to the node id.
   * The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<T>& operator[](uint32_t i);

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
  /** Copy from the byte string
   *
   * @param[in] const ByteString_t& source
   * Byte string source to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFromByteString(const ByteString_t& source);

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
   * @param[in] const ArrayUA_t& source
   *  Source array to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const ArrayUA_t<T>& source);

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
  virtual Status_t WriteSubsetTo(const Array_t<IndexRange_t>& indexRanges, IntrusivePtr_t<BaseDataType_t>& destination) const;

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
  virtual Status_t WriteSubsetFrom(const Array_t<IndexRange_t>& indexRanges, const BaseDataType_t& source);

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
  virtual uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const
  {
    namespaceIndex = 0; return OpcUaId_ApplicationDescription_Encoding_DefaultBinary;
  }

  /*****************************************************************************/
  /** Get the Array dimensions
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * array with Int32_t data type. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const ArrayUA_t<Int32_t> > Dimensions(void) const;

  /*****************************************************************************/
  /** Get the Array dimensions
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * array with Int32_t data type. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<ArrayUA_t<Int32_t> >& Dimensions(void);

  /*****************************************************************************/
  /** Encode the buffer as an array of extension objects (if appropriate)
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
  Status_t EncodeExtensionObjects(ICodec_t& encoder, IBuffer_t& buffer) const;

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
   * @param[out] ArrayUA_t& result
   * Decoded array object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, ArrayUA_t& result);

  /*****************************************************************************/
  /** Check if the array stores the number element
   *
   * @return
   * True - If the array elements are number
   * False - If the array elements are not number
   */
  virtual bool IsNumber(void) const;

  /*****************************************************************************/
  /** Get the size of the array
   *
   * @return
   * Size of the array
   */
  virtual uint32_t Size(void) const;

  /*****************************************************************************/
  /** Get the size of the array
   *
   * @return
   * Size of the array
   */
  virtual uint32_t Count(void) const
  {
    return Size();
  }

  /*****************************************************************************/
  /** Get the argument Value Rank
   *
   * @return
   * Returns the argument Value Rank
   */
  virtual int32_t ValueRank(void) const;

  /*****************************************************************************/
  /** Delete all the elements from the array
   *
   */
  void DeleteAll(void);
};

/** @} */

} // namespace uasdk
#endif // _OPCUA_ARRAY_UA_T_
