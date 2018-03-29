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

#include "opcua_session_diagnostics_data_type_t.h"

#if (UASDK_INCLUDE_SESSION_DIAGNOSTICS > 0)

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(SessionDiagnosticsDataType_t, Structure_t)

SessionDiagnosticsDataType_t::SessionDiagnosticsDataType_t()
{ }

SessionDiagnosticsDataType_t::~SessionDiagnosticsDataType_t()
{ }

bool SessionDiagnosticsDataType_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool SessionDiagnosticsDataType_t::operator==(SessionDiagnosticsDataType_t const & obj) const
{
  return (  (sessionId == obj.sessionId)
          && (sessionName == obj.sessionName)
          && (clientDescription == obj.clientDescription)
          && (serverUri == obj.serverUri)
          && (endpointUrl == obj.endpointUrl)
          && (localeIds == obj.localeIds) 
          && (actualSessionTimeout == obj.actualSessionTimeout)
          && (maxResponseMessageSize == obj.maxResponseMessageSize)
          && (clientConnectionTime == obj.clientConnectionTime)
          && (clientLastContactTime == obj.clientLastContactTime)
          && (currentSubscriptionsCount == obj.currentSubscriptionsCount)
          && (currentMonitoredItemsCount == obj.currentMonitoredItemsCount)
          && (currentPublishRequestsInQueue == obj.currentPublishRequestsInQueue)
          && (currentPublishTimerExpirations == obj.currentPublishTimerExpirations)
          && (totalRequestsCount == obj.totalRequestsCount)
          && (unauthorizedRequestsCount == obj.unauthorizedRequestsCount)
          && (readCount == obj.readCount)
          && (historyReadCount == obj.historyReadCount)
          && (writeCount == obj.writeCount)
          && (historyUpdateCount == obj.historyUpdateCount)
          && (callCount == obj.callCount)
          && (createMonitoredItemsCount == obj.createMonitoredItemsCount)
          && (modifyMonitoredItemsCount == obj.modifyMonitoredItemsCount)
          && (setMonitoringModeCount == obj.setMonitoringModeCount)
          && (setTriggeringCount == obj.setTriggeringCount)
          && (deleteMonitoredItemsCount == obj.deleteMonitoredItemsCount)
          && (createSubscriptionCount == obj.createSubscriptionCount)
          && (modifySubscriptionCount == obj.modifySubscriptionCount)
          && (setPublishingModeCount == obj.setPublishingModeCount)
          && (publishCount == obj.publishCount)
          && (republishCount == obj.republishCount)
          && (transferSubscriptionsCount == obj.transferSubscriptionsCount)
          && (deleteSubscriptionsCount == obj.deleteSubscriptionsCount)
          && (addNodesCount == obj.addNodesCount)
          && (addReferencesCount == obj.addReferencesCount)
          && (deleteNodesCount == obj.deleteNodesCount)
          && (deleteReferencesCount == obj.deleteReferencesCount)
          && (browseCount == obj.browseCount)
          && (browseNextCount == obj.browseNextCount)
          && (translateBrowsePathsToNodeIdsCount == obj.translateBrowsePathsToNodeIdsCount)
          && (queryFirstCount == obj.queryFirstCount)
          && (queryNextCount == obj.queryNextCount)
          && (registerNodesCount == obj.registerNodesCount)
          && (unregisterNodesCount == obj.unregisterNodesCount)
        );
}

bool SessionDiagnosticsDataType_t::operator!=(SessionDiagnosticsDataType_t const & obj) const
{
  return !(*this == obj);
}

bool SessionDiagnosticsDataType_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

