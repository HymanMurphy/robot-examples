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

#ifndef _OPCUA_SUBSCRIPTION_DIAGNOSTICS_DATA_TYPE_T_H_
#define _OPCUA_SUBSCRIPTION_DIAGNOSTICS_DATA_TYPE_T_H_

#include "uasdk_includes.h"

#if (UASDK_INCLUDE_SUBSCRIPTION_DIAGNOSTICS > 0)

#include "opcua_structure_t.h"
#include "opcua_node_id_guid_t.h"
#include "opcua_uint32_t.h"
#include "opcua_byte_t.h"
#include "opcua_duration_t.h"
#include "opcua_boolean_t.h"

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
class SubscriptionDiagnosticsDataType_t : public Structure_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(SubscriptionDiagnosticsDataType_t);

private:

  /*****************************************************************************/
  /* @var NodeIdGuid_t sessionId
   * session id that subscription belongs to
   */
  NodeIdGuid_t sessionId;
  
  /*****************************************************************************/
  /* @var UInt32_t subscriptionId
   * subscription id
   */
  UInt32_t subscriptionId;
  
  /*****************************************************************************/
  /* @var Byte_t priority
   * Subscription priority
   */
  Byte_t priority;

  /*****************************************************************************/
  /* @var Duration_t publishingInterval
  * Subscription publishingInterval
  */
  Duration_t publishingInterval;

  /*****************************************************************************/
  /* @var UInt32_t maxKeepAliveCount
  * Subscription maxKeepAliveCount
  */
  UInt32_t maxKeepAliveCount;

  /*****************************************************************************/
  /* @var UInt32_t priority
  * Subscription maxLifetimeCount
  */
  UInt32_t maxLifetimeCount;

  /*****************************************************************************/
  /* @var UInt32_t maxNotificationsPerPublish
  * Subscription maxNotificationsPerPublish
  */
  UInt32_t maxNotificationsPerPublish;

  /*****************************************************************************/
  /* @var Boolean_t publishingEnabled
  * Subscription publishingEnabled
  */
  Boolean_t publishingEnabled;

  /*****************************************************************************/
  /* @var UInt32_t modifyCount
  * Subscription modifyCount
  */
  UInt32_t modifyCount;

  /*****************************************************************************/
  /* @var UInt32_t enableCount
  * Subscription enableCount
  */
  UInt32_t enableCount;

  /*****************************************************************************/
  /* @var UInt32_t disableCount
  * Subscription disableCount
  */
  UInt32_t disableCount;

  /*****************************************************************************/
  /* @var UInt32_t republishRequestCount
  * Subscription republishRequestCount
  */
  UInt32_t republishRequestCount;

  /*****************************************************************************/
  /* @var UInt32_t republishMessageRequestCount
  * Subscription republishMessageRequestCount
  */
  UInt32_t republishMessageRequestCount;

  /*****************************************************************************/
  /* @var UInt32_t republishMessageCount
  * Subscription republishMessageCount
  */
  UInt32_t republishMessageCount;

  /*****************************************************************************/
  /* @var UInt32_t transferRequestCount
  * Subscription transferRequestCount
  */
  UInt32_t transferRequestCount;

  /*****************************************************************************/
  /* @var UInt32_t transferredToAltClientCount
  * Subscription transferredToAltClientCount
  */
  UInt32_t transferredToAltClientCount;

  /*****************************************************************************/
  /* @var UInt32_t transferredToSameClientCount
  * Subscription transferredToSameClientCount
  */
  UInt32_t transferredToSameClientCount;

  /*****************************************************************************/
  /* @var UInt32_t publishRequestCount
  * Subscription publishRequestCount
  */
  UInt32_t publishRequestCount;

  /*****************************************************************************/
  /* @var UInt32_t dataChangeNotificationsCount
  * Subscription dataChangeNotificationsCount
  */
  UInt32_t dataChangeNotificationsCount;

  /*****************************************************************************/
  /* @var UInt32_t eventNotificationsCount
  * Subscription eventNotificationsCount
  */
  UInt32_t eventNotificationsCount;

  /*****************************************************************************/
  /* @var UInt32_t notificationsCount
  * Subscription notificationsCount
  */
  UInt32_t notificationsCount;

  /*****************************************************************************/
  /* @var UInt32_t latePublishRequestCount
  * Subscription latePublishRequestCount
  */
  UInt32_t latePublishRequestCount;

  /*****************************************************************************/
  /* @var UInt32_t currentKeepAliveCount
  * Subscription currentKeepAliveCount
  */
  UInt32_t currentKeepAliveCount;

  /*****************************************************************************/
  /* @var UInt32_t currentLifetimeCount
  * Subscription currentLifetimeCount
  */
  UInt32_t currentLifetimeCount;

  /*****************************************************************************/
  /* @var UInt32_t unacknowledgedMessageCount
  * Subscription unacknowledgedMessageCount
  */
  UInt32_t unacknowledgedMessageCount;

  /*****************************************************************************/
  /* @var UInt32_t discardedMessageCount
  * Subscription discardedMessageCount
  */
  UInt32_t discardedMessageCount;

  /*****************************************************************************/
  /* @var UInt32_t monitoredItemCount
  * Subscription monitoredItemCount
  */
  UInt32_t monitoredItemCount;

  /*****************************************************************************/
  /* @var UInt32_t disabledMonitoredItemCount
  * Subscription disabledMonitoredItemCount
  */
  UInt32_t disabledMonitoredItemCount;

  /*****************************************************************************/
  /* @var UInt32_t monitoringQueueOverflowCount
  * Subscription monitoringQueueOverflowCount
  */
  UInt32_t monitoringQueueOverflowCount;

  /*****************************************************************************/
  /* @var UInt32_t nextSequenceNumber
  * Subscription nextSequenceNumber
  */
  UInt32_t nextSequenceNumber;

  /*****************************************************************************/
  /* @var UInt32_t eventQueueOverflowCount
  * Subscription eventQueueOverflowCount
  */
  UInt32_t eventQueueOverflowCount;

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID for ServerDiagnosticsSummaryDataType
   */
  static const uint32_t TYPE_ID = OpcUaId_SubscriptionDiagnosticsType;

  /*****************************************************************************/
  /** Constructor for the class.
   *
   */
  SubscriptionDiagnosticsDataType_t();
  
  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~SubscriptionDiagnosticsDataType_t();

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
   * @param[in] SubscriptionDiagnosticsDataType_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  bool operator==(SubscriptionDiagnosticsDataType_t const & obj) const;

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
  bool operator!=(SubscriptionDiagnosticsDataType_t const & obj) const;

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
   * @param[in] SubscriptionDiagnosticsDataType_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS SubscriptionDiagnosticsDataType_t object is greater than RHS SubscriptionDiagnosticsDataType_t object
   */
  bool operator>(SubscriptionDiagnosticsDataType_t const & obj) const;

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
   * @param[in] const SubscriptionDiagnosticsDataType_t& source
   * Server Diagnostics Summery Data Type source object to copy from
   *
   * @return
   * Status of the operation
   */
  virtual Status_t CopyFrom(const SubscriptionDiagnosticsDataType_t& source);

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
  /** Get the SubscriptionId
   *
   * @return
   * Returns the SubscriptionId
   */
  const UInt32_t& SubscriptionId() const;
  
  /*****************************************************************************/
  /** Get the SubscriptionId
   *
   * @return
   * Returns the SubscriptionId
   */
  UInt32_t& SubscriptionId();

  /*****************************************************************************/
  /** Get the Priority
   *
   * @return
   * Returns the Priority
   */
  const Byte_t& Priority() const;
  
  /*****************************************************************************/
  /** Get the Priority
   *
   * @return
   * Returns the Priority
   */
  Byte_t& Priority();

  /*****************************************************************************/
  /** Get the PublishingInterval
  *
  * @return
  * Returns the PublishingInterval
  */
  const Duration_t& PublishingInterval() const;

  /*****************************************************************************/
  /** Get the PublishingInterval
  *
  * @return
  * Returns the PublishingInterval
  */
  Duration_t& PublishingInterval();

  /*****************************************************************************/
  /** Get the MaxKeepAliveCount
  *
  * @return
  * Returns the MaxKeepAliveCount
  */
  const UInt32_t& MaxKeepAliveCount() const;

  /*****************************************************************************/
  /** Get the MaxKeepAliveCount
  *
  * @return
  * Returns the MaxKeepAliveCount
  */
  UInt32_t& MaxKeepAliveCount();

  /*****************************************************************************/
  /** Get the MaxLifetimeCount
  *
  * @return
  * Returns the MaxLifetimeCount
  */
  const UInt32_t& MaxLifetimeCount() const;

  /*****************************************************************************/
  /** Get the MaxLifetimeCount
  *
  * @return
  * Returns the MaxLifetimeCount
  */
  UInt32_t& MaxLifetimeCount();

  /*****************************************************************************/
  /** Get the MaxNotificationsPerPublish
  *
  * @return
  * Returns the MaxNotificationsPerPublish
  */
  const UInt32_t& MaxNotificationsPerPublish() const;

  /*****************************************************************************/
  /** Get the MaxNotificationsPerPublish
  *
  * @return
  * Returns the MaxNotificationsPerPublish
  */
  UInt32_t& MaxNotificationsPerPublish();

  /*****************************************************************************/
  /** Get the PublishingEnabled
  *
  * @return
  * Returns the PublishingEnabled
  */
  const Boolean_t& PublishingEnabled() const;

  /*****************************************************************************/
  /** Get the PublishingEnabled
  *
  * @return
  * Returns the PublishingEnabled
  */
  Boolean_t& PublishingEnabled();
  
  /*****************************************************************************/
  /** Get the ModifyCount
  *
  * @return
  * Returns the ModifyCount
  */
  const UInt32_t& ModifyCount() const;

  /*****************************************************************************/
  /** Get the ModifyCount
  *
  * @return
  * Returns the ModifyCount
  */
  UInt32_t& ModifyCount();

  /*****************************************************************************/
  /** Get the EnableCount
  *
  * @return
  * Returns the EnableCount
  */
  const UInt32_t& EnableCount() const;

  /*****************************************************************************/
  /** Get the EnableCount
  *
  * @return
  * Returns the EnableCount
  */
  UInt32_t& EnableCount();

  /*****************************************************************************/
  /** Get the DisableCount
  *
  * @return
  * Returns the DisableCount
  */
  const UInt32_t& DisableCount() const;

  /*****************************************************************************/
  /** Get the DisableCount
  *
  * @return
  * Returns the DisableCount
  */
  UInt32_t& DisableCount();

  /*****************************************************************************/
  /** Get the RepublishRequestCount
  *
  * @return
  * Returns the RepublishRequestCount
  */
  const UInt32_t& RepublishRequestCount() const;

  /*****************************************************************************/
  /** Get the RepublishRequestCount
  *
  * @return
  * Returns the RepublishRequestCount
  */
  UInt32_t& RepublishRequestCount();

  /*****************************************************************************/
  /** Get the RepublishMessageRequestCount
  *
  * @return
  * Returns the RepublishMessageRequestCount
  */
  const UInt32_t& RepublishMessageRequestCount() const;

  /*****************************************************************************/
  /** Get the RepublishMessageRequestCount
  *
  * @return
  * Returns the RepublishMessageRequestCount
  */
  UInt32_t& RepublishMessageRequestCount();

  /*****************************************************************************/
  /** Get the RepublishMessageCount
  *
  * @return
  * Returns the RepublishMessageCount
  */
  const UInt32_t& RepublishMessageCount() const;

  /*****************************************************************************/
  /** Get the RepublishMessageCount
  *
  * @return
  * Returns the RepublishMessageCount
  */
  UInt32_t& RepublishMessageCount();

  /*****************************************************************************/
  /** Get the TransferRequestCount
  *
  * @return
  * Returns the TransferRequestCount
  */
  const UInt32_t& TransferRequestCount() const;

  /*****************************************************************************/
  /** Get the TransferRequestCount
  *
  * @return
  * Returns the TransferRequestCount
  */
  UInt32_t& TransferRequestCount();

  /*****************************************************************************/
  /** Get the TransferredToAltClientCount
  *
  * @return
  * Returns the TransferredToAltClientCount
  */
  const UInt32_t& TransferredToAltClientCount() const;

  /*****************************************************************************/
  /** Get the TransferredToAltClientCount
  *
  * @return
  * Returns the TransferredToAltClientCount
  */
  UInt32_t& TransferredToAltClientCount();

  /*****************************************************************************/
  /** Get the TransferredToSameClientCount
  *
  * @return
  * Returns the TransferredToSameClientCount
  */
  const UInt32_t& TransferredToSameClientCount() const;

  /*****************************************************************************/
  /** Get the TransferredToSameClientCount
  *
  * @return
  * Returns the TransferredToSameClientCount
  */
  UInt32_t& TransferredToSameClientCount();

  /*****************************************************************************/
  /** Get the PublishRequestCount
  *
  * @return
  * Returns the PublishRequestCount
  */
  const UInt32_t& PublishRequestCount() const;

  /*****************************************************************************/
  /** Get the PublishRequestCount
  *
  * @return
  * Returns the PublishRequestCount
  */
  UInt32_t& PublishRequestCount();

  /*****************************************************************************/
  /** Get the DataChangeNotificationsCount
  *
  * @return
  * Returns the DataChangeNotificationsCount
  */
  const UInt32_t& DataChangeNotificationsCount() const;

  /*****************************************************************************/
  /** Get the DataChangeNotificationsCount
  *
  * @return
  * Returns the DataChangeNotificationsCount
  */
  UInt32_t& DataChangeNotificationsCount();

  /*****************************************************************************/
  /** Get the EventNotificationsCount
  *
  * @return
  * Returns the EventNotificationsCount
  */
  const UInt32_t& EventNotificationsCount() const;

  /*****************************************************************************/
  /** Get the EventNotificationsCount
  *
  * @return
  * Returns the EventNotificationsCount
  */
  UInt32_t& EventNotificationsCount();

  /*****************************************************************************/
  /** Get the NotificationsCount
  *
  * @return
  * Returns the NotificationsCount
  */
  const UInt32_t& NotificationsCount() const;

  /*****************************************************************************/
  /** Get the NotificationsCount
  *
  * @return
  * Returns the NotificationsCount
  */
  UInt32_t& NotificationsCount();

  /*****************************************************************************/
  /** Get the LatePublishRequestCount
  *
  * @return
  * Returns the LatePublishRequestCount
  */
  const UInt32_t& LatePublishRequestCount() const;

  /*****************************************************************************/
  /** Get the LatePublishRequestCount
  *
  * @return
  * Returns the LatePublishRequestCount
  */
  UInt32_t& LatePublishRequestCount();

  /*****************************************************************************/
  /** Get the CurrentKeepAliveCount
  *
  * @return
  * Returns the CurrentKeepAliveCount
  */
  const UInt32_t& CurrentKeepAliveCount() const;

  /*****************************************************************************/
  /** Get the CurrentKeepAliveCount
  *
  * @return
  * Returns the CurrentKeepAliveCount
  */
  UInt32_t& CurrentKeepAliveCount();

  /*****************************************************************************/
  /** Get the CurrentLifetimeCount
  *
  * @return
  * Returns the CurrentLifetimeCount
  */
  const UInt32_t& CurrentLifetimeCount() const;

  /*****************************************************************************/
  /** Get the CurrentLifetimeCount
  *
  * @return
  * Returns the CurrentLifetimeCount
  */
  UInt32_t& CurrentLifetimeCount();

  /*****************************************************************************/
  /** Get the UnacknowledgedMessageCount
  *
  * @return
  * Returns the UnacknowledgedMessageCount
  */
  const UInt32_t& UnacknowledgedMessageCount() const;

  /*****************************************************************************/
  /** Get the UnacknowledgedMessageCount
  *
  * @return
  * Returns the UnacknowledgedMessageCount
  */
  UInt32_t& UnacknowledgedMessageCount();

  /*****************************************************************************/
  /** Get the DiscardedMessageCount
  *
  * @return
  * Returns the DiscardedMessageCount
  */
  const UInt32_t& DiscardedMessageCount() const;

  /*****************************************************************************/
  /** Get the DiscardedMessageCount
  *
  * @return
  * Returns the DiscardedMessageCount
  */
  UInt32_t& DiscardedMessageCount();

  /*****************************************************************************/
  /** Get the MonitoredItemCount
  *
  * @return
  * Returns the MonitoredItemCount
  */
  const UInt32_t& MonitoredItemCount() const;

  /*****************************************************************************/
  /** Get the MonitoredItemCount
  *
  * @return
  * Returns the MonitoredItemCount
  */
  UInt32_t& MonitoredItemCount();

  /*****************************************************************************/
  /** Get the DisabledMonitoredItemCount
  *
  * @return
  * Returns the DisabledMonitoredItemCount
  */
  const UInt32_t& DisabledMonitoredItemCount() const;

  /*****************************************************************************/
  /** Get the DisabledMonitoredItemCount
  *
  * @return
  * Returns the DisabledMonitoredItemCount
  */
  UInt32_t& DisabledMonitoredItemCount();

  /*****************************************************************************/
  /** Get the MonitoringQueueOverflowCount
  *
  * @return
  * Returns the MonitoringQueueOverflowCount
  */
  const UInt32_t& MonitoringQueueOverflowCount() const;

  /*****************************************************************************/
  /** Get the MonitoringQueueOverflowCount
  *
  * @return
  * Returns the MonitoringQueueOverflowCount
  */
  UInt32_t& MonitoringQueueOverflowCount();

  /*****************************************************************************/
  /** Get the NextSequenceNumber
  *
  * @return
  * Returns the NextSequenceNumber
  */
  const UInt32_t& NextSequenceNumber() const;

  /*****************************************************************************/
  /** Get the NextSequenceNumber
  *
  * @return
  * Returns the NextSequenceNumber
  */
  UInt32_t& NextSequenceNumber();

  /*****************************************************************************/
  /** Get the EventQueueOverflowCount
  *
  * @return
  * Returns the EventQueueOverflowCount
  */
  const UInt32_t& EventQueueOverflowCount() const;

  /*****************************************************************************/
  /** Get the EventQueueOverflowCount
  *
  * @return
  * Returns the EventQueueOverflowCount
  */
  UInt32_t& EventQueueOverflowCount();
  
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
   * @param[out] SubscriptionDiagnosticsDataType_t& result
   * Decoded Subscription Diagnostics Data Type
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, SubscriptionDiagnosticsDataType_t& result);
};

/** @} */

} //namespace uasdk

#endif  //UASDK_INCLUDE_SUBSCRIPTION_DIAGNOSTICS

#endif /* _OPCUA_SUBSCRIPTION_DIAGNOSTICS_DATA_TYPE_T_H_ */
