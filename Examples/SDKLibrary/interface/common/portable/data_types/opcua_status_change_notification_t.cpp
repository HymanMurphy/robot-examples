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

#include "opcua_status_change_notification_t.h"

#if (UASDK_INCLUDE_SUBSCRIPTIONS > 0)

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(StatusChangeNotification_t, Structure_t)

bool StatusChangeNotification_t::operator==(StatusChangeNotification_t const & obj) const
{
  return (
      (statusCode == obj.statusCode)
      && (diagnosticInfo == obj.diagnosticInfo));
}

bool StatusChangeNotification_t::operator>(StatusChangeNotification_t const & obj) const
{
   return (
       (statusCode > obj.statusCode)
       && (diagnosticInfo > obj.diagnosticInfo));
}

Status_t StatusChangeNotification_t::CopyFrom(const BaseDataType_t& source)
{
  const StatusChangeNotification_t* ptr = RuntimeCast<const StatusChangeNotification_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t StatusChangeNotification_t::CopyFrom(const StatusChangeNotification_t& source)
{
  Status_t status = statusCode.CopyFrom(source.statusCode);
  if (status.IsBad())
  {
    return status;
  }

  status = diagnosticInfo.CopyFrom(source.diagnosticInfo);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t StatusChangeNotification_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  Status_t status = statusCode.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  status = diagnosticInfo.Encode(encoder, buffer);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t StatusChangeNotification_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, StatusChangeNotification_t& result)
{
  Status_t status = StatusCode_t::Decode(buffer, decoder, result.StatusCode());
  if (status.IsBad())
  {
    return status;
  }

  status = result.DiagnosticInfo().Decode(buffer, decoder, result.DiagnosticInfo());
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

StatusChangeNotification_t::~StatusChangeNotification_t()
{}

bool StatusChangeNotification_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool StatusChangeNotification_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

uint32_t StatusChangeNotification_t::BinaryEncodingId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0;
  return OpcUaId_StatusChangeNotification_Encoding_DefaultBinary;
}

Status_t StatusChangeNotification_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t StatusChangeNotification_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

const StatusCode_t& StatusChangeNotification_t::StatusCode(void) const
{
  return statusCode;
}

StatusCode_t& StatusChangeNotification_t::StatusCode(void)
{
  return statusCode;
}

const DiagnosticInfo_t& StatusChangeNotification_t::DiagnosticInfo(void) const
{
  return diagnosticInfo;
}

DiagnosticInfo_t& StatusChangeNotification_t::DiagnosticInfo(void)
{
  return diagnosticInfo;
}

} // namespace uasdk

#endif //UASDK_INCLUDE_SUBSCRIPTIONS
