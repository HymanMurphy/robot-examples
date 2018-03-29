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

#include "opcua_querydata_set_t.h"

#if (UASDK_INCLUDE_QUERY_SERVICE_SET > 0)

namespace uasdk
{

	UA_DEFINE_RUNTIME_TYPE(QueryDataSet_t, Structure_t)

		bool QueryDataSet_t::operator==(QueryDataSet_t const & obj) const
	{
		return (
			(nodeId == obj.nodeId)
			&& (typeDefinitionNode == obj.typeDefinitionNode)
			&& (values == obj.values));
	}

	bool QueryDataSet_t::operator>(QueryDataSet_t const & obj) const
	{
		return (
			(nodeId > obj.nodeId)
			&& (typeDefinitionNode > obj.typeDefinitionNode)
			&& (values > obj.values));
	}

	Status_t QueryDataSet_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
	{
		return CopyToDestination(*this, destination);
	}

	Status_t QueryDataSet_t::CopyFrom(const QueryDataSet_t& source)
	{
		Status_t status = nodeId.CopyFrom(source.nodeId);

		if (status.IsBad())
		{
			return status;
		}

		status = typeDefinitionNode.CopyFrom(source.typeDefinitionNode);
		if (status.IsBad())
		{
			return status;
		}

		status = values.CopyFrom(source.values);
		if (status.IsBad())
		{
			return status;
		}

		return status;
	}

	Status_t QueryDataSet_t::CopyFrom(const BaseDataType_t& source)
	{
		const QueryDataSet_t* ptr = RuntimeCast<const QueryDataSet_t *>(source);
		if (!ptr)
		{
			UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
		}

		return CopyFrom(*ptr);
	}
	
	Status_t QueryDataSet_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
	{
		Status_t status = nodeId.Encode(encoder, buffer);
		if (status.IsBad())
		{
			return status;
		}

		status = typeDefinitionNode.Encode(encoder, buffer);
		if (status.IsBad())
		{
			return status;
		}

		status = values.Encode(encoder, buffer);
		if (status.IsBad())
		{
			return status;
		}

		return status;
	}

	Status_t QueryDataSet_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, QueryDataSet_t& result)
	{
        	Status_t status = ExpandedNodeId_t::Decode(buffer, decoder, result.NodeId());
		if (status.IsBad())
		{
			return status;
		}

        	status = ExpandedNodeId_t::Decode(buffer, decoder, result.TypeDefinitionNode());
		if (status.IsBad())
		{
			return status;
		}

		status = ArrayUA_t<BaseDataType_t>::Decode(buffer, decoder, result.Values());
		if (status.IsBad())
		{
			return status;
		}

		return status;
	}

	QueryDataSet_t::~QueryDataSet_t()
	{}

	bool QueryDataSet_t::operator==(BaseDataType_t const & obj) const
	{
		return OperatorEqualTo(*this, obj);
	}

	bool QueryDataSet_t::operator>(BaseDataType_t const & obj) const
	{
		return OperatorGreaterThan(*this, obj);
	}

	uint32_t QueryDataSet_t::TypeId(uint16_t& namespaceIndex) const
	{
		namespaceIndex = 0; return TYPE_ID;
	}

	uint32_t QueryDataSet_t::BinaryEncodingId(uint16_t& namespaceIndex) const
	{
		namespaceIndex = 0; return OpcUaId_QueryDataSet_Encoding_DefaultBinary;
	}

    	const uasdk::ExpandedNodeId_t& QueryDataSet_t::NodeId() const
	{
		return nodeId;
	}

    	uasdk::ExpandedNodeId_t& QueryDataSet_t::NodeId()
	{
		return nodeId;
	}

    	const uasdk::ExpandedNodeId_t& QueryDataSet_t::TypeDefinitionNode() const
	{
		return typeDefinitionNode;
	}

    	uasdk::ExpandedNodeId_t& QueryDataSet_t::TypeDefinitionNode()
	{
		return typeDefinitionNode;
	}

	const uasdk::ArrayUA_t<uasdk::BaseDataType_t>& QueryDataSet_t::Values() const
	{
		return values;
	}

	uasdk::ArrayUA_t<uasdk::BaseDataType_t>& QueryDataSet_t::Values()
	{
		return values;
	}
} // namespace uasdk

#endif

