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

#include "opcua_string_t.h"
#include "scoped_ptr_t.h"
#include "array_t.h"
#include "opcua_datatype_utilities_t.h"
#include "icodec_t.h"
#include "utilities.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(String_t, BaseDataType_t)

Status_t String_t::CopyFrom(const BaseDataType_t& source)
{
  const String_t* ptr = RuntimeCast<const String_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t String_t::CopyFrom(const String_t& source)
{
  return byteString.CopyFrom(source.byteString);
}

Status_t String_t::CopyFrom(const char* source)
{
  uint32_t DEFAULT_MAX_STRING_LENGTH = 4096;
  return CopyFrom(source, DEFAULT_MAX_STRING_LENGTH);
}

Status_t String_t::CopyFrom(const char* source, uint32_t maxLen)
{
  if (source == 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  int32_t length = Utilities_t::Strnlen(source, maxLen);
  if (length == static_cast<int32_t>(maxLen))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }
  return byteString.CopyFrom(reinterpret_cast<const uint8_t*>(source), length);
}

Status_t String_t::WriteSubsetTo(const Array_t<IndexRange_t>& indexRange, IntrusivePtr_t<BaseDataType_t>& destination) const
{
  IntrusivePtr_t<BaseDataType_t> tempByteString ;

  Status_t status = byteString.WriteSubsetTo(indexRange, tempByteString);
  if(status.IsBad() || (!tempByteString.is_set()))
  {
    return status;
  }

  IntrusivePtr_t<String_t> tempString (new SafeRefCount_t<String_t>());
  if(!tempString.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  status = tempString->Payload().CopyFrom(*tempByteString);
  if(status.IsBad())
  {
    return status;
  }

  destination = tempString;

  return status;
}

Status_t String_t::WriteSubsetFrom(const Array_t<IndexRange_t>& indexRange, const BaseDataType_t& source)
{
  const String_t* ptr = RuntimeCast<const String_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return byteString.WriteSubsetFrom(indexRange, ptr->Payload());
}

Status_t String_t::ToString(ScopedPtr_t< Array_t<char> >& result) const
{
  int32_t length = byteString.Length() + 1;

  result.reset(new Array_t<char>());

  if(!result.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  if (length > 0)
  {
    Status_t status = result->Initialise((uint32_t)length);
    if (status.IsBad())
    {
      return status;
    }
    UASDK_memcpy(result->Value(), byteString.Data(), byteString.Length());
    result->Value()[length - 1] = '\0';
  }

  return OpcUa_Good;

}

Status_t String_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  return encoder.Encode(*this, buffer);
}

Status_t String_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, String_t& result)
{
  return decoder.Decode(buffer, result);
}

String_t::String_t() 
{}

String_t::~String_t()
{}

bool String_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool String_t::operator==(String_t const & obj) const
{
  return (byteString == obj.byteString);
}

bool String_t::operator!=(String_t const & obj) const
{
  return !(*this == obj);
}

bool String_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

bool String_t::operator>(String_t const & obj) const
{
  return (byteString > obj.byteString);
}

Status_t String_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const 
{
  return CopyToDestination(*this, destination); 
}

uint32_t String_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

int32_t String_t::Length(void) const
{
  return byteString.Length();
}

const ByteString_t& String_t::Payload(void) const
{
  return byteString;
}

ByteString_t& String_t::Payload(void)
{
  return byteString;
}

bool String_t::IsNull(void) const
{
  return (byteString.Length() == -1);
}

UA_UTF8_string_t String_t::ToLegacy(void) const
{
  UA_UTF8_string_t result = { Length(), Payload().Data() };
  return result;
}

Status_t UninitialisedCopy(String_t &destination, String_t const &source)
{
  PlacementNew_t pnx(static_cast<void*>(&destination));
  new(pnx) String_t();
  return destination.CopyFrom(source);
}

} // namespace uasdk
