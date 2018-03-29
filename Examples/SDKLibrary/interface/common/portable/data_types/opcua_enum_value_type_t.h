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

#ifndef _OPCUA_ENUM_VALUE_TYPE_T_
#define _OPCUA_ENUM_VALUE_TYPE_T_

#include "opcua_string_t.h"
#include "opcua_localized_text_t.h"
#include "opcua_application_type_t.h"
#include "opcua_array_ua_t.h"

#include "opcua_server_state_t.h"
#include "opcua_date_time_t.h"
#include "opcua_structure_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief Double_t
 *
 * This class implements the enumerated value data type
 *
 */
class EnumValueType_t : public Structure_t
{

public:
  UA_DECLARE_RUNTIME_TYPE(EnumValueType_t);
private:

  /*****************************************************************************/
  /* @var Int64_t value
   * Enumeration Value
   */
  Int64_t           value;

  /*****************************************************************************/
  /* @var LocalizedText_t displayName
   * Enumeration display name
   */
  LocalizedText_t   displayName;

  /*****************************************************************************/
  /* @var LocalizedText_t description
   * Enumeration description
   */
  LocalizedText_t   description;

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_EnumValueType;

  /*****************************************************************************/
  /** Default constructor for the class.
   *
   */
  EnumValueType_t();

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~EnumValueType_t();

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
   * @param[in] EnumValueType_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  bool operator==(EnumValueType_t const & obj) const;

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
   * @param[in] EnumValueType_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS EnumValueType_t object is greater than RHS EnumValueType_t object
   */
  bool operator>(EnumValueType_t const & obj) const;

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
   * @param[in] const EnumValueType_t& source
   *  EnumValueType_t source to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const EnumValueType_t& source);

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
  /** Get the enumeration value
   *
   * @return
   * Returns the enumeration value
   */
  const Int64_t& Value(void) const;

  /*****************************************************************************/
  /** Get the enumeration value
   *
   * @return
   * Returns the enumeration value
   */
  Int64_t& Value(void);

  /*****************************************************************************/
  /** Get the enumeration Display Name
   *
   * @return
   * Returns the enumeration Display Name
   */
  const LocalizedText_t& DisplayName(void) const;

  /*****************************************************************************/
  /** Get the enumeration Display Name
   *
   * @return
   * Returns the enumeration Display Name
   */
  LocalizedText_t& DisplayName(void);

  /*****************************************************************************/
  /** Get the enumeration description
   *
   * @return
   * Returns the enumeration description
   */
  const LocalizedText_t& Description(void) const;
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
   * @param[out] EnumValueType_t& result
   * Decoded EnumValueType_t object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, EnumValueType_t& result);

};

/** @} */

} // namespace uasdk
#endif // _OPCUA_ENUM_VALUE_TYPE_T_
