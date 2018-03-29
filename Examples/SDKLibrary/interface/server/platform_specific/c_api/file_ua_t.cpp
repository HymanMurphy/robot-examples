/* ----------------------------------------------------------------------------------------
                                        COPYRIGHT (c) 2009 - 2017
                                         HONEYWELL INC.,
                                        ALL RIGHTS RESERVED

            This software is a copyrighted work and/or information protected as a trade
            secret. Legal rights of Honeywell Inc. in this software are distinct from
            ownership of any medium in which the software is embodied. Copyright or trade
            secret notices included must be reproduced in any copies authorized by
            Honeywell Inc. The information in this software is subject to change without
            notice and should not be considered as a commitment by Honeywell Inc.
---------------------------------------------------------------------------------------- */

#include "file_ua_t.h"

#if (UASDK_INCLUDE_SERVER)
#if (UASDK_INCLUDE_SERVER_C_API > 0) && (UA_INCLUDE_FILE_TRANSFER_METHODS > 0)

#include "iaddress_space_t.h"
#include "opcua_byte_t.h"
#include "opcua_uint64_t.h"
#include "file_transfer_router.h"
#include "ua_server.h"

namespace uasdk
{

bool FileUA_t::IsSessionIdAndFileHandleValid(IntrusivePtr_t<const NodeId_t> sessionId, uint32_t fileHandle)
{
  uint32_t count = handles.Count();
  if (count == 0)
  {
    return false;
  }
  for (; count > 0; count--)
  {
    IntrusivePtr_t<Handle_t> id = handles.GetAtIndex(count - 1);
    if (!id.is_set())
    {
      return false;
    }
    if (*id->sessionId == *sessionId)
    {
      if (fileHandle == id->fileHandle)
      {
        return true;
      }
    }
  }
  return false;
}

Status_t FileUA_t::RemoveHandle(IntrusivePtr_t<const NodeId_t> sessionId, uint32_t fileHandle)
{
  uint32_t count = handles.Count();
  if (count == 0)
  {
    return OpcUa_BadInternalError;
  }
  for (; count > 0; count--)
  {
    IntrusivePtr_t<Handle_t> id = handles.GetAtIndex(count - 1);
    if (!id.is_set())
    {
      continue;
    }
    if (*id->sessionId == *sessionId)
    {
      if (id->fileHandle == fileHandle)
      {
        handles.DeleteCurrent();
        if (isOpenForWriting)
        {
          isOpenForWriting = false;
        }
        return OpcUa_Good;
      }
    }
  }
  return OpcUa_BadInternalError;
}

uintptr_t FileUA_t::NodeHandle(void)
{ 
  return nodeHandle; 
}

void FileUA_t::SessionCreated(IntrusivePtr_t<const NodeId_t>& sessionId)
{
  // Nothing to implement
  UASDK_UNUSED(sessionId);
}

void FileUA_t::SessionActivated(IntrusivePtr_t<const NodeId_t>& sessionId)
{
  // Nothing to implement
  UASDK_UNUSED(sessionId);
}

void FileUA_t::SessionClosed(IntrusivePtr_t<const NodeId_t>& sessionId)
{
  uint32_t count = handles.Count();
  if (count == 0)
  {
    return;
  }
  for (; count > 0; count--)
  {
    IntrusivePtr_t<Handle_t> id = handles.GetAtIndex(count - 1);
    if (!id.is_set())
    {
      continue;
    }
    if (*id->sessionId == *sessionId)
    {
      isOpenForWriting = false;
      handles.DeleteCurrent();
    }
  }
}

Status_t FileUA_t::Initialise(IntrusivePtr_t<const NodeId_t> fileObjectId_, IntrusivePtr_t<IServerConfiguration_t> sharedData_, IntrusivePtr_t<FileTransferRouter_t>& fileTransferRouter_)
{
  Status_t status;
  if ((!sharedData_.is_set()) || (!fileTransferRouter_.is_set()) || (!fileObjectId_.is_set()))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  IntrusivePtr_t<IAddressSpace_t> addressSpace = sharedData_->AddressSpace();
  if (!addressSpace.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }
  IntrusivePtr_t<IObjectNode_t> obj = addressSpace->FindObjectNode(*fileObjectId_, status);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
  IntrusivePtr_t<const NodeId_t> aliasId_ = obj->Alias();
  if (!aliasId_.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }
  const UInt32_t* tempAlias = DataTypeUtilities_t::DataTypeDownCast<UInt32_t>(aliasId_->IdentiferBase());
  if (!tempAlias)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  nodeHandle = tempAlias->Value();
  fileObjectId = fileObjectId_;
  status = fileTransferRouter_->AddFile(*this);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  status = sharedData_->AddSessionListener(this);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  return OpcUa_Good;
}

IntrusivePtr_t<const NodeId_t> FileUA_t::FileObjectId(void)
{
  return fileObjectId; 
}

uint16_t FileUA_t::OpenCount(void)
{ 
  return (uint16_t)(handles.Count()); 
}

uint64_t FileUA_t::Size(void)
{
  Status_t status;
  FileSizeContext_t context;

  UAServer_Callback_File_Size( nodeHandle, (uintptr_t) (&context));

  if (context.result != OpcUa_Good)
  {
    LOG_BAD_STATUS(context.result);
    return context.size;
  }

  return context.size;
}

//Part 5 Method calls 
Status_t FileUA_t::Open(
  IntrusivePtr_t<const NodeId_t> sessionId,
  Byte_t mode, uint32_t& fileHandle)
{
  Status_t status;
  FileOpenContext_t context;

  if (mode.Value() & 0x02)
  {
    if (OpenCount() > 0)
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadNotWritable);
    }
  }
  if (isOpenForWriting)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadNotReadable);
  }

  UAServer_Callback_File_Open((uintptr_t)nodeHandle, mode.Value(), (uintptr_t) (&context));

  if (context.result != OpcUa_Good)
  {
    UASDK_RETURN_BAD_STATUS(context.result);
  }

  IntrusivePtr_t<Handle_t> handle_(new SafeRefCount_t<Handle_t>());
  if (!handle_.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  fileHandle = handle_->fileHandle = context.file_handle;
  handle_->sessionId = sessionId;
  status = handles.AddToTail(handle_);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  if (mode.Value() & 0x02)
  {
    isOpenForWriting = true;
  }

  return status;
}

