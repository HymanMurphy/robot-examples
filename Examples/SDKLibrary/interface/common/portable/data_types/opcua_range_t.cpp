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

#include "opcua_range_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(Range_t, Structure_t)

bool Range_t::operator==(Range_t const & obj) const
{
  return (
      (low == obj.low)
      && (high == obj.high));
}

bool Range_t::operator>(Range_t const & obj) const
{
  return (
       (low > obj.low)
       && (high > obj.high));
}

Status_t Range_t::CopyFrom(const BaseDataType_t& source)
{
  const Range_t* ptr = RuntimeCast<const Range_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t Range_t::CopyFrom(const Range_t& source)
{
  Status_t status = low.CopyFrom(source.low);
  if (status.IsBad())
  {
    return status;
  }

  status = high.CopyFrom(source.high);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t Range_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = low.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = high.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t Range_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, Range_t& result)
{
  Status_t status = Double_t::Decode(buffer, decoder, result.Low());
  if (status.IsBad())
  {
    return status;
  }

  status = Double_t::Decode(buffer, decoder, result.High());
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Range_t::Range_t()
  : low(0), high(0)
{}

Range_t::Range_t(double low_, double high_)
  : low(low_), high(high_)
{}

Range_t::~Range_t()
{}

bool Range_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool Range_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t Range_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t Range_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t Range_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_Range_Encoding_DefaultBinary;
}

const Double_t& Range_t::Low(void) const
{
  return low;
}

Double_t& Range_t::Low(void)
{
  return low;
}

const Double_t& Range_t::High(void) const
{
  return high;
}

Double_t& Range_t::High(void)
{
  return high;
}

} // namespace uasdk
