/* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                        COPYRIGHT (c) 2009 - 2017
                                         HONEYWELL INC.,
                                        ALL RIGHTS RESERVED

            This software is a copyrighted work and/or information protected as a trade
            secret. Legal rights of Honeywell Inc. in this software are distinct from
            ownership of any medium in which the software is embodied. Copyright or trade
            secret notices included must be reproduced in any copies authorized by
            Honeywell Inc. The information in this software is subject to change without
            notice and should not be considered as a commitment by Honeywell Inc.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////// */

#ifndef _UASERVER_T_
#define _UASERVER_T_

#include "uasdk_default_build_config.h"
#if (UASDK_INCLUDE_SERVER)
#if (UASDK_INCLUDE_SERVER_C_API > 0)

#include <scoped_ptr_t.h>
#include "uasdk_includes.h"
#include "intrusive_ptr_t.h"
#include "opcua_message_security_mode_t.h"
#include "iserver_core_t.h"
#include "intrusive_embedded_queue_t.h"
#include "irunnable_t.h"
#include "itimer_provider_t.h"
#include "ithread_pool_t.h"
#include "ixml_nodeset_io_t.h"
#include "tcp_connection_platform_t.h"
#include "ua_types.h"
#include "inode_t.h"
#include "itransaction_listener_t.h"
#include "iserver_state_listener_t.h"
#include "iaddress_space_t.h"
#include "opcua_build_info_t.h"
#include "iserver_configuration_t.h"
#include "opcua_user_identity_token_type_t.h"
#include "ixml_nodeset_io_t.h"
//#include "std_file_t.h"
#include "access_level_t.h"
#include "write_mask_t.h"
#include "ilog_listener_t.h"
#include "certificate_generation_parameters_t.h"
#include "icertificate_private_key_password_provider_t.h"
#include "certificate_validation_options_t.h"
#include "opcua_node_id_numeric_t.h"
#include "iuser_permissions_t.h"
#include "iuser_permissions_provider_t.h"
#include "utilities.h"
#include "inode_application_context_t.h"
#include "opcua_x509_identity_token_t.h"
#include "ua_server.h"
#include "data_item_t.h"
#include "file_transfer_router.h"
#include "opcua_server_state_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)
#include "system_status_change_event_type_data_t.h"
#endif

namespace uasdk
{

static uint16_t userIndex = 0x01;

/** \addtogroup grpServer_C_API
 *@{*/

/*****************************************************************************/
/** \brief UA Server
 *
 * A class that integrate the UA Server implementations.
 *
 */
class UAServer_t : public Allocatable_t, public IRefCount_t
{
private:

  class ApplicationContext_t : public INodeApplicationContext_t, public Allocatable_t
  {
  private:
    uint16_t userVisibility;
    uint16_t userReadPermission;
    uint16_t userWritePermission;
    bool userExecutable;

  public:
    ApplicationContext_t()
      : userVisibility(0),
      userReadPermission(0),
      userWritePermission(0),
      userExecutable(0)
    {};

    ~ApplicationContext_t() {};

    uint16_t UserVisibility(void)
    {
      return userVisibility;
    }

    void UserVisibility(uint16_t value_)
    {
      userVisibility = value_;
    }

    uint16_t UserReadPermission(void)
    {
      return userReadPermission;
    }

    void UserReadPermission(uint16_t value_)
    {
      userReadPermission = value_;
    }

    uint16_t UserWritePermission(void)
    {
      return userWritePermission;
    }

    void UserWritePermission(uint16_t value_)
    {
      userWritePermission = value_;
    }

    bool UserExecutable(void)
    {
      return userExecutable;
    }

    void UserExecutable(bool value_)
    {
      userExecutable = value_;
    }
  };

  /*****************************************************************************/
  /** \brief User Permissions
   * A class implements the User permission
   */
  class UserPermissions_t : public IUserPermissions_t, public Allocatable_t
  {
  public:
    virtual ~UserPermissions_t() {};

    /*****************************************************************************/
    /** == operator overloading
     *
     * @param[in] IUserPermissions_t const & obj
     * Object to be compared with
     *
     * @return
     * Returns true if the objects are same
     */
    virtual bool operator==(IUserPermissions_t const & obj) const
    {
      UASDK_UNUSED(obj);
      return true;
    }

    /*****************************************************************************/
    /** != operator overloading
     *
     * @param[in] IUserPermissions_t const & obj
     * Object to be compared with
     *
     * @return
     * Returns true if the objects are same
     */
    virtual bool operator!=(IUserPermissions_t const & obj) const
    {
      UASDK_UNUSED(obj);
      return true;
    }

    /*****************************************************************************/
    /** Get Variable Node User Access Level
     *
     * @param[in] const IVariableNode_t& node
     * variable node
     *
     * @param[out] AccessLevel_t& userAccessLevel
     * Access level
     *
     * @return
     * Returns status of the operation
     */
    virtual Status_t GetVariableNodeUserAccessLevel(const IVariableNode_t& node,
      AccessLevel_t& userAccessLevel) const
    {
      IntrusivePtr_t<INodeApplicationContext_t> context_ = node.ApplicationContextHandle();
      if (context_.is_set())
      {
        ApplicationContext_t& context = static_cast<ApplicationContext_t&>(*context_);

        AccessLevel_t accessLevel(0x00);
        if (context.UserReadPermission() & userIndex)
        {
          accessLevel.Value(0x01);

          if (context.UserWritePermission() & userIndex)
          {
            accessLevel.Value(0x03);
          }

          userAccessLevel = accessLevel;
          return OpcUa_Good;
        }
        else
        {
          userAccessLevel = accessLevel;
          return OpcUa_Good;
        }
      }

      userAccessLevel = node.AccessLevel();
      return OpcUa_Good;
    }

