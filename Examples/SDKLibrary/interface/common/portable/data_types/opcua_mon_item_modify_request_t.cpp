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

#include "opcua_mon_item_modify_request_t.h"

#if (UASDK_INCLUDE_SUBSCRIPTIONS > 0)

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(MonItemModifyRequest_t, Structure_t)

bool MonItemModifyRequest_t::operator==(MonItemModifyRequest_t const & obj) const
{
  return (
      (monitoredItemId == obj.monitoredItemId)
      && (requestedParameters == obj.requestedParameters));
}

bool MonItemModifyRequest_t::operator>(MonItemModifyRequest_t const & obj) const
{
  return (
      (monitoredItemId > obj.monitoredItemId)
      && (requestedParameters > obj.requestedParameters));
}

Status_t MonItemModifyRequest_t::CopyFrom(const BaseDataType_t& source)
{
  const MonItemModifyRequest_t* ptr = RuntimeCast<const MonItemModifyRequest_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t MonItemModifyRequest_t::CopyFrom(const MonItemModifyRequest_t& source)
{
  Status_t status = monitoredItemId.CopyFrom(source.monitoredItemId);
  if (status.IsBad())
  {
    return status;
  }

  status = requestedParameters.CopyFrom(source.requestedParameters);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t MonItemModifyRequest_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = monitoredItemId.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = requestedParameters.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t MonItemModifyRequest_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, MonItemModifyRequest_t& result)
{
  Status_t status = IntegerId_t::Decode(buffer, decoder, result.MonitoredItemId());
  if (status.IsBad())
  {
    return status;
  }

  status = MonParameters_t::Decode(buffer, decoder, result.RequestedParameters());
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

MonItemModifyRequest_t::MonItemModifyRequest_t()
{}

MonItemModifyRequest_t::~MonItemModifyRequest_t()
{}

bool MonItemModifyRequest_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool MonItemModifyRequest_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t MonItemModifyRequest_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t MonItemModifyRequest_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t MonItemModifyRequest_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_MonitoredItemModifyRequest_Encoding_DefaultBinary;
}

const IntegerId_t& MonItemModifyRequest_t::MonitoredItemId(void) const
{
  return monitoredItemId;
}

IntegerId_t& MonItemModifyRequest_t::MonitoredItemId(void)
{
  return monitoredItemId;
}

const MonParameters_t& MonItemModifyRequest_t::RequestedParameters(void) const
{
  return requestedParameters;
}

MonParameters_t& MonItemModifyRequest_t::RequestedParameters(void)
{
  return requestedParameters;
}

} // namespace uasdk

#endif //UASDK_INCLUDE_SUBSCRIPTIONS