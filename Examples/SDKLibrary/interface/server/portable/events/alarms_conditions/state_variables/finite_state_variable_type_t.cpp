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

#include "finite_state_variable_type_t.h"

#if ((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

namespace uasdk
{

FiniteStateVariableType_t::FiniteStateVariableType_t()
{
}

FiniteStateVariableType_t::~FiniteStateVariableType_t()
{
}

Status_t FiniteStateVariableType_t::Initialise(IntrusivePtr_t<NodeId_t> id_)
{
  id = id_;
  return OpcUa_Good;
}

IntrusivePtr_t<NodeId_t>& FiniteStateVariableType_t::Id(void) 
{ 
  return id;
}

IntrusivePtr_t<const NodeId_t> FiniteStateVariableType_t::Id(void) const 
{ 
  return id; 
}

IntrusivePtr_t<const QualifiedName_t> FiniteStateVariableType_t::Name(void) const
{
  return name;
}

IntrusivePtr_t<QualifiedName_t>& FiniteStateVariableType_t::Name(void)
{
  return name;
}

IntrusivePtr_t<const UInt32_t> FiniteStateVariableType_t::Number(void) const
{
  return number;
}

IntrusivePtr_t<UInt32_t>& FiniteStateVariableType_t::Number(void)
{
  return number;
}

IntrusivePtr_t<const LocalizedText_t> FiniteStateVariableType_t::EffectiveDisplayName(void) const
{
  return effectiveDisplayName;
}

IntrusivePtr_t<LocalizedText_t>& FiniteStateVariableType_t::EffectiveDisplayName(void)
{
  return effectiveDisplayName;
}

Status_t FiniteStateVariableType_t::CopyFrom(const FiniteStateVariableType_t& source)
{
  Status_t status;

  if(source.id.is_set())
  {
    status = source.Id()->CopyToNodeId(id);
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
  }

  if (source.Number().is_set())
  {
    if (!number.is_set())
    {
      number = new SafeRefCount_t<UInt32_t>();
      UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(number);
    }
    status = number->CopyFrom(*source.Number());
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
  }

  if (source.Name().is_set())
  {
    if (!name.is_set())
    {
      name = new SafeRefCount_t<QualifiedName_t>();
      UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(name);
    }
    status = name->CopyFrom(*source.Name());
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
  }

  if (source.EffectiveDisplayName().is_set())
  {
    if (!effectiveDisplayName.is_set())
    {
      effectiveDisplayName = new SafeRefCount_t<LocalizedText_t>();
      UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(effectiveDisplayName);
    }
    status = effectiveDisplayName->CopyFrom(*source.EffectiveDisplayName());
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
  }

  return status;
}

Status_t FiniteStateVariableType_t::CopyTo(IntrusivePtr_t<FiniteStateVariableType_t>& destination)
{
  IntrusivePtr_t<FiniteStateVariableType_t> destination_ = new SafeRefCount_t<FiniteStateVariableType_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(destination_);

  Status_t status = destination_->CopyFrom(*this);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  destination = destination_;
  return OpcUa_Good;
}

} //namespace uasdk

#endif //((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))
