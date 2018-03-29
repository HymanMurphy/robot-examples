/* Copyright (c) 2009 - 2013 Embedded Labs Ltd. All Rights Reserved */

/*****************************************************************************/
/** \file ua_server.c
 *  \brief The OPC-UA Embedded Device Server Software Stack API implementation.
 *
 */

/*****************************************************************************/
/* Copyright (c) 2009 - 2011 Embedded Labs Limited.
 *
 * ALL RIGHTS RESERVED.
 *
 * The information contained herein is the confidential and proprietary product
 * of Embedded Labs Limited.  Any unauthorized use, reproduction or 
 * transfer of this information is strictly prohibited.
 */

/*****************************************************************************/
/* Include Files
 */
#include "ua_server.h"
#include "uaserver_t.h"
#include "wrap_buffer_t.h"
#include "read_only_nodes.h"

#if (UASDK_INCLUDE_SERVER)
#if (UASDK_INCLUDE_SERVER_C_API > 0)

#include "file_ua_t.h"

#define MAX_PRIVATE_PASSWORD_LEN 32

using namespace uasdk;

/*****************************************************************************/
/* Defines Macros Types
 */

/*****************************************************************************/
/* Data
*/
static IntrusivePtr_t<UAServer_t> UAServer;


/*****************************************************************************/
/* Functions
 */
extern "C" int64_t UAServer_Get_datetime(void)
{
  return UASDK_datetime();
}

extern "C" void UAServer_Time_emulation_enabled(bool_t enable)
{
  //TODO
  UASDK_UNUSED(enable);
}

extern "C" UA_Status_t UAServer_Initialise(const UA_Configuration_t* config)
{

  if (config == 0)
  {
    return OpcUa_BadConfigurationError;
  }

  IntrusivePtr_t<IServerConfiguration_t> configuration = UAServer_t::ValidateConfiguration(*config);
  if (!configuration.is_set())
  {
    return OpcUa_BadConfigurationError;
  }

  Status_t status;
  IntrusivePtr_t<IAddressSpace_t> addressSpace = UAServer_t::CreateAddressSpace((*config).INTERNALS.ADDRESS_SPACE_HASH_TABLE_NO_OF_BUCKETS, status);
  if (!addressSpace.is_set())
  {
    return OpcUa_BadOutOfMemory;
  }
  configuration->AddressSpace(addressSpace);

  UAServer = new SafeRefCount_t<UAServer_t>();
  if (!UAServer.is_set())
  {
	  return OpcUa_BadOutOfMemory;
  }

  IntrusivePtr_t<WrapBuffer_t> nodeBuffer = new SafeRefCount_t<WrapBuffer_t>();
  if (!nodeBuffer.is_set())
  {
    return OpcUa_BadOutOfMemory;
  }
#if (UA_INCLUDE_STANDARD_ADDRESS_SPACE > 0)
  nodeBuffer->Initialise(const_cast<uint8_t*>(ReadOnlyNodes_t::EMBEDDED_PROFILE_STANDARD_NODES), ReadOnlyNodes_t::EMBEDDED_PROFILE_STANDARD_NODES_LENGTH, false);
#else
  nodeBuffer->Initialise(const_cast<uint8_t*>(ReadOnlyNodes_t::NANO_AND_MICRO_PROFILE_STANDARD_NODES), ReadOnlyNodes_t::NANO_AND_MICRO_PROFILE_STANDARD_NODES_LENGTH, false);
#endif
  nodeBuffer->WriteIndex(nodeBuffer->TotalSize());

  status = addressSpace->ImportNodesFromByteArray(nodeBuffer);
  if (status.IsBad())
  {
    return status.Value();
  }

  status = UAServer->Initialise(configuration);
  if (status.IsBad())
  {
    return status.Value();
  }

  status = UAServer->UpdateNameSpaceArray(*config);
  if (status.IsBad())
  {
    return status.Value();
  }

#if (UA_INCLUDE_SECURITY > 0)
  UA_UTF8_string_t pki_path = { sizeof(SECURITY_CERTIFICATE_DIRECTORY_STORE_PATH) - 1, (const uint8_t*)SECURITY_CERTIFICATE_DIRECTORY_STORE_PATH };
  
  UA_Status_t result = UASecurity_library_initialise(&pki_path);
  if (result != OpcUa_Good)
  {
    return result;
  }

#endif

  return status.Value();
}

