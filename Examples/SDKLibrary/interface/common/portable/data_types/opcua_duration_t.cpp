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

#include "opcua_duration_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(Duration_t, Double_t)

Duration_t::Duration_t() 
{}

Duration_t::Duration_t(double val) : Double_t(val) {}
Duration_t::Duration_t(Duration_t const & other) : Double_t() { value = other.value; }
Duration_t::~Duration_t() {}

uint32_t Duration_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

Duration_t& Duration_t::operator=(Duration_t const & obj)
{
  value = obj.value;
  return *this;
}

Duration_t& Duration_t::operator=(double const & obj)
{
  value = obj;
  return *this;
}

bool Duration_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool Duration_t::operator==(Duration_t const & obj) const
{
  return (value == obj.value) || ((value != value) && (obj.value != obj.value));
}

bool Duration_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

bool Duration_t::operator>(Duration_t const & obj) const
{
  return Double_t::operator >(obj);
}

Status_t Duration_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

Status_t Duration_t::CopyFrom(const Duration_t& source)
{
  value = source.value;
  return OpcUa_Good;
}

Status_t Duration_t::CopyFrom(const BaseDataType_t& source)
{
  const Duration_t* ptr = RuntimeCast<const Duration_t *>(source);
  if (!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

}
