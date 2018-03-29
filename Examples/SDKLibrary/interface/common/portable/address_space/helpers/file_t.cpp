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

#include "file_t.h"

#if ( (UASDK_USE_HELPERS > 0) && (UASDK_USE_FILE_OBJECT_HELPERS > 0))

#include "address_space_utilities_t.h"
#include "opcua_uint64_t.h"
#include "browse_names_t.h"
#include "opcua_node_id_numeric_t.h"
#include "file_property_reader_writer_t.h"
#include "opcua_argument_t.h"
#include "opcua_array_ua_t.h"

namespace uasdk
{

/*-----------------------------------------------------------------------------------------*/
//TODO - remove this code once Structure value attibute parsring is supported in xml parser
const char* FILE_HANDLE = "FileHandle";
const char* POSITION    = "Position";
const char* MODE        = "Mode";
const char* LENGTH      = "Length";
const char* DATA        = "Data";

IntrusivePtr_t<Argument_t> GetArgument(const char* name_, uint32_t id_, Status_t& result)
{
  IntrusivePtr_t<Argument_t> empty;
  IntrusivePtr_t<Argument_t> argument(new SafeRefCount_t<Argument_t>);
  if (!argument.is_set())
  {
    result = OpcUa_BadOutOfMemory;
    return empty;
  }
  result = argument->Name().CopyFrom(name_);
  if (result.IsBad())
  {
    return empty;
  }
  IntrusivePtr_t<NodeIdNumeric_t> dataTypeId_(new SafeRefCount_t<NodeIdNumeric_t>());
  if (!dataTypeId_.is_set())
  {
    result = OpcUa_BadOutOfMemory;
    return empty;
  }
  dataTypeId_->NamespaceIndex().Value(0);
  dataTypeId_->Identifer().Value(id_);
  argument->DataType() = dataTypeId_;

  argument->ValueRank().Value(-1);

  result = OpcUa_Good;
  return argument;
}

Status_t AssignValueToArgument(const char* name, uint32_t dataTypeId, uint32_t index, IntrusivePtr_t< ArrayUA_t<Argument_t> >& value)
{
  if ((!value.is_set()) && (index > (value->Size() - 1)))
  {
    return OpcUa_BadInvalidArgument;
  }

  Status_t status;
  IntrusivePtr_t<Argument_t> argument = GetArgument(name, dataTypeId, status);
  if (!argument.is_set() || status.IsBad())
  {
    return status;
  }
  (*value)[index] = argument;

  return OpcUa_Good;
}

Status_t AssignArgumentValue(uint32_t methodId, bool outputArgument, IntrusivePtr_t<IVariableNode_t>& result)
{
  if (!result.is_set())
  {
    return OpcUa_BadInvalidArgument;
  }

  Status_t status;

  IntrusivePtr_t< ArrayUA_t<Argument_t> > value(new SafeRefCount_t< ArrayUA_t<Argument_t> >());
  if (!value.is_set())
  {
    return OpcUa_BadOutOfMemory;
  }

  if (outputArgument != true)
  {
    if ((methodId == OpcUaId_FileType_Read) || (methodId == OpcUaId_FileType_Write) || (methodId == OpcUaId_FileType_SetPosition))
    {
      status = value->Initialise(2);
      if (status.IsBad())
      {
        return status;
      }
    }
    else
    {
      status = value->Initialise(1);
      if (status.IsBad())
      {
        return status;
      }
    }
  }
  else
  {
    if ((methodId == OpcUaId_FileType_Open) || (methodId == OpcUaId_FileType_Read) || (methodId == OpcUaId_FileType_GetPosition))
    {
      status = value->Initialise(1);
      if (status.IsBad())
      {
        return status;
      }
    }
    else
    {
      status = OpcUa_BadInvalidArgument;
      return status;
    }
  }

  switch (methodId)
  {
    case OpcUaId_FileType_Open:
      if (outputArgument != true)
      {
        status = AssignValueToArgument(MODE, OpcUaId_Byte, 0, value);
        if (status.IsBad())
        {
          return status;
        }
      }
      else
      {
        status = AssignValueToArgument(FILE_HANDLE, OpcUaId_UInt32, 0, value);
        if (status.IsBad())
        {
          return status;
        }
      }
      break;

    case OpcUaId_FileType_Close:
      status = AssignValueToArgument(FILE_HANDLE, OpcUaId_UInt32, 0, value);
      if (status.IsBad())
      {
        return status;
      }
      break;

    case OpcUaId_FileType_Read:
      if (outputArgument != true)
      {
        status = AssignValueToArgument(FILE_HANDLE, OpcUaId_UInt32, 0, value);
        if (status.IsBad())
        {
          return status;
        }
        status = AssignValueToArgument(LENGTH, OpcUaId_Int32, 1, value);
        if (status.IsBad())
        {
          return status;
        }
      }
      else
      {
        status = AssignValueToArgument(DATA, OpcUaId_ByteString, 0, value);
        if (status.IsBad())
        {
          return status;
        }
      }
      break;

    case OpcUaId_FileType_Write:
      status = AssignValueToArgument(FILE_HANDLE, OpcUaId_UInt32, 0, value);
      if (status.IsBad())
      {
        return status;
      }
      status = AssignValueToArgument(DATA, OpcUaId_ByteString, 1, value);
      if (status.IsBad())
      {
        return status;
      }
      break;

    case OpcUaId_FileType_SetPosition:
      status = AssignValueToArgument(FILE_HANDLE, OpcUaId_UInt32, 0, value);
      if (status.IsBad())
      {
        return status;
      }
      status = AssignValueToArgument(POSITION, OpcUaId_UInt64, 1, value);
      if (status.IsBad())
      {
        return status;
      }
      break;

    case OpcUaId_FileType_GetPosition:
      if (outputArgument != true)
      {
        status = AssignValueToArgument(FILE_HANDLE, OpcUaId_UInt32, 0, value);
        if (status.IsBad())
        {
          return status;
        }
      }
      else
      {
        status = AssignValueToArgument(POSITION, OpcUaId_UInt64, 0, value);
        if (status.IsBad())
        {
          return status;
        }
      }
      break;

    default:
      return status;
  }  

  IntrusivePtr_t<DataValue_t> dataValue(new SafeRefCount_t<DataValue_t>());
  if (!dataValue.is_set())
  {
    return OpcUa_BadOutOfMemory;
  }
  dataValue->Value() = value;

  IntrusivePtr_t<DateTime_t> sourceTime(new SafeRefCount_t<DateTime_t>());
  if (!sourceTime.is_set())
  {
    return OpcUa_BadOutOfMemory;
  }
  sourceTime->Value(UASDK_datetime());
  dataValue->SourceTimestamp() = sourceTime;

  IntrusivePtr_t<StatusCode_t> statusCode_ = new SafeRefCount_t<StatusCode_t>();
  if (!statusCode_.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  statusCode_->Value().Value(OpcUa_Good);
  dataValue->StatusCode() = statusCode_;
  
  result->Value(dataValue);
  return OpcUa_Good;
}

Status_t AssignArgumentValueForStandardFileMethodNodes(IMethodNode_t& methodNode, uint32_t methodId, IAddressSpace_t& addressSpace_)
{
  Status_t status;
  IntrusivePtr_t<IVariableNode_t> inputArgument;
  
  //Input Argument
  String_t propertyName;
  status = propertyName.CopyFrom(BROWSE_NAME_INPUT_ARGUMENTS);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  status = AddressSpaceUtilities_t::GetProperty(methodNode, addressSpace_, propertyName, inputArgument);
  if (!inputArgument.is_set() || status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  status = AssignArgumentValue(methodId, false, inputArgument);
  if (status.IsBad() || !inputArgument->Value().is_set())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  if ((methodId == OpcUaId_FileType_Open) || (methodId == OpcUaId_FileType_Read) || (methodId == OpcUaId_FileType_GetPosition))
  {
    IntrusivePtr_t<IVariableNode_t> outputArgument;
    status = propertyName.CopyFrom(BROWSE_NAME_OUTPUT_ARGUMENTS);
    if (status.IsBad())
    {
      UASDK_RETURN_BAD_STATUS(status.Value());
    }

    status = AddressSpaceUtilities_t::GetProperty(methodNode, addressSpace_, propertyName, outputArgument);
    if (!outputArgument.is_set() || status.IsBad())
    {
      UASDK_RETURN_BAD_STATUS(status.Value());
    }

    status = AssignArgumentValue(methodId, true, outputArgument);
    if (status.IsBad() || !outputArgument->Value().is_set())
    {
      UASDK_RETURN_BAD_STATUS(status.Value());
    }
  }

  return OpcUa_Good;
}
/*-----------------------------------------------------------------------------------------*/
/*
 * private Functions
 */
Status_t File_t::AddMethodNodeReference(uint32_t id, IntrusivePtr_t<INodeMethodHandler_t>& methodHandler, File_t& fileObject)
{
  if (!fileObject.node.is_set() || !fileObject.addressSpace.is_set() || !methodHandler.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }
  Status_t status;
  NodeIdNumeric_t methodId(0, id);
  IntrusivePtr_t<IMethodNode_t> methodNode = fileObject.addressSpace->FindMethodNode(methodId, status);
  if (status.IsBad() || !methodNode.is_set())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
  
  status = methodNode->SetMethodHandler(methodHandler);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  status = AssignArgumentValueForStandardFileMethodNodes(*methodNode, id, *fileObject.addressSpace);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  return AddressSpaceUtilities_t::CreateReference(*fileObject.addressSpace, *fileObject.node, *methodNode, OpcUaId_HasComponent);
}

IntrusivePtr_t<File_t> File_t::CreateFileObject(IntrusivePtr_t<IObjectNode_t>& node_, IntrusivePtr_t<IAddressSpace_t>& addressSpace_, Status_t& result)
{
  IntrusivePtr_t<File_t> retVal;
  if (!node_.is_set() || !addressSpace_.is_set() || result.IsBad())
  {
    result = OpcUa_BadInvalidArgument;
    return retVal;
  }

  retVal.reset(new SafeRefCount_t<File_t>());
  if (!retVal.is_set())
  {
    result = OpcUa_BadOutOfMemory;
    return retVal;
  }

  retVal->Initialize(node_, addressSpace_);
  result = OpcUa_Good;

  return retVal;
}

Status_t File_t::SetReaderWriter(IntrusivePtr_t<IVariableNode_t>& propertyNode, uint32_t propertyType, const IntrusivePtr_t<IFileUA_t>& fileHandler)
{
  if (!propertyNode.is_set() || !fileHandler.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  IntrusivePtr_t<FilePropertyReaderWriter_t> readerWriter(new SafeRefCount_t<FilePropertyReaderWriter_t>());
  if (!readerWriter.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  Status_t status = readerWriter->Initialize(fileHandler);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  switch(propertyType)
  {
    case OpcUaId_FileType_Size:
      readerWriter->AddSizeNodeId(propertyNode->NodeId());
      break;

    case OpcUaId_FileType_OpenCount:
      readerWriter->AddOpenCountNodeId(propertyNode->NodeId());
      break;

    case OpcUaId_FileType_Writeable:
    case OpcUaId_FileType_UserWriteable:
      break;

    default :
      UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  if (propertyNode->Value().is_set())
  {
    IntrusivePtr_t<DataValue_t> empty;
    propertyNode->Value(empty);
  }

  return propertyNode->ValueAttributeReaderWriter(readerWriter);
}

IntrusivePtr_t<IVariableNode_t> File_t::SizeNode(void)
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return HelperBase_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_SIZE);
}
IntrusivePtr_t<const IVariableNode_t> File_t::SizeNode(void) const
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return HelperBase_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_SIZE);
}

IntrusivePtr_t<IVariableNode_t> File_t::WritableNode(void)
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return HelperBase_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_WRITABLE);
}
IntrusivePtr_t<const IVariableNode_t> File_t::WritableNode(void) const
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return HelperBase_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_WRITABLE);
}

