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

#include "opcua_localized_text_t.h"
#include "opcua_datatype_utilities_t.h"
#include "icodec_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(LocalizedText_t, BaseDataType_t)
  
bool LocalizedText_t::operator==(LocalizedText_t const & obj) const
{
  return (
      (locale == obj.locale)
      && (text == obj.text));
}

bool LocalizedText_t::operator>(LocalizedText_t const & obj) const
{
  return (
      (locale > obj.locale)
      && (text > obj.text));
}

Status_t LocalizedText_t::CopyFrom(const LocalizedText_t& source)
{
  Status_t status = locale.CopyFrom(source.locale);

  if (status.IsBad())
  {
    return status;
  }

  status = text.CopyFrom(source.text);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

Status_t LocalizedText_t::CopyFrom(const BaseDataType_t& source)
{
  const LocalizedText_t* ptr = RuntimeCast<const LocalizedText_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t LocalizedText_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  return encoder.Encode(*this, buffer);
}

Status_t LocalizedText_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, LocalizedText_t& result)
{
  return decoder.Decode(buffer, result);
}

LocalizedText_t::LocalizedText_t()
{}

LocalizedText_t::~LocalizedText_t()
{}

bool LocalizedText_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool LocalizedText_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t LocalizedText_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t LocalizedText_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

const String_t& LocalizedText_t::Locale(void) const
{
  return locale;
}

String_t& LocalizedText_t::Locale(void)
{
  return locale;
}

const String_t& LocalizedText_t::Text(void) const
{
  return text;
}

String_t& LocalizedText_t::Text(void)
{
  return text;
}

} // namespace uasdk
