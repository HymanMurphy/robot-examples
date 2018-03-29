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

#include "opcua_transfer_result_t.h"

#if (UASDK_INCLUDE_SUBSCRIPTIONS > 0 && UASDK_INCLUDE_TRANSFER_SUBSCRIPTIONS_SERVICE > 0)

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(TransferResult_t, Structure_t)

bool TransferResult_t::operator==(TransferResult_t const & obj) const
{
  return (
      (statusCode == obj.statusCode)
      && (availableSequenceNumbers == obj.availableSequenceNumbers));
}

bool TransferResult_t::operator>(TransferResult_t const & obj) const
{
  return (
      (statusCode > obj.statusCode)
      && (availableSequenceNumbers > obj.availableSequenceNumbers));
}

Status_t TransferResult_t::CopyFrom(const BaseDataType_t& source)
{
  const TransferResult_t* ptr = RuntimeCast<const TransferResult_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t TransferResult_t::CopyFrom(const TransferResult_t& source)
{
  Status_t status = statusCode.CopyFrom(source.statusCode);
  if (status.IsBad())
  {
    return status;
  }

  status = availableSequenceNumbers.CopyFrom(source.availableSequenceNumbers);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t TransferResult_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = statusCode.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = availableSequenceNumbers.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t TransferResult_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, TransferResult_t& result)
{
  Status_t status = StatusCode_t::Decode(buffer, decoder, result.StatusCode());
  if (status.IsBad())
  {
    return status;
  }

  status = ArrayUA_t<Counter_t>::Decode(buffer, decoder, result.AvailableSequenceNumbers());
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

TransferResult_t::~TransferResult_t()
{}

bool TransferResult_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool TransferResult_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t TransferResult_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t TransferResult_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t TransferResult_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_TransferResult_Encoding_DefaultBinary;
}

const StatusCode_t& TransferResult_t::StatusCode(void) const
{
  return statusCode;
}

StatusCode_t& TransferResult_t::StatusCode(void)
{
  return statusCode;
}

const ArrayUA_t<Counter_t>& TransferResult_t::AvailableSequenceNumbers(void) const
{
  return availableSequenceNumbers;
}

ArrayUA_t<Counter_t>& TransferResult_t::AvailableSequenceNumbers(void)
{
  return availableSequenceNumbers;
}

} // namespace uasdk

#endif //UASDK_INCLUDE_SUBSCRIPTIONS
