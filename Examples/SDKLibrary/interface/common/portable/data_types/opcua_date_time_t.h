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

#ifndef _OPCUA_DATE_TIME_T_
#define _OPCUA_DATE_TIME_T_

#include "opcua_int64_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief DataValue_t
 *
 * This class implements Date and time data type
 *
 */
class DateTime_t : public BaseDataType_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(DateTime_t);
private:

  /*****************************************************************************/
  /* @var Int64_t value
   * Date and time value
   */
  Int64_t value;

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_DateTime;

  /*****************************************************************************/
  /** constructor for the class.
   *
   */
  DateTime_t();

  /*****************************************************************************/
  /** constructor for the class.
   *
   * @param[in] int64_t val
   * Date time value to set
   *
   */
  DateTime_t(int64_t val);

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~DateTime_t(void);

  /*****************************************************************************/
  /** = operator overloading
   *
   * @param[in] DateTime_t const & obj
   * Object to be assigned
   *
   * @return
   * Reference to the DateTime_t object
   */
  DateTime_t& operator=(DateTime_t const & obj);

  /*****************************************************************************/
  /** = operator overloading
   *
   * @param[in] Int64_t const & obj
   * Object to be assigned
   *
   * @return
   * Reference to the DateTime_t object
   */
  DateTime_t& operator=(Int64_t const & obj);

  /*****************************************************************************/
  /** = operator overloading
   *
   * @param[in] int64_t const & obj
   * data time value to be assigned
   *
   * @return
   * Reference to the DateTime_t object
   */
  DateTime_t& operator=(int64_t const & obj);

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
   * @param[in] DateTime_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  bool operator==(DateTime_t const & obj) const;

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
   * @param[in] DateTime_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS DateTime_t object is greater than RHS DateTime_t object
   */
  bool operator>(DateTime_t const & obj) const;

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
   * @param[in] const DateTime_t& source
   *  Date and Time source object to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const DateTime_t& source);

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
  /** Get the date and time value.
   *
   * @return
   * Returns the date and time value.
   */
  int64_t Value(void) const;

  /*****************************************************************************/
  /** Set the date and time value.
   */
  void Value(int64_t val);

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
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, DateTime_t& result);
};

typedef DateTime_t UtcTime_t;

/** @} */

} // namespace uasdk
#endif // _OPCUA_DATE_TIME_T_