    /*****************************************************************************/
    /** Set Variable Node User Access Level
     *
     * @param[in] IVariableNode_t& node
     * variable node
     *
     * @param[in] AccessLevel_t userAccessLevel
     * Access level
     *
     * @return
     * Returns status of the operation
     */
    virtual Status_t SetVariableNodeUserAccessLevel(IVariableNode_t& node,
      AccessLevel_t userAccessLevel)
    {
      UASDK_UNUSED(node);
      UASDK_UNUSED(userAccessLevel);
      UASDK_RETURN_BAD_STATUS(OpcUa_BadNotWritable);
    }

    /*****************************************************************************/
    /** Get Node User Write Mask
     *
     * @param[in] const INode_t& node
     * node
     *
     * @param[out] WriteMask_t& userWriteMask
     * User Write Mask
     *
     * @return
     * Returns status of the operation
     */
    virtual Status_t GetNodeUserWriteMask(const INode_t& node,
      WriteMask_t& userWriteMask) const
    {
      userWriteMask = node.WriteMask();
      return OpcUa_Good;
    }

    /*****************************************************************************/
    /** Set Node User Write Mask
     *
     * @param[in] const INode_t& node
     * node
     *
     * @param[in] WriteMask_t userWriteMask
     * User Write Mask
     *
     * @return
     * Returns status of the operation
     */
    virtual Status_t SetNodeUserWriteMask(const INode_t& node,
      WriteMask_t userWriteMask)
    {
      UASDK_UNUSED(node);
      UASDK_UNUSED(userWriteMask);
      UASDK_RETURN_BAD_STATUS(OpcUa_BadNotWritable);
    }

    /*****************************************************************************/
    /** Get Node User Visibility
     *
     * @param[in] const INode_t& node
     * node
     *
     * @param[out] bool& visible
     * visibility flag
     *
     * @return
     * Returns status of the operation
     */
    virtual Status_t GetNodeUserVisibility(const INode_t& node, bool& visible) const
    {
      IntrusivePtr_t<INodeApplicationContext_t> context_ = node.ApplicationContextHandle();
      if (context_.is_set())
      {

        ApplicationContext_t& context = static_cast<ApplicationContext_t&>(*context_);

        if (context.UserVisibility() & userIndex)
        {
          visible = true;
          return OpcUa_Good;
        }
        else
        {
          visible = false;
          return OpcUa_Good;
        }
      }
      
      visible = true;
      return OpcUa_Good;
    }

    /*****************************************************************************/
    /** Set Node User Visibility
     *
     * @param[in] const INode_t& node
     * node
     *
     * @param[in] bool visible
     * visibility flag
     *
     * @return
     * Returns status of the operation
     */
    virtual Status_t SetNodeUserVisibility(INode_t& node,
      bool visible)
    {
      UASDK_UNUSED(node);
      UASDK_UNUSED(visible);
      UASDK_RETURN_BAD_STATUS(OpcUa_BadNotWritable);
    }

    /*****************************************************************************/
    /** Get Method Node User Executable
     *
     * @param[in] const IMethodNode_t& method
     * node
     *
     * @param[out] bool& userExecutable
     * visibility flag
     *
     * @return
     * Returns status of the operation
     */
    virtual Status_t GetMethodNodeUserExecutable(const IMethodNode_t& method,
      bool& userExecutable) const
    {
      IntrusivePtr_t<INodeApplicationContext_t> context_ = method.ApplicationContextHandle();
      if (context_.is_set())
      {
        ApplicationContext_t& context = static_cast<ApplicationContext_t&>(*context_);

        userExecutable = context.UserExecutable();
        return OpcUa_Good;
      }

      userExecutable = method.Executable();
      return OpcUa_Good;
    }

    /*****************************************************************************/
    /** Set Method Node User Executable
     *
     * @param[in] const IMethodNode_t& method
     * node
     *
     * @param[out] bool userExecutable
     * visibility flag
     *
     * @return
     * Returns status of the operation
     */
    virtual Status_t SetMethodNodeUserExecutable(IMethodNode_t& method,
      bool userExecutable)
    {
      UASDK_UNUSED(method);
      UASDK_UNUSED(userExecutable);
      UASDK_RETURN_BAD_STATUS(OpcUa_BadNotWritable);
    }

  };

  /*****************************************************************************/
  /** \brief User Permissions Provider
   *
   * This class provides interfaces to get the User permissions
   */
  class UserPermissionsProvider_t : public IUserPermissionsProvider_t, public Allocatable_t
  {
  public:
    virtual ~UserPermissionsProvider_t() {};


