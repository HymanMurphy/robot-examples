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

#include "content_filter_result_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "opcua_datatype_utilities_t.h"
#include "opcua_enum_value_type_t.h"
#include "opcua_mon_item_notification_t.h"
#include "opcua_data_change_notification_t.h"
#include "opcua_data_change_filter_t.h"
#include "opcua_browse_continuation_point_t.h"
#include "opcua_argument_t.h"
#include "opcua_call_method_result_t.h"
#include "opcua_call_method_request_t.h"
#include "opcua_transfer_result_t.h"
#include "opcua_subscription_acknowledgement_t.h"
#include "opcua_mon_item_modify_result_t.h"
#include "opcua_mon_item_modify_request_t.h"
#include "opcua_mon_item_create_result_t.h"
#include "opcua_mon_item_create_request_t.h"
#include "opcua_relative_path_element_t.h"
#include "opcua_browse_path_result_t.h"
#include "opcua_browse_path_t.h"
#include "opcua_write_value_t.h"
#include "opcua_browse_result_t.h"
#include "opcua_reference_description_t.h"
#include "opcua_user_token_policy_t.h"
#include "opcua_endpoint_description_t.h"
#include "opcua_float_t.h"
#include "opcua_uint64_t.h"
#include "opcua_int16_t.h"
#include "opcua_sbyte_t.h"
#include "opcua_xml_element_t.h"
#include "filter_operand_t.h"

namespace uasdk
{
  
UA_DEFINE_RUNTIME_TYPE(ContentFilterResult_t, Structure_t);

ContentFilterResult_t::ContentFilterResult_t()
{
}

ContentFilterResult_t::~ContentFilterResult_t()
{
}

bool ContentFilterResult_t::operator==(BaseDataType_t const & obj) const
{
	return OperatorEqualTo(*this, obj);
}

bool ContentFilterResult_t::operator==(ContentFilterResult_t const & obj) const
{
	return (
		(elementResults == obj.elementResults)
		&& (elementDiagnosticInfos == obj.elementDiagnosticInfos));
}

bool ContentFilterResult_t::operator>(BaseDataType_t const & obj) const
{
	return OperatorGreaterThan(*this, obj);
}

bool ContentFilterResult_t::operator>(ContentFilterResult_t const & obj) const
{
	return (
		(elementResults > obj.elementResults)
		&& (elementDiagnosticInfos > obj.elementDiagnosticInfos));
}

Status_t ContentFilterResult_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
	return CopyToDestination(*this, destination);
}

Status_t ContentFilterResult_t::CopyFrom(const BaseDataType_t& source)
{
	IntrusivePtr_t<const ContentFilterResult_t> ptr = RuntimeCast<const ContentFilterResult_t *>(source);
	if (!ptr.is_set())
	{
		return OpcUa_BadTypeMismatch;
	}

	return CopyFrom(*ptr);
}

Status_t ContentFilterResult_t::CopyFrom(const ContentFilterResult_t& source)
{
	Status_t status = elementResults.CopyFrom(source.elementResults);
	if (status.IsBad())
	{
		return status;
	}

	status = elementDiagnosticInfos.CopyFrom(source.elementDiagnosticInfos);
	if (status.IsBad())
	{
		return status;
	}

	return OpcUa_Good;
}

uint32_t ContentFilterResult_t::TypeId(uint16_t& namespaceIndex)  const
{
	namespaceIndex = 0; return TYPE_ID;
}

uint32_t ContentFilterResult_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
	namespaceIndex = 0; return OpcUaId_ContentFilterResult_Encoding_DefaultBinary;
}

const ArrayUA_t<ContentFilterElementResult_t>& ContentFilterResult_t::ElementResults(void) const
{
	return elementResults;
}

ArrayUA_t<ContentFilterElementResult_t>& ContentFilterResult_t::ElementResults(void) 
{ 
	return elementResults;
}

const ArrayUA_t<DiagnosticInfo_t>& ContentFilterResult_t::ElementDiagnosticInfos(void) const
{ 
	return elementDiagnosticInfos; 
}

ArrayUA_t<DiagnosticInfo_t>& ContentFilterResult_t::ElementDiagnosticInfos(void)
{ 
	return elementDiagnosticInfos; 
}

const Status_t& ContentFilterResult_t::StatusCode() const 
{
	return statusCode; 
}

Status_t& ContentFilterResult_t::StatusCode() 
{ 
	return statusCode; 
}

Status_t ContentFilterResult_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
	Status_t status = elementResults.Encode(encoder, buffer);
	if (status.IsBad())
	{
		return status;
	}

	status = elementDiagnosticInfos.Encode(encoder, buffer);
	if (status.IsBad())
	{
		return status;
	}

	return OpcUa_Good;
}

Status_t ContentFilterResult_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, ContentFilterResult_t& result)
{
	Status_t status = ArrayUA_t<ContentFilterElementResult_t>::Decode(buffer, decoder, result.ElementResults());
	if (status.IsBad())
	{
		return status;
	}

	status = ArrayUA_t<DiagnosticInfo_t>::Decode(buffer, decoder, result.ElementDiagnosticInfos());
	if (status.IsBad())
	{
		return status;
	}

	return OpcUa_Good;
}

} // namespace uasdk

#endif // UASDK_INCLUDE_EVENTS

