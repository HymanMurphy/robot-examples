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

#include "opcua_mon_parameters_t.h"

#if (UASDK_INCLUDE_SUBSCRIPTIONS > 0)

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(MonParameters_t, Structure_t)

bool MonParameters_t::operator==(MonParameters_t const & obj) const
{
  return (
      (clientHandle == obj.clientHandle)
      && (samplingInterval == obj.samplingInterval)
      && (filter == obj.filter)
      && (queueSize == obj.queueSize)
      && (discardOldest == obj.discardOldest));
}

bool MonParameters_t::operator>(MonParameters_t const & obj) const
{
  return (
      (clientHandle > obj.clientHandle)
      && (samplingInterval > obj.samplingInterval)
      && (filter > obj.filter)
      && (queueSize > obj.queueSize)
      && (discardOldest > obj.discardOldest));
}

Status_t MonParameters_t::CopyFrom(const BaseDataType_t& source)
{
  const MonParameters_t* ptr = RuntimeCast<const MonParameters_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t MonParameters_t::CopyFrom(const MonParameters_t& source)
{
  Status_t status = clientHandle.CopyFrom(source.clientHandle);
  if (status.IsBad())
  {
    return status;
  }

  status = samplingInterval.CopyFrom(source.samplingInterval);
  if (status.IsBad())
  {
    return status;
  }

  if(source.filter.Payload().is_set())
  {
    status = filter.CopyFrom(source.filter);
    if (status.IsBad())
    {
      return status;
    }
  }
  else
  {
    filter.Payload().reset();
  }

  status = queueSize.CopyFrom(source.queueSize);
  if (status.IsBad())
  {
    return status;
  }

  status = discardOldest.CopyFrom(source.discardOldest);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t MonParameters_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = clientHandle.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = samplingInterval.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = filter.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = queueSize.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = discardOldest.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t MonParameters_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, MonParameters_t& result)
{
  Status_t status = UInt32_t::Decode(buffer, decoder, result.ClientHandle());
  if (status.IsBad())
  {
    return status;
  }

  status = Duration_t::Decode(buffer, decoder, result.SamplingInterval());
  if (status.IsBad())
  {
    return status;
  }

  status = ExtensibleParameter_t::Decode(buffer, decoder, result.Filter());
  if (status.IsBad())
  {
    return status;
  }

  status = Counter_t::Decode(buffer, decoder, result.QueueSize());
  if (status.IsBad())
  {
    return status;
  }

  status = Boolean_t::Decode(buffer, decoder, result.DiscardOldest());
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

MonParameters_t::MonParameters_t()
{}

MonParameters_t::~MonParameters_t() 
{}

bool MonParameters_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool MonParameters_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t MonParameters_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t MonParameters_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t MonParameters_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_MonitoringParameters_Encoding_DefaultBinary;
}

const UInt32_t& MonParameters_t::ClientHandle(void) const
{
  return clientHandle;
}

UInt32_t& MonParameters_t::ClientHandle(void)
{
  return clientHandle;
}

const Duration_t& MonParameters_t::SamplingInterval(void) const
{
  return samplingInterval;
}

Duration_t& MonParameters_t::SamplingInterval(void)
{
  return samplingInterval;
}

const ExtensibleParameter_t& MonParameters_t::Filter(void) const
{
  return filter;
}

ExtensibleParameter_t& MonParameters_t::Filter(void)
{
  return filter;
}

const Counter_t& MonParameters_t::QueueSize(void) const
{
  return queueSize;
}

Counter_t& MonParameters_t::QueueSize(void)
{
  return queueSize;
}

const Boolean_t& MonParameters_t::DiscardOldest(void) const
{
  return discardOldest;
}

Boolean_t& MonParameters_t::DiscardOldest(void)
{
  return discardOldest;
}


} // namespace uasdk

#endif //UASDK_INCLUDE_SUBSCRIPTIONS
