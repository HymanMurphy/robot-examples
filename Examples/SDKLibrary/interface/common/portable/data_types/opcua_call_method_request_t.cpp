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

#include "opcua_call_method_request_t.h"

#if (UASDK_INCLUDE_METHOD_SERVICE_SET > 0)

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(CallMethodRequest_t, Structure_t)

bool CallMethodRequest_t::operator==(CallMethodRequest_t const & obj) const
{
  return (
      Equal(objectId, obj.objectId)
      && Equal(methodId, obj.methodId)
      && (inputArguments == obj.inputArguments));
}

bool CallMethodRequest_t::operator>(CallMethodRequest_t const & obj) const
{
  return (
      GreaterThan(objectId, obj.objectId)
      && GreaterThan(methodId, obj.methodId)
      && (inputArguments == obj.inputArguments));
}

Status_t CallMethodRequest_t::CopyFrom(const CallMethodRequest_t& source)
{
  if( (!source.objectId.is_set()) || (!source.methodId.is_set()) )
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  Status_t status = source.objectId->CopyToNodeId(objectId);
  if (status.IsBad())
  {
    return status;
  }

  status = source.methodId->CopyToNodeId(methodId);
  if (status.IsBad())
  {
    return status;
  }

  status = inputArguments.CopyFrom(source.inputArguments);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t CallMethodRequest_t::CopyFrom(const BaseDataType_t& source)
{
  const CallMethodRequest_t* ptr = RuntimeCast<const CallMethodRequest_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t CallMethodRequest_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status;

  if (!objectId.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadEncodingError);
  }
  status = objectId->Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  if (!methodId.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadEncodingError);
  }
  status = methodId->Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = inputArguments.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t CallMethodRequest_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, CallMethodRequest_t& result)
{
  Status_t status = NodeId_t::Decode(buffer, decoder, result.ObjectId());
  if (status.IsBad())
  {
    return status;
  }

  status = NodeId_t::Decode(buffer, decoder, result.MethodId());
  if (status.IsBad())
  {
    return status;
  }

  status = ArrayUA_t<BaseDataType_t>::Decode(buffer, decoder, result.InputArguments());
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

CallMethodRequest_t::~CallMethodRequest_t() {}

bool CallMethodRequest_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool CallMethodRequest_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t CallMethodRequest_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t CallMethodRequest_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t CallMethodRequest_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_CallMethodRequest_Encoding_DefaultBinary;
}

IntrusivePtr_t<const NodeId_t> CallMethodRequest_t::ObjectId(void) const 
{
  return objectId; 
}

IntrusivePtr_t<NodeId_t>& CallMethodRequest_t::ObjectId(void) 
{
  return objectId;
}

IntrusivePtr_t<const NodeId_t> CallMethodRequest_t::MethodId(void) const 
{
  return methodId; 
}

IntrusivePtr_t<NodeId_t>& CallMethodRequest_t::MethodId(void)
{
  return methodId; 
}

const ArrayUA_t<BaseDataType_t>& CallMethodRequest_t::InputArguments(void) const
{ 
  return inputArguments; 
}

ArrayUA_t<BaseDataType_t>& CallMethodRequest_t::InputArguments(void) 
{
  return inputArguments; 
}

} // namespace uasdk

#endif
