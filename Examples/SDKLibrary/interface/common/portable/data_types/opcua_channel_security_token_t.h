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

#ifndef _OPCUA_CHANNEL_SECURITY_TOKEN_T_
#define _OPCUA_CHANNEL_SECURITY_TOKEN_T_

#include "opcua_expanded_node_id_t.h"
#include "opcua_date_time_t.h"
#include "opcua_int32_t.h"
#include "opcua_structure_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief ChannelSecurityToken_t
 *
 * This class implements the Channel Security Token data type
 *
 */
class ChannelSecurityToken_t : public Structure_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(ChannelSecurityToken_t);

private:

  /*****************************************************************************/
  /* @var UInt32_t   channelId
   * Channel ID
   */
	UInt32_t   channelId;

  /*****************************************************************************/
  /* @var UInt32_t   tokenId
   * Tocken ID
   */
  UInt32_t   tokenId;

  /*****************************************************************************/
  /* @var DateTime_t createdAt
   * Date and time Created At
   */
  DateTime_t createdAt;

  /*****************************************************************************/
  /* @var Int32_t    revisedLifetime
   * Revised Life time
   */
  Int32_t    revisedLifetime;

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_ChannelSecurityToken;

  /*****************************************************************************/
  /** Constructor for the class.
   *
   */
  ChannelSecurityToken_t();

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~ChannelSecurityToken_t();

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
   * @param[in] ChannelSecurityToken_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  bool operator==(ChannelSecurityToken_t const & obj) const;

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
   * @param[in] ChannelSecurityToken_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS ChannelSecurityToken_t object is greater than RHS ChannelSecurityToken_t object
   */
  bool operator>(ChannelSecurityToken_t const & obj) const;

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
   * @param[in] const ChannelSecurityToken_t& source
   *  Channel Security Token source object to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const ChannelSecurityToken_t& source);

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
  /** Get the Channel id
   *
   * @return
   * Returns the chennel id
   */
  const UInt32_t& ChannelId(void) const;

  /*****************************************************************************/
  /** Get the Channel id
   *
   * @return
   * Returns the channel id
   */
  UInt32_t& ChannelId(void);

  /*****************************************************************************/
  /** Get the Token id
   *
   * @return
   * Returns the Token id
   */
  const UInt32_t& TokenId(void) const;

  /*****************************************************************************/
  /** Get the Token id
   *
   * @return
   * Returns the Token id
   */
  UInt32_t& TokenId(void);

  /*****************************************************************************/
  /** Get the Data and time created
   *
   * @return
   * Returns the Data and time created
   */
  const DateTime_t& CreatedAt(void) const;

  /*****************************************************************************/
  /** Get the Data and time created
   *
   * @return
   * Returns the Data and time created
   */
  DateTime_t& CreatedAt(void);

  /*****************************************************************************/
  /** Get the revised life time
   *
   * @return
   * Returns the revised life time
   */
  const Int32_t& RevisedLifetime(void) const;

  /*****************************************************************************/
  /** Get the revised life time
   *
   * @return
   * Returns the revised life time
   */
  Int32_t& RevisedLifetime(void);

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
   * @param[out] ChannelSecurityToken_t& result
   * Decoded Channel Security Token object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, ChannelSecurityToken_t& result);
};

/** @} */

} // namespace uasdk
#endif // _OPCUA_CHANNEL_SECURITY_TOKEN_T_
