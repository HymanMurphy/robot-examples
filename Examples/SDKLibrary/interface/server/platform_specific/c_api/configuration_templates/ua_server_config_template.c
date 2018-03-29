/*****************************************************************************/
/** \file opcua_server_config_template.c
 *  \brief Instance specific settings for the OPC-UA Server.
 *
 */

#if (0) /*A template only, do not compile this file but copy it to generate your own*/
 
#include "ua_types.h"

/*****************************************************************************/
/* Copyright (c) 2009 - 2012 Embedded Labs Limited.
 *
 * ALL RIGHTS RESERVED.
 *
 * The information contained herein is the confidential and proprietary product
 * of Embedded Labs Limited.  Any unauthorized use, reproduction or
 * transfer of this information is strictly prohibited.
 */

/** OPC-UA RAM buffer */
#define OPCUA_BUF_SIZE (10 * 1024 * 1024)
uint8_t opcua_buffer[OPCUA_BUF_SIZE];

/** Software certificates */
#define SOFTWARE_CERTIFICATES_LENGTH 0
/*UA_Byte_string_t SOFTWARE_CERTIFICATES[SOFTWARE_CERTIFICATES_LENGTH] =
{
    { 0, 0, NULL }
};*/

/** ServerProfileArray */
#define SERVER_PROFILE_ARRAY_LENGTH 3
const char* SERVER_PROFILE_ARRAY[SERVER_PROFILE_ARRAY_LENGTH] =
{
    "Micro Embedded Device Server Profile",
    "Embedded DataChange Subscription Server Facet",
    "Data Access Server Facet"
};

/** LocaleIdArray */
#define LOCALEID_ARRAY_LENGTH 1
const char* LOCALEID_ARRAY[LOCALEID_ARRAY_LENGTH] =
{
    "en"
};

/** Additional entries for NamespaceArray */
#define NAMESPACE_ARRAY_LENGTH 0
/*const char* NAMESPACE_ARRAY[NAMESPACE_ARRAY_LENGTH] =
{
    "Test namespace"
};*/

/** Intervals Array */
#define INTERVALS_ARRAY_LENGTH 4
uint64_t INTERVALS_ARRAY[INTERVALS_ARRAY_LENGTH] =
{
    100,
    500,
    1000,
    5000
};


/*****************************************************************************/
/** \brief The configuration structure for the UA Server
 *
 */
