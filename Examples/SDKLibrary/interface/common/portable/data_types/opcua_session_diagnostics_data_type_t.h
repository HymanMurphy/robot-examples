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

#ifndef _OPCUA_SESSION_DIAGNOSTICS_DATA_TYPE_T_H_
#define _OPCUA_SESSION_DIAGNOSTICS_DATA_TYPE_T_H_

#include "uasdk_includes.h"

#if (UASDK_INCLUDE_SESSION_DIAGNOSTICS > 0)

#include "opcua_structure_t.h"
#include "opcua_node_id_guid_t.h"
#include "opcua_uint32_t.h"
#include "opcua_duration_t.h"
#include "opcua_app_description_t.h"
#include "opcua_date_time_t.h"
#include "opcua_service_counter_data_type_t.h"

namespace uasdk
{
/** \addtogroup grpDataType
 *@{*/

/*****************************************************************************/
/** \brief SessionDiagnosticsDataType_t
 *
 * This class implements the Session Diagnostics Data Type
 *
 */
class SessionDiagnosticsDataType_t : public Structure_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(SessionDiagnosticsDataType_t);

private:

  /*****************************************************************************/
  /* @var NodeIdGuid_t sessionId
   * session id that session belongs to
   */
  NodeIdGuid_t sessionId;
  
  /*****************************************************************************/
  /* @var String_t sessionName
   * Session Name
   */
  String_t sessionName;
  
  /*****************************************************************************/
  /* @var AppDescription_t clientDescription
   * Session clientDescription
   */
  AppDescription_t clientDescription;

  /*****************************************************************************/
  /* @var String_t serverUri
  * Session serverUri 
  */
  String_t serverUri;

  /*****************************************************************************/
  /* @var String_t endpointUrl
  * Session endpointUrl 
  */
  String_t endpointUrl;

  /*****************************************************************************/
  /* @var String_t localeIds
  * Session localeIds
  */
  ArrayUA_t<String_t> localeIds;

  /*****************************************************************************/
  /* @var Duration_t actualSessionTimeout
  * Session actualSessionTimeout
  */
  Duration_t actualSessionTimeout;

  /*****************************************************************************/
  /* @var UInt32_t maxResponseMessageSize
  * Session maxResponseMessageSize.
  */
  UInt32_t maxResponseMessageSize;

  /*****************************************************************************/
  /* @var DateTime_t clientConnectionTime
  * Session clientConnectionTime
  */
  DateTime_t clientConnectionTime;

  /*****************************************************************************/
  /* @var DateTime_t clientLastContactTime
  * Session clientLastContactTime
  */
  DateTime_t clientLastContactTime;

  /*****************************************************************************/
  /* @var UInt32_t currentSubscriptionsCount
  * Session currentSubscriptionsCount.
  */
  UInt32_t currentSubscriptionsCount;

  /*****************************************************************************/
  /* @var UInt32_t currentMonitoredItemsCount
  * Session currentMonitoredItemsCount.
  */
  UInt32_t currentMonitoredItemsCount;

  /*****************************************************************************/
  /* @var UInt32_t currentPublishRequestsInQueue
  * Session currentPublishRequestsInQueue.
  */
  UInt32_t currentPublishRequestsInQueue;

  /*****************************************************************************/
  /* @var UInt32_t currentPublishTimerExpirations
  * Session currentPublishTimerExpirations.
  */
  UInt32_t currentPublishTimerExpirations;

  /*****************************************************************************/
  /* @var ServiceCounterDataType_t totalRequestsCount
  * Session totalRequestsCount.
  */
  ServiceCounterDataType_t totalRequestsCount;

  /*****************************************************************************/
  /* @var UInt32_t unauthorizedRequestsCount
  * Session unauthorizedRequestsCount.
  */
  UInt32_t unauthorizedRequestsCount;

  /*****************************************************************************/
  /* @var ServiceCounterDataType_t readCount
  * Session readCount.
  */
  ServiceCounterDataType_t readCount;

  /*****************************************************************************/
  /* @var ServiceCounterDataType_t historyReadCount
  * Session historyReadCount.
  */
  ServiceCounterDataType_t historyReadCount;

