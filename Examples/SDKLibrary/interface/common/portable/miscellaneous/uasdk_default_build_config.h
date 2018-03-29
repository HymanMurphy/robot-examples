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

#ifndef _UASDK_DEFAULT_BUILD_CONFIG_
#define _UASDK_DEFAULT_BUILD_CONFIG_

// For VS < 2010 we provide stdint.h
#ifdef _MSC_VER
  #if _MSC_VER < 1600 
    #include "stdint.h"
  #else
    #include <stdint.h>
  #endif
#else
  #include <stdint.h>
#endif

#include "uasdk_custom_build_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup grpBuildConfig
 *@{*/

/*****************************************************************************/
/** Include legacy C API
* Set this to 1 to include C API
*/
#ifndef UASDK_INCLUDE_SERVER_C_API
#define UASDK_INCLUDE_SERVER_C_API 0
#endif

#if (UASDK_INCLUDE_SERVER_C_API > 0)

#include "ua_server_config.h"

#ifndef UASDK_MAX_ALIGNMENT
#define UASDK_MAX_ALIGNMENT UA_MAX_ALIGNMENT
#endif

#ifndef UASDK_BIG_ENDIAN
#define UASDK_BIG_ENDIAN UASDK_BIG_ENDIAN
#endif

#ifndef UASDK_CROSS_ENDIAN_DOUBLE
#define UASDK_CROSS_ENDIAN_DOUBLE UA_CROSS_ENDIAN_DOUBLE
#endif

#ifndef UASDK_INCLUDE_SUBSCRIPTIONS
#define UASDK_INCLUDE_SUBSCRIPTIONS UA_INCLUDE_SUBSCRIPTIONS
#endif

#ifndef UASDK_OVERLOAD_NEW_AND_DELETE
#define UASDK_OVERLOAD_NEW_AND_DELETE UA_OVERLOAD_NEW_AND_DELETE
#endif

#ifndef UASDK_NO_THROW
#define UASDK_NO_THROW UA_NO_THROW
#endif

#ifndef UASDK_OPTIMISE_FOR_SPEED
#define UASDK_OPTIMISE_FOR_SPEED UA_OPTIMISE_FOR_SPEED
#endif

#ifndef UASDK_DEADBAND_DATA_TYPE
#define UASDK_DEADBAND_DATA_TYPE UA_DEADBAND_DATA_TYPE_T
#endif

#ifndef UASDK_INCLUDE_SECURITY
#define UASDK_INCLUDE_SECURITY UA_INCLUDE_SECURITY
#endif

#ifndef UASDK_USE_OPENSSL
#define UASDK_USE_OPENSSL UA_USE_OPENSSL
#endif

#ifndef UASDK_USE_NANOSSL
#define UASDK_USE_NANOSSL UA_USE_NANOSSL
#endif

#ifndef UASDK_USE_MBEDTLS
#define UASDK_USE_MBEDTLS UA_USE_MBEDTLS
#endif

#ifndef UASDK_USE_HELPERS
#define UASDK_USE_HELPERS 1
#endif

#ifndef UASDK_USE_DATA_ACCESS_HELPERS
#define UASDK_USE_DATA_ACCESS_HELPERS 0
#endif

#ifndef UASDK_USE_FILE_OBJECT_HELPERS
#define UASDK_USE_FILE_OBJECT_HELPERS UA_INCLUDE_FILE_TRANSFER_METHODS
#endif

/* Set to to include the system call library support in C API*/
#ifndef UASDK_INCLUDE_LIBRARY_C_API
#define UASDK_INCLUDE_LIBRARY_C_API 0
#endif

/* Set to to include the TCP/IP support in C API*/
#ifndef UASDK_INCLUDE_TCPIP_C_API
#define UASDK_INCLUDE_TCPIP_C_API 0
#endif

#ifndef UASDK_INCLUDE_EVENTS
#define UASDK_INCLUDE_EVENTS 0
#endif

#ifndef UASDK_INCLUDE_ALARMS_AND_CONDITIONS
#define UASDK_INCLUDE_ALARMS_AND_CONDITIONS 0
#endif

#ifndef UASDK_INCLUDE_SERVER_DIAGNOSTICS_SUMMARY
#define UASDK_INCLUDE_SERVER_DIAGNOSTICS_SUMMARY 0
#endif

#ifndef UASDK_INCLUDE_SUBSCRIPTION_DIAGNOSTICS
#define UASDK_INCLUDE_SUBSCRIPTION_DIAGNOSTICS 0
#endif

#ifndef UASDK_INCLUDE_SESSION_DIAGNOSTICS
#define UASDK_INCLUDE_SESSION_DIAGNOSTICS 0
#endif

#endif  //UASDK_INCLUDE_SERVER_C_API

/*****************************************************************************/
/* Windows/Linux Multi threaded Server Support.
 * Set to 1 to include
 */
#ifndef UASDK_INCLUDE_SERVER_WINDOWS_LINUX_MT
#define UASDK_INCLUDE_SERVER_WINDOWS_LINUX_MT 0
#endif

/*****************************************************************************/
/* Windows/Linux Single threaded Server Support.
 * Set to 1 to include
 */
#ifndef UASDK_INCLUDE_SERVER_WINDOWS_LINUX_ST
#define UASDK_INCLUDE_SERVER_WINDOWS_LINUX_ST 0
#endif

/*****************************************************************************/
/* LwIP Raw single threaded server.
 * Set to 1 to include
 */
#ifndef UASDK_INCLUDE_SERVER_LWIP_RAW
#define UASDK_INCLUDE_SERVER_LWIP_RAW 0
#endif

/*****************************************************************************/
/* Single threaded Atomic Support.
 * Set to 1 to support
 */
#ifndef UASDK_INCLUDE_ATOMIC_ANY_PLATFORM_ST
#define UASDK_INCLUDE_ATOMIC_ANY_PLATFORM_ST 0
#endif

/*****************************************************************************/
/* Multi threaded Atomic Support.
 * Set to 1 to support
 */
#ifndef UASDK_INCLUDE_ATOMIC_CPP11
#define UASDK_INCLUDE_ATOMIC_CPP11 0
#endif

/*****************************************************************************/
/* To include Standard file support in Linux and Windows Platform
 * Set to 1 to support
 */
#ifndef UASDK_INCLUDE_FILE_WINDOWS_LINUX
#define UASDK_INCLUDE_FILE_WINDOWS_LINUX 0
#endif

/*****************************************************************************/
/* System call support in Linux and Windows platforms
 * Set to 1 to support
 */
#ifndef UASDK_INCLUDE_LIBRARY_WINDOWS_LINUX
#define UASDK_INCLUDE_LIBRARY_WINDOWS_LINUX 0
#endif

/*****************************************************************************/
/* System call support on bare metal platforms
 * Set to 1 to support
 */
#ifndef UASDK_INCLUDE_LIBRARY_BARE_METAL
#define UASDK_INCLUDE_LIBRARY_BARE_METAL 0
#endif

/*****************************************************************************/
/* Single threaded Lock Support in Any platform.
 * Set to 1 to support
 */
#ifndef UASDK_INCLUDE_LOCKS_ANY_PLATFORM_ST
#define UASDK_INCLUDE_LOCKS_ANY_PLATFORM_ST 0
#endif

/*****************************************************************************/
/* Multi threaded Lock Support for Linux.
 * Set to 1 to support
 */
#ifndef UASDK_INCLUDE_LOCKS_CPP11
#define UASDK_INCLUDE_LOCKS_CPP11 0
#endif

/*****************************************************************************/
/* Multi threaded Locks Support for Windows.
 * Set to 1 to support
 */
#ifndef UASDK_INCLUDE_LOCKS_WINDOWS
#define UASDK_INCLUDE_LOCKS_WINDOWS 0
#endif

/*****************************************************************************/
/* Single threaded Reference counting Support for any platform.
 * Set to 1 to support
 */
#ifndef UASDK_INCLUDE_REF_COUNT_ANY_PLATFORM_ST
#define UASDK_INCLUDE_REF_COUNT_ANY_PLATFORM_ST 0
#endif

/*****************************************************************************/
/* Multi threaded reference counting Support.
 * Set to 1 to support
 */
#ifndef UASDK_INCLUDE_REF_COUNT_CPP11
#define UASDK_INCLUDE_REF_COUNT_CPP11 0
#endif

/*****************************************************************************/
/* Single threaded Socket Support for Windows and Linux.
 * Set to 1 to support
 */
#ifndef UASDK_INCLUDE_TCPIP_WINDOWS_LINUX_SOCKETS_SELECT_ST
#define UASDK_INCLUDE_TCPIP_WINDOWS_LINUX_SOCKETS_SELECT_ST 0
#endif

/*****************************************************************************/
/* Multi threaded Socket Support for Windows and Linux.
 * Set to 1 to support
 */
#ifndef UASDK_INCLUDE_TCPIP_WINDOWS_LINUX_SOCKETS_SELECT_MT
#define UASDK_INCLUDE_TCPIP_WINDOWS_LINUX_SOCKETS_SELECT_MT 0
#endif

/*****************************************************************************/
/* LwIP Raw networking support for bare metal.
 * Set to 1 to support
 */
#ifndef UASDK_INCLUDE_TCPIP_LWIP_RAW
#define UASDK_INCLUDE_TCPIP_LWIP_RAW 0
#endif

/*****************************************************************************/
/* Single threaded Thread pool Support for Any platform.
 * Set to 1 to support
 */
#ifndef UASDK_INCLUDE_THREAD_POOL_ANY_PLATFORM_ST
#define UASDK_INCLUDE_THREAD_POOL_ANY_PLATFORM_ST 0
#endif

/*****************************************************************************/
/* Multi threaded Thread pool Support.
 * Set to 1 to support
 */
#ifndef UASDK_INCLUDE_THREAD_POOL_CPP11
#define UASDK_INCLUDE_THREAD_POOL_CPP11 0
#endif

/*****************************************************************************/
/* Single threaded Timers for any platform.
 * Set to 1 to support
 */
#ifndef UASDK_INCLUDE_TIMERS_ANY_PLATFORM_POLLED
#define UASDK_INCLUDE_TIMERS_ANY_PLATFORM_POLLED 0
#endif

/*****************************************************************************/
/* Windows/Linux Multi threaded Client Support.
 * Set to 1 to support
 */
#ifndef UASDK_INCLUDE_CLIENT_WINDOWS_LINUX_MT
#define UASDK_INCLUDE_CLIENT_WINDOWS_LINUX_MT 0
#endif

/*****************************************************************************/
/* Windows/Linux Single threaded Client Support.
 * Set to 1 to support
 */
#ifndef UASDK_INCLUDE_CLIENT_WINDOWS_LINUX_ST
#define UASDK_INCLUDE_CLIENT_WINDOWS_LINUX_ST 0
#endif

/*****************************************************************************/
/* Multi threaded Timers Support.
 * Set to 1 to support
 */
#ifndef UASDK_INCLUDE_TIMERS_CPP11
#define UASDK_INCLUDE_TIMERS_CPP11 0
#endif

/*****************************************************************************/
/** Debug Setting
 * Set this to 1 to enable debug
 */
#ifndef UASDK_DEBUG
#define UASDK_DEBUG 0
#endif

/*****************************************************************************/
/** Debug Sessions setting
 * Set this to 1 to enable debug sessions
 */
#ifndef UASDK_DEBUG_SESSIONS
#define UASDK_DEBUG_SESSIONS 0
#endif

/*****************************************************************************/
/** Debug Channels setting
 * Set this to 1 to enable debug channels
 */
#ifndef UASDK_DEBUG_CHANNELS
#define UASDK_DEBUG_CHANNELS 0
#endif

/*****************************************************************************/
/** Debug Connections
 * Set this to 1 to enable debug connections
 */
#ifndef UASDK_DEBUG_CONNECTIONS
#define UASDK_DEBUG_CONNECTIONS 0
#endif

/*****************************************************************************/
/** Debug Subscriptions
 * Set this to 1 to enable debug subscriptions
 */
#ifndef UASDK_DEBUG_SUBSCRIPTIONS
#define UASDK_DEBUG_SUBSCRIPTIONS 0
#endif

/*****************************************************************************/
/** Debug Messages
 * Set this to 1 to enable debug messages
 */
#ifndef UASDK_DEBUG_MESSAGES
#define UASDK_DEBUG_MESSAGES 0
#endif

/*****************************************************************************/
/** Debug Memory
 * Set this to 1 to debug memory
 */
#ifndef UASDK_DEBUG_MEMORY
#define UASDK_DEBUG_MEMORY 0
#endif

/*****************************************************************************/
/** Maximum data alignment of target
 * Typically set this to 8 unless your platform has a larger requirement
 */
#ifndef UASDK_MAX_ALIGNMENT
#define UASDK_MAX_ALIGNMENT 8
#endif

/*****************************************************************************/
/** Endianess of target
 *  Set to 0 for little endian and 1 for big endian
 */
#ifndef UASDK_BIG_ENDIAN
#define UASDK_BIG_ENDIAN 0
#endif

/*****************************************************************************/
/** Endianess of target floating point unit
 *  Set to 1 for cross endian double or 0 for everything else
 */
#ifndef UASDK_CROSS_ENDIAN_DOUBLE
#define UASDK_CROSS_ENDIAN_DOUBLE 0
#endif

/*****************************************************************************/
/** Some compilers do not allow throw() when exceptions are disabled.
 * Altering this setting may cause hard faults on your platform in low memory
 * conditions. Do not alter without consulting support@matrikonopc.com.
 */
#ifndef UASDK_NO_THROW
#define UASDK_NO_THROW throw()
#endif

 /*****************************************************************************/
 /** Support Subscriptions and Monitored Items
 *  Set to 0 for no support, 1 for support
 */
#ifndef UASDK_INCLUDE_SUBSCRIPTIONS
#define UASDK_INCLUDE_SUBSCRIPTIONS 1
#endif

 /*****************************************************************************/
/** Support security
 *  Set to 0 for no support, 1 for support
 */
#ifndef UASDK_INCLUDE_SECURITY
#define UASDK_INCLUDE_SECURITY 1
#endif

/*****************************************************************************/
/** Support Events
 *  Set to 0 for no support, 1 for support
 */
#ifndef UASDK_INCLUDE_EVENTS
#define UASDK_INCLUDE_EVENTS 0
#endif

/*****************************************************************************/
/** Support Alarms and Conditions
 *  Set to 0 for no support, 1 for support
 *  Ensure that UASDK_INCLUDE_EVENTS is set to 1 before setting this flag to 1
 */
#ifndef UASDK_INCLUDE_ALARMS_AND_CONDITIONS
#define UASDK_INCLUDE_ALARMS_AND_CONDITIONS 0
#endif

/*****************************************************************************/
/** Use OpenSSL security implementation
 *  Set to 0 for no support, 1 for support
 */
#ifndef UASDK_USE_OPENSSL
#define UASDK_USE_OPENSSL 0
#endif

/*****************************************************************************/
/** Use NanoSSL security implementation
 *  Set to 0 for no support, 1 for support
 */
#ifndef UASDK_USE_NANOSSL
#define UASDK_USE_NANOSSL 0
#endif

/*****************************************************************************/
/** Use mbedTLS security implementation
 *  Set to 0 for no support, 1 for support
 */
#ifndef UASDK_USE_MBEDTLS
#define UASDK_USE_MBEDTLS 0
#endif

/*****************************************************************************/
/** Optimise build for speed over memory utilisation
 *  Set to 0 for size, 1 for speed
 */
#ifndef UASDK_OPTIMISE_FOR_SPEED
#define UASDK_OPTIMISE_FOR_SPEED 1
#endif

/*****************************************************************************/
/** Use system heap instead of internal allocator
 *  Set to 0 for internal allocator, 1 for system heap
 */
#ifndef UASDK_USE_SYSTEM_HEAP
#define UASDK_USE_SYSTEM_HEAP 1
#endif

 /*****************************************************************************/
 /** Overlaod new and delete to catch classes not inheriting from Allocatable_t
 *  Set to 1 to overload
 */
#ifndef UASDK_OVERLOAD_NEW_AND_DELETE
#define UASDK_OVERLOAD_NEW_AND_DELETE 0
#endif

 /*****************************************************************************/
/** Include Client functionality
 *  Set to 0 to exclude, 1 to include
 */
#ifndef UASDK_INCLUDE_CLIENT
#define UASDK_INCLUDE_CLIENT 1
#endif

/*****************************************************************************/
/** Include Server functionality
 *  Set to 0 to exclude, 1 to include
 */
#ifndef UASDK_INCLUDE_SERVER
#define UASDK_INCLUDE_SERVER 1
#endif

/*****************************************************************************/
/** Support XML Option
 *  Set to 0 for no support, 1 for support
 */
#ifndef UASDK_INCLUDE_XML_SUPPORT
#define UASDK_INCLUDE_XML_SUPPORT 1
#endif

/*****************************************************************************/
/** Use LIBXML2 for XML option
 *  Set to 0 for no support, 1 for support
 */
#ifndef UASDK_USE_LIBXML2
#define UASDK_USE_LIBXML2 0
#endif

/*****************************************************************************/
/** Use TINYXML2 for XML option
 *  Set to 0 for no support, 1 for support
 */
#ifndef UASDK_USE_TINYXML2
#define UASDK_USE_TINYXML2 1
#endif

 /*****************************************************************************/
 /** Include helper classes to make creating and interacting with Data Access
 *   nodes File object in the address space easier
 *  Set to 0 for no support, 1 for support
 */
#ifndef UASDK_USE_HELPERS
#define UASDK_USE_HELPERS 1
#endif

 /*****************************************************************************/
 /** Include helper classes to make creating and interacting with Data Access
 *   nodes in the address space easier
 *  Set to 0 for no support, 1 for support
 */
#ifndef UASDK_USE_DATA_ACCESS_HELPERS
#define UASDK_USE_DATA_ACCESS_HELPERS 1
#endif

 /*****************************************************************************/
 /** Include helper classes to make creating and interacting with File
 *   nodes in the address space easier
 *  Set to 0 for no support, 1 for support
 */
#ifndef UASDK_USE_FILE_OBJECT_HELPERS
#define UASDK_USE_FILE_OBJECT_HELPERS 0
#endif

#if (UASDK_USE_HELPERS > 0)

/*****************************************************************************/
/** Include Server Diagnostics Summary
*  Set to 0 for no support, 1 for support
*/
#ifndef UASDK_INCLUDE_SERVER_DIAGNOSTICS_SUMMARY
#define UASDK_INCLUDE_SERVER_DIAGNOSTICS_SUMMARY 0
#endif

/*****************************************************************************/
/** Include Subscription Diagnostics
*  Set to 0 for no support, 1 for support
*/
#ifndef UASDK_INCLUDE_SUBSCRIPTION_DIAGNOSTICS
#define UASDK_INCLUDE_SUBSCRIPTION_DIAGNOSTICS 0
#endif

/*****************************************************************************/
/** Include Session Diagnostics
*  Set to 0 for no support, 1 for support
*/
#ifndef UASDK_INCLUDE_SESSION_DIAGNOSTICS
#define UASDK_INCLUDE_SESSION_DIAGNOSTICS 0
#endif

#endif //UASDK_USE_HELPERS

/*****************************************************************************/
/** Include types for method service set. Exclude to reduce code size
*  Set to 0 for no support, 1 for support
*/
#ifndef UASDK_INCLUDE_METHOD_SERVICE_SET
#define UASDK_INCLUDE_METHOD_SERVICE_SET 1
#endif

/*****************************************************************************/
/** Include types for node management service set. Exclude to reduce code size
*  Set to 0 for no support, 1 for support
*/
#ifndef UASDK_INCLUDE_NODE_MANAGEMENT_SERVICE_SET
#define UASDK_INCLUDE_NODE_MANAGEMENT_SERVICE_SET 0
#endif

/*****************************************************************************/
/** Include types for transfer subscriptions service. Exclude to reduce code size
*  Set to 0 for no support, 1 for support
*/
#ifndef UASDK_INCLUDE_TRANSFER_SUBSCRIPTIONS_SERVICE
#define UASDK_INCLUDE_TRANSFER_SUBSCRIPTIONS_SERVICE 0
#endif

/*****************************************************************************/
/** Include types for query service set. Exclude to reduce code size
*  Set to 0 for no support, 1 for support
*/
#ifndef UASDK_INCLUDE_QUERY_SERVICE_SET
#define UASDK_INCLUDE_QUERY_SERVICE_SET 0

#endif

/*****************************************************************************/
/** Include types for history service set. Exclude to reduce code size
*  Set to 0 for no support, 1 for support
*/
#ifndef UASDK_INCLUDE_HISTORY_SERVICE_SET
#define UASDK_INCLUDE_HISTORY_SERVICE_SET 0
#endif

/*****************************************************************************/
/** Include types for additional discovery services. Exclude to reduce code size
*  Set to 0 for no support, 1 for support
*/
#ifndef UASDK_INCLUDE_ADDITIONAL_DISCOVERY_SERVICES
#define UASDK_INCLUDE_ADDITIONAL_DISCOVERY_SERVICES 0
#endif

/*****************************************************************************/
/** Include types for Discover Server Registration.
*  Set to 0 for no support, 1 for support
*/
#ifndef UASDK_INCLUDE_SERVER_REGISTRATION_AGENT
#define UASDK_INCLUDE_SERVER_REGISTRATION_AGENT 0
#endif // !UASDK_INCLUDE_SERVER_REGISTRATION_AGENT

/*****************************************************************************/
/** Include additional DA types. Exclude to reduce code size
*  Set to 0 for no support, 1 for support
*/
#ifndef UASDK_INCLUDE_ADDITIONAL_DA_TYPES
#define UASDK_INCLUDE_ADDITIONAL_DA_TYPES 0
#endif

/*****************************************************************************/
/** Must include methods when subscriptions are selected
*
*/
#if (UASDK_INCLUDE_SUBSCRIPTIONS > 0)
#undef UASDK_INCLUDE_METHOD_SERVICE_SET
#define UASDK_INCLUDE_METHOD_SERVICE_SET 1
#endif

/*****************************************************************************/
/** Include Additional Browse Name String liternals
*  Set to 0 for no support, 1 for support
*/
#ifndef UASDK_INCLUDE_ADDITIONAL_BROWSE_NAMES
#define UASDK_INCLUDE_ADDITIONAL_BROWSE_NAMES 0
#endif

#if ( ((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0)) \
      || (UASDK_INCLUDE_SUBSCRIPTION_DIAGNOSTICS > 0) || (UASDK_INCLUDE_SESSION_DIAGNOSTICS > 0))