    /*****************************************************************************/
    /** Get the User permission for the given session id, user name and password.
     *
     * @param[in] sessionId
     * The session ID
     *
     * @param[in] userName
     * The User Name
     *
     * @param[in] password
     * The Password
     *
     * @param[out] userPermissions
     * The User permission for the given session id, user name and password
     *
     * @return
     * Status of the operation
     */
    virtual Status_t GetUserPermissions(const NodeId_t& sessionId,
      const String_t& userName,
      const String_t& password,
      IntrusivePtr_t<IUserPermissions_t>& userPermissions) const
    {
      UASDK_UNUSED(sessionId);
      UASDK_UNUSED(userName);
      UASDK_UNUSED(password);

      UA_UTF8_string_t userName_;
      UA_UTF8_string_t password_;

      ScopedPtr_t< Array_t<char> > tempUserName;
      Status_t status = userName.ToString(tempUserName);
      if (status.IsBad() || !tempUserName.is_set())
      {
        UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
      }
      userName_.data = (const uint8_t*)(tempUserName->Value());
      userName_.length = tempUserName->Size();

      ScopedPtr_t< Array_t<char> > tempPassword;
      status = password.ToString(tempPassword);
      if (status.IsBad() || !tempPassword.is_set())
      {
        UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
      }
      password_.data = (const uint8_t*)(tempPassword->Value());
      password_.length = tempPassword->Size();
 
      uint16_t userIndex_ = 0;
      bool_t allowed = UAServer_Callback_login_username_password(&userName_, &password_, &userIndex_);
      if (allowed)
      {
        if (!userIndex_)
        {
          return OpcUa_BadUserAccessDenied;
        }

        userIndex |= userIndex_;
        userPermissions = new SafeRefCount_t<UserPermissions_t>();
        if (!userPermissions.is_set())
        {
          UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
        }
        return OpcUa_Good;
      }

      return OpcUa_BadUserAccessDenied;
    }

    /*****************************************************************************/
    /** Get the User permission for the given session id and certificate for user identity token
     *
     * @param[in] sessionId
     * The session ID
     *
     * @param[in] userIdentityToken
     * X509 User Identity Token
     *
     * @param[out] userPermissions
     * The User permission for the given session id, X509 User Identity Token
     *
     * @return
     * Status of the operation
     */
    virtual Status_t GetUserPermissions(const NodeId_t& sessionId,
      const X509IdentityToken_t& userIdentityToken,
      IntrusivePtr_t<IUserPermissions_t>& userPermissions) const
    {
      UASDK_UNUSED(sessionId);
      UASDK_UNUSED(userIdentityToken);
      UASDK_UNUSED(userPermissions);

#if (UA_INCLUDE_SECURITY > 0)
      UA_Byte_string_t certificate;
      certificate.data = (uint8_t*)(userIdentityToken.CertificateData().Data());
      certificate.length = userIdentityToken.CertificateData().Length();
      certificate.max_length = certificate.length;

      uint8_t hash[20];
      UA_Byte_string_t thumbprint;
      thumbprint.data = hash;
      thumbprint.length = 20;
      thumbprint.max_length = thumbprint.length;
      
      Status_t status = UASecurity_digest(UA_DIGEST_SHA1, &certificate, &thumbprint);
      if (status.IsBad())
      {
        UASDK_RETURN_BAD_STATUS(status.Value());
      }
      
      UA_UTF8_string_t temp;
      temp.data = thumbprint.data;
      temp.length = thumbprint.length;

      uint16_t userIndex_ = 0;
      bool_t allowed = UAServer_Callback_login_x509_certificate(&certificate, &temp, &userIndex_);
      if (allowed)
      {
        if (!userIndex_)
        {
          return OpcUa_BadUserAccessDenied;
        }

        userIndex |= userIndex_;
        userPermissions = new SafeRefCount_t<UserPermissions_t>();
        if (!userPermissions.is_set())
        {
          UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
        }
        return OpcUa_Good;
      }
#else
      return OpcUa_BadNotSupported;
#endif  //UA_INCLUDE_SECURITY

      return OpcUa_BadUserAccessDenied;
    }

    /*****************************************************************************/
    /** Get the User permission for the given session id and anonymous user identity token
     *
     * @param[in] sessionId
     * The session ID
     *
     * @param[in] userIdentityToken
     * Anonymous User Identity Token
     *
     * @param[out] userPermissions
     * The User permission for the given session id, Anonymous User Identity Token
     *
     * @return
     * Status of the operation
     */
    virtual Status_t GetUserPermissions(const NodeId_t& sessionId,
      const AnonymousIdentityToken_t& userIdentityToken,
      IntrusivePtr_t<IUserPermissions_t>& userPermissions) const
    {
      UASDK_UNUSED(sessionId);
      UASDK_UNUSED(userIdentityToken);

      if (userIndex | 0x01)
      {
        userPermissions = new SafeRefCount_t<UserPermissions_t>();
        if (!userPermissions.is_set())
        {
          UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
        }
        return OpcUa_Good;
      }

      return OpcUa_BadUserAccessDenied;
    }
  };

  /*****************************************************************************/
  /** \brief Certificate Private Key Password Provider
   *
   * This class provides interfaces to get the Certificate Private Key Password
   */
  class CertificatePrivateKeyPasswordProvider_t : public ICertificatePrivateKeyPasswordProvider_t, public Allocatable_t
  {
  public:
    virtual ~CertificatePrivateKeyPasswordProvider_t() {};

    /*****************************************************************************/
    /** This function is used to get the password.
     *
     * @param[in] type
     * Type of UA certificate.
     *
     * @param[in] group
     * group type of UA certificate.
     *
     * @param[out] password
     * Password to be returned
     *
     * @return
     * returns the result of the operation.
     */
    virtual Status_t GetPassword(UA_CertificateType_t type, UA_CertificateGroup_t group, String_t& password) const
    {
      UASDK_UNUSED(type);
      UASDK_UNUSED(group);
      return password.CopyFrom("password");
    }
  };

  static IntrusivePtr_t<ILogListener_t> logListener;

  /*****************************************************************************/
  /* @var namespaceIndexForAlias
   * Intrusive pointer to the Server core
   */
  uint16_t namespaceIndexForAlias;

  /*****************************************************************************/
  /* @var localeIdArray
  * An intrusive reference counting Boost-style smart pointer to the
  * address space. The caller must test the pointer
  * before dereferencing it.
  */
  IntrusivePtr_t<IAddressSpace_t> addressSpace;

