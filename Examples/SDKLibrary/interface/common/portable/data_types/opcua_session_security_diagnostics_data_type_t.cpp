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

#include "opcua_session_security_diagnostics_data_type_t.h"

#if (UASDK_INCLUDE_SESSION_DIAGNOSTICS > 0)

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(SessionSecurityDiagnosticsDataType_t, Structure_t)

SessionSecurityDiagnosticsDataType_t::SessionSecurityDiagnosticsDataType_t()
{ }

SessionSecurityDiagnosticsDataType_t::~SessionSecurityDiagnosticsDataType_t()
{ }

bool SessionSecurityDiagnosticsDataType_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool SessionSecurityDiagnosticsDataType_t::operator==(SessionSecurityDiagnosticsDataType_t const & obj) const
{
  return (  (sessionId == obj.sessionId)
          && (clientUserIdOfSession == obj.clientUserIdOfSession)
          && (clientUserIdHistory == obj.clientUserIdHistory)
          && (authenticationMechanism == obj.authenticationMechanism)
          && (encoding == obj.encoding)
          && (transportProtocol == obj.transportProtocol)
          && (securityMode == obj.securityMode)
          && (securityPolicyUri == obj.securityPolicyUri)
          && (clientCertificate == obj.clientCertificate)
        );
}

bool SessionSecurityDiagnosticsDataType_t::operator!=(SessionSecurityDiagnosticsDataType_t const & obj) const
{
  return !(*this == obj);
}

bool SessionSecurityDiagnosticsDataType_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

bool SessionSecurityDiagnosticsDataType_t::operator>(SessionSecurityDiagnosticsDataType_t const & obj) const
{
  return ((sessionId > obj.sessionId)
          && (clientUserIdOfSession > obj.clientUserIdOfSession)
          && (clientUserIdHistory > obj.clientUserIdHistory)
          && (authenticationMechanism > obj.authenticationMechanism)
          && (encoding > obj.encoding)
          && (transportProtocol > obj.transportProtocol)
          && (securityMode > obj.securityMode)
          && (securityPolicyUri > obj.securityPolicyUri)
          && (clientCertificate > obj.clientCertificate)
        );
}

Status_t SessionSecurityDiagnosticsDataType_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

Status_t SessionSecurityDiagnosticsDataType_t::CopyFrom(const BaseDataType_t& source)
{
  const SessionSecurityDiagnosticsDataType_t* ptr = RuntimeCast<const SessionSecurityDiagnosticsDataType_t*>(source);
  if (!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t SessionSecurityDiagnosticsDataType_t::CopyFrom(const SessionSecurityDiagnosticsDataType_t& source)
{
  Status_t status = sessionId.CopyFrom(source.sessionId);
  if (status.IsBad())
  {
    return status;
  }

  status = clientUserIdOfSession.CopyFrom(source.clientUserIdOfSession);
  if (status.IsBad())
  {
    return status;
  }

  status = clientUserIdHistory.CopyFrom(source.clientUserIdHistory);
  if (status.IsBad())
  {
    return status;
  }

  status = authenticationMechanism.CopyFrom(source.authenticationMechanism);
  if (status.IsBad())
  {
    return status;
  }
  

  status = encoding.CopyFrom(source.encoding);
  if (status.IsBad())
  {
    return status;
  }

  status = transportProtocol.CopyFrom(source.transportProtocol);
  if (status.IsBad())
  {
    return status;
  }

  status = securityMode.CopyFrom(source.securityMode);
  if (status.IsBad())
  {
    return status;
  }

  status = securityPolicyUri.CopyFrom(source.securityPolicyUri);
  if (status.IsBad())
  {
    return status;
  }

  return clientCertificate.CopyFrom(source.clientCertificate);
  
}

uint32_t SessionSecurityDiagnosticsDataType_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0;
  return TYPE_ID;
}

uint32_t SessionSecurityDiagnosticsDataType_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0;
  return OpcUaId_SessionSecurityDiagnosticsDataType_Encoding_DefaultBinary;
}

const NodeIdGuid_t& SessionSecurityDiagnosticsDataType_t::SessionId() const
{
  return sessionId;
}

