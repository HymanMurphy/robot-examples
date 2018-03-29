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

#include "opcua_subscription_diagnostics_data_type_t.h"

#if (UASDK_INCLUDE_SUBSCRIPTION_DIAGNOSTICS > 0)

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(SubscriptionDiagnosticsDataType_t, Structure_t)

SubscriptionDiagnosticsDataType_t::SubscriptionDiagnosticsDataType_t()
{ }

SubscriptionDiagnosticsDataType_t::~SubscriptionDiagnosticsDataType_t()
{ }

bool SubscriptionDiagnosticsDataType_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool SubscriptionDiagnosticsDataType_t::operator==(SubscriptionDiagnosticsDataType_t const & obj) const
{
  return (  (sessionId == obj.sessionId)
          && (subscriptionId == obj.subscriptionId)
          && (priority == obj.priority) 
          && (publishingInterval == obj.publishingInterval)
          && (maxKeepAliveCount == obj.maxKeepAliveCount)
          && (maxLifetimeCount == obj.maxLifetimeCount) 
          && (maxNotificationsPerPublish == obj.maxNotificationsPerPublish)
          && (publishingEnabled == obj.publishingEnabled) 
          && (modifyCount == obj.modifyCount)
          && (enableCount == obj.enableCount) 
          && (disableCount == obj.disableCount)
          && (republishRequestCount == obj.republishRequestCount)
          && (republishMessageRequestCount == obj.republishMessageRequestCount)
          && (republishMessageCount == obj.republishMessageCount) 
          && (transferRequestCount == obj.transferRequestCount)
          && (transferredToAltClientCount == obj.transferredToAltClientCount) 
          && (transferredToSameClientCount == obj.transferredToSameClientCount)
          && (publishRequestCount == obj.publishRequestCount) 
          && (dataChangeNotificationsCount == obj.dataChangeNotificationsCount)
          && (eventNotificationsCount == obj.eventNotificationsCount)
          && (notificationsCount == obj.notificationsCount)
          && (latePublishRequestCount == obj.latePublishRequestCount)
          && (currentKeepAliveCount == obj.currentKeepAliveCount)
          && (currentLifetimeCount == obj.currentLifetimeCount) 
          && (unacknowledgedMessageCount == obj.unacknowledgedMessageCount)
          && (discardedMessageCount == obj.discardedMessageCount) 
          && (monitoredItemCount == obj.monitoredItemCount)
          && (disabledMonitoredItemCount == obj.disabledMonitoredItemCount)
          && (monitoringQueueOverflowCount == obj.monitoringQueueOverflowCount)
          && (nextSequenceNumber == obj.nextSequenceNumber) 
          && (eventQueueOverflowCount == obj.eventQueueOverflowCount)
        );
}

bool SubscriptionDiagnosticsDataType_t::operator!=(SubscriptionDiagnosticsDataType_t const & obj) const
{
  return !(*this == obj);
}

bool SubscriptionDiagnosticsDataType_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

bool SubscriptionDiagnosticsDataType_t::operator>(SubscriptionDiagnosticsDataType_t const & obj) const
{
  return (  (sessionId > obj.sessionId)
          && (subscriptionId > obj.subscriptionId)
          && (priority > obj.priority)
          && (publishingInterval > obj.publishingInterval)
          && (maxKeepAliveCount > obj.maxKeepAliveCount)
          && (maxLifetimeCount > obj.maxLifetimeCount)
          && (maxNotificationsPerPublish > obj.maxNotificationsPerPublish)
          && (publishingEnabled > obj.publishingEnabled)
          && (modifyCount > obj.modifyCount)
          && (enableCount > obj.enableCount)
          && (disableCount > obj.disableCount)
          && (republishRequestCount > obj.republishRequestCount)
          && (republishMessageRequestCount > obj.republishMessageRequestCount)
          && (republishMessageCount > obj.republishMessageCount)
          && (transferRequestCount > obj.transferRequestCount)
          && (transferredToAltClientCount > obj.transferredToAltClientCount)
          && (transferredToSameClientCount > obj.transferredToSameClientCount)
          && (publishRequestCount > obj.publishRequestCount)
          && (dataChangeNotificationsCount > obj.dataChangeNotificationsCount)
          && (eventNotificationsCount > obj.eventNotificationsCount)
          && (notificationsCount > obj.notificationsCount)
          && (latePublishRequestCount > obj.latePublishRequestCount)
          && (currentKeepAliveCount > obj.currentKeepAliveCount)
          && (currentLifetimeCount > obj.currentLifetimeCount)
          && (unacknowledgedMessageCount > obj.unacknowledgedMessageCount)
          && (discardedMessageCount > obj.discardedMessageCount)
          && (monitoredItemCount > obj.monitoredItemCount)
          && (disabledMonitoredItemCount > obj.disabledMonitoredItemCount)
          && (monitoringQueueOverflowCount > obj.monitoringQueueOverflowCount)
          && (nextSequenceNumber > obj.nextSequenceNumber)
          && (eventQueueOverflowCount > obj.eventQueueOverflowCount)
    );
}

