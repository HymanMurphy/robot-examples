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

#include "uasdk_default_build_config.h"
#include "opcua_byte_t.h"
#include "opcua_uint64_t.h"
#include "ifile_t.h"
#include "iserver_configuration_t.h"
#include "file_transfer_router.h"
#include "iuser_permissions_t.h"
#include "opcua_call_method_request_t.h"
#include "opcua_call_method_result_t.h"
#include "inode_method_handler_t.h"
#include "imethod_node_t.h"
#include "iobject_node_t.h"
#include "opcua_datatype_utilities_t.h"
#include "intrusive_list_t.h"
#include "address_space_utilities_t.h"
#include "iaddress_space_t.h"

#if (UASDK_INCLUDE_SERVER)
#if (UASDK_INCLUDE_SERVER_C_API > 0) && (UASDK_USE_FILE_OBJECT_HELPERS > 0)

#define OPEN_METHOD_NODE_ID 11580
#define CLOSE_METHOD_NODE_ID 11583
#define READ_METHOD_NODE_ID 11585
#define WRITE_METHOD_NODE_ID 11588
#define GET_POSITION_METHOD_NODE_ID 11590
#define SET_POSITION_METHOD_NODE_ID 11593

namespace uasdk
{
Status_t FileTransferRouter_t::OpenMethodCall(IntrusivePtr_t<const NodeId_t> sessionId,
  IntrusivePtr_t<FileUA_t> file,
  IntrusivePtr_t<const CallMethodRequest_t>& requestParameters,
  IntrusivePtr_t<CallMethodResult_t>& result)
{
  IntrusivePtr_t< Byte_t > mode;
  uint32_t fileHandle = 0;

  Status_t status = AddressSpaceUtilities_t::CastInputArguments(requestParameters->InputArguments(), mode);

  if (!mode.is_set() || status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }
  status = file->Open(sessionId, *mode, fileHandle);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
  IntrusivePtr_t<UInt32_t > handle(new SafeRefCount_t<UInt32_t>());
  if (!handle.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  handle->Value(fileHandle);

  result.reset(new SafeRefCount_t<CallMethodResult_t>());
  if (!result.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  status = result->OutputArguments().Initialise(1);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
  status = handle->CopyTo((result->OutputArguments())[0]);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
  result->StatusCode() = OpcUa_Good;

  return OpcUa_Good;
}

Status_t FileTransferRouter_t::CloseMethodCall(IntrusivePtr_t<const NodeId_t> sessionId,
  IntrusivePtr_t<FileUA_t> file,
  IntrusivePtr_t<const CallMethodRequest_t>& requestParameters,
  IntrusivePtr_t<CallMethodResult_t>& result)
{
  IntrusivePtr_t< UInt32_t > fileHandle;

  Status_t status = AddressSpaceUtilities_t::CastInputArguments(requestParameters->InputArguments(), fileHandle);

  if (!fileHandle.is_set() || status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }
  status = file->Close(sessionId, fileHandle->Value());
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  result.reset(new SafeRefCount_t<CallMethodResult_t>());
  if (!result.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  result->StatusCode() = OpcUa_Good;

  return OpcUa_Good;
}

Status_t FileTransferRouter_t::ReadMethodCall(IntrusivePtr_t<const NodeId_t> sessionId,
  IntrusivePtr_t<FileUA_t> file,
  IntrusivePtr_t<const CallMethodRequest_t>& requestParameters,
  IntrusivePtr_t<CallMethodResult_t>& result)
{
  IntrusivePtr_t< UInt32_t > fileHandle;
  IntrusivePtr_t< Int32_t > lengthToRead;

  Status_t status = AddressSpaceUtilities_t::CastInputArguments(requestParameters->InputArguments(), fileHandle, lengthToRead);

  if (!fileHandle.is_set() || !lengthToRead.is_set() || status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }
  IntrusivePtr_t<ByteString_t> output;
  status = file->Read(sessionId, fileHandle->Value(), lengthToRead->Value(), output);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
 
  result.reset(new SafeRefCount_t<CallMethodResult_t>());
  if (!result.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  status = result->OutputArguments().Initialise(1);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
  status = output->CopyTo((result->OutputArguments())[0]);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
  result->StatusCode() = OpcUa_Good;

  return OpcUa_Good;
}

Status_t FileTransferRouter_t::WriteMethodCall(IntrusivePtr_t<const NodeId_t> sessionId,
  IntrusivePtr_t<FileUA_t> file,
  IntrusivePtr_t<const CallMethodRequest_t>& requestParameters,
  IntrusivePtr_t<CallMethodResult_t>& result)
{
  IntrusivePtr_t< UInt32_t > fileHandle;
  IntrusivePtr_t< ByteString_t > dataToWrite;

  Status_t status = AddressSpaceUtilities_t::CastInputArguments(requestParameters->InputArguments(), fileHandle, dataToWrite);

  if (!fileHandle.is_set() || !dataToWrite.is_set() || status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }
  IntrusivePtr_t<ByteString_t> output;
  status = file->Write(sessionId, fileHandle->Value(), dataToWrite);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  result.reset(new SafeRefCount_t<CallMethodResult_t>());
  if (!result.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  result->StatusCode() = OpcUa_Good;

  return OpcUa_Good;
}

Status_t FileTransferRouter_t::GetPositionMethodCall(IntrusivePtr_t<const NodeId_t> sessionId,
  IntrusivePtr_t<FileUA_t> file,
  IntrusivePtr_t<const CallMethodRequest_t>& requestParameters,
  IntrusivePtr_t<CallMethodResult_t>& result)
{
  IntrusivePtr_t< UInt32_t > fileHandle;

  Status_t status = AddressSpaceUtilities_t::CastInputArguments(requestParameters->InputArguments(), fileHandle);

  if (!fileHandle.is_set() || status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  IntrusivePtr_t<UInt64_t > position;
  status = file->GetPosition(sessionId, fileHandle->Value(), position);
  if (status.IsBad() || !position.is_set())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  result.reset(new SafeRefCount_t<CallMethodResult_t>());
  if (!result.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  status = result->OutputArguments().Initialise(1);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
  status = position->CopyTo((result->OutputArguments())[0]);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
  result->StatusCode() = OpcUa_Good;

  return OpcUa_Good;
}

Status_t FileTransferRouter_t::SetPositionMethodCall(IntrusivePtr_t<const NodeId_t> sessionId,
  IntrusivePtr_t<FileUA_t> file,
  IntrusivePtr_t<const CallMethodRequest_t>& requestParameters,
  IntrusivePtr_t<CallMethodResult_t>& result)
{
  IntrusivePtr_t< UInt32_t > fileHandle;
  IntrusivePtr_t< UInt64_t > position;

  Status_t status = AddressSpaceUtilities_t::CastInputArguments(requestParameters->InputArguments(), fileHandle, position);

  if (!fileHandle.is_set() || !position.is_set() || status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }
  IntrusivePtr_t<ByteString_t> output;
  status = file->SetPosition(sessionId, fileHandle->Value(), position);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  result.reset(new SafeRefCount_t<CallMethodResult_t>());
  if (!result.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  result->StatusCode() = OpcUa_Good;

  return OpcUa_Good;
}

IntrusivePtr_t<FileUA_t> FileTransferRouter_t::getFile(IntrusivePtr_t<const NodeId_t>& fileObjectId)
{
  IntrusivePtr_t<FileUA_t> empty;
  uint32_t count = allFiles.Count();
  if (count == 0)
  {
    return empty;
  }
  for (; count > 0; count--)
  {
    IntrusivePtr_t<FileUA_t> file = allFiles.GetAtIndex(count - 1);
    if (!file.is_set())
    {
      return empty;
    }
    if (*file->FileObjectId() == *fileObjectId)
    {
      return file;
    }
  }
  return empty;
}

Status_t FileTransferRouter_t::Initialise()
{
  allFiles.DeleteAll();
  return OpcUa_Good;
}

Status_t FileTransferRouter_t::AddFile(FileUA_t& file)
{
  return allFiles.AddToTail(file);
}

Status_t FileTransferRouter_t::RemoveFile(FileUA_t& file)
{
  uint32_t count = allFiles.Count();
  if (count == 0)
  {
    return OpcUa_BadInternalError;
  }
  for (; count > 0; count--)
  {
    IntrusivePtr_t<FileUA_t> tempFile = allFiles.GetAtIndex(count - 1);
    if (!tempFile.is_set())
    {
      return OpcUa_BadInternalError;
    }
    if (*tempFile->FileObjectId() == *file.FileObjectId())
    {
      allFiles.DeleteCurrent();
      break;
    }
  }
  return OpcUa_Good;
}

Status_t FileTransferRouter_t::CallMethodBegin(
  IntrusivePtr_t<const NodeId_t> sessionId,
  uint32_t transactionId,
  const IUserPermissions_t& userPermissions,
  uint32_t timeoutHint,
  IntrusivePtr_t<IObjectNode_t>& componentOf,
  IntrusivePtr_t<IMethodNode_t>& method,
  IntrusivePtr_t<const CallMethodRequest_t>& requestParameters,
  IntrusivePtr_t<CallMethodResult_t>& result,
  IntrusivePtr_t<ICallbackCallMethodCompleted_t>& completedCallback)
{
  UASDK_UNUSED(transactionId);
  UASDK_UNUSED(userPermissions);
  UASDK_UNUSED(timeoutHint);

  Status_t status;

  if (!method.is_set() || !componentOf.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  //if (!method->UserExecutable(userPermissions))
  //{
  //  UASDK_RETURN_BAD_STATUS(OpcUa_BadUserAccessDenied);
  //}
  IntrusivePtr_t<const NodeId_t> nodeId_ = componentOf->NodeId();
  if(!nodeId_.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  IntrusivePtr_t<FileUA_t> file = getFile(nodeId_);
  if (!file.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }
  
  if (method->NodeId()->NodeIdIdentiferType() != NodeId_t::NODEID_IDENTIFIER_NUMERIC)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }
  
  UInt32_t tempMethodID;
  status = tempMethodID.CopyFrom(method->NodeId()->IdentiferBase());
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  switch (tempMethodID.Value())
  {
  case OPEN_METHOD_NODE_ID:
    status = OpenMethodCall(sessionId, file, requestParameters, result);
    if (status.IsBad())
    {
      UASDK_RETURN_BAD_STATUS(status.Value());
    }
    break;

  case CLOSE_METHOD_NODE_ID:
    status = CloseMethodCall(sessionId, file, requestParameters, result);
    if (status.IsBad())
    {
      UASDK_RETURN_BAD_STATUS(status.Value());
    }
    break;

  case READ_METHOD_NODE_ID:
    status = ReadMethodCall(sessionId, file, requestParameters, result);
    if (status.IsBad())
    {
      UASDK_RETURN_BAD_STATUS(status.Value());
    }
    break;
  case WRITE_METHOD_NODE_ID:
    status = WriteMethodCall(sessionId, file, requestParameters, result);
    if (status.IsBad())
    {
      UASDK_RETURN_BAD_STATUS(status.Value());
    }
    break;
  case GET_POSITION_METHOD_NODE_ID: 
    status = GetPositionMethodCall(sessionId, file, requestParameters, result);
    if (status.IsBad())
    {
      UASDK_RETURN_BAD_STATUS(status.Value());
    }
    break;
  case SET_POSITION_METHOD_NODE_ID:
    status = SetPositionMethodCall(sessionId, file, requestParameters, result);
    if (status.IsBad())
    {
      UASDK_RETURN_BAD_STATUS(status.Value());
    }
    break;
  default:
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
    
  }
  
  return completedCallback->CallMethodCompleted(result);
}

} //namespace uasdk

#endif //(UASDK_INCLUDE_SERVER_C_API > 0) && (UASDK_USE_FILE_OBJECT_HELPERS > 0)
#endif //(UASDK_INCLUDE_SERVER)