#undef UASDK_INCLUDE_ADDITIONAL_BROWSE_NAMES
#define UASDK_INCLUDE_ADDITIONAL_BROWSE_NAMES 1
#endif

 /*****************************************************************************/
 /** Silence UASDK_UNUSED variable compiler warnings
 *  Cast to void for GCC
 */
#ifndef UASDK_UNUSED
#define UASDK_UNUSED(a) (void)a
#endif

 /*****************************************************************************/
 /** Type to use for deadband filter
 *  Can be set to float for Cortex-M4F which only has a single precision FPU
 */
#ifndef UASDK_DEADBAND_DATA_TYPE
#define UASDK_DEADBAND_DATA_TYPE double
#endif

#if (UASDK_INCLUDE_SERVER < 1)
#undef  UASDK_INCLUDE_EVENTS
#undef  UASDK_INCLUDE_ALARMS_AND_CONDITIONS
#define UASDK_INCLUDE_EVENTS   0
#define UASDK_INCLUDE_ALARMS_AND_CONDITIONS   0
#endif

#if (UASDK_INCLUDE_SERVER_REGISTRATION_AGENT > 0)
#if ( (UASDK_INCLUDE_CLIENT == 0) || (UASDK_INCLUDE_SERVER == 0) || (UASDK_INCLUDE_ADDITIONAL_DISCOVERY_SERVICES == 0))
#error IF you want to use the RegistrationAgent_t to register your server to LDS, please enable UASDK_INCLUDE_CLIENT, UASDK_INCLUDE_SERVER and UASDK_INCLUDE_ADDITIONAL_DISCOVERY_SERVICES
#endif
#endif

