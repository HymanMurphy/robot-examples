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

#include "opcua_notification_message_t.h"

#if (UASDK_INCLUDE_SUBSCRIPTIONS > 0)
namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(NotificationMessage_t, Structure_t)

bool NotificationMessage_t::operator==(NotificationMessage_t const & obj) const
{
  return (
      (sequenceNumber == obj.sequenceNumber)
      && (publishTime == obj.publishTime)
      && (notificationData == obj.notificationData));
}

bool NotificationMessage_t::operator>(NotificationMessage_t const & obj) const
{
  return (
          (sequenceNumber > obj.sequenceNumber)
          && (publishTime > obj.publishTime)
          && (notificationData > obj.notificationData));
}

Status_t NotificationMessage_t::CopyFrom(const BaseDataType_t& source)
{
  const NotificationMessage_t* ptr = RuntimeCast<const NotificationMessage_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t NotificationMessage_t::CopyFrom(const NotificationMessage_t& source)
{
  Status_t status = sequenceNumber.CopyFrom(source.sequenceNumber);
  if (status.IsBad())
  {
    return status;
  }

  status = publishTime.CopyFrom(source.publishTime);
  if (status.IsBad())
  {
    return status;
  }

  status = notificationData.CopyFrom(source.notificationData);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t NotificationMessage_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = sequenceNumber.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = publishTime.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = notificationData.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t NotificationMessage_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, NotificationMessage_t& result)
{
  Status_t status = Counter_t::Decode(buffer, decoder, result.SequenceNumber());
  if (status.IsBad())
  {
    return status;
  }

  status = result.PublishTime().Decode(buffer, decoder, result.PublishTime());
  if (status.IsBad())
  {
    return status;
  }

  status = ArrayUA_t<ExtensibleParameter_t>::Decode(buffer, decoder, result.NotificationData());
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

NotificationMessage_t::~NotificationMessage_t()
{}

bool NotificationMessage_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool NotificationMessage_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t NotificationMessage_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t NotificationMessage_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t NotificationMessage_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_NotificationMessage_Encoding_DefaultBinary;
}

const Counter_t&  NotificationMessage_t::SequenceNumber(void) const
{
  return sequenceNumber;
}

Counter_t&  NotificationMessage_t::SequenceNumber(void)
{
  return sequenceNumber;
}

const UtcTime_t& NotificationMessage_t::PublishTime(void) const
{
  return publishTime;
}

UtcTime_t& NotificationMessage_t::PublishTime(void)
{
  return publishTime;
}

const ArrayUA_t<ExtensibleParameter_t>& NotificationMessage_t::NotificationData(void) const
{
  return notificationData;
}

ArrayUA_t<ExtensibleParameter_t>& NotificationMessage_t::NotificationData(void)
{
  return notificationData;
}

} // namespace uasdk

#endif //UASDK_INCLUDE_SUBSCRIPTIONS

