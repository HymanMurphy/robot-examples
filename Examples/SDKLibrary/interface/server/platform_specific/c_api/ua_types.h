/** @file */

/**
 * \defgroup grpServer UA Server
 * \defgroup grpServer_C_API UA Server C API
 * \defgroup grpServer_ST UA Server Single Thread Implementation
 * \defgroup grpServer_MT UA Server MultiThread Implementation
 * \defgroup grpAddressSpace Address Space Interfaces
 * \defgroup grpTcpIp TCP/IP Functions
 * \defgroup grpMemory Memory Allocation Functions
 * \defgroup grpSecurity Security Functions
 * \defgroup grpStatusCodes OPC UA Status Codes
 * \defgroup grpC_APITypes C API Data Types
 * \defgroup grpBuffers Buffers
 * \defgroup grpSmartPointer Smart Pointers
 * \defgroup grpDataType Data Type Definitions
 * \defgroup grpTimer Timers
 * \defgroup grpMiscellaneous Miscellaneous
 * \defgroup grpCTypes C Type Definitions
 * \defgroup grpBuildConfig UA Server Build Configuration Definitions
 * \defgroup grpServerConfig UA Server Configuration
 * \defgroup grplockST UA Server Lock implementation for Single thread
 * \defgroup grplockCPP11 UA Server Lock implementation for CPP11 standard
 * \defgroup grpEventsandAC Events, Alarms and Conditions Interfaces
 * \defgroup grpClient Client Interfaces
 * \defgroup grpBuild Build Macros
 *
 */

/*****************************************************************************/
/** \file ua_types.h
 *  \brief Common definitions for the OPC-UA Embedded Server SDK.
 *
 */

/*****************************************************************************/
/* Copyright (c) 2009 - 2013 MatrikonOPC.
 *
 * ALL RIGHTS RESERVED.
 *
 * The information contained herein is the confidential and proprietary product
 * of MatrikonOPC.  Any unauthorized use, reproduction or
 * transfer of this information is strictly prohibited.
 */

#ifndef _UA_TYPES_
#define _UA_TYPES_

#include "uasdk_includes.h"
#if (UASDK_INCLUDE_SERVER)
#if (UASDK_INCLUDE_SERVER_C_API > 0)

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "uasdk_default_build_config.h"
#include "uasdk_c_declarations.h"
#include "opcua_status_codes.h"

/** \addtogroup grpServer_C_API
 *@{*/

/** \addtogroup grpC_APITypes
*@{*/

/*****************************************************************************/
/** Enumeration of value data types that can be stored in a variable node
 * 
 */
typedef enum 
{
  UA_TYPE_Invalid         = 0,  /**< Invalid type */
  UA_TYPE_Boolean         = 1,  /**< Boolean */
  UA_TYPE_SByte           = 2,  /**< signed byte */
  UA_TYPE_Byte            = 3,  /**< unsigned byte */
  UA_TYPE_Int16           = 4,  /**< signed 16 bit integer */
  UA_TYPE_UInt16          = 5,  /**< unsigned 16 bit integer */
  UA_TYPE_Int32           = 6,  /**< signed 32 bit integer */
  UA_TYPE_UInt32          = 7,  /**< unsigned 32 bit integer */
  UA_TYPE_Int64           = 8,  /**< signed 64 bit integer */
  UA_TYPE_UInt64          = 9,  /**< unsigned 64 bit integer */
  UA_TYPE_Float           = 10, /**< 32 bit single precision floating point */
  UA_TYPE_Double          = 11, /**< 64 bit double precision floating point */
  UA_TYPE_String          = 12, /**< UTF8 string */
  UA_TYPE_DateTime        = 13, /**< 64 bit signed integer containing date and time */
  UA_TYPE_Guid            = 14, /**< 16 byte long array of unsigned bytes */
  UA_TYPE_ByteString      = 15, /**< variable length array of unsigned bytes */
  UA_TYPE_XmlElement      = 16, /**< UTF8 string containing XML */
  UA_TYPE_NodeId          = 17, /**< Not supported for application */
  UA_TYPE_ExpandedNodeId  = 18, /**< Not supported for application */
  UA_TYPE_StatusCode      = 19, /**< Not supported for application */
  UA_TYPE_QualifiedName   = 20, /**< Not supported for application */
  UA_TYPE_LocalizedText   = 21, /**< Not supported for application */
  UA_TYPE_ExtensionObject = 22, /**< Not supported for application */
  UA_TYPE_DataValue       = 23, /**< Not supported for application */
  UA_TYPE_Variant         = 24, /**< Not supported for application */
  UA_TYPE_Range           = 884,/**< Not supported for application */
  UA_TYPE_EUInformation   = 887 /**< Not supported for application */
} UA_Value_type_t;

