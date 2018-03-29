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

#include "opcua_data_change_notification_t.h"

#if (UASDK_INCLUDE_SUBSCRIPTIONS > 0)

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(DataChangeNotification_t, Structure_t)

bool DataChangeNotification_t::operator==(DataChangeNotification_t const & obj) const
{
  return (
      (monitoredItems == obj.monitoredItems)
      && (diagnosticInfos == obj.diagnosticInfos));
}

bool DataChangeNotification_t::operator>(DataChangeNotification_t const & obj) const
{
  return (
      (monitoredItems > obj.monitoredItems)
      && (diagnosticInfos > obj.diagnosticInfos));
}

Status_t DataChangeNotification_t::CopyFrom(const DataChangeNotification_t& source)
{
  Status_t status = monitoredItems.CopyFrom(source.monitoredItems);

  if (status.IsBad())
  {
    return status;
  }

  status = diagnosticInfos.CopyFrom(source.diagnosticInfos);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t DataChangeNotification_t::CopyFrom(const BaseDataType_t& source)
{
  const DataChangeNotification_t* ptr = RuntimeCast<const DataChangeNotification_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t DataChangeNotification_t ::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = monitoredItems.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = diagnosticInfos.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t DataChangeNotification_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, DataChangeNotification_t& result)
{
  Status_t status = ArrayUA_t<MonItemNotification_t>::Decode(buffer, decoder, result.MonitoredItems());
  if (status.IsBad())
  {
    return status;
  }

  status = ArrayUA_t<DiagnosticInfo_t>::Decode(buffer, decoder, result.DiagnosticInfos());
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

DataChangeNotification_t::~DataChangeNotification_t() 
{}

bool DataChangeNotification_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool DataChangeNotification_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t DataChangeNotification_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t DataChangeNotification_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t DataChangeNotification_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_DataChangeNotification_Encoding_DefaultBinary;
}

const ArrayUA_t<MonItemNotification_t>& DataChangeNotification_t::MonitoredItems(void) const
{
  return monitoredItems; 
}

ArrayUA_t<MonItemNotification_t>& DataChangeNotification_t::MonitoredItems(void)
{
  return monitoredItems; 
}

const ArrayUA_t<DiagnosticInfo_t>& DataChangeNotification_t::DiagnosticInfos(void) const 
{ 
  return diagnosticInfos; 
}

ArrayUA_t<DiagnosticInfo_t>& DataChangeNotification_t::DiagnosticInfos(void)
{ 
  return diagnosticInfos; 
}

} // namespace uasdk

#endif //UASDK_INCLUDE_SUBSCRIPTIONS