extern "C" void UAServer_Terminate(void)
{
  if (!UAServer.is_set())
  {
    return;
  }
  
  UAServer->Terminate();
  UAServer.reset();
}

extern "C" UA_Status_t UAServer_memory_info(
    uint32_t* total_memory_provided,
    uint32_t* memory_unusable,
    uint32_t* max_memory_used_this_run,
    uint32_t* total_memory_recommended)
{
  if (!UAServer.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadConfigurationError);
  }

  if (!total_memory_provided || !memory_unusable || !max_memory_used_this_run || !total_memory_recommended)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument);
  }

  return UAServer->UAServerMemoryInfo(*total_memory_provided, *memory_unusable, *max_memory_used_this_run, *total_memory_recommended).Value();
}

extern "C" UA_Status_t UAServer_Perform_write(uintptr_t write_context,
                                   UA_Value_t data_value,
                                   int64_t* source_timestamp,
                                   bool_t completes_asynchronously,
                                   uint32_t* new_length_of_array)
{
  if (!UAServer.is_set())
  {
    return OpcUa_BadConfigurationError;
  }
  return UAServer->PerformWrite(write_context, data_value, source_timestamp, completes_asynchronously, new_length_of_array).Value();
}

extern "C" void UAServer_Set_write_operation_level_result_code( uintptr_t write_context, UA_Status_t result_code)
{
  if (!UAServer.is_set())
  {
    return;
  }
  UAServer->SetWriteOperationLevelResultCode(write_context, result_code);
}

extern "C" UA_Status_t UAServer_Perform_read(uintptr_t read_context,
                                             UA_Value_t data_value,
                                             int64_t source_timestamp,
                                             UA_Status_t status_code)
{
  if (!UAServer.is_set())
  {
    return OpcUa_BadConfigurationError;
  }

  return UAServer->PerformRead(read_context, data_value, source_timestamp, status_code).Value();
}

extern "C" UA_Status_t UAServer_Add_IP_address(uint8_t* ip_address)
{
  if (!UAServer.is_set())
  {
    return OpcUa_BadConfigurationError;
  }
  UASDK_UNUSED(ip_address);
  return OpcUa_Good;
}

extern "C" UA_Status_t UAServer_Clear_all_IP_addresses(void)
{
  if (!UAServer.is_set())
  {
    return OpcUa_BadConfigurationError;
  }
  return OpcUa_Good;
}

extern "C" UA_Status_t UAServer_Add_hostname(const char* hostname)
{
  if (!UAServer.is_set())
  {
    return OpcUa_BadConfigurationError;
  }
  UASDK_UNUSED(hostname);
  return OpcUa_Good;
}

extern "C" UA_Status_t UAServer_Clear_all_hostnames(void)
{
  if (!UAServer.is_set())
  {
    return OpcUa_BadConfigurationError;
  }
  return OpcUa_Good;
}

#if (UA_INCLUDE_SECURITY == 0)
extern "C" UA_Status_t UAServer_Generate_certificate( void )
{
  return OpcUa_BadNotSupported;
}

extern "C" UA_Status_t UAServer_Get_certificate_size(uint32_t* size_in_bytes)
{
  UASDK_UNUSED(size_in_bytes);
  return OpcUa_BadNotSupported;
}

extern "C" UA_Status_t UAServer_Read_certificate(UA_Byte_string_t* certificate)
{
  UASDK_UNUSED(certificate);
  return OpcUa_BadNotSupported;
}

extern "C" UA_Status_t UAServer_Write_certificate(UA_Byte_string_t* certificate)
{
  UASDK_UNUSED(certificate);
  return OpcUa_BadNotSupported;
}
#endif

extern "C" UA_Status_t UAServer_New_connection(uint64_t connection_id)
{
  if (!UAServer.is_set())
  {
    return OpcUa_BadConfigurationError;
  }
  return UAServer->TcpipNewConnection(connection_id).Value();
}

extern "C" UA_Status_t UAServer_Connection_closed(uint64_t connection_id)
{
  if (!UAServer.is_set())
  {
    return OpcUa_BadConfigurationError;
  }
  return UAServer->TcpipConnectionClosed(connection_id).Value();
}

UA_Status_t UAServer_New_data_received(void* read_context, uint64_t connection_id)
{
  if (!UAServer.is_set())
  {
    return OpcUa_BadConfigurationError;
  }
  return UAServer->TcpipNewDataReceived(read_context, connection_id).Value();
}