  /*****************************************************************************/
  /* @var ServiceCounterDataType_t writeCount
  * Session writeCount.
  */
  ServiceCounterDataType_t writeCount;

  /*****************************************************************************/
  /* @var ServiceCounterDataType_t historyUpdateCount
  * Session historyUpdateCount.
  */
  ServiceCounterDataType_t historyUpdateCount;

  /*****************************************************************************/
  /* @var ServiceCounterDataType_t callCount
  * Session callCount.
  */
  ServiceCounterDataType_t callCount;

  /*****************************************************************************/
  /* @var ServiceCounterDataType_t createMonitoredItemsCount
  * Session createMonitoredItemsCount.
  */
  ServiceCounterDataType_t createMonitoredItemsCount;

  /*****************************************************************************/
  /* @var ServiceCounterDataType_t modifyMonitoredItemsCount
  * Session modifyMonitoredItemsCount.
  */
  ServiceCounterDataType_t modifyMonitoredItemsCount;

  /*****************************************************************************/
  /* @var ServiceCounterDataType_t setMonitoringModeCount
  * Session setMonitoringModeCount.
  */
  ServiceCounterDataType_t setMonitoringModeCount;

  /*****************************************************************************/
  /* @var ServiceCounterDataType_t setTriggeringCount
  * Session setTriggeringCount.
  */
  ServiceCounterDataType_t setTriggeringCount;

  /*****************************************************************************/
  /* @var ServiceCounterDataType_t deleteMonitoredItemsCount
  * Session deleteMonitoredItemsCount.
  */
  ServiceCounterDataType_t deleteMonitoredItemsCount;

  /*****************************************************************************/
  /* @var ServiceCounterDataType_t createSubscriptionCount
  * Session createSubscriptionCount.
  */
  ServiceCounterDataType_t createSubscriptionCount;

  /*****************************************************************************/
  /* @var ServiceCounterDataType_t modifySubscriptionCount
  * Session modifySubscriptionCount.
  */
  ServiceCounterDataType_t modifySubscriptionCount;

  /*****************************************************************************/
  /* @var ServiceCounterDataType_t setPublishingModeCount
  * Session setPublishingModeCount.
  */
  ServiceCounterDataType_t setPublishingModeCount;

  /*****************************************************************************/
  /* @var ServiceCounterDataType_t publishCount
  * Session publishCount.
  */
  ServiceCounterDataType_t publishCount;

  /*****************************************************************************/
  /* @var ServiceCounterDataType_t republishCount
  * Session republishCount.
  */
  ServiceCounterDataType_t republishCount;

  /*****************************************************************************/
  /* @var ServiceCounterDataType_t transferSubscriptionsCount
  * Session transferSubscriptionsCount.
  */
  ServiceCounterDataType_t transferSubscriptionsCount;
  
  /*****************************************************************************/
  /* @var ServiceCounterDataType_t deleteSubscriptionsCount
  * Session deleteSubscriptionsCount.
  */
  ServiceCounterDataType_t deleteSubscriptionsCount;
  
  /*****************************************************************************/
  /* @var ServiceCounterDataType_t addNodesCount
  * Session addNodesCount.
  */
  ServiceCounterDataType_t addNodesCount;
  
  /*****************************************************************************/
  /* @var ServiceCounterDataType_t addReferencesCount
  * Session addReferencesCount.
  */
  ServiceCounterDataType_t addReferencesCount;
  
  /*****************************************************************************/
  /* @var ServiceCounterDataType_t deleteNodesCount
  * Session deleteNodesCount.
  */
  ServiceCounterDataType_t deleteNodesCount;
  
  /*****************************************************************************/
  /* @var ServiceCounterDataType_t deleteReferencesCount
  * Session deleteReferencesCount.
  */
  ServiceCounterDataType_t deleteReferencesCount;
  
  /*****************************************************************************/
  /* @var ServiceCounterDataType_t browseCount
  * Session browseCount.
  */
  ServiceCounterDataType_t browseCount;
  
  /*****************************************************************************/
  /* @var ServiceCounterDataType_t browseNextCount
  * Session browseNextCount.
  */
  ServiceCounterDataType_t browseNextCount;
  
