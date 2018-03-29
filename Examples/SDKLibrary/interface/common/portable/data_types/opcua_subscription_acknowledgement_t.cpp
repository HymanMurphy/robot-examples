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

#include "opcua_subscription_acknowledgement_t.h"

#if (UASDK_INCLUDE_SUBSCRIPTIONS > 0)

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(SubscriptionAcknowledgment_t, Structure_t)

bool SubscriptionAcknowledgment_t::operator==(SubscriptionAcknowledgment_t const & obj) const
{
  return (
      (subscriptionId == obj.subscriptionId)
      && (sequenceNumber == obj.sequenceNumber));
}

bool SubscriptionAcknowledgment_t::operator>(SubscriptionAcknowledgment_t const & obj) const
{
  return (
      (subscriptionId > obj.subscriptionId)
      && (sequenceNumber > obj.sequenceNumber));
}

Status_t SubscriptionAcknowledgment_t::CopyFrom(const BaseDataType_t& source)
{
  const SubscriptionAcknowledgment_t* ptr = RuntimeCast<const SubscriptionAcknowledgment_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t SubscriptionAcknowledgment_t::CopyFrom(const SubscriptionAcknowledgment_t& source)
{
  Status_t status = subscriptionId.CopyFrom(source.subscriptionId);
  if (status.IsBad())
  {
    return status;
  }

  status = sequenceNumber.CopyFrom(source.sequenceNumber);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t SubscriptionAcknowledgment_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = subscriptionId.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = sequenceNumber.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t SubscriptionAcknowledgment_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, SubscriptionAcknowledgment_t& result)
{
  Status_t status = IntegerId_t::Decode(buffer, decoder, result.SubscriptionId());
  if (status.IsBad())
  {
    return status;
  }

  status = Counter_t::Decode(buffer, decoder, result.SequenceNumber());
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

SubscriptionAcknowledgment_t::~SubscriptionAcknowledgment_t()
{}

bool SubscriptionAcknowledgment_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool SubscriptionAcknowledgment_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t SubscriptionAcknowledgment_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t SubscriptionAcknowledgment_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t SubscriptionAcknowledgment_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_SubscriptionAcknowledgement_Encoding_DefaultBinary;
}

const IntegerId_t& SubscriptionAcknowledgment_t::SubscriptionId(void) const
{
  return subscriptionId;
}

IntegerId_t& SubscriptionAcknowledgment_t::SubscriptionId(void)
{
  return subscriptionId;
}

const Counter_t& SubscriptionAcknowledgment_t::SequenceNumber(void) const
{
  return sequenceNumber;
}

Counter_t& SubscriptionAcknowledgment_t::SequenceNumber(void)
{
  return sequenceNumber;
}

} // namespace uasdk

#endif //UASDK_INCLUDE_SUBSCRIPTIONS