extern "C" UA_Status_t UAServer_Get_data_to_send(void* write_context, uint64_t connection_id)
{
  if (!UAServer.is_set())
  {
    return OpcUa_BadConfigurationError;
  }
  return UAServer->GetDataToSend(write_context, connection_id).Value();
}

extern "C" uint32_t UAServer_Ready_to_receive(uint64_t connection_id, bool_t* result)
{
  UASDK_UNUSED(connection_id);
  UASDK_UNUSED(result);
  return OpcUa_BadNotSupported;
}

extern "C" void UAServer_Poll(void)
{
  if (!UAServer.is_set())
  {
    return;
  }
  UAServer->Poll();
}

extern "C" UA_Status_t UAServer_Delete_all_nodes(void)
{
  return OpcUa_BadNotSupported;
}

extern "C" UA_Status_t UAServer_Delete_node(uintptr_t node_handle)
{
  if (!UAServer.is_set())
  {
    return OpcUa_BadConfigurationError;
  }
  return UAServer->DeleteNode(node_handle).Value();
}

extern "C" void UAServer_Init_config_structure_Base(UA_Base_t* configuration)
{
  if (configuration != 0)
  {
    configuration->description_handle = 0;
    configuration->display_name_handle = 0;
    configuration->node_handle = 0;
    configuration->user_visibility = 0xFFFF;
    configuration->namespace_index = 1;

    configuration->node_id.identifier_type = opcua_node_encoding_bytestring;
    configuration->node_id.string_identifier.data = 0;
    configuration->node_id.string_identifier.length = -1;
    configuration->node_id.guid_identifier = 0;
  }
}

extern "C" void UAServer_Init_config_structure_Folder(UA_Folder_t* configuration)
{
  if (configuration != 0)
  {
    UAServer_Init_config_structure_Base(configuration);
  }
}

extern "C" UA_Status_t UAServer_Create_Folder(const UA_Folder_t* configuration)
{
  if (!UAServer.is_set())
  {
    return OpcUa_BadConfigurationError;
  }
  return UAServer->CreateFolder(*configuration).Value();
}

extern "C" void UAServer_Init_config_structure_View(UA_View_t* configuration)
{
  if (configuration != 0)
  {
    UAServer_Init_config_structure_Base(configuration);
  }
}

extern "C" UA_Status_t UAServer_Create_View(const UA_View_t* configuration)
{
  if (!UAServer.is_set())
  {
    return OpcUa_BadConfigurationError;
  }
  return UAServer->CreateView(*configuration).Value();
}

extern "C" void UAServer_Init_config_structure_Method(UA_Method_t* configuration)
{
  if (configuration != 0)
  {
    UAServer_Init_config_structure_Base(&configuration->base_config);
    configuration->executable = true;
    configuration->user_executable = true;
  }
}

extern "C" UA_Status_t UAServer_Create_Method(const UA_Method_t* configuration)
{
  if (!UAServer.is_set())
  {
    return OpcUa_BadConfigurationError;
  }
  return UAServer->CreateMethod(*configuration).Value();
}

extern "C" void UAServer_Init_config_structure_BaseDataVariable(UA_BaseDataVariable_t* configuration)
{
  if (configuration != 0)
  {
    UAServer_Init_config_structure_Base(&configuration->base_config);
    configuration->value_type = UA_TYPE_Invalid;
    configuration->max_array_length = 0;
    configuration->user_read_permissions = 0xFFFF;
    configuration->user_write_permissions = 0x0000;
  }
}

extern "C" UA_Status_t UAServer_Create_BaseDataVariable(const UA_BaseDataVariable_t* configuration)
{
  if (!UAServer.is_set())
  {
    return OpcUa_BadConfigurationError;
  }
  return UAServer->CreateBaseDataVariable(*configuration).Value();
}

extern "C" void UAServer_Init_config_structure_DataItem(UA_DataItem_t* configuration)
{
  if (configuration != 0)
  {
    UAServer_Init_config_structure_BaseDataVariable(&configuration->data_variable_config);
    configuration->definition.data = 0;
    configuration->definition.length = 0;
    configuration->use_definition = false;
    configuration->value_precision = 0.0f;
    configuration->use_value_precision = false;
  }
}

