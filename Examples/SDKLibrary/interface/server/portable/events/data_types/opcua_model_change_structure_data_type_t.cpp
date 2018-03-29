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

#include "opcua_model_change_structure_data_type_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

namespace uasdk
{
  
UA_DEFINE_RUNTIME_TYPE(ModelChangeStructureDataType_t, Structure_t)

ModelChangeStructureDataType_t::ModelChangeStructureDataType_t()
{
}

ModelChangeStructureDataType_t::~ModelChangeStructureDataType_t()
{
}

bool ModelChangeStructureDataType_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool ModelChangeStructureDataType_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t ModelChangeStructureDataType_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t ModelChangeStructureDataType_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t ModelChangeStructureDataType_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_SemanticChangeStructureDataType_Encoding_DefaultBinary;
}

IntrusivePtr_t<const NodeId_t> ModelChangeStructureDataType_t::Affected(void) const
{
	return affected;
}

IntrusivePtr_t<NodeId_t>& ModelChangeStructureDataType_t::Affected(void)
{
	return affected;
}

IntrusivePtr_t<const NodeId_t> ModelChangeStructureDataType_t::AffectedType(void) const
{
  return affectedType;
}

IntrusivePtr_t<NodeId_t>& ModelChangeStructureDataType_t::AffectedType(void)
{
  return affectedType;
}

const Byte_t& ModelChangeStructureDataType_t::Verb(void) const
{
	return verb;
}

Byte_t& ModelChangeStructureDataType_t::Verb(void)
{
	return verb;
}

bool ModelChangeStructureDataType_t::operator==(ModelChangeStructureDataType_t const & obj) const
{
  return (
		Equal(affected, obj.affected)
      && Equal(affectedType, obj.affectedType)
			&& verb == obj.verb);
}

bool ModelChangeStructureDataType_t::operator>(ModelChangeStructureDataType_t const & obj) const
{
	return (
		GreaterThan(affected, obj.affected)
		&& GreaterThan(affectedType, obj.affectedType)
		&& verb > obj.verb);
}

Status_t ModelChangeStructureDataType_t::CopyFrom(const ModelChangeStructureDataType_t& source)
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

	status = verb.CopyFrom(source.verb);
	if (status.IsBad())
	{
		return status;
	}
 
  return status;
}

Status_t ModelChangeStructureDataType_t::CopyFrom(const BaseDataType_t& source)
{
  const ModelChangeStructureDataType_t* ptr = RuntimeCast<const ModelChangeStructureDataType_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t ModelChangeStructureDataType_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
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

	status = verb.Encode(encoder, buffer);
	if (status.IsBad())
	{
		return status;
	}

  return status;
}

Status_t ModelChangeStructureDataType_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, ModelChangeStructureDataType_t& result)
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

	status = Byte_t::Decode(buffer, decoder, result.Verb());
	if (status.IsBad())
	{
		return status;
	}

  return OpcUa_Good;
}
	
} // namespace uasdk

#endif // UASDK_INCLUDE_EVENTS


