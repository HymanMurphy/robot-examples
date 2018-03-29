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

#include "opcua_server_status_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(ServerStatus_t, Structure_t)

bool ServerStatus_t::operator==(ServerStatus_t const & obj) const
{
  return (
      (startTime == obj.startTime)
      && (currentTime == obj.currentTime)
      && (state == obj.state)
      && (buildInfo == obj.buildInfo)
      && (secondsTillShutdown == obj.secondsTillShutdown)
      && (shutdownReason == obj.shutdownReason));
}

bool ServerStatus_t::operator>(ServerStatus_t const & obj) const
{
  return (
      (startTime > obj.startTime)
      && (currentTime > obj.currentTime)
      && (state > obj.state)
      && (buildInfo > obj.buildInfo)
      && (secondsTillShutdown > obj.secondsTillShutdown)
      && (shutdownReason > obj.shutdownReason));
}

Status_t ServerStatus_t::CopyFrom(const BaseDataType_t& source)
{
  const ServerStatus_t* ptr = RuntimeCast<const ServerStatus_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t ServerStatus_t::CopyFrom(const ServerStatus_t& source)
{
  Status_t status = startTime.CopyFrom(source.startTime);
  if (status.IsBad())
  {
    return status;
  }

  status = currentTime.CopyFrom(source.currentTime);
  if (status.IsBad())
  {
    return status;
  }

  status = state.CopyFrom(source.state);
  if (status.IsBad())
  {
    return status;
  }

  status = buildInfo.CopyFrom(source.buildInfo);
  if (status.IsBad())
  {
    return status;
  }

  status = secondsTillShutdown.CopyFrom(source.secondsTillShutdown);
  if (status.IsBad())
  {
    return status;
  }

  status = shutdownReason.CopyFrom(source.shutdownReason);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t ServerStatus_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = startTime.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = currentTime.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = state.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = buildInfo.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = secondsTillShutdown.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = shutdownReason.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t ServerStatus_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, ServerStatus_t& result)
{
  Status_t status = result.StartTime().Decode(buffer, decoder, result.StartTime());
  if (status.IsBad())
  {
    return status;
  }

  status = result.CurrentTime().Decode(buffer, decoder, result.CurrentTime());
  if (status.IsBad())
  {
    return status;
  }

  status = ServerState_t::Decode(buffer, decoder, result.State());
  if (status.IsBad())
  {
    return status;
  }

  status = BuildInfo_t::Decode(buffer, decoder, result.BuildInfo());
  if (status.IsBad())
  {
    return status;
  }

  status = UInt32_t::Decode(buffer, decoder, result.SecondsTillShutdown());
  if (status.IsBad())
  {
    return status;
  }

  status = LocalizedText_t::Decode(buffer, decoder, result.ShutdownReason());
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

ServerStatus_t::ServerStatus_t()
{}

ServerStatus_t::~ServerStatus_t()
{}

bool ServerStatus_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool ServerStatus_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t ServerStatus_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t ServerStatus_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

uint32_t ServerStatus_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return OpcUaId_ServerStatusDataType_Encoding_DefaultBinary;
}

const UtcTime_t& ServerStatus_t::StartTime(void) const
{
  return startTime;
}

UtcTime_t& ServerStatus_t::StartTime(void)
{
  return startTime;
}

const UtcTime_t&  ServerStatus_t::CurrentTime(void) const
{
  return currentTime;
}

UtcTime_t&  ServerStatus_t::CurrentTime(void)
{
  return currentTime;
}

const  ServerState_t& ServerStatus_t::State(void) const
{
  return state;
}

ServerState_t& ServerStatus_t::State(void)
{
  return state;
}

const BuildInfo_t& ServerStatus_t::BuildInfo(void) const
{
  return buildInfo;
}

BuildInfo_t& ServerStatus_t::BuildInfo(void)
{
  return buildInfo;
}

const UInt32_t&  ServerStatus_t::SecondsTillShutdown(void) const
{
  return secondsTillShutdown;
}

UInt32_t&  ServerStatus_t::SecondsTillShutdown(void)
{
  return secondsTillShutdown;
}

const LocalizedText_t& ServerStatus_t::ShutdownReason(void) const
{
  return shutdownReason;
}

LocalizedText_t& ServerStatus_t::ShutdownReason(void)
{
  return shutdownReason;
}

} // namespace uasdk