bool SessionDiagnosticsDataType_t::operator>(SessionDiagnosticsDataType_t const & obj) const
{
  return (  (sessionId > obj.sessionId)
          && (sessionName > obj.sessionName)
          && (clientDescription > obj.clientDescription)
          && (serverUri > obj.serverUri)
          && (endpointUrl > obj.endpointUrl)
          && (localeIds > obj.localeIds) 
          && (actualSessionTimeout > obj.actualSessionTimeout)
          && (maxResponseMessageSize > obj.maxResponseMessageSize)
          && (clientConnectionTime > obj.clientConnectionTime)
          && (clientLastContactTime > obj.clientLastContactTime)
          && (currentSubscriptionsCount > obj.currentSubscriptionsCount)
          && (currentMonitoredItemsCount > obj.currentMonitoredItemsCount)
          && (currentPublishRequestsInQueue > obj.currentPublishRequestsInQueue)
          && (currentPublishTimerExpirations > obj.currentPublishTimerExpirations)
          && (totalRequestsCount > obj.totalRequestsCount)
          && (unauthorizedRequestsCount > obj.unauthorizedRequestsCount)
          && (readCount > obj.readCount)
          && (historyReadCount > obj.historyReadCount)
          && (writeCount > obj.writeCount)
          && (historyUpdateCount > obj.historyUpdateCount)
          && (callCount > obj.callCount)
          && (createMonitoredItemsCount > obj.createMonitoredItemsCount)
          && (modifyMonitoredItemsCount > obj.modifyMonitoredItemsCount)
          && (setMonitoringModeCount > obj.setMonitoringModeCount)
          && (setTriggeringCount > obj.setTriggeringCount)
          && (deleteMonitoredItemsCount > obj.deleteMonitoredItemsCount)
          && (createSubscriptionCount > obj.createSubscriptionCount)
          && (modifySubscriptionCount > obj.modifySubscriptionCount)
          && (setPublishingModeCount > obj.setPublishingModeCount)
          && (publishCount > obj.publishCount)
          && (republishCount > obj.republishCount)
          && (transferSubscriptionsCount > obj.transferSubscriptionsCount)
          && (deleteSubscriptionsCount > obj.deleteSubscriptionsCount)
          && (addNodesCount > obj.addNodesCount)
          && (addReferencesCount > obj.addReferencesCount)
          && (deleteNodesCount > obj.deleteNodesCount)
          && (deleteReferencesCount > obj.deleteReferencesCount)
          && (browseCount > obj.browseCount)
          && (browseNextCount > obj.browseNextCount)
          && (translateBrowsePathsToNodeIdsCount > obj.translateBrowsePathsToNodeIdsCount)
          && (queryFirstCount > obj.queryFirstCount)
          && (queryNextCount > obj.queryNextCount)
          && (registerNodesCount > obj.registerNodesCount)
          && (unregisterNodesCount > obj.unregisterNodesCount)
    );
}

Status_t SessionDiagnosticsDataType_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

