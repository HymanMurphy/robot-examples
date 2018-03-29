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

#include "opcua_mon_item_create_result_t.h"

#if (UASDK_INCLUDE_SUBSCRIPTIONS > 0)

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(MonItemCreateResult_t, Structure_t)

bool MonItemCreateResult_t::operator==(MonItemCreateResult_t const & obj) const
{
  return (
      (statusCode == obj.statusCode)
      && (monitoredItemId == obj.monitoredItemId)
      && (revisedSamplingInterval == obj.revisedSamplingInterval)
      && (revisedQueueSize == obj.revisedQueueSize)
      && (filterResult == obj.filterResult));
}

bool MonItemCreateResult_t::operator>(MonItemCreateResult_t const & obj) const
{
  return (
      (statusCode > obj.statusCode)
      && (monitoredItemId > obj.monitoredItemId)
      && (revisedSamplingInterval > obj.revisedSamplingInterval)
      && (revisedQueueSize > obj.revisedQueueSize)
      && (filterResult > obj.filterResult));
}

Status_t MonItemCreateResult_t::CopyFrom(const BaseDataType_t& source)
{
  const MonItemCreateResult_t* ptr = RuntimeCast<const MonItemCreateResult_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t MonItemCreateResult_t::CopyFrom(const MonItemCreateResult_t& source)
{
  Status_t status = statusCode.CopyFrom(source.statusCode);
  if (status.IsBad())
  {
    return status;
  }

  status = monitoredItemId.CopyFrom(source.monitoredItemId);
  if (status.IsBad())
  {
    return status;
  }

  status = revisedSamplingInterval.CopyFrom(source.revisedSamplingInterval);
  if (status.IsBad())
  {
    return status;
  }

  status = revisedQueueSize.CopyFrom(source.revisedQueueSize);
  if (status.IsBad())
  {
    return status;
  }

  status = filterResult.CopyFrom(source.filterResult);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t MonItemCreateResult_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = statusCode.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = monitoredItemId.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = revisedSamplingInterval.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = revisedQueueSize.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = filterResult.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t MonItemCreateResult_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, MonItemCreateResult_t& result)
{
  Status_t status = StatusCode_t::Decode(buffer, decoder, result.StatusCode());
  if (status.IsBad())
  {
    return status;
  }

  status = IntegerId_t::Decode(buffer, decoder, result.MonitoredItemId());
  if (status.IsBad())
  {
    return status;
  }

  status = Duration_t::Decode(buffer, decoder, result.RevisedSamplingInterval());
  if (status.IsBad())
  {
    return status;
  }

  status = Counter_t::Decode(buffer, decoder, result.RevisedQueueSize());
  if (status.IsBad())
  {
    return status;
  }

  status = ExtensibleParameter_t::Decode(buffer, decoder, result.FilterResult());
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

MonItemCreateResult_t::~MonItemCreateResult_t()
{}

bool MonItemCreateResult_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool MonItemCreateResult_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t MonItemCreateResult_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t MonItemCreateResult_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t MonItemCreateResult_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_MonitoredItemCreateResult_Encoding_DefaultBinary;
}

const StatusCode_t& MonItemCreateResult_t::StatusCode(void) const
{
  return statusCode;
}

StatusCode_t& MonItemCreateResult_t::StatusCode(void)
{
  return statusCode;
}

const IntegerId_t& MonItemCreateResult_t::MonitoredItemId(void) const
{
  return monitoredItemId;
}

IntegerId_t& MonItemCreateResult_t::MonitoredItemId(void)
{
  return monitoredItemId;
}

const Duration_t& MonItemCreateResult_t::RevisedSamplingInterval(void) const
{
  return revisedSamplingInterval;
}

Duration_t& MonItemCreateResult_t::RevisedSamplingInterval(void)
{
  return revisedSamplingInterval;
}

const Counter_t& MonItemCreateResult_t::RevisedQueueSize(void) const
{
  return revisedQueueSize;
}

Counter_t& MonItemCreateResult_t::RevisedQueueSize(void)
{
  return revisedQueueSize;
}

const ExtensibleParameter_t& MonItemCreateResult_t::FilterResult(void) const
{
  return filterResult;
}

ExtensibleParameter_t& MonItemCreateResult_t::FilterResult(void)
{
  return filterResult;
}

} // namespace uasdk

#endif //UASDK_INCLUDE_SUBSCRIPTIONS