Status_t FileUA_t::Close(
  IntrusivePtr_t<const NodeId_t> sessionId,
  uint32_t fileHandle)
{
  Status_t status;
  FileGenericContext_t context;

  if (!IsSessionIdAndFileHandleValid(sessionId, fileHandle))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  UAServer_Callback_File_Close(nodeHandle, fileHandle, (uintptr_t)(&context));

  if (context.result != OpcUa_Good)
  {
    UASDK_RETURN_BAD_STATUS(context.result);
  }

  return  RemoveHandle(sessionId, fileHandle);
}

Status_t FileUA_t::Read(
  IntrusivePtr_t<const NodeId_t> sessionId,
  uint32_t fileHandle,
  uint32_t lengthToRead,
  IntrusivePtr_t<ByteString_t>& output)
{
  Status_t status;
  FileReadContext_t context;
  if (!IsSessionIdAndFileHandleValid(sessionId, fileHandle))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  UAServer_Callback_File_Read(nodeHandle, fileHandle, lengthToRead, (uintptr_t)(&context));
  if (context.result != OpcUa_Good)
  {
    UASDK_RETURN_BAD_STATUS(context.result);
  }
  IntrusivePtr_t<ByteString_t> temp(new SafeRefCount_t<ByteString_t>());
  if (!temp.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  status = temp->CopyFrom(context.data);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
  output = temp;

  return status;
}

Status_t FileUA_t::Write(
  IntrusivePtr_t<const NodeId_t> sessionId,
  uint32_t fileHandle,
  IntrusivePtr_t<ByteString_t> dataToWrite)
{
  FileGenericContext_t context;
  UA_Byte_string_t tempData = dataToWrite->ToLegacy();

  if (!IsSessionIdAndFileHandleValid(sessionId, fileHandle))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  UAServer_Callback_File_Write(nodeHandle, fileHandle, tempData, (uintptr_t)(&context));
  if (context.result != OpcUa_Good)
  {
    UASDK_RETURN_BAD_STATUS(context.result);
  }

  return OpcUa_Good;
}

Status_t FileUA_t::GetPosition(
  IntrusivePtr_t<const NodeId_t> sessionId,
  uint32_t fileHandle,
  IntrusivePtr_t<UInt64_t >& position)
{
  FileGetPositionContext_t context;
  if (!IsSessionIdAndFileHandleValid(sessionId, fileHandle))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  UAServer_Callback_File_GetPosition(nodeHandle, fileHandle, (uintptr_t)(&context));
  if (context.result != OpcUa_Good)
  {
    UASDK_RETURN_BAD_STATUS(context.result);
  }
  IntrusivePtr_t<UInt64_t > temp(new SafeRefCount_t<UInt64_t>());
  if (!temp.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  temp->Value(context.position);
  position = temp;

  return OpcUa_Good;
}

Status_t FileUA_t::SetPosition(
  IntrusivePtr_t<const NodeId_t> sessionId,
  uint32_t fileHandle,
  IntrusivePtr_t<UInt64_t> position)
{
  FileGenericContext_t context;
  if (!IsSessionIdAndFileHandleValid(sessionId, fileHandle))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  UAServer_Callback_File_SetPosition(nodeHandle, fileHandle, position->Value(), (uintptr_t)(&context));
  if (context.result != OpcUa_Good)
  {
    UASDK_RETURN_BAD_STATUS(context.result);
  }
  return OpcUa_Good;
}

}

#endif  //#ifdef 
#endif  //(UASDK_INCLUDE_SERVER)