Status_t SessionDiagnosticsDataType_t::CopyFrom(const BaseDataType_t& source)
{
  const SessionDiagnosticsDataType_t* ptr = RuntimeCast<const SessionDiagnosticsDataType_t* >(source);
  if (!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t SessionDiagnosticsDataType_t::CopyFrom(const SessionDiagnosticsDataType_t& source)
{
  Status_t status = sessionId.CopyFrom(source.sessionId);
  if (status.IsBad())
  {
    return status;
  }

  status = sessionName.CopyFrom(source.sessionName);
  if (status.IsBad())
  {
    return status;
  }

  status = clientDescription.CopyFrom(source.clientDescription);
  if (status.IsBad())
  {
    return status;
  }

  status = serverUri.CopyFrom(source.serverUri);
  if (status.IsBad())
  {
    return status;
  }

  status = endpointUrl.CopyFrom(source.endpointUrl);
  if (status.IsBad())
  {
    return status;
  }

  status = localeIds.CopyFrom(source.localeIds);
  if (status.IsBad())
  {
    return status;
  }

  status = actualSessionTimeout.CopyFrom(source.actualSessionTimeout);
  if (status.IsBad())
  {
    return status;
  }

  status = maxResponseMessageSize.CopyFrom(source.maxResponseMessageSize);
  if (status.IsBad())
  {
    return status;
  }

  status = clientConnectionTime.CopyFrom(source.clientConnectionTime);
  if (status.IsBad())
  {
    return status;
  }

  status = clientLastContactTime.CopyFrom(source.clientLastContactTime);
  if (status.IsBad())
  {
    return status;
  }

  status = currentSubscriptionsCount.CopyFrom(source.currentSubscriptionsCount);
  if (status.IsBad())
  {
    return status;
  }

  status = currentMonitoredItemsCount.CopyFrom(source.currentMonitoredItemsCount);
  if (status.IsBad())
  {
    return status;
  }

  status = currentPublishRequestsInQueue.CopyFrom(source.currentPublishRequestsInQueue);
  if (status.IsBad())
  {
    return status;
  }

  status = currentPublishTimerExpirations.CopyFrom(source.currentPublishTimerExpirations);
  if (status.IsBad())
  {
    return status;
  }

  status = totalRequestsCount.CopyFrom(source.totalRequestsCount);
  if (status.IsBad())
  {
    return status;
  }

  status = unauthorizedRequestsCount.CopyFrom(source.unauthorizedRequestsCount);
  if (status.IsBad())
  {
    return status;
  }

  status = readCount.CopyFrom(source.readCount);
  if (status.IsBad())
  {
    return status;
  }

  status = historyReadCount.CopyFrom(source.historyReadCount);
  if (status.IsBad())
  {
    return status;
  }

  status = writeCount.CopyFrom(source.writeCount);
  if (status.IsBad())
  {
    return status;
  }

  status = historyUpdateCount.CopyFrom(source.historyUpdateCount);
  if (status.IsBad())
  {
    return status;
  }

  status = callCount.CopyFrom(source.callCount);
  if (status.IsBad())
  {
    return status;
  }

  status = createMonitoredItemsCount.CopyFrom(source.createMonitoredItemsCount);
  if (status.IsBad())
  {
    return status;
  }

  status = modifyMonitoredItemsCount.CopyFrom(source.modifyMonitoredItemsCount);
  if (status.IsBad())
  {
    return status;
  }

  status = setMonitoringModeCount.CopyFrom(source.setMonitoringModeCount);
  if (status.IsBad())
  {
    return status;
  }

  status = setTriggeringCount.CopyFrom(source.setTriggeringCount);
  if (status.IsBad())
  {
    return status;
  }

  status = deleteMonitoredItemsCount.CopyFrom(source.deleteMonitoredItemsCount);
  if (status.IsBad())
  {
    return status;
  }

  status = createSubscriptionCount.CopyFrom(source.createSubscriptionCount);
  if (status.IsBad())
  {
    return status;
  }

  status = modifySubscriptionCount.CopyFrom(source.modifySubscriptionCount);
  if (status.IsBad())
  {
    return status;
  }

  status = setPublishingModeCount.CopyFrom(source.setPublishingModeCount);
  if (status.IsBad())
  {
    return status;
  }

  status = publishCount.CopyFrom(source.publishCount);
  if (status.IsBad())
  {
    return status;
  }
  
  status = republishCount.CopyFrom(source.republishCount);
  if (status.IsBad())
  {
    return status;
  }
  
  status = transferSubscriptionsCount.CopyFrom(source.transferSubscriptionsCount);
  if (status.IsBad())
  {
    return status;
  }
  
  status = deleteSubscriptionsCount.CopyFrom(source.deleteSubscriptionsCount);
  if (status.IsBad())
  {
    return status;
  }
  
  status = addNodesCount.CopyFrom(source.addNodesCount);
  if (status.IsBad())
  {
    return status;
  }
  
  status = addReferencesCount.CopyFrom(source.addReferencesCount);
  if (status.IsBad())
  {
    return status;
  }
  
  status = deleteNodesCount.CopyFrom(source.deleteNodesCount);
  if (status.IsBad())
  {
    return status;
  }
  
  status = deleteReferencesCount.CopyFrom(source.deleteReferencesCount);
  if (status.IsBad())
  {
    return status;
  }
  
  status = browseCount.CopyFrom(source.browseCount);
  if (status.IsBad())
  {
    return status;
  }
  
  status = browseNextCount.CopyFrom(source.browseNextCount);
  if (status.IsBad())
  {
    return status;
  }
  
  status = translateBrowsePathsToNodeIdsCount.CopyFrom(source.translateBrowsePathsToNodeIdsCount);
  if (status.IsBad())
  {
    return status;
  }
  
  status = queryFirstCount.CopyFrom(source.queryFirstCount);
  if (status.IsBad())
  {
    return status;
  }
  
  status = queryNextCount.CopyFrom(source.queryNextCount);
  if (status.IsBad())
  {
    return status;
  }
  
  status = registerNodesCount.CopyFrom(source.registerNodesCount);
  if (status.IsBad())
  {
    return status;
  }
  
  return unregisterNodesCount.CopyFrom(source.unregisterNodesCount);
}

uint32_t SessionDiagnosticsDataType_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0;
  return TYPE_ID;
}

uint32_t SessionDiagnosticsDataType_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0;
  return OpcUaId_SessionDiagnosticsDataType_Encoding_DefaultBinary;
}