/*****************************************************************************/
/** \brief Enumeration of server state
 * 
 * API functions exist to read and write server state. When shutting down the
 * server, the shutdown takes 60 seconds to allow clients an opportunity to
 * disconnect.
 *
 */
typedef enum 
{
  opcua_server_state_running = 0,
  opcua_server_state_failed = 1,
  opcua_server_state_no_configuration = 2,
  opcua_server_state_suspended = 3,
  opcua_server_state_shutdown = 4,
  opcua_server_state_test = 5,
  opcua_server_state_communication_fault = 6,
  opcua_server_state_unknown = 7,
  end
} UA_Server_state_t;

/*****************************************************************************/
/** \brief Enumeration of log message severity
 *
 * UAServer_Log_callback() flags the severity of the log message with this type.
 *
 */
typedef enum
{
  UA_LOG_SEVERITY_ERROR = 0,   /**< Error */
  UA_LOG_SEVERITY_INFO = 1     /**< Info */
} UA_Log_severity_t;

/*****************************************************************************/
/** \brief Enumeration of log message data payload type
 *
 * UAServer_Log_callback() describes the format of the optional log data payload
 * with this type.
 *
 */
typedef enum
{
  UA_LOG_PAYLOAD_NONE = 0,      /**< No data payload */
  UA_LOG_PAYLOAD_CSTRING = 1,   /**< String payload */
  UA_LOG_PAYLOAD_BINARY = 2     /**< Binary payload */
} UA_Log_payload_t;

/*****************************************************************************/
/** \brief Enumeration of monitored item callabck operation type
 *
 * UAServer_Callback_monitored_item() uses this type.
 *
 */
typedef enum
{
  UA_MON_ITEM_CREATED = 0,    /**< A monitored item was created */
  UA_MON_ITEM_MODIFIED = 1,   /**< A monitored item was modified */
  UA_MON_ITEM_DESTROYED = 2   /**< A monitored item was destroyed */
} UA_Mon_Item_Callback_Operation_t;

/*****************************************************************************/
/** \brief A structure representing XMLElement values.
 * 
 */
typedef UA_Byte_string_t UA_Xml_element_t;

/*****************************************************************************/
/** \brief Represents a GUID as a pointer to an array of 16 bytes.
 *
 * As an example, GUID “72962B91-FA75-4AE6-8D28-B404DC7DAF63” should be
 * encoded as follows:
 *
 *    Data1      Data2   Data3           Data4
 * 91 2B 96 72   75 FA   E6 4A   8D 28 B4 04 DC 7D AF 63
 *
 *  0  1  2  3    4  5    6  7    8  9 10 11 12 13 14 15
 */
typedef uint8_t* UA_GUID_t;

/*****************************************************************************/
/** \brief The valid pointer types for a read or write operation
 * by the stack on host maintained variables (node value attributes) via
 * read and write callbacks.
 * 
 */
typedef union
{
  bool_t*           value_Boolean;    /**< Boolean value attribute */
  int8_t*           value_SByte;      /**< Signed byte value attribute */
  uint8_t*          value_Byte;       /**< Unsigned byte value attribute */
  int16_t*          value_Int16;      /**< Signed 16 bit integer value attribute */
  uint16_t*         value_UInt16;     /**< Unsigned 16 bit integer value attribute */
  int32_t*          value_Int32;      /**< Signed 32 bit integer value attribute */
  uint32_t*         value_UInt32;     /**< Unsigned 32 bit integer value attribute */
  int64_t*          value_Int64;      /**< Signed 64 bit integer value attribute */
  uint64_t*         value_UInt64;     /**< Unsigned 64 bit integer value attribute */
  float*            value_Float;      /**< 32 bit floating point value attribute */
  double*           value_Double;     /**< 64 bit floating point value attribute */
  UA_Var_string_t*  value_String;     /**< UTF8 string value attribute */
  int64_t*          value_DateTime;   /**< DateTime value attribute */
  uint8_t*          value_GUID;       /**< GUID value attribute */
  UA_Byte_string_t* value_ByteString; /**< Unsigned byte array value attribute */
  UA_Xml_element_t* value_XmlElement; /**< UTF8 string containing XML value attribute */
  void*             value_Any;        /**< Provided for convenience to allow void* usage in API calls */
} UA_Value_t;