  /*****************************************************************************/
  /* @var ServiceCounterDataType_t translateBrowsePathsToNodeIdsCount
  * Session translateBrowsePathsToNodeIdsCount.
  */
  ServiceCounterDataType_t translateBrowsePathsToNodeIdsCount;
  
  /*****************************************************************************/
  /* @var ServiceCounterDataType_t queryFirstCount
  * Session queryFirstCount.
  */
  ServiceCounterDataType_t queryFirstCount;
  
  /*****************************************************************************/
  /* @var ServiceCounterDataType_t queryNextCount
  * Session queryNextCount.
  */
  ServiceCounterDataType_t queryNextCount;
  
  /*****************************************************************************/
  /* @var ServiceCounterDataType_t registerNodesCount
  * Session registerNodesCount.
  */
  ServiceCounterDataType_t registerNodesCount;
  
  /*****************************************************************************/
  /* @var ServiceCounterDataType_t unregisterNodesCount
  * Session unregisterNodesCount.
  */
  ServiceCounterDataType_t unregisterNodesCount;

public:

  /*****************************************************************************/
  /* @var uint32_t TYPE_ID
   * Data type ID for ServerDiagnosticsSummaryDataType
   */
  static const uint32_t TYPE_ID = OpcUaId_SessionDiagnosticsDataType;

  /*****************************************************************************/
  /** Constructor for the class.
   *
   */
  SessionDiagnosticsDataType_t();
  
  /*****************************************************************************/
  /** Destructor for the class.
   *
   */
  virtual ~SessionDiagnosticsDataType_t();

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
   * @param[in] SessionDiagnosticsDataType_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are same
   * False - If the both the objects are not same
   */
  bool operator==(SessionDiagnosticsDataType_t const & obj) const;

  /*****************************************************************************/
  /** != operator overloading
   *
   * @param[in] SessionDiagnosticsDataType_t const & obj
   * Object to be compared with
   *
   * @return
   * True - If the both the objects are not same
   * False - If the both the objects are same
   */
  bool operator!=(SessionDiagnosticsDataType_t const & obj) const;

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
   * @param[in] SessionDiagnosticsDataType_t const & obj
   * Object to be compared with
   *
   * @return
   * True indicates that the LHS SessionDiagnosticsDataType_t object is greater than RHS SessionDiagnosticsDataType_t object
   */
  bool operator>(SessionDiagnosticsDataType_t const & obj) const;

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
   * @param[in] const SessionDiagnosticsDataType_t& source
   * Session Diagnostics Variable Data Type source object to copy from
   *
   * @return
   * Status of the operation
   */
  virtual Status_t CopyFrom(const SessionDiagnosticsDataType_t& source);

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
  /** Get the SessionName
   *
   * @return
   * Returns the SessionName
   */
  const String_t& SessionName() const;
  
  /*****************************************************************************/
  /** Get the SessionName
   *
   * @return
   * Returns the SessionName
   */
  String_t& SessionName();

  /*****************************************************************************/
  /** Get the ClientDescription
   *
   * @return
   * Returns the ClientDescription
   */
  const AppDescription_t& ClientDescription() const;
  
  /*****************************************************************************/
  /** Get the ClientDescription
   *
   * @return
   * Returns the ClientDescription
   */
  AppDescription_t& ClientDescription();

  /*****************************************************************************/
  /** Get the ServerUri
  *
  * @return
  * Returns the ServerUri
  */
  const String_t& ServerUri() const;

  /*****************************************************************************/
  /** Get the ServerUri
  *
  * @return
  * Returns the ServerUri
  */
  String_t& ServerUri();

  /*****************************************************************************/
  /** Get the EndpointUrl
  *
  * @return
  * Returns the EndpointUrl
  */
  const String_t& EndpointUrl() const;

  /*****************************************************************************/
  /** Get the EndpointUrl
  *
  * @return
  * Returns the EndpointUrl
  */
  String_t& EndpointUrl();

  /*****************************************************************************/
  /** Get the LocaleIds
  *
  * @return
  * Returns the LocaleIds
  */
  const ArrayUA_t<String_t>& LocaleIds() const;

