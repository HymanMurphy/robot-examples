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

#ifndef _OPCUA_UINT32_T_
#define _OPCUA_UINT32_T_


#include "opcua_number_t.h"
#include "opcua_identifiers.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief UInt32_t
 *
 * This class implements the UInt32_t data type
 *
 */
class UInt32_t : public Number_t<uint32_t>
{
public:
  UA_DECLARE_RUNTIME_TYPE(UInt32_t);

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_UInt32;

  /*****************************************************************************/
  /** Default constructor for the class.
   *
   */
  UInt32_t();

  /*****************************************************************************/
  /** constructor for the class.
   *
   * @param[in] uint32_t val
   * Value to be assigned
   *
   */
  UInt32_t(uint32_t val);

  /*****************************************************************************/
  /** Copy constructor for the class.
   *
   */
  UInt32_t(UInt32_t const & other);

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~UInt32_t();

  /*****************************************************************************/
  /** = operator overloading
   *
   * @param[in] const UInt32_t& obj
   * Object to be assigned
   *
   * @return
   * Reference to the UInt32_t object assigned
   */
  UInt32_t& operator=(UInt32_t const & obj);

  /*****************************************************************************/
  /** = operator overloading
   *
   * @param[in] uint32_t const & obj
   * uint32_t value to be assigned
   *
   * @return
   * Reference to the uint32_t object assigned
   */
  UInt32_t& operator=(uint32_t const & obj);

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
   * @param[in] const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  bool operator==(UInt32_t const & obj) const;

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
   * @param[in] UInt32_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS UInt32_t object is greater than RHS UInt32_t object
   */
  bool operator>(UInt32_t const & obj) const;

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
   * @param[in] const UInt32_t& source
   *  UInt32_t source to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const UInt32_t& source);

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
   * @param[out] UInt32_t& result
   * Decoded UInt32_t object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, UInt32_t& result);

};

typedef UInt32_t IntegerId_t;
typedef UInt32_t Counter_t;

/** @} */

} // namespace uasdk
#endif // _OPCUA_UINT32_T_
