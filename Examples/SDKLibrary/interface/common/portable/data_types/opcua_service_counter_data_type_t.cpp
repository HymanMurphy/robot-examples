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

#include "opcua_service_counter_data_type_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(ServiceCounterDataType_t, Structure_t)

ServiceCounterDataType_t::ServiceCounterDataType_t()
  : totalCount(0), errorCount(0)
{}

ServiceCounterDataType_t::ServiceCounterDataType_t(uint32_t totalCount_, uint32_t errorCount_)
  : totalCount(totalCount_), errorCount(errorCount_)
{}

ServiceCounterDataType_t::~ServiceCounterDataType_t()
{}

bool ServiceCounterDataType_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool ServiceCounterDataType_t::operator==(ServiceCounterDataType_t const & obj) const
{
  return (
      (totalCount == obj.totalCount)
      && (errorCount == obj.errorCount));
}

bool ServiceCounterDataType_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

bool ServiceCounterDataType_t::operator>(ServiceCounterDataType_t const & obj) const
{
  return (
       (totalCount > obj.totalCount)
       && (errorCount > obj.errorCount));
}

Status_t ServiceCounterDataType_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

Status_t ServiceCounterDataType_t::CopyFrom(const BaseDataType_t& source)
{
  const ServiceCounterDataType_t* ptr = RuntimeCast<const ServiceCounterDataType_t* >(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t ServiceCounterDataType_t::CopyFrom(const ServiceCounterDataType_t& source)
{
  Status_t status = totalCount.CopyFrom(source.totalCount);
  if (status.IsBad())
  {
    return status;
  }

  return errorCount.CopyFrom(source.errorCount);
}

uint32_t ServiceCounterDataType_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t ServiceCounterDataType_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0;
  return OpcUaId_ServiceCounterDataType_Encoding_DefaultBinary;
}

const UInt32_t& ServiceCounterDataType_t::TotalCount(void) const
{
  return totalCount;
}

UInt32_t& ServiceCounterDataType_t::TotalCount(void)
{
  return totalCount;
}

const UInt32_t& ServiceCounterDataType_t::ErrorCount(void) const
{
  return errorCount;
}

UInt32_t& ServiceCounterDataType_t::ErrorCount(void)
{
  return errorCount;
}

Status_t ServiceCounterDataType_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = totalCount.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return errorCount.Encode(encoder, buffer);
}

Status_t ServiceCounterDataType_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, ServiceCounterDataType_t& result)
{
  Status_t status = UInt32_t::Decode(buffer, decoder, result.TotalCount());
  if (status.IsBad())
  {
    return status;
  }

  return UInt32_t::Decode(buffer, decoder, result.ErrorCount());
}

} // namespace uasdk
