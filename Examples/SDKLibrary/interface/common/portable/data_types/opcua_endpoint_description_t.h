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

#ifndef _OPCUA_ENDPOINT_DESCRIPTION_T_
#define _OPCUA_ENDPOINT_DESCRIPTION_T_

#include "opcua_string_t.h"
#include "opcua_app_description_t.h"
#include "opcua_bytestring_t.h"
#include "opcua_message_security_mode_t.h"
#include "opcua_user_token_policy_t.h"
#include "opcua_byte_t.h"
#include "opcua_array_ua_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief EndpointDescription_t
 *
 * This class implements the End point Description data type
 *
 */
class EndpointDescription_t : public Structure_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(EndpointDescription_t);
private:

  /*****************************************************************************/
  /* @var String_t endpointUrl
   *  End point URL
   */
  String_t                        endpointUrl; /* Recommended parameter */

  /*****************************************************************************/
  /* @var AppDescription_t applicationDescription
   *  Application Description
   */
  AppDescription_t                applicationDescription;

  /*****************************************************************************/
  /* @var ByteString_t serverCertificate
   *  Server Certificate
   */
  ByteString_t                    serverCertificate;

  /*****************************************************************************/
  /* @var MessageSecurityMode_t securityMode
   *  Security Mode
   */
  MessageSecurityMode_t           securityMode; /* Recommended parameter */

  /*****************************************************************************/
  /* @var String_t securityPolicyUri
   * Security Policy URI
   */
  String_t                        securityPolicyUri; /* Recommended parameter */

  /*****************************************************************************/
  /* @var ArrayUA_t<UserTokenPolicy_t>
   *  User Identity Tokens
   */
  ArrayUA_t<UserTokenPolicy_t>    userIdentityTokens; /* Recommended parameter */

  /*****************************************************************************/
  /* @var String_t userIdentityTokens
   *  Transport Profile URI
   */
  String_t                        transportProfileUri; /* Recommended parameter */

  /*****************************************************************************/
  /* @var Byte_t securityLevel
   *  Security Level
   */
  Byte_t                          securityLevel; /* Recommended parameter */

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_EndpointDescription;

  /*****************************************************************************/
  /** Constructor for the class.
   *
   */
  EndpointDescription_t();

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~EndpointDescription_t();

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
   * @param[in] const EndpointDescription_t& obj
   * Object to be assigned
   *
   * @return
   * Reference to the Endpoint Description  object assigned
   */
  bool operator==(EndpointDescription_t const & obj) const;

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
   * @param[in] EndpointDescription_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS EndpointDescription_t object is greater than RHS EndpointDescription_t object
   */
  bool operator>(EndpointDescription_t const & obj) const;

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
   * @param[in] const EndpointDescription_t& source
   * Endpoint Description source object to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const EndpointDescription_t& source);

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
  /** Get the Endpoint URL
   *
   * @return
   * Returns the Endpoint URL
   */
  const String_t& EndpointUrl(void) const;

  /*****************************************************************************/
  /** Get the Endpoint URL
   *
   * @return
   * Returns the Endpoint URL
   */
  String_t& EndpointUrl(void);

  /*****************************************************************************/
  /** Get the Application Description
   *
   * @return
   * Returns the Application Description
   */
  const AppDescription_t& ApplicationDescription(void) const;

  /*****************************************************************************/
  /** Get the Application Description
   *
   * @return
   * Returns the Application Description
   */
  AppDescription_t& ApplicationDescription(void);

  /*****************************************************************************/
  /** Get the Server Certificate
   *
   * @return
   * Returns the Server Certificate
   */
  const ByteString_t& ServerCertificate(void) const;

  /*****************************************************************************/
  /** Get the Server Certificate
   *
   * @return
   * Returns the Server Certificate
   */
  ByteString_t& ServerCertificate(void);

  //  MessageSecurityMode_t::Enum_t SecurityMode(void) const { return securityMode.Value(); }
  //  void SecurityMode(MessageSecurityMode_t::Enum_t val) { securityMode.Value(val); }

  /*****************************************************************************/
  /** Get the Security Mode
   *
   * @return
   * Returns the Security Mode
   */
  const MessageSecurityMode_t& SecurityMode(void) const;

  /*****************************************************************************/
  /** Get the Security Mode
   *
   * @return
   * Returns the Security Mode
   */
  MessageSecurityMode_t& SecurityMode(void);

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
  /** Get the User Identity Tokens
   *
   * @return
   * Returns the User Identity Tokens
   */
  const ArrayUA_t<UserTokenPolicy_t>& UserIdentityTokens(void) const;

  /*****************************************************************************/
  /** Get the User Identity Tokens
   *
   * @return
   * Returns the User Identity Tokens
   */
  ArrayUA_t<UserTokenPolicy_t>& UserIdentityTokens(void);

  /*****************************************************************************/
  /** Get the Transport Profile URI
   *
   * @return
   * Returns the Transport Profile URI
   */
  const String_t& TransportProfileUri(void) const;

  /*****************************************************************************/
  /** Get the Transport Profile URI
   *
   * @return
   * Returns the Transport Profile URI
   */
  String_t& TransportProfileUri(void);

  /*****************************************************************************/
  /** Get the Security Level
   *
   * @return
   * Returns the Security Level
   */
  const Byte_t& SecurityLevel(void) const;

  /*****************************************************************************/
  /** Get the Security Level
   *
   * @return
   * Returns the Security Level
   */
  Byte_t& SecurityLevel(void);

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
   * @param[out] EndpointDescription_t& result
   * Decoded Endpoint Description object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, EndpointDescription_t& result);
};

/** @} */

} // namespace uasdk
#endif // _OPCUA_ENDPOINT_DESCRIPTION_T_
