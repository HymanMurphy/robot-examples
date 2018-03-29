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

#ifndef _ISERVER_CONFIGURATION_T_
#define _ISERVER_CONFIGURATION_T_

#include "uasdk_includes.h"
#include "allocatable_t.h"
#include "iref_count_t.h"
#include "opcua_message_security_mode_t.h"
#include "intrusive_list_t.h"
#include "opcua_user_identity_token_type_t.h"
#include "isession_listener_t.h"
#include "opcua_duration_t.h"

#if (UASDK_INCLUDE_SERVER > 0)
namespace uasdk
{

class BuildInfo_t;
class UserIdentityTokenType_t;
class IUserPermissionsProvider_t;
class IServerStateListener_t;
class IAddressSpace_t;
class ServerCertificateValidationOptions_t;
class ICertificatePrivateKeyPasswordProvider_t;
class ICertificateRejectedListListener_t;
class IRegisterNodeListener_t;
class ITransactionListener_t;
class IMonitoredItemListener_t;
class ILogListener_t;
#if (UASDK_INCLUDE_SECURITY > 0)
class ApplicationInstanceCertificate_t;
#endif

#if (UASDK_INCLUDE_EVENTS > 0)
class IEventIdGenerator_t;
class IEventDispatcher_t;
class TimeZoneDataType_t;
#endif  //(UASDK_INCLUDE_EVENTS > 0)

#if (UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0)
class IConditionRegistrar_t;
#endif  //(UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0)

template<typename T> class ArrayUA_t;

/** \addtogroup grpServer
 *@{*/

/*****************************************************************************/
/** \brief Server Configuration
 *
 * A class provides interface to the server configuration
 *
 */
class IServerConfiguration_t : public IRefCount_t
{
public:

  /*****************************************************************************/
  /** Get the maximum browse continuation points
   *
   * @return
   * Returns maximum browse continuation points
   */
  virtual uint32_t CapabilitiesMaxBrowseContinuationPoints(void) const = 0;

