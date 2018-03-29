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

#include "opcua_time_zone_data_type_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(TimeZoneDataType_t, Structure_t)

bool TimeZoneDataType_t::operator==(TimeZoneDataType_t const & obj) const
{
	return (
		(offset == obj.offset)
		&& (daylightSavingInOffset == obj.daylightSavingInOffset));
}

bool TimeZoneDataType_t::operator>(TimeZoneDataType_t const & obj) const
{
	return (
		(offset > obj.offset)
		&& (daylightSavingInOffset > obj.daylightSavingInOffset));
}

Status_t TimeZoneDataType_t::CopyFrom(const TimeZoneDataType_t& source)
{
  Status_t status = offset.CopyFrom(source.offset);

  if(status.IsBad())
  {
    return status;
  }

	status = daylightSavingInOffset.CopyFrom(source.daylightSavingInOffset);

	if (status.IsBad())
	{
		return status;
	}

  return status;
}

TimeZoneDataType_t& TimeZoneDataType_t::operator=(TimeZoneDataType_t const & obj)
{
  offset = obj.offset;
  daylightSavingInOffset = obj.daylightSavingInOffset;
  return *this;
}

Status_t TimeZoneDataType_t::CopyFrom(const BaseDataType_t& source)
{
  const TimeZoneDataType_t* ptr = RuntimeCast<const TimeZoneDataType_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t TimeZoneDataType_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
	return CopyToDestination(*this, destination);
}

Status_t TimeZoneDataType_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = offset.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

	status = daylightSavingInOffset.Encode(encoder, buffer);
	if (status.IsBad())
	{
		return status;
	}

  return status;
}

Status_t TimeZoneDataType_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, TimeZoneDataType_t& result)
{
  Int16_t offset;
	Boolean_t daylightSavingInOffset;

  Status_t status = Int16_t::Decode(buffer, decoder, result.Offset());
  if (status.IsBad())
  {
    return status;
  }

	status = Boolean_t::Decode(buffer, decoder, result.DaylightSavingInOffset());
	if (status.IsBad())
	{
		return status;
	}

  return status;
}

TimeZoneDataType_t::TimeZoneDataType_t()
  : offset(0) , daylightSavingInOffset(false)
{}

TimeZoneDataType_t::TimeZoneDataType_t(int16_t offset_, bool daylightSavingInOffset_)
  : offset(offset_), daylightSavingInOffset(daylightSavingInOffset_)
{}

TimeZoneDataType_t::~TimeZoneDataType_t(void)
{}


bool TimeZoneDataType_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool TimeZoneDataType_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

uint32_t TimeZoneDataType_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
	namespaceIndex = 0; return OpcUaId_TimeZoneDataType_Encoding_DefaultBinary;
}

uint32_t TimeZoneDataType_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

const Int16_t& TimeZoneDataType_t::Offset(void) const
{
	return offset;
}

Int16_t& TimeZoneDataType_t::Offset(void)
{
	return offset;
}

const Boolean_t& TimeZoneDataType_t::DaylightSavingInOffset(void) const
{
	return daylightSavingInOffset;
}

Boolean_t& TimeZoneDataType_t::DaylightSavingInOffset(void)
{
	return daylightSavingInOffset;
}

} // namespace uasdk

