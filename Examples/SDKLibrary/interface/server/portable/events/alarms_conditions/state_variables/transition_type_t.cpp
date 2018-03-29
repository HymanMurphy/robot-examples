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

#include "transition_type_t.h"

#if ((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

namespace uasdk
{

TransitionType_t::TransitionType_t() : transitionNumber(0)
{
}

TransitionType_t::~TransitionType_t()
{
}

Status_t TransitionType_t::Initialise()
{
  return OpcUa_Good;
}

const UInt32_t TransitionType_t::TransitionNumber(void) const
{ 
  return transitionNumber; 
}

UInt32_t& TransitionType_t::TransitionNumber(void)
{ 
  return transitionNumber;
}

Status_t TransitionType_t::CopyFrom(const TransitionType_t& source)
{
  return transitionNumber.CopyFrom(source.TransitionNumber());
}

Status_t TransitionType_t::CopyTo(IntrusivePtr_t<TransitionType_t>& destination)
{
  IntrusivePtr_t<TransitionType_t> destination_ = new SafeRefCount_t<TransitionType_t>();
  UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(destination_);

  Status_t status = destination_->CopyFrom(*this);
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());

  destination = destination_;

  return OpcUa_Good;
}

} //namespace uasdk

#endif //((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))
