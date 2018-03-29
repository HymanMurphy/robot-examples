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

#ifndef _OPCUA_ANONYMOUS_IDENTITY_TOKEN_T_
#define _OPCUA_ANONYMOUS_IDENTITY_TOKEN_T_

#include "opcua_structure_t.h"
#include "opcua_string_t.h"
#include "opcua_bytestring_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief AnonymousIdentityToken_t
 *
 * This class implements the Anonymous Identity Token data type
 *
 */
class AnonymousIdentityToken_t : public Structure_t
{
private:

  /*****************************************************************************/
  /* @var String_t     policyId
   * Policy ID
   */
  String_t     policyId;

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  UA_DECLARE_RUNTIME_TYPE(AnonymousIdentityToken_t);
  
  static const uint32_t TYPE_ID = OpcUaId_AnonymousIdentityToken;

  /*****************************************************************************/
  /** default constructor for the class.
   *
   */
  AnonymousIdentityToken_t();

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~AnonymousIdentityToken_t();

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
   * @param[in] AnonymousIdentityToken_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  bool operator==(AnonymousIdentityToken_t const & obj) const;

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
   * in both policy id has a greater value in lhs than in rhs as if evaluated
   * as unsigned char values; And a value of false indicates the opposite.
   */
  bool operator>(AnonymousIdentityToken_t const & obj) const;

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
   * @param[in] const AnonymousIdentityToken_t& source
   * Anonymous Identity Token
   *
   * @return
   * Status of the operation
   */
  virtual Status_t CopyFrom(const AnonymousIdentityToken_t& source);

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
   * @param[out] AnonymousIdentityToken_t& result
   * Decoded Anonymous Identity Token
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer,
                              ICodec_t& decoder,
                              AnonymousIdentityToken_t& result);

};

/** @} */

} // namespace uasdk
#endif // _OPCUA_ANONYMOUS_IDENTITY_TOKEN_T__