/*****************************************************************************/
/** \brief The configuration structure for the UA Server BuildInfo object
 *
 */
typedef struct
{
  /** Product URI for BuildInfo Standard Node */
  const char* PRODUCT_URI;
  /** Product name for BuildInfo Standard Node */
  const char* PRODUCT_NAME;
  /** Manufacturer name for BuildInfo Standard Node */
  const char* MANUFACTURER_NAME;
  /** Software version for BuildInfo Standard Node */
  const char* SOFTWARE_VERSION;
  /** Build number for BuildInfo Standard Node */
  const char* BUILD_NUMBER;
  /** Build date (Windows FileTime format) for BuildInfo Standard Node */
  uint64_t BUILD_DATE;
} UA_Configuration_BuildInfo_t;

/*****************************************************************************/
/** \brief The configuration structure for the UA Server TCP Binary Layer
 *
 */
typedef struct
{
  /** Hello Timeout in ms */
  uint32_t HELLO_TIMEOUT_IN_MS;
  /** Connection Timeout in ms */
  uint32_t CONNECTION_TIMEOUT_IN_MS;
  /** Port number (4840 is the standard port) */
  uint32_t PORT_NUMBER;
  /** Maximum TCP Binary Message Size */
  uint32_t MAX_MESSAGE_SIZE;
  /** Maximum TCP Binary Message Chunk Size */
  uint32_t MAX_MESSAGE_CHUNK_SIZE;
  /** Maximum TCP Binary Message Chunk Count */
  uint32_t MAX_MESSAGE_CHUNK_COUNT;
  /** Maximum TCP Binary connections */
  uint32_t MAX_CONNECTIONS;
} UA_Configuration_TcpBinary_t;

/*****************************************************************************/
/** \brief The configuration structure for the UA Server Secure Conversation
 * Layer
 *
 */
typedef struct
{
  /** Minimum Revised Channel Lifetime in ms */
  uint32_t MIN_REVISED_CHANNEL_LIFETIME_IN_MS;
  /** Maximum Revised Channel Lifetime in ms */
  uint32_t MAX_REVISED_CHANNEL_LIFETIME_IN_MS;
  /** Maximum Secure Channels */
  uint32_t MAX_SECURE_CHANNELS;
} UA_Configuration_SecureConversation_t;

/*****************************************************************************/
/** \brief The configuration structure for the UA Server Security
 * Policies
 *
 * Each field in the structure represents a security policy. To disable the
 * security policy enter zero for the field value.
 *
 * If you want to enable a security policy add a user token policy to the
 * security policy by specifying a bitmap of enabled user token policies as
 * defined below.
 *
 * If using user token username / password for unencrypted endpoint security
 * policies it is recommended to only enable user token policies that encrypt
 * the password. For other endpoint security policies there is no need to encrypt
 * the user password as the secure channel is encrypted. In the case of
 * encrypted endpoint security policies it is recommended to enable
 * username / password - token security policy none.
 *
 * If using X509v3 Certificate user token policies it is recommended to only
 * use token security polices that require signing (see Part 4 of the OPC UA
 * specification or contact support for more information).
 *
 * BITMAP
 * ------
 *
 * BIT      Meaning
 *
 *  0       User Token Anonymous - Token Security Policy None
 *  1       User Token Username / Password - Token Security Policy None
 *  2       User Token Username / Password - Token Security Policy Basic128Rsa15
 *  3       User Token Username / Password - Token Security Policy Basic256
 *  4       User Token Username / Password - Token Security Policy Basic256Sha256
 *  5       User Token X509v3 Certificate - Token Security Policy None
 *  6       User Token X509v3 Certificate - Token Security Policy Basic128Rsa15
 *  7       User Token X509v3 Certificate - Token Security Policy Basic256
 *  8       User Token X509v3 Certificate - Token Security Policy Basic256Sha256
 *  9 - 63  Reserved
 *
 */
