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

#include "opcua_querydata_description_t.h"

#if (UASDK_INCLUDE_QUERY_SERVICE_SET > 0)

namespace uasdk
{

	UA_DEFINE_RUNTIME_TYPE(QueryDataDescription_t, Structure_t)

		bool QueryDataDescription_t::operator==(QueryDataDescription_t const & obj) const
	{
		return (
			(relativePath == obj.relativePath)
			&& (attributeId == obj.attributeId)
			&& (indexRange == obj.indexRange));
	}

	bool QueryDataDescription_t::operator>(QueryDataDescription_t const & obj) const
	{
		return (
			(relativePath > obj.relativePath)
			&& (attributeId > obj.attributeId)
			&& (indexRange > obj.indexRange));
	}

	Status_t QueryDataDescription_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
	{
		return CopyToDestination(*this, destination);
	}

	Status_t QueryDataDescription_t::CopyFrom(const QueryDataDescription_t& source)
	{
		Status_t status = relativePath.CopyFrom(source.relativePath);

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

		return status;
	}

	Status_t QueryDataDescription_t::CopyFrom(const BaseDataType_t& source)
	{
		const QueryDataDescription_t* ptr = RuntimeCast<const QueryDataDescription_t *>(source);
		if (!ptr)
		{
			UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
		}

		return CopyFrom(*ptr);
	}

	Status_t QueryDataDescription_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
	{
		Status_t status = relativePath.Encode(encoder, buffer);
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

		return status;
	}

	Status_t QueryDataDescription_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, QueryDataDescription_t& result)
	{
		Status_t status = ArrayUA_t<RelativePathElement_t>::Decode(buffer, decoder, result.RelativePath());
		if (status.IsBad())
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

		return status;
	}

	QueryDataDescription_t::~QueryDataDescription_t()
	{}

	bool QueryDataDescription_t::operator==(BaseDataType_t const & obj) const
	{
		return OperatorEqualTo(*this, obj);
	}

	bool QueryDataDescription_t::operator>(BaseDataType_t const & obj) const
	{
		return OperatorGreaterThan(*this, obj);
	}

	uint32_t QueryDataDescription_t::TypeId(uint16_t& namespaceIndex) const
	{
		namespaceIndex = 0; return TYPE_ID;
	}

	uint32_t QueryDataDescription_t::BinaryEncodingId(uint16_t& namespaceIndex) const
	{
		namespaceIndex = 0; return OpcUaId_QueryDataDescription_Encoding_DefaultBinary;
	}

	const uasdk::ArrayUA_t<uasdk::RelativePathElement_t>& QueryDataDescription_t::RelativePath() const
	{
		return relativePath;
	}

	uasdk::ArrayUA_t<uasdk::RelativePathElement_t>& QueryDataDescription_t::RelativePath()
	{
		return relativePath;
	}

	const uasdk::IntegerId_t& QueryDataDescription_t::AttributeId(void) const
	{
		return attributeId;
	}

	uasdk::IntegerId_t& QueryDataDescription_t::AttributeId(void)
	{
		return attributeId;
	}

	const uasdk::String_t& QueryDataDescription_t::IndexRange(void) const
	{
		return indexRange;
	}

	uasdk::String_t& QueryDataDescription_t::IndexRange(void)
	{
		return indexRange;
	}


} // namespace uasdk

#endif
