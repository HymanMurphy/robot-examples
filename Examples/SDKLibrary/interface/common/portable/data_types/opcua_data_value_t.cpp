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

#include "opcua_data_value_t.h"
#include "opcua_datatype_utilities_t.h"
#include "utilities.h"
#include "array_t.h"
#include "icodec_t.h"

namespace uasdk
{

UA_DEFINE_RUNTIME_TYPE(DataValue_t, BaseDataType_t)

DataValue_t::DataValue_t() : statusCode(0),
sourcePicoseconds(0), serverPicoseconds(0)
{
}

DataValue_t::~DataValue_t(void)
{
}

bool DataValue_t::operator==(DataValue_t const & obj) const
{
  return (Equal(value, obj.value)
      && Equal(statusCode, obj.statusCode)
      && Equal(sourceTimestamp, obj.sourceTimestamp)
      && Equal(serverTimestamp, obj.serverTimestamp)
      && Equal(sourcePicoseconds, obj.sourcePicoseconds)
      && Equal(serverPicoseconds, obj.serverPicoseconds));
}

bool DataValue_t::operator>(DataValue_t const & obj) const
{
  return (GreaterThan(value, obj.value)
      && GreaterThan(statusCode, obj.statusCode)
      && GreaterThan(sourceTimestamp, obj.sourceTimestamp)
      && GreaterThan(serverTimestamp, obj.serverTimestamp)
      && GreaterThan(sourcePicoseconds, obj.sourcePicoseconds)
      && GreaterThan(serverPicoseconds, obj.serverPicoseconds));
}

Status_t DataValue_t::WriteSubsetTo(const Array_t<IndexRange_t>& indexRange, IntrusivePtr_t<BaseDataType_t>& destination) const
{
  Status_t status = OpcUa_Good;

  if(indexRange.Count() == 0)
  {
    return CopyTo(destination);
  }

  IntrusivePtr_t<DataValue_t> ptr1( new SafeRefCount_t<DataValue_t>() );
  if (!ptr1.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  if (value.is_set())
  {
    IntrusivePtr_t<BaseDataType_t> tempValue ;

    if(!indexRange.IsEmpty())
    {
      status = value->WriteSubsetTo(indexRange, tempValue);
      if (status.IsBad())
      {
        return status;
      }
    }
    else
    {
      status = value->CopyTo(tempValue);
      if (status.IsBad())
      {
        return status;
      }
    }
    ptr1->Value() = tempValue;
  }

  if (statusCode.is_set())
  {
    IntrusivePtr_t<StatusCode_t> temp = new SafeRefCount_t<StatusCode_t>();
    if (!temp.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }
    status = temp->CopyFrom(*statusCode);
    if (status.IsBad())
    {
      return status;
    }
    ptr1->StatusCode() = temp;
  }

  if (sourceTimestamp.is_set())
  {
    IntrusivePtr_t<DateTime_t> temp = new SafeRefCount_t<DateTime_t>();
    if (!temp.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }
    status = temp->CopyFrom(*sourceTimestamp);
    if (status.IsBad())
    {
      return status;
    }
    ptr1->SourceTimestamp() = temp;
  }

  if(serverTimestamp.is_set())
  {
    IntrusivePtr_t<DateTime_t> temp = new SafeRefCount_t<DateTime_t>();
    if (!temp.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }
    status = temp->CopyFrom(*serverTimestamp);
    if (status.IsBad())
    {
      return status;
    }
    ptr1->ServerTimestamp() = temp;
  }

  if(sourcePicoseconds.is_set())
  {
    IntrusivePtr_t<UInt16_t> temp = new SafeRefCount_t<UInt16_t>();
    if (!temp.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }
    status = temp->CopyFrom(*sourcePicoseconds);
    if (status.IsBad())
    {
      return status;
    }
    ptr1->SourcePicoseconds() = temp;
  }

  if(serverPicoseconds.is_set())
  {
    IntrusivePtr_t<UInt16_t> temp = new SafeRefCount_t<UInt16_t>();
    if (!temp.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }
    status = temp->CopyFrom(*serverPicoseconds);
    if (status.IsBad())
    {
      return status;
    }
    ptr1->ServerPicoseconds() = temp;
  }

  destination = ptr1;

  return OpcUa_Good;
}

Status_t DataValue_t::CopyFrom(const DataValue_t& source)
{
  Status_t status;

  if (!source.value.is_set())
  {
    value.reset();
  }
  else
  {
    if(value.is_set())
    {
      IntrusivePtr_t<BaseDataType_t> temp;
      status = value->CopyTo(temp);
      if (status.IsBad()|| !temp.is_set())
      {
        return status;
      }
      status = temp->CopyFrom(*source.value);
      if (status.IsBad())
      {
        return status;
      }
      value = temp;
    }
    else
    {
      IntrusivePtr_t<BaseDataType_t> temp;
      status = source.value->CopyTo(temp);
      if (status.IsBad() || !temp.is_set())
      {
        return status;
      }
      value = temp;
    }
  }

  if (!source.statusCode.is_set())
  {
    statusCode.reset();
  }
  else
  {
    IntrusivePtr_t<StatusCode_t> temp = new SafeRefCount_t<StatusCode_t>();
    if (!temp.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }
    status = temp->CopyFrom(*source.statusCode);
    if (status.IsBad())
    {
      return status;
    }
    statusCode = temp;
  }

  if (!source.sourceTimestamp.is_set())
  {
    sourceTimestamp.reset();
  }
  else
  {
    IntrusivePtr_t<DateTime_t> temp = new SafeRefCount_t<DateTime_t>();
    if (!temp.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }
    status = temp->CopyFrom(*source.sourceTimestamp);
    if (status.IsBad())
    {
      return status;
    }
    sourceTimestamp = temp;
  }

  if (!source.serverTimestamp.is_set())
  {
    serverTimestamp.reset();
  }
  else
  {
    IntrusivePtr_t<DateTime_t> temp = new SafeRefCount_t<DateTime_t>();
    if (!temp.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }
    status = temp->CopyFrom(*source.serverTimestamp);
    if (status.IsBad())
    {
      return status;
    }
    serverTimestamp = temp;
  }

  if (!source.sourcePicoseconds.is_set())
  {
    sourcePicoseconds.reset();
  }
  else
  {
    IntrusivePtr_t<UInt16_t> temp = new SafeRefCount_t<UInt16_t>();
    if (!temp.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }
    status = temp->CopyFrom(*source.sourcePicoseconds);
    if (status.IsBad())
    {
      return status;
    }
    sourcePicoseconds = temp;
  }

  if (!source.serverPicoseconds.is_set())
  {
    serverPicoseconds.reset();
  }
  else
  {
    IntrusivePtr_t<UInt16_t> temp = new SafeRefCount_t<UInt16_t>();
    if (!temp.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }
    status = temp->CopyFrom(*source.serverPicoseconds);
    if (status.IsBad())
    {
      return status;
    }
    serverPicoseconds = temp;
  }

  return OpcUa_Good;
}

Status_t DataValue_t::CopyFrom(const BaseDataType_t& source)
{
  const DataValue_t* ptr = RuntimeCast<const DataValue_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return CopyFrom(*ptr);
}

Status_t DataValue_t::WriteSubsetFrom(const Array_t<IndexRange_t>& indexRange, const BaseDataType_t& source)
{
  const DataValue_t* ptr = RuntimeCast<const DataValue_t *>(source);
  if(!ptr)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  if (indexRange.Count() == 0)
  {
    return CopyFrom(*ptr);
  }

  Status_t status;

  if((!Value().is_set()) && ptr->Value().is_set())
  {
    return CopyFrom(*ptr);
  }

  if (!ptr->Value().is_set())
  {
    value.reset();
  }
  else
  {
    IntrusivePtr_t<BaseDataType_t> tempValue ;

    status = Value()->CopyTo(tempValue);
    if (status.IsBad())
    {
      return status;
    }

    status = tempValue->WriteSubsetFrom(indexRange, *ptr->Value());
    if (status.IsBad())
    {
      return status;
    }
    value = tempValue;
  }

  if (!ptr->StatusCode().is_set())
  {
    statusCode.reset();
  }
  else
  {
    IntrusivePtr_t<StatusCode_t> temp = new SafeRefCount_t<StatusCode_t>();
    if (!temp.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }
    status = temp->CopyFrom(*ptr->StatusCode());
    if (status.IsBad())
    {
      return status;
    }
    statusCode = temp;
  }

  if (!ptr->SourceTimestamp().is_set())
  {
    sourceTimestamp.reset();
  }
  else
  {
    IntrusivePtr_t<DateTime_t> temp = new SafeRefCount_t<DateTime_t>();
    if (!temp.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }
    status = temp->CopyFrom(*ptr->SourceTimestamp());
    if (status.IsBad())
    {
      return status;
    }
    sourceTimestamp = temp;
  }

  if (!ptr->ServerTimestamp().is_set())
  {
    serverTimestamp.reset();
  }
  else
  {
    IntrusivePtr_t<DateTime_t> temp = new SafeRefCount_t<DateTime_t>();
    if (!temp.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }
    status = temp->CopyFrom(*ptr->ServerTimestamp());
    if (status.IsBad())
    {
      return status;
    }
    serverTimestamp = temp;
  }

  if (!ptr->SourcePicoseconds().is_set())
  {
    sourcePicoseconds.reset();
  }
  else
  {
    IntrusivePtr_t<UInt16_t> temp = new SafeRefCount_t<UInt16_t>();
    if (!temp.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }
    status = temp->CopyFrom(*ptr->SourcePicoseconds());
    if (status.IsBad())
    {
      return status;
    }
    sourcePicoseconds = temp;
  }

  if (!ptr->ServerPicoseconds().is_set())
  {
    serverPicoseconds.reset();
  }
  else
  {
    IntrusivePtr_t<UInt16_t> temp = new SafeRefCount_t<UInt16_t>();
    if (!temp.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }
    status = temp->CopyFrom(*ptr->ServerPicoseconds());
    if (status.IsBad())
    {
      return status;
    }
    serverPicoseconds = temp;
  }

  return OpcUa_Good;
}

Status_t DataValue_t::Encode(ICodec_t& encoder, IBuffer_t& buffer) const
{
  return encoder.Encode(*this, buffer);
}

Status_t DataValue_t::Decode(const IBuffer_t& buffer, ICodec_t& decoder, DataValue_t& result)
{
  return decoder.Decode(buffer, result);
}

bool DataValue_t::operator==(BaseDataType_t const & obj) const
{
  return OperatorEqualTo(*this, obj);
}

bool DataValue_t::operator>(BaseDataType_t const & obj) const
{
  return OperatorGreaterThan(*this, obj);
}

Status_t DataValue_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
  return CopyToDestination(*this, destination);
}

uint32_t DataValue_t::TypeId(uint16_t& namespaceIndex) const
{
  namespaceIndex = 0; return TYPE_ID;
}

IntrusivePtr_t<const BaseDataType_t> DataValue_t::Value(void) const 
{
  return value; 
}

IntrusivePtr_t<BaseDataType_t>& DataValue_t::Value(void) 
{
  return value; 
}

IntrusivePtr_t<const StatusCode_t> DataValue_t::StatusCode(void) const 
{ 
  return statusCode; 
}

IntrusivePtr_t<StatusCode_t>& DataValue_t::StatusCode(void) 
{
  return statusCode; 
}

IntrusivePtr_t<const DateTime_t> DataValue_t::SourceTimestamp(void) const
{
  return sourceTimestamp; 
}

IntrusivePtr_t<DateTime_t>& DataValue_t::SourceTimestamp(void) 
{
  return sourceTimestamp; 
}

IntrusivePtr_t<const UInt16_t> DataValue_t::SourcePicoseconds(void) const 
{
  return sourcePicoseconds; 
}

IntrusivePtr_t<UInt16_t>& DataValue_t::SourcePicoseconds(void)
{
  return sourcePicoseconds; 
}

IntrusivePtr_t<const DateTime_t> DataValue_t::ServerTimestamp() const 
{
  return serverTimestamp; 
}

IntrusivePtr_t<DateTime_t>& DataValue_t::ServerTimestamp() 
{
  return serverTimestamp; 
}

IntrusivePtr_t<const UInt16_t> DataValue_t::ServerPicoseconds(void) const 
{
  return serverPicoseconds; 
}

IntrusivePtr_t<UInt16_t>& DataValue_t::ServerPicoseconds(void) 
{
  return serverPicoseconds; 
}

} // namespace uasdk