const UA_Configuration_t UA_CONFIGURATION =
{
  /** Parameters for TCP Binary stack layer */
  {
    /** Hello Timeout in ms */
    60000,
    /** Connection Timeout in ms */
    60000,
    /** Port number (4840 is the standard port) */
    4840,
    /** Maximum TCP Binary Message Size */
    65536,
    /** Maximum TCP Binary Message Chunk Size */
    65536,
    /** Maximum TCP Binary Message Chunk Count */
    1,
    /** Maximum TCP Binary connections */
    12
  },
  /** Parameters for Secure Conversation layer */
  {
    /** Minimum Revised Channel Lifetime in ms */
    60 * 60 * 1000,
    /** Maximum Revised Channel Timeout in ms */
    24 * 60 * 60 * 1000,
    /** Maximum Secure Channels */
    11
  },
  /** Parameters for Security */
  {
    /** Endpoint Security Policy - None */
    UA_USER_TOKEN_POLICY_ANONYMOUS_TOKEN_SECURITY_POLICY_NONE,
    /** Endpoint Security Policy - Sign - Basic128Rsa15 */
    UA_USER_TOKEN_POLICY_ANONYMOUS_TOKEN_SECURITY_POLICY_NONE,
    /** Endpoint Security Policy - Sign & Encrypt - Basic128Rsa15 */
    UA_USER_TOKEN_POLICY_ANONYMOUS_TOKEN_SECURITY_POLICY_NONE,
    /** Endpoint Security Policy - Sign - Basic256 */
    UA_USER_TOKEN_POLICY_ANONYMOUS_TOKEN_SECURITY_POLICY_NONE,
    /** Endpoint Security Policy - Sign & Encrypt - Basic256 */
    UA_USER_TOKEN_POLICY_ANONYMOUS_TOKEN_SECURITY_POLICY_NONE,
    /** Endpoint Security Policy - Sign - Basic256Sha256 */
    UA_USER_TOKEN_POLICY_ANONYMOUS_TOKEN_SECURITY_POLICY_NONE,
    /** Endpoint Security Policy - Sign & Encrypt - Basic256Sha256 */
    UA_USER_TOKEN_POLICY_ANONYMOUS_TOKEN_SECURITY_POLICY_NONE
  },
  /** Parameters for Services */
  {
    /** Minimum Revised Session Timeout in ms */
    60000,
    /** Maximum Revised Session Timeout in ms */
    60000,
    /** Maximum Sessions */
    10,
    /** Maximum Subscriptions per Session */
    15,
    /** Minimum Subscription Keep Alive Count */
    1,
    /** Maximum Subscription Keep Alive Count */
    1000,
    /** Maximum Notification Retransmission Queue Size */
    10,
    /** Maximum Publish Requests per Session */
    20,
    /** Maximum Browse References per Node */
    500,
    /** Maximum Total Monitored Items (including all sessions) */
    100,
    /** Maximum Monitored Items Queue Size */
    10
  },
  /** Parameters for Address Space */
  {
    /** Additional Namespaces */
    {
      /** Namespace Array Length */
      NAMESPACE_ARRAY_LENGTH,
      /** Namespace Array */
      0
    }
  },
  /** Parameters for Certificate Management */
  {
    /** Software Certificates Length */
    SOFTWARE_CERTIFICATES_LENGTH,
    /** Software Certificates */
    0
  },
  /** Parameters for ProfileArray */
  {
    /** Server Profile Array Length */
    SERVER_PROFILE_ARRAY_LENGTH,
    /** Server Profile Array */
    SERVER_PROFILE_ARRAY
  },
  /** Parameters for ServerCapabilities */
  {
    /** Maximum Browse Continuation Points */
    100,
    /** Maximum Query Continuation Points */
    0,
    /** Maximum History Continuation Points */
    0,
    /** Maximum Array Length */
    128,
    /** Maximum String Length */
    4096,
    /** OperationLimits */
    {
      /** Enforce Operation Limits */
      FALSE,
      /** Maximum Nodes per Read */
      100,
      /** Maximum Nodes per History Read Data */
      0,
      /** Maximum Nodes per History Read Events */
      0,
      /** Maximum Nodes per Write */
      100,
      /** Maximum Nodes per History Update Data */
      0,
      /** Maximum Nodes per History Update Events */
      0,
      /** Maximum Nodes per Method Call */
      100,
      /** Maximum Nodes per Browse */
      100,
      /** Maximum Nodes per RegisterNodes */
      100,
      /** Maximum Nodes per TranslateBrowsePathsToNodeIds */
      10,
      /** Maximum Nodes per Node Management */
      0,
      /** Maximum Monitored Items per call */
      100
    }
  },
  /** Parameters for Locales */
  {
    /** Locale ID Array Length */
    LOCALEID_ARRAY_LENGTH,
    /** Locale ID Array */
    LOCALEID_ARRAY
  },
  /** Parameters for Internals */
  {
    /** Allocate on the heap instead of using the ram buffer */
    FALSE,
    /** Pointer to RAM buffer */
    opcua_buffer,
    /** Buffer length in  bytes */
    OPCUA_BUF_SIZE,
    /** Max allocation size in bytes */
    65536,
    /** Address Space hash table number of buckets */
    997,
    /** Maximum number of deferred response messages */
    1,
    /** Maximum number of deferred operations per response message */
    10
  },
  /** Parameters for Diagnostics */
  {
    /** Enable informational log messages */
    TRUE,
    /** Enable error log messages */
    TRUE
  },
  /** Parameters for Filters */
  {
    /** Disable percent deadband filter support */
    FALSE,
    /** Disable percent deadband filter support for all arrays */
    FALSE,
    /** Disable percent deadband filter support for all floating point values */
    FALSE,
    /** Disable percent deadband filter support for double precision floating point */
    FALSE,
    /** Disable percent deadband filter support for all floating point arrays */
    FALSE,
    /** Disable percent deadband filter support for double precision floating point arrays */
    FALSE
  },
  /** Parameters for Intervals */
  {
    /** Intervals Array Length */
    INTERVALS_ARRAY_LENGTH,
    /** Intervals Array */
    INTERVALS_ARRAY,
    /** Allow additional arbitrary intervals (can impact performance) */
    FALSE,
    /** Minimum interval in ms (must be <= first value in intervals array) */
    100,
    /** Maximum interval in ms (must be >= last value in intervals array) */
    (3600000000), //1 hour
    /** Server cyclic rate in ms */
    100
  }
};

#endif
