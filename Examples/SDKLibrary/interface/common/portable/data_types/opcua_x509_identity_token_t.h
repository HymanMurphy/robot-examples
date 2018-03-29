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

#ifndef _OPCUA_X509_IDENTITY_TOKEN_T_
#define _OPCUA_X509_IDENTITY_TOKEN_T_

#include "opcua_structure_t.h"
#include "opcua_string_t.h"
#include "opcua_bytestring_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief X509IdentityToken_t
 *
 * This class implements the X509 Identity Token data type
 */
class X509IdentityToken_t : public Structure_t
{
private:

  /*****************************************************************************/
  /* @var String_t policyId
   * Policy Id
   */
  String_t     policyId;

  /*****************************************************************************/
  /* @var ByteString_t certificateData
   * Certificate Data
   */
  ByteString_t certificateData;

public:
  UA_DECLARE_RUNTIME_TYPE(X509IdentityToken_t);

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_X509IdentityToken;

  /*****************************************************************************/
  /** Constructor for the class.
   *
   */
  X509IdentityToken_t();

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~X509IdentityToken_t();

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
   * @param[in] const X509IdentityToken_t& obj
   * Object to be assigned
   *
   * @return
   * Reference to the X509IdentityToken_t object assigned
   */
  bool operator==(X509IdentityToken_t const & obj) const;

  /*****************************************************************************/
  /**!= operator overloading
   *
   * @param[in] const BaseDataType_t& obj
   * Object to be assigned
   *
   * @return
   * Reference to the BaseDataType_t object assigned
   */

  virtual bool operator>(BaseDataType_t const & obj) const;

  /*****************************************************************************/
  /** > operator overloading
   *
   * @param[in] X509IdentityToken_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If grater than RHS
   * False - If less than RHS
   */
  bool operator>(X509IdentityToken_t const & obj) const;

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
   * @param[in] const X509IdentityToken_t& source
   *  X509IdentityToken_t source to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const X509IdentityToken_t& source);

  /*****************************************************************************/
  /** Copy indes range from the source
   *
   * @param[in] const X509IdentityToken_t& source
   * const char to copy from
   *
   * @param[in] const String_t& indexRange
   * index range
   *
   * @return
   * Status of the operation
   */
  virtual Status_t CopyFrom(const X509IdentityToken_t& source, const String_t& indexRange);

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
  /** Get the Policy ID
   *
   * @return
   * Returns Policy ID object value.
   */
  const String_t& PolicyId(void) const;

  /*****************************************************************************/
  /** Get the Policy ID
   *
   * @return
   * Returns Policy ID object value.
   */
  String_t& PolicyId(void);

  /*****************************************************************************/
  /** Get the Certificate data
   *
   * @return
   * Returns Certificate data
   */
  const ByteString_t& CertificateData(void) const;

  /*****************************************************************************/
  /** Get the certificate.
   *
   * @return
   * Returns ByteString_t object value.
   */
  ByteString_t& CertificateData(void);

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
   * @param[out] X509IdentityToken_t& result
   * X509IdentityToken_t Result object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, X509IdentityToken_t& result);
};

/** @} */

} // namespace uasdk
#endif // _OPCUA_X509_IDENTITY_TOKEN_T_
