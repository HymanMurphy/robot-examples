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

#include "opcua_guid_t.h"
#include "opcua_datatype_utilities_t.h"
#include "icodec_t.h"
#include "opcua_string_t.h"

#if (UASDK_INCLUDE_SECURITY > 0)
#include "ua_security.h"
#else
#include "ua_system_calls.h"
#endif

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(Guid_t, BaseDataType_t)

Guid_t::Guid_t()
{
  for (int i = 0; i < GUID_LENGTH; i++)
  {
    data[i] = 0;
  }
}

Guid_t::Guid_t( const uint8_t* data_ )
{
  for (int i = 0; i < GUID_LENGTH; i++)
  {
    this->data[i] = 0;
  }

  if (data_ != 0)
  {
    CopyFrom(data_);
  }
}

void Guid_t::SetVersion4Guid(void)
{
  uint8_t temp = data[6];
  data[6] = ((temp & 0x0F) | 0x40);

  temp = data[8];
  data[8] = ((temp & 0x3F) | 0x80);
}

void Guid_t::Swap(uint8_t pos1, uint8_t pos2)
{
  if (pos1 >= GUID_LENGTH || pos2 >= GUID_LENGTH)
  {
    return;
  }

  uint8_t temp = data[pos1];
  data[pos1] = data[pos2];
  data[pos2] = temp;
}

void Guid_t::Reverse(uint8_t dataField)
{
  switch (dataField)
  {
    case GUID_DATA_1:
      Swap(0, 3);
      Swap(1, 2);
      break;

    case GUID_DATA_2:
      Swap(4, 5);
      break;

    case GUID_DATA_3:
      Swap(6, 7);
      break;

    default:
      return;
  }
}

void Guid_t::ConvertToAscii(uint8_t& value) const
{
  if (value < 0x0A)
  {
    value += 0x30;
  }
  else
  {
    value = (value - 0x0A) + 0x41;
  }
}

void Guid_t::ConvertGuidToString(uint8_t dataField, uint8_t position, uint8_t* result) const
{
  uint8_t startIndex;
  uint8_t endIndex;
  switch (dataField)
  {
    case GUID_DATA_1:
      startIndex = 0;
      endIndex = 3;
      break;

    case GUID_DATA_2:
      startIndex = 4;
      endIndex = 5;
      break;

    case GUID_DATA_3:
      startIndex = 6;
      endIndex = 7;
      break;

    case GUID_DATA_4_PART_1:
      startIndex = 8;
      endIndex = 9;
      break;

    case GUID_DATA_4_PART_2:
      startIndex = 10;
      endIndex = 15;
      break;

    default:
      return;
  }

  if (result && (endIndex < GUID_LENGTH))
  {
    for (uint8_t i = startIndex, j = position; i <= endIndex; i++, j++)
    {
      uint8_t indexData = data[i];

      result[j] = (indexData & 0xF0) >> 4;
      ConvertToAscii(result[j]);

      j++;

      result[j] = indexData & 0x0F;
      ConvertToAscii(result[j]);
    }
  }
}

Status_t Guid_t::Initialise(void)
{
  Status_t status;
#if (UASDK_INCLUDE_SECURITY > 0)
  UA_Byte_string_t buf;
  buf.length = 0;
  buf.max_length = GUID_LENGTH;
  buf.data = data;

  status = UASecurity_rand_pseudo_bytes(&buf);
  if(status.IsBad())
  {
    return status;
  }
#else
  uint32_t* temp = (uint32_t*) data;
  for(uint8_t i = 0; i < (GUID_LENGTH / 4); i++)
  {
    temp[i] = UASDK_pseudeo_random_number();
  }
#endif

  SetVersion4Guid();

  return status;
}

Status_t Guid_t::CopyFrom(const BaseDataType_t& source)
{
  const Guid_t* ptr = RuntimeCast<const Guid_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t Guid_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  return encoder.Encode(*this, buffer);
}

Status_t Guid_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, Guid_t& result)
{
  return decoder.Decode(buffer, result);
}

Guid_t::~Guid_t() 
{}

bool Guid_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool Guid_t::operator==(Guid_t const & obj) const
{
  return (UASDK_memcmp(data, obj.data, GUID_LENGTH) == 0);
}

bool Guid_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

bool Guid_t::operator>(Guid_t const & obj) const
{
  return (UASDK_memcmp(data, obj.data, GUID_LENGTH) > 0);
}

Status_t Guid_t::CopyTo(uint8_t* destination) const
{
  UASDK_memcpy(destination, data, GUID_LENGTH);

  return OpcUa_Good;
}

Status_t Guid_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

Status_t Guid_t::CopyFrom(const uint8_t* source)
{
  UASDK_memcpy(data, source, GUID_LENGTH);

  return OpcUa_Good;
}

Status_t Guid_t::CopyFrom(const Guid_t& source)
{
  return CopyFrom(source.Value());
}

uint32_t Guid_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

const uint8_t* Guid_t::Value(void) const
{
  return data;
}

uint8_t* Guid_t::Value(void)
{
  return data;
}

bool Guid_t::IsNull(void) const
{
  uint8_t temp[GUID_LENGTH];
  UASDK_memset(temp, '\0', GUID_LENGTH);
  return (UASDK_memcmp(data, temp, GUID_LENGTH) == 0);
}

Status_t Guid_t::ToString(ScopedPtr_t< Array_t<uint8_t> >& value) const
{
  /*
  * As an example, GUID “72962B91-FA75-4AE6-8D28-B404DC7DAF63” should be
  * encoded as follows:
  *
  *    Data1      Data2   Data3           Data4
  * 91 2B 96 72   75 FA   E6 4A   8D 28 B4 04 DC 7D AF 63
  *
  *  0  1  2  3    4  5    6  7    8  9 10 11 12 13 14 15
  */

  Guid_t guid;
  Status_t status = guid.CopyFrom(*this);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
  guid.Reverse(GUID_DATA_1);
  guid.Reverse(GUID_DATA_2);
  guid.Reverse(GUID_DATA_3);

  value.reset(new SafeRefCount_t< Array_t<uint8_t> >());
  if (!value.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  status = value->Initialise(GUID_LENGTH_IN_STRING + 1); //1 NULL terminate
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
  UASDK_memset(value->Value(), '-', GUID_LENGTH_IN_STRING);
  value->Value()[GUID_LENGTH_IN_STRING] = '\0';

  uint8_t* data_ = value->Value();
  if (!data_)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  guid.ConvertGuidToString(GUID_DATA_1,         0, data_);
  guid.ConvertGuidToString(GUID_DATA_2,         (GUID_DATA_1_SIZE + 1), data_);
  guid.ConvertGuidToString(GUID_DATA_3,         (GUID_DATA_1_SIZE + 1 + GUID_DATA_2_SIZE + 1), data_);
  guid.ConvertGuidToString(GUID_DATA_4_PART_1,  (GUID_DATA_1_SIZE + 1 + GUID_DATA_2_SIZE + 1 + GUID_DATA_3_SIZE + 1), data_);
  guid.ConvertGuidToString(GUID_DATA_4_PART_2,  (GUID_DATA_1_SIZE + 1 + GUID_DATA_2_SIZE + 1 + GUID_DATA_3_SIZE + 1 + GUID_DATA_4_PART_1_SIZE + 1), data_);

  return OpcUa_Good;
}

} // namespace uasdk
