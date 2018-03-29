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

#include "opcua_enumeration_t.h"
#include "opcua_int32_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(Enumeration_t, BaseDataType_t)

Enumeration_t::Enumeration_t()
{
}

Enumeration_t::~Enumeration_t()
{
}

Status_t Enumeration_t::TryCopyFromInt32(const BaseDataType_t& source)
{
  const Int32_t* ptr = RuntimeCast<const Int32_t *>(source);
  if (!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }
  return WriteIntToValue(ptr->Value());
}

Status_t Enumeration_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, Enumeration_t& result)
{
  Int32_t raw_val(0);
  Status_t status = Int32_t::Decode(buffer, decoder, raw_val);
  if (status.IsBad())
  {
    return status;
  }

  return result.WriteIntToValue(raw_val.Value());
}

} // namespace uasdk
