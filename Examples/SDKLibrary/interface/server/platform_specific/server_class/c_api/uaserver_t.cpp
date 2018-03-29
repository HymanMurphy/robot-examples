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

#include "uaserver_t.h"
#if (UASDK_INCLUDE_SERVER)
#if (UASDK_INCLUDE_SERVER_C_API > 0)

#include "icertificate_private_key_password_provider_t.h"
#include "icertificate_rejected_list_listener_t.h"
#include "ilog_listener_t.h"
#include "imonitored_item_listener_t.h"
#include "inode_method_handler_t.h"
#include "inode_value_attribute_reader_writer_t.h"
#include "ioperation_complete_listener_t.h"
#include "iregister_node_listener_t.h"
#include "iserver_state_listener_t.h"
#include "ithread_pool_t.h"
#include "itimer_provider_t.h"
#include "itransaction_listener_t.h"
#include "iuser_permissions_provider_t.h"
#include "safe_ref_count_t.h"
#include "iserver_configuration_t.h"
#include "opcua_build_info_t.h"
#include "opcua_message_security_mode_t.h"
#include "opcua_user_token_policy_t.h"
#include "iaddress_space_t.h"
#include "certificate_generation_parameters_t.h"
#include "iserver_core_t.h"
#include "intrusive_ptr_t.h"
#include "irunnable_t.h"
#include "timer_provider_t.h"
#include "thread_pool_t.h"
#include "utilities.h"
#include <stdio.h>
#include <time.h>

#include "address_space_utilities_t.h"
#include "opcua_array_ua_t.h"
#include "opcua_string_t.h"
#include "localizable_text_translate_for_c_api_t.h"
#include "opcua_qualified_name_t.h"
#include "ua_server_config.h"
#include "value_attribute_reader_writer_for_c_api.h"
#include "localizable_text_stored_t.h"

#include "file_ua_t.h"
#include "analog_item_t.h"
#include "two_state_discrete_t.h"
#include "multi_state_discrete_t.h"
#include "opcua_range_t.h"
#include "opcua_eu_information_t.h"
#include "file_t.h"

#ifdef _WIN32
#include <WinSock2.h>
#endif // _WIN32

#if (UASDK_INCLUDE_EVENTS > 0)
#include "event_helper_t.h"
#include "system_status_change_event_type_data_t.h"
#endif

using namespace uasdk;

#if (UASDK_DEBUG > 0)
#include <cstdio>

IntrusivePtr_t<ILogListener_t> UAServer_t::logListener;

class LogListener_t : public ILogListener_t, public Allocatable_t
{
private:
  static const uint32_t BUF_SIZE = 256;

  UA_Log_severity_t GetLevel(LogLevel_t logLevel) const
  {
    switch (logLevel)
    {
    case LOG_LEVEL_INFORMATION:
    case LOG_LEVEL_WARNING:
    	return UA_LOG_SEVERITY_INFO;

    case LOG_LEVEL_ERROR:
    case LOG_LEVEL_CRITICAL:
    default:
    	return UA_LOG_SEVERITY_ERROR;
    }
  }

public:
  void LogMessage(LogLevel_t logLevel, const char* format, va_list& args) const
  {
    char buf[BUF_SIZE];
    const char* filename = "No filename";

    vsnprintf(buf, BUF_SIZE, format, args);

    UA_Log_severity_t severity = GetLevel(logLevel);

    UAServer_Callback_log(severity,
        UASDK_datetime(),
		filename,
        0,
		UA_LOG_PAYLOAD_CSTRING,
        buf,
        0);
  }

  void LogMessage(LogLevel_t logLevel, const char* functionName, int lineNumber, const char* format, va_list& args) const
  {
    char buf[BUF_SIZE];

    vsnprintf(buf, BUF_SIZE, format, args);

    UA_Log_severity_t severity = GetLevel(logLevel);

    UAServer_Callback_log(severity,
        UASDK_datetime(),
		functionName,
		lineNumber,
		UA_LOG_PAYLOAD_CSTRING,
        buf,
        0);
  }

};
#endif

namespace uasdk
{

class OperationCompleteListener_t : public IOperationCompleteListener_t, public Allocatable_t
{
private:
  IntrusivePtr_t<IThreadPool_t> threadPool;
  bool isComplete;
  Status_t result;

public:
  OperationCompleteListener_t() : isComplete(false){}

  Status_t Initialise(IntrusivePtr_t<IThreadPool_t>& threadPool_)
  {
    UASDK_ASSERT(threadPool_.is_set());
    threadPool = threadPool_;
    return OpcUa_Good;
  }

  Status_t WaitForResult(void)
  {
    Status_t status;
    do
    {
      if (isComplete)
      {
        return OpcUa_Good;
      }
      status = threadPool->Operate();

    } while (status.IsGood());

    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  virtual void OperationComplete(Status_t result_)
  {
    result = result_;
    isComplete = true;
  }

};

Status_t UAServer_t::AddEndpoints(IntrusivePtr_t<IServerConfiguration_t> serverConfig,
  uint64_t policy,
  SecurityPolicy_t endpointPolicy,
  MessageSecurityMode_t::Enum_t mode)
{
  Status_t result;
  if (policy)
  {
    UserIdentityTokenType_t::Enum_t userTokenType;
    SecurityPolicy_t userPolicy;
    for (int i = 0; i < 9; i++)
    {
      if (policy & ((uint64_t)1 << i))
      {
        if (i == 0)
        {
          userTokenType = UserIdentityTokenType_t::OPCUA_USER_IDENTITY_TOKEN_TYPE_ANONYMOUS;
          userPolicy = SECURITY_POLICY_NONE;
        }
        else if (i < 5)
        {
          userTokenType = UserIdentityTokenType_t::OPCUA_USER_IDENTITY_TOKEN_TYPE_USERNAME;
          userPolicy = (SecurityPolicy_t)i;
        }
        else if (i < 9)
        {
          userTokenType = UserIdentityTokenType_t::OPCUA_USER_IDENTITY_TOKEN_TYPE_CERTIFICATE;
          userPolicy = (SecurityPolicy_t)(i - 4);
        }
        else
        {
          break;
        }
        result = serverConfig->AddEndpointUserTokenPolicy(endpointPolicy,
          mode,
          userTokenType,
          userPolicy);
        if (result.IsBad())
        {
          return result;
        }
      }
    }
  }
  return OpcUa_Good;
}

uasdk::IntrusivePtr_t<uasdk::TcpConnectionPlatform_t> UAServer_t::GetConnection(uint64_t connectionId)
{
  connections.ResetCurrent();
  IntrusivePtr_t<TcpConnectionPlatform_t> connection;

  do
  {
    connection = connections.GetNext();
    if (connection.is_set())
    {
      if (connection->ConnectionId() == connectionId)
      {
        return connection;
      }
    }
  } while (connection.is_set());
  return connection;
}

Status_t UAServer_t::UpdateLocaleIdArray(void)
{
  Status_t status;

  if (!localeIdArray.is_set())
  {
    if (!core.is_set() || !core->GetConfiguration(status).is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
    }

    localeIdArray = core->GetConfiguration(status)->LocaleIds();
  }

  return status;
}

Status_t UAServer_t::UpdateAddressSpaceVariable(void)
{
  Status_t status;

  if (!addressSpace.is_set())
  {
    if (!core.is_set() || !core->GetConfiguration(status).is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
    }

    addressSpace = core->GetConfiguration(status)->AddressSpace();
    if (!addressSpace.is_set() || status.IsBad())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
    }
  }

