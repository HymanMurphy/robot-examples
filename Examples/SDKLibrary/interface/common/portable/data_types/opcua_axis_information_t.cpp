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

#include "opcua_axis_information_t.h"

#if (UASDK_INCLUDE_ADDITIONAL_DA_TYPES > 0)

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(AxisInformation_t, Structure_t)

bool AxisInformation_t::operator==(AxisInformation_t const & obj) const
{
  return (
      (engineeringUnits == obj.engineeringUnits)
      && (eURange == obj.eURange)
      && (title == obj.title)
      && (axisScaleType == obj.axisScaleType)
      && (Equal(axisSteps, obj.axisSteps))  );
}

bool AxisInformation_t::operator>(AxisInformation_t const & obj) const
{
  return (
      (engineeringUnits > obj.engineeringUnits)
      && (eURange > obj.eURange)
      && (title > obj.title)
      && (axisScaleType > obj.axisScaleType)
      && (GreaterThan(axisSteps, obj.axisSteps))  );
}

Status_t AxisInformation_t::CopyFrom(const BaseDataType_t& source)
{
  const AxisInformation_t* ptr = RuntimeCast<const AxisInformation_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t AxisInformation_t::CopyFrom(const AxisInformation_t& source)
{
  Status_t status = engineeringUnits.CopyFrom(source.engineeringUnits);
  if (status.IsBad())
  {
    return status;
  }

  status = eURange.CopyFrom(source.eURange);
  if (status.IsBad())
  {
    return status;
  }

  status = title.CopyFrom(source.title);
  if (status.IsBad())
  {
    return status;
  }

  status = axisScaleType.CopyFrom(source.axisScaleType);
  if (status.IsBad())
  {
    return status;
  }

  if(source.axisSteps.is_set())
  {
    axisSteps.reset(new SafeRefCount_t<ArrayUA_t<Double_t> >());
    if(!axisSteps.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }

    status = axisSteps->CopyFrom(*source.axisSteps);
    if(status.IsBad())
    {
      return status;
    }
  }

  return OpcUa_Good;
}

Status_t AxisInformation_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = engineeringUnits.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = eURange.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = title.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = axisScaleType.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  if(axisSteps.is_set())
  {
    status = axisSteps->Encode(encoder, buffer);
    if (status.IsBad())
    {
      return status;
    }
  }

  return OpcUa_Good;
}

Status_t AxisInformation_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, AxisInformation_t& result)
{
  Status_t status = EUInformation_t::Decode(buffer, decoder, result.EngineeringUnits());
  if (status.IsBad())
  {
    return status;
  }

  status = Range_t::Decode(buffer, decoder, result.EURange());
  if (status.IsBad())
  {
    return status;
  }

  status = LocalizedText_t::Decode(buffer, decoder, result.Title());
  if (status.IsBad())
  {
    return status;
  }

  status = AxisScaleEnumeration_t::Decode(buffer, decoder, result.AxisScaleType());
  if (status.IsBad())
  {
    return status;
  }

  if(result.AxisSteps().is_set())
  {
    status = ArrayUA_t<Double_t>::Decode(buffer, decoder, *(result.AxisSteps()) );
    if(status.IsBad())
    {
      return status;
    }
  }

  return OpcUa_Good;
}

AxisInformation_t::~AxisInformation_t()
{}

bool AxisInformation_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool AxisInformation_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t AxisInformation_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t AxisInformation_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t AxisInformation_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_AxisInformation_Encoding_DefaultBinary;
}

const EUInformation_t& AxisInformation_t::EngineeringUnits(void) const
{
  return engineeringUnits;
}

EUInformation_t& AxisInformation_t::EngineeringUnits(void)
{
  return engineeringUnits;
}

const Range_t& AxisInformation_t::EURange(void) const
{
  return eURange;
}

Range_t& AxisInformation_t::EURange(void)
{
  return eURange;
}

const LocalizedText_t& AxisInformation_t::Title(void) const
{
  return title;
}

LocalizedText_t& AxisInformation_t::Title(void)
{
  return title;
}

const AxisScaleEnumeration_t& AxisInformation_t::AxisScaleType(void) const
{
  return axisScaleType;
}

AxisScaleEnumeration_t& AxisInformation_t::AxisScaleType(void)
{
  return axisScaleType;
}

const IntrusivePtr_t<ArrayUA_t<Double_t> >& AxisInformation_t::AxisSteps(void) const
{
  return axisSteps;
}

IntrusivePtr_t<ArrayUA_t<Double_t> >& AxisInformation_t::AxisSteps(void)
{
  return axisSteps;
}

} //namespace uasdk

#endif
