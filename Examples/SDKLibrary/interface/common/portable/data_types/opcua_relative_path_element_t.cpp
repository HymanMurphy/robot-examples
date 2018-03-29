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

#include "opcua_relative_path_element_t.h"
#include "ua_binary_codec_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(RelativePathElement_t, Structure_t)

bool RelativePathElement_t::operator==(RelativePathElement_t const & obj) const
{
  return (
      Equal(referenceTypeId, obj.referenceTypeId)
      && (isInverse == obj.isInverse)
      && (includeSubtypes == obj.includeSubtypes)
      && (targetName == obj.targetName));
}

bool RelativePathElement_t::operator>(RelativePathElement_t const & obj) const
{
  return (
      GreaterThan(referenceTypeId, obj.referenceTypeId)
      && (isInverse > obj.isInverse)
      && (includeSubtypes > obj.includeSubtypes)
      && (targetName > obj.targetName));
}

Status_t RelativePathElement_t::CopyFrom(const BaseDataType_t& source)
{
  const RelativePathElement_t* ptr = RuntimeCast<const RelativePathElement_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t RelativePathElement_t::CopyFrom(const RelativePathElement_t& source)
{
  Status_t status;

  if(source.referenceTypeId.is_set())
  {
    status = source.referenceTypeId->CopyToNodeId(referenceTypeId);
    if (status.IsBad())
    {
      return status;
    }
  }
  else {
      referenceTypeId.reset();
  }

  status = isInverse.CopyFrom(source.isInverse);
  if (status.IsBad())
  {
    return status;
  }

  status = includeSubtypes.CopyFrom(source.includeSubtypes);
  if (status.IsBad())
  {
    return status;
  }

  status = targetName.CopyFrom(source.targetName);
  if (status.IsBad())
  {
    return status;
  }
  return OpcUa_Good;
}

Status_t RelativePathElement_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status;

  status = encoder.Encode(referenceTypeId, buffer);
  if (status.IsBad())
  {
      return status;
  }

  status = isInverse.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = includeSubtypes.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = targetName.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t RelativePathElement_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, RelativePathElement_t& result)
{
  Status_t status = NodeId_t::Decode(buffer, decoder, result.ReferenceTypeId());
  if (status.IsBad())
  {
    return status;
  }

  status = Boolean_t::Decode(buffer, decoder, result.IsInverse());
  if (status.IsBad())
  {
    return status;
  }

  status = Boolean_t::Decode(buffer, decoder, result.IncludeSubtypes());
  if (status.IsBad())
  {
    return status;
  }

  status = QualifiedName_t::Decode(buffer, decoder, result.TargetName());
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

RelativePathElement_t::~RelativePathElement_t()
{}

bool RelativePathElement_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool RelativePathElement_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t RelativePathElement_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t RelativePathElement_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t RelativePathElement_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_RelativePathElement_Encoding_DefaultBinary;
}

IntrusivePtr_t<const NodeId_t> RelativePathElement_t::ReferenceTypeId(void) const
{
  return referenceTypeId;
}

IntrusivePtr_t<NodeId_t>& RelativePathElement_t::ReferenceTypeId(void)
{
  return referenceTypeId;
}

const Boolean_t& RelativePathElement_t::IsInverse(void) const
{
  return isInverse;
}
Boolean_t& RelativePathElement_t::IsInverse(void)
{
  return isInverse;
}

const Boolean_t& RelativePathElement_t::IncludeSubtypes(void) const
{
  return includeSubtypes;
}

Boolean_t& RelativePathElement_t::IncludeSubtypes(void)
{
  return includeSubtypes;
}

const QualifiedName_t& RelativePathElement_t::TargetName(void) const
{
  return targetName;
}

QualifiedName_t& RelativePathElement_t::TargetName(void)
{
  return targetName;
}

} // namespace uasdk
