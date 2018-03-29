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

#include "opcua_extensible_parameter_t.h"
#include "opcua_int32_t.h"
#include "opcua_datatype_utilities_t.h"
#include "icodec_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(ExtensibleParameter_t, Structure_t)

bool ExtensibleParameter_t::operator==(ExtensibleParameter_t const & obj) const
{
  return Equal(payload, obj.payload);
}

bool ExtensibleParameter_t::operator>(ExtensibleParameter_t const & obj) const
{
  return GreaterThan(payload, obj.payload);
}

Status_t ExtensibleParameter_t::CopyFrom(const ExtensibleParameter_t& source)
{
  if(!source.Payload().is_set())
  {
    payload.reset();
    return OpcUa_Good;
  }

  return source.Payload()->CopyToStructure(payload);
}

Status_t ExtensibleParameter_t::CopyFrom(const BaseDataType_t& source)
{
  const ExtensibleParameter_t* ptr = RuntimeCast<const ExtensibleParameter_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t ExtensibleParameter_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  return encoder.EncodeExtensionObject(payload, buffer);
}

Status_t ExtensibleParameter_t::Decode(const IBuffer_t& buffer,
                                       ICodec_t& decoder,
                                       ExtensibleParameter_t& result)
{
  Status_t status = Structure_t::Decode(buffer, decoder, result.Payload());
  if (status.IsBad())
  {
    return status;
  }
  return 0;
}

ExtensibleParameter_t::ExtensibleParameter_t()
{}

ExtensibleParameter_t::~ExtensibleParameter_t()
{}

bool ExtensibleParameter_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool ExtensibleParameter_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t ExtensibleParameter_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t ExtensibleParameter_t::TypeId(uint16_t& namespaceIndex) const
{
  if (payload.is_set())
  {
    return payload->TypeId(namespaceIndex);
  }
  namespaceIndex = 0;
  return 0;
}

uint32_t ExtensibleParameter_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  if (payload.is_set())
  {
    return payload->BinaryEncodingId(namespaceIndex);
  }
  namespaceIndex = 0;
  return 0;
}

uint32_t ExtensibleParameter_t::BinaryEncodingId(void) const
{
  uint16_t namespaceIndex = 0;
  return BinaryEncodingId(namespaceIndex);
}

IntrusivePtr_t<const Structure_t> ExtensibleParameter_t::Payload(void) const
{
  return payload;
}

IntrusivePtr_t<Structure_t>& ExtensibleParameter_t::Payload(void)
{
  return payload;
}

} // namespace uasdk