  /*****************************************************************************/
  /** Set the maximum browse continuation points
   *
   * @param[in] value
   * The Maximum Browse Continuation Points to be set
   */
  virtual void CapabilitiesMaxBrowseContinuationPoints(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Maximum Query Continuation Points
   *
   * @return
   * Returns Maximum Query Continuation Points
   */
  virtual uint32_t CapabilitiesMaxQueryContinuationPoints(void) const = 0;

  /*****************************************************************************/
  /** Set the Maximum Query Continuation Points
   *
   * @param[in] value
   * The Maximum Query Continuation Point to be set
   */
  virtual void CapabilitiesMaxQueryContinuationPoints(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Maximum History Continuation Points
   *
   * @return
   * Returns Maximum History Continuation Points
   */
  virtual uint32_t CapabilitiesMaxHistoryContinuationPoints(void) const = 0;

  /*****************************************************************************/
  /** Set the Maximum History Continuation Points
   *
   * @param[in] value
   * The Maximum History Continuation Points to be set
   */
  virtual void CapabilitiesMaxHistoryContinuationPoints(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Maximum Array Length
   *
   * @return
   * Returns the Maximum Array Length
   */
  virtual uint32_t CapabilitiesMaxArrayLength(void) const = 0;

  /*****************************************************************************/
  /** Set the Maximum Array Length
   *
   * @param[in] value
   * The Maximum Array Length to be set
   */
  virtual void CapabilitiesMaxArrayLength(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Maximum String Length
   *
   * @return
   * Returns the Maximum String Length
   */
  virtual uint32_t CapabilitiesMaxStringLength(void) const = 0;

  /*****************************************************************************/
  /** Set the Maximum String Length
   *
   * @param[in] value
   * The Maximum String Length to be set
   */
  virtual void CapabilitiesMaxStringLength(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Operation Limits Enforce
   *
   * @return
   * Returns the Operation Limits Enforce
   */
  virtual bool OperationLimitsEnforce(void) const = 0;

  /*****************************************************************************/
  /** Set the Operation Limits Enforce
   *
   * @param[in] value
   * The Operation Limits Enforce to be set
   */
  virtual void OperationLimitsEnforce(bool value) = 0;

  /*****************************************************************************/
  /** Get the Maximum Nodes per Read
   *
   * @return
   * Returns the Maximum Nodes per Read
   */
  virtual uint32_t OperationLimitsMaxNodesPerRead(void) const = 0;

  /*****************************************************************************/
  /** Set the Maximum Nodes per Read
   *
   * @param[in] value
   * The Maximum Nodes per Read to be set
   */
  virtual void OperationLimitsMaxNodesPerRead(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Maximum Nodes per History Read Data
   *
   * @return
   * Returns the Maximum Nodes per History Read Data
   */
  virtual uint32_t OperationLimitsMaxNodesPerHistoryReadData(void) const = 0;

  /*****************************************************************************/
  /** Set the Maximum Nodes per History Read Data
   *
   * @param[in] value
   * The Maximum Nodes per History Read Data to be set
   */
  virtual void OperationLimitsMaxNodesPerHistoryReadData(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Maximum Nodes per History Read Events
   *
   * @return
   * Returns the Maximum Nodes per History Read Events
   */
  virtual uint32_t OperationLimitsMaxNodesPerHistoryReadEvents(void) const = 0;

  /*****************************************************************************/
  /** Set the Maximum Nodes per History Read Events
   *
   * @param[in] value
   * The Maximum Nodes per History Read Events to be set
   */
  virtual void OperationLimitsMaxNodesPerHistoryReadEvents(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Maximum Nodes per Write
   *
   * @return
   * Returns the Maximum Nodes per Write
   */
  virtual uint32_t OperationLimitsMaxNodesPerWrite(void) const = 0;

  /*****************************************************************************/
  /** Set the Maximum Nodes per Write
   *
   * @param[in] value
   * The Maximum Nodes per Write to be set
   */
  virtual void OperationLimitsMaxNodesPerWrite(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Maximum Nodes per History Update Data
   *
   * @return
   * Returns the Maximum Nodes per History Update Data
   */
  virtual uint32_t OperationLimitsMaxNodesPerHistoryUpdateData(void) const = 0;

  /*****************************************************************************/
  /** Set the Maximum Nodes per Write
   *
   * @param[in] value
   * The Maximum Nodes per History Update Data to be set
   */
  virtual void OperationLimitsMaxNodesPerHistoryUpdateData(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Maximum Nodes per History Update Events
   *
   * @return
   * Returns the Maximum Nodes per History Update Events
   */
  virtual uint32_t OperationLimitsMaxNodesPerHistoryUpdateEvents(void) const = 0;

  /*****************************************************************************/
  /** Set the Maximum Nodes per History Update Events
   *
   * @param[in] value
   * The Maximum Nodes per History Update Events to be set
   */
  virtual void OperationLimitsMaxNodesPerHistoryUpdateEvents(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Maximum Nodes per Method Call
   *
   * @return
   * Returns the Maximum Nodes per Method Call
   */
  virtual uint32_t OperationLimitsMaxNodesPerMethodCall(void) const = 0;

  /*****************************************************************************/
  /** Set the Maximum Nodes per Method Call
   *
   * @param[in] value
   * The Maximum Nodes per Method Call to be set
   */
  virtual void OperationLimitsMaxNodesPerMethodCall(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Maximum Nodes per Browse
   *
   * @return
   * Returns the Maximum Nodes per Browse
   */
  virtual uint32_t OperationLimitsMaxNodesPerBrowse(void) const = 0;

  /*****************************************************************************/
  /** Set the Maximum Nodes per Browse
   *
   * @param[in] value
   * The Maximum Nodes per Browse to be set
   */
  virtual void OperationLimitsMaxNodesPerBrowse(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Maximum Nodes per RegisterNodes
   *
   * @return
   * Returns the Maximum Nodes per RegisterNodes
   */
  virtual uint32_t OperationLimitsMaxNodesPerRegisterNodes(void) const = 0;

  /*****************************************************************************/
  /** Set the Maximum Nodes per RegisterNodes
   *
   * @param[in] value
   * The Maximum Nodes per RegisterNodes to be set
   */
  virtual void OperationLimitsMaxNodesPerRegisterNodes(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Maximum Nodes per TranslateBrowsePathsToNodeIds
   *
   * @return
   * Returns the Maximum Nodes per TranslateBrowsePathsToNodeIds
   */
  virtual uint32_t OperationLimitsMaxNodesPerTranslateBrowsePathsToNodeIds(void) const = 0;

  /*****************************************************************************/
  /** Set the Maximum Nodes per TranslateBrowsePathsToNodeIds
   *
   * @param[in] value
   * The Maximum Nodes per TranslateBrowsePathsToNodeIds to be set
   */
  virtual void OperationLimitsMaxNodesPerTranslateBrowsePathsToNodeIds(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Maximum Nodes per Node Management
   *
   * @return
   * Returns the Maximum Nodes per Node Management
   */
  virtual uint32_t OperationLimitsMaxNodesPerNodeManagement(void) const = 0;

  /*****************************************************************************/
  /** Set the Maximum Nodes per Node Management
   *
   * @param[in] value
   * The Maximum Nodes per Node Management to be set
   */
  virtual void OperationLimitsMaxNodesPerNodeManagement(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Maximum Monitored Items per call
   *
   * @return
   * Returns the Maximum Monitored Items per call
   */
  virtual uint32_t OperationLimitsMaxMonitoredItemsPerCall(void) const = 0;

  /*****************************************************************************/
  /** Set the Maximum Monitored Items per call
   *
   * @param[in] value
   * The Maximum Monitored Items per call to be set
   */
  virtual void OperationLimitsMaxMonitoredItemsPerCall(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Discovery Endpoint enable status
   *
   * @return
   * Returns the Discovery Endpoint enabled status
   */
  virtual bool DiscoveryEndpointEnable(void) const = 0;

  /*****************************************************************************/
  /** Enable/Disable discovery Endpoint
   *
   * @param[in] value
   * Discovery Endpoint Enable/Disable
   */
  virtual void DiscoveryEndpointEnable(bool value) = 0;

  /*****************************************************************************/
  /** Get the Discovery Endpoint TCP port
   *
   * @return
   * Returns the Discovery Endpoint TCP port
   */
  virtual uint32_t DiscoveryEndpointTCPPort(void) const = 0;

  /*****************************************************************************/
  /** Set the Discovery Endpoint TCP port
   *
   * @param[in] value
   * The Discovery Endpoint TCP port to be set
   */
  virtual void DiscoveryEndpointTCPPort(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Server Endpoint TCP port
   *
   * @return
   * Returns the Server Endpoint TCP port
   */
  virtual uint32_t ServerEndpointTCPPort(void) const = 0;

  /*****************************************************************************/
  /** Set the Server Endpoint TCP port
   *
   * @param[in] value
   * The Server Endpoint TCP port to be set
   */
  virtual void ServerEndpointTCPPort(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Connection Timeout in Milliseconds
   *
   * @return
   * Returns the Connection Timeout in Milliseconds
   */
  virtual uint32_t TCPBinaryConnectionTimeoutInMs(void) const = 0;

  /*****************************************************************************/
  /** Set the Connection Timeout in Milliseconds
   *
   * @param[in] value
   * The Connection Timeout in Milliseconds to be set
   */
  virtual void TCPBinaryConnectionTimeoutInMs(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Maximum TCP Binary Message Size
   *
   * @return
   * Returns the Maximum TCP Binary Message Size
   */
  virtual uint32_t TCPBinaryMaxMessageSize(void) const = 0;

  /*****************************************************************************/
  /** Set the Maximum TCP Binary Message Size
   *
   * @param[in] value
   * The Maximum TCP Binary Message Size to be set
   */
  virtual void TCPBinaryMaxMessageSize(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the  Maximum TCP Binary Message Chunk Size
   *
   * @return
   * Returns the  Maximum TCP Binary Message Chunk Size
   */
  virtual uint32_t TCPBinaryMaxMessageChunkSize(void) const = 0;

  /*****************************************************************************/
  /** Set the  Maximum TCP Binary Message Chunk Size
   *
   * @param[in] value
   * The  Maximum TCP Binary Message Chunk Size to be set
   */
  virtual void TCPBinaryMaxMessageChunkSize(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Maximum TCP Binary Message Chunk Count
   *
   * @return
   * Returns the Maximum TCP Binary Message Chunk Count
   */
  virtual uint32_t TCPBinaryMaxChunkCount(void) const = 0;


  /*****************************************************************************/
  /** Set the Maximum TCP Binary Message Chunk Count
   *
   * @param[in] value
   * The Maximum TCP Binary Message Chunk Count to be set
   */
  virtual void TCPBinaryMaxChunkCount(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Maximum TCP Binary connections
   *
   * @return
   * Returns the Maximum TCP Binary connections
   */
  virtual uint32_t TCPBinaryMaxConnections(void) const = 0;

  /*****************************************************************************/
  /** Set the Maximum TCP Binary connections
   *
   * @param[in] value
   * The Maximum TCP Binary connections to be set
   */
  virtual void TCPBinaryMaxConnections(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Minimum Revised Channel Lifetime in Millisecond
   *
   * @return
   * Returns the Minimum Revised Channel Lifetime in Millisecond
   */
  virtual uint32_t SecureChannelMinRevisedChannelLifetimeInMs(void) const = 0;

  /*****************************************************************************/
  /** Set the Minimum Revised Channel Lifetime in Millisecond
   *
   * @param[in] value
   * The Minimum Revised Channel Lifetime in Millisecond to be set
   */
  virtual void SecureChannelMinRevisedChannelLifetimeInMs(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Maximum Revised Channel Lifetime in Millisecond
   *
   * @return
   * Returns the Maximum Revised Channel Lifetime in Millisecond
   */
  virtual uint32_t SecureChannelMaxRevisedChannelLifetimeInMs(void) const = 0;

  /*****************************************************************************/
  /** Set the Maximum Revised Channel Lifetime in Millisecond
   *
   * @param[in] value
   * The Maximum Revised Channel Lifetime in Millisecond to be set
   */
  virtual void SecureChannelMaxRevisedChannelLifetimeInMs(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Maximum Secure Channels
   *
   * @return
   * Returns the Maximum Secure Channels
   */
  virtual uint32_t SecureChannelMaxChannels(void) const = 0;

  /*****************************************************************************/
  /** Set the Maximum Secure Channels
   *
   * @param[in] value
   * The Maximum Secure Channels to be set
   */
  virtual void SecureChannelMaxChannels(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Server cyclic rate in Millisecond
   *
   * @return
   * Returns the Server cyclic rate in Millisecond
   */
  virtual uint32_t ServerCyclicRateInMs(void) const = 0;

  /*****************************************************************************/
  /** Set the Get the Server cyclic rate in Millisecond
   *
   * @param[in] value
   * The Server cyclic rate in Millisecond to be set
   */
  virtual void ServerCyclicRateInMs(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Minimum Revised Session Timeout in Millisecond
   *
   * @return
   * Returns the Minimum Revised Session Timeout in Millisecond
   */
  virtual uint32_t MinRevisedSessionTimeoutInMs(void) const = 0;

  /*****************************************************************************/
  /** Set the Minimum Revised Session Timeout in Millisecond
   *
   * @param[in] value
   * The Minimum Revised Session Timeout in Millisecond to be set
   */
  virtual void MinRevisedSessionTimeoutInMs(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Maximum Revised Session Timeout in Millisecond
   *
   * @return
   * Returns the Maximum Revised Session Timeout in Millisecond
   */
  virtual uint32_t MaxRevisedSessionTimeoutInMs(void) const = 0;

  /*****************************************************************************/
  /** Set the Maximum Revised Session Timeout in Millisecond
   *
   * @param[in] value
   * The Maximum Revised Session Timeout in Millisecond to be set
   */
  virtual void MaxRevisedSessionTimeoutInMs(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Maximum Sessions
   *
   * @return
   * Returns the Maximum Sessions
   */
  virtual uint32_t MaxSessions(void) const = 0;

  /*****************************************************************************/
  /** Set the Maximum Sessions
   *
   * @param[in] value
   * The Maximum Sessions to be set
   */
  virtual void MaxSessions(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Maximum Subscriptions per Session
   *
   * @return
   * Returns the Maximum Subscriptions per Session
   */
  virtual uint32_t MaxSubscriptionsPerSession(void) const = 0;

  /*****************************************************************************/
  /** Set the Maximum Subscriptions per Session
   *
   * @param[in] value
   * The Maximum Subscriptions per Session to be set
   */
  virtual void MaxSubscriptionsPerSession(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Minimum Subscription Maximum Keep Alive Count
   *
   * @return
   * Returns the Minimum Subscription Max Keep Alive Count
   */
  virtual uint32_t MinMaxKeepAliveCount(void) const = 0;

  /*****************************************************************************/
  /** Set the Minimum Subscription Maximum Keep Alive Count
   *
   * @param[in] value
   * The Minimum Subscription Max Keep Alive Count to be set
   */
  virtual void MinMaxKeepAliveCount(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Maximum Subscription Maximum Keep Alive Count
   *
   * @return
   * Returns the Maximum Subscription Maximum Keep Alive Count
   */
  virtual uint32_t MaxMaxKeepAliveCount(void) const = 0;

  /*****************************************************************************/
  /** Set Maximum Subscription Maximum Keep Alive Count
   *
   * @param[in] value
   * The Maximum Subscription Maximum Keep Alive Count to be set
   */
  virtual void MaxMaxKeepAliveCount(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Maximum Notification Retransmission Queue Size
   *
   * @return
   * Returns the Maximum Notification Retransmission Queue Size
   */
  virtual uint32_t MaxNotificationRetransmissionQueueSize(void) const = 0;

  /*****************************************************************************/
  /** Set the Maximum Notification Retransmission Queue Size
   *
   * @param[in] value
   * The Maximum Notification Retransmission Queue Size to be set
   */
  virtual void MaxNotificationRetransmissionQueueSize(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Maximum Publish Requests per Session which must be
   * greater than MAX_SUBSCRIPTIONS_PER_SESSION
   *
   * @return
   * Returns the Maximum Publish Requests per Session
   */
  virtual uint32_t MaxPublishRequestsPerSession(void) const = 0;

  /*****************************************************************************/
  /** Set the Maximum Publish Requests per Session which must be
   * greater than MAX_SUBSCRIPTIONS_PER_SESSION
   *
   * @param[in] value
   * The Maximum Publish Requests per Session to be set
   */
  virtual void MaxPublishRequestsPerSession(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Maximum browse references to return per node
   *
   * @return
   * Returns the Maximum browse references
   */
  virtual uint32_t MaxBrowseRefsPerNode(void) const = 0;

  /*****************************************************************************/
  /** Set the Maximum browse references to return per node
   *
   * @param[in] value
   * The Maximum Maximum browse references
   */
  virtual void MaxBrowseRefsPerNode(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Maximum Total Monitored Items (including all sessions)
   *
   * @return
   * Returns the Maximum Total Monitored Items
   */
  virtual uint32_t MaxMonitoredItems(void) const = 0;

  /*****************************************************************************/
  /** Set the Maximum Total Monitored Items (including all sessions)
   *
   * @param[in] value
   * The Maximum Total Monitored Items to be set
   */
  virtual void MaxMonitoredItems(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Maximum Monitored Items Queue Size
   *
   * @return
   * Returns the Maximum Monitored Items Queue Size
   */
  virtual uint32_t MaxMonItemQueueSize(void) const = 0;

  /*****************************************************************************/
  /** Set the Maximum Monitored Items Queue Size
   *
   * @param[in] value
   * The Maximum Monitored Items Queue Size to be set
   */
  virtual void MaxMonItemQueueSize(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Disable percent deadband filter support status
   *
   * @return
   * Returns the Disable percent deadband filter support status
   */
  virtual bool PercentDeadbandDisable(void) const = 0;

  /*****************************************************************************/
  /** Disable/Enable percent deadband filter support
   *
   * @param[in] value
   * Disable/Enable
   */
  virtual void PercentDeadbandDisable(bool value) = 0;

  /*****************************************************************************/
  /** Get the Disable percent deadband filter support status for all arrays
   *
   * @return
   * Returns the Disable percent deadband filter support status for all arrays
   */
  virtual bool PercentDeadbandVectorsDisable(void) const = 0;

  /*****************************************************************************/
  /** Disable/Enable percent deadband filter support status for all arrays
   *
   * @param[in] value
   * Disable/Enable
   */
  virtual void PercentDeadbandVectorsDisable(bool value) = 0;

  /*****************************************************************************/
  /** Get the Disable percent deadband filter support for all floating point values
   *
   * @return
   * Returns the Disable percent deadband filter support for all floating point values
   */
  virtual bool PercentDeadbandFloatingPointDisable(void) const = 0;

  /*****************************************************************************/
  /** Disable/Enable percent deadband filter support for all floating point values
   *
   * @param[in] value
   * Disable/Enable
   */
  virtual void PercentDeadbandFloatingPointDisable(bool value) = 0;

  /*****************************************************************************/
  /** Get the Disabled/Enabled status of percent deadband filter support for
   * double precision floating point
   *
   * @return
   * Returns the Disabled/Enabled status of percent deadband filter support for
   * double precision floating point
   */
  virtual bool PercentDeadbandDoubleDisable(void) const = 0;

  /*****************************************************************************/
  /** Disable/Enable percent deadband filter support for double precision floating point
   *
   * @param[in] value
   * The Maximum Nodes per Browse to be set
   */
  virtual void PercentDeadbandDoubleDisable(bool value) = 0;

  /*****************************************************************************/
  /** Get the Disabled/Enabled status of percent deadband filter
   * support for all floating point arrays
   *
   * @return
   * Returns the Disabled/Enabled status of percent deadband filter support for
   * all floating point arrays
   */
  virtual bool PercentDeadbandFloatingPointVectorsDisable(void) const = 0;

  /*****************************************************************************/
  /** Disable/Enable the status of percent deadband filter
   * support for all floating point arrays
   *
   * @param[in] value
   * Enable/Disable
   */
  virtual void PercentDeadbandFloatingPointVectorsDisable(bool value) = 0;

  /** */
  /*****************************************************************************/
  /** Get the Disabled/Enabled status of percent deadband filter support for
   * double precision floating point arrays
   *
   * @return
   * Returns the Disabled/Enabled status of percent deadband filter support for
   * double precision floating point arrays
   */
  virtual bool PercentDeadbandDoubleVectorsDisable(void) const = 0;

  /*****************************************************************************/
  /** Disable/Enable the percent deadband filter support for
   * double precision floating point arrays
   *
   * @param[in] value
   * Enable/Disable
   */
  virtual void PercentDeadbandDoubleVectorsDisable(bool value) = 0;

  /*****************************************************************************/
  /** Use single precision float for all filter operations
   *
   * @return
   * Returns true if single precision float is used for all filter operations
   */
  virtual bool UseSinglePrecisionFloatForAllFilterOperations(void) const = 0;

  /*****************************************************************************/
  /** set single precision float for all filter operations setting
   *
   * @param[in] value
   * True - Use single precision; False- Default
   */
  virtual void UseSinglePrecisionFloatForAllFilterOperations(bool value) = 0;

  /*****************************************************************************/
  /** Get the Minimum Publishing Interval in MilliSecond
   *
   * @return
   * Returns the Minimum Publishing Interval in MilliSecond
   */
  virtual uint32_t MinPublishingIntervalInMs(void) const = 0;

  /*****************************************************************************/
  /** Set the Minimum Publishing Interval in MilliSecond
   *
   * @param[in] value
   * The Minimum Publishing Interval in MilliSecond to be set
   */
  virtual void MinPublishingIntervalInMs(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Minimum Sampling Interval in MilliSecond
   *
   * @return
   * Returns the Minimum Sampling Interval in MilliSecond
   */
  virtual uint32_t MinSamplingIntervalInMs(void) const = 0;

  /*****************************************************************************/
  /** Set the Minimum Publishing Interval in MilliSecond
   *
   * @param[in] value
   * The Minimum Publishing Interval in MilliSecond to be set
   */
  virtual void MinSamplingIntervalInMs(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get the Server Diagnostics Enabled Flag
   *
   * @return
   * Returns the Server Diagnostics Enabled Flag
   */
  virtual bool ServerDiagnosticsEnabledFlag(void) const = 0;

  /*****************************************************************************/
  /** Set the Server Diagnostics Enabled Flag
   *
   * @param[in] value
   * The Server Diagnostics Enabled Flag to be set
   *
   * @return
   * returns status of creation of Server diagnostics object operation
   */
  virtual Status_t ServerDiagnosticsEnabledFlag(bool value) = 0;

  /*****************************************************************************/
  /** Get the User Permission Provider
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * IUserPermissionsProvider_t. The caller must test the pointer
   * before dereferencing it.
   */
  virtual IntrusivePtr_t<const IUserPermissionsProvider_t> UserPermissionsProvider(void) const = 0;

  /*****************************************************************************/
  /** Set the User Permission Provider
   *
   * @param[in] value
   * An intrusive reference counting Boost-style smart pointer to the
   * IUserPermissionsProvider_t.
   */
  virtual void UserPermissionsProvider(IntrusivePtr_t<const IUserPermissionsProvider_t> value) = 0;

  /*****************************************************************************/
  /** Get the Server State listener
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * IServerStateListener_t. The caller must test the pointer
   * before dereferencing it.
   */
  virtual IntrusivePtr_t<const IServerStateListener_t> ServerStateListener(void) const = 0;

  /*****************************************************************************/
  /** Set the Server State listener
   *
   * @param[in] value
   * An intrusive reference counting Boost-style smart pointer to the
   * IServerStateListener_t.
   */
  virtual void ServerStateListener(IntrusivePtr_t<IServerStateListener_t> value) = 0;

  /*****************************************************************************/
  /** Get the Server State
  *
  * @return
  * The server state.
  */
  virtual ServerState_t::Enum_t ServerState(void) const = 0;

  /*****************************************************************************/
  /** Get the Security Certificate Directory Stores Path
   *
   * @return
   * Returns the Security Certificate Directory Stores Path. An intrusive
   * reference counting Boost-style smart pointer to the String_t. The caller
   * must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const String_t> SecurityCertificateDirectoryStoresPath(void) const = 0;

  /*****************************************************************************/
  /** Set the Security Certificate Directory Stores Path
   *
   * @param[in] value
   * The Security Certificate Directory Stores Path to be set. An intrusive
   * reference counting Boost-style smart pointer to the String_t.
   */
  virtual void SecurityCertificateDirectoryStoresPath(IntrusivePtr_t<const String_t> value) = 0;

  /*****************************************************************************/
  /** Get the Address Space
   *
   * @return
   * Returns the address space. An intrusive
   * reference counting Boost-style smart pointer to the IAddressSpace_t. The caller
   * must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<IAddressSpace_t> AddressSpace(void) const = 0;

  /*****************************************************************************/
  /** Set the Address Space
   *
   * @param[in] value
   * The Address Space to be set. An intrusive
   * reference counting Boost-style smart pointer to the IAddressSpace_t.
   */
  virtual void AddressSpace(IntrusivePtr_t<IAddressSpace_t> value) = 0;

#if (UASDK_INCLUDE_SECURITY > 0)
  /*****************************************************************************/
  /** Get the Get Application Instance Certificate
   *
   * @param[in] type
   * The UA Certificate types
   *
   * @param[in] group
   * The UA Certificate Group
   *
   * @param[out] result
   * On the successful completion the result holds the application instance
   * certificate which is an intrusive reference counting Boost-style
   * smart pointer to the ApplicationInstanceCertificate_t.
   *
   * @return
   * Returns the status of the operation
   */
  virtual Status_t GetApplicationInstanceCertificate(
      UA_CertificateType_t type,
      UA_CertificateGroup_t group,
      IntrusivePtr_t<const ApplicationInstanceCertificate_t>& result) const = 0;

  /*****************************************************************************/
  /** Get Application Instance Certificate
   *
   * @param[in] policy
   * The Security Policy
   *
   * @param[out] result
   * On the successful completion the result holds the application instance
   * certificate which is an intrusive reference counting Boost-style
   * smart pointer to the ApplicationInstanceCertificate_t.
   *
   * @return
   * Returns the status of the operation
   */
  virtual Status_t GetApplicationInstanceCertificate(
      SecurityPolicy_t policy,
      IntrusivePtr_t<const ApplicationInstanceCertificate_t>& result) const = 0;
#endif

  /*****************************************************************************/
  /** Get the status of Application Instance Certificate creation for Security Policy NONE
   *
   * @return
   * Enabled - GetApplicationInstanceCertificate with SecurityPolicyNone
   * Disabled - if disabled the security policy NONE configuration dosen't return the certificate
   */
  virtual bool SendApplicationInstanceCertificateForSecurityPolicyNone(void) const = 0;

  /*****************************************************************************/
  /** Enable/Disable creation of Application Instance Certificate for Security Policy NONE
   *
   * @param[in] value
   * Enable - If enabled returns the Application Instance certificate for security policy NONE
   * Disable - If disabled the security policy NONE configuration dosen't return the certificate
   */
  virtual void SendApplicationInstanceCertificateForSecurityPolicyNone(bool value) = 0;

  /*****************************************************************************/
  /** Get the Time Emulation Enable status
   *
   * @return
   * Returns the Time Emulation Enable status
   */
  virtual bool TimeEmulationEnable(void) const = 0;

  /*****************************************************************************/
  /** Enable/Disable Time Emulation
   *
   * @param[in] value
   * Enable/Disable Time Emulation
   */
  virtual void TimeEmulationEnable(bool value) = 0;

  /*****************************************************************************/
  /** Get the IP Address
   *
   * @return
   * Returns the IP Address. An intrusive
   * reference counting Boost-style smart pointer to the String_t. The caller
   * must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const IntrusiveList_t<String_t> > IpAddresses(void) const = 0;

  /*****************************************************************************/
  /** Set the IP Address
   *
   * @param[in] value
   * The IP Address
   */
  virtual void IpAddresses(IntrusivePtr_t<const IntrusiveList_t<String_t> > value) = 0;

  /*****************************************************************************/
  /** Get the Host Name
   *
   * @return
   * Returns the Host Name. An intrusive
   * reference counting Boost-style smart pointer to the String_t. The caller
   * must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const IntrusiveList_t<String_t> > Hostnames(void) const = 0;

  /*****************************************************************************/
  /** Set the Host Name
   *
   * @param[in] value
   * The Host Name to be set
   */
  virtual void Hostnames(IntrusivePtr_t<const IntrusiveList_t<String_t> > value) = 0;

  /*****************************************************************************/
  /** Get the ApplicationURI
   *
   * @return
   * Returns the ApplicationURI. An intrusive
   * reference counting Boost-style smart pointer to the String_t. The caller
   * must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const String_t> ApplicationURI(void) const = 0;

  /*****************************************************************************/
  /** Set the ApplicationURI
   *
   * @param[in] value
   * The ApplicationURI to be set
   */
  virtual void ApplicationURI(IntrusivePtr_t<const String_t> value) = 0;

  /*****************************************************************************/
  /** Get the LocaleIds
   *
   * @return
   * Returns the LocaleIds. An intrusive
   * reference counting Boost-style smart pointer to the ArrayUA_t<String_t> >. The caller
   * must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const ArrayUA_t<String_t> > LocaleIds(void) const = 0;
  
  /*****************************************************************************/
  /** Set the LocaleIds
   *
   * @param[in] value
   * The LocaleIds to be set
   */
  virtual void LocaleIds(IntrusivePtr_t<const ArrayUA_t<String_t> > value) = 0;
  
  /*****************************************************************************/
  /** Get the Build Information
   *
   * @return
   * Returns the Build Information. An intrusive
   * reference counting Boost-style smart pointer to the BuildInfo_t. The caller
   * must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const BuildInfo_t> BuildInfo(void) const = 0;

  /*****************************************************************************/
  /** Set the Build Information
   *
   * @param[in] value
   * The Build Information to be set
   */
  virtual void BuildInfo(IntrusivePtr_t<const BuildInfo_t> value) = 0;

  /*****************************************************************************/
  /** This method adds the end point user token policy.
   *
   * @param[in] endpointSecurityPolicy
   * The end point security policy
   *
   * @param[in] endpointMessageSecurityMode
   * The Message security Mode
   *
   * @param[in] userTokenType
   * The User identity Token
   *
   * @param[in] userTokenSecurityPolicy
   * The security policy for the user
   *
   * @return
   * Returns Status of the operation
   */
  virtual Status_t AddEndpointUserTokenPolicy(SecurityPolicy_t endpointSecurityPolicy,
                                              MessageSecurityMode_t::Enum_t endpointMessageSecurityMode,
                                              UserIdentityTokenType_t::Enum_t userTokenType,
                                              SecurityPolicy_t userTokenSecurityPolicy) = 0;

  /*****************************************************************************/
  /** This method removes the end point user token policy.
   *
   * @param[in] endpointSecurityPolicy
   * The security policy for end point
   *
   * @param[in] endpointMessageSecurityMode
   * The Message security Mode
   *
   * @param[in] userTokenType
   * The User identity Token
   *
   * @param[in] userTokenSecurityPolicy
   * The security policy for the user
   *
   * @return
   * Returns Status of the operation
   */
  virtual Status_t RemoveEndpointUserTokenPolicy(SecurityPolicy_t endpointSecurityPolicy,
                                                 MessageSecurityMode_t::Enum_t endpointMessageSecurityMode,
                                                 UserIdentityTokenType_t::Enum_t userTokenType,
                                                 SecurityPolicy_t userTokenSecurityPolicy) = 0;

  /*****************************************************************************/
  /** This method close the Endpoint by resetting the Endpoint configuration
   * for the given security policy and message security mode.
   *
   * @param[in] securityPolicy
   * The security policy
   *
   * @param[in] messageSecurityMode
   * The Message security Mode
   *
   * @return
   * Returns Status of the operation
   */
  virtual Status_t CloseEndpoint(SecurityPolicy_t securityPolicy,
                                 MessageSecurityMode_t::Enum_t messageSecurityMode) = 0;

  /*****************************************************************************/
  /** This method close the Endpoint by resetting the Endpoint configuration
   * for the given security policy.
   *
   * @param[in] securityPolicy
   * The security policy
   *
   * @return
   * Returns Status of the operation
   */
  virtual Status_t CloseEndpoints(SecurityPolicy_t securityPolicy) = 0;

  /*****************************************************************************/
  /** This method close the Endpoint by resetting the Endpoint configuration
   * for the given message security mode.
   *
   * @param[in] messageSecurityMode
   * The Message Security Mode
   *
   * @return
   * Returns Status of the operation
   */
  virtual Status_t CloseEndpoints(MessageSecurityMode_t::Enum_t messageSecurityMode) = 0;

  /*****************************************************************************/
  /** This method close the all the Endpoints by resetting the complete Endpoint configurations
   *
   * @param[in] messageSecurityMode
   * The Message Security Mode
   */
  virtual void CloseAllEndpoints(void) = 0;

  /*****************************************************************************/
  /** This method check the end point is open or closed for the given security policy
   *
   * @param[in] securityPolicy
   * The Security Policy
   *
   * @return
   * True - If the End point is open
   */
  virtual bool IsEndpointOpen(SecurityPolicy_t securityPolicy) = 0;

  /*****************************************************************************/
  /** This method check the end point is open or closed for the given
   * security policy and the message security mode
   *
   * @param[in] securityPolicy
   * The Security Policy
   *
   * @param[in] messageSecurityMode
   * The Message Security Mode
   *
   * @return
   * True - If the End point is open
   */
  virtual bool IsEndpointOpen(SecurityPolicy_t securityPolicy,
                              MessageSecurityMode_t::Enum_t messageSecurityMode) = 0;

  /*****************************************************************************/
  /** Get the Certificate Validation options
   *
   * @return
   * The Certificate Validation options.
   */
  virtual ServerCertificateValidationOptions_t CertificateValidationOptions(void) const = 0;

  /*****************************************************************************/
  /** Set the Certificate Validation options
   *
   * @param[in] value
   * The Certificate Validation options.
   */
  virtual void CertificateValidationOptions(ServerCertificateValidationOptions_t value) = 0;

  /*****************************************************************************/
  /** Get the Certificate Private Key Password Provider
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the ICertificatePrivateKeyPasswordProvider_t.
   * The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const ICertificatePrivateKeyPasswordProvider_t> CertificatePrivateKeyPasswordProvider(void) const = 0;

  /*****************************************************************************/
  /** Set the Certificate Private Key Password Provider
   *
   * @param[in] value
   * The Certificate Validation options. An intrusive reference counting Boost-style
   * smart pointer to the ICertificatePrivateKeyPasswordProvider_t.
   */
  virtual void CertificatePrivateKeyPasswordProvider(IntrusivePtr_t<const ICertificatePrivateKeyPasswordProvider_t> value) = 0;

  /*****************************************************************************/
  /** Get the Certificate Rejected List Listener
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the ICertificateRejectedListListener_t.
   * The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const ICertificateRejectedListListener_t> CertificateRejectedListListener(void) const = 0;

  /*****************************************************************************/
  /** Set the Certificate Rejected List Listener
   *
   * @param[in] value
   * The Certificate Validation options. An intrusive reference counting Boost-style
   * smart pointer to the ICertificateRejectedListListener_t.
   */
  virtual void CertificateRejectedListListener(IntrusivePtr_t<const ICertificateRejectedListListener_t> value) = 0;

  /*****************************************************************************/
  /** Get the Register Node Listener
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the IRegisterNodeListener_t.
   * The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const IRegisterNodeListener_t> RegisterNodeListener(void) const = 0;

  /*****************************************************************************/
  /** Set the Register Node Listener
   *
   * @param[in] value
   * The Certificate Validation options. An intrusive reference counting Boost-style
   * smart pointer to the IRegisterNodeListener_t.
   */
  virtual void RegisterNodeListener(IntrusivePtr_t<const IRegisterNodeListener_t> value) = 0;

  /*****************************************************************************/
  /** Get the Read Service Transaction Listener
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the CertificateValidationOptions_t.
   * The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const ITransactionListener_t> ReadServiceTransactionListener(void) const = 0;

  /*****************************************************************************/
  /** Set the Read Service Transaction Listener
   *
   * @param[in] value
   * The Certificate Validation options. An intrusive reference counting Boost-style
   * smart pointer to the ITransactionListener_t.
   */
  virtual void ReadServiceTransactionListener(IntrusivePtr_t<const ITransactionListener_t> value) = 0;

  /*****************************************************************************/
  /** Get the Write Service Transaction Listener
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the ITransactionListener_t.
   * The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const ITransactionListener_t> WriteServiceTransactionListener(void) const = 0;

  /*****************************************************************************/
  /** Set the Write Service Transaction Listener
   *
   * @param[in] value
   * The Certificate Validation options. An intrusive reference counting Boost-style
   * smart pointer to the ITransactionListener_t.
   */
  virtual void WriteServiceTransactionListener(IntrusivePtr_t<const ITransactionListener_t> value) = 0;

  /*****************************************************************************/
  /** Get the Call Service Transaction Listener
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the ITransactionListener_t.
   * The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const ITransactionListener_t> CallServiceTransactionListener(void) const = 0;

  /*****************************************************************************/
  /** Set the Call Service Transaction Listener
   *
   * @param[in] value
   * The Certificate Validation options. An intrusive reference counting Boost-style
   * smart pointer to the ITransactionListener_t.
   */
  virtual void CallServiceTransactionListener(IntrusivePtr_t<const ITransactionListener_t> value) = 0;

  /*****************************************************************************/
  /** Get the Monitored Item Listener
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the IMonitoredItemListener_t.
   * The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<const IMonitoredItemListener_t> MonitoredItemListener(void) const = 0;

  /*****************************************************************************/
  /** Set the Monitored Item Listener
   *
   * @param[in] value
   * An intrusive reference counting Boost-style
   * smart pointer to the IMonitoredItemListener_t.
   */
  virtual void MonitoredItemListener(IntrusivePtr_t<const IMonitoredItemListener_t> value) = 0;

  /*****************************************************************************/
  /** Add a Session Listener
  *
  * @param[in] value
  * An intrusive reference counting Boost-style
  * smart pointer to the ISessionListener_t.
  */
  virtual Status_t AddSessionListener(IntrusivePtr_t<ISessionListener_t> value) = 0;

  /*****************************************************************************/
  /** Remove a Session Listener
  *
  * @param[in] value
  * The listener to remove.
  */
  virtual Status_t RemoveSessionListener(ISessionListener_t& value) = 0;

  virtual uint32_t GetNumberOfConnections(void) const = 0;

  virtual uint32_t GetNumberOfChannels(void) const = 0;

  virtual uint32_t GetNumberOfSessions(void) const = 0;

  virtual uint32_t GetNumberOfSubscriptions(void) const = 0;

  virtual uint32_t GetNumberOfMonitoredItems(void) const = 0;

  /*****************************************************************************/
  /** Configure the Server profile for Nano server profile
   *
   * @return
   * Returns the status of the operation
   */
  virtual Status_t ConfigureAsNanoDeviceServerProfile(void) = 0;

  /*****************************************************************************/
  /** Configure the Server profile for Micro server profile
   *
   * @return
   * Returns the status of the operation
   */
  virtual Status_t ConfigureAsMicroDeviceServerProfile(void) = 0;

  /*****************************************************************************/
  /** Configure the Server profile for Embedded server profile
   *
   * @return
   * Returns the status of the operation
   */
  virtual Status_t ConfigureAsEmbeddedServerProfile(void) = 0;

  /*****************************************************************************/
  /** Add IP address to IP address white list
  *
  * @param[in] octets
  * The IP Address to add in binary big endian octet format.
  *
  * @return
  * Returns the status of the operation
  */
  virtual Status_t AddIPAddressToWhiteList(const ByteString_t& octets) = 0;

  /*****************************************************************************/
  /** Add IP address to IP address white list
  *
  * @param[in] ipAddress
  * The IP Address to add in dot notation.
  *
  * @return
  * Returns the status of the operation
  */
  virtual Status_t AddIPAddressToWhiteList(const String_t& ipAddress) = 0;

  /*****************************************************************************/
  /** Remove IP address from white list
  *
  * @param[in] octets
  * The IP Address to remove in binary big endian octet format.
  *
  * @return
  * Returns the status of the operation
  */
  virtual Status_t RemoveIPAddressFromWhiteList(const ByteString_t& octets) = 0;

  /*****************************************************************************/
  /** Remove IP address from white list
  *
  * @param[in] ipAddress
  * The IP Address to remove in dot notation.
  *
  * @return
  * Returns the status of the operation
  */
  virtual Status_t RemoveIPAddressFromWhiteList(const String_t& ipAddress) = 0;

  /*****************************************************************************/
  /** Clear IP address white list
  *
  */
  virtual void ClearIPAddressWhiteList(void) = 0;

  /*****************************************************************************/
  /** Is IP address in white list
  *
  * @param[in] octets
  * The IP Address to test in big endian binary octet format.
  *
  * @return
  * Returns true if the IP Address is in the whitelist
  */
  virtual bool IsIPAddressInWhiteList(const ByteString_t& octets) const = 0;

  /*****************************************************************************/
  /** Is IP address in white list
  *
  * @param[in] ipAddress
  * The IP Address to test in dot notation.
  *
  * @return
  * Returns true if the IP Address is in the whitelist
  */
  virtual bool IsIPAddressInWhiteList(const String_t& ipAddress) const = 0;

  /*****************************************************************************/
  /** Is IP address white list in use
  *
  * @return
  * Returns true if the whitelist is in use (i.e. not empty)
  */
  virtual bool IsIPAddressWhiteListInUse(void) const = 0;

#if (UASDK_INCLUDE_EVENTS > 0)
	/*****************************************************************************/
	/** Get the Maximum Number of Operands for ContentFilterElement_InList_t
	*
	* @return
	* Returns the Maximum Monitored Items Queue Size
	*/
	virtual uint32_t MaxOperandsInListOperator(void) const = 0;

	/*****************************************************************************/
	/** Set the Maximum Number of Operands for ContentFilterElement_InList_t
	*
	* @param[in] value
	* The Maximum Monitored Items Queue Size to be set
	*/
	virtual void MaxOperandsInListOperator(uint32_t value) = 0;

	/*****************************************************************************/
  /** Check if the server object is only event notifier node
   *
   * @return
   * True - If the server object is only event notifier node
   * False - otherwise
   */
  virtual bool IsServerObjectOnlyEventNotifierNode(void) const = 0;

  /*****************************************************************************/
  /** Set if the server object is only event notifier node
   *
   * @param[in] value
   * Set to true if the server object is only event notifier node, otherwise false
   */
  virtual void IsServerObjectOnlyEventNotifierNode(bool value) = 0;

  /*****************************************************************************/
  /** Get if that the server application receives event notification is enabled
   *
   * @return
   * True - If the server application is configured to receive event notification
   * False - otherwise
   */
  virtual bool IsServerApplicationReceivingEventNotificationEnabled(void) const = 0;

  /*****************************************************************************/
  /** Set if the server application is allowed to receive event notification
   *
   * @param[in] value
   * Set to true if the server application is allowed to receive event notification, otherwise false
   */
  virtual void IsServerApplicationReceivingEventNotificationEnabled(bool value) = 0;

  /*****************************************************************************/
  /** Check if the model change events compression is enabled
   *
   * @return
   * True - If the model change event compression is enabled
   * False - otherwise
   */
  virtual bool IsModelChangeEventsCompressionEnabled(void) const = 0;

  /*****************************************************************************/
  /** enable/disable the model change events compression
   *
   * @param[in] value
   * Set true to enable the model change events compression, otherwise false to disable it
   */
  virtual void IsModelChangeEventsCompressionEnabled(bool value) = 0;

  /*****************************************************************************/
  /** Check if the semantic change events compression is enabled
   *
   * @return
   * True - If the semantic change event compression is enabled
   * False - otherwise
   */
  virtual bool IsSemanticChangeEventsCompressionEnabled(void) const = 0;

  /*****************************************************************************/
  /** enable/disable the semantic change events compression
   *
   * @param[in] value
   * Set true to enable the semantic change events compression, otherwise false to disable it
   */
  virtual void IsSemanticChangeEventsCompressionEnabled(bool value) = 0;

  /*****************************************************************************/
  /** Get a 32-bit event activation status for each individual event type
   *
   *  Please refer to the header file "event_type_activation_bits_defs.h" for
   *  the detailed bit activation definition of each individual event type
   *
   * @return
   * Returns the activation status for event types
   */
  virtual uint32_t EventTypesActivationStatus(void) const = 0;

  /*****************************************************************************/
  /** Set a 32-bit event activation status for each individual event type
   *
   *  Please refer to the header file "event_type_activation_bits_defs.h" for
   *  the detailed bit activation definition of each individual event type
   *
   * @param[in] value
   * The enable bits for event types to be set
   */
  virtual void EventTypesActivationStatus(uint32_t value) = 0;

  /*****************************************************************************/
  /** Get EventIdGenerator
  *
  * return
  * intrusive pointer to Event Id generator
  */
  virtual IntrusivePtr_t<IEventIdGenerator_t> EventIdGenerator(void) const = 0;
  
  /*****************************************************************************/
  /** Set EventIdGenerator
  *
  * return
  */
  virtual void EventIdGenerator(IntrusivePtr_t<IEventIdGenerator_t> value) = 0;

  /*****************************************************************************/
  /** Get EventDispatcher
  *
  * return
  * intrusive pointer to Event Id generator
  */
  virtual IntrusivePtr_t<IEventDispatcher_t> EventDispatcher(void) const = 0;

  /*****************************************************************************/
  /** Set EventDispatcher
  *
  * return
  */
  virtual void EventDispatcher(IntrusivePtr_t<IEventDispatcher_t> value) = 0;

  /*****************************************************************************/
  /** Get local time
  *
  * return 
  * intrusive pointer to TimeZoneDataType_t for local time
  */
  virtual IntrusivePtr_t<TimeZoneDataType_t> LocalTime(void) const = 0;

  /*****************************************************************************/
  /** Set local time
  *
  * @param[in] value
  * local time value
  */
  virtual void LocalTime(IntrusivePtr_t<TimeZoneDataType_t> value) = 0;

#if (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0)
  /*****************************************************************************/
  /** Getter for Condition registrar
  *
  * @return
  * An intrusive reference counting Boost-style smart pointer to the
  * condition Registrar Variable. The caller must test the pointer before dereferencing it.
  */
  virtual IntrusivePtr_t<IConditionRegistrar_t> ConditionRegistrar(void) const = 0;

  /*****************************************************************************/
  /** setter for Condition registry bucket size
  *
  *  @param[in] value
  *  input bucket size
  *  
  */
  virtual void ConditionRegistryBucketSize(uint32_t value) = 0;

  /*****************************************************************************/
  /** getter for Condition registry bucket size
  *
  *  @return  
  *  bucket size
  */
  virtual uint32_t ConditionRegistryBucketSize(void) const = 0;

#if (UASDK_INCLUDE_SECURITY > 0)

  virtual Duration_t ExpirationLimit(void) const = 0;

  virtual void ExpirationLimit(Duration_t value) = 0;

  virtual uint32_t CertificateExpirationCheckIntervalInMS(void) const = 0;

  virtual void CertificateExpirationCheckIntervalInMS(uint32_t value) = 0;

#endif //UASDK_INCLUDE_SECURITY

#endif  //(UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0)

#endif //UASDK_INCLUDE_EVENTS
};

/** @} */

} // namespace uasdk
#endif //#if (UASDK_INCLUDE_SERVER > 0)
#endif // _ISERVER_CONFIGURATION_T_
