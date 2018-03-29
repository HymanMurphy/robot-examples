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

#include "opcua_view_description_t.h"
#include "icodec_t.h"
namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(ViewDescription_t, Structure_t)

bool ViewDescription_t::operator==(ViewDescription_t const & obj) const
{
  return (
      Equal(viewId, obj.viewId)
      && (timestamp == obj.timestamp)
      && (viewVersion == obj.viewVersion));
}

bool ViewDescription_t::operator>(ViewDescription_t const & obj) const
{
  return (
      GreaterThan(viewId, obj.viewId)
      && (timestamp > obj.timestamp)
      && (viewVersion > obj.viewVersion));
}

Status_t ViewDescription_t::CopyFrom(const BaseDataType_t& source)
{
  const ViewDescription_t* ptr = RuntimeCast<const ViewDescription_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t ViewDescription_t::CopyFrom(const ViewDescription_t& source)
{
  if(!source.viewId.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  Status_t status = source.viewId->CopyToNodeId(viewId);
  if (status.IsBad())
  {
    return status;
  }

  status = timestamp.CopyFrom(source.timestamp);
  if (status.IsBad())
  {
    return status;
  }

  status = viewVersion.CopyFrom(source.viewVersion);
  if (status.IsBad())
  {
    return status;
  }
  return OpcUa_Good;
}

Status_t ViewDescription_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status;

  status = encoder.Encode(viewId, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = timestamp.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = viewVersion.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t ViewDescription_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, ViewDescription_t& result)
{
  Status_t status = NodeId_t::Decode(buffer, decoder, result.ViewId());
  if (status.IsBad())
  {
    return status;
  }

  status = result.Timestamp().Decode(buffer, decoder, result.Timestamp());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.ViewVersion());
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

ViewDescription_t::~ViewDescription_t()
{}

bool ViewDescription_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool ViewDescription_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t ViewDescription_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t ViewDescription_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t ViewDescription_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_ViewDescription_Encoding_DefaultBinary;
}

IntrusivePtr_t<const NodeId_t> ViewDescription_t::ViewId(void) const
{
  return viewId;
}

IntrusivePtr_t<NodeId_t>& ViewDescription_t::ViewId(void)
{
  return viewId;
}

const UtcTime_t& ViewDescription_t::Timestamp(void) const
{
  return timestamp;
}

UtcTime_t& ViewDescription_t::Timestamp(void)
{
  return timestamp;
}

const UInt32_t&  ViewDescription_t::ViewVersion(void) const
{
  return viewVersion;
}

UInt32_t&  ViewDescription_t::ViewVersion(void)
{
  return viewVersion;
}

} // namespace uasdk
