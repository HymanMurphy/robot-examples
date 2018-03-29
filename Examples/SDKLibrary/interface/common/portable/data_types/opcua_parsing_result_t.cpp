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

#include "opcua_parsing_result_t.h"

#if (UASDK_INCLUDE_QUERY_SERVICE_SET > 0)

namespace uasdk
{

	UA_DEFINE_RUNTIME_TYPE(ParsingResult_t, Structure_t)

		bool ParsingResult_t::operator==(ParsingResult_t const & obj) const
	{
		return (
			(statusCode == obj.statusCode)
			&& (dataStatusCodes == obj.dataStatusCodes)
			&& (dataDiagnosticInfos == obj.dataDiagnosticInfos));
	}

	bool ParsingResult_t::operator>(ParsingResult_t const & obj) const
	{
		return (
			(statusCode > obj.statusCode)
			&& (dataStatusCodes > obj.dataStatusCodes)
			&& (dataDiagnosticInfos > obj.dataDiagnosticInfos));
	}

	Status_t ParsingResult_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
	{
		return CopyToDestination(*this, destination);
	}

	Status_t ParsingResult_t::CopyFrom(const ParsingResult_t& source)
	{
		Status_t status = statusCode.CopyFrom(source.statusCode);

		if (status.IsBad())
		{
			return status;
		}

		status = dataStatusCodes.CopyFrom(source.dataStatusCodes);
		if (status.IsBad())
		{
			return status;
		}

		status = dataDiagnosticInfos.CopyFrom(source.dataDiagnosticInfos);
		if (status.IsBad())
		{
			return status;
		}

		return status;
	}

	Status_t ParsingResult_t::CopyFrom(const BaseDataType_t& source)
	{
		const ParsingResult_t* ptr = RuntimeCast<const ParsingResult_t *>(source);
		if (!ptr)
		{
			UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
		}

		return CopyFrom(*ptr);
	}

	Status_t ParsingResult_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
	{
		Status_t status = statusCode.Encode(encoder, buffer);
		if (status.IsBad())
		{
			return status;
		}

		status = dataStatusCodes.Encode(encoder, buffer);
		if (status.IsBad())
		{
			return status;
		}

		status = dataDiagnosticInfos.Encode(encoder, buffer);
		if (status.IsBad())
		{
			return status;
		}

		return status;
	}

	Status_t ParsingResult_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, ParsingResult_t& result)
	{
		Status_t status = StatusCode_t::Decode(buffer, decoder, result.StatusCode());
		if (status.IsBad())
		{
			return status;
		}

		status = ArrayUA_t<StatusCode_t>::Decode(buffer, decoder, result.DataStatusCodes());
		if (status.IsBad())
		{
			return status;
		}

		status = ArrayUA_t<DiagnosticInfo_t>::Decode(buffer, decoder, result.DataDiagnosticInfos());
		if (status.IsBad())
		{
			return status;
		}

		return status;
	}

	ParsingResult_t::~ParsingResult_t()
	{}

	bool ParsingResult_t::operator==(BaseDataType_t const & obj) const
	{
		return OperatorEqualTo(*this, obj);
	}

	bool ParsingResult_t::operator>(BaseDataType_t const & obj) const
	{
		return OperatorGreaterThan(*this, obj);
	}

	uint32_t ParsingResult_t::TypeId(uint16_t& namespaceIndex) const
	{
		namespaceIndex = 0; return TYPE_ID;
	}

	uint32_t ParsingResult_t::BinaryEncodingId(uint16_t& namespaceIndex) const
	{
		namespaceIndex = 0; return OpcUaId_ParsingResult_Encoding_DefaultBinary;
	}

	const StatusCode_t & ParsingResult_t::StatusCode() const
	{
		return statusCode;
	}

	StatusCode_t & ParsingResult_t::StatusCode()
	{
		return statusCode;
	}

	const ArrayUA_t<StatusCode_t>& ParsingResult_t::DataStatusCodes() const
	{
		return dataStatusCodes;
	}

	ArrayUA_t<StatusCode_t>& ParsingResult_t::DataStatusCodes()
	{
		return dataStatusCodes;
	}

	const ArrayUA_t<DiagnosticInfo_t>& ParsingResult_t::DataDiagnosticInfos() const
	{
		return dataDiagnosticInfos;
	}

	ArrayUA_t<DiagnosticInfo_t>& ParsingResult_t::DataDiagnosticInfos()
	{
		return dataDiagnosticInfos;
	}

} // namespace uasdk

#endif

