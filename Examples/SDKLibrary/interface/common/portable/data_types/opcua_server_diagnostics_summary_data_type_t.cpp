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

#include "opcua_server_diagnostics_summary_data_type_t.h"

#if (UASDK_INCLUDE_SERVER_DIAGNOSTICS_SUMMARY > 0)

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(ServerDiagnosticsSummaryDataType_t, Structure_t)

ServerDiagnosticsSummaryDataType_t::ServerDiagnosticsSummaryDataType_t()
{ }

ServerDiagnosticsSummaryDataType_t::~ServerDiagnosticsSummaryDataType_t()
{ }

bool ServerDiagnosticsSummaryDataType_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool ServerDiagnosticsSummaryDataType_t::operator==(ServerDiagnosticsSummaryDataType_t const & obj) const
{
  return (  (serverViewCount == obj.serverViewCount)
          && (currentSessionCount == obj.currentSessionCount)
          && (cumulatedSessionCount == obj.cumulatedSessionCount)
          && (securityRejectedSessionCount == obj.securityRejectedSessionCount)
          && (rejectedSessionCount == obj.rejectedSessionCount)
          && (sessionTimeoutCount == obj.sessionTimeoutCount)
          && (sessionAbortCount == obj.sessionAbortCount)
          && (publishingIntervalCount == obj.publishingIntervalCount)
          && (currentSubscriptionCount == obj.currentSubscriptionCount)
          && (cumulatedSubscriptionCount == obj.cumulatedSubscriptionCount)
          && (securityRejectedRequestsCount == obj.securityRejectedRequestsCount)
          && (rejectedRequestsCount == obj.rejectedRequestsCount) );
}

bool ServerDiagnosticsSummaryDataType_t::operator!=(ServerDiagnosticsSummaryDataType_t const & obj) const
{
  return !(*this == obj);
}

bool ServerDiagnosticsSummaryDataType_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

bool ServerDiagnosticsSummaryDataType_t::operator>(ServerDiagnosticsSummaryDataType_t const & obj) const
{
  return (  (serverViewCount > obj.serverViewCount)
          && (currentSessionCount > obj.currentSessionCount)
          && (cumulatedSessionCount > obj.cumulatedSessionCount)
          && (securityRejectedSessionCount > obj.securityRejectedSessionCount)
          && (rejectedSessionCount > obj.rejectedSessionCount)
          && (sessionTimeoutCount > obj.sessionTimeoutCount)
          && (sessionAbortCount > obj.sessionAbortCount)
          && (publishingIntervalCount > obj.publishingIntervalCount)
          && (currentSubscriptionCount > obj.currentSubscriptionCount)
          && (cumulatedSubscriptionCount > obj.cumulatedSubscriptionCount)
          && (securityRejectedRequestsCount > obj.securityRejectedRequestsCount)
          && (rejectedRequestsCount > obj.rejectedRequestsCount) );
}

Status_t ServerDiagnosticsSummaryDataType_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

Status_t ServerDiagnosticsSummaryDataType_t::CopyFrom(const BaseDataType_t& source)
{
  const ServerDiagnosticsSummaryDataType_t* ptr = RuntimeCast<const ServerDiagnosticsSummaryDataType_t*>(source);
  if (!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t ServerDiagnosticsSummaryDataType_t::CopyFrom(const ServerDiagnosticsSummaryDataType_t& source)
{
  Status_t status = serverViewCount.CopyFrom(source.serverViewCount);
  if (status.IsBad())
  {
    return status;
  }

  status = currentSessionCount.CopyFrom(source.currentSessionCount);
  if (status.IsBad())
  {
    return status;
  }

  status = cumulatedSessionCount.CopyFrom(source.cumulatedSessionCount);
  if (status.IsBad())
  {
    return status;
  }

  status = securityRejectedSessionCount.CopyFrom(source.securityRejectedSessionCount);
  if (status.IsBad())
  {
    return status;
  }

  status = rejectedSessionCount.CopyFrom(source.rejectedSessionCount);
  if (status.IsBad())
  {
    return status;
  }

  status = sessionTimeoutCount.CopyFrom(source.sessionTimeoutCount);
  if (status.IsBad())
  {
    return status;
  }

  status = sessionAbortCount.CopyFrom(source.sessionAbortCount);
  if (status.IsBad())
  {
    return status;
  }

  status = publishingIntervalCount.CopyFrom(source.publishingIntervalCount);
  if (status.IsBad())
  {
    return status;
  }

  status = currentSubscriptionCount.CopyFrom(source.currentSubscriptionCount);
  if (status.IsBad())
  {
    return status;
  }

  status = cumulatedSubscriptionCount.CopyFrom(source.cumulatedSubscriptionCount);
  if (status.IsBad())
  {
    return status;
  }

  status = securityRejectedRequestsCount.CopyFrom(source.securityRejectedRequestsCount);
  if (status.IsBad())
  {
    return status;
  }

  return rejectedRequestsCount.CopyFrom(source.rejectedRequestsCount);
}

uint32_t ServerDiagnosticsSummaryDataType_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0;
  return TYPE_ID;
}

uint32_t ServerDiagnosticsSummaryDataType_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0;
  return OpcUaId_ServerDiagnosticsSummaryDataType_Encoding_DefaultBinary;
}

