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

#include "opcua_channel_security_token_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(ChannelSecurityToken_t, Structure_t)

ChannelSecurityToken_t::ChannelSecurityToken_t() : channelId(0), tokenId(0), revisedLifetime(0)
{
}

bool ChannelSecurityToken_t::operator==(ChannelSecurityToken_t const & obj) const
{
  return (
      (channelId == obj.channelId)
      && (tokenId == obj.tokenId)
      && (createdAt == obj.createdAt)
      && (revisedLifetime == obj.revisedLifetime));
}

bool ChannelSecurityToken_t::operator>(ChannelSecurityToken_t const & obj) const
{
  return (
      (channelId > obj.channelId)
      && (tokenId > obj.tokenId)
      && (createdAt > obj.createdAt)
      && (revisedLifetime > obj.revisedLifetime));
}

Status_t ChannelSecurityToken_t::CopyFrom(const ChannelSecurityToken_t& source)
{
  Status_t status = channelId.CopyFrom(source.channelId);
  if (status.IsBad())
  {
    return status;
  }

  status = tokenId.CopyFrom(source.tokenId);
  if (status.IsBad())
  {
    return status;
  }

  status = createdAt.CopyFrom(source.createdAt);
  if (status.IsBad())
  {
    return status;
  }

  status = revisedLifetime.CopyFrom(source.revisedLifetime);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t ChannelSecurityToken_t::CopyFrom(const BaseDataType_t& source)
{
  const ChannelSecurityToken_t* ptr = RuntimeCast<const ChannelSecurityToken_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t ChannelSecurityToken_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = channelId.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = tokenId.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = createdAt.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = revisedLifetime.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t ChannelSecurityToken_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, ChannelSecurityToken_t& result)
{
  Status_t status = UInt32_t::Decode(buffer, decoder, result.ChannelId());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.TokenId());
  if (status.IsBad())
  {
    return status;
  }

  status = DateTime_t::Decode(buffer, decoder, result.CreatedAt());
  if (status.IsBad())
  {
    return status;
  }

  status = Int32_t::Decode(buffer, decoder, result.RevisedLifetime());
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

ChannelSecurityToken_t::~ChannelSecurityToken_t() 
{}

bool ChannelSecurityToken_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool ChannelSecurityToken_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t ChannelSecurityToken_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

const UInt32_t& ChannelSecurityToken_t::ChannelId(void) const 
{
  return channelId; 
}

UInt32_t& ChannelSecurityToken_t::ChannelId(void) 
{
  return channelId; 
}

const UInt32_t& ChannelSecurityToken_t::TokenId(void) const 
{
  return tokenId; 
}

UInt32_t& ChannelSecurityToken_t::TokenId(void) 
{
  return tokenId; 
}

const DateTime_t& ChannelSecurityToken_t::CreatedAt(void) const 
{
  return createdAt; 
}

DateTime_t& ChannelSecurityToken_t::CreatedAt(void) 
{
  return createdAt; 
}

const Int32_t& ChannelSecurityToken_t::RevisedLifetime(void) const
{
  return revisedLifetime; 
}

Int32_t& ChannelSecurityToken_t::RevisedLifetime(void) 
{
  return revisedLifetime; 
}

uint32_t ChannelSecurityToken_t::TypeId(uint16_t &namespaceIndex) const
{
  namespaceIndex = 0;
  return ChannelSecurityToken_t::TYPE_ID;
}

uint32_t ChannelSecurityToken_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_ChannelSecurityToken_Encoding_DefaultBinary;
}

} // namespace uasdk
