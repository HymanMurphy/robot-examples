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

#include "helper_base_t.h"

#if (UASDK_USE_HELPERS > 0)

#include "address_space_utilities_t.h"
#include "utilities.h"
#include "ivariable_node_t.h"
#include "opcua_date_time_t.h"
#include "opcua_uint16_t.h"
#include "opcua_qualified_name_t.h"
#include "opcua_data_value_t.h"
#include "access_level_t.h"
#include "opcua_node_id_numeric_t.h"
#include "localizable_text_stored_t.h"
#include "opcua_diagnostic_info_t.h"
#include "opcua_node_id_string_t.h"

static char stringNodeIdSeperator = '/';

namespace uasdk
{
/*
 * Private functions
 */
Status_t HelperBase_t::CreateQualifiedName(const String_t& name, uint16_t namespaceIndex, IntrusivePtr_t<const QualifiedName_t>& result)
{
  IntrusivePtr_t<QualifiedName_t> qualifiedName(new SafeRefCount_t<QualifiedName_t>());
  if(!qualifiedName.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
 
  qualifiedName->NamespaceIndex().Value(namespaceIndex);
  Status_t status = qualifiedName->Name().CopyFrom(name);
  if(status.IsBad())
  {
    return status;
  }
 
  result = qualifiedName;
 
  return OpcUa_Good;
}
 
Status_t HelperBase_t::CreateLocalizableText(const String_t& text, IntrusivePtr_t<const ILocalizableText_t>& result)
{
  IntrusivePtr_t<LocalizedText_t> localizedText(new SafeRefCount_t<LocalizedText_t>());
  if(!localizedText.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
 
  Status_t status = localizedText->Text().CopyFrom(text);
  if(status.IsBad())
  {
    return status;
  }
 
  IntrusivePtr_t<const LocalizedText_t> localizedText_ = localizedText;
  IntrusivePtr_t<LocalizableTextStored_t> localizableTextStored(new SafeRefCount_t<LocalizableTextStored_t>());
  if(!localizableTextStored.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  localizableTextStored->AddText(localizedText_);
 
  result = localizableTextStored;
 
  return OpcUa_Good;
}

Status_t HelperBase_t::ConvertToNodeIdPointer(const NodeId_t& sourceId, IAddressSpace_t& addressSpace_, IntrusivePtr_t<const NodeId_t>& result)
{
  Status_t status;
  IntrusivePtr_t<INode_t> node_ = addressSpace_.FindNode(sourceId, status);
  if (status.IsGood() && node_.is_set() && node_->NodeId().is_set())
  {
    result = node_->NodeId();
  }
  else
  {
    IntrusivePtr_t<NodeId_t> temp;
    Status_t status = sourceId.CopyToNodeId(temp);
    if (status.IsBad())
    {
      return status;
    }
    result = temp;
  }
  return OpcUa_Good;
}

Status_t HelperBase_t::UpdateAttributes(uint16_t namespaceIndex,
                                        const String_t& browseName_,
                                        INode_t& result)
{
  if (!result.NodeId().is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  //BrowseName Attribute
  IntrusivePtr_t<const QualifiedName_t> browseName;
  Status_t status = HelperBase_t::CreateQualifiedName(browseName_, namespaceIndex, browseName);
  if (status.IsBad() || !browseName.is_set())
  {
    return status;
  }
  result.BrowseName(browseName);

  //DisplayName Attribute
  IntrusivePtr_t<const ILocalizableText_t> displayName;
  status = HelperBase_t::CreateLocalizableText(browseName_, displayName);
  result.DisplayName(displayName);
  
  return OpcUa_Good;
}

Status_t HelperBase_t::UpdateAttributes(uint16_t namespaceIndex,
                                        IAddressSpace_t& addressSpace_,
                                        const String_t& browseName_,
                                        uint32_t dataTypeId,
                                        int32_t valueRank,
                                        IntrusivePtr_t<IVariableNode_t>& result)
{
  if (!result.is_set() || !result->NodeId().is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  Status_t status = UpdateAttributes(namespaceIndex, browseName_, *result);

  //DataType Attribute
  NodeIdNumeric_t numericNodeId(0, dataTypeId);
  IntrusivePtr_t<const NodeId_t> dataTypeNodeId;

  status = HelperBase_t::ConvertToNodeIdPointer(numericNodeId, addressSpace_, dataTypeNodeId);
  if (status.IsBad() || !dataTypeNodeId.is_set())
  {
    return status;
  }
  result->DataType(dataTypeNodeId);

  //Value Rank
  result->ValueRank(valueRank);

  //AccessLevel
  AccessLevel_t accessLevel(0x01);
  result->AccessLevel(accessLevel);

  return OpcUa_Good;
}

/*
 * Protected Function
 */
HelperBase_t::HelperBase_t() : deleteNode(false)
{}

void HelperBase_t::Initialize(IntrusivePtr_t<INode_t> node_, IntrusivePtr_t<IAddressSpace_t> addressSpace_)
{
  node = node_;
  addressSpace = addressSpace_;
}

Status_t HelperBase_t::CheckHasTypeDefinition(const INode_t& node, const IAddressSpace_t& addressSpace_, uint32_t typeId)
{
  Status_t status;
  IntrusivePtr_t<NodeId_t> hasTypeDef;
  status = AddressSpaceUtilities_t::GetTypeDefinition(node, addressSpace_, hasTypeDef);
  if (status.IsBad() || !hasTypeDef.is_set())
  {
    return status;
  }

  const UInt32_t* typeDef_ = RuntimeCast<const UInt32_t* >(hasTypeDef->IdentiferBase());
  if ((!typeDef_) || (typeDef_->Value() != typeId))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  return status;
}

IntrusivePtr_t<IVariableNode_t> HelperBase_t::GetPropertyNode(IAddressSpace_t& addressSpace, const INode_t& sourceNode, const char* propertyName)
{
  IntrusivePtr_t<IVariableNode_t> empty;

  String_t name;
  Status_t status = name.CopyFrom(propertyName);
  if (status.IsBad())
  {
    return empty;
  }

  IntrusivePtr_t<IVariableNode_t> retVal;
  status = AddressSpaceUtilities_t::GetProperty(sourceNode, addressSpace, name, retVal);
  if (status.IsBad() || !retVal.is_set())
  {
    return empty;
  }

  return retVal;
}

Status_t HelperBase_t::GenerateStringNodeId(const NodeId_t& sourceId, const char* propertyName, IntrusivePtr_t<const NodeId_t>& result)
{
  if ((sourceId.NodeIdIdentiferType() != NodeId_t::NODEID_IDENTIFIER_STRING) || !propertyName)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  String_t sourceStringId;
  Status_t status = sourceStringId.CopyFrom(sourceId.IdentiferBase());
  UASDK_RETURN_STATUS_ONLY_IF_BAD(status.Value());
  
  ScopedPtr_t<Array_t<char> > str;
  status = sourceStringId.ToString(str);
  if (status.IsBad() || !str.is_set())
  {
    return status;
  }
  int32_t strLenght = str->Size() - 1; // NUll termination is also included with str->Size().
  int32_t propertyNameLength = Utilities_t::Strnlen(propertyName, 200);
  if (propertyNameLength == 200)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  int32_t length = strLenght + 1 + propertyNameLength;

  Array_t<char> strId;
  status = strId.Initialise(length + 1);
  if (status.IsBad())
  {
    return status;
  }

  //create id
  char* id = strId.Value();
  if (!id)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  if (UASDK_memcpy(strId.Value(), str->Value(), strLenght) != id)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
  }
  id[strLenght] = HelperBase_t::StringNodeIdSeparator();

  char* temp = id + (strLenght + 1);
  if (UASDK_memcpy(temp, propertyName, propertyNameLength) != temp)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
  }
  id[length] = '\0';

  String_t stringId;
  status = stringId.CopyFrom(strId.Value());
  if (status.IsBad())
  {
    return status;
  }

  return AddressSpaceUtilities_t::GenerateStringNodeId(sourceId.NamespaceIndex().Value(), stringId, result);
}

Status_t HelperBase_t::GenerateOpaqueNodeId(const uint16_t namespaceIndex, const uint8_t* data, const int32_t lengthOfData, const char* propertyName, IntrusivePtr_t<const NodeId_t>& result)
{
  uint32_t propertyNameLength = Utilities_t::Strnlen(propertyName, 4096);
  if (propertyNameLength == 4096)
  {
    return OpcUa_BadUnexpectedError;
  }

  ByteString_t id_;
  Status_t status = id_.Initialise(lengthOfData + 1 + propertyNameLength);
  if (status.IsBad())
  {
    return status;
  }

  uint8_t* temp = id_.Data();
  if (!temp)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  if (UASDK_memcpy(temp, data, lengthOfData) != temp)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
  }

  temp[lengthOfData] = HelperBase_t::StringNodeIdSeparator();
  temp = temp + lengthOfData + 1;

  if (UASDK_memcpy(temp, propertyName, propertyNameLength) != temp)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInternalError);
  }

  return AddressSpaceUtilities_t::GenerateOpaqueNodeId(namespaceIndex, id_, result);
}

IntrusivePtr_t<IObjectNode_t> HelperBase_t::Create(IntrusivePtr_t<const NodeId_t> nodeId,
                                                   IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                   const String_t& browseName,
                                                   uint32_t hasTypeReferenceId,
                                                   Status_t& result)
{
  IntrusivePtr_t<IObjectNode_t> empty;
  if (!nodeId.is_set() || !addressSpace_.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  IntrusivePtr_t<IObjectNode_t> retVal = addressSpace_->CreateObject(*nodeId, result);
  if (result.IsBad() || !retVal.is_set())
  {
    result = OpcUa_BadUnexpectedError;
    return empty;
  }

  result = HelperBase_t::UpdateAttributes(nodeId->NamespaceIndex().Value(), browseName, *retVal);
  if (result.IsBad())
  {
    return empty;
  }

  result = AddressSpaceUtilities_t::CreateHasTypeDefintion(*addressSpace_, retVal, hasTypeReferenceId);
  if (result.IsBad())
  {
    return empty;
  }

  return retVal;
}

IntrusivePtr_t<IMethodNode_t> HelperBase_t::CreateMethod(IntrusivePtr_t<const NodeId_t> nodeId,
                                                         IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                         const String_t& browseName,
                                                         bool executable,
                                                         Status_t& result)
{
  IntrusivePtr_t<IMethodNode_t> empty;
  if (!nodeId.is_set() || !addressSpace_.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  IntrusivePtr_t<IMethodNode_t> retVal = addressSpace_->CreateMethod(*nodeId, result);
  if (result.IsBad() || !retVal.is_set())
  {
    result = OpcUa_BadUnexpectedError;
    return empty;
  }

  result = HelperBase_t::UpdateAttributes(nodeId->NamespaceIndex().Value(), browseName, *retVal);
  if (result.IsBad())
  {
    return empty;
  }

  result = retVal->Executable(executable);
  if (result.IsBad())
  {
    return empty;
  }

  return retVal;
}

IntrusivePtr_t<IVariableNode_t> HelperBase_t::Create(IntrusivePtr_t<const NodeId_t> nodeId,
                                                     uint32_t dataTypeId,
                                                     IntrusivePtr_t<IAddressSpace_t>& addressSpace_,
                                                     const String_t& browseName,
                                                     uint32_t hasTypeReferenceId,
                                                     int32_t valueRank,
                                                     Status_t& result)
{
  IntrusivePtr_t<IVariableNode_t> empty;
  if (!nodeId.is_set() || !addressSpace_.is_set())
  {
    result = OpcUa_BadInvalidArgument;
    return empty;
  }

  IntrusivePtr_t<IVariableNode_t> retVal = addressSpace_->CreateVariable(*nodeId, result);
  if (result.IsBad() || !retVal.is_set())
  {
    result = OpcUa_BadUnexpectedError;
    return empty;
  }

  result = HelperBase_t::UpdateAttributes(nodeId->NamespaceIndex().Value(), *addressSpace_, browseName, dataTypeId, valueRank, retVal);
  if (result.IsBad())
  {
    return empty;
  }

  result = AddressSpaceUtilities_t::CreateHasTypeDefintion(*addressSpace_, retVal, hasTypeReferenceId);
  if (result.IsBad())
  {
    return empty;
  }

  return retVal;
}

Status_t HelperBase_t::CreateProperty(HelperBase_t& sourceNode,
                                      uint32_t numericId,
                                      const char* browseName_,
                                      uint32_t dataTypeId,
                                      IntrusivePtr_t<IVariableNode_t>& propertyNode)
{
  if (propertyNode.is_set())
  {
    return OpcUa_Good;
  }

  if (!sourceNode.node.is_set() || !sourceNode.node->NodeId().is_set() || !sourceNode.addressSpace.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  Status_t status = OpcUa_BadNotSupported;
  IntrusivePtr_t<const NodeId_t> propertyNodeId;
  IntrusivePtr_t<const NodeId_t> sourceNodeId = sourceNode.node->NodeId();

  if (numericId > 0)
  {
    if (sourceNodeId->NodeIdIdentiferType() != NodeId_t::NODEID_IDENTIFIER_NUMERIC)
    {
      return status;
    }
  }
  else
  {
    if (sourceNodeId->NodeIdIdentiferType() == NodeId_t::NODEID_IDENTIFIER_NUMERIC)
    {
      return status;
    }
  }

  switch (sourceNodeId->NodeIdIdentiferType())
  {
  case NodeId_t::NODEID_IDENTIFIER_NUMERIC:
    status = AddressSpaceUtilities_t::GenerateNumericNodeId(sourceNodeId->NamespaceIndex().Value(), numericId, propertyNodeId);
    break;

  case NodeId_t::NODEID_IDENTIFIER_STRING:
    status = HelperBase_t::GenerateStringNodeId(*sourceNode.node->NodeId(), browseName_, propertyNodeId);
    break;

  case NodeId_t::NODEID_IDENTIFIER_GUID:
    {
      Guid_t nodeId;
      status = nodeId.CopyFrom(sourceNode.node->NodeId()->IdentiferBase());
      if (status.IsBad())
      {
        UASDK_RETURN_BAD_STATUS(status.Value());
      }

      status = HelperBase_t::GenerateOpaqueNodeId(sourceNode.node->NodeId()->NamespaceIndex().Value(),
                                                  nodeId.Value(),
                                                  nodeId.GUID_LENGTH,
                                                  browseName_,
                                                  propertyNodeId);
    }
    break;

  case NodeId_t::NODEID_IDENTIFIER_OPAQUE:
    {
      ByteString_t nodeId;
      status = nodeId.CopyFrom(sourceNode.node->NodeId()->IdentiferBase());
      if (status.IsBad())
      {
        UASDK_RETURN_BAD_STATUS(status.Value());
      }

      status = HelperBase_t::GenerateOpaqueNodeId(sourceNode.node->NodeId()->NamespaceIndex().Value(),
                                                  nodeId.Data(),
                                                  nodeId.Length(),
                                                  browseName_,
                                                  propertyNodeId);
    }
    break;

  default:
    break;
  }

  if (status.IsBad() || !propertyNodeId.is_set())
  {
    return status;
  }

  String_t browseName;
  status = browseName.CopyFrom(browseName_);
  if (status.IsBad())
  {
    return status;
  }

  int32_t valueRank_ = -2;
  propertyNode = HelperBase_t::Create(propertyNodeId, dataTypeId, sourceNode.addressSpace, browseName, OpcUaId_PropertyType, valueRank_, status);
  if (status.IsBad() || !propertyNode.is_set())
  {
    return status;
  }

  //BrowseName should have the namesapce index as 0 for properties
  if (propertyNode->BrowseName().is_set())
  {
    IntrusivePtr_t<QualifiedName_t> browseName = new SafeRefCount_t<QualifiedName_t>();
    if (!browseName.is_set())
    {
      return OpcUa_BadOutOfMemory;
    }
    status = browseName->CopyFrom(*propertyNode->BrowseName());
    if (status.IsBad())
    {
      return status;
    }
    browseName->NamespaceIndex().Value(0);
    status = propertyNode->BrowseName(browseName);
    if (status.IsBad())
    {
      return status;
    }
  }

  propertyNode->Hide(false);

  //Create References
  status = AddressSpaceUtilities_t::CreateReference(*(sourceNode.addressSpace), sourceNode.node, propertyNode, OpcUaId_HasProperty);
  if (status.IsBad())
  {
    return status;
  }

  return OpcUa_Good;
}

Status_t HelperBase_t::CreateAndAssignDataValue(IntrusivePtr_t<IVariableNode_t> node_,
                                                IntrusivePtr_t<BaseDataType_t>& value,
                                                DateTime_t& sourceTimeStamp_)
{
  if (!node_.is_set() || !value.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  Status_t status;
  IntrusivePtr_t<DataValue_t> dataValue(new SafeRefCount_t<DataValue_t>());
  if (!dataValue.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  IntrusivePtr_t<DateTime_t> timeStamp(new SafeRefCount_t<DateTime_t>());
  if (!timeStamp.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  if (sourceTimeStamp_.Value() > 0)
  {
    timeStamp->Value(sourceTimeStamp_.Value());
    dataValue->SourceTimestamp() = timeStamp;   //Assign SourceTimestamp
  }

  dataValue->Value() = value;
  
  IntrusivePtr_t<StatusCode_t> statusCode_ = new SafeRefCount_t<StatusCode_t>();
  if (!statusCode_.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  statusCode_->Value().Value(OpcUa_Good);
  dataValue->StatusCode() = statusCode_;

  if (node_->Value().is_set() || node_->CanWriteValueSynchronously() != true)
  {
    node_->Value(dataValue);
  }
  else
  {
    Array_t<IndexRange_t> indexRange;
    uint32_t transactionId = 0;
    uint32_t timeoutHint = 0;
    IntrusivePtr_t<DiagnosticInfo_t> diagInfo;
    status = node_->WriteValue(indexRange, dataValue, transactionId, timeoutHint, diagInfo);
  }

  return status;
}

Status_t HelperBase_t::CreatePropertyAndAssignValue(HelperBase_t& sourceNode,
                                                    uint32_t numericId,
                                                    const char* browseName_,
                                                    uint32_t dataTypeId,
                                                    IntrusivePtr_t<BaseDataType_t> destinationValue,
                                                    const BaseDataType_t& sourceValue,
                                                    IntrusivePtr_t<IVariableNode_t>& propertyNode)  
{
  if (!destinationValue.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  Status_t status = HelperBase_t::CreateProperty(sourceNode, numericId, browseName_, dataTypeId, propertyNode);
  if (status.IsBad())
  {
    return status;
  }

  status = destinationValue->CopyFrom(sourceValue);
  if (status.IsBad())
  {
    return status;
  }

  DateTime_t sourceTime_(UASDK_datetime());
  status = HelperBase_t::CreateAndAssignDataValue(propertyNode, destinationValue, sourceTime_);
  if (status.IsBad())
  {
    return status;
  }

  return status;
}

/*
 * public function definition
 */
HelperBase_t::~HelperBase_t()
{
  if (deleteNode && addressSpace.is_set())
  {
    Status_t status = AddressSpaceUtilities_t::RemoveAllInverseReferences(node, *addressSpace);

    if (node.is_set() && node->NodeId().is_set())
    {
      node->ReferencesRemoveAllReferences();

      addressSpace->RemoveNode(*(node->NodeId()));
    }

    UASDK_UNUSED(status);
  }
}

void HelperBase_t::Hide(bool value)
{
  node->Hide(value);
}

void HelperBase_t::RemoveNodesOnDeletion(bool value)
{
  deleteNode = value;
}

char HelperBase_t::StringNodeIdSeparator(void)
{
  return stringNodeIdSeperator;
}

void HelperBase_t::StringNodeIdSeparator(char separator)
{
  stringNodeIdSeperator = separator;
}

IntrusivePtr_t<INode_t> HelperBase_t::Node(void)
{
  return node;
}

IntrusivePtr_t<const INode_t> HelperBase_t::Node(void) const
{
  return node;
}

} //namespace uasdk

#endif  //UASDK_USE_HELPERS