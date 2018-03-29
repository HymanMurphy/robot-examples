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

#include "finite_state_machine_type_t.h"

#if ((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

namespace uasdk
{

FiniteStateMachineType_t::FiniteStateMachineType_t()
{
}

FiniteStateMachineType_t::~FiniteStateMachineType_t()
{
}

Status_t FiniteStateMachineType_t::Initialise()
{
  return OpcUa_Good;
}

IntrusivePtr_t<const FiniteStateVariableType_t> FiniteStateMachineType_t::CurrentStateProperties(void) const
{
  return currentStateProperties;
}

IntrusivePtr_t<const FiniteTransitionVariableType_t> FiniteStateMachineType_t::LastTransitionProperties(void) const
{
  return lastTransitionProperties;
}

IntrusivePtr_t<FiniteStateVariableType_t>& FiniteStateMachineType_t::CurrentStateProperties(void)
{
  return currentStateProperties;
}

IntrusivePtr_t<FiniteTransitionVariableType_t>& FiniteStateMachineType_t::LastTransitionProperties(void)
{
  return lastTransitionProperties;
}

IntrusivePtr_t<const ILocalizableText_t> FiniteStateMachineType_t::CurrentStateValue(void) const
{ 
  return currentStateValue; 
}

IntrusivePtr_t<const ILocalizableText_t> FiniteStateMachineType_t::LastTransitionValue(void) const
{ 
  return lastTransitionValue;
}

IntrusivePtr_t<ILocalizableText_t>& FiniteStateMachineType_t::CurrentStateValue(void)
{
  return currentStateValue;
}

IntrusivePtr_t<ILocalizableText_t>& FiniteStateMachineType_t::LastTransitionValue(void)
{
  return lastTransitionValue;
}

Status_t FiniteStateMachineType_t::CopyFrom(const FiniteStateMachineType_t& source)
{
  Status_t status;

  if (source.currentStateProperties.is_set())
  {
    status = source.currentStateProperties->CopyTo(currentStateProperties);
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
  }
  
  if (source.lastTransitionProperties.is_set())
  {
    status = source.lastTransitionProperties->CopyTo(lastTransitionProperties);
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
  }

  if (source.CurrentStateValue().is_set())
  {
    status = source.CurrentStateValue()->CopyTo(currentStateValue);
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
  }

  if (source.LastTransitionValue().is_set())
  {
    status = source.LastTransitionValue()->CopyTo(lastTransitionValue);
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
  }

  return status;
}

Status_t FiniteStateMachineType_t::CopyTo(IntrusivePtr_t<FiniteStateMachineType_t>& destination)
{
  IntrusivePtr_t<FiniteStateMachineType_t> destination_ = new SafeRefCount_t<FiniteStateMachineType_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(destination_);

  Status_t status = destination_->CopyFrom(*this);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  destination = destination_;
  return OpcUa_Good;
}

} //namespace uasdk

#endif //((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))