  return status;
}

Status_t UAServer_t::RemoveStandardNode(uint32_t nodeId_)
{
  if (!addressSpace.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  IntrusivePtr_t<NodeIdNumeric_t> nodeId = new SafeRefCount_t<NodeIdNumeric_t>();
  if (!nodeId.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  nodeId->NamespaceIndex() = 0;
  nodeId->Identifer() = nodeId_;

  return addressSpace->RemoveNode(*nodeId);
}

Status_t UAServer_t::CreateObjectsFolder(void)
{
  if (!addressSpace.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  IntrusivePtr_t<NodeIdNumeric_t> objectsFolderId = new SafeRefCount_t<NodeIdNumeric_t>();
  if (!objectsFolderId.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  objectsFolderId->NamespaceIndex() = 0;
  objectsFolderId->Identifer() = OpcUaId_ObjectsFolder;

  Status_t status = addressSpace->RemoveNode(*objectsFolderId);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  IntrusivePtr_t<INode_t> objectsFolder = addressSpace->CreateObject(objectsFolderId, status);
  if (!objectsFolder.is_set())
  {
    return status;
  }
  objectsFolder->Hide(false);

  status = AddressSpaceUtilities_t::CreateHasTypeDefintion(*addressSpace, objectsFolder, OpcUaId_FolderType);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  IntrusivePtr_t<QualifiedName_t> browseName = new SafeRefCount_t<QualifiedName_t>();
  if (!browseName.is_set())
  {
    return status;
  }
  browseName->NamespaceIndex() = 0;
  status = browseName->Name().CopyFrom("Objects");
  if (status.IsBad())
  {
    return status;
  }
  status = objectsFolder->BrowseName(browseName);

  IntrusivePtr_t<LocalizableTextStored_t> displayName = new SafeRefCount_t<LocalizableTextStored_t>();
  if (!displayName.is_set())
  {
    return status;
  }
  IntrusivePtr_t<LocalizedText_t> displayNameValue = new SafeRefCount_t<LocalizedText_t>();
  if (!displayNameValue.is_set())
  {
    return status;
  }
  status = displayNameValue->Text().CopyFrom(browseName->Name());
  if (status.IsBad())
  {
    return status;
  }
  status = displayName->AddText(displayNameValue);
  if (status.IsBad())
  {
    return status;
  }
  status = objectsFolder->DisplayName(displayName);
  if (status.IsBad())
  {
    return status;
  }

  //Creating the reference between the Object folder and Server Object with type Organizes
  IntrusivePtr_t<NodeIdNumeric_t> targetId = new SafeRefCount_t<NodeIdNumeric_t>();
  if (!targetId.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  targetId->NamespaceIndex() = 0;
  targetId->Identifer() = OpcUaId_Server;

  IntrusivePtr_t<INode_t> serverObject = addressSpace->FindNode(*targetId, status);
  if (status.IsBad() || !serverObject.is_set())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  IntrusivePtr_t<NodeIdNumeric_t> refId = new SafeRefCount_t<NodeIdNumeric_t>();
  if (!refId.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  refId->NamespaceIndex() = 0;
  refId->Identifer() = OpcUaId_Organizes;

  objectsFolder->ReferencesCreateReference(refId, serverObject->NodeId(), false, status);
  
  return status;
}

Status_t UAServer_t::UpdateNamespaceIndexForAlias(void)
{
  if (!addressSpace.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  Status_t status;
  NodeIdNumeric_t uriNode(0, OpcUaId_Server_NamespaceArray);
  IntrusivePtr_t<IVariableNode_t> node = addressSpace->FindVariableNode(uriNode, status);
  if (status.IsBad() || !node.is_set())
  {
    status = OpcUa_BadUnexpectedError;
  }
  
  if (!node.is_set() || !node->Value().is_set() || !node->Value()->Value().is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  IntrusivePtr_t< const ArrayUA_t<String_t> > uris = RuntimeCast< const ArrayUA_t<String_t>* >(*(node->Value()->Value()));
  if (!uris.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  if (uris->Count() < 1)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  namespaceIndexForAlias = static_cast<uint16_t>(uris->Count());

  return OpcUa_Good;
}

Status_t UAServer_t::CreateAliasIdAndNodeId(const UA_Base_t& base_config, IntrusivePtr_t<const NodeId_t>& aliasId, IntrusivePtr_t<const NodeId_t>& nodeId)
{
  if (!base_config.namespace_index)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  if (!addressSpace.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  Status_t status;
  //Get the NameSpaceIndex for Alias!
  if (!namespaceIndexForAlias)
  {
    status = UpdateNamespaceIndexForAlias();
    if (status.IsBad() || !namespaceIndexForAlias)
    {
      UASDK_RETURN_BAD_STATUS(status.Value());
    }
  }

  //Create Numeric Id for Alias
  status = uasdk::AddressSpaceUtilities_t::GenerateNumericNodeId(namespaceIndexForAlias, static_cast<uint32_t>(base_config.node_handle), aliasId);
  if (status.IsBad() || !aliasId.is_set())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  //Create NodeId
  switch (base_config.node_id.identifier_type)
  {
    case opcua_node_encoding_numeric:
    {
      if (base_config.node_id.numeric_identifier <= 0)
      {
        UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
      }

      status = uasdk::AddressSpaceUtilities_t::GenerateNumericNodeId(base_config.namespace_index, base_config.node_id.numeric_identifier, nodeId);
      if (status.IsBad() || !nodeId.is_set())
      {
        UASDK_RETURN_BAD_STATUS(status.Value());
      }
    }
    break;

    case opcua_node_encoding_string:
    {
      if ((!base_config.node_id.string_identifier.data) || (base_config.node_id.string_identifier.length < 0))
      {
        UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
      }

      String_t stringId;
      status = stringId.CopyFrom((const char*)(base_config.node_id.string_identifier.data), base_config.node_id.string_identifier.length + 1);
      if (status.IsBad())
      {
        UASDK_RETURN_BAD_STATUS(status.Value());
      }

      status = uasdk::AddressSpaceUtilities_t::GenerateStringNodeId(base_config.namespace_index, stringId, nodeId);
      if (status.IsBad() || !nodeId.is_set())
      {
        UASDK_RETURN_BAD_STATUS(status.Value());
      }
    }
    break;

    case opcua_node_encoding_guid:
    {
      if (!base_config.node_id.guid_identifier)
      {
        UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
      }

      status = uasdk::AddressSpaceUtilities_t::GenerateGuidNodeId(base_config.namespace_index, base_config.node_id.guid_identifier, nodeId);
      if (status.IsBad() || !nodeId.is_set())
      {
        UASDK_RETURN_BAD_STATUS(status.Value());
      }
    }
    break;

    case opcua_node_encoding_bytestring:
    {
      ByteString_t id_;
      status = id_.CopyFrom((const uint8_t*)(&base_config.node_handle), sizeof(base_config.node_handle));
      if(status.IsBad())
      {
        UASDK_RETURN_BAD_STATUS(status.Value());
      }

      status = uasdk::AddressSpaceUtilities_t::GenerateOpaqueNodeId(base_config.namespace_index, id_, nodeId);
      if (status.IsBad() || !nodeId.is_set())
      {
        UASDK_RETURN_BAD_STATUS(status.Value());
      }
    }
    break;

    default:
      return OpcUa_BadUnexpectedError;
  }

  //Check for the duplicate node id
  IntrusivePtr_t<const INode_t> temp = addressSpace->FindNode(*nodeId, status);
  if (temp.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadNodeIdExists);
  }
  temp = addressSpace->FindNode(*aliasId, status);
  if (temp.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadNodeIdExists);
  }

  return OpcUa_Good;
}

IntrusivePtr_t<const NodeId_t> UAServer_t::GetDataType(UA_Value_type_t type, Status_t& result)
{
  IntrusivePtr_t<NodeIdNumeric_t> dataType(new SafeRefCount_t<NodeIdNumeric_t>());
  if (!dataType.is_set())
  {
    result = OpcUa_BadOutOfMemory;
    return dataType;
  }
  dataType->NamespaceIndex().Value(0);

  switch (type)
  {
    case UA_TYPE_Boolean:
      dataType->Identifer().Value(OpcUaId_Boolean);
      break;

    case UA_TYPE_SByte:
      dataType->Identifer().Value(OpcUaId_SByte);
      break;

    case UA_TYPE_Byte:
      dataType->Identifer().Value(OpcUaId_Byte);
      break;

    case UA_TYPE_Int16:
      dataType->Identifer().Value(OpcUaId_Int16);
      break;

    case UA_TYPE_UInt16:
      dataType->Identifer().Value(OpcUaId_UInt16);
      break;

    case UA_TYPE_Int32:
      dataType->Identifer().Value(OpcUaId_Int32);
      break;

    case UA_TYPE_UInt32:
      dataType->Identifer().Value(OpcUaId_UInt32);
      break;

    case UA_TYPE_Int64:
      dataType->Identifer().Value(OpcUaId_Int64);
      break;

    case UA_TYPE_UInt64:
      dataType->Identifer().Value(OpcUaId_UInt64);
      break;

    case UA_TYPE_Float:
      dataType->Identifer().Value(OpcUaId_Float);
      break;

    case UA_TYPE_Double:
      dataType->Identifer().Value(OpcUaId_Double);
      break;

    case UA_TYPE_String:
      dataType->Identifer().Value(OpcUaId_String);
      break;

    case UA_TYPE_DateTime:
      dataType->Identifer().Value(OpcUaId_DateTime);
      break;

    case UA_TYPE_Guid:
      dataType->Identifer().Value(OpcUaId_Guid);
      break;

    case UA_TYPE_ByteString:
      dataType->Identifer().Value(OpcUaId_ByteString);
      break;

    case UA_TYPE_XmlElement:
      dataType->Identifer().Value(OpcUaId_XmlElement);
      break;

    default:
      {
        IntrusivePtr_t<const NodeId_t> empty;
        result = OpcUa_BadInvalidArgument;
        return empty;
      }
      break;
  }

  result = OpcUa_Good;
  return dataType;
}

Status_t UAServer_t::CreateLocaleTextTranslator(uintptr_t handle, IntrusivePtr_t<const ILocalizableText_t>& result)
{
  Status_t status = UpdateLocaleIdArray();
  if (!localeIdArray.is_set() || status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  if (handle)
  {
    IntrusivePtr_t<LocalizableTextTranslateForCAPI_t> localizableText(new SafeRefCount_t<LocalizableTextTranslateForCAPI_t>());
    if (!localizableText.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }

    localizableText->AddTextHandle(handle);
    localizableText->AddLocaleIdArray(localeIdArray);

    result = localizableText;
  }

  return OpcUa_Good;
}

Status_t UAServer_t::CreateTranslatorAndGetEnglishText(uintptr_t handle, IntrusivePtr_t<const ILocalizableText_t>& translator, String_t& result)
{
  if (!handle)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  Status_t status = CreateLocaleTextTranslator(handle, translator);
  if (status.IsBad() || !translator.is_set())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  //for English Text
  ArrayUA_t<String_t> locales;
  status = locales.Initialise(1);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  IntrusivePtr_t<String_t> locale(new SafeRefCount_t<String_t>());
  if (!locale.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  status = locale->CopyFrom("en");
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
  locales[0] = locale;

  IntrusivePtr_t<const LocalizedText_t> browseName_ = translator->GetLocalizedText(locales, status);
  if (status.IsBad() || !browseName_.is_set())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  return result.CopyFrom(browseName_->Text());
}

Status_t UAServer_t::UpdateDescriptionTranslator(IntrusivePtr_t<INode_t> node, uintptr_t handle)
{
  Status_t status;
  if (handle)
  {
    IntrusivePtr_t<const ILocalizableText_t> description;

    status = CreateLocaleTextTranslator(handle, description);
    if (status.IsBad() || !description.is_set())
    {
      UASDK_RETURN_BAD_STATUS(status.Value());
    }

    status = node->Description(description);
    if (status.IsBad())
    {
      UASDK_RETURN_BAD_STATUS(status.IsBad());
    }
  }

  return status;
}

Status_t UAServer_t::CreateBrowseNameDisplayNameAndDescription(IntrusivePtr_t<INode_t> node, const UA_Base_t& base_config)
{
  if (!node.is_set() || !node->NodeId().is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  IntrusivePtr_t<const ILocalizableText_t> displayNameTranslator;
  String_t browseName_;
  Status_t status = CreateTranslatorAndGetEnglishText(base_config.display_name_handle, displayNameTranslator, browseName_);
  if(status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  IntrusivePtr_t<QualifiedName_t> browseName(new SafeRefCount_t<QualifiedName_t>());
  if (!browseName.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  browseName->NamespaceIndex().Value(node->NodeId()->NamespaceIndex().Value());
  status = browseName->Name().CopyFrom(browseName_);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
  
  status = node->BrowseName(browseName);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  //Disaply Name
  status = node->DisplayName(displayNameTranslator);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  return UpdateDescriptionTranslator(node, base_config.description_handle);
}

Status_t UAServer_t::CreateApplicationContextForUserVisibility(uint16_t userVisibility_, IntrusivePtr_t<INode_t> node_)
{
  if (!node_.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  IntrusivePtr_t<ApplicationContext_t> applicationContext(new SafeRefCount_t<ApplicationContext_t>());
  if (!applicationContext.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  applicationContext->UserVisibility(userVisibility_);

  IntrusivePtr_t<INodeApplicationContext_t> appContext = applicationContext;
  return node_->ApplicationContextHandle(appContext);
}

Status_t UAServer_t::CreateNodeAndItsAttributes(uint32_t nodeType,
                                                const UA_Base_t& baseConfig,
                                                IntrusivePtr_t<INode_t>& node)
{
  if (!baseConfig.node_handle || !baseConfig.display_name_handle || !baseConfig.namespace_index)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  if (!addressSpace.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  //Create Node Id and Alias Id
  uasdk::IntrusivePtr_t<const uasdk::NodeId_t> aliasId;
  uasdk::IntrusivePtr_t<const uasdk::NodeId_t> nodeId;

  Status_t status = CreateAliasIdAndNodeId(baseConfig, aliasId, nodeId);
  if (status.IsBad() || !aliasId.is_set() || !nodeId.is_set())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  switch (nodeType)
  {
    case OpcUaId_VariableNode:
      {
        node = addressSpace->CreateVariable(nodeId, status);
        if (status.IsBad() || !node.is_set())
        {
          UASDK_RETURN_BAD_STATUS(status.Value());
        }
        node->Hide(false);
      }
      break;

    case OpcUaId_ObjectNode:
      {
        node = addressSpace->CreateObject(nodeId, status);
        if (status.IsBad() || !node.is_set())
        {
          UASDK_RETURN_BAD_STATUS(status.Value());
        }
        node->Hide(false);
      }
      break;

    case OpcUaId_ViewNode:
      {
        node = addressSpace->CreateView(nodeId, status);
        if (status.IsBad() || !node.is_set())
        {
          UASDK_RETURN_BAD_STATUS(status.Value());
        }
        node->Hide(false);
      }
      break;

    case OpcUaId_MethodNode:
      {
        node = addressSpace->CreateMethod(nodeId, status);
        if (status.IsBad() || !node.is_set())
        {
          UASDK_RETURN_BAD_STATUS(status.Value());
        }
        node->Hide(false);
      }
      break;

    case OpcUaId_DataTypeNode:
      {
        node = addressSpace->CreateDataType(nodeId, status);
        if (status.IsBad() || !node.is_set())
        {
          UASDK_RETURN_BAD_STATUS(status.Value());
        }
        node->Hide(false);
      }
      break;

    case OpcUaId_VariableTypeNode:
      {
        node = addressSpace->CreateVariableType(nodeId, status);
        if (status.IsBad() || !node.is_set())
        {
          UASDK_RETURN_BAD_STATUS(status.Value());
        }
        node->Hide(false);
      }
      break;

    case OpcUaId_ObjectTypeNode:
      {
        node = addressSpace->CreateObjectType(nodeId, status);
        if (status.IsBad() || !node.is_set())
        {
          UASDK_RETURN_BAD_STATUS(status.Value());
        }
        node->Hide(false);
      }
      break;

    case OpcUaId_ReferenceTypeNode:
      {
        node = addressSpace->CreateReferenceType(nodeId, status);
        if (status.IsBad() || !node.is_set())
        {
          UASDK_RETURN_BAD_STATUS(status.Value());
        }
        node->Hide(false);
      }
      break;

    default:
      return OpcUa_BadInvalidArgument;
  }

  status = addressSpace->AddNodeAlias(*(node->NodeId()), aliasId);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  //DisplayName and Description Attributes
  status = CreateBrowseNameDisplayNameAndDescription(node, baseConfig);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  //WriteMask
  WriteMask_t writeMask(0x00);
  node->WriteMask(writeMask);

  //UserVisibility
  return CreateApplicationContextForUserVisibility(baseConfig.user_visibility, node);
}

Status_t UAServer_t::UpdateVariableNodeAttributes(IntrusivePtr_t<IVariableNode_t> node, const UA_BaseDataVariable_t& data)
{
  if (!node.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }
  if (!addressSpace.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  Status_t status;
  //Value Attribute
  IntrusivePtr_t<const NodeId_t> dataType = GetDataType(data.value_type, status);
  if (status.IsBad() || !dataType.is_set())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  status = node->DataType(dataType);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  //Set Value Rank
  int32_t valueRannk;
  valueRannk = (data.max_array_length == 0) ? -1 : 0;
  node->ValueRank(valueRannk);

  //Array Size
  if (data.max_array_length > 0)
  {
    IntrusivePtr_t<UInt32_t> size(new SafeRefCount_t<UInt32_t>());
    if (!size.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }
    size->Value(data.max_array_length);

    IntrusivePtr_t< ArrayUA_t<UInt32_t> > dimensionArray(new SafeRefCount_t< ArrayUA_t<UInt32_t> >());
    if (!dimensionArray.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }

    status = dimensionArray->Initialise(1);
    if (status.IsBad())
    {
      UASDK_RETURN_BAD_STATUS(status.Value());
    }
    (*dimensionArray)[0] = size;

    node->ArrayDimensions(dimensionArray);
  }

  //AccessLevel
  AccessLevel_t accessLevel(0x00);
  if (data.user_read_permissions > 0)
  {
    accessLevel.Value(0x01);
    if (data.user_write_permissions > 0)
    {
      accessLevel.Value(0x03);
    }
  }
  node->AccessLevel(accessLevel);

  //Setting the Read and write permissions
  IntrusivePtr_t<INodeApplicationContext_t> context_ = node->ApplicationContextHandle();
  if (!context_.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  ApplicationContext_t& context = static_cast<ApplicationContext_t&> (*context_);
  context.UserReadPermission(data.user_read_permissions);
  context.UserWritePermission(data.user_write_permissions);

  //For Value Attribute Reader and Writer
  IntrusivePtr_t<ValueAttributeReaderWriterForCAPI_t> readerWriter(new SafeRefCount_t<ValueAttributeReaderWriterForCAPI_t>());
  if (!readerWriter.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  status = readerWriter->Initialize(data.base_config.node_handle, data.max_array_length, data.value_type, addressSpace);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  return node->ValueAttributeReaderWriter(readerWriter);
}

Status_t UAServer_t::CreateEssenstialsForHelpers(const UA_Base_t& baseConfig,
                                                 IntrusivePtr_t<const NodeId_t>& aliasId,
                                                 IntrusivePtr_t<const NodeId_t>& nodeId,
                                                 IntrusivePtr_t<const ILocalizableText_t>& displayNameTranslator,
                                                 String_t& browseName_)
{
  if (!addressSpace.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  Status_t status = CreateAliasIdAndNodeId(baseConfig, aliasId, nodeId);
  if (status.IsBad() || !nodeId.is_set() || !aliasId.is_set())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  return CreateTranslatorAndGetEnglishText(baseConfig.display_name_handle, displayNameTranslator, browseName_);
}

Status_t UAServer_t::UpdateEssentialsForHelper(const UA_BaseDataVariable_t& data,
                                               IntrusivePtr_t<const NodeId_t>& aliasId,
                                               IntrusivePtr_t<const ILocalizableText_t>& displayNameTranslator,
                                               IntrusivePtr_t<IVariableNode_t>& node_)
{
  if (!node_.is_set() || !node_->NodeId().is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  if (!addressSpace.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  Status_t status = addressSpace->AddNodeAlias(*(node_->NodeId()), aliasId);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  status = node_->DisplayName(displayNameTranslator);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  status = UpdateDescriptionTranslator(node_, data.base_config.description_handle);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  //User visibilty
  status = CreateApplicationContextForUserVisibility(data.base_config.user_visibility, node_);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  //Assign the proper access level
  if (data.user_write_permissions > 0)
  {
    AccessLevel_t accessLevel(node_->AccessLevel().Value() | 0x02);
    status = node_->AccessLevel(accessLevel);
    if (status.IsBad())
    {
      UASDK_RETURN_BAD_STATUS(status.Value());
    }
  }

  return UpdateVariableNodeAttributes(node_, data);
}

uint32_t UAServer_t::GenerateNumericId(uint16_t namespaceIndex_)
{
  uint32_t id_ = 0;
  while (!id_)
  {
    id_ = UASDK_pseudeo_random_number();

    Status_t status;
    NodeIdNumeric_t numericId_(namespaceIndex_, id_);
    IntrusivePtr_t<INode_t> temp = addressSpace->FindNode(numericId_, status);
    if (temp.is_set() || (status.Value() == OpcUa_BadNodeIdExists))
    {
      id_ = 0;
    }
  }

  return id_;
}

Status_t UAServer_t::CreatePropertyValuesForTwoStateDiscrete(uintptr_t handle, IntrusivePtr_t<const ILocalizableText_t>& translator, LocalizedText_t& result)
{
  String_t temp;
  Status_t status = CreateTranslatorAndGetEnglishText(handle, translator, temp);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
  status = result.Locale().CopyFrom("en");
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
  return result.Text().CopyFrom(temp);
}

#if ((UASDK_USE_HELPERS > 0) && (UASDK_USE_DATA_ACCESS_HELPERS > 0))
Status_t UAServer_t::CreateDefinitionAndValuePrecisionProperty(const UA_DataItem_t& dataItemConfig, DataItem_t& node_)
{
  Status_t status;
  UA_Base_t baseConfig = dataItemConfig.data_variable_config.base_config;
  if (dataItemConfig.use_definition != FALSE)
  {
    String_t defintion_;
    status = defintion_.CopyFrom((const char*)dataItemConfig.definition.data, (dataItemConfig.definition.length + 1));
    if (status.IsBad())
    {
      UASDK_RETURN_BAD_STATUS(status.Value());
    }

    if (baseConfig.node_id.identifier_type != opcua_node_encoding_numeric)
    {
      status = node_.CreateDefinitionProperty(defintion_);
    }
    else
    {
      uint32_t numericId = GenerateNumericId(baseConfig.namespace_index);
      status = node_.CreateDefinitionProperty(numericId, defintion_);
    }
    if (status.IsBad())
    {
      UASDK_RETURN_BAD_STATUS(status.Value());
    }
  }

  if (dataItemConfig.use_value_precision != FALSE)
  {
    if (baseConfig.node_id.identifier_type != opcua_node_encoding_numeric)
    {
      status = node_.CreateValuePrecisionProperty(dataItemConfig.value_precision);
    }
    else
    {
      uint32_t numericId = GenerateNumericId(baseConfig.namespace_index);
      status = node_.CreateValuePrecisionProperty(numericId, dataItemConfig.value_precision);
    }
    if (status.IsBad())
    {
      UASDK_RETURN_BAD_STATUS(status.Value());
    }
  }

  return status;
}
#endif  //#if (UASDK_USE_DATA_ACCESS_HELPERS > 0)

IntrusivePtr_t<const NodeId_t> UAServer_t::GetViewNodeId(uint16_t viewMask, Status_t& result)
{
  IntrusivePtr_t<const NodeId_t> empty;
  if (viewMask <= 1)
  {
    result = OpcUa_Good;
    return empty;
  }

  if (!addressSpace.is_set())
  {
    result = OpcUa_BadUnexpectedError;
    LOG_WARNING_WITH_LOCATION(OpcUa_BadUnexpectedError);
    return empty;
  }

  NodeIdNumeric_t viewFolderNodeId(0, 87);

  IntrusivePtr_t<INode_t> viewFolderNode = addressSpace->FindNode(viewFolderNodeId, result);
  if (!viewFolderNode.is_set() || result.IsBad())
  {
    LOG_WARNING_WITH_LOCATION(result.Value());
    return empty;
  }

  IntrusivePtr_t<const IIterator_t<IReference_t> > references = viewFolderNode->ReferencesGetConstIterator(result);
  if (!references.is_set() || result.IsBad())
  {
    LOG_WARNING_WITH_LOCATION(result.Value());
    return empty;
  }

  IntrusivePtr_t<IReference_t> reference;
  do
  {
    reference = references->Next();
    if (reference.is_set())
    {
      NodeIdNumeric_t refType(0, OpcUaId_Organizes);
      if ((reference->TypeId().is_set())&&(*reference->TypeId() == refType) && (!reference->IsInverse()))
      {
        IntrusivePtr_t<INode_t> viewNode = reference->TargetNode();
        if (viewNode.is_set() && (viewNode->NodeClass() == NodeClass_t::OPCUA_NODECLASS_VIEW) )
        {
          IntrusivePtr_t<INodeApplicationContext_t> context_ = viewNode->ApplicationContextHandle();
          if (!context_.is_set())
          {
            result = OpcUa_BadUnexpectedError;
            LOG_WARNING_WITH_LOCATION(OpcUa_BadUnexpectedError);
            return empty;
          }

          ApplicationContext_t& context = static_cast<ApplicationContext_t&>(*context_);

          if (context.UserVisibility() & viewMask)
          {
            result = OpcUa_Good;
            return viewNode->NodeId();
          }
        }
      }
    }
  } while (reference.is_set());

  result = OpcUa_BadViewIdUnknown;
  LOG_WARNING_WITH_LOCATION(OpcUa_BadViewIdUnknown);
  return empty;
}

Status_t UAServer_t::AddUri(const char* uri, uint32_t index, ArrayUA_t<String_t>& nameSpaceArray)
{
  if ( !uri || (index > (nameSpaceArray.Size() - 1) ))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  IntrusivePtr_t<String_t> data(new SafeRefCount_t<String_t>());
  if (!data.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  Status_t status = data->CopyFrom(uri);
  if (status.IsBad())
  {
    return status;
  }

  nameSpaceArray[index] = data;
  return status;
}

IntrusivePtr_t<IServerConfiguration_t> UAServer_t::CreateConfiguration(Status_t& result)
{
  return IServerCore_t::CreateConfiguration(result);
}

uasdk::IntrusivePtr_t<uasdk::IXmlNodesetIO_t> UAServer_t::CreateXmlNodesetIO(bool doNotAllowDuplicateNodeId, Status_t& result)
{
  return IServerCore_t::CreateXmlNodesetIO(doNotAllowDuplicateNodeId, result);
}

uasdk::IntrusivePtr_t<uasdk::IAddressSpace_t> UAServer_t::CreateAddressSpace(uint32_t numberOfBuckets, Status_t& result)
{
  return IServerCore_t::CreateAddressSpace(numberOfBuckets, result);
}

uasdk::Status_t UAServer_t::CreateAllocator(uint8_t* buffer, uint32_t bufferLengthInBytes, uint32_t maxAllocationSizeInBytes)
{
  return IServerCore_t::CreateAllocator(buffer, bufferLengthInBytes, maxAllocationSizeInBytes);
}

/*
 * Control methods
 */
Status_t UAServer_t::Initialise(IntrusivePtr_t<IServerConfiguration_t> configuration)
{
  #if (UASDK_USE_SYSTEM_HEAP == 0)
    if (!Allocatable_t::Allocator())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadConfigurationError);
    }
  #endif

  Status_t status;
  core = IServerCore_t::Create(status);
  if (!core.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  threadPool = new SafeRefCount_t<ThreadPool_t>();
  if (!threadPool.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  IntrusivePtr_t<TimerProvider_t> timerProvider_ = new SafeRefCount_t<TimerProvider_t>();
  if (!timerProvider_.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
    status = timerProvider_->Initialise();
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  timerProvider = timerProvider_;

  IntrusivePtr_t<OperationCompleteListener_t> callbackOpComplete = new SafeRefCount_t<OperationCompleteListener_t>();
  if (!callbackOpComplete.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  callbackOpComplete->Initialise(threadPool);

  status = core->Initialise(configuration, threadPool, timerProvider, callbackOpComplete);
  if (status.IsBad())
  {
    return status;
  }

  status = callbackOpComplete->WaitForResult();
  if (status.IsBad())
  {
    return status;
  }

#if (UASDK_USE_FILE_OBJECT_HELPERS > 0)
  fileTransferRouter.reset( new SafeRefCount_t<FileTransferRouter_t>());
  if (!fileTransferRouter.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
#endif

  status = UpdateAddressSpaceVariable();
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  status = CreateObjectsFolder();
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
  return OpcUa_Good;
}

Status_t UAServer_t::Start(const String_t& license)
{
  UASDK_UNUSED(license);
  IntrusivePtr_t<OperationCompleteListener_t> callbackOpComplete = new SafeRefCount_t<OperationCompleteListener_t>();
  if (!callbackOpComplete.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  callbackOpComplete->Initialise(threadPool);

  Status_t status = core->Start(callbackOpComplete);
  if (status.IsBad())
  {
    return status;
  }

  status = callbackOpComplete->WaitForResult();
  if (status.IsBad())
	{
		return status;
	}

#if (UASDK_INCLUDE_EVENTS > 0)
    IntrusivePtr_t<IServerConfiguration_t> configuration = core->GetConfiguration(status);
		if (status.IsBad() || !configuration.is_set())
		{
			UASDK_RETURN_BAD_STATUS(OpcUa_BadConfigurationError);
		}

		if (configuration->EventTypesActivationStatus() & ENABLE_SYSTEM_STATUS_CHANGE_EVENT_TYPE)
		{
			status = FireSystemStatusChangeEvent(ServerState_t::OPCUA_SERVER_STATE_RUNNING);
			if (status.IsBad())
			{
				//Log it
			}
		}
#endif //UASDK_INCLUDE_EVENTS

	return status;
}

Status_t UAServer_t::Stop(void)
{
  IntrusivePtr_t<OperationCompleteListener_t> callbackOpComplete = new SafeRefCount_t<OperationCompleteListener_t>();
  if (!callbackOpComplete.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  callbackOpComplete->Initialise(threadPool);

  Status_t status = core->Stop(callbackOpComplete);
  if (status.IsBad())
  {
    return status;
  }

#if (UASDK_INCLUDE_EVENTS > 0)
    Status_t result;
    IntrusivePtr_t<IServerConfiguration_t> configuration = core->GetConfiguration(result);
		if (result.IsBad() || !configuration.is_set())
		{
			UASDK_RETURN_BAD_STATUS(OpcUa_BadConfigurationError);
		}

		if (configuration->EventTypesActivationStatus() & ENABLE_SYSTEM_STATUS_CHANGE_EVENT_TYPE)
		{
			result = FireSystemStatusChangeEvent(ServerState_t::OPCUA_SERVER_STATE_SHUTDOWN);
			if (result.IsBad())
			{
				//Log it
			}
		}
#endif //UASDK_INCLUDE_EVENTS

  return callbackOpComplete->WaitForResult();
}

/*
 * Configuration methods
 */
IntrusivePtr_t<IServerConfiguration_t> UAServer_t::GetConfiguration(Status_t& result)
{
  if (core.is_set())
  {
    return core->GetConfiguration(result);
  }
  result = OpcUa_BadConfigurationError;
  IntrusivePtr_t<IServerConfiguration_t> empty;
  return empty;
}

/*
 * Security methods
 */
Status_t UAServer_t::SecurityValidateApplicationInstanceCertificate(SecurityPolicy_t securityPolicy)
{
  return core->SecurityValidateApplicationInstanceCertificate(securityPolicy);
}

Status_t UAServer_t::SecurityCreateSelfSignedApplicationInstanceCertificate(
    IntrusivePtr_t<const CertificateGenerationParameters_t> parameters)
{
  IntrusivePtr_t<OperationCompleteListener_t> callbackOpComplete = new SafeRefCount_t<OperationCompleteListener_t>();
  if (!callbackOpComplete.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  callbackOpComplete->Initialise(threadPool);

  Status_t status = core->SecurityCreateSelfSignedApplicationInstanceCertificate(parameters,
                                                                                 callbackOpComplete);
  if (status.IsBad())
  {
    return status;
  }

  status = callbackOpComplete->WaitForResult();
  return status;
}

Status_t UAServer_t::SecurityCreateCertificateDirectoryStores(void)
{
  IntrusivePtr_t<OperationCompleteListener_t> callbackOpComplete = new SafeRefCount_t<OperationCompleteListener_t>();
  if (!callbackOpComplete.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  callbackOpComplete->Initialise(threadPool);

  Status_t status = core->SecurityCreateCertificateDirectoryStores(callbackOpComplete);
  if (status.IsBad())
  {
    return status;
  }

  status = callbackOpComplete->WaitForResult();
  return status;
}

Status_t UAServer_t::SecurityRefreshApplicationCertificateDirectoryStores(void)
{
  IntrusivePtr_t<OperationCompleteListener_t> callbackOpComplete = new SafeRefCount_t<OperationCompleteListener_t>();
  if (!callbackOpComplete.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  callbackOpComplete->Initialise(threadPool);

  Status_t status = core->SecurityRefreshCertificateDirectoryStores(UA_CERTIFICATE_GROUP_DEFAULT_APPLICATION_GROUP,
                                                                    callbackOpComplete);
  if (status.IsBad())
  {
    return status;
  }

  status = callbackOpComplete->WaitForResult();
  return status;
}

Status_t UAServer_t::SecurityRefreshUserCertificateDirectoryStores(void)
{
  IntrusivePtr_t<OperationCompleteListener_t> callbackOpComplete = new SafeRefCount_t<OperationCompleteListener_t>();
  if (!callbackOpComplete.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  callbackOpComplete->Initialise(threadPool);

  Status_t status = core->SecurityRefreshCertificateDirectoryStores(UA_CERTIFICATE_GROUP_DEFAULT_USER_GROUP,
                                                                    callbackOpComplete);
  if (status.IsBad())
  {
    return status;
  }

  status = callbackOpComplete->WaitForResult();
  return status;
}

uasdk::Status_t UAServer_t::TcpipNewConnection(uint64_t connectionId)
{
  Status_t status;
  IntrusivePtr_t<TcpConnectionPlatform_t> newConnection = new SafeRefCount_t<TcpConnectionPlatform_t>();
  if (!newConnection.is_set())
  {
    return OpcUa_BadOutOfMemory;
  }

  status = newConnection->Initialise(connectionId, connections);
  if (status.IsGood())
  {
    status = core->TCPNewConnectionReceived(newConnection);
    if (status.IsGood())
    {
      status = connections.AddToTail(*newConnection);
    }
  }

  if (status.IsBad())
  {
    IntrusivePtr_t<TcpConnectionPlatform_t> connection = GetConnection(connectionId);
    if (connection.is_set())
    {
      connection->CloseFromPlatform();
      connections.RemoveSpecific(*connection);
    }
  }

  return status;
}

uasdk::Status_t UAServer_t::TcpipConnectionClosed(uint64_t connectionId)
{
  IntrusivePtr_t<TcpConnectionPlatform_t> connection = GetConnection(connectionId);
  if (connection.is_set())
  {
    connection->CloseFromPlatform();
    connections.RemoveSpecific(*connection);
    return OpcUa_Good;
  }
  return OpcUa_BadNotFound;
}

uasdk::Status_t UAServer_t::TcpipNewDataReceived(void* readContext, uint64_t connectionId)
{
  IntrusivePtr_t<TcpConnectionPlatform_t> connection = GetConnection(connectionId);
  if (connection.is_set())
  {
    connection->NetworkRxAllowed(true);
    connection->Context(readContext);
    connection->DataAvailable();

    Status_t status;
    do
    {
      status = threadPool->Operate();
    } while (status.IsGood());
    connection->Context(0);
    connection->NetworkRxAllowed(false);

    return OpcUa_Good;
  }
  return OpcUa_BadNotFound;
}

uasdk::Status_t UAServer_t::GetDataToSend(void* writeContext, uint64_t connectionId)
{
  IntrusivePtr_t<TcpConnectionPlatform_t> connection = GetConnection(connectionId);
  if (connection.is_set())
  {
    connection->NetworkTxAllowed(true);
    connection->Context(writeContext);
    connection->NetworkReady();

    Status_t status;
    do
    {
      status = threadPool->Operate();
    } while (status.IsGood());
    connection->Context(0);
    connection->NetworkTxAllowed(false);

    return OpcUa_Good;
  }
  return OpcUa_BadNotFound;
}

void UAServer_t::Poll(void)
{
  Status_t status;

  timerProvider->Poll();

  do
  {
    status = threadPool->Operate();
  } while (status.IsGood());
}

uasdk::Status_t UAServer_t::Terminate(void)
{
  return core->Shutdown();
}

uasdk::IntrusivePtr_t<uasdk::IServerConfiguration_t> UAServer_t::ValidateConfiguration(const UA_Configuration_t& cfg)
{
  Status_t result;
  IntrusivePtr_t<IServerConfiguration_t> empty;
  const UA_Configuration_Diagnostics_t& DIAGNOSTICS = cfg.DIAGNOSTICS;
  const UA_Configuration_Internals_t& INTERNALS = cfg.INTERNALS;

  UASDK_UNUSED(DIAGNOSTICS);

#if (UASDK_USE_SYSTEM_HEAP == 0)
  if (INTERNALS.USE_HEAP_RATHER_THAN_RAM_BUFFER != 0)
  {
    //LOG_ERROR("INTERNALS.USE_HEAP_RATHER_THAN_RAM_BUFFER is true");
    return empty;
  }
  if (INTERNALS.BUFFER == NULL)
  {
    //LOG_ERROR("INTERNALS.BUFFER pointer is Null");
    return empty;
  }
  if (INTERNALS.BUFFER_LENGTH_IN_BYTES == 0)
  {
    //LOG_ERROR("INTERNALS.BUFFER_LENGTH_IN_BYTES is 0");
    return empty;
  }
  if (INTERNALS.MAX_ALLOCATION_SIZE_IN_BYTES == 0)
  {
    //LOG_ERROR("INTERNALS.MAX_ALLOCATION_SIZE_IN_BYTES is 0");
    return empty;
  }
  if (INTERNALS.MAX_NO_OF_DEFERRED_RESPONSE_MESSAGES == 0)
  {
    //LOG_ERROR("INTERNALS.MAX_NO_OF_DEFERRED_RESPONSE_MESSAGES is 0");
    return empty;
  }
  if (INTERNALS.MAX_NO_OF_DEFERRED_OPERATIONS_PER_RESPONSE_MESSAGE == 0)
  {
    //LOG_ERROR("INTERNALS.MAX_NO_OF_DEFERRED_OPERATIONS_PER_RESPONSE_MESSAGE is 0");
    return empty;
  }

  result = UAServer_t::CreateAllocator(
    cfg.INTERNALS.BUFFER,
    cfg.INTERNALS.BUFFER_LENGTH_IN_BYTES,
    cfg.INTERNALS.MAX_ALLOCATION_SIZE_IN_BYTES);
  if (result.IsBad())
  {
    return empty;
  }
#endif

#if (UASDK_DEBUG > 0)
  logListener = new SafeRefCount_t<LogListener_t>();
  if (!logListener.is_set())
  {
	return empty;
  }
  Logger_t::Initialise(*logListener);
#endif

  IntrusivePtr_t<IServerConfiguration_t> serverConfig = UAServer_t::CreateConfiguration(result);
  if (!serverConfig.is_set() || result.IsBad())
  {
    return empty;
  }

  const UA_Configuration_TcpBinary_t& TCP_BINARY = cfg.TCP_BINARY;

  if (TCP_BINARY.CONNECTION_TIMEOUT_IN_MS == 0)
  {
    LOG_ERROR("TCP_BINARY.CONNECTION_TIMEOUT_IN_MS is 0");
    return empty;
  }
  if (TCP_BINARY.PORT_NUMBER == 0)
  {
    LOG_ERROR("TCP_BINARY.PORT_NUMBER is 0");
    return empty;
  }
  if (TCP_BINARY.MAX_MESSAGE_SIZE < TCP_BINARY.MAX_MESSAGE_CHUNK_SIZE)
  {
    LOG_ERROR("TCP_BINARY.MAX_MESSAGE_SIZE is < TCP_BINARY.MAX_MESSAGE_CHUNK_SIZE");
    return empty;
  }
  if (TCP_BINARY.MAX_MESSAGE_CHUNK_SIZE < 8200)
  {
    LOG_ERROR("TCP_BINARY.MAX_MESSAGE_CHUNK_SIZE <= 8200");
    return empty;
  }
  if ((TCP_BINARY.MAX_MESSAGE_CHUNK_SIZE * TCP_BINARY.MAX_MESSAGE_CHUNK_COUNT) < TCP_BINARY.MAX_MESSAGE_SIZE)
  {
    LOG_ERROR("TCP_BINARY.MAX_MESSAGE_CHUNK_SIZE * TCP_BINARY.MAX_MESSAGE_CHUNK_COUNT) < TCP_BINARY.MAX_MESSAGE_SIZE");
    return empty;
  }
  if (TCP_BINARY.MAX_CONNECTIONS < 2)
  {
    LOG_ERROR("TCP_BINARY.MAX_CONNECTIONS < 2. At least two connections needed for a single session and the LDS");
    return empty;
  }

  serverConfig->TCPBinaryConnectionTimeoutInMs(TCP_BINARY.CONNECTION_TIMEOUT_IN_MS);
  serverConfig->ServerEndpointTCPPort(TCP_BINARY.PORT_NUMBER);
  serverConfig->DiscoveryEndpointTCPPort(TCP_BINARY.PORT_NUMBER);
  serverConfig->TCPBinaryMaxMessageSize(TCP_BINARY.MAX_MESSAGE_SIZE);
  serverConfig->TCPBinaryMaxMessageChunkSize(TCP_BINARY.MAX_MESSAGE_CHUNK_SIZE);
  serverConfig->TCPBinaryMaxChunkCount(TCP_BINARY.MAX_MESSAGE_CHUNK_COUNT);
  serverConfig->TCPBinaryMaxConnections(TCP_BINARY.MAX_CONNECTIONS);

  const UA_Configuration_SecureConversation_t& SECURE_CONVERSATION = cfg.SECURE_CONVERSATION;

  if (SECURE_CONVERSATION.MIN_REVISED_CHANNEL_LIFETIME_IN_MS == 0)
  {
    LOG_ERROR("SECURE_CONVERSATION.MIN_REVISED_CHANNEL_LIFETIME_IN_MS == 0");
    return empty;
  }
  if (SECURE_CONVERSATION.MAX_REVISED_CHANNEL_LIFETIME_IN_MS == 0)
  {
    LOG_ERROR("SECURE_CONVERSATION.MAX_REVISED_CHANNEL_LIFETIME_IN_MS == 0");
    return empty;
  }
  if (SECURE_CONVERSATION.MAX_REVISED_CHANNEL_LIFETIME_IN_MS < SECURE_CONVERSATION.MIN_REVISED_CHANNEL_LIFETIME_IN_MS)
  {
    LOG_ERROR("SECURE_CONVERSATION.MAX_REVISED_CHANNEL_LIFETIME_IN_MS < SECURE_CONVERSATION.MIN_REVISED_CHANNEL_LIFETIME_IN_MS");
    return empty;
  }
  if (SECURE_CONVERSATION.MAX_SECURE_CHANNELS >= TCP_BINARY.MAX_CONNECTIONS)
  {
    LOG_ERROR("SECURE_CONVERSATION.MAX_SECURE_CHANNELS >= TCP_BINARY.MAX_CONNECTIONS. Allow at least one extra TCP Connection.");
    return empty;
  }
  serverConfig->SecureChannelMinRevisedChannelLifetimeInMs(SECURE_CONVERSATION.MIN_REVISED_CHANNEL_LIFETIME_IN_MS);
  serverConfig->SecureChannelMaxRevisedChannelLifetimeInMs(SECURE_CONVERSATION.MAX_REVISED_CHANNEL_LIFETIME_IN_MS);
  serverConfig->SecureChannelMaxChannels(SECURE_CONVERSATION.MAX_SECURE_CHANNELS);

  const UA_Configuration_Security_t& SECURITY = cfg.SECURITY;

#if (UASDK_INCLUDE_SECURITY != 0)
  if (SECURITY.ENDPOINT_SECURITY_POLICY_NONE == 0)
  {
    LOG_INFO("An insecure endpoint security policy is defined. This is a security risk.");
  }

  uint64_t sum = SECURITY.ENDPOINT_SECURITY_POLICY_NONE
    + SECURITY.ENDPOINT_SECURITY_POLICY_SIGN_Basic128Rsa15
    + SECURITY.ENDPOINT_SECURITY_POLICY_SIGN_AND_ENCRYPT_Basic128Rsa15
    + SECURITY.ENDPOINT_SECURITY_POLICY_SIGN_Basic256
    + SECURITY.ENDPOINT_SECURITY_POLICY_SIGN_AND_ENCRYPT_Basic256
    + SECURITY.ENDPOINT_SECURITY_POLICY_SIGN_Basic256Sha256
    + SECURITY.ENDPOINT_SECURITY_POLICY_SIGN_AND_ENCRYPT_Basic256Sha256;
  if (sum == 0)
  {
    LOG_ERROR("No endpoint security policies are defined");
    return empty;
  }

  if (SECURITY.ENDPOINT_SECURITY_POLICY_NONE)
  {
    result = AddEndpoints(serverConfig,
      SECURITY.ENDPOINT_SECURITY_POLICY_NONE,
      SECURITY_POLICY_NONE,
      MessageSecurityMode_t::OPCUA_MESSAGE_SECURITY_MODE_NONE);
    if (result.IsBad())
    {
      LOG_ERROR("No endpoint security policies are defined");
      return empty;
    }
  }
  if (SECURITY.ENDPOINT_SECURITY_POLICY_SIGN_Basic128Rsa15)
  {
    result = AddEndpoints(serverConfig,
      SECURITY.ENDPOINT_SECURITY_POLICY_SIGN_Basic128Rsa15,
      SECURITY_POLICY_BASIC128RSA15,
      MessageSecurityMode_t::OPCUA_MESSAGE_SECURITY_MODE_SIGN);
    if (result.IsBad())
    {
      LOG_ERROR("No endpoint security policies are defined");
      return empty;
    }
  }
  if (SECURITY.ENDPOINT_SECURITY_POLICY_SIGN_AND_ENCRYPT_Basic128Rsa15)
  {
    result = AddEndpoints(serverConfig,
      SECURITY.ENDPOINT_SECURITY_POLICY_SIGN_AND_ENCRYPT_Basic128Rsa15,
      SECURITY_POLICY_BASIC128RSA15,
      MessageSecurityMode_t::OPCUA_MESSAGE_SECURITY_MODE_SIGNANDENCRYPT);
    if (result.IsBad())
    {
      LOG_ERROR("No endpoint security policies are defined");
      return empty;
    }
  }
  if (SECURITY.ENDPOINT_SECURITY_POLICY_SIGN_Basic256)
  {
    result = AddEndpoints(serverConfig,
      SECURITY.ENDPOINT_SECURITY_POLICY_SIGN_Basic256,
      SECURITY_POLICY_BASIC256,
      MessageSecurityMode_t::OPCUA_MESSAGE_SECURITY_MODE_SIGN);
    if (result.IsBad())
    {
      LOG_ERROR("No endpoint security policies are defined");
      return empty;
    }
  }
  if (SECURITY.ENDPOINT_SECURITY_POLICY_SIGN_AND_ENCRYPT_Basic256)
  {
    result = AddEndpoints(serverConfig,
      SECURITY.ENDPOINT_SECURITY_POLICY_SIGN_AND_ENCRYPT_Basic256,
      SECURITY_POLICY_BASIC256,
      MessageSecurityMode_t::OPCUA_MESSAGE_SECURITY_MODE_SIGNANDENCRYPT);
    if (result.IsBad())
    {
      LOG_ERROR("No endpoint security policies are defined");
      return empty;
    }
  }
  if (SECURITY.ENDPOINT_SECURITY_POLICY_SIGN_Basic256Sha256)
  {
    result = AddEndpoints(serverConfig,
      SECURITY.ENDPOINT_SECURITY_POLICY_SIGN_Basic256Sha256,
      SECURITY_POLICY_BASIC256SHA256,
      MessageSecurityMode_t::OPCUA_MESSAGE_SECURITY_MODE_SIGN);
    if (result.IsBad())
    {
      LOG_ERROR("No endpoint security policies are defined");
      return empty;
    }
  }
  if (SECURITY.ENDPOINT_SECURITY_POLICY_SIGN_AND_ENCRYPT_Basic256Sha256)
  {
    result = AddEndpoints(serverConfig,
      SECURITY.ENDPOINT_SECURITY_POLICY_SIGN_AND_ENCRYPT_Basic256Sha256,
      SECURITY_POLICY_BASIC256SHA256,
      MessageSecurityMode_t::OPCUA_MESSAGE_SECURITY_MODE_SIGNANDENCRYPT);
    if (result.IsBad())
    {
      LOG_ERROR("No endpoint security policies are defined");
      return empty;
    }
  }

#if (ALLOW_USER_TOKEN_POLICY_X509v3_CERTIFICATE_TOKEN_SECURITY_POLICY_NONE == 0)
  if (
    (SECURITY.ENDPOINT_SECURITY_POLICY_NONE & UA_USER_TOKEN_POLICY_X509v3_CERTIFICATE_TOKEN_SECURITY_POLICY_NONE) ||
    (SECURITY.ENDPOINT_SECURITY_POLICY_SIGN_Basic128Rsa15 & UA_USER_TOKEN_POLICY_X509v3_CERTIFICATE_TOKEN_SECURITY_POLICY_NONE) ||
    (SECURITY.ENDPOINT_SECURITY_POLICY_SIGN_AND_ENCRYPT_Basic128Rsa15 & UA_USER_TOKEN_POLICY_X509v3_CERTIFICATE_TOKEN_SECURITY_POLICY_NONE) ||
    (SECURITY.ENDPOINT_SECURITY_POLICY_SIGN_Basic256 & UA_USER_TOKEN_POLICY_X509v3_CERTIFICATE_TOKEN_SECURITY_POLICY_NONE) ||
    (SECURITY.ENDPOINT_SECURITY_POLICY_SIGN_AND_ENCRYPT_Basic256 & UA_USER_TOKEN_POLICY_X509v3_CERTIFICATE_TOKEN_SECURITY_POLICY_NONE) ||
    (SECURITY.ENDPOINT_SECURITY_POLICY_SIGN_Basic256Sha256 & UA_USER_TOKEN_POLICY_X509v3_CERTIFICATE_TOKEN_SECURITY_POLICY_NONE) ||
    (SECURITY.ENDPOINT_SECURITY_POLICY_SIGN_AND_ENCRYPT_Basic256Sha256 & UA_USER_TOKEN_POLICY_X509v3_CERTIFICATE_TOKEN_SECURITY_POLICY_NONE))
  {
    LOG_ERROR("UA_USER_TOKEN_POLICY_X509v3_CERTIFICATE_TOKEN_SECURITY_POLICY_NONE is not permitted");
    return empty;
  }
#endif

#else
  if (SECURITY.ENDPOINT_SECURITY_POLICY_NONE == 0)
  {
    LOG_ERROR("No endpoint security policies are defined");
    return empty;
  }

  if (SECURITY.ENDPOINT_SECURITY_POLICY_NONE)
  {
    result = AddEndpoints(serverConfig,
      SECURITY.ENDPOINT_SECURITY_POLICY_NONE,
      SECURITY_POLICY_NONE,
      MessageSecurityMode_t::OPCUA_MESSAGE_SECURITY_MODE_NONE);
    if (result.IsBad())
    {
      LOG_ERROR("No endpoint security policies are defined");
      return empty;
    }
  }
  uint64_t sum = SECURITY.ENDPOINT_SECURITY_POLICY_SIGN_Basic128Rsa15
    + SECURITY.ENDPOINT_SECURITY_POLICY_SIGN_AND_ENCRYPT_Basic128Rsa15
    + SECURITY.ENDPOINT_SECURITY_POLICY_SIGN_Basic256
    + SECURITY.ENDPOINT_SECURITY_POLICY_SIGN_AND_ENCRYPT_Basic256
    + SECURITY.ENDPOINT_SECURITY_POLICY_SIGN_Basic256Sha256
    + SECURITY.ENDPOINT_SECURITY_POLICY_SIGN_AND_ENCRYPT_Basic256Sha256;
  if (sum > 0)
  {
    LOG_INFO("Secure endpoint security policies are defined but UA_INCLUDE_SECURITY is not enabled");
  }
#endif

  const UA_Configuration_Intervals_t& INTERVALS = cfg.INTERVALS;
  if (INTERVALS.CYCLIC_RATE_IN_MS == 0)
  {
    LOG_ERROR("INTERVALS.CYCLIC_RATE_IN_MS == 0");
    return empty;
  }
  serverConfig->ServerCyclicRateInMs(INTERVALS.CYCLIC_RATE_IN_MS);

  const UA_Configuration_Services_t& SERVICES = cfg.SERVICES;

  if (SERVICES.MIN_REVISED_SESSION_TIMEOUT_IN_MS == 0)
  {
    LOG_ERROR("SERVICES.MIN_REVISED_SESSION_TIMEOUT_IN_MS == 0");
    return empty;
  }
  if (SERVICES.MAX_REVISED_SESSION_TIMEOUT_IN_MS == 0)
  {
    LOG_ERROR("SERVICES.MAX_REVISED_SESSION_TIMEOUT_IN_MS == 0");
    return empty;
  }
  if (SERVICES.MAX_SESSIONS == 0)
  {
    LOG_ERROR("SERVICES.MAX_SESSIONS == 0");
    return empty;
  }
  if (SERVICES.MAX_SESSIONS > (SECURE_CONVERSATION.MAX_SECURE_CHANNELS - 1))
  {
    LOG_ERROR("SERVICES.MAX_SESSIONS > (SECURE_CONVERSATION.MAX_SECURE_CHANNELS - 1). At least one secure channel must be reserve for the LDS");
    return empty;
  }

  serverConfig->MinRevisedSessionTimeoutInMs(SERVICES.MIN_REVISED_SESSION_TIMEOUT_IN_MS);
  serverConfig->MaxRevisedSessionTimeoutInMs(SERVICES.MAX_REVISED_SESSION_TIMEOUT_IN_MS);
  serverConfig->MaxSessions(SERVICES.MAX_SESSIONS);

#if (UASDK_INCLUDE_SUBSCRIPTIONS > 0)
  if (SERVICES.MAX_SUBSCRIPTIONS_PER_SESSION == 0)
  {
    LOG_ERROR("SERVICES.MAX_SUBSCRIPTIONS_PER_SESSION == 0");
    return empty;
  }
  if (SERVICES.MIN_MAX_KEEP_ALIVE_COUNT == 0)
  {
    LOG_ERROR("SERVICES.MIN_MAX_KEEP_ALIVE_COUNT == 0");
    return empty;
  }
  if (SERVICES.MAX_MAX_KEEP_ALIVE_COUNT == 0)
  {
    LOG_ERROR("SERVICES.MAX_MAX_KEEP_ALIVE_COUNT == 0");
    return empty;
  }
  if (SERVICES.MAX_MAX_KEEP_ALIVE_COUNT < SERVICES.MIN_MAX_KEEP_ALIVE_COUNT)
  {
    LOG_ERROR("SERVICES.MAX_MAX_KEEP_ALIVE_COUNT < SERVICES.MIN_MAX_KEEP_ALIVE_COUNT");
    return empty;
  }
  if (SERVICES.MAX_PUBLISH_REQUESTS_PER_SESSION <= SERVICES.MAX_SUBSCRIPTIONS_PER_SESSION)
  {
    LOG_ERROR("SERVICES.MAX_PUBLISH_REQUESTS_PER_SESSION <= SERVICES.MAX_SUBSCRIPTIONS_PER_SESSION");
    return empty;
  }
  if (SERVICES.MAX_MONITORED_ITEMS == 0)
  {
    LOG_ERROR("SERVICES.MAX_MONITORED_ITEMS == 0");
    return empty;
  }
  if (SERVICES.MAX_MON_ITEM_QUEUE_SIZE == 0)
  {
    LOG_ERROR("SERVICES.MAX_MON_ITEM_QUEUE_SIZE == 0");
    return empty;
  }
  serverConfig->MaxSubscriptionsPerSession(SERVICES.MAX_SUBSCRIPTIONS_PER_SESSION);
  serverConfig->MinMaxKeepAliveCount(SERVICES.MIN_MAX_KEEP_ALIVE_COUNT);
  serverConfig->MaxMaxKeepAliveCount(SERVICES.MAX_MAX_KEEP_ALIVE_COUNT);
  serverConfig->MaxNotificationRetransmissionQueueSize(SERVICES.MAX_NOTIFICATION_RETRANSMISSION_QUEUE_SIZE);
  serverConfig->MaxPublishRequestsPerSession(SERVICES.MAX_PUBLISH_REQUESTS_PER_SESSION);
  serverConfig->MaxBrowseRefsPerNode(SERVICES.BROWSE_MAX_REFS_PER_NODE);
  serverConfig->MaxMonitoredItems(SERVICES.MAX_MONITORED_ITEMS);
  serverConfig->MaxMonItemQueueSize(SERVICES.MAX_MON_ITEM_QUEUE_SIZE);
#endif

  const UA_Configuration_Locales_t& LOCALES = cfg.LOCALES;

  if (LOCALES.LOCALE_ID_ARRAY_LENGTH > 0)
  {
    LOG_INFO("Checking LOCALES");
    IntrusivePtr_t<ArrayUA_t<String_t> > locales(new SafeRefCount_t<ArrayUA_t<String_t> >());
    if (!locales.is_set())
    {
      LOG_ERROR("LOCALES is not set, bad out of memory");
      return empty;
    }
    result = locales->Initialise(LOCALES.LOCALE_ID_ARRAY_LENGTH);
    if (result.IsBad())
    {
      LOG_ERROR("LOCALES is not set, bad out of memory");
      return empty;
    }
    for (uint32_t i = 0; i < LOCALES.LOCALE_ID_ARRAY_LENGTH; i++)
    {
      /* Catch potential hard faults here before we run the server */
      if (LOCALES.LOCALE_ID_ARRAY[i] == 0)
      {
        LOG_ERROR("LOCALES.LOCALE_ID_ARRAY contains 0s");
        return empty;
      }
      IntrusivePtr_t<String_t> locale(new SafeRefCount_t<String_t>());
      if (!locale.is_set())
      {
        LOG_ERROR("locale is not set, bad out of memory");
        return empty;
      }
      result = locale->CopyFrom(LOCALES.LOCALE_ID_ARRAY[i]);
      if (result.IsBad())
      {
        LOG_ERROR("locale is not set, bad out of memory");
        return empty;
      }
      (*locales)[i] = locale;
    }

    serverConfig->LocaleIds(locales);
  }

  const UA_Configuration_ProfileArray_t& PROFILE_ARRAY = cfg.PROFILE_ARRAY;

  if (PROFILE_ARRAY.SERVER_PROFILE_ARRAY_LENGTH > 0)
  {
    LOG_INFO("Checking PROFILE_ARRAY");

    for (uint32_t i = 0; i < PROFILE_ARRAY.SERVER_PROFILE_ARRAY_LENGTH; i++)
    {
      /* Catch potential hard faults here before we run the server */
      if (PROFILE_ARRAY.SERVER_PROFILE_ARRAY[i] == 0)
      {
        LOG_ERROR("PROFILE_ARRAY.SERVER_PROFILE_ARRAY contains 0s");
        return empty;
      }
    }
  }

  const UA_Configuration_OperationLimits_t& OPERATION_LIMITS = cfg.SERVER_CAPABILITIES.OPERATION_LIMITS;

  if (OPERATION_LIMITS.MAX_NODES_PER_READ == 0)
  {
    LOG_ERROR("OPERATION_LIMITS.MAX_NODES_PER_READ == 0");
    return empty;
  }
  if (OPERATION_LIMITS.MAX_NODES_PER_WRITE == 0)
  {
    LOG_ERROR("OPERATION_LIMITS.MAX_NODES_PER_WRITE == 0");
    return empty;
  }
  if (OPERATION_LIMITS.MAX_NODES_PER_BROWSE == 0)
  {
    LOG_ERROR("OPERATION_LIMITS.MAX_NODES_PER_BROWSE == 0");
    return empty;
  }
  if (OPERATION_LIMITS.MAX_NODES_PER_REGISTER_NODES == 0)
  {
    LOG_ERROR("OPERATION_LIMITS.MAX_NODES_PER_REGISTER_NODES == 0");
    return empty;
  }
  if (OPERATION_LIMITS.MAX_NODES_PER_TRANSLATE_BROWSE_PATHS_TO_NODE_IDS == 0)
  {
    LOG_ERROR("OPERATION_LIMITS.MAX_NODES_PER_TRANSLATE_BROWSE_PATHS_TO_NODE_IDS == 0");
    return empty;
  }
  serverConfig->OperationLimitsEnforce(((OPERATION_LIMITS.ENFORCE_OPERATION_LIMITS == 0)? false : true));
  serverConfig->OperationLimitsMaxNodesPerRead(OPERATION_LIMITS.MAX_NODES_PER_READ);
  //  serverConfig->OperationLimitsMaxNodesPerHistoryReadData(OPERATION_LIMITS.MAX_NODES_PER_HISTORY_READ_DATA);
  //  serverConfig->OperationLimitsMaxNodesPerHistoryReadEvents(OPERATION_LIMITS.MAX_NODES_PER_HISTORY_READ_EVENTS);
  serverConfig->OperationLimitsMaxNodesPerWrite(OPERATION_LIMITS.MAX_NODES_PER_WRITE);
  //  serverConfig->OperationLimitsMaxNodesPerHistoryUpdateData(OPERATION_LIMITS.MAX_NODES_PER_HISTORY_UPDATE_DATA);
  //  serverConfig->OperationLimitsMaxNodesPerHistoryUpdateEvents(OPERATION_LIMITS.MAX_NODES_PER_HISTORY_UPDATE_EVENTS);
  serverConfig->OperationLimitsMaxNodesPerMethodCall(OPERATION_LIMITS.MAX_NODES_PER_METHOD_CALL);
  serverConfig->OperationLimitsMaxNodesPerBrowse(OPERATION_LIMITS.MAX_NODES_PER_BROWSE);
  serverConfig->OperationLimitsMaxNodesPerRegisterNodes(OPERATION_LIMITS.MAX_NODES_PER_REGISTER_NODES);
  serverConfig->OperationLimitsMaxNodesPerTranslateBrowsePathsToNodeIds(OPERATION_LIMITS.MAX_NODES_PER_TRANSLATE_BROWSE_PATHS_TO_NODE_IDS);
  serverConfig->OperationLimitsMaxNodesPerNodeManagement(OPERATION_LIMITS.MAX_NODES_PER_NODE_MANAGEMENT);
#if (UASDK_INCLUDE_SUBSCRIPTIONS > 0)
  if (OPERATION_LIMITS.MAX_MONITORED_ITEMS_PER_CALL == 0)
  {
    LOG_ERROR("OPERATION_LIMITS.MAX_MONITORED_ITEMS_PER_CALL == 0");
    return empty;
  }
  serverConfig->OperationLimitsMaxMonitoredItemsPerCall(OPERATION_LIMITS.MAX_MONITORED_ITEMS_PER_CALL);
#endif

  const UA_Configuration_ServerCapabilities_t& SERVER_CAPABILITIES = cfg.SERVER_CAPABILITIES;

  if (SERVER_CAPABILITIES.MAX_BROWSE_CONTINUATION_POINTS == 0)
  {
    LOG_ERROR("SERVER_CAPABILITIES.MAX_BROWSE_CONTINUATION_POINTS == 0");
    return empty;
  }
  if (SERVER_CAPABILITIES.MAX_STRING_LENGTH == 0)
  {
    LOG_ERROR("SERVER_CAPABILITIES.MAX_STRING_LENGTH == 0");
    return empty;
  }
  if (SERVER_CAPABILITIES.MAX_ARRAY_LENGTH == 0)
  {
    LOG_ERROR("SERVER_CAPABILITIES.MAX_STRING_LENGTH == 0");
    return empty;
  }
  serverConfig->CapabilitiesMaxHistoryContinuationPoints(SERVER_CAPABILITIES.MAX_BROWSE_CONTINUATION_POINTS);
  serverConfig->CapabilitiesMaxStringLength(SERVER_CAPABILITIES.MAX_STRING_LENGTH);
  serverConfig->CapabilitiesMaxArrayLength(SERVER_CAPABILITIES.MAX_ARRAY_LENGTH);
  //  serverConfig->CapabilitiesMaxHistoryContinuationPoints(SERVER_CAPABILITIES.MAX_HISTORY_CONTINUATION_POINTS);
  //  serverConfig->CapabilitiesMaxQueryContinuationPoints(SERVER_CAPABILITIES.MAX_QUERY_CONTINUATION_POINTS);

  if (!INTERNALS.USE_HEAP_RATHER_THAN_RAM_BUFFER)
  {
    if (INTERNALS.MAX_ALLOCATION_SIZE_IN_BYTES < TCP_BINARY.MAX_MESSAGE_SIZE)
    {
      LOG_ERROR("INTERNALS.MAX_ALLOCATION_SIZE_IN_BYTES < TCP_BINARY.MAX_MESSAGE_SIZE");
      return empty;
    }
    if (INTERNALS.MAX_ALLOCATION_SIZE_IN_BYTES < SERVER_CAPABILITIES.MAX_ARRAY_LENGTH)
    {
      LOG_ERROR("INTERNALS.MAX_ALLOCATION_SIZE_IN_BYTES < SERVER_CAPABILITIES.MAX_ARRAY_LENGTH");
      return empty;
    }
    if (INTERNALS.MAX_ALLOCATION_SIZE_IN_BYTES < SERVER_CAPABILITIES.MAX_STRING_LENGTH)
    {
      LOG_ERROR("INTERNALS.MAX_ALLOCATION_SIZE_IN_BYTES < SERVER_CAPABILITIES.MAX_STRING_LENGTH");
      return empty;
    }
  }

  if (INTERNALS.ADDRESS_SPACE_HASH_TABLE_NO_OF_BUCKETS == 0)
  {
    LOG_ERROR("INTERNALS.ADDRESS_SPACE_HASH_TABLE_NO_OF_BUCKETS == 0");
    return empty;
  }

  IntrusivePtr_t<String_t> applicationURI = new SafeRefCount_t<String_t>();
  if (!applicationURI.is_set())
  {
    LOG_ERROR("INTERNALS.MAX_ALLOCATION_SIZE_IN_BYTES < SERVER_CAPABILITIES.MAX_STRING_LENGTH");
    return empty;
  }
  result = applicationURI->CopyFrom("urn://Dummy URI", 100);
  if (result.IsBad())
  {
    LOG_ERROR("INTERNALS.MAX_ALLOCATION_SIZE_IN_BYTES < SERVER_CAPABILITIES.MAX_STRING_LENGTH");
    return empty;
  }

  IntrusivePtr_t<BuildInfo_t> buildInfo = new SafeRefCount_t<BuildInfo_t>();
  if (!buildInfo.is_set())
  {
    LOG_ERROR("INTERNALS.MAX_ALLOCATION_SIZE_IN_BYTES < SERVER_CAPABILITIES.MAX_STRING_LENGTH");
    return empty;
  }
  result = buildInfo->ProductName().CopyFrom(UA_PRODUCT_NAME, 100);
  if (result.IsBad())
  {
    LOG_ERROR("INTERNALS.MAX_ALLOCATION_SIZE_IN_BYTES < SERVER_CAPABILITIES.MAX_STRING_LENGTH");
    return empty;
  }
  result = buildInfo->ProductUri().CopyFrom(UA_PRODUCT_URI, 100);
  if (result.IsBad())
  {
    LOG_ERROR("INTERNALS.MAX_ALLOCATION_SIZE_IN_BYTES < SERVER_CAPABILITIES.MAX_STRING_LENGTH");
    return empty;
  }
  result = buildInfo->ManufacturerName().CopyFrom(UA_MANUFACTURER_NAME, 100);
  if (result.IsBad())
  {
    LOG_ERROR("INTERNALS.MAX_ALLOCATION_SIZE_IN_BYTES < SERVER_CAPABILITIES.MAX_STRING_LENGTH");
    return empty;
  }
  result = buildInfo->SoftwareVersion().CopyFrom(UA_SOFTWARE_VERSION, 100);
  if (result.IsBad())
  {
    LOG_ERROR("INTERNALS.MAX_ALLOCATION_SIZE_IN_BYTES < SERVER_CAPABILITIES.MAX_STRING_LENGTH");
    return empty;
  }
  result = buildInfo->BuildNumber().CopyFrom(UA_BUILD_NUMBER, 100);
  if (result.IsBad())
  {
    LOG_ERROR("INTERNALS.MAX_ALLOCATION_SIZE_IN_BYTES < SERVER_CAPABILITIES.MAX_STRING_LENGTH");
    return empty;
  }
  result = buildInfo->BuildDate().CopyFrom(UASDK_datetime());
  if (result.IsBad())
  {
    LOG_ERROR("INTERNALS.MAX_ALLOCATION_SIZE_IN_BYTES < SERVER_CAPABILITIES.MAX_STRING_LENGTH");
    return empty;
  }

  serverConfig->BuildInfo(buildInfo);
  serverConfig->SendApplicationInstanceCertificateForSecurityPolicyNone(true);

  ServerCertificateValidationOptions_t validationOptions;
  validationOptions.doNotSaveRejectedCertificates = false;
  serverConfig->CertificateValidationOptions(validationOptions);

  IntrusivePtr_t<const IUserPermissionsProvider_t> userAuthenticatorProvider = new SafeRefCount_t<UserPermissionsProvider_t>();
  if (!userAuthenticatorProvider.is_set())
  {
    LOG_ERROR("INTERNALS.MAX_ALLOCATION_SIZE_IN_BYTES < SERVER_CAPABILITIES.MAX_STRING_LENGTH");
    return empty;
  }
  serverConfig->UserPermissionsProvider(userAuthenticatorProvider);

  IntrusivePtr_t<const ICertificatePrivateKeyPasswordProvider_t> passwordProvider = new SafeRefCount_t<CertificatePrivateKeyPasswordProvider_t>();
  if (!passwordProvider.is_set())
  {
    LOG_ERROR("INTERNALS.MAX_ALLOCATION_SIZE_IN_BYTES < SERVER_CAPABILITIES.MAX_STRING_LENGTH");
    return empty;
  }
  serverConfig->CertificatePrivateKeyPasswordProvider(passwordProvider);

  IntrusivePtr_t<IServerStateListener_t> serverStateListener;
  serverConfig->ServerStateListener(serverStateListener);
  IntrusivePtr_t<String_t> securityCertificateDirectoryStoresPath = new SafeRefCount_t<String_t>();
  if (!securityCertificateDirectoryStoresPath.is_set())
  {
    LOG_ERROR("INTERNALS.MAX_ALLOCATION_SIZE_IN_BYTES < SERVER_CAPABILITIES.MAX_STRING_LENGTH");
    return empty;
  }
  result = securityCertificateDirectoryStoresPath->CopyFrom(SECURITY_CERTIFICATE_DIRECTORY_STORE_PATH);
  if (result.IsBad())
  {
    LOG_ERROR("INTERNALS.MAX_ALLOCATION_SIZE_IN_BYTES < SERVER_CAPABILITIES.MAX_STRING_LENGTH");
    return empty;
  }
  serverConfig->SecurityCertificateDirectoryStoresPath(securityCertificateDirectoryStoresPath);

  return serverConfig;
}

Status_t UAServer_t::UpdateNameSpaceArray(const UA_Configuration_t& cfg)
{
  Status_t status;
  const char* opcUri = "http://opcfoundation.org/UA/";
  IntrusivePtr_t< ArrayUA_t<String_t> > newUris;

  UA_Configuration_NamespaceArray_t namespaceArrayConfig = cfg.ADDRESS_SPACE.NAMESPACES;
  if (namespaceArrayConfig.NAMESPACE_ARRAY_LENGTH > 0)
  {
    if (!namespaceArrayConfig.NAMESPACE_ARRAY)
    {
      LOG_ERROR("NAMESPACE_ARRAY is empty Or Configuration Error");
      return OpcUa_BadConfigurationError;
    }

    newUris.reset(new SafeRefCount_t< ArrayUA_t<String_t> >());
    if (!newUris.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }

    status = newUris->Initialise(namespaceArrayConfig.NAMESPACE_ARRAY_LENGTH + 1);
    if (status.IsBad())
    {
      UASDK_RETURN_BAD_STATUS(status.Value());
    }

    status = AddUri(opcUri, 0, *newUris);
    if (status.IsBad())
    {
      return status;
    }

    const char** namespaceArray = namespaceArrayConfig.NAMESPACE_ARRAY;
    uint32_t totalSize = namespaceArrayConfig.NAMESPACE_ARRAY_LENGTH + 1;
    for (uint32_t i = 1; i < totalSize; i++)
    {
      if (i > namespaceArrayConfig.NAMESPACE_ARRAY_LENGTH)
      {
        UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
      }

      if (!namespaceArray[i - 1])
      {
        UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
      }

      status = AddUri(namespaceArray[i - 1], i, *newUris);
      if (status.IsBad())
      {
        return status;
      }
    }
  }
  else
  {
    newUris.reset(new SafeRefCount_t< ArrayUA_t<String_t> >());
    if (!newUris.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }

    status = newUris->Initialise(2);
    if (status.IsBad())
    {
      UASDK_RETURN_BAD_STATUS(status.Value());
    }

    status = AddUri(opcUri, 0, *newUris);
    if (status.IsBad())
    {
      return status;
    }

    status = AddUri("uri://Dummy URI", 1, *newUris);
    if (status.IsBad())
    {
      return status;
    }
  }

  //Update this Namesapce array to Node

  if (!addressSpace.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  NodeIdNumeric_t nodeId_(0, OpcUaId_Server_NamespaceArray);
  IntrusivePtr_t<IVariableNode_t> varNode = addressSpace->FindVariableNode(nodeId_, status);
  if (status.IsBad() || !varNode.is_set())
  {
    return status;
  }

  IntrusivePtr_t<DataValue_t> val(new SafeRefCount_t<DataValue_t>());
  if (!val.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  IntrusivePtr_t<DateTime_t> sourceTimeStamp(new SafeRefCount_t<DateTime_t>());
  if (!sourceTimeStamp.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  sourceTimeStamp->Value(UASDK_datetime());
  
  IntrusivePtr_t<StatusCode_t> statusCode_ = new SafeRefCount_t<StatusCode_t>();
  if (!statusCode_.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }
  statusCode_->Value().Value(OpcUa_Good);

  val->Value() = newUris;
  val->StatusCode() = statusCode_;
  val->SourceTimestamp() = sourceTimeStamp;
  if (!val->Value().is_set() || !val->StatusCode().is_set() || !val->SourceTimestamp().is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  IntrusivePtr_t<const DataValue_t> val_ = val;
  varNode->Value(val_);

  return OpcUa_Good;
}

uasdk::Status_t UAServer_t::DeleteNode(uintptr_t node_handle)
{
  if (!addressSpace.is_set() || !node_handle)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  Status_t status;

  if (!namespaceIndexForAlias)
  {
    status = UpdateNamespaceIndexForAlias();
    if (status.IsBad() || !namespaceIndexForAlias)
    {
      UASDK_RETURN_BAD_STATUS(status.Value());
    }
  }

  NodeIdNumeric_t nodeId(namespaceIndexForAlias, static_cast<uint32_t>(node_handle));
  IntrusivePtr_t<INode_t> node = addressSpace->FindNode(nodeId, status);
  if (status.IsBad() || !node.is_set())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  status = AddressSpaceUtilities_t::RemoveAllInverseReferences(node, *addressSpace);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  return addressSpace->RemoveNode(*(node->NodeId()));
}

uasdk::Status_t UAServer_t::CreateFolder(const UA_Folder_t& data)
{
  if (!data.node_handle || !data.display_name_handle || !data.namespace_index )
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  IntrusivePtr_t<INode_t> node_;
  Status_t status = CreateNodeAndItsAttributes(OpcUaId_ObjectNode, data, node_);
  if (status.IsBad() || !node_.is_set())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
  IntrusivePtr_t<IObjectNode_t> node = AddressSpaceUtilities_t::NodeDownCast<IObjectNode_t>(*node_);
  if (!node.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  // HasType definition
  return AddressSpaceUtilities_t::CreateHasTypeDefintion(*addressSpace, node, OpcUaId_FolderType);
}


uasdk::Status_t UAServer_t::CreateView(const UA_View_t& data)
{
  if (!data.node_handle || !data.display_name_handle || !data.namespace_index)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  IntrusivePtr_t<INode_t> node_;
  Status_t status = CreateNodeAndItsAttributes(OpcUaId_ViewNode, data, node_);
  if (status.IsBad() || !node_.is_set())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
  IntrusivePtr_t<IViewNode_t> node = AddressSpaceUtilities_t::NodeDownCast<IViewNode_t>(*node_);
  if (!node.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  // HasType definition
  return AddressSpaceUtilities_t::CreateHasTypeDefintion(*addressSpace, node, OpcUaId_ViewNode);
}


uasdk::Status_t UAServer_t::CreateMethod(const UA_Method_t& data)
{
  if (!data.base_config.node_handle || !data.base_config.display_name_handle || !data.base_config.namespace_index)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  IntrusivePtr_t<INode_t> node_;
  Status_t status = CreateNodeAndItsAttributes(OpcUaId_MethodNode, data.base_config, node_);
  if (status.IsBad() || !node_.is_set())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
  IntrusivePtr_t<IMethodNode_t> node = AddressSpaceUtilities_t::NodeDownCast<IMethodNode_t>(*node_);
  if (!node.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  node->Executable(data.executable != 0);

  //Setting the user executable
  IntrusivePtr_t<INodeApplicationContext_t> context_ = node->ApplicationContextHandle();
  if (!context_.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  ApplicationContext_t& context = static_cast<ApplicationContext_t&> (*context_);
  context.UserExecutable(data.user_executable != 0);

  return OpcUa_Good;
}


uasdk::Status_t UAServer_t::CreateBaseDataVariable(const UA_BaseDataVariable_t& data)
{
  if (!data.base_config.node_handle || !data.base_config.display_name_handle
      || !data.base_config.namespace_index || (data.value_type == UA_TYPE_Invalid) || (data.value_type > UA_TYPE_XmlElement))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  IntrusivePtr_t<INode_t> node_;
  Status_t status = CreateNodeAndItsAttributes(OpcUaId_VariableNode, data.base_config, node_);
  if (status.IsBad() || !node_.is_set())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
  IntrusivePtr_t<IVariableNode_t> node = AddressSpaceUtilities_t::NodeDownCast<IVariableNode_t>(*node_);
  if (!node.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadTypeMismatch);
  }

  // HasType definition
  status = AddressSpaceUtilities_t::CreateHasTypeDefintion(*addressSpace, node, OpcUaId_BaseDataVariableType);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  return UpdateVariableNodeAttributes(node, data);
}


uasdk::Status_t UAServer_t::CreateDataItem(const UA_DataItem_t& data)
{
#if ((UASDK_USE_HELPERS > 0) && (UASDK_USE_DATA_ACCESS_HELPERS > 0))
  if ( ((data.use_definition != FALSE) && (!data.definition.data || (data.definition.length <= 0)) )
    || !data.data_variable_config.base_config.node_handle || !data.data_variable_config.base_config.display_name_handle
    || !data.data_variable_config.base_config.namespace_index || (data.data_variable_config.value_type == UA_TYPE_Invalid) || (data.data_variable_config.value_type > UA_TYPE_XmlElement))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  UA_Base_t baseConfig = data.data_variable_config.base_config;

  IntrusivePtr_t<DataItem_t> dataItem;
  IntrusivePtr_t<const NodeId_t> aliasId;
  IntrusivePtr_t<const NodeId_t> nodeId;
  IntrusivePtr_t<const ILocalizableText_t> displayNameTranslator;
  String_t browseName_;

  Status_t status = CreateEssenstialsForHelpers(baseConfig, aliasId, nodeId, displayNameTranslator, browseName_);
  if (status.IsBad() || !aliasId.is_set() || !nodeId.is_set() || !displayNameTranslator.is_set() || (browseName_.Length() <= 0))
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  switch(baseConfig.node_id.identifier_type)
  {
    case opcua_node_encoding_numeric:
      dataItem = DataItem_t::CreateWithNumericId<Byte_t>(baseConfig.namespace_index, baseConfig.node_id.numeric_identifier, addressSpace, browseName_, status);
      break;

    case opcua_node_encoding_string:
      {
        const NodeIdString_t& stringId = static_cast<const NodeIdString_t&>(*nodeId);
        dataItem = DataItem_t::CreateWithStringId<Byte_t>(baseConfig.namespace_index, stringId.Identifer(), addressSpace, browseName_, status);
      }
      break;

    case opcua_node_encoding_guid:
      {
        const NodeIdGuid_t& guidNodeId = static_cast<const NodeIdGuid_t&>(*nodeId);
        dataItem = DataItem_t::CreateWithGuidId<Byte_t>(baseConfig.namespace_index, guidNodeId.Identifer(), addressSpace, browseName_, status);
      }
      break;

    case opcua_node_encoding_bytestring:
      {
        dataItem = DataItem_t::CreateWithOpaqueId<Byte_t>(baseConfig.namespace_index, browseName_.Payload(), addressSpace, browseName_, status);
      }
      break;

    default:
      return OpcUa_BadInvalidArgument;
  }

  if (status.IsBad() || !dataItem.is_set())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
  dataItem->Hide(false);  // Node should be unhide before assigning the alias for a node!

  IntrusivePtr_t<IVariableNode_t> dataItemNode = dataItem->GetVariableNode();
  status = UpdateEssentialsForHelper(data.data_variable_config, aliasId, displayNameTranslator, dataItemNode);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  return CreateDefinitionAndValuePrecisionProperty(data, *dataItem);
#else
return OpcUa_BadNotSupported;
#endif  //#if (UASDK_USE_DATA_ACCESS_HELPERS > 0)
}


uasdk::Status_t UAServer_t::CreateAnalogItem(const UA_AnalogItem_t& data)
{
#if ((UASDK_USE_HELPERS > 0) && (UASDK_USE_DATA_ACCESS_HELPERS > 0))
  UA_DataItem_t dataItemConfig = data.data_item_config;
  UA_BaseDataVariable_t baseVariableConfig = dataItemConfig.data_variable_config;
  UA_Base_t baseConfig = baseVariableConfig.base_config;

  if ( ((dataItemConfig.use_definition != FALSE) && (!dataItemConfig.definition.data || (dataItemConfig.definition.length <= 0)) )
    || !baseVariableConfig.base_config.node_handle || !baseVariableConfig.base_config.display_name_handle
    || !baseVariableConfig.base_config.namespace_index || (baseVariableConfig.value_type == UA_TYPE_Invalid) || (baseVariableConfig.value_type > UA_TYPE_XmlElement))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  IntrusivePtr_t<AnalogItem_t> analogItem;
  IntrusivePtr_t<const NodeId_t> aliasId;
  IntrusivePtr_t<const NodeId_t> nodeId;
  IntrusivePtr_t<const ILocalizableText_t> displayNameTranslator;
  String_t browseName_;

  Status_t status = CreateEssenstialsForHelpers(baseConfig, aliasId, nodeId, displayNameTranslator, browseName_);
  if (status.IsBad() || !aliasId.is_set() || !nodeId.is_set() || !displayNameTranslator.is_set() || (browseName_.Length() <= 0))
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  Range_t euRange(data.EU_range.low, data.EU_range.high);
  switch (baseConfig.node_id.identifier_type)
  {
    case opcua_node_encoding_numeric:
      {
        uint32_t euRangeNumericId = GenerateNumericId(baseConfig.namespace_index);
        analogItem = AnalogItem_t::CreateWithNumericId<Byte_t>(baseConfig.namespace_index, baseConfig.node_id.numeric_identifier, addressSpace,
                                                               browseName_, euRangeNumericId, euRange, status);
      }
      break;

    case opcua_node_encoding_string:
      {
        const NodeIdString_t& stringId = static_cast<const NodeIdString_t&>(*nodeId);
        analogItem = AnalogItem_t::CreateWithStringId<Byte_t>(baseConfig.namespace_index, stringId.Identifer(), addressSpace, browseName_, euRange, status);
      }
      break;

    case opcua_node_encoding_guid:
      {
        const NodeIdGuid_t& guidNodeId = static_cast<const NodeIdGuid_t&>(*nodeId);
        analogItem = AnalogItem_t::CreateWithGuidId<Byte_t>(baseConfig.namespace_index, guidNodeId.Identifer(), addressSpace, browseName_, euRange, status);
      }
      break;

    case opcua_node_encoding_bytestring:
      analogItem = AnalogItem_t::CreateWithOpaqueId<Byte_t>(baseConfig.namespace_index, browseName_.Payload(), addressSpace, browseName_, euRange, status);
      break;

    default:
      return OpcUa_BadInvalidArgument;
  }

  if (status.IsBad() || !analogItem.is_set())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
  analogItem->Hide(false);

  if (data.use_engineering_units != FALSE)
  {
    EUInformation_t euInformation;

    String_t temp;
    IntrusivePtr_t<const ILocalizableText_t> euInfoDisplayNameTranslator;
    IntrusivePtr_t<const ILocalizableText_t> descriptionTranslator;

    //DisplayName
    status = CreateTranslatorAndGetEnglishText(data.engineering_units.display_name_handle, euInfoDisplayNameTranslator, temp);
    if (status.IsBad() || !euInfoDisplayNameTranslator.is_set() || (temp.Length() <= 0) )
    {
      UASDK_RETURN_BAD_STATUS(status.Value());
    }

    status = euInformation.DisplayName().Text().CopyFrom(temp);
    if (status.IsBad())
    {
      UASDK_RETURN_BAD_STATUS(status.Value());
    }

    status = euInformation.DisplayName().Locale().CopyFrom("en");
    if (status.IsBad())
    {
      UASDK_RETURN_BAD_STATUS(status.Value());
    }

    //Description
    status = CreateTranslatorAndGetEnglishText(data.engineering_units.display_name_handle, descriptionTranslator, temp);
    if (status.IsBad())
    {
      UASDK_RETURN_BAD_STATUS(status.Value());
    }

    status = euInformation.Description().Text().CopyFrom(temp);
    if (status.IsBad())
    {
      UASDK_RETURN_BAD_STATUS(status.Value());
    }

    status = euInformation.Description().Locale().CopyFrom("en");
    if (status.IsBad())
    {
      UASDK_RETURN_BAD_STATUS(status.Value());
    }

    //namespaceUri
    if (data.engineering_units.namespace_uri.length > 0)
    {
      status = temp.CopyFrom((const char*)data.engineering_units.namespace_uri.data, (data.engineering_units.namespace_uri.length + 1));
      if (status.IsBad())
      {
        UASDK_RETURN_BAD_STATUS(status.Value());
      }

      status = euInformation.NamespaceUri().CopyFrom(temp);
      if (status.IsBad())
      {
        UASDK_RETURN_BAD_STATUS(status.Value());
      }
    }
    //unitId
    euInformation.UnitId().Value(data.engineering_units.unit_id);

    //Create Engineering Units
    if (baseConfig.node_id.identifier_type != opcua_node_encoding_numeric)
    {
      status = analogItem->CreateEngineeringUnitsProperty(euInformation);
    }
    else
    {
      uint32_t numericId = GenerateNumericId(baseConfig.namespace_index);
      status = analogItem->CreateEngineeringUnitsProperty(numericId, euInformation);
    }
    if (status.IsBad())
    {
      UASDK_RETURN_BAD_STATUS(status.Value());
    }
  }

  if(data.use_instrument_range != FALSE)
  {
    Range_t instrumentRange(data.instrument_range.low, data.instrument_range.high);

    if (baseConfig.node_id.identifier_type != opcua_node_encoding_numeric)
    {
      status = analogItem->CreateInstrumentRangeProperty(instrumentRange);
    }
    else
    {
      uint32_t numericId = GenerateNumericId(baseConfig.namespace_index);
      status = analogItem->CreateInstrumentRangeProperty(numericId, instrumentRange);
    }
    if (status.IsBad())
    {
      UASDK_RETURN_BAD_STATUS(status.Value());
    }
  }

  IntrusivePtr_t<IVariableNode_t> analogItemNode = analogItem->GetVariableNode();
  status = UpdateEssentialsForHelper(baseVariableConfig, aliasId, displayNameTranslator, analogItemNode);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  //Add definition and Value precision
  return CreateDefinitionAndValuePrecisionProperty(data.data_item_config, *analogItem);
#else
return OpcUa_BadNotSupported;
#endif  //#if (UASDK_USE_DATA_ACCESS_HELPERS > 0)
}


uasdk::Status_t UAServer_t::CreateTwoStateDiscrete(const UA_TwoStateDiscrete_t& data)
{
#if ((UASDK_USE_HELPERS > 0) && (UASDK_USE_DATA_ACCESS_HELPERS > 0))
  UA_DataItem_t dataItemConfig = data.data_item_config;
  UA_BaseDataVariable_t baseVariableConfig = dataItemConfig.data_variable_config;
  UA_Base_t baseConfig = baseVariableConfig.base_config;

  if (((dataItemConfig.use_definition != FALSE) && (!dataItemConfig.definition.data || (dataItemConfig.definition.length <= 0)))
    || !data.false_state_handle || !data.true_state_handle
    || !baseVariableConfig.base_config.node_handle || !baseVariableConfig.base_config.display_name_handle
    || !baseVariableConfig.base_config.namespace_index || (baseVariableConfig.value_type == UA_TYPE_Invalid) || (baseVariableConfig.value_type > UA_TYPE_XmlElement))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  IntrusivePtr_t<TwoStateDiscrete_t> twoStateDiscrete;
  IntrusivePtr_t<const NodeId_t> aliasId;
  IntrusivePtr_t<const NodeId_t> nodeId;
  IntrusivePtr_t<const ILocalizableText_t> displayNameTranslator;
  String_t browseName_;

  Status_t status = CreateEssenstialsForHelpers(baseConfig, aliasId, nodeId, displayNameTranslator, browseName_);
  if (status.IsBad() || !aliasId.is_set() || !nodeId.is_set() || !displayNameTranslator.is_set() || (browseName_.Length() <= 0))
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  //Create Mandatory Property
  String_t temp;
  TwoStateDiscrete_t::MandatoryPropertyValues_t propertyValues;
  IntrusivePtr_t<const ILocalizableText_t> trueStateDisplayNameTranslator;
  IntrusivePtr_t<const ILocalizableText_t> falseStateDisplayNameTranslator;

  // True State
  status = CreatePropertyValuesForTwoStateDiscrete(data.true_state_handle, trueStateDisplayNameTranslator, propertyValues.trueState);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
  
  //False State
  status = CreatePropertyValuesForTwoStateDiscrete(data.false_state_handle, falseStateDisplayNameTranslator, propertyValues.falseState);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  //Create Two State Discrete
  switch (baseConfig.node_id.identifier_type)
  {
    case opcua_node_encoding_numeric:
      {
        TwoStateDiscrete_t::MandatoryPropertyNumericIds_t propertyIds;

        propertyIds.trueState = GenerateNumericId(baseConfig.namespace_index);
        propertyIds.falseState = GenerateNumericId(baseConfig.namespace_index);

        twoStateDiscrete = TwoStateDiscrete_t::CreateWithNumericId(baseConfig.namespace_index, baseConfig.node_id.numeric_identifier, addressSpace,
          browseName_, propertyIds, propertyValues, status);
      }
      break;

    case opcua_node_encoding_string:
      {
        const NodeIdString_t& stringId = static_cast<const NodeIdString_t&>(*nodeId);
        twoStateDiscrete = TwoStateDiscrete_t::CreateWithStringId(baseConfig.namespace_index, stringId.Identifer(), addressSpace, browseName_, propertyValues, status);
      }
      break;

    case opcua_node_encoding_guid:
      {
        const NodeIdGuid_t& guidNodeId = static_cast<const NodeIdGuid_t&>(*nodeId);
        twoStateDiscrete = TwoStateDiscrete_t::CreateWithGuidId(baseConfig.namespace_index, guidNodeId.Identifer(), addressSpace, browseName_, propertyValues, status);
      }
      break;

    case opcua_node_encoding_bytestring:
      twoStateDiscrete = TwoStateDiscrete_t::CreateWithOpaqueId(baseConfig.namespace_index, browseName_.Payload(), addressSpace, browseName_, propertyValues, status);
      break;

    default:
      return OpcUa_BadInvalidArgument;
  }

  if (status.IsBad() || !twoStateDiscrete.is_set())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
  twoStateDiscrete->Hide(false);

  IntrusivePtr_t<IVariableNode_t> twoStateDiscreteNode = twoStateDiscrete->GetVariableNode();
  status = UpdateEssentialsForHelper(baseVariableConfig, aliasId, displayNameTranslator, twoStateDiscreteNode);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  //Add definition and Value precision
  status = CreateDefinitionAndValuePrecisionProperty(data.data_item_config, *twoStateDiscrete);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  return status;
#else
  return OpcUa_BadNotSupported;
#endif  //#if (UASDK_USE_DATA_ACCESS_HELPERS > 0)
}


uasdk::Status_t UAServer_t::CreateMultiStateDiscrete(const UA_MultiStateDiscrete_t& data)
{
#if ((UASDK_USE_HELPERS > 0) && (UASDK_USE_DATA_ACCESS_HELPERS > 0))
  UA_DataItem_t dataItemConfig = data.data_item_config;
  UA_BaseDataVariable_t baseVariableConfig = dataItemConfig.data_variable_config;
  UA_Base_t baseConfig = baseVariableConfig.base_config;

  if (((dataItemConfig.use_definition != FALSE) && (!dataItemConfig.definition.data || (dataItemConfig.definition.length <= 0)))
    || !data.no_of_values || !data.enum_handle
    || !baseVariableConfig.base_config.node_handle || !baseVariableConfig.base_config.display_name_handle
    || !baseVariableConfig.base_config.namespace_index || (baseVariableConfig.value_type == UA_TYPE_Invalid) || (baseVariableConfig.value_type > UA_TYPE_XmlElement))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  IntrusivePtr_t<const NodeId_t> aliasId;
  IntrusivePtr_t<const NodeId_t> nodeId;
  IntrusivePtr_t<const ILocalizableText_t> displayNameTranslator;
  String_t browseName_;

  Status_t status = CreateEssenstialsForHelpers(baseConfig, aliasId, nodeId, displayNameTranslator, browseName_);
  if (status.IsBad() || !aliasId.is_set() || !nodeId.is_set() || !displayNameTranslator.is_set() || (browseName_.Length() <= 0))
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  //Create Enum Strings Property
  ArrayUA_t<LocalizedText_t> enumStrings;
  status = enumStrings.Initialise(data.no_of_values);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  for (uint16_t i = 0; i < data.no_of_values; i++)
  {
	  const UA_UTF8_string_t* temp = UAServer_Callback_translate_enumstrings( 0, data.enum_handle, i);
    if (!temp || !temp->data || (temp->length <= 0))
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
    }

    IntrusivePtr_t<LocalizedText_t> enumString(new SafeRefCount_t<LocalizedText_t>());
    if (!enumString.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }

    status = enumString->Text().CopyFrom((const char*)temp->data, (temp->length + 1));
    if (status.IsBad())
    {
      UASDK_RETURN_BAD_STATUS(status.Value());
    }

    enumStrings[i] = enumString;
  }

  IntrusivePtr_t<MultiStateDiscrete_t> multiStateDiscrete;
  switch (baseConfig.node_id.identifier_type)
  {
    case opcua_node_encoding_numeric:
      {
        uint32_t propertyId = GenerateNumericId(baseConfig.namespace_index);
        multiStateDiscrete = MultiStateDiscrete_t::CreateWithNumericId<Byte_t>(baseConfig.namespace_index, baseConfig.node_id.numeric_identifier, addressSpace,
                                                                               browseName_, propertyId, enumStrings, status);
      }
      break;

    case opcua_node_encoding_string:
      {
        const NodeIdString_t& stringId = static_cast<const NodeIdString_t&>(*nodeId);
        multiStateDiscrete = MultiStateDiscrete_t::CreateWithStringId<Byte_t>(baseConfig.namespace_index, stringId.Identifer(), addressSpace, browseName_, enumStrings, status);
      }
      break;

    case opcua_node_encoding_guid:
      {
        const NodeIdGuid_t& guidNodeId = static_cast<const NodeIdGuid_t&>(*nodeId);
        multiStateDiscrete = MultiStateDiscrete_t::CreateWithGuidId<Byte_t>(baseConfig.namespace_index, guidNodeId.Identifer(), addressSpace, browseName_, enumStrings, status);
      }
    break;

    case opcua_node_encoding_bytestring:
      multiStateDiscrete = MultiStateDiscrete_t::CreateWithOpaqueId<Byte_t>(baseConfig.namespace_index, browseName_.Payload(), addressSpace, browseName_, enumStrings, status);
      break;

    default:
      return OpcUa_BadInvalidArgument;
  }

  if (status.IsBad() || !multiStateDiscrete.is_set())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
  multiStateDiscrete->Hide(false);

  IntrusivePtr_t<IVariableNode_t> multiStateDiscreteNode = multiStateDiscrete->GetVariableNode();
  status = UpdateEssentialsForHelper(baseVariableConfig, aliasId, displayNameTranslator, multiStateDiscreteNode);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  //Add definition and Value precision
  return CreateDefinitionAndValuePrecisionProperty(data.data_item_config, *multiStateDiscrete);
#else
return OpcUa_BadNotSupported;
#endif
}


uasdk::Status_t UAServer_t::UACreateFile(const UA_File_t& data)
{
#if ((UASDK_USE_HELPERS > 0) && (UASDK_USE_FILE_OBJECT_HELPERS > 0))
  UA_Base_t baseConfig = data.base_config;

  if (!data.base_config.node_handle || !data.base_config.display_name_handle || !data.base_config.namespace_index)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  IntrusivePtr_t<const NodeId_t> aliasId;
  IntrusivePtr_t<const NodeId_t> nodeId;
  IntrusivePtr_t<const ILocalizableText_t> displayNameTranslator;
  String_t browseName_;

  Status_t status = CreateEssenstialsForHelpers(baseConfig, aliasId, nodeId, displayNameTranslator, browseName_);
  if (status.IsBad() || !aliasId.is_set() || !nodeId.is_set() || !displayNameTranslator.is_set() || (browseName_.Length() <= 0))
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  if (!addressSpace.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  IntrusivePtr_t<FileUA_t> file(new SafeRefCount_t<FileUA_t>());
  if (!file.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  Boolean_t writable((data.writable == TRUE)? true : false);
  Boolean_t userWritable((data.user_writable > 0)? true : false);
  File_t::MandatoryPropertyValues_t propertyValues = {writable, userWritable, file};

  IntrusivePtr_t<File_t> fileObjectHelper;
  switch (baseConfig.node_id.identifier_type)
  {
    case opcua_node_encoding_numeric:
      {

        File_t::MandatoryPropertyNumericIds_t propertyIds;
        propertyIds.sizeId = GenerateNumericId(baseConfig.namespace_index);
        propertyIds.writableId = GenerateNumericId(baseConfig.namespace_index);
        propertyIds.userWritableId = GenerateNumericId(baseConfig.namespace_index);
        propertyIds.openCountId = GenerateNumericId(baseConfig.namespace_index);

        fileObjectHelper = File_t::CreateWithNumericId(baseConfig.namespace_index, baseConfig.node_id.numeric_identifier, addressSpace,
          browseName_, propertyIds, propertyValues, fileTransferRouter, status);
      }
      break;

    case opcua_node_encoding_string:
      {
        const NodeIdString_t& stringId = static_cast<const NodeIdString_t&>(*nodeId);
        fileObjectHelper = File_t::CreateWithStringId(baseConfig.namespace_index, stringId.Identifer(), addressSpace, browseName_, propertyValues, fileTransferRouter, status);
      }
      break;

    case opcua_node_encoding_guid:
      {
        const NodeIdGuid_t& guidNodeId = static_cast<const NodeIdGuid_t&>(*nodeId);
        fileObjectHelper = File_t::CreateWithGuidId(baseConfig.namespace_index, guidNodeId.Identifer(), addressSpace, browseName_, propertyValues, fileTransferRouter, status);
      }
      break;

    case opcua_node_encoding_bytestring:
      fileObjectHelper = File_t::CreateWithOpaqueId(baseConfig.namespace_index, browseName_.Payload(), addressSpace, browseName_, propertyValues, fileTransferRouter, status);
      break;

    default:
      return OpcUa_BadInvalidArgument;
  }

  if (status.IsBad() || !fileObjectHelper.is_set() || !fileObjectHelper->Node().is_set())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }
  fileObjectHelper->Hide(false);

  status = addressSpace->AddNodeAlias(*(fileObjectHelper->Node()->NodeId()), aliasId);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  status = fileObjectHelper->Node()->DisplayName(displayNameTranslator);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  status = UpdateDescriptionTranslator(fileObjectHelper->Node(), data.base_config.description_handle);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  //User visibilty
  status = CreateApplicationContextForUserVisibility(data.base_config.user_visibility, fileObjectHelper->Node());
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  //Now Initialize the FileUA_t object
  if (!core.is_set() || !core->GetConfiguration(status).is_set() || status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }
  status = file->Initialise(fileObjectHelper->Node()->NodeId(), core->GetConfiguration(status), fileTransferRouter);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  return OpcUa_Good;
#else
  UASDK_UNUSED(data);
  return OpcUa_BadNotSupported;
#endif  //((UASDK_USE_HELPERS > 0) && (UASDK_USE_FILE_OBJECT_HELPERS> 0))
}


uasdk::Status_t UAServer_t::AddToFolder(uintptr_t folder_handle, uintptr_t node_handle)
{
  uint16_t viewMask = 0;
  return AddToFolder(folder_handle, node_handle, viewMask);
}


uasdk::Status_t UAServer_t::AddToFolder(uintptr_t folder_handle, uintptr_t node_handle, uint16_t view_mask)
{
  Status_t status;
  IntrusivePtr_t<const NodeId_t> viewNodeId;
  if (view_mask > 1)
  {
    viewNodeId = GetViewNodeId(view_mask, status);
  }

  if (!addressSpace.is_set() || !folder_handle || !node_handle)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  if (!namespaceIndexForAlias)
  {
    status = UpdateNamespaceIndexForAlias();
    if (status.IsBad() || !namespaceIndexForAlias)
    {
      UASDK_RETURN_BAD_STATUS(status.Value());
    }
  }

  NodeIdNumeric_t sourceNodeId(namespaceIndexForAlias, static_cast<uint32_t>(folder_handle));
  IntrusivePtr_t<INode_t> sourceNode = addressSpace->FindNode(sourceNodeId, status);
  if (status.IsBad() || !sourceNode.is_set())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  NodeIdNumeric_t targetNodeId(namespaceIndexForAlias, static_cast<uint32_t>(node_handle));
  IntrusivePtr_t<INode_t> targetNode = addressSpace->FindNode(targetNodeId, status);
  if (status.IsBad() || !targetNode.is_set())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  return AddressSpaceUtilities_t::CreateSlowReference(*addressSpace, sourceNode->NodeId(), targetNode->NodeId(), OpcUaId_Organizes, viewNodeId);
}


uasdk::Status_t UAServer_t::AddToObjectsFolder(uintptr_t node_handle)
{
  if (!addressSpace.is_set() || !node_handle)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  Status_t status;

  NodeIdNumeric_t targetNodeId(namespaceIndexForAlias, static_cast<uint32_t>(node_handle));
  IntrusivePtr_t<INode_t> targetNode = addressSpace->FindNode(targetNodeId, status);
  if (status.IsBad() || !targetNode.is_set())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  NodeIdNumeric_t objectFolderNodeId(0, OpcUaId_ObjectsFolder);
  IntrusivePtr_t<IObjectNode_t> objectFolderNode = addressSpace->FindObjectNode(objectFolderNodeId, status);
  if (status.IsBad() || !objectFolderNode.is_set())
  {
    return status;
  }

  return AddressSpaceUtilities_t::CreateSlowReference(*addressSpace, objectFolderNode->NodeId(), targetNode->NodeId(), OpcUaId_Organizes);
}

bool UAServer_t::IsReadOperationDeferrable(uintptr_t readContext)
{
  UASDK_UNUSED(readContext);
  return false;
  //return !(IsReadOperationDeferred(readContext));
}

bool UAServer_t::IsReadOperationDeferred(uintptr_t readContext)
{
  if (!readContext)
  {
    LOG_BAD_STATUS(OpcUa_BadInvalidArgument);
    return false;
  }

  ValueAttributeReaderWriterForCAPI_t* reader = reinterpret_cast<ValueAttributeReaderWriterForCAPI_t*> (readContext);
  if(!reader)
  {
    LOG_BAD_STATUS(OpcUa_BadUnexpectedError);
    return false;
  }

  return reader->IsReadOperationDeferred();
}

uint32_t UAServer_t::GetReadTimeOutHint(uintptr_t readContext)
{
  if (!readContext)
  {
	LOG_BAD_STATUS(OpcUa_BadInvalidArgument);
	return false;
  }

  ValueAttributeReaderWriterForCAPI_t* reader = reinterpret_cast<ValueAttributeReaderWriterForCAPI_t*> (readContext);
  if(!reader)
  {
	LOG_BAD_STATUS(OpcUa_BadUnexpectedError);
	return false;
  }

  return reader->GetReadTimeOutHint();
}

Status_t UAServer_t::DeferReadOperation(uintptr_t readContext, uintptr_t* deferralHandle)
{
  if (!readContext || !deferralHandle)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  *deferralHandle = readContext;

  ValueAttributeReaderWriterForCAPI_t* reader = reinterpret_cast<ValueAttributeReaderWriterForCAPI_t*> (readContext);
  if (!reader)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  return reader->UpdateDeferralHandle(deferralHandle);
}

uasdk::Status_t UAServer_t::ReadDeferralComplete(uintptr_t deferralHandle, UA_Status_t statusCode)
{
  if ((statusCode > 0) || !deferralHandle)
  {
    UASDK_RETURN_BAD_STATUS(statusCode);
  }

  ValueAttributeReaderWriterForCAPI_t* reader = reinterpret_cast<ValueAttributeReaderWriterForCAPI_t*> (deferralHandle);
  if (!reader)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  reader->CallApplicationLayerRead();

  return reader->ReadDeferralComplete();
}

uasdk::Status_t UAServer_t::UAServerMemoryInfo(uint32_t& totalMemoryProvided, uint32_t& memoryUnusable, uint32_t& maxMemoryUsedThisRun, uint32_t& totalMemoryRecommended)
{
#if (UASDK_USE_SYSTEM_HEAP == 0)
  IAllocator_t* allocator = Allocatable_t::Allocator();
  if (!allocator)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadConfigurationError);
  }

  uint32_t usableMemory;
  uint32_t maxMemoryCommitted;
  Status_t status = allocator->MemoryInfo(totalMemoryProvided, usableMemory, maxMemoryCommitted, maxMemoryUsedThisRun, totalMemoryRecommended);
  if (status.IsBad())
  {
    UASDK_RETURN_BAD_STATUS(status.Value());
  }

  memoryUnusable = maxMemoryCommitted - usableMemory;

#else
  totalMemoryProvided = 0;
  memoryUnusable = 0;
  maxMemoryUsedThisRun = 0;
  totalMemoryRecommended = 0;
#endif  //UASDK_USE_SYSTEM_HEAP

  return OpcUa_Good;
}


uasdk::Status_t UAServer_t::PerformWrite(uintptr_t writeContext, UA_Value_t dataValue, int64_t* sourceTimeStamp, bool_t completesAsynchronously, uint32_t* newLengthOfArray)
{
  if (!writeContext || !sourceTimeStamp || !newLengthOfArray)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  UASDK_UNUSED(completesAsynchronously);

  ValueAttributeReaderWriterForCAPI_t* writer = reinterpret_cast<ValueAttributeReaderWriterForCAPI_t*> (writeContext);
  if (!writer)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  writer->PerformWrite(dataValue, *sourceTimeStamp, *newLengthOfArray);

  return OpcUa_Good;
}


uasdk::Status_t UAServer_t::SetWriteOperationLevelResultCode(uintptr_t writeContext, Status_t resultCode)
{
  if (!writeContext)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  ValueAttributeReaderWriterForCAPI_t* writer = reinterpret_cast<ValueAttributeReaderWriterForCAPI_t*> (writeContext);
  if (!writer)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }
  
  return writer->SetWriteOperationLevelResultCode(resultCode).Value();
}


uasdk::Status_t UAServer_t::PerformRead(uintptr_t readContext, UA_Value_t dataValue, int64_t sourceTimestamp, uint32_t dataQuality)
{
  if (!readContext)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  ValueAttributeReaderWriterForCAPI_t* reader = reinterpret_cast<ValueAttributeReaderWriterForCAPI_t*> (readContext);
  if (!reader)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

  reader->PerformRead(dataValue, dataQuality, sourceTimestamp);

  return OpcUa_Good;
}


uasdk::Status_t UAServer_t::AddIpAddress(uint8_t* ipAddress)
{
  UASDK_UNUSED(ipAddress);
  return OpcUa_Good;
}


uasdk::Status_t UAServer_t::ClearAllIpAddresses(void)
{
  return OpcUa_Good;
}


uasdk::Status_t UAServer_t::AddHostname(const char* hostname)
{
  UASDK_UNUSED(hostname);
  return OpcUa_Good;
}


uasdk::Status_t UAServer_t::ClearAllHostnames(void)
{
  return OpcUa_Good;

}


uasdk::Status_t UAServer_t::SetURI(const char* uri)
{
  IntrusivePtr_t<String_t> applicationURI(new SafeRefCount_t<String_t>());
  if (!applicationURI.is_set())
  {
    return OpcUa_BadOutOfMemory;
  }
  Status_t result = applicationURI->CopyFrom(uri);
  if (result.IsBad())
  {
    return result;
  }

  core->GetConfiguration(result)->ApplicationURI(applicationURI);
  return result;
}


UA_Server_state_t UAServer_t::GetServerState(bool& shutdown_complete)
{
  UASDK_UNUSED(shutdown_complete);
  return opcua_server_state_unknown;
}

#if (UASDK_INCLUDE_EVENTS > 0)
  Status_t UAServer_t::FireEvent(IntrusivePtr_t<IAttributeAccess_t> event,
																 IntrusivePtr_t<NodeId_t>& eventSource,
                                 IntrusivePtr_t<UtcTime_t>& receiveTime)
  {
  	if (core.is_set())
    {
      return core->FireEvent(event, eventSource, receiveTime);
    }

		UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
  }

	Status_t UAServer_t::FireSystemStatusChangeEvent(ServerState_t::Enum_t state)
	{
		Status_t status;

		//SourceNode
		IntrusivePtr_t<NodeId_t> sourceNodeId = EventHelper_t::GetServerNodeId();

		//SourceName
		IntrusivePtr_t<String_t> sourceName = new SafeRefCount_t<String_t>();
		status = sourceName->CopyFrom("SystemName-LocalHost");
		if (status.IsBad())
		{
			return status;
		}

		//Message
		//Adding Englist Text
		IntrusivePtr_t<ILocalizableText_t> message;
		String_t locale, text;
		locale.CopyFrom(LOCALE_EN);
		if (ServerState_t::OPCUA_SERVER_STATE_RUNNING == state)
		{
			text.CopyFrom("System is running now");
		}
		else if (ServerState_t::OPCUA_SERVER_STATE_SHUTDOWN == state)
		{
			text.CopyFrom("System is shutting down now");
		}

		status = EventHelper_t::AddToLocalizableTextStored(locale, text, message);
		if (status.IsBad())
		{
			return status;
		}
		//Adding French Text
		locale.CopyFrom(LOCALE_FR);
		if (ServerState_t::OPCUA_SERVER_STATE_RUNNING == state)
		{
			text.CopyFrom("Le système est en cours d'exécution maintenant");
		}
		else if (ServerState_t::OPCUA_SERVER_STATE_SHUTDOWN == state)
		{
			text.CopyFrom("Le système est en cours d'arrêt maintenant");
		}

		status = EventHelper_t::AddToLocalizableTextStored(locale, text, message);
		if (status.IsBad())
		{
			return status;
		}
		//Adding German Text
		locale.CopyFrom(LOCALE_GR);
		if (ServerState_t::OPCUA_SERVER_STATE_RUNNING == state)
		{
			text.CopyFrom("System läuft jetzt");
		}
		else if (ServerState_t::OPCUA_SERVER_STATE_SHUTDOWN == state)
		{
			text.CopyFrom("System heruntergefahren wird jetzt");
		}

		status = EventHelper_t::AddToLocalizableTextStored(locale, text, message);
		if (status.IsBad())
		{
			return status;
		}

		// Severity
		IntrusivePtr_t<UInt16_t> severity = new SafeRefCount_t<UInt16_t>();
		if (!severity.is_set())
		{
			return status;
		}
		severity->Value(EventSeverity_t::OPCUA_EVENT_SEVERITY_LOW);

		//Server State
		IntrusivePtr_t<ServerState_t> serverState = new SafeRefCount_t<ServerState_t>();
		if (!serverState.is_set())
		{
			return status;
		}
		serverState->Value() = /*ServerState_t::OPCUA_SERVER_STATE_RUNNING*/state;

		IntrusivePtr_t<SystemStatusChangeEventTypeData_t> systemStatusChangeEvent;
		IntrusivePtr_t<const ArrayUA_t<String_t> > localeIds;//Empty parameter is passed. The below method will take the default values.

		if (!core.is_set())
		{
			UASDK_RETURN_BAD_STATUS(OpcUa_BadConfigurationError);
		}

		IntrusivePtr_t<IServerConfiguration_t> configuration = core->GetConfiguration(status);
		if (status.IsBad() || !configuration.is_set())
		{
			UASDK_RETURN_BAD_STATUS(OpcUa_BadConfigurationError);
		}

		status = EventHelper_t::CreateEventAndSetBaseEventProperties(configuration,
			sourceNodeId,
			sourceName,
			severity->Value(),
			message,
			localeIds,
			systemStatusChangeEvent,
			false);

		systemStatusChangeEvent->SystemState() = serverState;

		if (status.IsBad())
		{
			return status;
		}

		status = FireEvent(systemStatusChangeEvent, systemStatusChangeEvent->SourceNode(), systemStatusChangeEvent->ReceiveTime());

		return status;
	}

	Status_t UAServer_t::RegisterAuditEventListener(IntrusivePtr_t<IAuditEventListener_t>& auditEventListener)
	{
		return core->RegisterAuditEventListener(auditEventListener);
	}

#endif //UASDK_INCLUDE_EVENTS
}

#endif //UASDK_INCLUDE_SERVER_C_API
#endif //(UASDK_INCLUDE_SERVER)