const NodeIdGuid_t& SessionDiagnosticsDataType_t::SessionId() const
{
  return sessionId;
}

NodeIdGuid_t& SessionDiagnosticsDataType_t::SessionId()
{
  return sessionId;
}

const String_t& SessionDiagnosticsDataType_t::SessionName() const
{
  return sessionName;
}

String_t& SessionDiagnosticsDataType_t::SessionName()
{
  return sessionName;
}

const AppDescription_t& SessionDiagnosticsDataType_t::ClientDescription() const
{
  return clientDescription;
}

AppDescription_t& SessionDiagnosticsDataType_t::ClientDescription()
{
  return clientDescription;
}

const String_t& SessionDiagnosticsDataType_t::ServerUri() const
{
  return serverUri;
}

String_t& SessionDiagnosticsDataType_t::ServerUri()
{
  return serverUri;
}

const String_t& SessionDiagnosticsDataType_t::EndpointUrl() const
{
  return endpointUrl;
}

String_t& SessionDiagnosticsDataType_t::EndpointUrl()
{
  return endpointUrl;
}

const ArrayUA_t<String_t>& SessionDiagnosticsDataType_t::LocaleIds() const
{
  return localeIds;
}

ArrayUA_t<String_t>& SessionDiagnosticsDataType_t::LocaleIds()
{
  return localeIds;
}

const UInt32_t& SessionDiagnosticsDataType_t::MaxResponseMessageSize() const
{
  return maxResponseMessageSize;
}

const Duration_t& SessionDiagnosticsDataType_t::ActualSessionTimeout() const
{
  return actualSessionTimeout;
}

Duration_t& SessionDiagnosticsDataType_t::ActualSessionTimeout()
{
  return actualSessionTimeout;
}

UInt32_t& SessionDiagnosticsDataType_t::MaxResponseMessageSize()
{
  return maxResponseMessageSize;
}

const DateTime_t& SessionDiagnosticsDataType_t::ClientConnectionTime() const
{
  return clientConnectionTime;
}

DateTime_t& SessionDiagnosticsDataType_t::ClientConnectionTime()
{
  return clientConnectionTime;
}

const DateTime_t& SessionDiagnosticsDataType_t::ClientLastContactTime() const
{
  return clientLastContactTime;
}

DateTime_t& SessionDiagnosticsDataType_t::ClientLastContactTime()
{
  return clientLastContactTime;
}

const UInt32_t& SessionDiagnosticsDataType_t::CurrentSubscriptionsCount() const
{
  return currentSubscriptionsCount;
}

UInt32_t& SessionDiagnosticsDataType_t::CurrentSubscriptionsCount()
{
  return currentSubscriptionsCount;
}

const UInt32_t& SessionDiagnosticsDataType_t::CurrentMonitoredItemsCount() const
{
  return currentMonitoredItemsCount;
}

UInt32_t& SessionDiagnosticsDataType_t::CurrentMonitoredItemsCount()
{
  return currentMonitoredItemsCount;
}

const UInt32_t& SessionDiagnosticsDataType_t::CurrentPublishRequestsInQueue() const
{
  return currentPublishRequestsInQueue;
}

UInt32_t& SessionDiagnosticsDataType_t::CurrentPublishRequestsInQueue()
{
  return currentPublishRequestsInQueue;
}
const UInt32_t& SessionDiagnosticsDataType_t::CurrentPublishTimerExpirations() const
{
  return currentPublishTimerExpirations;
}

UInt32_t& SessionDiagnosticsDataType_t::CurrentPublishTimerExpirations()
{
  return currentPublishTimerExpirations;
}

