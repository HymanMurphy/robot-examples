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

#include "opcua_call_method_result_t.h"

#if (UASDK_INCLUDE_METHOD_SERVICE_SET > 0)

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(CallMethodResult_t, Structure_t)

bool CallMethodResult_t::operator==(CallMethodResult_t const & obj) const
{
  return (
      (statusCode == obj.statusCode)
      && (inputArgumentResults == obj.inputArgumentResults)
      && (inputArgumentDiagnosticInfos == obj.inputArgumentDiagnosticInfos)
      && (outputArguments == obj.outputArguments));
}

bool CallMethodResult_t::operator>(CallMethodResult_t const & obj) const
{
  return (
      (statusCode > obj.statusCode)
      && (inputArgumentResults > obj.inputArgumentResults)
      && (inputArgumentDiagnosticInfos > obj.inputArgumentDiagnosticInfos)
      && (outputArguments > obj.outputArguments));
}

Status_t CallMethodResult_t::CopyFrom(const CallMethodResult_t& source)
{
  Status_t status = statusCode.CopyFrom(source.statusCode);
  if (status.IsBad())
  {
    return status;
  }

  status = inputArgumentResults.CopyFrom(source.inputArgumentResults);
  if (status.IsBad())
  {
    return status;
  }

  status = inputArgumentDiagnosticInfos.CopyFrom(source.inputArgumentDiagnosticInfos);
  if (status.IsBad())
  {
    return status;
  }

  status = outputArguments.CopyFrom(source.outputArguments);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t CallMethodResult_t::CopyFrom(const BaseDataType_t& source)
{
  const CallMethodResult_t* ptr = RuntimeCast<const CallMethodResult_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t CallMethodResult_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = statusCode.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = inputArgumentResults.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = inputArgumentDiagnosticInfos.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = outputArguments.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t CallMethodResult_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, CallMethodResult_t& result)
{
  Status_t status = StatusCode_t::Decode(buffer, decoder, result.StatusCode());
  if (status.IsBad())
  {
    return status;
  }

  status = ArrayUA_t<StatusCode_t>::Decode(buffer, decoder, result.InputArgumentResults());
  if (status.IsBad())
  {
    return status;
  }

  status = ArrayUA_t<DiagnosticInfo_t>::Decode(buffer, decoder, result.InputArgumentDiagnosticInfos());
  if (status.IsBad())
  {
    return status;
  }

  status = ArrayUA_t<BaseDataType_t>::Decode(buffer, decoder, result.OutputArguments());
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

CallMethodResult_t::~CallMethodResult_t() {}

bool CallMethodResult_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool CallMethodResult_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t CallMethodResult_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t CallMethodResult_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t CallMethodResult_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_CallMethodResult_Encoding_DefaultBinary;
}

const StatusCode_t& CallMethodResult_t::StatusCode(void) const 
{ 
  return statusCode; 
}

StatusCode_t& CallMethodResult_t::StatusCode(void) 
{ 
  return statusCode; 
}

const ArrayUA_t<StatusCode_t>& CallMethodResult_t::InputArgumentResults(void) const 
{
  return inputArgumentResults; 
}

ArrayUA_t<StatusCode_t>& CallMethodResult_t::InputArgumentResults(void)
{ 
  return inputArgumentResults; 
}

const ArrayUA_t<DiagnosticInfo_t>& CallMethodResult_t::InputArgumentDiagnosticInfos(void) const 
{
  return inputArgumentDiagnosticInfos; 
}

ArrayUA_t<DiagnosticInfo_t>& CallMethodResult_t::InputArgumentDiagnosticInfos(void) 
{
  return inputArgumentDiagnosticInfos; 
}

const ArrayUA_t<BaseDataType_t>& CallMethodResult_t::OutputArguments(void) const
{
  return outputArguments; 
}

ArrayUA_t<BaseDataType_t>& CallMethodResult_t::OutputArguments(void) 
{ 
  return outputArguments; 
}

} // namespace uasdk

#endif
