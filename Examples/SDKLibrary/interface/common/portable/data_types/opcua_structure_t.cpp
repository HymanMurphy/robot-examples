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

#include "opcua_structure_t.h"
#include "icodec_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(Structure_t, BaseDataType_t)

Status_t Structure_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, IntrusivePtr_t<Structure_t>& result)
{
  return decoder.Decode(buffer, result);
}

Structure_t::Structure_t()
{}

Structure_t::~Structure_t()
{}

uint32_t Structure_t::BinaryEncodingId(void) const
{
  uint16_t namespaceIndex = 0;
  return BinaryEncodingId(namespaceIndex);
}

Status_t Structure_t::CopyToStructure(IntrusivePtr_t<Structure_t>& destination) const
{
  IntrusivePtr_t<BaseDataType_t> destinationBase;
  Status_t status = CopyTo(destinationBase);
  if (status.IsBad() || !destinationBase.is_set())
  {
    return status;
  }
  destination = RuntimeCast<Structure_t*>(*destinationBase);
  if (destination.is_set())
  {
    return OpcUa_Good;
  }
  return OpcUa_BadTypeMismatch;
}

} // namespace uasdk
