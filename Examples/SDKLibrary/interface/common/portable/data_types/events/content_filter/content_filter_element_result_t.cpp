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

#include "content_filter_element_result_t.h"

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
  
UA_DEFINE_RUNTIME_TYPE(ContentFilterElementResult_t, Structure_t);

ContentFilterElementResult_t::ContentFilterElementResult_t()
{
}

ContentFilterElementResult_t::~ContentFilterElementResult_t()
{
}

bool ContentFilterElementResult_t::operator==(BaseDataType_t const & obj) const
{
	return OperatorEqualTo(*this, obj);
}

bool ContentFilterElementResult_t::operator==(ContentFilterElementResult_t const & obj) const
{
	return (
		(statusCode == obj.statusCode)
		&&(operandStatusCodes == obj.operandStatusCodes)
		&& (operandDiagnosticInfos == obj.operandDiagnosticInfos));
}

bool ContentFilterElementResult_t::operator>(BaseDataType_t const & obj) const
{
	return OperatorGreaterThan(*this, obj);
}

bool ContentFilterElementResult_t::operator>(ContentFilterElementResult_t const & obj) const
{
	return (
		(statusCode > obj.statusCode)
		&&(operandStatusCodes > obj.operandStatusCodes)
		&& (operandDiagnosticInfos > obj.operandDiagnosticInfos));
}

Status_t ContentFilterElementResult_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
	return CopyToDestination(*this, destination);
}

Status_t ContentFilterElementResult_t::CopyFrom(const BaseDataType_t& source)
{
	IntrusivePtr_t<const ContentFilterElementResult_t> ptr = RuntimeCast<const ContentFilterElementResult_t*>(source);
	if (!ptr.is_set())
	{
		return OpcUa_BadTypeMismatch;
	}

	return CopyFrom(*ptr);
}

Status_t ContentFilterElementResult_t::CopyFrom(const ContentFilterElementResult_t& source)
{
	Status_t status = statusCode.CopyFrom(source.statusCode);
	if (status.IsBad())
	{
		return status;
	}

	status = operandStatusCodes.CopyFrom(source.operandStatusCodes);
	if (status.IsBad())
	{
		return status;
	}

	status = operandDiagnosticInfos.CopyFrom(source.operandDiagnosticInfos);
	if (status.IsBad())
	{
		return status;
	}

	return OpcUa_Good;
}

uint32_t ContentFilterElementResult_t::TypeId(uint16_t& namespaceIndex)  const
{
	namespaceIndex = 0; return TYPE_ID;
}

uint32_t ContentFilterElementResult_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
	namespaceIndex = 0; return OpcUaId_ContentFilterElementResult_Encoding_DefaultBinary;
}

const StatusCode_t& ContentFilterElementResult_t::StatusCode(void) const 
{ 
	return statusCode; 
}

StatusCode_t& ContentFilterElementResult_t::StatusCode(void)
{ 
	return statusCode;
}

const ArrayUA_t<StatusCode_t>& ContentFilterElementResult_t::OperandStatusCodes(void) const 
{ 
	return operandStatusCodes; 
}

ArrayUA_t<StatusCode_t>& ContentFilterElementResult_t::OperandStatusCodes(void) 
{ 
	return operandStatusCodes; 
}

const ArrayUA_t<DiagnosticInfo_t>& ContentFilterElementResult_t::OperandDiagnosticInfos(void) const 
{ 
	return operandDiagnosticInfos;
}

ArrayUA_t<DiagnosticInfo_t>& ContentFilterElementResult_t::OperandDiagnosticInfos(void) 
{ 
	return operandDiagnosticInfos;
}

Status_t ContentFilterElementResult_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
	Status_t status = statusCode.Encode(encoder, buffer);
	if (status.IsBad())
	{
		return status;
	}

	status = operandStatusCodes.Encode(encoder, buffer);
	if (status.IsBad())
	{
		return status;
	}

	status = operandDiagnosticInfos.Encode(encoder, buffer);
	if (status.IsBad())
	{
		return status;
	}

	return OpcUa_Good;
}

Status_t ContentFilterElementResult_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, ContentFilterElementResult_t& result)
{
	Status_t status = StatusCode_t::Decode(buffer, decoder, result.StatusCode());
	if (status.IsBad())
	{
		return status;
	}

	status = ArrayUA_t<StatusCode_t>::Decode(buffer, decoder, result.OperandStatusCodes());
	if (status.IsBad())
	{
		return status;
	}

	status = ArrayUA_t<DiagnosticInfo_t>::Decode(buffer, decoder, result.OperandDiagnosticInfos());
	if (status.IsBad())
	{
		return status;
	}

	return OpcUa_Good;
}

} // namespace uasdk

#endif // UASDK_INCLUDE_EVENTS
