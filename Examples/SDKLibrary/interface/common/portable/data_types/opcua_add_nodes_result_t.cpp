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

#include "opcua_add_nodes_result_t.h"
#include "icodec_t.h"

#if (UASDK_INCLUDE_NODE_MANAGEMENT_SERVICE_SET > 0)

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(AddNodesResult_t, Structure_t)

bool AddNodesResult_t::operator==(AddNodesResult_t const & obj) const
{
  return (
      (statusCode == obj.statusCode)
      && (addedNodeId == obj.addedNodeId));
}

bool AddNodesResult_t::operator>(AddNodesResult_t const & obj) const
{
	return (
		(statusCode > obj.statusCode)
		&& (addedNodeId > obj.addedNodeId));
}

Status_t AddNodesResult_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

Status_t AddNodesResult_t::CopyFrom(const AddNodesResult_t& source)
{
  Status_t status = statusCode.CopyFrom(source.statusCode);

  if (status.IsBad())
  {
    return status;
  }

  status = addedNodeId->CopyFrom(*source.addedNodeId);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t AddNodesResult_t::CopyFrom(const BaseDataType_t& source)
{
  const AddNodesResult_t* ptr = RuntimeCast<const AddNodesResult_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t AddNodesResult_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = statusCode.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = encoder.Encode(addedNodeId, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t AddNodesResult_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, AddNodesResult_t& result)
{
  Status_t status = StatusCode_t::Decode(buffer, decoder, result.StatusCode());
  if (status.IsBad()) 
  {
    return status;
  }

  status = NodeId_t::Decode(buffer, decoder, result.AddedNodeId());
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

AddNodesResult_t::~AddNodesResult_t()
{}

bool AddNodesResult_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool AddNodesResult_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

uint32_t AddNodesResult_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t AddNodesResult_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_AddNodesResult_Encoding_DefaultBinary;
}

const StatusCode_t & AddNodesResult_t::StatusCode() const
{
	return statusCode;
}

StatusCode_t & AddNodesResult_t::StatusCode()
{
	return statusCode;
}

IntrusivePtr_t<const NodeId_t> AddNodesResult_t::AddedNodeId() const
{
	return addedNodeId;
}

IntrusivePtr_t<NodeId_t>& AddNodesResult_t::AddedNodeId()
{
	return addedNodeId;
}

} // namespace uasdk

#endif