extern "C" UA_Status_t UAServer_Create_DataItem(const UA_DataItem_t* configuration)
{
  if (!UAServer.is_set())
  {
    return OpcUa_BadConfigurationError;
  }
  return UAServer->CreateDataItem(*configuration).Value();
}

extern "C" void UAServer_Init_config_structure_AnalogItem(UA_AnalogItem_t* configuration)
{
  if (configuration != 0)
  {
    UAServer_Init_config_structure_DataItem(&configuration->data_item_config);
    configuration->engineering_units.description_handle = 0;
    configuration->engineering_units.display_name_handle = 0;
    configuration->engineering_units.namespace_uri.data = 0;
    configuration->engineering_units.namespace_uri.length = 0;
    configuration->engineering_units.unit_id = -1;
    configuration->use_engineering_units = false;
    configuration->EU_range.low = 0.0f;
    configuration->EU_range.high = 0.0f;
    configuration->instrument_range.low = 0.0f;
    configuration->instrument_range.high = 0.0f;
    configuration->use_instrument_range = false;
  }
}

extern "C" UA_Status_t UAServer_Create_AnalogItem(const UA_AnalogItem_t* configuration)
{
  if (!UAServer.is_set())
  {
    return OpcUa_BadConfigurationError;
  }
  return UAServer->CreateAnalogItem(*configuration).Value();
}

extern "C" void UAServer_Init_config_structure_TwoStateDiscrete(UA_TwoStateDiscrete_t* configuration)
{
  if (configuration != 0)
  {
    UAServer_Init_config_structure_DataItem(&configuration->data_item_config);
    configuration->data_item_config.data_variable_config.value_type = UA_TYPE_Boolean;
    configuration->false_state_handle = 0;
    configuration->true_state_handle = 0;
  }
}

extern "C" UA_Status_t UAServer_Create_TwoStateDiscrete(const UA_TwoStateDiscrete_t* configuration)
{
  if (!UAServer.is_set())
  {
    return OpcUa_BadConfigurationError;
  }
  return UAServer->CreateTwoStateDiscrete(*configuration).Value();
}

extern "C" void UAServer_Init_config_structure_MultiStateDiscrete(UA_MultiStateDiscrete_t* configuration)
{
  if (configuration != 0)
  {
    UAServer_Init_config_structure_DataItem(&configuration->data_item_config);
    configuration->data_item_config.data_variable_config.value_type = UA_TYPE_UInt32;
    configuration->enum_handle = 0;
    configuration->no_of_values = 0;
  }
}

extern "C" UA_Status_t UAServer_Create_MultiStateDiscrete(const UA_MultiStateDiscrete_t* configuration)
{
  if (!UAServer.is_set())
  {
    return OpcUa_BadConfigurationError;
  }
  return UAServer->CreateMultiStateDiscrete(*configuration).Value();
}

extern "C" void UAServer_Init_config_structure_File(UA_File_t* configuration)
{
  if (configuration != 0)
  {
    UAServer_Init_config_structure_Base(&configuration->base_config);
    configuration->writable = false;
    configuration->user_writable = 0xFFFF;
  }
}

#if (UA_INCLUDE_FILE_TRANSFER_METHODS > 0)
extern "C" UA_Status_t UAServer_Create_File(const UA_File_t* configuration)
{
  if (!UAServer.is_set())
  {
    return OpcUa_BadConfigurationError;
  }
  return UAServer->UACreateFile(*configuration).Value();
}
#endif

extern "C" UA_Status_t UAServer_Add_to_folder(uintptr_t folder_handle, uintptr_t node_handle)
{
  if (!UAServer.is_set())
  {
    return OpcUa_BadConfigurationError;
  }
  return UAServer->AddToFolder(folder_handle, node_handle).Value();
}

extern "C" UA_Status_t UAServer_Add_to_folder_with_view_mask(uintptr_t folder_handle,
  uintptr_t node_handle,
  uint16_t view_mask)
{
  if (!UAServer.is_set())
  {
    return OpcUa_BadConfigurationError;
  }
  return UAServer->AddToFolder(folder_handle, node_handle, view_mask).Value();
}

extern "C" UA_Status_t UAServer_Add_to_objects_folder(uintptr_t node_handle)
{
  if (!UAServer.is_set())
  {
    return OpcUa_BadConfigurationError;
  }
  return UAServer->AddToObjectsFolder(node_handle).Value();
}