  /*****************************************************************************/
  /* @var localeIdArray
   * An intrusive reference counting Boost-style smart pointer to the
   * locale id array. The caller must test the pointer
   * before dereferencing it.
   */
  IntrusivePtr_t<const ArrayUA_t<String_t> > localeIdArray;

  /*****************************************************************************/
  /* @var IntrusivePtr_t<IServerCore_t> core
   * Intrusive pointer to the Server core
   */
  IntrusivePtr_t<IServerCore_t> core;

  /*****************************************************************************/
  /* @var IntrusivePtr_t<IThreadPool_t> threadPool
   * Intrusive pointer to the thread pool
   */
  IntrusivePtr_t<IThreadPool_t> threadPool;

  /*****************************************************************************/
  /* @var IntrusiveEmbeddedQueue_t<IRunnable_t> runQueue
   * Intrusive pointer to the run queue
   */
  IntrusiveEmbeddedQueue_t<IRunnable_t> runQueue;

  /*****************************************************************************/
  /* @var IntrusivePtr_t<ITimerProvider_t> timerProvider
   * Intrusive pointer to the timer provider
   */
  IntrusivePtr_t<ITimerProvider_t> timerProvider;

  /*****************************************************************************/
  /* @var IntrusivePtr_t<TcpConnectionPlatform_t> connections
   * Intrusive pointer to the TCP Connection Platform
   */
  IntrusiveList_t<TcpConnectionPlatform_t> connections;

#if (UASDK_USE_FILE_OBJECT_HELPERS > 0)
  /*****************************************************************************/
  /* @var IntrusivePtr_t<FileTransferRouter_t> fileTransferRouter
   * Intrusive pointer to the File Transfer Router
   */
  IntrusivePtr_t<FileTransferRouter_t> fileTransferRouter;
#endif

  /*****************************************************************************/
  /** Add endpoints
   *
   * @param[in] serverConfig
   * server configuration
   *
   * @param[in] policy
   * security policy
   *
   * @param[in] endpointPolicy
   * endpoint security Policy
   * 
   * @param[in] mode
   * message security mode
   *
   * @return
   * status of the operation
   */
  static Status_t AddEndpoints(IntrusivePtr_t<IServerConfiguration_t> serverConfig,
                               uint64_t policy,
                               SecurityPolicy_t endpointPolicy,
                               MessageSecurityMode_t::Enum_t mode);

  /*****************************************************************************/
  /** Get the TCP Connection Platform
   *
   * @param[in] uint64_t connectionId
   * Connection ID
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * TcpConnectionPlatform_t. The caller must test the pointer
   * before dereferencing it.
   */
  IntrusivePtr_t<TcpConnectionPlatform_t> GetConnection(uint64_t connectionId);

  /*****************************************************************************/
  /** Get the AddressSpace
   *
   * @return
   * status of the operation
   */
  Status_t UpdateLocaleIdArray(void);

  /*****************************************************************************/
  /** Get the AddressSpace
   *
   * @param[out] result
   * status of the operation
   *
   * @return
   * result of the operation
   */
  Status_t UpdateAddressSpaceVariable(void);

  Status_t RemoveStandardNode(uint32_t nodeId_);

  /*****************************************************************************/
  /** Create Standard Objects folder
  *
  * @return
  * result of the operation
  */
  Status_t CreateObjectsFolder(void);

  /*****************************************************************************/
  /** Get the new namepsace index for Alias
   *
   * This function will look for the lenght of the namespace array and, lenght+1 
   * will be returned as the new namespace index.
   *
   * @return
   * status of the operation
   */
  Status_t UpdateNamespaceIndexForAlias(void);

  /*****************************************************************************/
  /** Get the new namepsace index for Alias
   *
   * @param[in] base_config
   * reference to Base config which is common to all nodes
   *
   * @param[out] aliasId
   * alias ID
   *
   * @param[out] nodeId
   * Node ID
   *
   * @return
   * status of the operation
   */
  Status_t CreateAliasIdAndNodeId(const UA_Base_t& base_config, IntrusivePtr_t<const NodeId_t>& aliasId, IntrusivePtr_t<const NodeId_t>& nodeId);

  /*****************************************************************************/
  /** Get the datatype for node
   *
   * @param[in] type
   * given type
   *
   * @param[out] result
   * status of the operation
   *
   * @return
   * new namespace index
   */
  IntrusivePtr_t<const NodeId_t> GetDataType(UA_Value_type_t type, Status_t& result);

  /*****************************************************************************/
  /** Create Locale translator
   *
   * @param[in] handle
   * handle to locale text
   *
   * @param[out] result
   * An intrusive reference counting Boost-style smart pointer to the
   * localizable text. The caller must test the pointer
   * before dereferencing it.
   *
   * @return
   * status of the operation
   */
  Status_t CreateLocaleTextTranslator(uintptr_t handle, IntrusivePtr_t<const ILocalizableText_t>& result);

  /*****************************************************************************/
  /** Get the English text fro Browse Name
  *
  * @param[in] handle
  * handle for translator
  *
  * @param[out] translator
  * Translator for DisplayName
  *
  * @param[out] englishText
  * English Text as String for Browse Name
  *
  * @return
  * status of the operation
  */
  Status_t CreateTranslatorAndGetEnglishText(uintptr_t handle, IntrusivePtr_t<const ILocalizableText_t>& translator, String_t& englishText);

