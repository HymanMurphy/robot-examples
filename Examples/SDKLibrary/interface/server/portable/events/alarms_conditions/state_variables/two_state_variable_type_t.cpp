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

#include "two_state_variable_type_t.h"

#if ((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

namespace uasdk
{

TwoStateVariableType_t::TwoStateVariableType_t()
{
  
}

TwoStateVariableType_t::~TwoStateVariableType_t()
{
}

Status_t TwoStateVariableType_t::Initialise(bool initialState,
  IntrusivePtr_t<ILocalizableText_t> trueState_,
  IntrusivePtr_t<ILocalizableText_t> falseState_)
{
  id = new SafeRefCount_t<Boolean_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(id);

  effectiveTransitionTime = new SafeRefCount_t<UtcTime_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(effectiveTransitionTime);

  transitionTime = new SafeRefCount_t<UtcTime_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(transitionTime);

  id->Value(initialState == true);
  trueState = trueState_;
  falseState = falseState_;
 
  return OpcUa_Good;
}

IntrusivePtr_t<Boolean_t>& TwoStateVariableType_t::Id(void)
{ 
  return id;
}

IntrusivePtr_t<const Boolean_t> TwoStateVariableType_t::Id(void) const
{ 
  return id; 
}

IntrusivePtr_t<UtcTime_t>& TwoStateVariableType_t::TransitionTime(void)
{ 
  return transitionTime; 
}

IntrusivePtr_t<const UtcTime_t> TwoStateVariableType_t::TransitionTime(void) const
{ 
  return transitionTime; 
}

IntrusivePtr_t<UtcTime_t>& TwoStateVariableType_t::EffectiveTransitionTime(void)
{ 
  return effectiveTransitionTime; 
}

IntrusivePtr_t<const UtcTime_t> TwoStateVariableType_t::EffectiveTransitionTime(void) const
{ 
  return effectiveTransitionTime;
}

IntrusivePtr_t<const ILocalizableText_t> TwoStateVariableType_t::TrueState(void) const 
{ 
  return trueState; 
}

IntrusivePtr_t<const ILocalizableText_t> TwoStateVariableType_t::FalseState(void) const 
{ 
  return falseState; 
}

IntrusivePtr_t<ILocalizableText_t>& TwoStateVariableType_t::TrueState(void)
{
  return trueState;
}

IntrusivePtr_t<ILocalizableText_t>& TwoStateVariableType_t::FalseState(void)
{
  return falseState;
}

IntrusivePtr_t<const QualifiedName_t> TwoStateVariableType_t::Name(void) const
{
  return name;
}

IntrusivePtr_t<QualifiedName_t>& TwoStateVariableType_t::Name(void)
{
  return name;
}

IntrusivePtr_t<const UInt32_t> TwoStateVariableType_t::Number(void) const
{
  return number;
}

IntrusivePtr_t<UInt32_t>& TwoStateVariableType_t::Number(void)
{
  return number;
}

IntrusivePtr_t<const LocalizedText_t> TwoStateVariableType_t::EffectiveDisplayName(void) const
{
  return effectiveDisplayName;
}

IntrusivePtr_t<LocalizedText_t>& TwoStateVariableType_t::EffectiveDisplayName(void)
{
  return effectiveDisplayName;
}

IntrusivePtr_t<const ILocalizableText_t> TwoStateVariableType_t::Value(void)
{
  if (id->Value())
  {
    return trueState;
  }
  else
  {
    return falseState;
  }
}

Status_t TwoStateVariableType_t::CopyFrom(const TwoStateVariableType_t& source)
{
  UASDK_RETURN_INVALID_ARGUMENT_IF_NULL(source.id);
  UASDK_RETURN_INVALID_ARGUMENT_IF_NULL(source.effectiveTransitionTime);
  UASDK_RETURN_INVALID_ARGUMENT_IF_NULL(source.transitionTime);

  if (!id.is_set())
  {
    id = new SafeRefCount_t<Boolean_t>();
    UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(id);
  }
  Status_t status = id->CopyFrom(*source.id);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  if (!effectiveTransitionTime.is_set())
  {
    effectiveTransitionTime = new SafeRefCount_t<UtcTime_t>();
    UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(id);
  }
  status = effectiveTransitionTime->CopyFrom(*source.effectiveTransitionTime);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  if (!transitionTime.is_set())
  {
    transitionTime = new SafeRefCount_t<UtcTime_t>();
    UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(id);
  }

  status = transitionTime->CopyFrom(*source.transitionTime);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  if (source.TrueState().is_set())
  {
    status = source.TrueState()->CopyTo(trueState);
    UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
  }

  if (source.FalseState().is_set())
  {
    status = source.FalseState()->CopyTo(falseState);
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

Status_t TwoStateVariableType_t::CopyTo(IntrusivePtr_t<TwoStateVariableType_t>& destination)
{
  IntrusivePtr_t<TwoStateVariableType_t> destination_ = new SafeRefCount_t<TwoStateVariableType_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(destination_);

  Status_t status = destination_->CopyFrom(*this);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  destination = destination_;
  return OpcUa_Good;
}

} //namespace uasdk

#endif //((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))