NodeIdGuid_t& SessionSecurityDiagnosticsDataType_t::SessionId()
{
  return sessionId;
}

const String_t& SessionSecurityDiagnosticsDataType_t::ClientUserIdOfSession() const
{
  return clientUserIdOfSession;
}

String_t& SessionSecurityDiagnosticsDataType_t::ClientUserIdOfSession()
{
  return clientUserIdOfSession;
}

const ArrayUA_t<String_t>& SessionSecurityDiagnosticsDataType_t::ClientUserIdHistory() const
{
  return clientUserIdHistory;
}

ArrayUA_t<String_t>& SessionSecurityDiagnosticsDataType_t::ClientUserIdHistory()
{
  return clientUserIdHistory;
}

const String_t& SessionSecurityDiagnosticsDataType_t::AuthenticationMechanism() const
{
  return authenticationMechanism;
}

String_t& SessionSecurityDiagnosticsDataType_t::AuthenticationMechanism()
{
  return authenticationMechanism;
}

const String_t& SessionSecurityDiagnosticsDataType_t::Encoding() const
{
  return encoding;
}

String_t& SessionSecurityDiagnosticsDataType_t::Encoding()
{
  return encoding;
}

const String_t& SessionSecurityDiagnosticsDataType_t::TransportProtocol() const
{
  return transportProtocol;
}

String_t& SessionSecurityDiagnosticsDataType_t::TransportProtocol()
{
  return transportProtocol;
}

const MessageSecurityMode_t& SessionSecurityDiagnosticsDataType_t::SecurityMode() const
{
  return securityMode;
}

MessageSecurityMode_t& SessionSecurityDiagnosticsDataType_t::SecurityMode()
{
  return securityMode;
}

const String_t& SessionSecurityDiagnosticsDataType_t::SecurityPolicyUri() const
{
  return securityPolicyUri;
}

String_t& SessionSecurityDiagnosticsDataType_t::SecurityPolicyUri()
{
  return securityPolicyUri;
}

const ByteString_t& SessionSecurityDiagnosticsDataType_t::ClientCertificate() const
{
  return clientCertificate;
}

ByteString_t& SessionSecurityDiagnosticsDataType_t::ClientCertificate()
{
  return clientCertificate;
}

Status_t SessionSecurityDiagnosticsDataType_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = sessionId.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = clientUserIdOfSession.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }
 
  status = clientUserIdHistory.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = authenticationMechanism.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = encoding.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = transportProtocol.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = securityMode.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = securityPolicyUri.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return clientCertificate.Encode(encoder, buffer);
}

Status_t SessionSecurityDiagnosticsDataType_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, SessionSecurityDiagnosticsDataType_t& result)
{
  IntrusivePtr_t<NodeId_t> sessionId_;
  Status_t status = NodeId_t::Decode(buffer, decoder, sessionId_);
  if (status.IsBad() || !sessionId_.is_set())
  {
    return status;
  }

  status = result.SessionId().CopyFrom(*sessionId_);
  if (status.IsBad())
  {
    return status;
  }

  status = String_t::Decode(buffer, decoder, result.ClientUserIdOfSession());
  if (status.IsBad())
  {
    return status;
  }

  status = ArrayUA_t<String_t>::Decode(buffer, decoder, result.ClientUserIdHistory());
  if (status.IsBad())
  {
    return status;
  }

  status = String_t::Decode(buffer, decoder, result.AuthenticationMechanism());
  if (status.IsBad())
  {
    return status;
  }

  status = String_t::Decode(buffer, decoder, result.Encoding());
  if (status.IsBad())
  {
    return status;
  }

  status = String_t::Decode(buffer, decoder, result.TransportProtocol());
  if (status.IsBad())
  {
    return status;
  }

  status = MessageSecurityMode_t::Decode(buffer, decoder, result.SecurityMode());
  if (status.IsBad())
  {
    return status;
  }

  status = String_t::Decode(buffer, decoder, result.SecurityPolicyUri());
  if (status.IsBad())
  {
    return status;
  }

  return ByteString_t::Decode(buffer, decoder, result.ClientCertificate());
}

} // namespace uasdk

#endif  //UASDK_INCLUDE_SESSION_DIAGNOSTICS