  /*****************************************************************************/
  /** Create BrowseName, DisplayName and Description
  *
  * @param[in] node
  * node for which display name and description has to be created
  *
  * @param[in] handle
  * Description Handle
  *
  * @return
  * status of the operation
  */
  Status_t UpdateDescriptionTranslator(IntrusivePtr_t<INode_t> node, uintptr_t handle);

  /*****************************************************************************/
  /** Create BrowseName, DisplayName and Description
  *
  * @param[in] node
  * node for which display name and description has to be created
  *
  * @param[in] base_config
  * reference to base config. Where handles for display name and description is available
  *
  * @return
  * status of the operation
  */
  Status_t CreateBrowseNameDisplayNameAndDescription(IntrusivePtr_t<INode_t> node, const UA_Base_t& base_config);

  /*****************************************************************************/
  /** Create Application instace for a node for user visibility
  *
  * @param[in] userVisibility_
  * user visibility mask of node
  *
  * @param[in] node_
  * Intrusive pointer to node
  *
  * @return
  * status of the operation
  */
  Status_t CreateApplicationContextForUserVisibility(uint16_t userVisibility_, IntrusivePtr_t<INode_t> node_);

  /*****************************************************************************/
  /** Create DisplayName and Description
   *
   * @param[in] nodeType
   * Type of node to be created
   *
   * @param[in] baseConfig
   * reference to base config.
   *
   * @param[in] node
   * reference to node.
   *
   * @return
   * status of the operation
   */
  Status_t CreateNodeAndItsAttributes(uint32_t nodeType, const UA_Base_t& baseConfig, IntrusivePtr_t<INode_t>& node);

  /*****************************************************************************/
  /** Update Variable Node Attributes
  *
  * @param[in] node
  * Variable Node
  *
  * @param[in] data
  * Variable node configuration
  *
  * @return
  * status of the operation
  */
  Status_t UpdateVariableNodeAttributes(IntrusivePtr_t<IVariableNode_t> node, const UA_BaseDataVariable_t& data);

  /*****************************************************************************/
  /** create Alias Id, Node Id, Display Name Translator, browse name required 
  *   for creating the helper node
  *
  * @param[in] baseConfig
  * base config
  *
  * @param[out] aliasId
  * alias id
  *
  * @param[out] nodeId
  * node id
  *
  * @param[out] displayNameTranslator
  * display name translator
  *
  * @param[out] browseName_
  * browse name
  *
  * @return
  * status of the operation
  */
  Status_t CreateEssenstialsForHelpers(const UA_Base_t& baseConfig,
                                       IntrusivePtr_t<const NodeId_t>& aliasId,
                                       IntrusivePtr_t<const NodeId_t>& nodeId,
                                       IntrusivePtr_t<const ILocalizableText_t>& displayNameTranslator,
                                       String_t& browseName_);

  /*****************************************************************************/
  /** This function is used for updating the essentials for Helpers
  * Assigning the Alias, Dispaly na,e translator, Description translator
  * Application context for user visibility, Variable node's attributes
  *
  * @param[in] baseConfig
  * base config
  *
  * @param[in] aliasId
  * alias id
  *
  * @param[in] displayNameTranslator
  * display name translator
  *
  * @param[out] node_
  * browse name
  *
  * @return
  * status of the operation
  */
  Status_t UpdateEssentialsForHelper(const UA_BaseDataVariable_t& data,
                                     IntrusivePtr_t<const NodeId_t>& aliasId,
                                     IntrusivePtr_t<const ILocalizableText_t>& displayNameTranslator,
                                     IntrusivePtr_t<IVariableNode_t>& node_);

  /*****************************************************************************/
  /** This function will generate numeric id
  *
  * @param[in] namespaceIndex_
  * namespaceIndex_ for a node
  *
  * @return
  * valid numeric Id
  */
  uint32_t GenerateNumericId(uint16_t namespaceIndex_);

  /*****************************************************************************/
  /** This function will be used to create the property values for Two State discrete
  *
  * @param[in] handle
  * handle
  *
  * @param[out] translator
  * translator
  *
  * @param[out] result
  * localized text
  *
  * @return
  * valid numeric Id
  */
  Status_t CreatePropertyValuesForTwoStateDiscrete(uintptr_t handle, IntrusivePtr_t<const ILocalizableText_t>& translator, LocalizedText_t& result);

#if ((UASDK_USE_HELPERS > 0) && (UASDK_USE_DATA_ACCESS_HELPERS > 0))
  /*****************************************************************************/
  /** This function will be used to create the property values for Two State discrete
  *
  * @param[in] dataItemConfig
  * dataItem configuration
  *
  * @param[out] node_
  * node to which property has to be created
  */
  Status_t CreateDefinitionAndValuePrecisionProperty(const UA_DataItem_t& dataItemConfig, DataItem_t& node_);
#endif  //#if (UASDK_USE_DATA_ACCESS_HELPERS > 0)

  /*****************************************************************************/
  /** This function will search for a View node whose user vibility matches with the view mask
  *
  * @param[in] viewMask
  * view Mask to be found
  *
  * @param[out] result
  * result of getting view id
  *
  * @return
  * Intrusive pointer to view node id. Empty if required view is not found.
  */
  IntrusivePtr_t<const NodeId_t> GetViewNodeId(uint16_t viewMask, Status_t& result);

  /*****************************************************************************/
  /** This function will add the Opc Foundation URI to the namespace array
  *
  * @param[out] namespaceArray
  * where OpcFOundation uri needs to be added
  *
  * @return
  * status of the operation
  */
  Status_t AddUri(const char* uri, uint32_t index, ArrayUA_t<String_t>& nameSpaceArray);

public:
  virtual ~UAServer_t() {};

