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


#include "event_notifier_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(EventNotifier_t, Byte_t)
  
void EventNotifier_t::SetOrClear(bool val, uint32_t bit)
{
  if (bit < BIT_RESERVED)
  {
    if (val)
    {
      value |= (1 << bit);
    }
    else
    {
      value &= ~(1 << bit);
    }
  }
}


EventNotifier_t::EventNotifier_t() 
{}

EventNotifier_t::EventNotifier_t(uint8_t val) : Byte_t(val) 
{}
    
EventNotifier_t::EventNotifier_t(EventNotifier_t const & other) :Byte_t() 
{
  value = other.value; 
}
    
EventNotifier_t::~EventNotifier_t() 
{}

uint32_t EventNotifier_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

bool EventNotifier_t::SubscribeToEvents(void) const
{
  return (value & (1 << BIT_SUBSCRIBE_TO_EVENTS)) != 0;
}

void EventNotifier_t::SubscribeToEvents(bool val)
{
  SetOrClear(val, BIT_SUBSCRIBE_TO_EVENTS);
}

bool EventNotifier_t::HistoryRead(void) const
{
  return (value & (1 << BIT_HISTORY_READ)) != 0;
}

void EventNotifier_t::HistoryRead(bool val)
{
  SetOrClear(val, BIT_HISTORY_READ);
}

bool EventNotifier_t::HistoryWrite(void) const
{
  return (value & (1 << BIT_HISTORY_WRITE)) != 0;
}

void EventNotifier_t::HistoryWrite(bool val)
{
  SetOrClear(val, BIT_HISTORY_WRITE);
}

} // namespace uasdk


