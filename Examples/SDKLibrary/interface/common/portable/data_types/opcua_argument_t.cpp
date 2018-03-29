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

#include "opcua_argument_t.h"
#include "opcua_identifiers.h"
#include "buffer_t.h"

#if (UASDK_INCLUDE_METHOD_SERVICE_SET > 0)

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(Argument_t, Structure_t)

bool Argument_t::operator==(Argument_t const & obj) const
{
  return (
      (name == obj.name)
      && Equal(dataType, obj.dataType)
      && (valueRank == obj.valueRank)
      && (arrayDimensions == obj.arrayDimensions)
      && (description == obj.description));
}

bool Argument_t::operator>(Argument_t const & obj) const
{
  return (
      (name > obj.name)
      && GreaterThan(dataType, obj.dataType)
      && (valueRank > obj.valueRank)
      && (arrayDimensions > obj.arrayDimensions)
      && (description > obj.description));
}

Status_t Argument_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

Status_t Argument_t::CopyFrom(const Argument_t& source)
{
  Status_t status = name.CopyFrom(source.name);
  if (status.IsBad())
  {
    return status;
  }

  if(!source.dataType.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  status = source.dataType->CopyToNodeId(dataType);
  if (status.IsBad())
  {
    return status;
  }

  status = valueRank.CopyFrom(source.valueRank);
  if (status.IsBad())
  {
    return status;
  }

  status = arrayDimensions.CopyFrom(source.arrayDimensions);
  if (status.IsBad())
  {
    return status;
  }

  status = description.CopyFrom(source.description);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t Argument_t::CopyFrom(const BaseDataType_t& source)
{
  const Argument_t* ptr = RuntimeCast<const Argument_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t Argument_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = name.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  if (!dataType.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadEncodingError);
  }
  status = dataType->Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = valueRank.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = arrayDimensions.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = description.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return 0;
}

Status_t Argument_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, Argument_t& result)
{
  Status_t status = String_t::Decode(buffer, decoder, result.Name());
  if (status.IsBad())
  {
    return status;
  }

  status = NodeId_t::Decode(buffer, decoder, result.DataType());
  if (status.IsBad())
  {
    return status;
  }

  status = Int32_t::Decode(buffer, decoder, result.ValueRank());
  if (status.IsBad())
  {
    return status;
  }

  status = ArrayUA_t<UInt32_t>::Decode(buffer, decoder, result.ArrayDimensions());
  if (status.IsBad())
  {
    return status;
  }

  status = LocalizedText_t::Decode(buffer, decoder, result.Description());
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Argument_t::Argument_t() 
{}

Argument_t::~Argument_t() 
{}

bool Argument_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool Argument_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

uint32_t Argument_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t Argument_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_Argument_Encoding_DefaultBinary;
}

const String_t& Argument_t::Name(void) const 
{
  return name; 
}

String_t& Argument_t::Name(void) 
{ 
  return name; 
}

IntrusivePtr_t<const NodeId_t> Argument_t::DataType(void) const 
{ 
  return dataType; 
}

IntrusivePtr_t<NodeId_t>& Argument_t::DataType(void) 
{ 
  return dataType; 
}

const Int32_t& Argument_t::ValueRank(void) const 
{ 
  return valueRank; 
}

Int32_t& Argument_t::ValueRank(void) 
{ 
  return valueRank; 
}

const ArrayUA_t<UInt32_t>& Argument_t::ArrayDimensions(void) const 
{ 
  return arrayDimensions; 
}

ArrayUA_t<UInt32_t>& Argument_t::ArrayDimensions(void) 
{ 
  return arrayDimensions; 
}

const LocalizedText_t& Argument_t::Description(void) const 
{ 
  return description; 
}

LocalizedText_t& Argument_t::Description(void)
{ 
  return description; 
}

} // namespace uasdk

#endif
