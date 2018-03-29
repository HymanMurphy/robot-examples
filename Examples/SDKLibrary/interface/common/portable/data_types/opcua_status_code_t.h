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

#ifndef _OPCUA_STATUS_CODE_T_
#define _OPCUA_STATUS_CODE_T_

#include "opcua_uint32_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief ServerState_t
 *
 * This class implements the status code data type
 *
 */
class StatusCode_t : public BaseDataType_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(StatusCode_t);
private:

  /*****************************************************************************/
  /* @var UInt32_t value
   *  Status code
   */
  UInt32_t value;

  /*****************************************************************************/
  /** Constructor for the class.
   *
   */
  StatusCode_t(StatusCode_t const &);

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_StatusCode;

  /*****************************************************************************/
  /** Constructor for the class.
   *
   */
  StatusCode_t();

  /*****************************************************************************/
  /** Constructor for the class.
   *
   * @param[in] uint32_t val
   * Status code value to be assigned
   */
  StatusCode_t(uint32_t val);

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~StatusCode_t();

  /*****************************************************************************/
  /** = operator overloading
   *
   * @param[in] StatusCode_t const & obj
   * Object to be assigned
   *
   * @return
   * Reference to the status code object assigned
   */
  StatusCode_t& operator=(StatusCode_t const & obj);

  /*****************************************************************************/
  /** = operator overloading
   *
   * @param[in] Status_t const & obj
   * Object to be assigned
   *
   * @return
   * Reference to the Status_t object assigned
   */
  StatusCode_t& operator=(Status_t const & obj);

  /*****************************************************************************/
  /** = operator overloading
   *
   * @param[in] UInt32_t const & obj
   * Object to be assigned
   *
   * @return
   * Reference to the UInt32_t object assigned
   */
  StatusCode_t& operator=(UInt32_t const & value_);

  /*****************************************************************************/
  /** = operator overloading
   *
   * @param[in] uint32_t const & obj
   * uint32_t value to be assigned
   *
   * @return
   * Reference to the uint32_t value assigned
   */
  StatusCode_t& operator=(uint32_t const & value_);

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
   * @param[in] const StatusCode_t& obj
   * Object to be assigned
   *
   * @return
   * Reference to the Status code object assigned
   */
  bool operator==(StatusCode_t const & obj) const;
  
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
   * @param[in] ServerState_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS ServerState_t object is greater than RHS ServerState_t object
   */
  bool operator>(StatusCode_t const & obj) const;

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
   * @param[in] const StatusCode_t& source
   * Status Code source object to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const StatusCode_t& source);

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
  /** Get the Status code value
   *
   * @return
   * Returns the Status code value
   */
  const UInt32_t& Value(void) const;

  /*****************************************************************************/
  /** Get the Status code value
   *
   * @return
   * Returns the Status code value
   */
  UInt32_t& Value(void);

  /*****************************************************************************/
  /** Get the Status code value as a status object
   *
   * @return
   * Returns the Status code value as a status object
   */
  Status_t ValueAsStatus(void) const;

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
   * @param[out] StatusCode_t& result
   * Decoded Status Code object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, StatusCode_t& result);
};

/** @} */

} // namespace uasdk
#endif // _OPCUA_STATUS_CODE_T_
