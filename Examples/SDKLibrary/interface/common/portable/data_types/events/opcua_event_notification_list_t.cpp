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

#include "opcua_event_notification_list_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

namespace uasdk
{
  
UA_DEFINE_RUNTIME_TYPE(EventNotificationList_t, Structure_t)

EventNotificationList_t::EventNotificationList_t()
{
}

EventNotificationList_t::~EventNotificationList_t()
{
}

bool EventNotificationList_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool EventNotificationList_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t EventNotificationList_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t EventNotificationList_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t EventNotificationList_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_EventNotificationList_Encoding_DefaultBinary;
}

const ArrayUA_t<EventFieldList_t>& EventNotificationList_t::Events(void) const
{
	return events;
}

ArrayUA_t<EventFieldList_t>& EventNotificationList_t::Events(void)
{
	return events;
}

EventNotificationList_t& EventNotificationList_t::operator=(EventNotificationList_t const & other)
{
  if (this != &other)
  {
    events.CopyFrom(other.events);
  }
  return *this;
}

bool EventNotificationList_t::operator==(EventNotificationList_t const & obj) const
{
  return (events == obj.events);
}

bool EventNotificationList_t::operator>(EventNotificationList_t const & obj) const
{
  return (events > obj.events);
}

Status_t EventNotificationList_t::CopyFrom(const EventNotificationList_t& source)
{
  Status_t status = OpcUa_Good;

  status = events.CopyFrom(source.events);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t EventNotificationList_t::CopyFrom(const BaseDataType_t& source)
{
  const EventNotificationList_t* ptr = RuntimeCast<const EventNotificationList_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t EventNotificationList_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = events.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t EventNotificationList_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, EventNotificationList_t& result)
{
  Status_t status = ArrayUA_t<EventFieldList_t>::Decode(buffer, decoder, result.Events());
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}
	
} // namespace uasdk

#endif // UASDK_INCLUDE_EVENTS


