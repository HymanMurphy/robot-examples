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

#include "opcua_event_field_list_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

namespace uasdk
{
  
UA_DEFINE_RUNTIME_TYPE(EventFieldList_t, Structure_t)

EventFieldList_t::EventFieldList_t()
{
}

EventFieldList_t::~EventFieldList_t()
{
}

bool EventFieldList_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool EventFieldList_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t EventFieldList_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t EventFieldList_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t EventFieldList_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_EventFieldList_Encoding_DefaultBinary;
}

const ArrayUA_t<BaseDataType_t>& EventFieldList_t::EventFields(void) const
{
	return eventFields;
}

ArrayUA_t<BaseDataType_t>& EventFieldList_t::EventFields(void)
{
	return eventFields;
}

const IntegerId_t& EventFieldList_t::ClientHandle(void) const
{
  return clientHandle;
}

IntegerId_t& EventFieldList_t::ClientHandle(void)
{
  return clientHandle;
}

EventFieldList_t& EventFieldList_t::operator=(EventFieldList_t const & other)
{
  if (this != &other)
  {
    clientHandle.CopyFrom(other.clientHandle);
    eventFields.CopyFrom(other.eventFields);
  }
  return *this;
}

bool EventFieldList_t::operator==(EventFieldList_t const & obj) const
{
  return (
     (clientHandle == obj.clientHandle)
      && (eventFields == obj.eventFields));
}

bool EventFieldList_t::operator>(EventFieldList_t const & obj) const
{
  return (
      (clientHandle > obj.clientHandle)
      && (eventFields > obj.eventFields));
}

Status_t EventFieldList_t::CopyFrom(const EventFieldList_t& source)
{
  Status_t status = OpcUa_Good;

  status = clientHandle.CopyFrom(source.clientHandle);
  if (status.IsBad())
  {
    return status;
  }

  status = eventFields.CopyFrom(source.eventFields);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t EventFieldList_t::CopyFrom(const BaseDataType_t& source)
{
  const EventFieldList_t* ptr = RuntimeCast<const EventFieldList_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t EventFieldList_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = clientHandle.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = eventFields.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t EventFieldList_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, IntrusivePtr_t<EventFieldList_t>& result)
{
  Status_t status = IntegerId_t::Decode(buffer, decoder, result->ClientHandle());
  if (status.IsBad())
  {
    return status;
  }

  status = ArrayUA_t<BaseDataType_t>::Decode(buffer, decoder, result->EventFields());
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}
	
} // namespace uasdk

#endif // UASDK_INCLUDE_EVENTS