  /*****************************************************************************/
  /** Create the Server Configuration
   *
   * @param[out] result
   * The result of the Server configuration creation status
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * IServerConfiguration_t. The caller must test the pointer
   * before dereferencing it.
   */
  static IntrusivePtr_t<IServerConfiguration_t> CreateConfiguration(Status_t& result);

  /*****************************************************************************/
  /** Create the XLM node set IO
   *
   * @param[in] bool doNotAllowDuplicateNodeId
   * Do not allow dupilcate node id
   *
   * @param[out] result
   * The status of the operation
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * IXmlNodesetIO_t. The caller must test the pointer
   * before dereferencing it.
   */
  static IntrusivePtr_t<IXmlNodesetIO_t> CreateXmlNodesetIO(bool doNotAllowDuplicateNodeId, Status_t& result);

  /*****************************************************************************/
  /** Create the AddressSpace
   *
   * @param[in] numberOfBuckets
   * Address space Hash buckets's number of buckets as per the configuration
   *
   * @param[out] result
   * The status of the operation
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * IAddressSpace_t. The caller must test the pointer
   * before dereferencing it.
   */
  static IntrusivePtr_t<IAddressSpace_t> CreateAddressSpace(uint32_t numberOfBuckets, Status_t& result);

  /*****************************************************************************/
  /** Create the allocator
   *
   * @param[out] uint8_t* buffer
   *  Allocator Buffer
   *
   * @param[out] uint32_t bufferLengthInBytes
   * Buffer length in bytes
   *
   * @param[out] uint32_t maxAllocationSizeInBytes
   *  Maximum allocation size in bytes
   *
   * @return
   * Status of the operation
   */
  static Status_t CreateAllocator(uint8_t* buffer, uint32_t bufferLengthInBytes, uint32_t maxAllocationSizeInBytes);

  /*****************************************************************************/
  /** Initialize the Server
   *
   * @param[in] configuration
   * The Server configuration. An intrusive reference counting Boost-style smart
   * pointer to the IServerConfiguration_t.
   *
   * @return
   * Status of the Initialize operation.
   */
  Status_t Initialise(IntrusivePtr_t<IServerConfiguration_t> configuration);

  /*****************************************************************************/
  /** Start the Server
   *
   * @param[in] license
   * The Server License
   *
   * @return
   * Status of the Initialize operation.
   */
  Status_t Start(const String_t& license);

  /*****************************************************************************/
  /** Stop the server
   *
   * @return
   * Status of the Initialize operation.
   */
  Status_t Stop(void);

  /*****************************************************************************/
  /** Get the Server Configuration
   *
   * @param[out] result
   * The result of the get Server configuration status
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * IServerConfiguration_t. The caller must test the pointer
   * before dereferencing it.
   */
  IntrusivePtr_t<IServerConfiguration_t> GetConfiguration(Status_t& result);

  /*****************************************************************************/
  /** Validate the application instance certificate based on the security policy
   *
   * @param[in] policy
   * The Security policy configuration
   *
   * @return
   * Status of the operation.
   */
  Status_t SecurityValidateApplicationInstanceCertificate(SecurityPolicy_t securityPolicy);

  /*****************************************************************************/
  /** Create the Self-signed application instance certificate
   *
   * @param[in] parameters
   *  The Certificate generation Parameters
   *
   * @return
   * Status of the operation.
   */
  Status_t SecurityCreateSelfSignedApplicationInstanceCertificate(
      IntrusivePtr_t<const CertificateGenerationParameters_t> parameters);

  /*****************************************************************************/
  /** Create the Certificate directory stores
   *
   * @return
   * Status of the operation.
   */
  Status_t SecurityCreateCertificateDirectoryStores(void);

  /*****************************************************************************/
  /** Refresh the Application Certificate directory stores
   *
   * @return
   * Status of the operation.
   */
  Status_t SecurityRefreshApplicationCertificateDirectoryStores(void);

  /*****************************************************************************/
  /** Refresh the User Certificate directory stores
   *
   * @return
   * Status of the operation.
   */
  Status_t SecurityRefreshUserCertificateDirectoryStores(void);

  /*****************************************************************************/
  /** Create a new TCP IP connection
   *
   * @param[in] uint64_t connectionId
   * Connection ID
   *
   * @return
   * Status of the operation.
   */
  Status_t TcpipNewConnection(uint64_t connectionId);

  /*****************************************************************************/
  /** Close the TCP IP connection
   *
   * @param[in] uint64_t connectionId
   * Connection ID
   *
   * @return
   * Status of the operation.
   */
  Status_t TcpipConnectionClosed(uint64_t connectionId);

  /*****************************************************************************/
  /** Receive new data from TCP IP
   *
   * @param[in] void* readContext
   * Read context pointer
   *
   * @param[in] uint64_t connectionId
   * Connection ID
   *
   *
   * @return
   * Status of the operation.
   */
  Status_t TcpipNewDataReceived(void* readContext, uint64_t connectionId);

  /*****************************************************************************/
  /** Get the data to send
   *
   * @param[out] void* writeContext
   * Write context pointer
   *
   * @param[in] uint64_t connectionId
   * Connection ID
   *
   * @return
   * Status of the operation.
   */
  Status_t GetDataToSend(void* writeContext, uint64_t connectionId);


  /*****************************************************************************/
  /** Poll the server
   *
   */
  void Poll(void);

  /*****************************************************************************/
  /** Terminate the server
  *
  * @return
  * Status of the operation.
  */
  Status_t Terminate(void);