#if (UASDK_INCLUDE_SERVER_C_API > 0)

// UASDK_INCLUDE_SERVER_C_API is server only and registration to LDS is now limitted.
#if (UASDK_INCLUDE_SERVER == 0)
#error if UASDK_INCLUDE_SERVER_C_API is set to 1, UASDK_INCLUDE_SERVER must be set to 1 too
#endif

#if (UASDK_INCLUDE_CLIENT > 0)
#error if UASDK_INCLUDE_SERVER_C_API is set to 1, WITH_BUILD_CLIENT must NOT be set to 1
#endif

#if (UASDK_INCLUDE_SERVER_REGISTRATION_AGENT > 0)
#error if UASDK_INCLUDE_SERVER_C_API is set to 1, UASDK_INCLUDE_SERVER_REGISTRATION_AGENT must NOT be set to 1
#endif

#endif

#ifndef __cplusplus
 /*****************************************************************************/
 /** Type to use for return bad status
 *
 */
#ifndef UASDK_RETURN_BAD_STATUS
#define UASDK_RETURN_BAD_STATUS(a) return a
#endif

 /*****************************************************************************/
 /** Intrusive pointer NULL check. Return bad and unexpected status if null
 *
 */
#ifndef UASDK_RETURN_UNEXPECTED_IF_NULL
#define UASDK_RETURN_UNEXPECTED_IF_NULL(a) if (!a.is_set()) { UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError); }
#endif

 /*****************************************************************************/
 /** Intrusive pointer NULL check. Return if null
 *
 */
#ifndef UASDK_RETURN_IF_NULL
#define UASDK_RETURN_IF_NULL(a) if (!a.is_set()) { return; }
#endif

/** @} */

#endif //!__cplusplus

#ifdef __cplusplus
}
#endif

#endif /*_UASDK_DEFAULT_BUILD_CONFIG_*/