Status_t SubscriptionDiagnosticsDataType_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

Status_t SubscriptionDiagnosticsDataType_t::CopyFrom(const BaseDataType_t& source)
{
  const SubscriptionDiagnosticsDataType_t* ptr = RuntimeCast<const SubscriptionDiagnosticsDataType_t*>(source);
  if (!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t SubscriptionDiagnosticsDataType_t::CopyFrom(const SubscriptionDiagnosticsDataType_t& source)
{
  Status_t status = sessionId.CopyFrom(source.sessionId);
  if (status.IsBad())
  {
    return status;
  }

  status = subscriptionId.CopyFrom(source.subscriptionId);
  if (status.IsBad())
  {
    return status;
  }

  status = priority.CopyFrom(source.priority);
  if (status.IsBad())
  {
    return status;
  }
  status = publishingInterval.CopyFrom(source.publishingInterval);
  if (status.IsBad())
  {
    return status;
  }

  status = maxKeepAliveCount.CopyFrom(source.maxKeepAliveCount);
  if (status.IsBad())
  {
    return status;
  }

  status = maxLifetimeCount.CopyFrom(source.maxLifetimeCount);
  if (status.IsBad())
  {
    return status;
  }

  status = maxNotificationsPerPublish.CopyFrom(source.maxNotificationsPerPublish);
  if (status.IsBad())
  {
    return status;
  }

  status = publishingEnabled.CopyFrom(source.publishingEnabled);
  if (status.IsBad())
  {
    return status;
  }

  status = modifyCount.CopyFrom(source.modifyCount);
  if (status.IsBad())
  {
    return status;
  }

  status = enableCount.CopyFrom(source.enableCount);
  if (status.IsBad())
  {
    return status;
  }

  status = disableCount.CopyFrom(source.disableCount);
  if (status.IsBad())
  {
    return status;
  }

  status = republishRequestCount.CopyFrom(source.republishRequestCount);
  if (status.IsBad())
  {
    return status;
  }

  status = republishMessageRequestCount.CopyFrom(source.republishMessageRequestCount);
  if (status.IsBad())
  {
    return status;
  }

  status = republishMessageCount.CopyFrom(source.republishMessageCount);
  if (status.IsBad())
  {
    return status;
  }

  status = transferRequestCount.CopyFrom(source.transferRequestCount);
  if (status.IsBad())
  {
    return status;
  }

  status = transferredToAltClientCount.CopyFrom(source.transferredToAltClientCount);
  if (status.IsBad())
  {
    return status;
  }

  status = transferredToSameClientCount.CopyFrom(source.transferredToSameClientCount);
  if (status.IsBad())
  {
    return status;
  }

  status = publishRequestCount.CopyFrom(source.publishRequestCount);
  if (status.IsBad())
  {
    return status;
  }

  status = dataChangeNotificationsCount.CopyFrom(source.dataChangeNotificationsCount);
  if (status.IsBad())
  {
    return status;
  }

  status = eventNotificationsCount.CopyFrom(source.eventNotificationsCount);
  if (status.IsBad())
  {
    return status;
  }

  status = notificationsCount.CopyFrom(source.notificationsCount);
  if (status.IsBad())
  {
    return status;
  }

  status = latePublishRequestCount.CopyFrom(source.latePublishRequestCount);
  if (status.IsBad())
  {
    return status;
  }

  status = currentKeepAliveCount.CopyFrom(source.currentKeepAliveCount);
  if (status.IsBad())
  {
    return status;
  }

  status = currentLifetimeCount.CopyFrom(source.currentLifetimeCount);
  if (status.IsBad())
  {
    return status;
  }

  status = unacknowledgedMessageCount.CopyFrom(source.unacknowledgedMessageCount);
  if (status.IsBad())
  {
    return status;
  }

  status = discardedMessageCount.CopyFrom(source.discardedMessageCount);
  if (status.IsBad())
  {
    return status;
  }

  status = monitoredItemCount.CopyFrom(source.monitoredItemCount);
  if (status.IsBad())
  {
    return status;
  }

  status = disabledMonitoredItemCount.CopyFrom(source.disabledMonitoredItemCount);
  if (status.IsBad())
  {
    return status;
  }

  status = monitoringQueueOverflowCount.CopyFrom(source.monitoringQueueOverflowCount);
  if (status.IsBad())
  {
    return status;
  }

  status = nextSequenceNumber.CopyFrom(source.nextSequenceNumber);
  if (status.IsBad())
  {
    return status;
  }

  return eventQueueOverflowCount.CopyFrom(source.eventQueueOverflowCount);
}

uint32_t SubscriptionDiagnosticsDataType_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0;
  return TYPE_ID;
}

uint32_t SubscriptionDiagnosticsDataType_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0;
  return OpcUaId_SubscriptionDiagnosticsDataType_Encoding_DefaultBinary;
}