typedef struct
{
  /** Endpoint Security Policy - None */
  uint64_t ENDPOINT_SECURITY_POLICY_NONE;
  /** Endpoint Security Policy - Sign - Basic128Rsa15 */
  uint64_t ENDPOINT_SECURITY_POLICY_SIGN_Basic128Rsa15;
  /** Endpoint Security Policy - Sign & Encrypt - Basic128Rsa15 */
  uint64_t ENDPOINT_SECURITY_POLICY_SIGN_AND_ENCRYPT_Basic128Rsa15;
  /** Endpoint Security Policy - Sign - Basic256 */
  uint64_t ENDPOINT_SECURITY_POLICY_SIGN_Basic256;
  /** Endpoint Security Policy - Sign & Encrypt - Basic256 */
  uint64_t ENDPOINT_SECURITY_POLICY_SIGN_AND_ENCRYPT_Basic256;
  /** Endpoint Security Policy - Sign - Basic256Sha256 */
  uint64_t ENDPOINT_SECURITY_POLICY_SIGN_Basic256Sha256;
  /** Endpoint Security Policy - Sign & Encrypt - Basic256Sha256 */
  uint64_t ENDPOINT_SECURITY_POLICY_SIGN_AND_ENCRYPT_Basic256Sha256;
} UA_Configuration_Security_t;

/*****************************************************************************/
/** \brief Bit definitions for the UA Server Security Configuration bitmaps
 *
 */

/** User Token Anonymous - Token Security Policy None */
#define UA_USER_TOKEN_POLICY_ANONYMOUS_TOKEN_SECURITY_POLICY_NONE           (1<<0)

/** User Token Username / Password - Token Security Policy None */
#define UA_USER_TOKEN_POLICY_USERNAME_PASSWORD_TOKEN_SECURITY_POLICY_NONE           (1<<1)
/** User Token Username / Password - Token Security Policy Basic128Rsa15 */
#define UA_USER_TOKEN_POLICY_USERNAME_PASSWORD_TOKEN_SECURITY_POLICY_Basic128Rsa15  (1<<2)
/** User Token Username / Password - Token Security Policy Basic256 */
#define UA_USER_TOKEN_POLICY_USERNAME_PASSWORD_TOKEN_SECURITY_POLICY_Basic256       (1<<3)
/** User Token Username / Password - Token Security Policy Basic256Sha256 */
#define UA_USER_TOKEN_POLICY_USERNAME_PASSWORD_TOKEN_SECURITY_POLICY_Basic256Sha256 (1<<4)

/** User Token X509v3 Certificate - Token Security Policy None */
#define UA_USER_TOKEN_POLICY_X509v3_CERTIFICATE_TOKEN_SECURITY_POLICY_NONE           (1<<5)
/** User Token X509v3 Certificate - Token Security Policy Basic128Rsa15 */
#define UA_USER_TOKEN_POLICY_X509v3_CERTIFICATE_TOKEN_SECURITY_POLICY_Basic128Rsa15  (1<<6)
/** User Token X509v3 Certificate - Token Security Policy Basic256 */
#define UA_USER_TOKEN_POLICY_X509v3_CERTIFICATE_TOKEN_SECURITY_POLICY_Basic256       (1<<7)
/** User Token X509v3 Certificate - Token Security Policy Basic256Sha256 */
#define UA_USER_TOKEN_POLICY_X509v3_CERTIFICATE_TOKEN_SECURITY_POLICY_Basic256Sha256 (1<<8)

/*****************************************************************************/
/** \brief The configuration structure for the Server Intervals
 *
 * Controls the intervals the server allows for subscriptions and monitored
 * items. It also controls the frequency with which the server cycles all
 * internal timers, counters, etc.
 */
typedef struct
{
  /** Intervals Array Length */
  uint32_t INTERVALS_ARRAY_LENGTH;
  /** Intervals Array */
  uint64_t* INTERVALS_ARRAY;
  /** Allow additional arbitrary intervals (can impact performance) */
  bool_t ALLOW_ARBITRARY_INTERVALS;
  /** Minimum interval in ms (must be <= first value in intervals array) */
  uint64_t MIN_INTERVAL_IN_MS;
  /** Maximum interval in ms (must be >= last value in intervals array) */
  uint64_t MAX_INTERVAL_IN_MS;
  /** Server cyclic rate in ms */
  uint32_t CYCLIC_RATE_IN_MS;
} UA_Configuration_Intervals_t;

/*****************************************************************************/
/** \brief The configuration structure for the UA Server Services
 *
 */