extern "C" UA_Status_t UAServer_Set_URI(const char* uri)
{
  if (!UAServer.is_set())
  {
    return OpcUa_BadConfigurationError;
  }

  return UAServer->SetURI(uri).Value();
}

extern "C" UA_Status_t UAServer_Start( const char* license )
{
  if (!UAServer.is_set())
  {
    return OpcUa_BadConfigurationError;
  }

  if (!license)
  {
    license = "";
  }

  String_t lic;
  Status_t status = lic.CopyFrom(license);
  if (status.IsBad())
  {
    return status.Value();
  }

  return UAServer->Start(lic).Value();
}

extern "C" UA_Status_t UAServer_Stop( void )
{
  if (!UAServer.is_set())
  {
    return OpcUa_BadConfigurationError;
  }
  return UAServer->Stop().Value();
}

extern "C" UA_Server_state_t UAServer_Get_state( bool_t* shutdown_complete )
{
  if (!UAServer.is_set())
  {
    return opcua_server_state_no_configuration;
  }

  bool complete = false;
  UA_Server_state_t state = opcua_server_state_unknown;//TODO = UAServer->Get_server_state(complete);
  if (shutdown_complete != 0)
  {
    *shutdown_complete = complete;
  }
  return state;
}

extern "C" void* UAServer_Calloc(size_t size)
{
  return UASDK_Calloc(size);
}

extern "C" void* UAServer_Malloc(size_t size)
{
  return UASDK_Malloc(size);
}

extern "C" void* UAServer_Realloc(void* ptr, size_t size)
{
  return UASDK_Realloc(ptr, size);
}

extern "C" void UAServer_Free(void* ptr)
{
  return UASDK_Free(ptr);
}

extern "C" bool_t UAServer_Is_read_operation_asynchronous(uintptr_t read_context)
{
  UASDK_UNUSED(read_context);
  return TRUE;
}

extern "C" bool_t UAServer_Is_read_operation_deferrable(uintptr_t read_context)
{
  return (UAServer->IsReadOperationDeferrable(read_context) != 0);
}

extern "C" bool_t UAServer_Is_read_operation_deferred(uintptr_t read_context)
{
  return (UAServer->IsReadOperationDeferred(read_context) != 0);
}

extern "C" uint32_t UAServer_Get_Read_Timeout_Hint(uintptr_t read_context)
{
  return UAServer->GetReadTimeOutHint(read_context);
}

extern "C" UA_Status_t UAServer_Defer_read_operation(uintptr_t read_context, uintptr_t* deferral_handle)
{
  return (UAServer->DeferReadOperation(read_context, deferral_handle).Value());
}

extern "C" UA_Status_t UAServer_Read_deferral_complete(uintptr_t deferral_handle, UA_Status_t status_code)
{
  if (!UAServer.is_set())
  {
    return OpcUa_BadConfigurationError;
  }

  return UAServer->ReadDeferralComplete(deferral_handle, status_code).Value();
}

#if (UA_INCLUDE_FILE_TRANSFER_METHODS > 0)
extern "C" UA_Status_t UAServer_File_Size_result(
    uintptr_t context,
    uint64_t size,
    UA_Status_t result)
{
  FileSizeContext_t& ctx = *reinterpret_cast<FileSizeContext_t*>(context);
  ctx.size = size;
  ctx.result = result;
  return OpcUa_Good;
}

extern "C" UA_Status_t UAServer_File_Open_result(
    uintptr_t context,
    uint32_t file_handle,
    UA_Status_t result)
{
  FileOpenContext_t& ctx = *reinterpret_cast<FileOpenContext_t*>(context);
  ctx.file_handle = file_handle;
  ctx.result = result;
  return OpcUa_Good;
}

extern "C" UA_Status_t UAServer_File_Close_result(
    uintptr_t context,
    UA_Status_t result)
{
  FileGenericContext_t& ctx = *reinterpret_cast<FileGenericContext_t*>(context);
  ctx.result = result;
  return OpcUa_Good;
}

