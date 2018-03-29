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

#ifndef _OPCUA_APP_DESCRIPTION_T_
#define _OPCUA_APP_DESCRIPTION_T_


#include "opcua_string_t.h"
#include "opcua_localized_text_t.h"
#include "opcua_application_type_t.h"
#include "opcua_array_ua_t.h"
#include "opcua_structure_t.h"

namespace uasdk
{
/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief AppDescription_t
 *
 * This class implements the Application Description data type
 *
 */
class AppDescription_t : public Structure_t
{
private:

  /*****************************************************************************/
  /* @var String_t applicationUri
   * Application URI
   */
  String_t                applicationUri;

  /*****************************************************************************/
  /* @var String_t productUri
   * Product URI
   */
  String_t                productUri;

  /*****************************************************************************/
  /* @var LocalizedText_t applicationName
   * Application name
   */
  LocalizedText_t			    applicationName;

  /*****************************************************************************/
  /* @var ApplicationType_t applicationType
   * Application type
   */
  ApplicationType_t       applicationType;

  /*****************************************************************************/
  /* @var String_t gatewayServerUri
   * Gateway Server URI
   */
  String_t                gatewayServerUri;

  /*****************************************************************************/
  /* @var String_t discoveryProfileUri
   * Discovery Profile URI
   */
  String_t                discoveryProfileUri;

  /*****************************************************************************/
  /* @var ArrayUA_t<String_t> discoveryUrls
   * Discovery URI
   */
  ArrayUA_t<String_t>     discoveryUrls;

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  UA_DECLARE_RUNTIME_TYPE(AppDescription_t);
  
  static const uint32_t TYPE_ID = OpcUaId_ApplicationDescription;

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~AppDescription_t();

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
   * @param[in] AppDescription_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  bool operator==(AppDescription_t const & obj) const;

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
   * @param[in] AnonymousIdentityToken_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the first byte that does not match
   * in both the class member variables have a greater value in lhs than in rhs as if evaluated
   * as unsigned char values; And a value of false indicates the opposite.
   */
  bool operator>(AppDescription_t const & obj) const;

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
   * @param[in] const AppDescription_t& source
   * Application Description to copy from
   *
   * @return
   * Status of the operation
   */
  virtual Status_t CopyFrom(const AppDescription_t& source);

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
  /** Get the Application Uri
   *
   * @return
   * Returns the Application Uri
   */
  const String_t& ApplicationUri(void) const;

  /*****************************************************************************/
  /** Get the Application Uri
   *
   * @return
   * Returns the Application Uri
   */
  String_t& ApplicationUri(void);

  /*****************************************************************************/
  /** Get the Product Uri
   *
   * @return
   * Returns the Product Uri
   */
  const String_t& ProductUri(void) const;

  /*****************************************************************************/
  /** Get the Product Uri
   *
   * @return
   * Returns the Product Uri
   */
  String_t& ProductUri(void);

  /*****************************************************************************/
  /** Get the Application Name
   *
   * @return
   * Returns the Application Name
   */
  const LocalizedText_t& ApplicationName(void) const;

  /*****************************************************************************/
  /** Get the Application Name
   *
   * @return
   * Returns the Application Name
   */
  LocalizedText_t& ApplicationName(void);

  /*****************************************************************************/
  /** Get the Application Type
   *
   * @return
   * Returns the Application Type
   */
  const ApplicationType_t& ApplicationType(void) const;

  /*****************************************************************************/
  /** Get the Application Type
   *
   * @return
   * Returns the Application Type
   */
  ApplicationType_t& ApplicationType(void);

  /*****************************************************************************/
  /** Get the Gateway Server URI
   *
   * @return
   * Returns the Gateway Server URI
   */
  const String_t& GatewayServerUri(void) const;

  /*****************************************************************************/
  /** Get the Gateway Server URI
   *
   * @return
   * Returns the Gateway Server v
   */
  String_t& GatewayServerUri(void);

  /*****************************************************************************/
  /** Get the Discovery Profile URI
   *
   * @return
   * Returns the Discovery Profile URI
   */
  const String_t& DiscoveryProfileUri(void) const;

  /*****************************************************************************/
  /** Get the Discovery Profile URI
   *
   * @return
   * Returns the Discovery Profile URI
   */
  String_t& DiscoveryProfileUri(void);

  /*****************************************************************************/
  /** Get the Discovery Urls
   *
   * @return
   * Returns the Discovery Urls
   */
  const ArrayUA_t<String_t>& DiscoveryUrls(void) const;

  /*****************************************************************************/
  /** Get the Discovery Urls
   *
   * @return
   * Returns the Discovery Urls
   */
  ArrayUA_t<String_t>& DiscoveryUrls(void);

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
   * @param[out] AppDescription_t& result
   * Decoded Application Description
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, AppDescription_t& result);

};

/** @} */

} // namespace uasdk
#endif // _OPCUA_APP_DESCRIPTION_T_
