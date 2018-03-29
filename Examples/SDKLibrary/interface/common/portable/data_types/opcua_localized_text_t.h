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

#ifndef _OPCUA_LOCALIZED_TEXT_T_
#define _OPCUA_LOCALIZED_TEXT_T_

#include "opcua_string_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief LocalizedText_t
 *
 * This class implements the Localized Text data type
 *
 */
class LocalizedText_t : public BaseDataType_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(LocalizedText_t); 
private:

  /*****************************************************************************/
  /* @var String_t locale
   * Locale
   */
	String_t locale;

  /*****************************************************************************/
  /* @var String_t text
   * Text
   */
  String_t text;

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_LocalizedText;

  /*****************************************************************************/
  /** Default constructor for the class.
   *
   */
  LocalizedText_t();
//  LocalizedText_t(const char* locale_, const UA_UTF8_string_t& text_) : locale(locale_), text(text_) {}
//  LocalizedText_t(const char* locale_, const char* text_) : locale(locale_), text(text_) {}

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~LocalizedText_t();


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
   * @param[in] LocalizedText_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  bool operator==(LocalizedText_t const & obj) const;

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
   * @param[in] LocalizedText_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS LocalizedText_t object is greater than RHS LocalizedText_t object
   */
  bool operator>(LocalizedText_t const & obj) const;

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
   * @param[in] const LocalizedText_t& source
   *  LocalizedText_t source to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const LocalizedText_t& source);

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
   * Name space index
   *
   * @return
   * Returns the Type ID
   */
  virtual uint32_t TypeId(uint16_t& namespaceIndex) const;

  /*****************************************************************************/
  /** Get the Locale value
   *
   * @return
   * Returns the Locale value
   */
  const String_t& Locale(void) const;

  /*****************************************************************************/
  /** Get the Locale value
   *
   * @return
   * Returns the Locale value
   */
  String_t& Locale(void);

  /*****************************************************************************/
  /** Get the Text
   *
   * @return
   * Returns the Text
   */
  const String_t& Text(void) const;

  /*****************************************************************************/
  /** Get the Text
   *
   * @return
   * Returns the Text
   */
  String_t& Text(void);

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
   * @param[out] LocalizedText_t& result
   * Decoded LocalizedText_t object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, LocalizedText_t& result);
};

/** @} */

} // namespace uasdk
#endif // _OPCUA_LOCALIZED_TEXT_T_