extern "C" UA_Status_t UAServer_File_Read_result(
    uintptr_t context,
    UA_Byte_string_t data,
    UA_Status_t result)
{
  FileReadContext_t& ctx = *reinterpret_cast<FileReadContext_t*>(context);

  if (result != OpcUa_Good)
  {
    return result;
  }

  if ( (data.length < 0) || ((data.length > 0) && (data.data == 0)) )
  {
    return OpcUa_BadInvalidArgument;
  }

  Status_t status = ctx.data.CopyFrom(data.data, data.length);
  if (status.IsBad())
  {
    ctx.result = status.Value();
  }
  else
  {
    ctx.result = result;
  }
  return status.Value();
}

extern "C" UA_Status_t UAServer_File_Write_result(
    uintptr_t context,
    UA_Status_t result)
{
  FileGenericContext_t& ctx = *reinterpret_cast<FileGenericContext_t*>(context);
  ctx.result = result;
  return OpcUa_Good;
}

extern "C" UA_Status_t UAServer_File_GetPosition_result(
    uintptr_t context,
    uint64_t position,
    UA_Status_t result)
{
  FileGetPositionContext_t& ctx = *reinterpret_cast<FileGetPositionContext_t*>(context);
  ctx.position = position;
  ctx.result = result;
  return OpcUa_Good;
}

extern "C" UA_Status_t UAServer_File_SetPosition_result(
    uintptr_t context,
    UA_Status_t result)
{
  FileGenericContext_t& ctx = *reinterpret_cast<FileGenericContext_t*>(context);
  ctx.result = result;
  return OpcUa_Good;
}

#endif

#if (UA_INCLUDE_SECURITY > 0)

UA_Status_t UASecurity_Check_application_certificate_exists(void)
{
#ifdef _WIN32
  if (!UASDK_memcmp(SECURITY_CERTIFICATE_DIRECTORY_STORE_PATH, ".", 1))
  {
    return OpcUa_BadConfigurationError;
  }
#endif  //_WIN32
  Status_t status = UAServer->SecurityRefreshApplicationCertificateDirectoryStores();
  if (status.IsBad())
  {
    return status.Value();
  }
  status = UAServer->SecurityValidateApplicationInstanceCertificate(SECURITY_POLICY_BASIC128RSA15);
  if (status.IsBad())
  {
    return status.Value();
  }

  return OpcUa_Good;
}

UA_Status_t UASecurity_Create_self_signed_certificate(
  const UA_Configuration_t* sdk_configuration,
  const char* server_uri,
  const char** hostnames, int no_of_hostnames,
  const char** ip_addresses, int no_of_ip_addresses)
{
  UASDK_UNUSED(sdk_configuration);

  Status_t status;
  IntrusivePtr_t<CertificateGenerationParameters_t> parameters = new SafeRefCount_t<CertificateGenerationParameters_t>();
  if (!parameters.is_set())
  {
    return OpcUa_BadOutOfMemory;
  }

  parameters->type = UA_CERTIFICATE_TYPE_RSA_MIN_APPLICATION_TYPE;
  parameters->group = UA_CERTIFICATE_GROUP_DEFAULT_APPLICATION_GROUP;
  parameters->privateKeyBitLength = APPLICATION_RSA_KEY_LENGTH;

  UA_Var_string_t password;
  password.max_length = MAX_PRIVATE_PASSWORD_LEN;
  password.data = (uint8_t*)UASDK_Calloc(MAX_PRIVATE_PASSWORD_LEN);
  if (!password.data)
  {
    return OpcUa_BadOutOfMemory;
  }
  UASecurity_Callback_get_private_key_password(&password);

  Array_t<char> passwordStr;
  status = passwordStr.Initialise(password.length + 1);
  if (status.IsBad())
  {
    return status.Value();
  }
  if (password.length > 0)
  {
    UASDK_memcpy(passwordStr.Value(), password.data, password.length);
  }
  passwordStr[password.length] = '\0';

  status = parameters->privateKeyPassword.CopyFrom((const char*)passwordStr.Value(), passwordStr.Size() + 1);
  UASDK_Free(password.data);
  if (status.IsBad())
  {
    return status.Value();
  }

  parameters->start_date = UASDK_datetime();
  parameters->end_date = parameters->start_date.Value() + static_cast<int64_t>(315360e9);
  status = parameters->applicationUri.CopyFrom(server_uri);
  if (status.IsBad())
  {
    return status.Value();
  }

  status = parameters->ipAddresses.Initialise(no_of_ip_addresses);
  if (status.IsBad())
  {
    return status.Value();
  }
  for (int i = 0; i < no_of_ip_addresses; i++)
  {
    status = parameters->ipAddresses[i].CopyFrom(ip_addresses[i]);
    if (status.IsBad())
    {
      return status.Value();
    }
  }

  status = parameters->hostnames.Initialise(no_of_hostnames);
  if (status.IsBad())
  {
    return status.Value();
  }
  for (int i = 0; i < no_of_hostnames; i++)
  {
    status = parameters->hostnames[i].CopyFrom(hostnames[i]);
    if (status.IsBad())
    {
      return status.Value();
    }
  }

  status = parameters->commonName.CopyFrom(UA_PRODUCT_NAME);
  if (status.IsBad())
  {
    return status.Value();
  }
  status = parameters->organisationUnit.CopyFrom(UA_MANUFACTURER_NAME);
  if (status.IsBad())
  {
    return status.Value();
  }

  status = UAServer->SecurityCreateSelfSignedApplicationInstanceCertificate(parameters);
  if (status.IsBad())
  {
    return status.Value();
  }

  parameters->type = UA_CERTIFICATE_TYPE_RSA_SHA_256_APPLICATION_TYPE;
  parameters->privateKeyBitLength = 2048;

  status = UAServer->SecurityCreateSelfSignedApplicationInstanceCertificate(parameters);
  if (status.IsBad())
  {
    return status.Value();
  }

  return OpcUa_Good;
}