const ServiceCounterDataType_t& SessionDiagnosticsDataType_t::TotalRequestsCount() const
{
  return totalRequestsCount;
}

ServiceCounterDataType_t& SessionDiagnosticsDataType_t::TotalRequestsCount()
{
  return totalRequestsCount;
}

const UInt32_t& SessionDiagnosticsDataType_t::UnauthorizedRequestsCount() const
{
  return unauthorizedRequestsCount;
}

UInt32_t& SessionDiagnosticsDataType_t::UnauthorizedRequestsCount()
{
  return unauthorizedRequestsCount;
}

const ServiceCounterDataType_t& SessionDiagnosticsDataType_t::ReadCount() const
{
  return readCount;
}

ServiceCounterDataType_t& SessionDiagnosticsDataType_t::ReadCount()
{
  return readCount;
}

const ServiceCounterDataType_t& SessionDiagnosticsDataType_t::HistoryReadCount() const
{
  return historyReadCount;
}

ServiceCounterDataType_t& SessionDiagnosticsDataType_t::HistoryReadCount()
{
  return historyReadCount;
}

const ServiceCounterDataType_t& SessionDiagnosticsDataType_t::WriteCount() const
{
  return writeCount;
}

ServiceCounterDataType_t& SessionDiagnosticsDataType_t::WriteCount()
{
  return writeCount;
}

const ServiceCounterDataType_t& SessionDiagnosticsDataType_t::HistoryUpdateCount() const
{
  return historyUpdateCount;
}

ServiceCounterDataType_t& SessionDiagnosticsDataType_t::HistoryUpdateCount()
{
  return historyUpdateCount;
}

const ServiceCounterDataType_t& SessionDiagnosticsDataType_t::CallCount() const
{
  return callCount;
}

ServiceCounterDataType_t& SessionDiagnosticsDataType_t::CallCount()
{
  return callCount;
}

const ServiceCounterDataType_t& SessionDiagnosticsDataType_t::CreateMonitoredItemsCount() const
{
  return createMonitoredItemsCount;
}

ServiceCounterDataType_t& SessionDiagnosticsDataType_t::CreateMonitoredItemsCount()
{
  return createMonitoredItemsCount;
}

const ServiceCounterDataType_t& SessionDiagnosticsDataType_t::ModifyMonitoredItemsCount() const
{
  return modifyMonitoredItemsCount;
}

ServiceCounterDataType_t& SessionDiagnosticsDataType_t::ModifyMonitoredItemsCount()
{
  return modifyMonitoredItemsCount;
}

const ServiceCounterDataType_t& SessionDiagnosticsDataType_t::SetMonitoringModeCount() const
{
  return setMonitoringModeCount;
}

ServiceCounterDataType_t& SessionDiagnosticsDataType_t::SetMonitoringModeCount()
{
  return setMonitoringModeCount;
}

const ServiceCounterDataType_t& SessionDiagnosticsDataType_t::SetTriggeringCount() const
{
  return setTriggeringCount;
}

ServiceCounterDataType_t& SessionDiagnosticsDataType_t::SetTriggeringCount()
{
  return setTriggeringCount;
}

const ServiceCounterDataType_t& SessionDiagnosticsDataType_t::DeleteMonitoredItemsCount() const
{
  return deleteMonitoredItemsCount;
}

ServiceCounterDataType_t& SessionDiagnosticsDataType_t::DeleteMonitoredItemsCount()
{
  return deleteMonitoredItemsCount;
}

const ServiceCounterDataType_t& SessionDiagnosticsDataType_t::CreateSubscriptionCount() const
{
  return createSubscriptionCount;
}

ServiceCounterDataType_t& SessionDiagnosticsDataType_t::CreateSubscriptionCount()
{
  return createSubscriptionCount;
}

const ServiceCounterDataType_t& SessionDiagnosticsDataType_t::ModifySubscriptionCount() const
{
  return modifySubscriptionCount;
}

ServiceCounterDataType_t& SessionDiagnosticsDataType_t::ModifySubscriptionCount()
{
  return modifySubscriptionCount;
}

