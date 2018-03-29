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

#include "opcua_event_filter_result_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "opcua_datatype_utilities_t.h"

namespace uasdk
{
  
UA_DEFINE_RUNTIME_TYPE(EventFilterResult_t, Structure_t);

EventFilterResult_t::EventFilterResult_t()
{
}

EventFilterResult_t::~EventFilterResult_t()
{
}

bool EventFilterResult_t::operator==(BaseDataType_t const & obj) const
{
	return OperatorEqualTo(*this, obj);
}

bool EventFilterResult_t::operator==(EventFilterResult_t const & obj) const
{
	return (
		   (selectClauseResults == obj.selectClauseResults)
		&& (selectClauseDiagnosticInfos == obj.selectClauseDiagnosticInfos)
		&& (whereClauseResult == obj.whereClauseResult));
}

bool EventFilterResult_t::operator>(BaseDataType_t const & obj) const
{
	return OperatorGreaterThan(*this, obj);
}

bool EventFilterResult_t::operator>(EventFilterResult_t const & obj) const
{
	return (
		   (selectClauseResults > obj.selectClauseResults)
		&& (selectClauseDiagnosticInfos > obj.selectClauseDiagnosticInfos)
		&& (whereClauseResult > obj.whereClauseResult));
}

Status_t EventFilterResult_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
	return CopyToDestination(*this, destination);
}

Status_t EventFilterResult_t::CopyFrom(const BaseDataType_t& source)
{
	IntrusivePtr_t<const EventFilterResult_t> ptr = RuntimeCast<const EventFilterResult_t *>(source);
	if (!ptr.is_set())
	{
		return OpcUa_BadTypeMismatch;
	}

	return CopyFrom(*ptr);
}

Status_t EventFilterResult_t::CopyFrom(const EventFilterResult_t& source)
{
	Status_t status = selectClauseResults.CopyFrom(source.selectClauseResults);
	if (status.IsBad())
	{
		return status;
	}

	status = selectClauseDiagnosticInfos.CopyFrom(source.selectClauseDiagnosticInfos);
	if (status.IsBad())
	{
		return status;
	}

	status = whereClauseResult.CopyFrom(source.whereClauseResult);
	if (status.IsBad())
	{
		return status;
	}

	return OpcUa_Good;
}

uint32_t EventFilterResult_t::TypeId(uint16_t& namespaceIndex)  const
{
	namespaceIndex = 0; return TYPE_ID;
}

uint32_t EventFilterResult_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
	namespaceIndex = 0; return OpcUaId_EventFilterResult_Encoding_DefaultBinary;
}

const ArrayUA_t<StatusCode_t>& EventFilterResult_t::SelectClauseResults(void) const
{
	return selectClauseResults;
}

ArrayUA_t<StatusCode_t>& EventFilterResult_t::SelectClauseResults(void)
{ 
	return selectClauseResults;
}

const ArrayUA_t<DiagnosticInfo_t>& EventFilterResult_t::SelectClauseDiagnosticInfos(void) const
{ 
	return selectClauseDiagnosticInfos;
}

ArrayUA_t<DiagnosticInfo_t>& EventFilterResult_t::SelectClauseDiagnosticInfos(void)
{ 
	return selectClauseDiagnosticInfos;
}

const ContentFilterResult_t& EventFilterResult_t::WhereClauseResult(void) const
{
	return whereClauseResult;
}

ContentFilterResult_t& EventFilterResult_t::WhereClauseResult(void)
{ 
	return whereClauseResult;
}

Status_t EventFilterResult_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
	Status_t status = selectClauseResults.Encode(encoder, buffer);
	if (status.IsBad())
	{
		return status;
	}

	status = selectClauseDiagnosticInfos.Encode(encoder, buffer);
	if (status.IsBad())
	{
		return status;
	}

	status = whereClauseResult.Encode(encoder, buffer);
	if (status.IsBad())
	{
		return status;
	}

	return OpcUa_Good;
}

Status_t EventFilterResult_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, EventFilterResult_t& result)
{
	Status_t status = ArrayUA_t<StatusCode_t>::Decode(buffer, decoder, result.SelectClauseResults());
	if (status.IsBad())
	{
		return status;
	}

	status = ArrayUA_t<DiagnosticInfo_t>::Decode(buffer, decoder, result.SelectClauseDiagnosticInfos());
	if (status.IsBad())
	{
		return status;
	}

	status = ContentFilterResult_t::Decode(buffer, decoder, result.WhereClauseResult());
	if (status.IsBad())
	{
		return status;
	}

	return OpcUa_Good;
}

} // namespace uasdk

#endif // UASDK_INCLUDE_EVENTS