  /*****************************************************************************/
  /** Get the LocaleIds
  *
  * @return
  * Returns the LocaleIds
  */
  ArrayUA_t<String_t>& LocaleIds();

  /*****************************************************************************/
  /** Get the ActualSessionTimeout
  *
  * @return
  * Returns the ActualSessionTimeout
  */
  const Duration_t& ActualSessionTimeout() const;

  /*****************************************************************************/
  /** Get the ActualSessionTimeout
  *
  * @return
  * Returns the ActualSessionTimeout
  */
  Duration_t& ActualSessionTimeout();

  /*****************************************************************************/
  /** Get the MaxResponseMessageSize
  *
  * @return
  * Returns the MaxResponseMessageSize
  */
  const UInt32_t& MaxResponseMessageSize() const;

  /*****************************************************************************/
  /** Get the MaxResponseMessageSize
  *
  * @return
  * Returns the MaxResponseMessageSize
  */
  UInt32_t& MaxResponseMessageSize();

  /*****************************************************************************/
  /** Get the ClientConnectionTime
  *
  * @return
  * Returns the ClientConnectionTime
  */
  const DateTime_t& ClientConnectionTime() const;

  /*****************************************************************************/
  /** Get the ClientConnectionTime
  *
  * @return
  * Returns the ClientConnectionTime
  */
  DateTime_t& ClientConnectionTime();

  /*****************************************************************************/
  /** Get the ClientLastContactTime
  *
  * @return
  * Returns the ClientLastContactTime
  */
  const DateTime_t& ClientLastContactTime() const;

  /*****************************************************************************/
  /** Get the ClientLastContactTime
  *
  * @return
  * Returns the ClientLastContactTime
  */
  DateTime_t& ClientLastContactTime();

  /*****************************************************************************/
  /** Get the CurrentSubscriptionsCount
  *
  * @return
  * Returns the CurrentSubscriptionsCount
  */
  const UInt32_t& CurrentSubscriptionsCount() const;

  /*****************************************************************************/
  /** Get the CurrentSubscriptionsCount
  *
  * @return
  * Returns the CurrentSubscriptionsCount
  */
  UInt32_t& CurrentSubscriptionsCount();

  /*****************************************************************************/
  /** Get the CurrentMonitoredItemsCount
  *
  * @return
  * Returns the CurrentMonitoredItemsCount
  */
  const UInt32_t& CurrentMonitoredItemsCount() const;

  /*****************************************************************************/
  /** Get the CurrentMonitoredItemsCount
  *
  * @return
  * Returns the CurrentMonitoredItemsCount
  */
  UInt32_t& CurrentMonitoredItemsCount();

  /*****************************************************************************/
  /** Get the CurrentPublishRequestsInQueue
  *
  * @return
  * Returns the CurrentPublishRequestsInQueue
  */
  const UInt32_t& CurrentPublishRequestsInQueue() const;

  /*****************************************************************************/
  /** Get the CurrentPublishRequestsInQueue
  *
  * @return
  * Returns the CurrentPublishRequestsInQueue
  */
  UInt32_t& CurrentPublishRequestsInQueue();

  /*****************************************************************************/
  /** Get the CurrentPublishTimerExpirations
  *
  * @return
  * Returns the CurrentPublishTimerExpirations
  */
  const UInt32_t& CurrentPublishTimerExpirations() const;

  /*****************************************************************************/
  /** Get the CurrentPublishTimerExpirations
  *
  * @return
  * Returns the CurrentPublishTimerExpirations
  */
  UInt32_t& CurrentPublishTimerExpirations();

  /*****************************************************************************/
  /** Get the TotalRequestsCount
  *
  * @return
  * Returns the TotalRequestsCount
  */
  const ServiceCounterDataType_t& TotalRequestsCount() const;

  /*****************************************************************************/
  /** Get the TotalRequestsCount
  *
  * @return
  * Returns the TotalRequestsCount
  */
  ServiceCounterDataType_t& TotalRequestsCount();

  /*****************************************************************************/
  /** Get the UnauthorizedRequestsCount
  *
  * @return
  * Returns the UnauthorizedRequestsCount
  */
  const UInt32_t& UnauthorizedRequestsCount() const;