const ServiceCounterDataType_t& SessionDiagnosticsDataType_t::SetPublishingModeCount() const
{
  return setPublishingModeCount;
}

ServiceCounterDataType_t& SessionDiagnosticsDataType_t::SetPublishingModeCount()
{
  return setPublishingModeCount;
}

const ServiceCounterDataType_t& SessionDiagnosticsDataType_t::PublishCount() const
{
  return publishCount;
}

ServiceCounterDataType_t& SessionDiagnosticsDataType_t::PublishCount()
{
  return publishCount;
}

const ServiceCounterDataType_t& SessionDiagnosticsDataType_t::RepublishCount() const
{
  return republishCount;
}

ServiceCounterDataType_t& SessionDiagnosticsDataType_t::RepublishCount()
{
  return republishCount;
}

const ServiceCounterDataType_t& SessionDiagnosticsDataType_t::TransferSubscriptionsCount() const
{
  return transferSubscriptionsCount;
}

ServiceCounterDataType_t& SessionDiagnosticsDataType_t::TransferSubscriptionsCount()
{
  return transferSubscriptionsCount;
}

const ServiceCounterDataType_t& SessionDiagnosticsDataType_t::DeleteSubscriptionsCount() const
{
  return deleteSubscriptionsCount;
}

ServiceCounterDataType_t& SessionDiagnosticsDataType_t::DeleteSubscriptionsCount()
{
  return deleteSubscriptionsCount;
}

const ServiceCounterDataType_t& SessionDiagnosticsDataType_t::AddNodesCount() const
{
  return addNodesCount;
}

ServiceCounterDataType_t& SessionDiagnosticsDataType_t::AddNodesCount()
{
  return addNodesCount;
}

const ServiceCounterDataType_t& SessionDiagnosticsDataType_t::AddReferencesCount() const
{
  return addReferencesCount;
}

ServiceCounterDataType_t& SessionDiagnosticsDataType_t::AddReferencesCount()
{
  return addReferencesCount;
}

const ServiceCounterDataType_t& SessionDiagnosticsDataType_t::DeleteNodesCount() const
{
  return deleteNodesCount;
}

ServiceCounterDataType_t& SessionDiagnosticsDataType_t::DeleteNodesCount()
{
  return deleteNodesCount;
}

const ServiceCounterDataType_t& SessionDiagnosticsDataType_t::DeleteReferencesCount() const
{
  return deleteReferencesCount;
}

ServiceCounterDataType_t& SessionDiagnosticsDataType_t::DeleteReferencesCount()
{
  return deleteReferencesCount;
}

const ServiceCounterDataType_t& SessionDiagnosticsDataType_t::BrowseCount() const
{
  return browseCount;
}

ServiceCounterDataType_t& SessionDiagnosticsDataType_t::BrowseCount()
{
  return browseCount;
}

const ServiceCounterDataType_t& SessionDiagnosticsDataType_t::BrowseNextCount() const
{
  return browseNextCount;
}

ServiceCounterDataType_t& SessionDiagnosticsDataType_t::BrowseNextCount()
{
  return browseNextCount;
}

const ServiceCounterDataType_t& SessionDiagnosticsDataType_t::TranslateBrowsePathsToNodeIdsCount() const
{
  return translateBrowsePathsToNodeIdsCount;
}

ServiceCounterDataType_t& SessionDiagnosticsDataType_t::TranslateBrowsePathsToNodeIdsCount()
{
  return translateBrowsePathsToNodeIdsCount;
}

const ServiceCounterDataType_t& SessionDiagnosticsDataType_t::QueryFirstCount() const
{
  return queryFirstCount;
}

ServiceCounterDataType_t& SessionDiagnosticsDataType_t::QueryFirstCount()
{
  return queryFirstCount;
}

const ServiceCounterDataType_t& SessionDiagnosticsDataType_t::QueryNextCount() const
{
  return queryNextCount;
}

ServiceCounterDataType_t& SessionDiagnosticsDataType_t::QueryNextCount()
{
  return queryNextCount;
}

const ServiceCounterDataType_t& SessionDiagnosticsDataType_t::RegisterNodesCount() const
{
  return registerNodesCount;
}

