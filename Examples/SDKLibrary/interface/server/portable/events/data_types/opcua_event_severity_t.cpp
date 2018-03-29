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

#include "opcua_event_severity_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "opcua_int32_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(EventSeverity_t, Enumeration_t)

EventSeverity_t::EventSeverity_t(void) : value(OPCUA_EVENT_SEVERITY_LOW)
{
}

EventSeverity_t::EventSeverity_t(Enum_t value_)
{
  value = value_;
}

bool EventSeverity_t::operator==(EventSeverity_t const & obj) const
{
  return value == obj.value;
}

bool EventSeverity_t::operator>(EventSeverity_t const & obj) const
{
  return value > obj.value;
}

Status_t EventSeverity_t::CopyFrom(const BaseDataType_t& source)
{
  const EventSeverity_t* ptr = RuntimeCast<const EventSeverity_t *>(source);
  if(!ptr)
  {
    return TryCopyFromInt32(source);
  }

  return CopyFrom(*ptr);
}

Status_t EventSeverity_t::CopyFrom(const EventSeverity_t& source)
{
  Status_t status = OpcUa_BadOutOfRange;

  if ( (source.value < OPCUA_EVENT_SEVERITY_MIN) || (source.value > OPCUA_EVENT_SEVERITY_MAX) )
  {
    return status;
  }

  value = source.value;

  return OpcUa_Good;
}

Status_t EventSeverity_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Int32_t raw_val((int32_t)value);
  Status_t status = raw_val.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t EventSeverity_t::WriteIntToValue(int32_t newValue)
{
  if ((newValue < 0) || (newValue >= OPCUA_EVENT_SEVERITY_MAX))
  {
	  UASDK_RETURN_BAD_STATUS(OpcUa_BadDecodingError);
  }
  else
  {
	value = static_cast<Enum_t>(newValue);
  }
  return OpcUa_Good;
}

EventSeverity_t::~EventSeverity_t()
{}

bool EventSeverity_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool EventSeverity_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t EventSeverity_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t EventSeverity_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

const EventSeverity_t::Enum_t& EventSeverity_t::Value(void) const
{
  return value;
}

EventSeverity_t::Enum_t& EventSeverity_t::Value(void)
{
  return value;
}

} // namespace uasdk

#endif //UASDK_INCLUDE_EVENTS