  /*****************************************************************************/
  /** validate the server configuration
   *
   * @param[in] const UA_Configuration_t& cfg
   * Server configuration
   *
   * @return
   * Status of the operation.
   */
  static IntrusivePtr_t<IServerConfiguration_t> ValidateConfiguration(const UA_Configuration_t& cfg);

  /*****************************************************************************/
  /** Updates the namespace array Information from the configuration
  *
  * @param[in] const UA_Configuration_t& cfg
  * Server configuration
  *
  * @return
  * Status of the operation.
  */
  Status_t UpdateNameSpaceArray(const UA_Configuration_t& cfg);

  /*****************************************************************************/
  /** Delete the node
   *
   * @param[in] uintptr_t node_handle
   * Node handle
   *
   * @return
   * Status of the operation.
   */
  Status_t DeleteNode(uintptr_t node_handle);

  /*****************************************************************************/
  /** Create a folder
   *
   * @param[in] const UA_Folder_t& data
   * UA folder
   *
   * @return
   * Status of the operation.
   */
  Status_t CreateFolder(const UA_Folder_t& data);

  /*****************************************************************************/
  /** Create a view
   *
   * @param[in] const UA_View_t& data
   * UA view
   *
   * @return
   * Status of the operation.
   */
  Status_t CreateView(const UA_View_t& data);

  /*****************************************************************************/
  /** Create a Method
   *
   * @param[in] const UA_Method_t& data
   * UA Method
   *
   * @return
   * Status of the operation.
   */
  Status_t CreateMethod(const UA_Method_t& data);

  /*****************************************************************************/
  /** Create a Base Data Variable
   *
   * @param[in] const UA_BaseDataVariable_t& data
   * Base Data Variable
   *
   * @return
   * Status of the operation.
   */
  Status_t CreateBaseDataVariable(const UA_BaseDataVariable_t& data);

  /*****************************************************************************/
  /** Create a Data Item
   *
   * @param[in] const UA_DataItem_t& data
   * UA Data Item
   *
   * @return
   * Status of the operation.
   */
  Status_t CreateDataItem(const UA_DataItem_t& data);

  /*****************************************************************************/
  /** Create a Analog item
   *
   * @param[in] const UA_AnalogItem_t& data
   * UA Analog item
   *
   * @return
   * Status of the operation.
   */
  Status_t CreateAnalogItem(const UA_AnalogItem_t& data);

  /*****************************************************************************/
  /** Create a Two State Discrete
   *
   * @param[in] const UA_TwoStateDiscrete_t& data
   * UA Two State Discrete
   *
   * @return
   * Status of the operation.
   */
  Status_t CreateTwoStateDiscrete(const UA_TwoStateDiscrete_t& data);

  /*****************************************************************************/
  /** Create a Multi State Discrete
   *
   * @param[in] const UA_MultiStateDiscrete_t& data
   * Multi State Discrete
   *
   * @return
   * Status of the operation.
   */
  Status_t CreateMultiStateDiscrete(const UA_MultiStateDiscrete_t& data);

  /*****************************************************************************/
  /** Create a file
   *
   * @param[in] const UA_File_t& data
   * UA file
   *
   * @return
   * Status of the operation.
   */
  Status_t UACreateFile(const UA_File_t& data);

  /*****************************************************************************/
  /** Add node to folder
   *
   * @param[in] uintptr_t folder_handle
   * Folder handle
   *
   * @param[in] uintptr_t node_handle
   * Node handle
   *
   * @return
   * Status of the operation.
   */
  Status_t AddToFolder(uintptr_t folder_handle, uintptr_t node_handle);

  /*****************************************************************************/
  /** Add node to folder
   *
   * @param[in] uintptr_t folder_handle
   * Folder handle
   *
   * @param[in] uintptr_t node_handle
   * Node handle
   *
   * @param[in] uint16_t view_mask
   * View mask
   *
   * @return
   * Status of the operation.
   */
  Status_t AddToFolder(uintptr_t folder_handle, uintptr_t node_handle, uint16_t view_mask);

  /*****************************************************************************/
  /** Add to objects folder
   *
   * @param[in] uintptr_t node_handle
   * Node handle
   *
   * @return
   * Status of the operation.
   */
  Status_t AddToObjectsFolder(uintptr_t node_handle);

  /*****************************************************************************/
  /** Can the current read operation be deferred if we have to obtain the data value
  * from a slow remote data source?
  *
  * This function can only be called from UAServer_Callback_read().
  *
  * @param[in] readContext
  * The read context provided by the SDK.
  *
  * @return
  * TRUE if the read operation can be deferred.
  */
  bool IsReadOperationDeferrable(uintptr_t readContext);

  /*****************************************************************************/
  /** Is the current read operation a repeat of an operation that was previously
  * deferred?
  *
  * @param[in] readContext
  * The read context provided by the SDK.
  *
  * @return
  * true if the read operation was previously deferred deferred.
  */
  bool IsReadOperationDeferred(uintptr_t readContext);

  /*****************************************************************************/
  /** Get Time Out Hint
  *
  *
  * @return
  * time out value of the read operation.
  */
  uint32_t GetReadTimeOutHint(uintptr_t readContext);

  /*****************************************************************************/
  /** Defer the current read operation as we have to obtain the data from a slow
  * remote data source and doing so synchronously would degrade server response
  * for all connected clients.
  *
  * This function can only be called from UAServer_Callback_read().
  *
  * @param[in] readContext
  * The read context provided by the SDK.
  *
  * @param[out] deferralHandle
  * A unique handle representing this specific deferral.
  *
  * @return
  * OpcUa_Good if the deferral was successful.
  */
  Status_t DeferReadOperation(uintptr_t readContext, uintptr_t* deferralHandle);

