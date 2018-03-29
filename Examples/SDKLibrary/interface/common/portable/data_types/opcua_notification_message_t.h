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

#ifndef _OPCUA_NOTIFICATION_MESSAGE_T_
#define _OPCUA_NOTIFICATION_MESSAGE_T_

#include "opcua_node_id_t.h"
#include "opcua_bytestring_t.h"
#include "opcua_string_t.h"
#include "opcua_browse_direction_t.h"
#include "opcua_uint32_t.h"
#include "opcua_date_time_t.h"
#include "opcua_array_ua_t.h"
#include "opcua_extensible_parameter_t.h"

#if (UASDK_INCLUDE_SUBSCRIPTIONS > 0)

namespace uasdk
{
/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief NotificationMessage_t
 *
 * This class implements the Notification Message data type
 *
 */
class NotificationMessage_t : public Structure_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(NotificationMessage_t);
private:

  /*****************************************************************************/
  /* @var Counter_t sequenceNumber
   * Sequence Number
   */
  Counter_t                         sequenceNumber;

  /*****************************************************************************/
  /* @var UtcTime_t publishTime
   * Publish time
   */
  UtcTime_t                      publishTime;

  /*****************************************************************************/
  /* @var ArrayUA_t<ExtensibleParameter_t> notificationData
   * Notification Data
   */
  ArrayUA_t<ExtensibleParameter_t>  notificationData;

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID
   */
  static const uint32_t TYPE_ID = OpcUaId_NotificationMessage;

  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~NotificationMessage_t();

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
   * @param[in]  NotificationMessage_t const & obj
   * Object to be assigned
   *
   * @return
   * Reference to the Notification Message object assigned
   */
  bool operator==(NotificationMessage_t const & obj) const;

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
   * @param[in] NotificationMessage_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS NotificationMessage_t object is greater than RHS NotificationMessage_t object
   */
  bool operator>(NotificationMessage_t const & obj) const;

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
   * @param[in] const NotificationMessage_t& source
   *  Notification Message source object to copy from
   *
   * @return
   * Status of the operation
   */
  Status_t CopyFrom(const NotificationMessage_t& source);

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
  /** Get the Sequence Number
   *
   * @return
   * Returns the Sequence Number
   */
  const Counter_t&  SequenceNumber(void) const;

  /*****************************************************************************/
  /** Get the Sequence Number
   *
   * @return
   * Returns the Sequence Number
   */
  Counter_t&  SequenceNumber(void);

  /*****************************************************************************/
  /** Get the Publish time
   *
   * @return
   * Returns the Publish time
   */
  const UtcTime_t& PublishTime(void) const;

  /*****************************************************************************/
  /** Get the Publish time
   *
   * @return
   * Returns the Publish time
   */
  UtcTime_t& PublishTime(void);

  /*****************************************************************************/
  /** Get the Notification data
   *
   * @return
   * Returns the Notification data
   */
  const ArrayUA_t<ExtensibleParameter_t>& NotificationData(void) const;

  /*****************************************************************************/
  /** Get the Notification data
   *
   * @return
   * Returns the Notification data
   */
  ArrayUA_t<ExtensibleParameter_t>& NotificationData(void);

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
   * @param[out] NotificationMessage_t& result
   * Decoded Notification Message object
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, NotificationMessage_t& result);
};

/** @} */

} // namespace uasdk

#endif //UASDK_INCLUDE_SUBSCRIPTIONS

#endif // _OPCUA_NOTIFICATION_MESSAGE_T_
