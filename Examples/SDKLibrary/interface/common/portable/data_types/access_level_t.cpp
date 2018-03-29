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

#include "access_level_t.h"
namespace uasdk
{

void AccessLevel_t::SetOrClear(bool val, uint32_t bit)
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

AccessLevel_t::AccessLevel_t() 
{}

AccessLevel_t::AccessLevel_t(uint8_t val)
  : Byte_t(val) 
{}

AccessLevel_t::AccessLevel_t(AccessLevel_t const & other) 
  : Byte_t() 
{
  value = other.value; 
}

AccessLevel_t::~AccessLevel_t()
{}

uint32_t AccessLevel_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

bool AccessLevel_t::CurrentRead(void) const
{
  return value & (1 << BIT_CURRENT_READ);
}

void AccessLevel_t::CurrentRead(bool val)
{
  SetOrClear(val, BIT_CURRENT_READ);
}

bool AccessLevel_t::CurrentWrite(void) const
{
  return (value & (1 << BIT_CURRENT_WRITE)) != 0;
}

void AccessLevel_t::CurrentWrite(bool val)
{
  SetOrClear(val, BIT_CURRENT_WRITE);
}

bool AccessLevel_t::HistoryRead(void) const
{
  return (value & (1 << BIT_HISTORY_READ)) != 0;
}

void AccessLevel_t::HistoryRead(bool val)
{
  SetOrClear(val, BIT_HISTORY_READ);
}

bool AccessLevel_t::HistoryWrite(void) const
{
  return (value & (1 << BIT_HISTORY_WRITE)) != 0;
}

void AccessLevel_t::StatusWrite(bool val)
{
  SetOrClear(val, BIT_HISTORY_WRITE);
}

bool AccessLevel_t::StatusWrite(void) const
{
  return (value & (1 << BIT_STATUS_WRITE)) != 0;
}

void AccessLevel_t::TimestampWrite(bool val)
{
  SetOrClear(val, BIT_STATUS_WRITE);
}

bool AccessLevel_t::TimestampWrite(void) const
{
  return (value & (1 << BIT_TIMESTAMP_WRITE)) != 0;
}

void AccessLevel_t::HistoryWrite(bool val)
{
  SetOrClear(val, BIT_TIMESTAMP_WRITE);
}

}