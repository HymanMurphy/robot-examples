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

#ifndef _opcua_int16_t_
#define _opcua_int16_t_


#include "opcua_number_t.h"
#include "opcua_identifiers.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief Int16_t
 *
 * This class implements the Int16 data type
 *
 */
class Int16_t : public Number_t<int16_t>
{
public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */

  UA_DECLARE_RUNTIME_TYPE(Int16_t);

  static const uint32_t TYPE_ID = OpcUaId_Int16;

  /*****************************************************************************/
  /** Default constructor for the class.
   *
   */
  Int16_t();

  /*****************************************************************************/
  /** constructor for the class.
   *
   * @param[in] int16_t val
   * Value to be assigned
   *
   */
  Int16_t(int16_t val);

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~Int16_t();

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
  /** = operator overloading
   *
   * @param[in] const Int16_t& obj
   * Object to be assigned
   *
   * @return
   * Reference to the Int16_t object assigned
   */
  Int16_t& operator=(Int16_t const & obj);

  /*****************************************************************************/
  /** = operator overloading
   *
   * @param[in] int16_t const & obj
   * int16_t value to be assigned
   *
   * @return
   * Reference to the int16_t object assigned
   */
  Int16_t& operator=(int16_t const & obj);

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
   * @param[in] Int16_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  bool operator==(Int16_t const & obj) const;

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
   * @param[in] Int16_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS Int16_t object is greater than RHS Int16_t object
   */
  bool operator>(Int16_t const & obj) const;

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
   * @param[in] const Int16_t& source
   *  Int16_t source to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const Int16_t& source);

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
   * @param[out] Int16_t& result
   * Decoded Int16_t object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, Int16_t& result);
};

/** @} */

} // namespace uasdk
#endif // _opcua_int16_t_