typedef struct
{
  /** Minimum Revised Session Timeout in ms */
  uint32_t MIN_REVISED_SESSION_TIMEOUT_IN_MS;
  /** Maximum Revised Session Timeout in ms */
  uint32_t MAX_REVISED_SESSION_TIMEOUT_IN_MS;
  /** Maximum Sessions */
  uint32_t MAX_SESSIONS;
  /** Maximum Subscriptions per Session */
  uint32_t MAX_SUBSCRIPTIONS_PER_SESSION;
  /** Minimum Subscription Max Keep Alive Count */
  uint32_t MIN_MAX_KEEP_ALIVE_COUNT;
  /** Maximum Subscription Max Keep Alive Count */
  uint32_t MAX_MAX_KEEP_ALIVE_COUNT;
  /** Maximum Notification Retransmission Queue Size */
  uint32_t MAX_NOTIFICATION_RETRANSMISSION_QUEUE_SIZE;
  /** Maximum Publish Requests per Session (must be greater than MAX_SUBSCRIPTIONS_PER_SESSION) */
  uint32_t MAX_PUBLISH_REQUESTS_PER_SESSION;
  /** Maximum Browse References per Node */
  uint32_t BROWSE_MAX_REFS_PER_NODE;
  /** Maximum Total Monitored Items (including all sessions) */
  uint32_t MAX_MONITORED_ITEMS;
  /** Maximum Monitored Items Queue Size */
  uint32_t MAX_MON_ITEM_QUEUE_SIZE;
} UA_Configuration_Services_t;

/*****************************************************************************/
/** \brief The configuration structure for the Namespace Array
 *
 * The first two entries in the namespace array are the OPC-UA Namespace and the
 * server namespace. These are provided internally and do not need to be added
 * here. Any namespaces added here will be added to the namespace array
 * sequentially beginning at index 2 of the Namespace Array.
 */
typedef struct
{
  /** Namespace Array Length */
  uint32_t NAMESPACE_ARRAY_LENGTH;
  /** Namespace Array */
  const char** NAMESPACE_ARRAY;
} UA_Configuration_NamespaceArray_t;

/*****************************************************************************/
/** \brief The configuration structure for the UA Server Address Space
 *
 */
typedef struct
{
  /** Additional Namespaces */
  UA_Configuration_NamespaceArray_t NAMESPACES;
} UA_Configuration_AddressSpace_t;

/*****************************************************************************/
/** \brief The configuration structure for the UA Server Certificate
 * Management
 *
 */
typedef struct
{
  /** Software Certificates Length */
  uint32_t SOFTWARE_CERTIFICATES_LENGTH;
  /** Software Certificates */
  UA_Byte_string_t* SOFTWARE_CERTIFICATES;
} UA_Configuration_CertManagement_t;

/*****************************************************************************/
/** \brief The configuration structure for the UA Server Locale Handling
 *
 */
typedef struct
{
  /** Locale ID Array Length */
  uint32_t LOCALE_ID_ARRAY_LENGTH;
  /** Locale ID Array
   * Add a table of available locales
   *
   * These parameters provide the supported locales to the library.
   * The library uses this table when negotiating sessions with clients and returns
   * the corresponding locale index to the host when making translate callbacks.
   * This table is referenced internally by the library so it must remain in scope.
   * The locale at index 0 is the default locale which is used for the BrowseName
   * of each node. */
  const char** LOCALE_ID_ARRAY;
} UA_Configuration_Locales_t;

/*****************************************************************************/
/** \brief The configuration structure for the UA Server Profile Array
 *
 */
typedef struct
{
  /** Server Profile Array Length */
  uint32_t SERVER_PROFILE_ARRAY_LENGTH;
  /** Server Profile Array */
  const char** SERVER_PROFILE_ARRAY;
} UA_Configuration_ProfileArray_t;

/*****************************************************************************/
/** \brief The configuration structure for the UA Server Operation Limits object
 *
 */
typedef struct
{
  /** Enforce Operation Limits */
  bool_t ENFORCE_OPERATION_LIMITS;
  /** Maximum Nodes per Read */
  uint32_t MAX_NODES_PER_READ;
  /** Maximum Nodes per History Read Data */
  uint32_t MAX_NODES_PER_HISTORY_READ_DATA;
  /** Maximum Nodes per History Read Events */
  uint32_t MAX_NODES_PER_HISTORY_READ_EVENTS;
  /** Maximum Nodes per Write */
  uint32_t MAX_NODES_PER_WRITE;
  /** Maximum Nodes per History Update Data */
  uint32_t MAX_NODES_PER_HISTORY_UPDATE_DATA;
  /** Maximum Nodes per History Update Events */
  uint32_t MAX_NODES_PER_HISTORY_UPDATE_EVENTS;
  /** Maximum Nodes per Method Call */
  uint32_t MAX_NODES_PER_METHOD_CALL;
  /** Maximum Nodes per Browse */
  uint32_t MAX_NODES_PER_BROWSE;
  /** Maximum Nodes per RegisterNodes */
  uint32_t MAX_NODES_PER_REGISTER_NODES;
  /** Maximum Nodes per TranslateBrowsePathsToNodeIds */
  uint32_t MAX_NODES_PER_TRANSLATE_BROWSE_PATHS_TO_NODE_IDS;
  /** Maximum Nodes per Node Management */
  uint32_t MAX_NODES_PER_NODE_MANAGEMENT;
  /** Maximum Monitored Items per call */
  uint32_t MAX_MONITORED_ITEMS_PER_CALL;
} UA_Configuration_OperationLimits_t;

