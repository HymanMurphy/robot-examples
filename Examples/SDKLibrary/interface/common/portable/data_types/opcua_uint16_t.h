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

#ifndef _OPCUA_UINT16_T_
#define _OPCUA_UINT16_T_

#include "opcua_number_t.h"
#include "opcua_identifiers.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief SByte_t
 *
 * This class implements the UInt16_t data type
 *
 */
class UInt16_t : public Number_t<uint16_t>
{
public:
  UA_DECLARE_RUNTIME_TYPE(UInt16_t);

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_UInt16;

  /*****************************************************************************/
  /** Default Constructor for the class.
   *
   */
  UInt16_t();

  /*****************************************************************************/
  /** Constructor for the class.
   *
   * @param[in] uint16_t val
   * Value to be set
   */
  UInt16_t(uint16_t val);

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~UInt16_t();

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
  /** = operator overloading
   *
   * @param[in] UInt16_t const & obj
   * Object to be compared with
   *
   * @return
   * Reference to the UInt16_t object to be assigned
   */
  UInt16_t& operator=(UInt16_t const & obj);

  /*****************************************************************************/
  /** = operator overloading
   *
   * @param[in] uint16_t const & obj
   * Object to be compared with
   *
   * @return
   * Reference to the UInt16_t object to be assigned
   */
  UInt16_t& operator=(uint16_t const & obj);

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
   * @param[in] UInt16_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  bool operator==(UInt16_t const & obj) const;

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
   * @param[in] Float_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS Float_t object is greater than RHS Float_t object
   */
  bool operator>(UInt16_t const & obj) const;

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
   *  Float_t source to copy from
   *
   * @return
   * Status of the operation
   */
  virtual Status_t CopyFrom(const BaseDataType_t& source);

  /*****************************************************************************/
  /** Copy from the source
   *
   * @param[in] const UInt16_t& source
   * Source data type
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const UInt16_t& source);

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
   * @param[out] UInt16_t& result
   * Decoded UInt16_t object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, UInt16_t& result);

};

/** @} */

} // namespace uasdk
#endif // _OPCUA_UINT16_T_
