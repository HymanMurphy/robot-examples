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

#include "opcua_mon_item_create_request_t.h"

#if (UASDK_INCLUDE_SUBSCRIPTIONS > 0)

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(MonItemCreateRequest_t, Structure_t)

bool MonItemCreateRequest_t::operator==(MonItemCreateRequest_t const & obj) const
{
  return (
      (itemToMonitor == obj.itemToMonitor)
      && (monitoringMode == obj.monitoringMode)
      && (requestedParameters == obj.requestedParameters));
}

bool MonItemCreateRequest_t::operator>(MonItemCreateRequest_t const & obj) const
{
  return (
      (itemToMonitor == obj.itemToMonitor)
      && (monitoringMode == obj.monitoringMode)
      && (requestedParameters == obj.requestedParameters));
}

Status_t MonItemCreateRequest_t::CopyFrom(const BaseDataType_t& source)
{
  const MonItemCreateRequest_t* ptr = RuntimeCast<const MonItemCreateRequest_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t MonItemCreateRequest_t::CopyFrom(const MonItemCreateRequest_t& source)
{
  Status_t status = itemToMonitor.CopyFrom(source.itemToMonitor);
  if (status.IsBad())
  {
    return status;
  }

  status = monitoringMode.CopyFrom(source.monitoringMode);
  if (status.IsBad())
  {
    return status;
  }

  status = requestedParameters.CopyFrom(source.requestedParameters);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t MonItemCreateRequest_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = itemToMonitor.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = monitoringMode.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = requestedParameters.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return 0;
}

Status_t MonItemCreateRequest_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, MonItemCreateRequest_t& result)
{
  Status_t status = ReadValueId_t::Decode(buffer, decoder, result.ItemToMonitor());
  if (status.IsBad())
  {
    return status;
  }

  status = MonitoringMode_t::Decode(buffer, decoder, result.MonitoringMode());
  if (status.IsBad())
  {
    return status;
  }

  status = MonParameters_t::Decode(buffer, decoder, result.RequestedParameters());
  if (status.IsBad())
  {
    return status;
  }

  return 0;
}

MonItemCreateRequest_t::MonItemCreateRequest_t()
{}

MonItemCreateRequest_t::~MonItemCreateRequest_t()
{}

bool MonItemCreateRequest_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool MonItemCreateRequest_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t MonItemCreateRequest_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t MonItemCreateRequest_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t MonItemCreateRequest_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_MonitoredItemCreateRequest_Encoding_DefaultBinary;
}

const ReadValueId_t& MonItemCreateRequest_t::ItemToMonitor(void) const
{
  return itemToMonitor;
}

ReadValueId_t& MonItemCreateRequest_t::ItemToMonitor(void)
{
  return itemToMonitor;
}

const MonitoringMode_t& MonItemCreateRequest_t::MonitoringMode(void) const
{
  return monitoringMode;
}

MonitoringMode_t& MonItemCreateRequest_t::MonitoringMode(void)
{
  return monitoringMode;
}

const MonParameters_t& MonItemCreateRequest_t::RequestedParameters(void) const
{
  return requestedParameters;
}

MonParameters_t& MonItemCreateRequest_t::RequestedParameters(void)
{
  return requestedParameters;
}

} // namespace uasdk

#endif //UASDK_INCLUDE_SUBSCRIPTIONS
