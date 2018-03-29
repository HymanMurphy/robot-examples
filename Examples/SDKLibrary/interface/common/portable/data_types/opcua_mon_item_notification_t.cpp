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

#include "opcua_mon_item_notification_t.h"
#include "opcua_datatype_utilities_t.h"

#if (UASDK_INCLUDE_SUBSCRIPTIONS > 0)

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(MonItemNotification_t, Structure_t)

bool MonItemNotification_t::operator==(MonItemNotification_t const & obj) const
{
  return (
      (clientHandle == obj.clientHandle)
      && (value == obj.value));
}

bool MonItemNotification_t::operator>(MonItemNotification_t const & obj) const
{
  return (
      (clientHandle > obj.clientHandle)
      && (value > obj.value));
}

Status_t MonItemNotification_t::CopyFrom(const BaseDataType_t& source)
{
  const MonItemNotification_t* ptr = RuntimeCast<const MonItemNotification_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t MonItemNotification_t::CopyFrom(const MonItemNotification_t& source)
{
  Status_t status = clientHandle.CopyFrom(source.clientHandle);
  if (status.IsBad())
  {
    return status;
  }

  if (source.value.is_set())
  {
    if (!value.is_set())
    {
      value = new SafeRefCount_t<DataValue_t>();
      if (!value.is_set())
      {
        UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
      }
    }

    status = value->CopyFrom(*source.value);
    if (status.IsBad())
    {
      return status;
    }
  }
  else
  {
    value.reset();
  }

  return OpcUa_Good;
}

Status_t MonItemNotification_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = clientHandle.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  if (!value.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadEncodingError);
  }

  status = value->Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t MonItemNotification_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, MonItemNotification_t& result)
{
  Status_t status = IntegerId_t::Decode(buffer, decoder, result.ClientHandle());
  if (status.IsBad())
  {
    return status;
  }

  result.Value() = new SafeRefCount_t<DataValue_t>();
  if (!result.Value() .is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadDecodingError);
  }

  status = DataValue_t::Decode(buffer, decoder, *result.Value());
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

MonItemNotification_t::MonItemNotification_t()
{}

MonItemNotification_t::~MonItemNotification_t()
{}

bool MonItemNotification_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool MonItemNotification_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t MonItemNotification_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t MonItemNotification_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t MonItemNotification_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_MonitoredItemNotification_Encoding_DefaultBinary;
}

const IntegerId_t& MonItemNotification_t::ClientHandle(void) const
{
  return clientHandle;
}

IntegerId_t& MonItemNotification_t::ClientHandle(void)
{
  return clientHandle;
}

IntrusivePtr_t<const DataValue_t> MonItemNotification_t::Value(void) const
{
  return value;
}

IntrusivePtr_t<DataValue_t>& MonItemNotification_t::Value(void)
{
  return value;
}


} // namespace uasdk

#endif //UASDK_INCLUDE_SUBSCRIPTIONS