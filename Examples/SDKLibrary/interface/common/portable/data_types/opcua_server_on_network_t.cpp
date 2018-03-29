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

#include "opcua_server_on_network_t.h"

#if (UASDK_INCLUDE_ADDITIONAL_DISCOVERY_SERVICES > 0)

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(ServerOnNetwork_t, Structure_t)

bool ServerOnNetwork_t::operator==(ServerOnNetwork_t const & obj) const
{
  return (
      (recordId == obj.recordId)
      && (serverName == obj.serverName)
      && (discoveryUrl == obj.discoveryUrl)
      && (serverCapabilities == obj.serverCapabilities));
}

bool ServerOnNetwork_t::operator>(ServerOnNetwork_t const & obj) const
{
  return (
      (recordId > obj.recordId)
      && (serverName > obj.serverName)
      && (discoveryUrl > obj.discoveryUrl)
      && (serverCapabilities > obj.serverCapabilities));
}

Status_t ServerOnNetwork_t::CopyFrom(const BaseDataType_t& source)
{
  const ServerOnNetwork_t* ptr = RuntimeCast<const ServerOnNetwork_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t ServerOnNetwork_t::CopyFrom(const ServerOnNetwork_t& source)
{
  Status_t status = recordId.CopyFrom(source.recordId);
  if (status.IsBad())
  {
    return status;
  }

  status = serverName.CopyFrom(source.serverName);
  if (status.IsBad())
  {
    return status;
  }

  status = discoveryUrl.CopyFrom(source.discoveryUrl);
  if (status.IsBad())
  {
    return status;
  }

  status = serverCapabilities.CopyFrom(source.serverCapabilities);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t ServerOnNetwork_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = recordId.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = serverName.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = discoveryUrl.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = serverCapabilities.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t ServerOnNetwork_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, ServerOnNetwork_t& result)
{
  Status_t status = UInt32_t::Decode(buffer, decoder, result.RecordId());
  if (status.IsBad())
  {
    return status;
  }

  status = String_t::Decode(buffer, decoder, result.ServerName());
  if (status.IsBad())
  {
    return status;
  }

  status = String_t::Decode(buffer, decoder, result.DiscoveryUrl());
  if (status.IsBad())
  {
    return status;
  }

  status = ArrayUA_t<String_t>::Decode(buffer, decoder, result.ServerCapabilities());
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

ServerOnNetwork_t::ServerOnNetwork_t()
{}

ServerOnNetwork_t::~ServerOnNetwork_t()
{}

bool ServerOnNetwork_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool ServerOnNetwork_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t ServerOnNetwork_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t ServerOnNetwork_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t ServerOnNetwork_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
    namespaceIndex = 0; return OpcUaId_ServerOnNetwork_Encoding_DefaultBinary;
}

const UInt32_t &ServerOnNetwork_t::RecordId() const
{
    return recordId;
}

UInt32_t &ServerOnNetwork_t::RecordId()
{
    return recordId;
}

const String_t &ServerOnNetwork_t::ServerName() const
{
    return serverName;
}

String_t &ServerOnNetwork_t::ServerName()
{
    return serverName;
}

const String_t &ServerOnNetwork_t::DiscoveryUrl() const
{
    return discoveryUrl;
}

String_t &ServerOnNetwork_t::DiscoveryUrl()
{
    return discoveryUrl;
}

const ArrayUA_t<String_t> &ServerOnNetwork_t::ServerCapabilities() const
{
    return serverCapabilities;
}

ArrayUA_t<String_t> &ServerOnNetwork_t::ServerCapabilities()
{
    return serverCapabilities;
}

} // namespace uasdk

#endif
