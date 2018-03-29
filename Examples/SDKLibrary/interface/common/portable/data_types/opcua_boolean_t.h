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

#ifndef _OPCUA_BOOLEAN_T_
#define _OPCUA_BOOLEAN_T_

#include "opcua_identifiers.h"
#include "opcua_base_data_type_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief Boolean_t
 *
 * This class implements the boolean  data type
 *
 */
class Boolean_t : public BaseDataType_t
{

public:
  UA_DECLARE_RUNTIME_TYPE(Boolean_t);

private:

  /*****************************************************************************/
  /* @var bool value
   * Boolean value
   */
  bool value;

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_Boolean;

  /*****************************************************************************/
  /** Default constructor for the class.
   *
   */
  Boolean_t();

  /*****************************************************************************/
  /** constructor for the class.
   *
   * @param[in] bool value_
   * Boolean value
   *
   */
  Boolean_t(bool value_);

  /*****************************************************************************/
  /** Copy constructor
   *
   * @param[in] Boolean_t const & other
   * Object to be copied from
   */
  Boolean_t(const Boolean_t& other);

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~Boolean_t();

  /*****************************************************************************/
  /** = operator overloading
   *
   * @param[in] const Boolean_t& obj
   * Object to be assigned
   *
   * @return
   * Reference to the Boolean object assigned
   */
  Boolean_t& operator =(const Boolean_t& obj);

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
   * @param[in] Boolean_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  bool operator==(Boolean_t const & obj) const;

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
   * @param[in] Boolean_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS Boolean_t object is greater than RHS Boolean_t object
   */
  bool operator>(Boolean_t const & obj) const;

  /*****************************************************************************/
  /** Copy to the destination
   *
   * @param[out] IntrusivePtr_t<BaseDataType_t>& destination
   * Destination data type
   *
   * @return
   * Status of the operation
   */
  Status_t CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const;

  /*****************************************************************************/
  /** Copy from the source
   *
   * @param[in] const Boolean_t& source
   *  Boolean_t source to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const Boolean_t& source);

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
  /** Get the boolean value
   *
   * @return
   * Returns the boolean value
   */
  bool Value(void) const;

  /*****************************************************************************/
  /** Get the boolean value
   *
   * @return
   * Returns the boolean value
   */
  Status_t Value(bool val);

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
   * @param[out] Boolean_t& result
   * Decoded Boolean_t object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, Boolean_t& result);

};

/** @} */

} // namespace uasdk
#endif // _OPCUA_BOOLEAN_T_
