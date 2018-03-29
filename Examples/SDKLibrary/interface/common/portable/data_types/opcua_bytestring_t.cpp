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

#include "opcua_bytestring_t.h"
#include "opcua_int32_t.h"
#include "opcua_array_ua_t.h"
#include "opcua_byte_t.h"
#include "icodec_t.h"
#include "utilities.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(ByteString_t, BaseDataType_t)

ByteString_t::ByteString_t()
{
}

bool ByteString_t::operator==(ByteString_t const & obj) const
{
  if( (Data()) && (obj.Data()) )
  {
    return ( (Length() == obj.Length()) && !UASDK_memcmp(Data(), obj.Data(), Length()) );
  }

  else if( !Data() && !obj.Data() )
  {
    return true;
  }

  return false;
}

bool ByteString_t::operator>(ByteString_t const & rhs) const
{
  int32_t lhs_length = (Data() ? Length() : 0);
  lhs_length = (lhs_length >= 0 ? lhs_length : 0);

  int32_t rhs_length = (rhs.Data() ? rhs.Length() : 0);
  rhs_length = (rhs_length >= 0) ? rhs_length : 0;

  int32_t min_length = (lhs_length < rhs_length) ? lhs_length : rhs_length;

  if (min_length > 0)
  {
    int comp = UASDK_memcmp(Data(), rhs.Data(), min_length);
    if (comp == 0)
    {
      // Break a tie with length
      return lhs_length > rhs_length;
    }
    else
    {
      return comp > 0;
    }
  }
  else
  {
    // The longer one is greater.
    return lhs_length > rhs_length;
  }
}

Status_t ByteString_t::CopyFrom(const ByteString_t& source)
{
  return CopyFrom(source.Data(), source.Length());
}

Status_t ByteString_t::CopyFrom(const uint8_t* source, int32_t length)
{
  Status_t status = data.Initialise(length);
  if (status.IsBad())
  {
    return status;
  }
  if (length > 0)
  {
    UASDK_memcpy(data.Value(), source, length);
  }
  return OpcUa_Good;
}

Status_t ByteString_t::CopyFromByteArray(const BaseDataType_t& source)
{
  const ArrayUA_t<Byte_t>* ptr = RuntimeCast<const ArrayUA_t<Byte_t> * >(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  uint32_t length = ptr->Count();
  Status_t status = data.Initialise(length);
  if (status.IsBad())
  {
    return status;
  }
  for(uint32_t i = 0; i < length; i++)
  {
    data[i] = (*ptr)[i]->Value();
  }

  return OpcUa_Good;
}

Status_t ByteString_t::CopyFromByteArray(const BaseDataType_t& source, uint32_t start, uint32_t end)
{
  const ArrayUA_t<Byte_t>* ptr = RuntimeCast< const ArrayUA_t<Byte_t> * >(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  uint32_t length = ptr->Count();
  if(length < (end - start + 1))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadIndexRangeNoData);
  }

  for(uint32_t i = start; i <= end; i++)
  {
    data[i] = (*ptr)[i - start]->Value();
  }
  return OpcUa_Good;
}

Status_t ByteString_t::CopyFrom(const BaseDataType_t& source)
{
  const ByteString_t* ptr = RuntimeCast<const ByteString_t *>(source);
  if(!ptr)
  {
    uint16_t namespaceIndex = 0;
    if(OpcUaId_Byte == source.TypeId(namespaceIndex))
    {
      return CopyFromByteArray(source);
    }
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t ByteString_t::WriteSubsetTo(const Array_t<IndexRange_t>& indexRange, IntrusivePtr_t<BaseDataType_t>& destination) const
{
  if (indexRange.Size() == 0)
  {
    return CopyTo(destination);
  }

  if(indexRange.Size() > 1)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadIndexRangeInvalid);
  }

  uint32_t start = indexRange[0].start;
  uint32_t end = indexRange[0].end;

  if(start > end)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadIndexRangeInvalid);
  }

  int32_t Len = Length();
  if(start >= (uint32_t)Len)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadIndexRangeNoData);
  }

  if(end >= (uint32_t)Len)
  {
    end = Len - 1;
  }

  IntrusivePtr_t<ByteString_t> ptr(new SafeRefCount_t<ByteString_t>());
  if (!ptr.is_set())
  {
   UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  Status_t status = ptr->Initialise( end - start + 1);
  if(status.IsBad())
  {
    return status;
  }

  UASDK_memcpy( ptr->Data(), &(data[start]), (end - start) + 1);

  destination = ptr;

  return status;
}

Status_t ByteString_t::WriteSubsetFrom(const Array_t<IndexRange_t>& indexRange, const BaseDataType_t& source)
{
  if (indexRange.Size() == 0)
  {
    return CopyFrom(source);
  }

  if(indexRange.Size() > 1)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadIndexRangeInvalid);
  }

  uint32_t start = indexRange[0].start;
  uint32_t end = indexRange[0].end;

  if(start > end)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadIndexRangeInvalid);
  }

  int32_t Len = Length();
  if(start >= (uint32_t)Len)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadIndexRangeNoData);
  }

  if(end >= (uint32_t)Len)
  {
    end = Len - 1;
  }

  const ByteString_t* ptr = RuntimeCast<const ByteString_t *>(source);
  if(!ptr)
  {
    uint16_t namespaceIndex = 0;
    if(OpcUaId_Byte == source.TypeId(namespaceIndex))
    {
      return CopyFromByteArray(source, start, end);
    }
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  if(ptr->Length() < (int32_t)( (end - start) + 1))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadIndexRangeNoData);
  }

  UASDK_memcpy(&(data[start]), ptr->Data(), (end - start) + 1);

  return OpcUa_Good;
}

Status_t ByteString_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  return encoder.Encode(*this, buffer);
}

Status_t ByteString_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, ByteString_t& result)
{
  return decoder.Decode(buffer, result);
}

ByteString_t::~ByteString_t()
{}

Status_t ByteString_t::Initialise(int32_t length)
{
  if (length < 0)
  {
    length = 0;
  }
  return data.Initialise(length);
}

bool ByteString_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool ByteString_t::operator!=(ByteString_t const & obj) const
{
  return !(*this == obj);
}

bool ByteString_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t ByteString_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination); 
}

uint32_t ByteString_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

int32_t ByteString_t::Length(void) const
{
  if (data.Initialised())
  {
    return data.Size();
  }
  else
  {
    return -1;
  }
}

const uint8_t* ByteString_t::Data(void) const
{
  if (data.Initialised())
  {
    return data.Value();
  }
  return 0;
}

uint8_t* ByteString_t::Data(void)
{
  if (data.Initialised())
  {
    return data.Value();
  }
  return 0;
}

bool ByteString_t::IsNull(void) const
{
  return (Length() == -1);
}

const UA_Byte_string_t ByteString_t::ToLegacy(void) const
{
  UA_Byte_string_t result = { Length(), Length(), const_cast<uint8_t*>(Data()) };
  return result;
}

UA_Byte_string_t ByteString_t::ToLegacy(void)
{
  UA_Byte_string_t result = { Length(), Length(), Data() };
  return result;
}

} // namespace uasdk