const NodeIdGuid_t& SubscriptionDiagnosticsDataType_t::SessionId() const
{
  return sessionId;
}

NodeIdGuid_t& SubscriptionDiagnosticsDataType_t::SessionId()
{
  return sessionId;
}

const UInt32_t& SubscriptionDiagnosticsDataType_t::SubscriptionId() const
{
  return subscriptionId;
}

UInt32_t& SubscriptionDiagnosticsDataType_t::SubscriptionId()
{
  return subscriptionId;
}

const Byte_t& SubscriptionDiagnosticsDataType_t::Priority() const
{
  return priority;
}

Byte_t& SubscriptionDiagnosticsDataType_t::Priority()
{
  return priority;
}

const Duration_t& SubscriptionDiagnosticsDataType_t::PublishingInterval() const
{
  return publishingInterval;
}

Duration_t& SubscriptionDiagnosticsDataType_t::PublishingInterval()
{
  return publishingInterval;
}

const UInt32_t& SubscriptionDiagnosticsDataType_t::MaxKeepAliveCount() const
{
  return maxKeepAliveCount;
}

UInt32_t& SubscriptionDiagnosticsDataType_t::MaxKeepAliveCount()
{
  return maxKeepAliveCount;
}

const UInt32_t& SubscriptionDiagnosticsDataType_t::MaxLifetimeCount() const
{
  return maxLifetimeCount;
}

UInt32_t& SubscriptionDiagnosticsDataType_t::MaxLifetimeCount()
{
  return maxLifetimeCount;
}

const UInt32_t& SubscriptionDiagnosticsDataType_t::MaxNotificationsPerPublish() const
{
  return maxNotificationsPerPublish;
}

UInt32_t& SubscriptionDiagnosticsDataType_t::MaxNotificationsPerPublish()
{
  return maxNotificationsPerPublish;
}

const Boolean_t& SubscriptionDiagnosticsDataType_t::PublishingEnabled() const
{
  return publishingEnabled;
}

Boolean_t& SubscriptionDiagnosticsDataType_t::PublishingEnabled()
{
  return publishingEnabled;
}

const UInt32_t& SubscriptionDiagnosticsDataType_t::ModifyCount() const
{
  return modifyCount;
}

UInt32_t& SubscriptionDiagnosticsDataType_t::ModifyCount()
{
  return modifyCount;
}

const UInt32_t& SubscriptionDiagnosticsDataType_t::EnableCount() const
{
  return enableCount;
}

UInt32_t& SubscriptionDiagnosticsDataType_t::EnableCount()
{
  return enableCount;
}

const UInt32_t& SubscriptionDiagnosticsDataType_t::DisableCount() const
{
  return disableCount;
}

