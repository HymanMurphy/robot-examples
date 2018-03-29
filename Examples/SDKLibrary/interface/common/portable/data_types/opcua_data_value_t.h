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

#ifndef _OPCUA_DATA_VALUE_T_
#define _OPCUA_DATA_VALUE_T_

#include "opcua_date_time_t.h"
#include "intrusive_ptr_t.h"
#include "opcua_uint16_t.h"
#include "opcua_status_code_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief DataValue_t
 *
 * This class implements Data value data type
 *
 */
class DataValue_t : public BaseDataType_t
{

public:
  UA_DECLARE_RUNTIME_TYPE(DataValue_t);
private:

  /*****************************************************************************/
  /* @var IntrusivePtr_t<BaseDataType_t> value
   * An intrusive reference counting Boost-style smart pointer to the value.
   */
  IntrusivePtr_t<BaseDataType_t>  value;

  /*****************************************************************************/
  /* @var IntrusivePtr_t<StatusCode_t> statusCode
   * An intrusive reference counting Boost-style smart pointer to the status code.
   */
  IntrusivePtr_t<StatusCode_t>    statusCode;

  /*****************************************************************************/
  /* @var IntrusivePtr_t<DateTime_t> sourceTimestamp
   * An intrusive reference counting Boost-style smart pointer to the source time stamp.
   */
  IntrusivePtr_t<DateTime_t>      sourceTimestamp;

  /*****************************************************************************/
  /* @var IntrusivePtr_t<DateTime_t> serverTimestamp
   * An intrusive reference counting Boost-style smart pointer to the server time stamp.
   */
  IntrusivePtr_t<DateTime_t>      serverTimestamp;

  /*****************************************************************************/
  /* @var IntrusivePtr_t<UInt16_t> sourcePicoseconds
   * An intrusive reference counting Boost-style smart pointer to the source pico seconds.
   */
  IntrusivePtr_t<UInt16_t>        sourcePicoseconds;

  /*****************************************************************************/
  /* @var IntrusivePtr_t<UInt16_t> serverPicoseconds
   * An intrusive reference counting Boost-style smart pointer to the server pico seconds.
   */
  IntrusivePtr_t<UInt16_t>        serverPicoseconds;

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_DataValue;

  /*****************************************************************************/
  /** constructor for the class.
   *
   */
  DataValue_t();

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~DataValue_t();

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
   * @param[in] const DataValue_t& obj
   * Object to be assigned
   *
   * @return
   * Reference to the DataValue_t object assigned
   */
  bool operator==(DataValue_t const & obj) const;

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
   * @param[in] DataValue_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS DataValue_t object is greater than RHS DataValue_t object
   */
  bool operator>(DataValue_t const & obj) const;

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
  /** Copy from the source
   *
   * @param[in] const DataValue_t& source
   *  Call Method Request source to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const DataValue_t& source);

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
  /** Get the data value.
   *
   * @return
   * Returns the data value. An intrusive reference counting Boost-style
   * smart pointer to the data value. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const BaseDataType_t> Value(void) const;

  /*****************************************************************************/
  /** Get the data value.
   *
   * @return
   * Returns the data value. An intrusive reference counting Boost-style
   * smart pointer to the data value. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<BaseDataType_t>& Value(void);

  /*****************************************************************************/
  /** Get the status code
   *
   * @return
   * Returns the status code. An intrusive reference counting Boost-style
   * smart pointer to the status code . The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const StatusCode_t> StatusCode(void) const;

  /*****************************************************************************/
  /** Get the status code
   *
   * @return
   * Returns the status code. An intrusive reference counting Boost-style
   * smart pointer to the status code . The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<StatusCode_t>& StatusCode(void);

  /*****************************************************************************/
  /** Get the source time stamp
   *
   * @return
   * Returns the Source Time stamp. An intrusive reference counting Boost-style
   * smart pointer to the source time stamp. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const DateTime_t> SourceTimestamp(void) const;

  /*****************************************************************************/
  /** Get the source time stamp
   *
   * @return
   * Returns the Source Time stamp. An intrusive reference counting Boost-style
   * smart pointer to the source time stamp. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<DateTime_t>& SourceTimestamp(void);

  /*****************************************************************************/
  /** Get the Source Pico seconds
   *
   * @return
   * Returns the Source Pico seconds. An intrusive reference counting Boost-style
   * smart pointer to the Source Pico seconds. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const UInt16_t> SourcePicoseconds(void) const;

  /*****************************************************************************/
  /** Get the Source Pico seconds
   *
   * @return
   * Returns the Source Pico seconds. An intrusive reference counting Boost-style
   * smart pointer to the Source Pico seconds. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<UInt16_t>& SourcePicoseconds(void);

  /*****************************************************************************/
  /** Get the Server Time stamp
   *
   * @return
   * Returns the Server Time stamp. An intrusive reference counting Boost-style
   * smart pointer to the Server Time stamp. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const DateTime_t> ServerTimestamp() const;

  /*****************************************************************************/
  /** Get the Server Time stamp
   *
   * @return
   * Returns the Server Time stamp. An intrusive reference counting Boost-style
   * smart pointer to the Server Time stamp. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<DateTime_t>& ServerTimestamp();

  /*****************************************************************************/
  /** Get the Server Pico seconds
   *
   * @return
   * Returns the Server Pico seconds. An intrusive reference counting Boost-style
   * smart pointer to the Server Pico seconds. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<const UInt16_t> ServerPicoseconds(void) const;

  /*****************************************************************************/
  /** Get the Server Pico seconds
   *
   * @return
   * Returns the Server Pico seconds. An intrusive reference counting Boost-style
   * smart pointer to the Server Pico seconds. The caller must test the pointer before dereferencing it.
   */
  IntrusivePtr_t<UInt16_t>& ServerPicoseconds(void);

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
   * @param[out] DataValue_t& result
   * Decoded data value object object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, DataValue_t& result);
};

/** @} */

} // namespace uasdk
#endif // _OPCUA_DATA_VALUE_T_