UA_Status_t UASecurity_Reload_directory_stores_now(void)
{
  return UAServer->SecurityRefreshApplicationCertificateDirectoryStores().Value();
}

void UASecurity_Reload_directory_stores_before_each_validation(bool_t enable)
{
  //Not implememted for R300
  UASDK_UNUSED(enable);
}

UA_Status_t UASecurity_Create_directory_stores(void)
{
  return  UAServer->SecurityCreateCertificateDirectoryStores().Value();
}

void UASecurity_Set_validation_options(uint32_t option_bits)
{
  Status_t status;
  IntrusivePtr_t<IServerConfiguration_t> config = UAServer->GetConfiguration(status);
  if ((status.IsBad()) || (!config.is_set()))
  {
    return;
  }

  ServerCertificateValidationOptions_t validationOptions;

  if (option_bits & OB_SUPPRESS_CERTIFICATE_EXPIRED)
  {
    validationOptions.suppressCertificateExpired = true;
  }
  if (option_bits & OB_SUPPRESS_REVOCATION_STATUS_UNKNOWN)
  {
    validationOptions.suppressRevocationStatusUnknown = true;
  }
  if (option_bits & OB_CHECK_REVOCATION_STATUS_ONLINE)
  {
    validationOptions.checkRevocationStatusOnline = true;
  }
  if (option_bits & OB_CHECK_REVOCATION_STATUS_OFFLINE)
  {
    validationOptions.checkRevocationStatusOffline = true;
  }
  if (option_bits & OB_SUPPRESS_URI_MISMATCH)
  {
    validationOptions.suppressUriMismatch = true;
  }

  config->CertificateValidationOptions(validationOptions);
}

void UASecurity_Set_validation_options2(uint32_t option_bits, bool_t trustAllClientsWhenTrustListIsEmpty, bool_t doNotSaveRejectedCertificates)
{
  UASecurity_Set_validation_options(option_bits);

  Status_t status;
  IntrusivePtr_t<IServerConfiguration_t> config = UAServer->GetConfiguration(status);
  if ((status.IsBad()) || (!config.is_set()))
  {
    return;
  }

  ServerCertificateValidationOptions_t validationOptions = config->CertificateValidationOptions();

  validationOptions.trustAllClientsWhenTrustListIsEmpty = (trustAllClientsWhenTrustListIsEmpty == TRUE);
  validationOptions.doNotSaveRejectedCertificates = (doNotSaveRejectedCertificates == TRUE);

  config->CertificateValidationOptions(validationOptions);
}

UA_Status_t UASecurity_Get_thumbprint(const char* filepath, char* thumbprint, uint32_t thumbprint_max_length)
{
  UASDK_UNUSED(filepath);
  UASDK_UNUSED(thumbprint);
  UASDK_UNUSED(thumbprint_max_length);
  return OpcUa_BadNotImplemented;
}

#endif //(UA_INCLUDE_SECURITY > 0)

#endif //UASDK_INCLUDE_SERVER_C_API
#endif //(UASDK_INCLUDE_SERVER)
