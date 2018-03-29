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

#include "write_mask_t.h"

namespace uasdk
{

void WriteMask_t::SetOrClear(bool val, uint32_t bit)
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

WriteMask_t::WriteMask_t() 
{}

WriteMask_t::WriteMask_t(uint32_t val) 
  : UInt32_t(val) 
{}

WriteMask_t::WriteMask_t(WriteMask_t const & other) 
  : UInt32_t() 
{
  value = other.value; 
}

WriteMask_t::~WriteMask_t() 
{}

WriteMask_t& WriteMask_t::operator=(WriteMask_t const & rhs)
{
  value = rhs.value;
  return *this;
}

uint32_t WriteMask_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

bool WriteMask_t::AccessLevel(void) const
{
  return value & (1 << BIT_ACCESS_LEVEL);
}

void WriteMask_t::AccessLevel(bool val)
{
  SetOrClear(val, BIT_ACCESS_LEVEL);
}

bool WriteMask_t::ArrayDimensions(void) const
{
  return (value & (1 << BIT_ARRAY_DIMENSIONS)) != 0;
}

void WriteMask_t::ArrayDimensions(bool val)
{
  SetOrClear(val, BIT_ARRAY_DIMENSIONS);
}

bool WriteMask_t::BrowseName(void) const
{
  return (value & (1 << BIT_BROWSE_NAME)) != 0;
}

void WriteMask_t::BrowseName(bool val)
{
  SetOrClear(val, BIT_BROWSE_NAME);
}

bool WriteMask_t::ContainsNoLoops(void) const
{
  return (value & (1 << BIT_CONTAINS_NO_LOOPS)) != 0;
}

void WriteMask_t::ContainsNoLoops(bool val)
{
  SetOrClear(val, BIT_CONTAINS_NO_LOOPS);
}

bool WriteMask_t::DataType(void) const
{
  return (value & (1 << BIT_DATA_TYPE)) != 0;
}

void WriteMask_t::DataType(bool val)
{
  SetOrClear(val, BIT_DATA_TYPE);
}

bool WriteMask_t::Description(void) const
{
  return (value & (1 << BIT_DESCRIPTION)) != 0;
}

void WriteMask_t::Description(bool val)
{
  SetOrClear(val, BIT_DESCRIPTION);
}

bool WriteMask_t::DisplayName(void) const
{
  return (value & (1 << BIT_DISPLAY_NAME)) != 0;
}

void WriteMask_t::DisplayName(bool val)
{
  SetOrClear(val, BIT_DISPLAY_NAME);
}

bool WriteMask_t::EventNotifier(void) const
{
  return (value & (1 << BIT_EVENT_NOTIFIER)) != 0;
}

void WriteMask_t::EventNotifier(bool val)
{
  SetOrClear(val, BIT_EVENT_NOTIFIER);
}

bool WriteMask_t::Executable(void) const
{
  return (value & (1 << BIT_EXECUTABLE)) != 0;
}

void WriteMask_t::Executable(bool val)
{
  SetOrClear(val, BIT_EXECUTABLE);
}

bool WriteMask_t::Historizing(void) const
{
  return (value & (1 << BIT_HISTORIZING)) != 0;
}

void WriteMask_t::Historizing(bool val)
{
  SetOrClear(val, BIT_HISTORIZING);
}

bool WriteMask_t::InverseName(void) const
{
  return (value & (1 << BIT_INVERSE_NAME)) != 0;
}

void WriteMask_t::InverseName(bool val)
{
  SetOrClear(val, BIT_INVERSE_NAME);
}

bool WriteMask_t::IsAbstract(void) const
{
  return (value & (1 << BIT_IS_ABSTRACT)) != 0;
}

void WriteMask_t::IsAbstract(bool val)
{
  SetOrClear(val, BIT_IS_ABSTRACT);
}

bool WriteMask_t::MinimumSamplingInterval(void) const
{
  return (value & (1 << BIT_MINIMUM_SAMPLING_INTERVAL)) != 0;
}

void WriteMask_t::MinimumSamplingInterval(bool val)
{
  SetOrClear(val, BIT_MINIMUM_SAMPLING_INTERVAL);
}

bool WriteMask_t::NodeClass(void) const
{
  return (value & (1 << BIT_NODE_CLASS)) != 0;
}

void WriteMask_t::NodeClass(bool val)
{
  SetOrClear(val, BIT_NODE_CLASS);
}

bool WriteMask_t::NodeId(void) const
{
  return (value & (1 << BIT_NODE_ID)) != 0;
}

void WriteMask_t::NodeId(bool val)
{
  SetOrClear(val, BIT_NODE_ID);
}

bool WriteMask_t::Symmetric(void) const
{
  return (value & (1 << BIT_SYMMETRIC)) != 0;
}

void WriteMask_t::Symmetric(bool val)
{
  SetOrClear(val, BIT_SYMMETRIC);
}

bool WriteMask_t::UserAccessLevel(void) const
{
  return (value & (1 << BIT_USER_ACCESS_LEVEL)) != 0;
}

void WriteMask_t::UserAccessLevel(bool val)
{
  SetOrClear(val, BIT_USER_ACCESS_LEVEL);
}

bool WriteMask_t::UserExecutable(void) const
{
  return (value & (1 << BIT_USER_EXECUTABLE)) != 0;
}

void WriteMask_t::UserExecutable(bool val)
{
  SetOrClear(val, BIT_USER_EXECUTABLE);
}

bool WriteMask_t::UserWriteMask(void) const
{
  return (value & (1 << BIT_USER_WRITEMASK)) != 0;
}

void WriteMask_t::UserWriteMask(bool val)
{
  SetOrClear(val, BIT_USER_WRITEMASK);
}

bool WriteMask_t::ValueRank(void) const
{
  return (value & (1 << BIT_VALUE_RANK)) != 0;
}

void WriteMask_t::ValueRank(bool val)
{
  SetOrClear(val, BIT_VALUE_RANK);
}

bool WriteMask_t::WriteMask(void) const
{
  return (value & (1 << BIT_WRITE_MASK)) != 0;
}

void WriteMask_t::WriteMask(bool val)
{
  SetOrClear(val, BIT_WRITE_MASK);
}

bool WriteMask_t::ValueForVariableType(void) const
{
  return (value & (1 << BIT_VALUE_FOR_VARIABLE_TYPE)) != 0;
}

void WriteMask_t::ValueForVariableType(bool val)
{
  SetOrClear(val, BIT_VALUE_FOR_VARIABLE_TYPE);
}

bool WriteMask_t::IsSet(AttributeId_t::Enum_t attributeId)
{
  switch (attributeId)
  {
  case AttributeId_t::ATTRIBUTE_ID_NODEID:
    return NodeId();

  case AttributeId_t::ATTRIBUTE_ID_NODECLASS:
    return NodeClass();

  case AttributeId_t::ATTRIBUTE_ID_BROWSENAME:
    return BrowseName();

  case AttributeId_t::ATTRIBUTE_ID_DISPLAYNAME:
    return DisplayName();

  case AttributeId_t::ATTRIBUTE_ID_DESCRIPTION:
    return Description();

  case AttributeId_t::ATTRIBUTE_ID_WRITEMASK:
    return WriteMask();

  case AttributeId_t::ATTRIBUTE_ID_USERWRITEMASK:
    return UserWriteMask();

  case AttributeId_t::ATTRIBUTE_ID_ISABSTRACT:
    return IsAbstract();

  case AttributeId_t::ATTRIBUTE_ID_SYMMETRIC:
    return Symmetric();

  case AttributeId_t::ATTRIBUTE_ID_INVERSENAME:
    return InverseName();

  case AttributeId_t::ATTRIBUTE_ID_CONTAINSNOLOOPS:
    return ContainsNoLoops();

  case AttributeId_t::ATTRIBUTE_ID_EVENTNOTIFIER:
    return EventNotifier();

  case AttributeId_t::ATTRIBUTE_ID_VALUE:
    return ValueForVariableType();

  case AttributeId_t::ATTRIBUTE_ID_DATATYPE:
    return DataType();

  case AttributeId_t::ATTRIBUTE_ID_VALUERANK:
    return ValueRank();

  case AttributeId_t::ATTRIBUTE_ID_ARRAYDIMENSIONS:
    return ArrayDimensions();

  case AttributeId_t::ATTRIBUTE_ID_ACCESSLEVEL:
    return AccessLevel();

  case AttributeId_t::ATTRIBUTE_ID_USERACCESSLEVEL:
    return UserAccessLevel();

  case AttributeId_t::ATTRIBUTE_ID_MINIMUMSAMPLINGINTERVAL:
    return MinimumSamplingInterval();

  case AttributeId_t::ATTRIBUTE_ID_HISTORIZING:
    return Historizing();

  case AttributeId_t::ATTRIBUTE_ID_EXECUTABLE:
    return Executable();

  case AttributeId_t::ATTRIBUTE_ID_USEREXECUTABLE:
    return UserExecutable();

  default:
    break;
  }
  return false;
}

}