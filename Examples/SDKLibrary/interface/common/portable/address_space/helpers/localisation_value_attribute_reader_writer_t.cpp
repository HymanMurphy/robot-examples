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

#include "localisation_value_attribute_reader_writer_t.h"

#if (UASDK_USE_HELPERS > 0)

#include "auto_lock_t.h"

#include "utilities.h"
#include "opcua_data_value_t.h"
#include "opcua_diagnostic_info_t.h"
#include "opcua_duration_t.h"
#include "opcua_array_ua_t.h"
#include "opcua_enum_value_type_t.h"

#include "opcua_byte_t.h"
#include "opcua_sbyte_t.h"
#include "opcua_int16_t.h"
#include "opcua_uint64_t.h"

#include "ivariable_node_t.h"

namespace uasdk
{
/*
 * private functions
 */
Status_t LocalisationValueAttributeReaderWriter_t::ReadValue(bool setSourceTimestamp, const ArrayUA_t<String_t>& locales, IntrusivePtr_t<DataValue_t>& dataValue)
{
  AutoLock_t lk(lock);
  if (!localizableTextStored.is_set())
  {
    return OpcUa_BadInvalidArgument;
  }

  Status_t status;
  IntrusivePtr_t<const LocalizedText_t> value = localizableTextStored->GetLocalizedText(locales, status);
  if (!value.is_set() || status.IsBad())
  {
    return status;
  }

  dataValue.reset(new SafeRefCount_t<DataValue_t>());
  if (!dataValue.is_set())
  {
    return OpcUa_BadOutOfMemory;
  }
  if(setSourceTimestamp)
  {
    IntrusivePtr_t<DateTime_t> dateTime(new SafeRefCount_t<DateTime_t>());
    if(!dateTime.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }
    dateTime->Value(UASDK_datetime());
    dataValue->SourceTimestamp() = dateTime;
  }

  return value->CopyTo(dataValue->Value());
}

Status_t LocalisationValueAttributeReaderWriter_t::WriteValue(IntrusivePtr_t<const DataValue_t> dataValue)
{
  if (!localizableTextStored.is_set())
  {
    return OpcUa_BadInvalidArgument;
  }

  if (!dataValue.is_set())
  {
    return OpcUa_BadInvalidArgument;
  }

  Status_t status;
  {
    AutoLock_t lk(lock);
    if (dataValue->Value().is_set())
    {
      IntrusivePtr_t<LocalizedText_t> value = new SafeRefCount_t<LocalizedText_t>();
      if (!value.is_set())
      {
        return OpcUa_BadOutOfMemory;
      }

      status = value->CopyFrom(*dataValue->Value());
      if (status.IsBad())
      {
        return status;
      }

      status = localizableTextStored->AddText(value);
    }
  }

  return status;
}

/*
 * public functions
 */
LocalisationValueAttributeReaderWriter_t::~LocalisationValueAttributeReaderWriter_t()
{}

Status_t LocalisationValueAttributeReaderWriter_t::Initialize(IntrusivePtr_t<LocalizedText_t> localizedText)
{
  if (!localizedText.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  if(!localizableTextStored.is_set())
  {
    localizableTextStored = new SafeRefCount_t<LocalizableTextStored_t>();
    if (!localizableTextStored.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    } 
  }
  
  Status_t status = localizableTextStored->AddText(localizedText);
  if(status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
  
  return lock.Initialise();
}

Status_t LocalisationValueAttributeReaderWriter_t::AddText(IntrusivePtr_t<LocalizedText_t> localizedText)
{
  if (!localizedText.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  return localizableTextStored->AddText(localizedText);
}

bool LocalisationValueAttributeReaderWriter_t::CanReadValueSynchronously(const IVariableNode_t& node)
{
  UASDK_UNUSED(node);
  return true;
}

Status_t LocalisationValueAttributeReaderWriter_t::ReadValueAttributeBegin(
  IntrusivePtr_t<const IVariableNode_t>& node,
  uint32_t maxAge,
  bool setSourceTimestamp,
  IntrusivePtr_t<const ArrayUA_t<String_t> >& locales,
  IntrusivePtr_t<const ArrayRef_t<IndexRange_t> >& indexRange,
  uint32_t transactionId,
  uint32_t timeoutHint,
  IntrusivePtr_t<ICallbackNodeValueAttributeAccessCompleted_t>& completedCallback)
{
  UASDK_UNUSED(node);
  UASDK_UNUSED(maxAge);
  UASDK_UNUSED(setSourceTimestamp);
  UASDK_UNUSED(locales);
  UASDK_UNUSED(indexRange);
  UASDK_UNUSED(transactionId);
  UASDK_UNUSED(timeoutHint);
  UASDK_UNUSED(completedCallback);
  UASDK_RETURN_BAD_STATUS(OpcUa_BadNotWritable);
}

Status_t LocalisationValueAttributeReaderWriter_t::ReadValueAttribute(
  const IVariableNode_t& node,
  uint32_t maxAge,
  bool setSourceTimestamp,
  const ArrayUA_t<String_t>& locales,
  const Array_t<IndexRange_t>& indexRange,
  uint32_t transactionId,
  uint32_t timeoutHint,
  IntrusivePtr_t<DataValue_t>& dataValue,
  IntrusivePtr_t<DiagnosticInfo_t>& diagnosticInfo)
{
  UASDK_UNUSED(node);
  UASDK_UNUSED(maxAge);
  UASDK_UNUSED(indexRange);
  UASDK_UNUSED(transactionId);
  UASDK_UNUSED(timeoutHint);
  UASDK_UNUSED(diagnosticInfo);
  return ReadValue(setSourceTimestamp, locales, dataValue);
}

bool LocalisationValueAttributeReaderWriter_t::CanWriteValueSynchronously(const IVariableNode_t& node)
{
  UASDK_UNUSED(node);
  return true;
}

Status_t LocalisationValueAttributeReaderWriter_t::WriteValueAttributeBegin(IntrusivePtr_t<IVariableNode_t>& node,
                                                                            IntrusivePtr_t<const ArrayRef_t<IndexRange_t> > indexRange,
                                                                            IntrusivePtr_t<const DataValue_t> dataValue,
                                                                            uint32_t transactionId,
                                                                            uint32_t timeoutHint,
                                                                            IntrusivePtr_t<ICallbackNodeValueAttributeAccessCompleted_t>& completedCallback)
{
  UASDK_UNUSED(node);
  UASDK_UNUSED(indexRange);
  UASDK_UNUSED(dataValue);
  UASDK_UNUSED(transactionId);
  UASDK_UNUSED(timeoutHint);
  UASDK_UNUSED(completedCallback);

  UASDK_RETURN_BAD_STATUS(OpcUa_BadNotWritable);
}

Status_t LocalisationValueAttributeReaderWriter_t::WriteValueAttribute(IVariableNode_t& node,
                                                                       const Array_t<IndexRange_t>& indexRange,
                                                                       IntrusivePtr_t<const DataValue_t> dataValue,
                                                                       uint32_t transactionId,
                                                                       uint32_t timeoutHint,
                                                                       IntrusivePtr_t<DiagnosticInfo_t>& diagnosticInfo)
{
  UASDK_UNUSED(node);
  UASDK_UNUSED(indexRange);
  UASDK_UNUSED(dataValue);
  UASDK_UNUSED(transactionId);
  UASDK_UNUSED(timeoutHint);
  UASDK_UNUSED(diagnosticInfo);

  return WriteValue(dataValue);
}

} //namespace uasdk

#endif //(UASDK_USE_HELPERS > 0)