const UInt32_t& ServerDiagnosticsSummaryDataType_t::ServerViewCount() const
{
  return serverViewCount;
}

UInt32_t& ServerDiagnosticsSummaryDataType_t::ServerViewCount()
{
  return serverViewCount;
}

const UInt32_t& ServerDiagnosticsSummaryDataType_t::CurrentSessionCount() const
{
  return currentSessionCount;
}

UInt32_t& ServerDiagnosticsSummaryDataType_t::CurrentSessionCount()
{
  return currentSessionCount;
}

const UInt32_t& ServerDiagnosticsSummaryDataType_t::CumulatedSessionCount() const
{
  return cumulatedSessionCount;
}

UInt32_t& ServerDiagnosticsSummaryDataType_t::CumulatedSessionCount()
{
  return cumulatedSessionCount;
}

const UInt32_t& ServerDiagnosticsSummaryDataType_t::SecurityRejectedSessionCount() const
{
  return securityRejectedSessionCount;
}

UInt32_t& ServerDiagnosticsSummaryDataType_t::SecurityRejectedSessionCount()
{
  return securityRejectedSessionCount;
}

const UInt32_t& ServerDiagnosticsSummaryDataType_t::RejectedSessionCount() const
{
  return rejectedSessionCount;
}

UInt32_t& ServerDiagnosticsSummaryDataType_t::RejectedSessionCount()
{
  return rejectedSessionCount;
}

const UInt32_t& ServerDiagnosticsSummaryDataType_t::SessionTimeoutCount() const
{
  return sessionTimeoutCount;
}

UInt32_t& ServerDiagnosticsSummaryDataType_t::SessionTimeoutCount()
{
  return sessionTimeoutCount;
}

const UInt32_t& ServerDiagnosticsSummaryDataType_t::SessionAbortCount() const
{
  return sessionAbortCount;
}

UInt32_t& ServerDiagnosticsSummaryDataType_t::SessionAbortCount()
{
  return sessionAbortCount;
}

const UInt32_t& ServerDiagnosticsSummaryDataType_t::PublishingIntervalCount() const
{
  return publishingIntervalCount;
}

UInt32_t& ServerDiagnosticsSummaryDataType_t::PublishingIntervalCount()
{
  return publishingIntervalCount;
}

const UInt32_t& ServerDiagnosticsSummaryDataType_t::CurrentSubscriptionCount() const
{
  return currentSubscriptionCount;
}

UInt32_t& ServerDiagnosticsSummaryDataType_t::CurrentSubscriptionCount()
{
  return currentSubscriptionCount;
}

const UInt32_t& ServerDiagnosticsSummaryDataType_t::CumulatedSubscriptionCount() const
{
  return cumulatedSubscriptionCount;
}

UInt32_t& ServerDiagnosticsSummaryDataType_t::CumulatedSubscriptionCount()
{
  return cumulatedSubscriptionCount;
}

const UInt32_t& ServerDiagnosticsSummaryDataType_t::SecurityRejectedRequestsCount() const
{
  return securityRejectedRequestsCount;
}

UInt32_t& ServerDiagnosticsSummaryDataType_t::SecurityRejectedRequestsCount()
{
  return securityRejectedRequestsCount;
}

const UInt32_t& ServerDiagnosticsSummaryDataType_t::RejectedRequestsCount() const
{
  return rejectedRequestsCount;
}

UInt32_t& ServerDiagnosticsSummaryDataType_t::RejectedRequestsCount()
{
  return rejectedRequestsCount;
}

Status_t ServerDiagnosticsSummaryDataType_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = serverViewCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = currentSessionCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = cumulatedSessionCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = securityRejectedSessionCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = rejectedSessionCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = sessionTimeoutCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = sessionAbortCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = publishingIntervalCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = currentSubscriptionCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = cumulatedSubscriptionCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = securityRejectedRequestsCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return rejectedRequestsCount.Encode(encoder, buffer);
}

Status_t ServerDiagnosticsSummaryDataType_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, ServerDiagnosticsSummaryDataType_t& result)
{
  Status_t status = UInt32_t::Decode(buffer, decoder, result.ServerViewCount());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.CurrentSessionCount());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.CumulatedSessionCount());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.SecurityRejectedSessionCount());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.RejectedSessionCount());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.SessionTimeoutCount());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.SessionAbortCount());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.PublishingIntervalCount());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.CurrentSubscriptionCount());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.CumulatedSubscriptionCount());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.SecurityRejectedRequestsCount());
  if (status.IsBad())
  {
    return status;
  }

  return UInt32_t::Decode(buffer, decoder, result.RejectedRequestsCount());
}

} // namespace uasdk

#endif  //UASDK_INCLUDE_SERVER_DIAGNOSTICS_SUMMARY