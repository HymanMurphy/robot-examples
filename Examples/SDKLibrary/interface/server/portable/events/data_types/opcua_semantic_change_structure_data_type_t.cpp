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

#include "opcua_semantic_change_structure_data_type_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

namespace uasdk
{
  
UA_DEFINE_RUNTIME_TYPE(SemanticChangeStructureDataType_t, Structure_t)

SemanticChangeStructureDataType_t::SemanticChangeStructureDataType_t()
{
}

SemanticChangeStructureDataType_t::~SemanticChangeStructureDataType_t()
{
}

bool SemanticChangeStructureDataType_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool SemanticChangeStructureDataType_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t SemanticChangeStructureDataType_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t SemanticChangeStructureDataType_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t SemanticChangeStructureDataType_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_SemanticChangeStructureDataType_Encoding_DefaultBinary;
}

IntrusivePtr_t<const NodeId_t> SemanticChangeStructureDataType_t::Affected(void) const
{
	return affected;
}

IntrusivePtr_t<NodeId_t>& SemanticChangeStructureDataType_t::Affected(void)
{
	return affected;
}

IntrusivePtr_t<const NodeId_t> SemanticChangeStructureDataType_t::AffectedType(void) const
{
  return affectedType;
}

IntrusivePtr_t<NodeId_t>& SemanticChangeStructureDataType_t::AffectedType(void)
{
  return affectedType;
}

bool SemanticChangeStructureDataType_t::operator==(SemanticChangeStructureDataType_t const & obj) const
{
  return (
		Equal(affected, obj.affected)
      && Equal(affectedType, obj.affectedType));
}

bool SemanticChangeStructureDataType_t::operator>(SemanticChangeStructureDataType_t const & obj) const
{
	return (
		GreaterThan(affected, obj.affected)
		&& GreaterThan(affectedType, obj.affectedType));
}

Status_t SemanticChangeStructureDataType_t::CopyFrom(const SemanticChangeStructureDataType_t& source)
{
	if ((!source.affected.is_set()) || (!source.affectedType.is_set()))
	{
		UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
	}

  Status_t status = source.affected->CopyToNodeId(affected);
	if (status.IsBad())
	{
		return status;
	}

	status = source.affectedType->CopyToNodeId(affectedType);
	if (status.IsBad())
	{
		return status;
	}
 
  return status;
}

Status_t SemanticChangeStructureDataType_t::CopyFrom(const BaseDataType_t& source)
{
  const SemanticChangeStructureDataType_t* ptr = RuntimeCast<const SemanticChangeStructureDataType_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t SemanticChangeStructureDataType_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
	if ((!affected.is_set()) || (!affectedType.is_set()))
	{
		UASDK_RETURN_BAD_STATUS(OpcUa_BadEncodingError);
	}

  Status_t status = affected->Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = affectedType->Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t SemanticChangeStructureDataType_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, SemanticChangeStructureDataType_t& result)
{
	Status_t status = NodeId_t::Decode(buffer, decoder, result.Affected());
	if (!result.Affected().is_set() || (status.IsBad()))
	{
		return status;
	}

	status = NodeId_t::Decode(buffer, decoder, result.AffectedType());
	if (!result.AffectedType().is_set() || (status.IsBad()))
	{
		return status;
	}

  return OpcUa_Good;
}
	
} // namespace uasdk

#endif // UASDK_INCLUDE_EVENTS


