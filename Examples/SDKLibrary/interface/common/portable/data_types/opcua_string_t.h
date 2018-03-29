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

#ifndef _OPCUA_STRING_T_
#define _OPCUA_STRING_T_

#include "opcua_base_data_type_t.h"
#include "opcua_bytestring_t.h"

namespace uasdk
{

class UABinaryCodec_t;

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief ArrayUA_t
 *
 * This class implements the String_t data type
 *
 */
class String_t : public BaseDataType_t
{
private:

  /*****************************************************************************/
  /* @var ByteString_t byteString
   * string object
   */
  ByteString_t byteString;

  String_t& operator=(String_t const &);
  String_t(String_t const &);

public:
  UA_DECLARE_RUNTIME_TYPE(String_t);

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_String;

  /*****************************************************************************/
  /** Default constructor for the class.
   *
   */
  String_t();

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~String_t();

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
   * @param[in] String_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  bool operator==(String_t const & obj) const;

  /*****************************************************************************/
  /** != operator overloading
   *
   * @param[in] String_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  bool operator!=(String_t const & obj) const;

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
   * @param[in] String_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If grater than RHS
   * False - If less than RHS
   */
  bool operator>(String_t const & obj) const;

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
   * @param[in] const String_t& source
   * Source data type
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const String_t& source);

  /*****************************************************************************/
  /** Copy from the source
   *
   * @param[in] const char* source
   * Source data type
   *
   * @param[in] uint32_t maxLen
   * Maximum length to copy
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const char* source, uint32_t maxLen);

  /*****************************************************************************/
  /** Copy from the source
   *
   * @param[in] const char* source
   * Source data type
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const char* source);


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
  /** Get the Length of the string
   *
   * @return
   * Returns the Length of the string
   */
  int32_t Length(void) const;


  /*****************************************************************************/
  /** Get the payload string
   *
   * @return
   * Returns the payload string
   */
  const ByteString_t& Payload(void) const;

  /*****************************************************************************/
  /** Get the payload string
   *
   * @return
   * Returns the payload string
   */
  ByteString_t& Payload(void);

  /*****************************************************************************/
  /** Check if the string is null
   *
   * @return
   * True - If the array elements are number
   * False - If the array elements are not number
   */
  bool IsNull(void) const;

  /*****************************************************************************/
  /** Covert the string into char array
   *
   * @param[out] ScopedPtr_t< Array_t<char> >& result
   * Result char array
   *
   * @return
   * True - If the array elements are number
   * False - If the array elements are not number
   */
  Status_t ToString(ScopedPtr_t< Array_t<char> >& result) const;

  /*****************************************************************************/
  /** Covert to the Legacy UTF string
   *
   * @return
   * returns the UTF string
   *
   */
  UA_UTF8_string_t ToLegacy(void) const;

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
   * @param[out] String_t& result
   * Decoded string object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, String_t& result);
};

Status_t UninitialisedCopy(String_t &destination, String_t const &source);

/** @} */

} // namespace uasdk
#endif // _OPCUA_STRING_T_
