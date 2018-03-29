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

#ifndef _OPCUA_USERNAME_IDENTITY_TOKEN_T_
#define _OPCUA_USERNAME_IDENTITY_TOKEN_T_

#include "opcua_structure_t.h"
#include "opcua_string_t.h"
#include "opcua_bytestring_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief UsernameIdentityToken_t
 *
 * This class implements the User Name Identity Token data type
 *
 */
class UsernameIdentityToken_t : public Structure_t
{
private:
  /*****************************************************************************/
  /* @var String_t policyId
   *  Policy Id
   */
  String_t     policyId;

  /*****************************************************************************/
  /* @var String_t username
   *  User name
   */
  String_t     username;

  /*****************************************************************************/
  /* @var String_t password
   *  Password
   */
  ByteString_t password;

  /*****************************************************************************/
  /* @var String_t encryptionAlgorithm
   *  Encryption Algorithm
   */
  String_t     encryptionAlgorithm;

public:
  UA_DECLARE_RUNTIME_TYPE(UsernameIdentityToken_t);

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_UserNameIdentityToken;

  /*****************************************************************************/
  /** Constructor for the class.
   *
   */
  
  UsernameIdentityToken_t();

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~UsernameIdentityToken_t();

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
  bool operator==(UsernameIdentityToken_t const & obj) const;

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
   * @param[in] UsernameIdentityToken_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS UsernameIdentityToken_t object is greater than RHS UsernameIdentityToken_t object
   */
  bool operator>(UsernameIdentityToken_t const & obj) const;

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
   * @param[in] const UsernameIdentityToken_t& source
   * User Name Identity Token source object to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const UsernameIdentityToken_t& source);

  /*****************************************************************************/
  /** Copy from the source
   *
   * @param[in] const UsernameIdentityToken_t& source
   * User Name Identity Token source object to copy from
   *
   * @param[in] const String_t& indexRange
   * Index rage to copy from
   *
   * @return
   * Status of the operation
   */
  virtual Status_t CopyFrom(const UsernameIdentityToken_t& source, const String_t& indexRange);

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
  /** Get the Policy Id
   *
   * @return
   * Returns the Policy Id
   */
  const String_t& PolicyId(void) const;

  /*****************************************************************************/
  /** Get the Policy Id
   *
   * @return
   * Returns the Policy Id
   */
  String_t& PolicyId(void);

  /*****************************************************************************/
  /** Get the User name
   *
   * @return
   * Returns the User name
   */
  const String_t& Username(void) const;

  /*****************************************************************************/
  /** Get the User name
   *
   * @return
   * Returns the User name
   */
  String_t& Username(void);

  /*****************************************************************************/
  /** Get the Password
   *
   * @return
   * Returns the Password
   */
  const ByteString_t& Password(void) const;

  /*****************************************************************************/
  /** Get the Password
   *
   * @return
   * Returns the Password
   */
  ByteString_t& Password(void);

  /*****************************************************************************/
  /** Get the Encryption Algorithm
   *
   * @return
   * Returns the Encryption Algorithm
   */
  const String_t& EncryptionAlgorithm(void) const;

  /*****************************************************************************/
  /** Get the Encryption Algorithm
   *
   * @return
   * Returns the Encryption Algorithm
   */
  String_t& EncryptionAlgorithm(void);

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
   * @param[out] UsernameIdentityToken_t& result
   * Decoded User Name Identity Token object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, UsernameIdentityToken_t& result);
};

/** @} */

} // namespace uasdk
#endif // _OPCUA_USERNAME_IDENTITY_TOKEN_T_
