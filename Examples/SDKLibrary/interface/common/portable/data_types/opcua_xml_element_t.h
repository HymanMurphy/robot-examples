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

#ifndef _OPCUA_XML_ELEMENT_T_
#define _OPCUA_XML_ELEMENT_T_

#include "opcua_bytestring_t.h"

namespace uasdk
{

class UABinaryCodec_t;

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief XmlElement_t
 *
 * This class implements the XML Element data type
 */
class XmlElement_t : public BaseDataType_t
{
  friend class UABinaryCodec_t;

private:

  /*****************************************************************************/
  /* @var ByteString_t byteString
   * Byte String object
   */
  ByteString_t byteString;

  XmlElement_t& operator=(XmlElement_t const &);
  XmlElement_t(XmlElement_t const &);

public:
  UA_DECLARE_RUNTIME_TYPE(XmlElement_t);

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_XmlElement;

  /*****************************************************************************/
  /** Constructor for the class.
   *
   */
  XmlElement_t();

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~XmlElement_t();

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
   * @param[in] const XmlElement_t& obj
   * Object to be assigned
   *
   * @return
   * Reference to the Xml Element object assigned
   */
  bool operator==(XmlElement_t const & obj) const;

  /*****************************************************************************/
  /**!= operator overloading
   *
   * @param[in] const XmlElement_t& obj
   * Object to be assigned
   *
   * @return
   * Reference to the Xml Element object assigned
   */

  bool operator!=(XmlElement_t const & obj) const;

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
   * @param[in] XmlElement_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS XmlElement_t object is greater than RHS MonItemModifyResult_t object
   */
  bool operator>(XmlElement_t const & obj) const;

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
   * @param[in] const XmlElement_t& source
   *  Xml Element source to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const XmlElement_t& source);

  /*****************************************************************************/
  /** Copy specified length from the source
   *
   * @param[in] const char* source
   * const char to copy from
   *
   * @param[in] uint32_t maxLen
   * length of the string to copy
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const char* source, uint32_t maxLen);

  /*****************************************************************************/
  /** write subset to destination
   *
   * @param[in] IndexRange_t indexRange
   * index range.
   *
   * @param[in] BaseDataType_t destination
   * data written to destination.
   *
   * @return
   * Status of the operation
   */
  virtual Status_t WriteSubsetTo(const Array_t<IndexRange_t>& indexRange, IntrusivePtr_t<BaseDataType_t>& destination) const;

  /*****************************************************************************/
  /** write subset from source
   *
   * @param[in] IndexRange_t indexRange
   * index range.
   *
   * @param[in] BaseDataType_t source
   * data writting from source.
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
  /** Get the length value
   *
   * @return
   * Returns integer length.
   */
  int32_t Length(void) const;

  /*****************************************************************************/
  /** Get the payload.
   *
   * @return
   * Returns payload.
   */
  const ByteString_t& Payload(void) const;

  /*****************************************************************************/
  /** Get the payload.
   *
   * @return
   * Returns payload.
   */
  ByteString_t& Payload(void);

  /*****************************************************************************/
  /** Checks the string for Null
   *
   * @return
   * Returns true if null
   */
  bool IsNull(void) const;

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
   * @param[out] XmlElement_t& result
   * Decoded XML Element object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, XmlElement_t& result);
};

/** @} */

} // namespace uasdk
#endif // _OPCUA_XML_ELEMENT_T_