  /*****************************************************************************/
  /** Get the UnauthorizedRequestsCount
  *
  * @return
  * Returns the UnauthorizedRequestsCount
  */
  UInt32_t& UnauthorizedRequestsCount();

  /*****************************************************************************/
  /** Get the ReadCount
  *
  * @return
  * Returns the ReadCount
  */
  const ServiceCounterDataType_t& ReadCount() const;

  /*****************************************************************************/
  /** Get the ReadCount
  *
  * @return
  * Returns the ReadCount
  */
  ServiceCounterDataType_t& ReadCount();

  /*****************************************************************************/
  /** Get the HistoryReadCount
  *
  * @return
  * Returns the HistoryReadCount
  */
  const ServiceCounterDataType_t& HistoryReadCount() const;

  /*****************************************************************************/
  /** Get the HistoryReadCount
  *
  * @return
  * Returns the HistoryReadCount
  */
  ServiceCounterDataType_t& HistoryReadCount();

  /*****************************************************************************/
  /** Get the WriteCount
  *
  * @return
  * Returns the WriteCount
  */
  const ServiceCounterDataType_t& WriteCount() const;

  /*****************************************************************************/
  /** Get the WriteCount
  *
  * @return
  * Returns the WriteCount
  */
  ServiceCounterDataType_t& WriteCount();

  /*****************************************************************************/
  /** Get the HistoryUpdateCount
  *
  * @return
  * Returns the HistoryUpdateCount
  */
  const ServiceCounterDataType_t& HistoryUpdateCount() const;

  /*****************************************************************************/
  /** Get the HistoryUpdateCount
  *
  * @return
  * Returns the HistoryUpdateCount
  */
  ServiceCounterDataType_t& HistoryUpdateCount();

  /*****************************************************************************/
  /** Get the CallCount
  *
  * @return
  * Returns the CallCount
  */
  const ServiceCounterDataType_t& CallCount() const;

  /*****************************************************************************/
  /** Get the CallCount
  *
  * @return
  * Returns the CallCount
  */
  ServiceCounterDataType_t& CallCount();

  /*****************************************************************************/
  /** Get the CreateMonitoredItemsCount
  *
  * @return
  * Returns the CreateMonitoredItemsCount
  */
  const ServiceCounterDataType_t& CreateMonitoredItemsCount() const;

  /*****************************************************************************/
  /** Get the CreateMonitoredItemsCount
  *
  * @return
  * Returns the CreateMonitoredItemsCount
  */
  ServiceCounterDataType_t& CreateMonitoredItemsCount();

  /*****************************************************************************/
  /** Get the ModifyMonitoredItemsCount
  *
  * @return
  * Returns the ModifyMonitoredItemsCount
  */
  const ServiceCounterDataType_t& ModifyMonitoredItemsCount() const;

  /*****************************************************************************/
  /** Get the ModifyMonitoredItemsCount
  *
  * @return
  * Returns the ModifyMonitoredItemsCount
  */
  ServiceCounterDataType_t& ModifyMonitoredItemsCount();

  /*****************************************************************************/
  /** Get the SetMonitoringModeCount
  *
  * @return
  * Returns the SetMonitoringModeCount
  */
  const ServiceCounterDataType_t& SetMonitoringModeCount() const;

  /*****************************************************************************/
  /** Get the SetMonitoringModeCount
  *
  * @return
  * Returns the SetMonitoringModeCount
  */
  ServiceCounterDataType_t& SetMonitoringModeCount();

  /*****************************************************************************/
  /** Get the SetTriggeringCount
  *
  * @return
  * Returns the SetTriggeringCount
  */
  const ServiceCounterDataType_t& SetTriggeringCount() const;

  /*****************************************************************************/
  /** Get the SetTriggeringCount
  *
  * @return
  * Returns the SetTriggeringCount
  */
  ServiceCounterDataType_t& SetTriggeringCount();

  /*****************************************************************************/
  /** Get the DeleteMonitoredItemsCount
  *
  * @return
  * Returns the DeleteMonitoredItemsCount
  */
  const ServiceCounterDataType_t& DeleteMonitoredItemsCount() const;