/*****************************************************************************/
/** \brief The configuration structure for the UA Server Capabilities object
 *
 */
typedef struct
{
  /** Maximum Browse Continuation Points */
  uint32_t MAX_BROWSE_CONTINUATION_POINTS;
  /** Maximum Query Continuation Points */
  uint32_t MAX_QUERY_CONTINUATION_POINTS;
  /** Maximum History Continuation Points */
  uint32_t MAX_HISTORY_CONTINUATION_POINTS;
  /** Maximum Array Length */
  uint32_t MAX_ARRAY_LENGTH;
  /** Maximum String Length */
  uint32_t MAX_STRING_LENGTH;
  /** OperationLimits */
  UA_Configuration_OperationLimits_t OPERATION_LIMITS;
} UA_Configuration_ServerCapabilities_t;

/*****************************************************************************/
/** \brief The configuration structure for the UA Server miscellaneous internals
 *
 */
typedef struct
{
  /** Allocate on the heap instead of using the ram buffer */
  bool_t USE_HEAP_RATHER_THAN_RAM_BUFFER;
  /** Pointer to RAM buffer */
  uint8_t* BUFFER;
  /** Buffer length in bytes */
  uint32_t BUFFER_LENGTH_IN_BYTES;
  /** Max allocation size */
  uint32_t MAX_ALLOCATION_SIZE_IN_BYTES;
  /** Address Space hash table number of buckets */
  uint32_t ADDRESS_SPACE_HASH_TABLE_NO_OF_BUCKETS;
  /** Maximum number of deferred response messages */
  uint32_t MAX_NO_OF_DEFERRED_RESPONSE_MESSAGES;
  /** Maximum number of deferred operations per response message */
  uint32_t MAX_NO_OF_DEFERRED_OPERATIONS_PER_RESPONSE_MESSAGE;
} UA_Configuration_Internals_t;

/*****************************************************************************/
/** \brief The configuration structure for the UA Server diagnostics
 *
 */
typedef struct
{
  /** Enable informational log messages */
  bool_t ENABLE_INFO_LOG;
  /** Enable error log messages */
  bool_t ENABLE_ERROR_LOG;
} UA_Configuration_Diagnostics_t;

/*****************************************************************************/
/** \brief The configuration structure for the UA Server Filters
 *
 */
typedef struct
{
  /** Disable percent deadband filter support */
  bool_t DISABLE_PCT_DEADBAND;
  /** Disable percent deadband filter support for all arrays */
  bool_t DISABLE_PCT_DEADBAND_VECTORS;
  /** Disable percent deadband filter support for all floating point values */
  bool_t DISABLE_PCT_DEADBAND_FLOATING_POINT;
  /** Disable percent deadband filter support for double precision floating point */
  bool_t DISABLE_PCT_DEADBAND_DOUBLE;
  /** Disable percent deadband filter support for all floating point arrays */
  bool_t DISABLE_PCT_DEADBAND_FLOATING_POINT_VECTORS;
  /** Disable percent deadband filter support for double precision floating point arrays */
  bool_t DISABLE_PCT_DEADBAND_DOUBLE_VECTORS;
} UA_Configuration_Filters_t;

/*****************************************************************************/
/** \brief The configuration structure for the UA Server
 *
 */
typedef struct
{
  /** Parameters for TCP Binary stack layer */
  UA_Configuration_TcpBinary_t TCP_BINARY;
  /** Parameters for Secure Conversation layer */
  UA_Configuration_SecureConversation_t SECURE_CONVERSATION;
  /** Parameters for Security Policies */
  UA_Configuration_Security_t SECURITY;
  /** Parameters for Services */
  UA_Configuration_Services_t SERVICES;
  /** Parameters for Address Space */
  UA_Configuration_AddressSpace_t ADDRESS_SPACE;
  /** Parameters for Certificate Management */
  UA_Configuration_CertManagement_t CERT_MANAGEMENT;
  /** Parameters for ProfileArray */
  UA_Configuration_ProfileArray_t PROFILE_ARRAY;
  /** Parameters for ServerCapabilities */
  UA_Configuration_ServerCapabilities_t SERVER_CAPABILITIES;
  /** Parameters for Locales */
  UA_Configuration_Locales_t LOCALES;
  /** Parameters for Internals */
  UA_Configuration_Internals_t INTERNALS;
  /** Parameters for Diagnostics */
  UA_Configuration_Diagnostics_t DIAGNOSTICS;
  /** Parameters for Filters */
  UA_Configuration_Filters_t FILTERS;
  /** Parameters for Intervals */
  UA_Configuration_Intervals_t INTERVALS;
} UA_Configuration_t;