  /*****************************************************************************/
  /** Read Deferral Complete
   *
   * @param[in] deferralHandle
   * Deferral handle
   *
   * @param[in] statusCode
   * Status code
   *
   * @return
   * Status of the operation.
   */
  Status_t ReadDeferralComplete(uintptr_t deferralHandle, UA_Status_t statusCode);

  /*****************************************************************************/
  /** This function used to get the memory information.
   *
   * @param[out] totalMemoryProvided
   * total memory provided for the process.
   *
   * @param[out] memoryUnusable
   * unusable memory out of total memory.
   *
   * @param[out] maxMemoryUsedThisRun
   * maximum memory committed for the process.
   *
   * @param[out]  totalMemoryRecommended
   * total memory recommended for the the process.
   *
   * @return
   * returns status of the operation.
   *
   */
  Status_t UAServerMemoryInfo(
    uint32_t& totalMemoryProvided,
    uint32_t& memoryUnusable,
    uint32_t& maxMemoryUsedThisRun,
    uint32_t& totalMemoryRecommended);

  /*****************************************************************************/
  /** Perform write
   *
   * @param[in] writeContext
   * Write context
   *
   * @param[in] dataValue
   * Data value
   *
   * @param[in] sourceTimestamp
   * Source Time stamp
   *
   * @param[in] completesAsynchronously
   * Complete the write Asynchronously is set
   *
   * @param[in] newLengthOfArray
   * New Length Of Array
   *
   * @return
   * Status of the operation.
   */
  Status_t PerformWrite(uintptr_t writeContext,
    UA_Value_t dataValue,
    int64_t* sourceTimeStamp,
    bool_t completesAsynchronously,
    uint32_t* newLengthOfArray);


  /*****************************************************************************/
  /** Set Write Operation Level Result Code
   *
   * @param[in] uintptr_t writeContext
   * Write context
   *
   * @param[in] Status_t resultCode
   * Result code
   *
   * @return
   * Status of the operation.
   */
  Status_t SetWriteOperationLevelResultCode(uintptr_t writeContext, Status_t resultCode);

  /*****************************************************************************/
  /** Perform Read
   *
   * @param[in] readContext
   * read context
   *
   * @param[in] dataValue
   * Data value
   *
   * @param[in] int64_t& sourceTimestamp
   * Source Time stamp
   *
   * @param[in] uint32_t dataQuality
   * Data quality
   *
   * @return
   * Status of the operation.
   */
  Status_t PerformRead(uintptr_t readContext, UA_Value_t dataValue, int64_t sourceTimestamp, uint32_t dataQuality);

  /*****************************************************************************/
  /** Add the IP Address
   *
   * @param[in] uint8_t* ipAddress
   * IP address to add
   *
   * @return
   * Status of the operation.
   */
  Status_t AddIpAddress(uint8_t* ipAddress);

  /*****************************************************************************/
  /** Clear All IP Addresses
   *
   * @return
   * Status of the operation.
   */
  Status_t ClearAllIpAddresses(void);

  /*****************************************************************************/
  /** Add Host Name
   *
   * @return
   * Status of the operation.
   */
  Status_t AddHostname(const char* hostname);

  /*****************************************************************************/
  /** Clear all the Host Name
   *
   * @return
   * Status of the operation.
   */
  Status_t ClearAllHostnames(void);

  /*****************************************************************************/
  /** Set the URI
   *
   * @param[in] const char* uri
   * URI to be set
   *
   * @return
   * Status of the operation.
   */
  Status_t SetURI(const char* uri);

  /*****************************************************************************/
  /** Get the Server state
   *
   * @param[out] bool& shutdown_complete
   * Server state indicates shutdown complete or not
   *
   * @return
   * Returns the server state
   */
  UA_Server_state_t GetServerState(bool& shutdown_complete);

#if (UASDK_INCLUDE_EVENTS > 0)
  /*****************************************************************************/
   /** Fire event
    *
    * This function will be called when the server application want to fire an event
    *
    * @param[in] event
    * The event to be fired
    *
    * @param[in] eventSource
    * The event source node Id of the event to be fired
    *
    * @param[in] receiveTime
    * The UTC time that the event is received or generated
    *
    * @return
    * Status of the operation.
    */
  Status_t FireEvent(IntrusivePtr_t<IAttributeAccess_t> event,
										 IntrusivePtr_t<NodeId_t>& eventSource,
                     IntrusivePtr_t<UtcTime_t>& receiveTime);

	/*****************************************************************************/
	/** Fire System Status Change event
	*
	* This function is used to create and fire a System Status Change event
	*
	* @param[in] state
	* The server state to be changed into
	*
	* @return
	* Status of the operation.
	*/
  Status_t FireSystemStatusChangeEvent(ServerState_t::Enum_t state);

	/**************************************************************************/
	/** Register Audit Event Listener
	*
	* This function is called by the server application to register a callback for audit events
	*
	* @param[in] auditEventListener
	* The listener to receive the callback.  Provide an empty pointer to clear the registered listener.
	*
	* @return
	* Status of the operation
	*/
	Status_t RegisterAuditEventListener(IntrusivePtr_t<IAuditEventListener_t>& auditEventListener);

#endif //UASDK_INCLUDE_EVENTS

};

/*@}*/

}

#endif //UASDK_INCLUDE_SERVER_C_API
#endif //(UASDK_INCLUDE_SERVER)
#endif // _UASERVER_T_