ServiceCounterDataType_t& SessionDiagnosticsDataType_t::RegisterNodesCount()
{
  return registerNodesCount;
}

const ServiceCounterDataType_t& SessionDiagnosticsDataType_t::UnregisterNodesCount() const
{
  return unregisterNodesCount;
}

ServiceCounterDataType_t& SessionDiagnosticsDataType_t::UnregisterNodesCount()
{
  return unregisterNodesCount;
}

Status_t SessionDiagnosticsDataType_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = sessionId.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = sessionName.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = clientDescription.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = serverUri.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = endpointUrl.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = localeIds.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = actualSessionTimeout.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = maxResponseMessageSize.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = clientConnectionTime.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = clientLastContactTime.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = currentSubscriptionsCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = currentMonitoredItemsCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = currentPublishRequestsInQueue.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = currentPublishTimerExpirations.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = totalRequestsCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = unauthorizedRequestsCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = readCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = historyReadCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = writeCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = historyUpdateCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = callCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = createMonitoredItemsCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = modifyMonitoredItemsCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = setMonitoringModeCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = setTriggeringCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = deleteMonitoredItemsCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = createSubscriptionCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = modifySubscriptionCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = setPublishingModeCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = publishCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = republishCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = transferSubscriptionsCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = deleteSubscriptionsCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = addNodesCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = addReferencesCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = deleteNodesCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = deleteReferencesCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = browseCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = browseNextCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = translateBrowsePathsToNodeIdsCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = queryFirstCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = queryNextCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = registerNodesCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return unregisterNodesCount.Encode(encoder, buffer);
}

