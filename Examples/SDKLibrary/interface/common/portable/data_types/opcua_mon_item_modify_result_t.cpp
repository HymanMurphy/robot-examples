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

#include "opcua_mon_item_modify_result_t.h"

#if (UASDK_INCLUDE_SUBSCRIPTIONS > 0)

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(MonItemModifyResult_t, Structure_t)

bool MonItemModifyResult_t::operator==(MonItemModifyResult_t const & obj) const
{
  return (
      (statusCode == obj.statusCode)
      && (revisedSamplingInterval == obj.revisedSamplingInterval)
      && (revisedQueueSize == obj.revisedQueueSize)
      && (filterResult == obj.filterResult));
}

bool MonItemModifyResult_t::operator>(MonItemModifyResult_t const & obj) const
{
  return (
      (statusCode > obj.statusCode)
      && (revisedSamplingInterval > obj.revisedSamplingInterval)
      && (revisedQueueSize > obj.revisedQueueSize)
      && (filterResult > obj.filterResult));
}

Status_t MonItemModifyResult_t::CopyFrom(const BaseDataType_t& source)
{
  const MonItemModifyResult_t* ptr = RuntimeCast<const MonItemModifyResult_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t MonItemModifyResult_t::CopyFrom(const MonItemModifyResult_t& source)
{
  Status_t status = statusCode.CopyFrom(source.statusCode);
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

Status_t MonItemModifyResult_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = statusCode.Encode(encoder, buffer);
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

Status_t MonItemModifyResult_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, MonItemModifyResult_t& result)
{
  Status_t status = StatusCode_t::Decode(buffer, decoder, result.StatusCode());
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

MonItemModifyResult_t::MonItemModifyResult_t()
{}

MonItemModifyResult_t::~MonItemModifyResult_t()
{}

bool MonItemModifyResult_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool MonItemModifyResult_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t MonItemModifyResult_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t MonItemModifyResult_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t MonItemModifyResult_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_MonitoredItemModifyResult_Encoding_DefaultBinary;
}

const StatusCode_t& MonItemModifyResult_t::StatusCode(void) const
{
  return statusCode;
}

StatusCode_t& MonItemModifyResult_t::StatusCode(void)
{
  return statusCode;
}

const Duration_t& MonItemModifyResult_t::RevisedSamplingInterval(void) const
{
  return revisedSamplingInterval;
}

Duration_t& MonItemModifyResult_t::RevisedSamplingInterval(void)
{
  return revisedSamplingInterval;
}

const Counter_t& MonItemModifyResult_t::RevisedQueueSize(void) const
{
  return revisedQueueSize;
}

Counter_t& MonItemModifyResult_t::RevisedQueueSize(void)
{
  return revisedQueueSize;
}

const ExtensibleParameter_t& MonItemModifyResult_t::FilterResult(void) const
{
  return filterResult;
}

ExtensibleParameter_t& MonItemModifyResult_t::FilterResult(void)
{
  return filterResult;
}

} // namespace uasdk

#endif //UASDK_INCLUDE_SUBSCRIPTIONS