IntrusivePtr_t<IVariableNode_t> File_t::UserWritableNode(void)
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return HelperBase_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_USER_WRITABLE);
}
IntrusivePtr_t<const IVariableNode_t> File_t::UserWritableNode(void) const
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return HelperBase_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_USER_WRITABLE);
}

IntrusivePtr_t<IVariableNode_t> File_t::OpenCountNode(void)
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return HelperBase_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_OPEN_COUNT);
}
IntrusivePtr_t<const IVariableNode_t> File_t::OpenCountNode(void) const
{
  if (!addressSpace.is_set() || !node.is_set())
  {
    IntrusivePtr_t<IVariableNode_t> empty;
    return empty;
  }

  return HelperBase_t::GetPropertyNode(*addressSpace, *node, BROWSE_NAME_OPEN_COUNT);
}

Status_t File_t::CreateSizeProperty(File_t& fileObject,
  const MandatoryPropertyNumericIds_t& propertyIdentifier,
  const MandatoryPropertyValues_t& value)
{
  IntrusivePtr_t<IVariableNode_t> propertyNode = fileObject.SizeNode();
  IntrusivePtr_t<UInt64_t> destinationVal(new SafeRefCount_t<UInt64_t>());
  if (!destinationVal.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  UInt64_t dummy(0);

  Status_t status = HelperBase_t::CreatePropertyAndAssignValue(fileObject, propertyIdentifier.sizeId, BROWSE_NAME_SIZE,
                                                               OpcUaId_UInt64, destinationVal, dummy, propertyNode);
  if (status.IsBad() || !propertyNode.is_set())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
  
  //Set the value attribute reader writer for Size preoperty
  return SetReaderWriter(propertyNode, OpcUaId_FileType_Size, value.fileHandler);
}

Status_t File_t::CreateWritableProperty(File_t& fileObject,
  const MandatoryPropertyNumericIds_t& propertyIdentifier,
  const MandatoryPropertyValues_t& value)
{
  IntrusivePtr_t<IVariableNode_t> propertyNode = fileObject.WritableNode();
  IntrusivePtr_t<Boolean_t> destinationVal(new SafeRefCount_t<Boolean_t>());
  if (!destinationVal.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  return HelperBase_t::CreatePropertyAndAssignValue(fileObject, propertyIdentifier.writableId, BROWSE_NAME_WRITABLE,
                                                    OpcUaId_Boolean, destinationVal, value.writable, propertyNode);
}

Status_t File_t::CreateUserWritableProperty(File_t& fileObject,
  const MandatoryPropertyNumericIds_t& propertyIdentifier,
  const MandatoryPropertyValues_t& value)
{
  IntrusivePtr_t<IVariableNode_t> propertyNode = fileObject.UserWritableNode();
  IntrusivePtr_t<Boolean_t> destinationVal(new SafeRefCount_t<Boolean_t>());
  if (!destinationVal.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  return HelperBase_t::CreatePropertyAndAssignValue(fileObject, propertyIdentifier.userWritableId, BROWSE_NAME_USER_WRITABLE,
                                                    OpcUaId_Boolean, destinationVal, value.userWritable, propertyNode);
}

Status_t File_t::CreateOpenCountProperty(File_t& fileObject,
  const MandatoryPropertyNumericIds_t& propertyIdentifier,
  const MandatoryPropertyValues_t& value)
{
  IntrusivePtr_t<IVariableNode_t> propertyNode = fileObject.OpenCountNode();
  IntrusivePtr_t<UInt16_t> destinationVal(new SafeRefCount_t<UInt16_t>());
  if (!destinationVal.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  UInt16_t dummy(0);

  Status_t status = HelperBase_t::CreatePropertyAndAssignValue(fileObject, propertyIdentifier.openCountId, BROWSE_NAME_OPEN_COUNT,
                                                               OpcUaId_UInt16, destinationVal, dummy, propertyNode);
  if (status.IsBad() || !propertyNode.is_set())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  //Set the value attribute reader writer for Size preoperty
  return SetReaderWriter(propertyNode, OpcUaId_FileType_OpenCount, value.fileHandler);
}

IntrusivePtr_t<File_t> File_t::CreateFileObjectWithMandatoryProperty(IntrusivePtr_t<const NodeId_t>& nodeId_,
                                                                                 const String_t& browseName,
                                                                                 IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                                                 const MandatoryPropertyNumericIds_t& ids,
                                                                                 const MandatoryPropertyValues_t& value,
                                                                                 IntrusivePtr_t<INodeMethodHandler_t>& methodHandler,
                                                                                 Status_t& result)
{
  IntrusivePtr_t<File_t> empty;

  if (!methodHandler.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  IntrusivePtr_t<IObjectNode_t> fileNode = HelperBase_t::Create(nodeId_, addressSpace_, browseName, OpcUaId_FileType, result);
  if (result.IsBad() || !fileNode.is_set())
  {
    return empty;
  }

  IntrusivePtr_t<File_t> fileObject = File_t::CreateFileObject(fileNode, addressSpace_, result);
  if (!fileObject.is_set() || result.IsBad())
  {
    return empty;
  }

  //Create properties
  result = CreateSizeProperty(*fileObject, ids, value);
  if (result.IsBad())
  {
    return empty;
  }

  result = CreateWritableProperty(*fileObject, ids, value);
  if (result.IsBad())
  {
    return empty;
  }

  result = CreateUserWritableProperty(*fileObject, ids, value);
  if (result.IsBad())
  {
    return empty;
  }

  result = CreateOpenCountProperty(*fileObject, ids, value);
  if (result.IsBad())
  {
    return empty;
  }

  result = AddMethodNodeReference(OpcUaId_FileType_Open, methodHandler, *fileObject);
  if (result.IsBad())
  {
    return empty;
  }
  result = AddMethodNodeReference(OpcUaId_FileType_Close, methodHandler, *fileObject);
  if (result.IsBad())
  {
    return empty;
  }
  result = AddMethodNodeReference(OpcUaId_FileType_Read, methodHandler, *fileObject);
  if (result.IsBad())
  {
    return empty;
  }
  result = AddMethodNodeReference(OpcUaId_FileType_Write, methodHandler, *fileObject);
  if (result.IsBad())
  {
    return empty;
  }
  result = AddMethodNodeReference(OpcUaId_FileType_SetPosition, methodHandler, *fileObject);
  if (result.IsBad())
  {
    return empty;
  }
  result = AddMethodNodeReference(OpcUaId_FileType_GetPosition, methodHandler, *fileObject);
  if (result.IsBad())
  {
    return empty;
  }

  return fileObject;
}

/*
* public functions
*/

File_t::File_t()
{
}

void File_t::DeleteProperties(File_t& fileObject)
{
  UASDK_RETURN_IF_NULL(fileObject.addressSpace);
  IntrusivePtr_t<IVariableNode_t> node_ = SizeNode();
  if (node_.is_set() && (node_->NodeId().is_set()))
  {
    fileObject.addressSpace->RemoveNode(*(node_->NodeId()));
  }

  node_ = WritableNode();
  if (node_.is_set() && (node_->NodeId().is_set()))
  {
    fileObject.addressSpace->RemoveNode(*(node_->NodeId()));
  }

  node_ = UserWritableNode();
  if (node_.is_set() && (node_->NodeId().is_set()))
  {
    fileObject.addressSpace->RemoveNode(*(node_->NodeId()));
  }

  node_ = OpenCountNode();
  if (node_.is_set() && (node_->NodeId().is_set()))
  {
    fileObject.addressSpace->RemoveNode(*(node_->NodeId()));
  }
}

/*
* public functions
*/

File_t::~File_t()
{
  if (deleteNode)
  {
    DeleteProperties(*this);
  }
}

IntrusivePtr_t<File_t> File_t::Get(const NodeId_t& nodeId,
                                               IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                               Status_t& result)
{
  IntrusivePtr_t<File_t> empty;
  if (!addressSpace_.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  IntrusivePtr_t<IObjectNode_t> fileObjectNode = addressSpace_->FindObjectNode(nodeId, result);
  if (result.IsBad() || !fileObjectNode.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  return Get(fileObjectNode, addressSpace_, result);
}

IntrusivePtr_t<File_t> File_t::Get(IntrusivePtr_t<IObjectNode_t>& node,
                                               IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                               Status_t& result)
{
  IntrusivePtr_t<File_t> empty;
  if (!node.is_set() || !addressSpace_.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  result = HelperBase_t::CheckHasTypeDefinition(*node, *addressSpace_, OpcUaId_FileType);
  if (result.IsBad())
  {
    return empty;
  }

  return File_t::CreateFileObject(node, addressSpace_, result);
}

IntrusivePtr_t<File_t> File_t::CreateWithNumericId(uint16_t namespaceIndex,
                                                   uint32_t nodeIdentifier,
                                                   IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                   const String_t& browseName,
                                                   MandatoryPropertyNumericIds_t& propertyIds,
                                                   MandatoryPropertyValues_t& propertyValues,
                                                   IntrusivePtr_t<INodeMethodHandler_t> methodHandler,
                                                   Status_t& result)
{
  IntrusivePtr_t<File_t> empty;

  IntrusivePtr_t<const NodeId_t> nodeId;
  result = AddressSpaceUtilities_t::GenerateNumericNodeId(namespaceIndex, nodeIdentifier, nodeId);
  if (result.IsBad())
  {
    return empty;
  }

  return File_t::CreateFileObjectWithMandatoryProperty(nodeId, browseName, addressSpace_, propertyIds, propertyValues, methodHandler, result);
}

IntrusivePtr_t<File_t> File_t::CreateWithStringId(uint16_t namespaceIndex,
                                                  const String_t& nodeIdentifier,
                                                  IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                  const String_t& browseName,
                                                  MandatoryPropertyValues_t& propertyValues,
                                                  IntrusivePtr_t<INodeMethodHandler_t> methodHandler,
                                                  Status_t& result)
{
  IntrusivePtr_t<File_t> empty;

  IntrusivePtr_t<const NodeId_t> nodeId;
  result = AddressSpaceUtilities_t::GenerateStringNodeId(namespaceIndex, nodeIdentifier, nodeId);
  if (result.IsBad())
  {
    return empty;
  }

  MandatoryPropertyNumericIds_t dummy = { 0, 0, 0, 0 };
  return File_t::CreateFileObjectWithMandatoryProperty(nodeId, browseName, addressSpace_, dummy, propertyValues, methodHandler, result);
}

IntrusivePtr_t<File_t> File_t::CreateWithGuidId(uint16_t namespaceIndex,
                                                const Guid_t& nodeIdentifier,
                                                IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                const String_t& browseName,
                                                MandatoryPropertyValues_t& propertyValues,
                                                IntrusivePtr_t<INodeMethodHandler_t> methodHandler,
                                                Status_t& result)
{
  IntrusivePtr_t<File_t> empty;

  IntrusivePtr_t<const NodeId_t> nodeId;
  result = AddressSpaceUtilities_t::GenerateGuidNodeId(namespaceIndex, nodeIdentifier, nodeId);
  if (result.IsBad())
  {
    return empty;
  }

  MandatoryPropertyNumericIds_t dummy = { 0, 0, 0, 0 };
  return File_t::CreateFileObjectWithMandatoryProperty(nodeId, browseName, addressSpace_, dummy, propertyValues, methodHandler, result);
}

IntrusivePtr_t<File_t> File_t::CreateWithOpaqueId(uint16_t namespaceIndex,
                                                  const ByteString_t& nodeIdentifier,
                                                  IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                  const String_t& browseName,
                                                  MandatoryPropertyValues_t& propertyValues,
                                                  IntrusivePtr_t<INodeMethodHandler_t> methodHandler,
                                                  Status_t& result)
{
  IntrusivePtr_t<File_t> empty;

  IntrusivePtr_t<const NodeId_t> nodeId;
  result = AddressSpaceUtilities_t::GenerateOpaqueNodeId(namespaceIndex, nodeIdentifier, nodeId);
  if (result.IsBad())
  {
    return empty;
  }

  MandatoryPropertyNumericIds_t dummy = { 0, 0, 0, 0 };
  return File_t::CreateFileObjectWithMandatoryProperty(nodeId, browseName, addressSpace_, dummy, propertyValues, methodHandler, result);
}

}

#endif  //UASDK_USE_FILE_TRANSFER_HELPERS