UInt32_t& SubscriptionDiagnosticsDataType_t::DisableCount()
{
  return disableCount;
}

const UInt32_t& SubscriptionDiagnosticsDataType_t::RepublishRequestCount() const
{
  return republishRequestCount;
}

UInt32_t& SubscriptionDiagnosticsDataType_t::RepublishRequestCount()
{
  return republishRequestCount;
}

const UInt32_t& SubscriptionDiagnosticsDataType_t::RepublishMessageRequestCount() const
{
  return republishMessageRequestCount;
}

UInt32_t& SubscriptionDiagnosticsDataType_t::RepublishMessageRequestCount()
{
  return republishMessageRequestCount;
}

const UInt32_t& SubscriptionDiagnosticsDataType_t::RepublishMessageCount() const
{
  return republishMessageCount;
}

UInt32_t& SubscriptionDiagnosticsDataType_t::RepublishMessageCount()
{
  return republishMessageCount;
}

const UInt32_t& SubscriptionDiagnosticsDataType_t::TransferRequestCount() const
{
  return transferRequestCount;
}

UInt32_t& SubscriptionDiagnosticsDataType_t::TransferRequestCount()
{
  return transferRequestCount;
}

const UInt32_t& SubscriptionDiagnosticsDataType_t::TransferredToAltClientCount() const
{
  return transferredToAltClientCount;
}

UInt32_t& SubscriptionDiagnosticsDataType_t::TransferredToAltClientCount()
{
  return transferredToAltClientCount;
}

const UInt32_t& SubscriptionDiagnosticsDataType_t::TransferredToSameClientCount() const
{
  return transferredToSameClientCount;
}

UInt32_t& SubscriptionDiagnosticsDataType_t::TransferredToSameClientCount()
{
  return transferredToSameClientCount;
}

const UInt32_t& SubscriptionDiagnosticsDataType_t::PublishRequestCount() const
{
  return publishRequestCount;
}

UInt32_t& SubscriptionDiagnosticsDataType_t::PublishRequestCount()
{
  return publishRequestCount;
}

const UInt32_t& SubscriptionDiagnosticsDataType_t::DataChangeNotificationsCount() const
{
  return dataChangeNotificationsCount;
}

UInt32_t& SubscriptionDiagnosticsDataType_t::DataChangeNotificationsCount()
{
  return dataChangeNotificationsCount;
}

const UInt32_t& SubscriptionDiagnosticsDataType_t::EventNotificationsCount() const
{
  return eventNotificationsCount;
}

UInt32_t& SubscriptionDiagnosticsDataType_t::EventNotificationsCount()
{
  return eventNotificationsCount;
}

const UInt32_t& SubscriptionDiagnosticsDataType_t::NotificationsCount() const
{
  return notificationsCount;
}

UInt32_t& SubscriptionDiagnosticsDataType_t::NotificationsCount()
{
  return notificationsCount;
}

const UInt32_t& SubscriptionDiagnosticsDataType_t::LatePublishRequestCount() const
{
  return latePublishRequestCount;
}

UInt32_t& SubscriptionDiagnosticsDataType_t::LatePublishRequestCount()
{
  return latePublishRequestCount;
}

const UInt32_t& SubscriptionDiagnosticsDataType_t::CurrentKeepAliveCount() const
{
  return currentKeepAliveCount;
}

UInt32_t& SubscriptionDiagnosticsDataType_t::CurrentKeepAliveCount()
{
  return currentKeepAliveCount;
}

const UInt32_t& SubscriptionDiagnosticsDataType_t::CurrentLifetimeCount() const
{
  return currentLifetimeCount;
}

UInt32_t& SubscriptionDiagnosticsDataType_t::CurrentLifetimeCount()
{
  return currentLifetimeCount;
}

const UInt32_t& SubscriptionDiagnosticsDataType_t::UnacknowledgedMessageCount() const
{
  return unacknowledgedMessageCount;
}

UInt32_t& SubscriptionDiagnosticsDataType_t::UnacknowledgedMessageCount()
{
  return unacknowledgedMessageCount;
}

const UInt32_t& SubscriptionDiagnosticsDataType_t::DiscardedMessageCount() const
{
  return discardedMessageCount;
}