  /*****************************************************************************/
  /** Get the DeleteMonitoredItemsCount
  *
  * @return
  * Returns the DeleteMonitoredItemsCount
  */
  ServiceCounterDataType_t& DeleteMonitoredItemsCount();

  /*****************************************************************************/
  /** Get the CreateSubscriptionCount
  *
  * @return
  * Returns the CreateSubscriptionCount
  */
  const ServiceCounterDataType_t& CreateSubscriptionCount() const;

  /*****************************************************************************/
  /** Get the CreateSubscriptionCount
  *
  * @return
  * Returns the CreateSubscriptionCount
  */
  ServiceCounterDataType_t& CreateSubscriptionCount();

  /*****************************************************************************/
  /** Get the ModifySubscriptionCount
  *
  * @return
  * Returns the ModifySubscriptionCount
  */
  const ServiceCounterDataType_t& ModifySubscriptionCount() const;

  /*****************************************************************************/
  /** Get the ModifySubscriptionCount
  *
  * @return
  * Returns the ModifySubscriptionCount
  */
  ServiceCounterDataType_t& ModifySubscriptionCount();

  /*****************************************************************************/
  /** Get the SetPublishingModeCount
  *
  * @return
  * Returns the SetPublishingModeCount
  */
  const ServiceCounterDataType_t& SetPublishingModeCount() const;

  /*****************************************************************************/
  /** Get the SetPublishingModeCount
  *
  * @return
  * Returns the SetPublishingModeCount
  */
  ServiceCounterDataType_t& SetPublishingModeCount();
 
  /*****************************************************************************/
  /** Get the PublishCount
  *
  * @return
  * Returns the PublishCount
  */
  const ServiceCounterDataType_t& PublishCount() const;

  /*****************************************************************************/
  /** Get the PublishCount
  *
  * @return
  * Returns the PublishCount
  */
  ServiceCounterDataType_t& PublishCount();

  /*****************************************************************************/
  /** Get the RepublishCount
  *
  * @return
  * Returns the RepublishCount
  */
  const ServiceCounterDataType_t& RepublishCount() const;

  /*****************************************************************************/
  /** Get the RepublishCount
  *
  * @return
  * Returns the RepublishCount
  */
  ServiceCounterDataType_t& RepublishCount();
  
  /*****************************************************************************/
  /** Get the TransferSubscriptionsCount
  *
  * @return
  * Returns the TransferSubscriptionsCount
  */
  const ServiceCounterDataType_t& TransferSubscriptionsCount() const;

  /*****************************************************************************/
  /** Get the TransferSubscriptionsCount
  *
  * @return
  * Returns the TransferSubscriptionsCount
  */
  ServiceCounterDataType_t& TransferSubscriptionsCount();
  
  /*****************************************************************************/
  /** Get the DeleteSubscriptionsCount
  *
  * @return
  * Returns the DeleteSubscriptionsCount
  */
  const ServiceCounterDataType_t& DeleteSubscriptionsCount() const;

  /*****************************************************************************/
  /** Get the DeleteSubscriptionsCount
  *
  * @return
  * Returns the DeleteSubscriptionsCount
  */
  ServiceCounterDataType_t& DeleteSubscriptionsCount();
  
  /*****************************************************************************/
  /** Get the AddNodesCount
  *
  * @return
  * Returns the AddNodesCount
  */
  const ServiceCounterDataType_t& AddNodesCount() const;

  /*****************************************************************************/
  /** Get the AddNodesCount
  *
  * @return
  * Returns the AddNodesCount
  */
  ServiceCounterDataType_t& AddNodesCount();
  
  /*****************************************************************************/
  /** Get the AddReferencesCount
  *
  * @return
  * Returns the AddReferencesCount
  */
  const ServiceCounterDataType_t& AddReferencesCount() const;

  /*****************************************************************************/
  /** Get the AddReferencesCount
  *
  * @return
  * Returns the AddReferencesCount
  */
  ServiceCounterDataType_t& AddReferencesCount();
  
  /*****************************************************************************/
  /** Get the DeleteNodesCount
  *
  * @return
  * Returns the DeleteNodesCount
  */
  const ServiceCounterDataType_t& DeleteNodesCount() const;