/*****************************************************************************/
/** \brief Node id encoding types for an address space node.
 *
 */
typedef enum
{
  opcua_node_encoding_numeric     = 0x02, /**< Numeric */
  opcua_node_encoding_string      = 0x03, /**< String */
  opcua_node_encoding_guid        = 0x04, /**< GUID */
  opcua_node_encoding_bytestring  = 0x05  /**< Opaque */
} UA_NodeId_Identifier_Type_t;

/*****************************************************************************/
/** \brief Optionally specifies a non-opaque node id for an address space node.
 * 
 */
typedef struct
{
  /**
   * Specifies the identifier type for the node. If this parameter is set to
   * the default value then the SDK will assign an opaque node id to the node.
   * Opaque node ids are easily decoded by the SDK and offer the best
   * performance. Only change this parameter if your application requires it.
   */
  UA_NodeId_Identifier_Type_t identifier_type;
  /**
   * A node id containing a string. Server node ids must be unique.
   * The SDK performs no testing for uniqueness. The application must ensure
   * that the provided string is unique.
   */
  UA_UTF8_string_t  string_identifier;
  /**
   * A node id containing a GUID. Server node ids must be unique.
   * The SDK performs no testing for uniqueness. The application must ensure
   * that the provided GUID is unique.
   */
  UA_GUID_t  guid_identifier;
  /**
   * A node id containing a numeric value. Server node ids must be unique.
   * The SDK performs no testing for uniqueness. The application must ensure
   * that the provided value is unique.
   */
  uint32_t  numeric_identifier;
} UA_NodeId_Config_t;

/*****************************************************************************/
/** \brief A configuration structure for all address space nodes.
 *
 */
typedef struct
{
  /**
   * A mandatory unique identifier that identifies the node in the library.
   * The value zero is invalid.
   */
  uintptr_t  node_handle;
  /**
   * A mandatory unique identifier that allows the host to efficiently look up the
   * node name text to display in a translate callback. The value zero is invalid.
   */
  uintptr_t  display_name_handle;
  /**
   * An optional unique identifier that allows the host to efficiently look up the
   * node description text to display in a translate callback. The value zero is
   * invalid.
   */
  uintptr_t  description_handle;
  /**
   * An optional visibility mask that restricts the visibility of the node depending
   * on which user is logged in. The anonymous user is bit 0 and bits 1 - 15
   * represent the corresponding users or user groups.
   */
  uint16_t  user_visibility;
  /**
   * Specifies the namespace index for this node. The UA namespace is 0 and cannot
   * be used. The default server namespace is 1. Other namespaces may be added
   * to the configuration data structure.
   */
  uint16_t  namespace_index;
  /**
   * An optional parameter set that defines the NodeId for the node as a numeric, string
   * or a GUID. If this parameter is set to default values then the SDK will assign
   * an opaque node id to the node. Opaque node ids are easily decoded by the SDK
   * and offer the best performance. Only populate this parameter set if your
   * application requires it.
   */
  UA_NodeId_Config_t node_id;
} UA_Base_t;

/*****************************************************************************/
/** \brief A configuration structure for Folder address space nodes.
 * 
 */
typedef UA_Base_t UA_Folder_t;

/*****************************************************************************/
/** \brief A configuration structure for View address space nodes.
 * 
 */
typedef UA_Folder_t UA_View_t;

/*****************************************************************************/
/** \brief A configuration structure for Method address space nodes.
 * 
 */
typedef struct
{
  /**
   * Configuration common to all nodes
   */
  UA_Base_t       base_config;
  /**
   * The file is writable
   */
  bool_t          writable;
  /**
   * An optional writable mask that restricts write access of the file depending
   * on which user is logged in. The anonymous user is bit 0 and bits 1 - 15
   * represent the corresponding users or user groups.
   */
  uint16_t  user_writable;
} UA_File_t;

/*****************************************************************************/
/** \brief A configuration structure for File address space nodes.
 *
 */