UInt32_t& SubscriptionDiagnosticsDataType_t::DiscardedMessageCount()
{
  return discardedMessageCount;
}

const UInt32_t& SubscriptionDiagnosticsDataType_t::MonitoredItemCount() const
{
  return monitoredItemCount;
}

UInt32_t& SubscriptionDiagnosticsDataType_t::MonitoredItemCount()
{
  return monitoredItemCount;
}

const UInt32_t& SubscriptionDiagnosticsDataType_t::DisabledMonitoredItemCount() const
{
  return disabledMonitoredItemCount;
}

UInt32_t& SubscriptionDiagnosticsDataType_t::DisabledMonitoredItemCount()
{
  return disabledMonitoredItemCount;
}

const UInt32_t& SubscriptionDiagnosticsDataType_t::MonitoringQueueOverflowCount() const
{
  return monitoringQueueOverflowCount;
}

UInt32_t& SubscriptionDiagnosticsDataType_t::MonitoringQueueOverflowCount()
{
  return monitoringQueueOverflowCount;
}

const UInt32_t& SubscriptionDiagnosticsDataType_t::NextSequenceNumber() const
{
  return nextSequenceNumber;
}

UInt32_t& SubscriptionDiagnosticsDataType_t::NextSequenceNumber()
{
  return nextSequenceNumber;
}

const UInt32_t& SubscriptionDiagnosticsDataType_t::EventQueueOverflowCount() const
{
  return eventQueueOverflowCount;
}

UInt32_t& SubscriptionDiagnosticsDataType_t::EventQueueOverflowCount()
{
  return eventQueueOverflowCount;
}

Status_t SubscriptionDiagnosticsDataType_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = sessionId.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = subscriptionId.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = priority.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = publishingInterval.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = maxKeepAliveCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = maxLifetimeCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = maxNotificationsPerPublish.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = publishingEnabled.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = modifyCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = enableCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = disableCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = republishRequestCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = republishMessageRequestCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = republishMessageCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = transferRequestCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = transferredToAltClientCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = transferredToSameClientCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = publishRequestCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = dataChangeNotificationsCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = eventNotificationsCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = notificationsCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = latePublishRequestCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = currentKeepAliveCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = currentLifetimeCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = unacknowledgedMessageCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = discardedMessageCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = monitoredItemCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = disabledMonitoredItemCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = monitoringQueueOverflowCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = nextSequenceNumber.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return eventQueueOverflowCount.Encode(encoder, buffer);
}

Status_t SubscriptionDiagnosticsDataType_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, SubscriptionDiagnosticsDataType_t& result)
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

  status = UInt32_t::Decode(buffer, decoder, result.SubscriptionId());
  if (status.IsBad())
  {
    return status;
  }

  status = Byte_t::Decode(buffer, decoder, result.Priority());
  if (status.IsBad())
  {
    return status;
  }

  status = Duration_t::Decode(buffer, decoder, result.PublishingInterval());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.MaxKeepAliveCount());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.MaxLifetimeCount());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.MaxNotificationsPerPublish());
  if (status.IsBad())
  {
    return status;
  }

  status = Boolean_t::Decode(buffer, decoder, result.PublishingEnabled());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.ModifyCount());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.EnableCount());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.DisableCount());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.RepublishRequestCount());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.RepublishMessageRequestCount());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.RepublishMessageCount());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.TransferRequestCount());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.TransferredToAltClientCount());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.TransferredToSameClientCount());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.PublishRequestCount());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.DataChangeNotificationsCount());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.EventNotificationsCount());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.NotificationsCount());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.LatePublishRequestCount());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.CurrentKeepAliveCount());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.CurrentLifetimeCount());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.UnacknowledgedMessageCount());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.DiscardedMessageCount());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.MonitoredItemCount());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.DisabledMonitoredItemCount());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.MonitoringQueueOverflowCount());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.NextSequenceNumber());
  if (status.IsBad())
  {
    return status;
  }

  return UInt32_t::Decode(buffer, decoder, result.EventQueueOverflowCount());
}

} // namespace uasdk

#endif  //UASDK_INCLUDE_SUBSCRIPTION_DIAGNOSTICS