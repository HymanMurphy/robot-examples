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

#ifndef _OPCUA_SIGNATURE_DATA_T_
#define _OPCUA_SIGNATURE_DATA_T_

#include "opcua_structure_t.h"
#include "opcua_bytestring_t.h"
#include "opcua_string_t.h"

namespace uasdk
{
/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief Range_t
 *
 * This class implements the Rage data type
 *
 */
class SignatureData_t : public Structure_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(SignatureData_t);
private:

  /*****************************************************************************/
  /* @var String_t algorithm
   * Algorithm
   */
  String_t     algorithm;

  /*****************************************************************************/
  /* @var ByteString_t signature
   * Signature
   */
  ByteString_t signature;

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_SignatureData;

  /*****************************************************************************/
  /** Default constructor for the class.
   *
   */
  SignatureData_t();

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~SignatureData_t();

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
   * @param[in] SignatureData_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  bool operator==(SignatureData_t const & obj) const;

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
   * @param[in] SignatureData_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS SignatureData_t object is greater than RHS SignatureData_t object
   */
  bool operator>(SignatureData_t const & obj) const;

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
   * @param[in] const SignatureData_t& source
   *  Signature Data source object to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const SignatureData_t& source);

  /*****************************************************************************/
  /** Copy from the source
   *
   * @param[in] const SignatureData_t& source
   *  Signature Data source object to copy from
   *
   * @param[in] const String_t& indexRange
   *  Index range to copy from
   *
   * @return
   * Status of the operation
   */
  virtual Status_t CopyFrom(const SignatureData_t& source, const String_t& indexRange);

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
  /** Get the Algorithm
   *
   * @return
   * Returns the Algorithm
   */
  const String_t& Algorithm(void) const;

  /*****************************************************************************/
  /** Get the Algorithm
   *
   * @return
   * Returns the Algorithm
   */
  String_t& Algorithm(void);

  /*****************************************************************************/
  /** Get the Signature
   *
   * @return
   * Returns the Signature
   */
  const ByteString_t& Signature(void) const;

  /*****************************************************************************/
  /** Get the Signature
   *
   * @return
   * Returns the Signature
   */
  ByteString_t& Signature(void);

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
   * @param[out] SignatureData_t& result
   * Decoded Signature Data object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, SignatureData_t& result);
};

/** @} */

} // namespace uasdk
#endif // _OPCUA_SIGNATURE_DATA_T_