  /*****************************************************************************/
  /** Get the DeleteNodesCount
  *
  * @return
  * Returns the DeleteNodesCount
  */
  ServiceCounterDataType_t& DeleteNodesCount();
  
  /*****************************************************************************/
  /** Get the DeleteReferencesCount
  *
  * @return
  * Returns the DeleteReferencesCount
  */
  const ServiceCounterDataType_t& DeleteReferencesCount() const;

  /*****************************************************************************/
  /** Get the DeleteReferencesCount
  *
  * @return
  * Returns the DeleteReferencesCount
  */
  ServiceCounterDataType_t& DeleteReferencesCount();
  
  /*****************************************************************************/
  /** Get the BrowseCount
  *
  * @return
  * Returns the BrowseCount
  */
  const ServiceCounterDataType_t& BrowseCount() const;

  /*****************************************************************************/
  /** Get the BrowseCount
  *
  * @return
  * Returns the BrowseCount
  */
  ServiceCounterDataType_t& BrowseCount();
  
  /*****************************************************************************/
  /** Get the BrowseNextCount
  *
  * @return
  * Returns the BrowseNextCount
  */
  const ServiceCounterDataType_t& BrowseNextCount() const;

  /*****************************************************************************/
  /** Get the BrowseNextCount
  *
  * @return
  * Returns the BrowseNextCount
  */
  ServiceCounterDataType_t& BrowseNextCount();
  
  /*****************************************************************************/
  /** Get the TranslateBrowsePathsToNodeIdsCount
  *
  * @return
  * Returns the TranslateBrowsePathsToNodeIdsCount
  */
  const ServiceCounterDataType_t& TranslateBrowsePathsToNodeIdsCount() const;

  /*****************************************************************************/
  /** Get the TranslateBrowsePathsToNodeIdsCount
  *
  * @return
  * Returns the TranslateBrowsePathsToNodeIdsCount
  */
  ServiceCounterDataType_t& TranslateBrowsePathsToNodeIdsCount();
  
  /*****************************************************************************/
  /** Get the QueryFirstCount
  *
  * @return
  * Returns the QueryFirstCount
  */
  const ServiceCounterDataType_t& QueryFirstCount() const;

  /*****************************************************************************/
  /** Get the QueryFirstCount
  *
  * @return
  * Returns the QueryFirstCount
  */
  ServiceCounterDataType_t& QueryFirstCount();
  /*****************************************************************************/
  /** Get the QueryNextCount
  *
  * @return
  * Returns the QueryNextCount
  */
  const ServiceCounterDataType_t& QueryNextCount() const;

  /*****************************************************************************/
  /** Get the QueryNextCount
  *
  * @return
  * Returns the QueryNextCount
  */
  ServiceCounterDataType_t& QueryNextCount();
  
  /*****************************************************************************/
  /** Get the RegisterNodesCount
  *
  * @return
  * Returns the RegisterNodesCount
  */
  const ServiceCounterDataType_t& RegisterNodesCount() const;

  /*****************************************************************************/
  /** Get the RegisterNodesCount
  *
  * @return
  * Returns the RegisterNodesCount
  */
  ServiceCounterDataType_t& RegisterNodesCount();
  
  /*****************************************************************************/
  /** Get the UnregisterNodesCount
  *
  * @return
  * Returns the UnregisterNodesCount
  */
  const ServiceCounterDataType_t& UnregisterNodesCount() const;

  /*****************************************************************************/
  /** Get the UnregisterNodesCount
  *
  * @return
  * Returns the UnregisterNodesCount
  */
  ServiceCounterDataType_t& UnregisterNodesCount();

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
   * @param[out] ServiceCounterDataType_t& result
   * Decoded Subscription Diagnostics Data Type
   *
   * @return
   * Returns status of the operation
   */
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, SessionDiagnosticsDataType_t& result);
};

/** @} */

} //namespace uasdk

#endif  //UASDK_INCLUDE_SUBSCRIPTION_DIAGNOSTICS

#endif /* _OPCUA_SUBSCRIPTION_DIAGNOSTICS_DATA_TYPE_T_H_ */
