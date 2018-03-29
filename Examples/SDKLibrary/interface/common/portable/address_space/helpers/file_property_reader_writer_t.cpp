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

#include "file_property_reader_writer_t.h"

#if ((UASDK_USE_HELPERS > 0) && (UASDK_USE_FILE_OBJECT_HELPERS > 0))

#include "ivariable_node_t.h"
#include "opcua_uint64_t.h"
#include "auto_lock_t.h"

namespace uasdk
{
Status_t FilePropertyReaderWriter_t::ReadValue(const IVariableNode_t& node, bool setSourceTimestamp, IntrusivePtr_t<DataValue_t>& dataValue)
{
  if (!node.NodeId().is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  IntrusivePtr_t<BaseDataType_t> value;
  if ( sizeNodeId.is_set() && (*sizeNodeId == *(node.NodeId()) ) )
  {
    uint64_t size = fileUAObject->Size();
    IntrusivePtr_t<UInt64_t> temp(new SafeRefCount_t<UInt64_t>());
    if (!temp.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }

    temp->Value(size);
    value = temp;
  }
  else if (openCountNodeId.is_set() && (*openCountNodeId == *(node.NodeId()) ) )
  {
    uint16_t openCount = fileUAObject->OpenCount();
    IntrusivePtr_t<UInt64_t> temp(new SafeRefCount_t<UInt64_t>());
    if (!temp.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }

    temp->Value(openCount);
    value = temp;
  }
  else
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadNodeIdUnknown);
  }

  AutoLock_t lk(lock);
  dataValue.reset(new SafeRefCount_t<DataValue_t>());
  if (!dataValue.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  
  dataValue->Value() = value;

  if (setSourceTimestamp)
  {
    IntrusivePtr_t<DateTime_t> dateTime(new SafeRefCount_t<DateTime_t>());
    if (!dateTime.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }
    dateTime->Value(UASDK_datetime());
    dataValue->SourceTimestamp() = dateTime;
  }

  IntrusivePtr_t<StatusCode_t> statusCode_ = new SafeRefCount_t<StatusCode_t>();
  if (!statusCode_.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  statusCode_->Value().Value(OpcUa_Good);
  dataValue->StatusCode() = statusCode_;

  return OpcUa_Good;
}

FilePropertyReaderWriter_t::~FilePropertyReaderWriter_t()
{
}

Status_t FilePropertyReaderWriter_t::Initialize(IntrusivePtr_t<IFileUA_t> fileUAObject_)
{
  fileUAObject = fileUAObject_;

  return lock.Initialise();
}

void FilePropertyReaderWriter_t::AddSizeNodeId(IntrusivePtr_t<const NodeId_t> sizeNodeId_)
{
  sizeNodeId = sizeNodeId_;
}

void FilePropertyReaderWriter_t::AddOpenCountNodeId(IntrusivePtr_t<const NodeId_t> openCountNodeId_)
{
  openCountNodeId = openCountNodeId_;
}

bool FilePropertyReaderWriter_t::CanReadValueSynchronously(const IVariableNode_t& node_)
{
  UASDK_UNUSED(node_);
  return true;
}

Status_t FilePropertyReaderWriter_t::ReadValueAttributeBegin(
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

  return OpcUa_BadNotReadable;
}

Status_t FilePropertyReaderWriter_t::ReadValueAttribute(
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
  UASDK_UNUSED(setSourceTimestamp);
  UASDK_UNUSED(locales);
  UASDK_UNUSED(indexRange);
  UASDK_UNUSED(transactionId);
  UASDK_UNUSED(timeoutHint);
  UASDK_UNUSED(diagnosticInfo);
  return ReadValue(node, setSourceTimestamp, dataValue);
}

/*****************************************************************************/
/** Availability of write value attribute object synchronously or not
*
* @return
* TRUE if object can be accessed synchronously. FALSE Otherwise
*/

bool FilePropertyReaderWriter_t::CanWriteValueSynchronously(const IVariableNode_t& node_)
{
  UASDK_UNUSED(node_);
  return true;
}

Status_t FilePropertyReaderWriter_t::WriteValueAttributeBegin(
  IntrusivePtr_t<IVariableNode_t>& node,
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

  return OpcUa_BadNotWritable;
}

Status_t FilePropertyReaderWriter_t::WriteValueAttribute(
  IVariableNode_t& node,
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
  return OpcUa_BadNotWritable;
}

}

#endif  //( (UASDK_USE_HELPERS > 0) && (UASDK_USE_FILE_OBJECT_HELPERS > 0))