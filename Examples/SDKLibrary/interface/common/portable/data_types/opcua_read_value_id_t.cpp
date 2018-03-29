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

#include "opcua_read_value_id_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(ReadValueId_t, Structure_t)

bool  ReadValueId_t::operator==(ReadValueId_t const & obj) const
{
  return (
      Equal(nodeId, obj.nodeId)
      && (attributeId == obj.attributeId)
      && (indexRange == obj.indexRange)
      && (dataEncoding == obj.dataEncoding));
}

bool  ReadValueId_t::operator>(ReadValueId_t const & obj) const
{
  return (
      GreaterThan(nodeId, obj.nodeId)
      && (attributeId > obj.attributeId)
      && (indexRange > obj.indexRange)
      && (dataEncoding > obj.dataEncoding));
}

Status_t ReadValueId_t::CopyFrom(const BaseDataType_t& source)
{
  const ReadValueId_t* ptr = RuntimeCast<const ReadValueId_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t ReadValueId_t::CopyFrom(const ReadValueId_t& source)
{
  if(!source.nodeId.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  Status_t status = source.nodeId->CopyToNodeId(nodeId);
  if(status.IsBad())
  {
    return status;
  }

  status = attributeId.CopyFrom(source.attributeId);
  if(status.IsBad())
  {
    return status;
  }

  status = indexRange.CopyFrom(source.indexRange);
  if(status.IsBad())
  {
    return status;
  }

  status = dataEncoding.CopyFrom(source.dataEncoding);
  if(status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t ReadValueId_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status;

  if (!nodeId.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadEncodingError);
  }

  status = nodeId->Encode(encoder, buffer);
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

  status = dataEncoding.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t ReadValueId_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, ReadValueId_t& result)
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

  status = QualifiedName_t::Decode(buffer, decoder, result.DataEncoding());
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

ReadValueId_t::ReadValueId_t()
{}

ReadValueId_t::~ReadValueId_t()
{}

bool ReadValueId_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool ReadValueId_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t ReadValueId_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}


uint32_t ReadValueId_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t ReadValueId_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_ReadValueId_Encoding_DefaultBinary;
}

IntrusivePtr_t<const NodeId_t> ReadValueId_t::NodeId(void) const
{
  return nodeId;
}

IntrusivePtr_t<NodeId_t>& ReadValueId_t::NodeId(void)
{
  return nodeId;
}

const IntegerId_t& ReadValueId_t::AttributeId(void) const
{
  return attributeId;
}

IntegerId_t& ReadValueId_t::AttributeId(void)
{
  return attributeId;
}

const String_t& ReadValueId_t::IndexRange(void) const
{
  return indexRange;
}

String_t& ReadValueId_t::IndexRange(void)
{
  return indexRange;
}

const QualifiedName_t& ReadValueId_t::DataEncoding(void) const
{
  return dataEncoding;
}

QualifiedName_t& ReadValueId_t::DataEncoding(void)
{
  return dataEncoding;
}

} // namespace uasdk