typedef struct
{
  /**
   * Configuration common to all nodes
   */
  UA_Base_t       base_config;
  /**
   * The method is executable
   */
  bool_t          executable;
  /**
   * The method is user executable
   */
  bool_t          user_executable;
} UA_Method_t;

/*****************************************************************************/
/** \brief A configuration structure for BaseDataVariable address space nodes.
 * 
 */
typedef struct
{
  /**
   * Configuration common to all nodes
   */
  UA_Base_t         base_config;
  /**
   * The data type of the value attribute
   */
  UA_Value_type_t   value_type;
  /**
   * The maximum array length of the value attribute or zero if scalar
   */
  uint32_t          max_array_length;
  /**
   * The users that are allowed read the variable value attribute
   */
  uint16_t          user_read_permissions;                 
  /**
   * The users that are allowed write the variable value attribute
   */
  uint16_t          user_write_permissions;
} UA_BaseDataVariable_t;

/*****************************************************************************/
/** \brief A configuration structure for DataItem address space nodes.
 * 
 */
typedef struct
{
  /**
   * Configuration inherited from BaseDataVariable
   */
  UA_BaseDataVariable_t data_variable_config;
  /**
   * This node exposes a definition property
   */
  bool_t                use_definition;
  /**
   * Definition property (see user manual for description)
   */
  UA_UTF8_string_t      definition;
  /**
   * This node exposes a value precision property
   */
  bool_t                use_value_precision;
  /**
   * Value Precision property (see user manual for description)
   */
  float                 value_precision;
} UA_DataItem_t;

/**
 * \brief Range data type
 */
typedef struct
{
/**
 * Low limit
 */
  float low;
/**
 * High limit
 */
  float high;
} UA_Range_t;

/**
 * \brief Engineering Units configuration (see user manual for description)
 */
typedef struct
{
/**
 * Namespace of Standards Body that defines units (see user manual for
 * description)
 */
  UA_UTF8_string_t  namespace_uri;
/**
 * Unit ID (see user manual for description)
 */
  int16_t           unit_id;
  /**
   * A unique identifier that allows the host to efficiently look up the
   * property name text to display in a translate callback. The value zero
   * is invalid.
   */
  uintptr_t          display_name_handle;
  /**
   * A unique identifier that allows the host to efficiently look up the
   * property description text to display in a translate callback. The
   * value zero is invalid.
   */
  uintptr_t          description_handle;
} UA_EUInformation_t;

/*****************************************************************************/
/** \brief A configuration structure for AnalogItem address space nodes.
 * 
 */
typedef struct
{
  /**
   * Configuration inherited from DataItem
   */
  UA_DataItem_t       data_item_config;
  /**
   * This node exposes an Instrument Range property (see user manual for
   * description)
   */
  bool_t              use_instrument_range;
  /**
   * Full scale instrument range
   */
  UA_Range_t          instrument_range;
  /**
   * Typical operating range
   */
  UA_Range_t          EU_range;
  /**
   * This node exposes an Engineering Units property (see user manual for
   * description)
   */
  bool_t              use_engineering_units;
  /**
   * Configuration for Engineering Units property
   */
  UA_EUInformation_t  engineering_units;
} UA_AnalogItem_t;

/*****************************************************************************/
/** \brief A configuration structure for TwoStateDiscrete address space nodes.
 * 
 */
typedef struct
{
  /**
   * Configuration inherited from DataItem
   */
  UA_DataItem_t data_item_config;
  /**
   * Display name handle for true state text.
   */
  uintptr_t      true_state_handle;
  /**
   * Display name handle for false state text.
   */
  uintptr_t      false_state_handle;
} UA_TwoStateDiscrete_t;

/*****************************************************************************/
/** \brief A configuration structure for MultiStateDiscrete address space nodes.
 * 
 */
typedef struct
{
  /**
   * Configuration inherited from DataItem
   */
  UA_DataItem_t data_item_config;
  /**
   * Number of values present in the enumeration
   */
  uint16_t      no_of_values;
  /**
   * Display name handle for enum strings. This handle resolves to on
   * an array of UTF8 strings with the same number elements as
   * the number of values above.
   */
  uintptr_t      enum_handle;
} UA_MultiStateDiscrete_t;

/*@}*/

/*@}*/

#ifdef __cplusplus
}
#endif

#endif //UASDK_INCLUDE_SERVER_C_API
#endif //(UASDK_INCLUDE_SERVER)
#endif /*_UA_TYPES_*/

