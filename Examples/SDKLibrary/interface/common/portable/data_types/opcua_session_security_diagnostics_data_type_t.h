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

#ifndef _OPCUA_SESSION_SECURITY_DIAGNOSTICS_DATA_TYPE_T_H_
#define _OPCUA_SESSION_SECURITY_DIAGNOSTICS_DATA_TYPE_T_H_

#include "uasdk_includes.h"

#if (UASDK_INCLUDE_SESSION_DIAGNOSTICS > 0)

#include "opcua_structure_t.h"
#include "opcua_node_id_guid_t.h"
#include "opcua_message_security_mode_t.h"
#include "opcua_array_ua_t.h"


namespace uasdk
{
/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief SubscriptionDiagnosticsDataType_t
 *
 * This class implements the Subscription Diagnostics Data Type
 *
 */
class SessionSecurityDiagnosticsDataType_t : public Structure_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(SessionSecurityDiagnosticsDataType_t);

private:

  /*****************************************************************************/
  /* @var NodeIdGuid_t sessionId
   * session id that subscription belongs to
   */
  NodeIdGuid_t sessionId;
  
  /*****************************************************************************/
  /* @var String_t clientUserIdOfSession
   * Client User Id Of the Session 
   */
  String_t clientUserIdOfSession;

  /*****************************************************************************/
  /* @var ArrayUA_t<String_t>  clientUserIdHistory
  * Client User Id Of History
  */
  ArrayUA_t<String_t> clientUserIdHistory;
  
  /*****************************************************************************/
  /* @var String_t authenticationMechanism
   * Session Security authenticationMechanism
   */
  String_t authenticationMechanism;

  /*****************************************************************************/
  /* @var String_t encoding
  * Session Security Encoding
  */
  String_t encoding;

  /*****************************************************************************/
  /* @var String_t transportProtocol
  * Session Security transportProtocol
  */
  String_t transportProtocol;

  /*****************************************************************************/
  /* @var MessageSecurityMode_t securityMode
  * Session Security SecurityMode
  */
  MessageSecurityMode_t securityMode;

  /*****************************************************************************/
  /* @var String_t securityPolicyUri
  * Session SecurityPolicyUri
  */
  String_t securityPolicyUri;

  /*****************************************************************************/
  /* @var ByteString_t clientCertificate
  * Session Security clientCertificate
  */
  ByteString_t clientCertificate;

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID for SessionSecurityDiagnosticsType
   */
  static const uint32_t TYPE_ID = OpcUaId_SessionSecurityDiagnosticsType;

  /*****************************************************************************/
  /** Constructor for the class.
   *
   */
  SessionSecurityDiagnosticsDataType_t();
  
  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~SessionSecurityDiagnosticsDataType_t();

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
   * @param[in] SessionSecurityDiagnosticsDataType_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  bool operator==(SessionSecurityDiagnosticsDataType_t const & obj) const;

  /*****************************************************************************/
  /** != operator overloading
   *
   * @param[in] const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are not same
   * False - If the both the objects are same
   */
  bool operator!=(SessionSecurityDiagnosticsDataType_t const & obj) const;

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
   * @param[in] SessionSecurityDiagnosticsDataType_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS SessionSecurityDiagnosticsDataType_t object is greater than RHS SessionSecurityDiagnosticsDataType_t object
   */
  bool operator>(SessionSecurityDiagnosticsDataType_t const & obj) const;

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
   * @param[in] const SessionSecurityDiagnosticsDataType_t& source
   * Session Security Diagnostics Data Type source object to copy from
   *
   * @return
   * Status of the operation
   */
  virtual Status_t CopyFrom(const SessionSecurityDiagnosticsDataType_t& source);

  /*****************************************************************************/
  /** Get the Type ID
   *
   * @param[in] uint16_t& namespaceIndex
   * Reference to the name space index
   *
   * @return
   * Returns the Data Type ID
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
  /** Get the SessionId
   *
   * @return
   * Returns the SessionId
   */
  const NodeIdGuid_t& SessionId() const;
  
  /*****************************************************************************/
  /** Get the SessionId
   *
   * @return
   * Returns the SessionId
   */
  NodeIdGuid_t& SessionId();

  /*****************************************************************************/
  /** Get the ClientUserIdOfSession
   *
   * @return
   * Returns the ClientUserIdOfSession
   */
  const String_t& ClientUserIdOfSession() const;
  
  /*****************************************************************************/
  /** Get the ClientUserIdOfSession
   *
   * @return
   * Returns the ClientUserIdOfSession
   */
   String_t& ClientUserIdOfSession() ;

   /*****************************************************************************/
   /** Get the ClientUserIdHistory
   *
   * @return
   * Returns the ClientUserIdHistory
   */
   const  ArrayUA_t<String_t>& ClientUserIdHistory() const;

   /*****************************************************************************/
   /** Get the ClientUserIdHistory
   *
   * @return
   * Returns the ClientUserIdHistory
   */
   ArrayUA_t<String_t>& ClientUserIdHistory();

   /*****************************************************************************/
   /** Get the AuthenticationMechanism
   *
   * @return
   * Returns the AuthenticationMechanism
   */
   const String_t& AuthenticationMechanism() const;

   /*****************************************************************************/
   /** Get the AuthenticationMechanism
   *
   * @return
   * Returns the AuthenticationMechanism
   */
   String_t& AuthenticationMechanism();

   /*****************************************************************************/
   /** Get the Encoding
   *
   * @return
   * Returns the Encoding
   */
   const String_t& Encoding() const;

   /*****************************************************************************/
   /** Get the Encoding
   *
   * @return
   * Returns the Encoding
   */
   String_t& Encoding();

   /*****************************************************************************/
   /** Get the TransportProtocol
   *
   * @return
   * Returns the TransportProtocol
   */
   const String_t& TransportProtocol() const;

   /*****************************************************************************/
   /** Get the TransportProtocol
   *
   * @return
   * Returns the TransportProtocol
   */
   String_t& TransportProtocol();

   /*****************************************************************************/
   /** Get the SecurityMode
   *
   * @return
   * Returns the SecurityMode
   */
   const MessageSecurityMode_t& SecurityMode() const;

   /*****************************************************************************/
   /** Get the SecurityMode
   *
   * @return
   * Returns the SecurityMode
   */
   MessageSecurityMode_t& SecurityMode();

   /*****************************************************************************/
   /** Get the SecurityPolicyUri
   *
   * @return
   * Returns the SecurityPolicyUri
   */
   const String_t& SecurityPolicyUri() const;

   /*****************************************************************************/
   /** Get the SecurityPolicyUri
   *
   * @return
   * Returns the SecurityPolicyUri
   */
   String_t& SecurityPolicyUri();

   /*****************************************************************************/
   /** Get the ClientCertificate
   *
   * @return
   * Returns the ClientCertificate
   */
   const ByteString_t& ClientCertificate() const;

   /*****************************************************************************/
   /** Get the ClientCertificate
   *
   * @return
   * Returns the ClientCertificate
   */
   ByteString_t& ClientCertificate();

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
   * @param[out] SessionSecurityDiagnosticsDataType_t& result
   * Decoded Subscription Diagnostics Data Type
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, SessionSecurityDiagnosticsDataType_t& result);
};

/** @} */

} //namespace uasdk

#endif  //UASDK_INCLUDE_SESSION_SECURITY_DIAGNOSTICS

#endif /* _OPCUA_SESSION_SECURITY_DIAGNOSTICS_DATA_TYPE_T_H_ */
