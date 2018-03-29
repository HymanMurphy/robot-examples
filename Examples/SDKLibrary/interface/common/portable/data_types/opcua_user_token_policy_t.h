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

#ifndef _OPCUA_USER_TOKEN_POLICY_T_
#define _OPCUA_USER_TOKEN_POLICY_T_

#include "opcua_structure_t.h"
#include "opcua_string_t.h"
#include "opcua_user_identity_token_type_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief UserTokenPolicy_t
 *
 * This class implements the User Token Policy data type
 *
 */
class UserTokenPolicy_t : public Structure_t
{
private:
  /*****************************************************************************/
  /* @var String_t policyId
   *  Policy Id
   */
	String_t                   policyId;

  /*****************************************************************************/
  /* @var UserIdentityTokenType_t tokenType
   *  User Identity Token Type
   */
  UserIdentityTokenType_t    tokenType;

  /*****************************************************************************/
  /* @var String_t issuedTokenType
   *  Issued Token Type
   */
  String_t                   issuedTokenType;

  /*****************************************************************************/
  /* @var String_t issuerEndpointUrl
   *  Issuer Endpoint URL
   */
  String_t                   issuerEndpointUrl;

  /*****************************************************************************/
  /* @var String_t securityPolicyUri
   *  Security Policy URI
   */
  String_t                   securityPolicyUri;

public:
  UA_DECLARE_RUNTIME_TYPE(UserTokenPolicy_t);

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_UserTokenPolicy;

  /*****************************************************************************/
  /** Constructor for the class.
   *
   */
  UserTokenPolicy_t();

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~UserTokenPolicy_t();

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
  bool operator==(UserTokenPolicy_t const & obj) const;

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
   * @param[in] UserTokenPolicy_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS UserTokenPolicy_t object is greater than RHS UserTokenPolicy_t object
   */
  bool operator>(UserTokenPolicy_t const & obj) const;

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
   * @param[in] const UserTokenPolicy_t& source
   * User Token Policy source object to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const UserTokenPolicy_t& source);

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
  /** Get the Token Type
   *
   * @return
   * Returns the Token Type
   */
  const UserIdentityTokenType_t& TokenType(void) const;

  /*****************************************************************************/
  /** Get the Token Type
   *
   * @return
   * Returns the Token Type
   */
  UserIdentityTokenType_t& TokenType(void);

  /*****************************************************************************/
  /** Get the Issued Token Type
   *
   * @return
   * Returns the Issued Token Type
   */
  const String_t& IssuedTokenType(void) const;

  /*****************************************************************************/
  /** Get the Issued Token Type
   *
   * @return
   * Returns theIssued Token Type
   */
  String_t& IssuedTokenType(void);

  /*****************************************************************************/
  /** Get the Issuer Endpoint URL
   *
   * @return
   * Returns the Issuer Endpoint URL
   */
  const String_t& IssuerEndpointUrl(void) const;

  /*****************************************************************************/
  /** Get the Issuer Endpoint URL
   *
   * @return
   * Returns the Issuer Endpoint URL
   */
  String_t& IssuerEndpointUrl(void);

  /*****************************************************************************/
  /** Get the Security Policy URI
   *
   * @return
   * Returns the Security Policy URI
   */
  const String_t& SecurityPolicyUri(void) const;

  /*****************************************************************************/
  /** Get the Security Policy URI
   *
   * @return
   * Returns the Security Policy URI
   */
  String_t& SecurityPolicyUri(void);

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
   * @param[out] UserTokenPolicy_t& result
   * Decoded User Token Policy object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, UserTokenPolicy_t& result);
};

/** @} */

} // namespace uasdk
#endif // _OPCUA_USER_TOKEN_POLICY_T_
