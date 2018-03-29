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

#include "opcua_write_value_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(WriteValue_t, Structure_t);

WriteValue_t::WriteValue_t()
{
}

bool WriteValue_t::operator==(WriteValue_t const & obj) const
{
  return (
      Equal(nodeId, obj.nodeId)
      && (attributeId == obj.attributeId)
      && (indexRange == obj.indexRange)
      && Equal(dataValue, obj.dataValue));
}

bool WriteValue_t::operator>(WriteValue_t const & obj) const
{
  return (
      GreaterThan(nodeId, obj.nodeId)
      && (attributeId > obj.attributeId)
      && (indexRange > obj.indexRange)
      && GreaterThan(dataValue, obj.dataValue));
}

Status_t WriteValue_t::CopyFrom(const BaseDataType_t& source)
{
  const WriteValue_t* ptr = RuntimeCast<const WriteValue_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t WriteValue_t::CopyFrom(const WriteValue_t& source)
{
  if(!source.nodeId.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  Status_t status = source.nodeId->CopyToNodeId(nodeId);
  if (status.IsBad())
  {
    return status;
  }

  status = attributeId.CopyFrom(source.attributeId);
  if (status.IsBad())
  {
    return status;
  }

  status = indexRange.CopyFrom(source.indexRange);
  if (status.IsBad())
  {
    return status;
  }

  if (!source.dataValue.is_set())
  {
    dataValue.reset();
  }
  else
  {
    if (!dataValue.is_set())
    {
      dataValue = new SafeRefCount_t<DataValue_t>();
      if (!dataValue.is_set())
      {
        UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
      }
    }
    status = dataValue->CopyFrom(*source.dataValue);
    if (status.IsBad())
    {
      return status;
    }
  }

  return OpcUa_Good;
}

Status_t WriteValue_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  if (!nodeId.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadEncodingError);
  }

  Status_t status = nodeId->Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = attributeId.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = indexRange.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  if (!dataValue.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadEncodingError);
  }
  status = dataValue->Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t WriteValue_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, WriteValue_t& result)
{
  Status_t status = NodeId_t::Decode(buffer, decoder, result.NodeId());
  if (!result.NodeId().is_set() || (status.IsBad()))
  {
    return status;
  }

  status = IntegerId_t::Decode(buffer, decoder, result.AttributeId());
  if (status.IsBad())
  {
    return status;
  }

  status = String_t::Decode(buffer, decoder, result.IndexRange());
  if (status.IsBad())
  {
    return status;
  }

  result.DataValue() = new SafeRefCount_t<DataValue_t>();
  if (!result.DataValue().is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  status = DataValue_t::Decode(buffer, decoder, *result.DataValue());
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

WriteValue_t::~WriteValue_t() {}

bool WriteValue_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool WriteValue_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t WriteValue_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t WriteValue_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t WriteValue_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_WriteValue_Encoding_DefaultBinary;
}

IntrusivePtr_t<const NodeId_t> WriteValue_t::NodeId(void) const
{
  return nodeId;
}

IntrusivePtr_t<NodeId_t>& WriteValue_t::NodeId(void)
{
  return nodeId;
}

const IntegerId_t& WriteValue_t::AttributeId(void) const
{
  return attributeId;
}

IntegerId_t& WriteValue_t::AttributeId(void)
{
  return attributeId;
}

const String_t& WriteValue_t::IndexRange(void) const
{
  return indexRange;
}

String_t& WriteValue_t::IndexRange(void)
{
  return indexRange;
}

IntrusivePtr_t<const DataValue_t> WriteValue_t::DataValue(void) const
{
  return dataValue;
}

IntrusivePtr_t<DataValue_t>& WriteValue_t::DataValue(void)
{
  return dataValue;
}

} // namespace uasdk