Status_t SessionDiagnosticsDataType_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, SessionDiagnosticsDataType_t& result)
{
  IntrusivePtr_t<NodeId_t> sessionId_;
  Status_t status = NodeId_t::Decode(buffer, decoder, sessionId_);
  if (status.IsBad() || !sessionId_.is_set())
  {
    return status;
  }

  status = result.SessionId().CopyFrom(*sessionId_);
  if (status.IsBad())
  {
    return status;
  }

  status = String_t::Decode(buffer, decoder, result.SessionName());
  if (status.IsBad())
  {
    return status;
  }

  status = AppDescription_t::Decode(buffer, decoder, result.ClientDescription());
  if (status.IsBad())
  {
    return status;
  }

  status = String_t::Decode(buffer, decoder, result.ServerUri());
  if (status.IsBad())
  {
    return status;
  }

  status = String_t::Decode(buffer, decoder, result.EndpointUrl());
  if (status.IsBad())
  {
    return status;
  }

  status = ArrayUA_t<String_t>::Decode(buffer, decoder, result.LocaleIds());
  if (status.IsBad())
  {
    return status;
  }

  status = Duration_t::Decode(buffer, decoder, result.ActualSessionTimeout());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.MaxResponseMessageSize());
  if (status.IsBad())
  {
    return status;
  }

  status = DateTime_t::Decode(buffer, decoder, result.ClientConnectionTime());
  if (status.IsBad())
  {
    return status;
  }

  status = DateTime_t::Decode(buffer, decoder, result.ClientLastContactTime());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.CurrentSubscriptionsCount());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.CurrentMonitoredItemsCount());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.CurrentPublishRequestsInQueue());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.CurrentPublishTimerExpirations());
  if (status.IsBad())
  {
    return status;
  }

  status = ServiceCounterDataType_t::Decode(buffer, decoder, result.TotalRequestsCount());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.UnauthorizedRequestsCount());
  if (status.IsBad())
  {
    return status;
  }

  status = ServiceCounterDataType_t::Decode(buffer, decoder, result.ReadCount());
  if (status.IsBad())
  {
    return status;
  }

  status = ServiceCounterDataType_t::Decode(buffer, decoder, result.HistoryReadCount());
  if (status.IsBad())
  {
    return status;
  }

  status = ServiceCounterDataType_t::Decode(buffer, decoder, result.WriteCount());
  if (status.IsBad())
  {
    return status;
  }

  status = ServiceCounterDataType_t::Decode(buffer, decoder, result.HistoryUpdateCount());
  if (status.IsBad())
  {
    return status;
  }

  status = ServiceCounterDataType_t::Decode(buffer, decoder, result.CallCount());
  if (status.IsBad())
  {
    return status;
  }

  status = ServiceCounterDataType_t::Decode(buffer, decoder, result.CreateMonitoredItemsCount());
  if (status.IsBad())
  {
    return status;
  }

  status = ServiceCounterDataType_t::Decode(buffer, decoder, result.ModifyMonitoredItemsCount());
  if (status.IsBad())
  {
    return status;
  }

  status = ServiceCounterDataType_t::Decode(buffer, decoder, result.SetMonitoringModeCount());
  if (status.IsBad())
  {
    return status;
  }

  status = ServiceCounterDataType_t::Decode(buffer, decoder, result.SetMonitoringModeCount());
  if (status.IsBad())
  {
    return status;
  }

  status = ServiceCounterDataType_t::Decode(buffer, decoder, result.SetTriggeringCount());
  if (status.IsBad())
  {
    return status;
  }

  status = ServiceCounterDataType_t::Decode(buffer, decoder, result.DeleteMonitoredItemsCount());
  if (status.IsBad())
  {
    return status;
  }

  status = ServiceCounterDataType_t::Decode(buffer, decoder, result.CreateSubscriptionCount());
  if (status.IsBad())
  {
    return status;
  }

  status = ServiceCounterDataType_t::Decode(buffer, decoder, result.ModifySubscriptionCount());
  if (status.IsBad())
  {
    return status;
  }

  status = ServiceCounterDataType_t::Decode(buffer, decoder, result.SetPublishingModeCount());
  if (status.IsBad())
  {
    return status;
  }

  status = ServiceCounterDataType_t::Decode(buffer, decoder, result.PublishCount());
  if (status.IsBad())
  {
    return status;
  }
  
  status = ServiceCounterDataType_t::Decode(buffer, decoder, result.RepublishCount());
  if (status.IsBad())
  {
    return status;
  }
  
  status = ServiceCounterDataType_t::Decode(buffer, decoder, result.TransferSubscriptionsCount());
  if (status.IsBad())
  {
    return status;
  }
  
  status = ServiceCounterDataType_t::Decode(buffer, decoder, result.DeleteSubscriptionsCount());
  if (status.IsBad())
  {
    return status;
  }
  
  status = ServiceCounterDataType_t::Decode(buffer, decoder, result.AddNodesCount());
  if (status.IsBad())
  {
    return status;
  }
  
  status = ServiceCounterDataType_t::Decode(buffer, decoder, result.AddReferencesCount());
  if (status.IsBad())
  {
    return status;
  }
  
  status = ServiceCounterDataType_t::Decode(buffer, decoder, result.DeleteNodesCount());
  if (status.IsBad())
  {
    return status;
  }
  
  status = ServiceCounterDataType_t::Decode(buffer, decoder, result.DeleteReferencesCount());
  if (status.IsBad())
  {
    return status;
  }
  
  status = ServiceCounterDataType_t::Decode(buffer, decoder, result.BrowseCount());
  if (status.IsBad())
  {
    return status;
  }
  
  status = ServiceCounterDataType_t::Decode(buffer, decoder, result.BrowseNextCount());
  if (status.IsBad())
  {
    return status;
  }
  
  status = ServiceCounterDataType_t::Decode(buffer, decoder, result.TranslateBrowsePathsToNodeIdsCount());
  if (status.IsBad())
  {
    return status;
  }
  
  status = ServiceCounterDataType_t::Decode(buffer, decoder, result.QueryFirstCount());
  if (status.IsBad())
  {
    return status;
  }
  
  status = ServiceCounterDataType_t::Decode(buffer, decoder, result.QueryNextCount());
  if (status.IsBad())
  {
    return status;
  }
  
  status = ServiceCounterDataType_t::Decode(buffer, decoder, result.RegisterNodesCount());
  if (status.IsBad())
  {
    return status;
  }

  return ServiceCounterDataType_t::Decode(buffer, decoder, result.UnregisterNodesCount());
}

} // namespace uasdk

#endif  //UASDK_INCLUDE_SUBSCRIPTION_DIAGNOSTICS