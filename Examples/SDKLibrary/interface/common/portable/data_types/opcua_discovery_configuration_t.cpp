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

#include "opcua_discovery_configuration_t.h"

#if (UASDK_INCLUDE_ADDITIONAL_DISCOVERY_SERVICES > 0)

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(MdnsDiscoveryConfiguration_t, Structure_t)

bool MdnsDiscoveryConfiguration_t::operator==(MdnsDiscoveryConfiguration_t const & obj) const
{
  return (
      (mdnsServerName == obj.mdnsServerName)
      && (serverCapabilities == obj.serverCapabilities));
}

bool MdnsDiscoveryConfiguration_t::operator>(MdnsDiscoveryConfiguration_t const & obj) const
{
	return (
		(mdnsServerName > obj.mdnsServerName)
		&& (serverCapabilities > obj.serverCapabilities));
}

Status_t MdnsDiscoveryConfiguration_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

Status_t MdnsDiscoveryConfiguration_t::CopyFrom(const MdnsDiscoveryConfiguration_t& source)
{
  Status_t status = mdnsServerName.CopyFrom(source.mdnsServerName);

  if (status.IsBad())
  {
    return status;
  }

  status = serverCapabilities.CopyFrom(source.serverCapabilities);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t MdnsDiscoveryConfiguration_t::CopyFrom(const BaseDataType_t& source)
{
  const MdnsDiscoveryConfiguration_t* ptr = RuntimeCast<const MdnsDiscoveryConfiguration_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

const uasdk::ArrayUA_t<uasdk::String_t>& MdnsDiscoveryConfiguration_t::ServerCapabilities(void) const
{
	return serverCapabilities;
}

uasdk::ArrayUA_t<uasdk::String_t>& MdnsDiscoveryConfiguration_t::ServerCapabilities(void)
{
	return serverCapabilities;
}

Status_t MdnsDiscoveryConfiguration_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = mdnsServerName.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = serverCapabilities.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t MdnsDiscoveryConfiguration_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, MdnsDiscoveryConfiguration_t& result)
{
  Status_t status = String_t::Decode(buffer, decoder, result.MdnsServerName());
  if (status.IsBad()) 
  {
    return status;
  }

  status = ArrayUA_t<String_t>::Decode(buffer, decoder, result.ServerCapabilities());
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

MdnsDiscoveryConfiguration_t::~MdnsDiscoveryConfiguration_t()
{}

bool MdnsDiscoveryConfiguration_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool MdnsDiscoveryConfiguration_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

uint32_t MdnsDiscoveryConfiguration_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t MdnsDiscoveryConfiguration_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_MdnsDiscoveryConfiguration_Encoding_DefaultBinary;
}

const uasdk::String_t& MdnsDiscoveryConfiguration_t::MdnsServerName(void) const
{
	return mdnsServerName;
}

uasdk::String_t& MdnsDiscoveryConfiguration_t::MdnsServerName(void)
{
	return mdnsServerName;
}

} // namespace uasdk

#endif
