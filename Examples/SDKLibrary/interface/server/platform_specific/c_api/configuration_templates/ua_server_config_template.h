/** @file */

/*****************************************************************************/
/** \file ua_server_config_template.h
 *  \brief Template configuration for the OPC-UA Embedded Server SDK.
 *
 */

/* Copyright (c) 2009 - 2013 MatrikonOPC. All Rights Reserved */

/** \addtogroup grpBuild
*@{*/

#ifndef UA_SERVER_BUILD_CONFIG_H_
#define UA_SERVER_BUILD_CONFIG_H_

/*****************************************************************************/
/** Maximum data alignment of target
 * Typically set this to 8 unless your platform has a larger requirement
 */
#ifndef UA_MAX_ALIGNMENT
#define UA_MAX_ALIGNMENT 8
#endif

/*****************************************************************************/
/** Endianess of target
 *  Set to 0 for little endian and 1 for big endian
 */
#ifndef UA_BIG_ENDIAN
#define UA_BIG_ENDIAN 0
#endif

/*****************************************************************************/
/** Endianess of target floating point unit
 *  Set to 1 for cross endian double or 0 for everything else
 */
#ifndef UA_CROSS_ENDIAN_DOUBLE
#define UA_CROSS_ENDIAN_DOUBLE 0
#endif

/*****************************************************************************/
/** Support Subscriptions and Monitored Items
 *  Set to 0 for no support, 1 for support
 */
#ifndef UA_INCLUDE_SUBSCRIPTIONS
#define UA_INCLUDE_SUBSCRIPTIONS 1
#endif

/*****************************************************************************/
/** Support Monitored Item Triggering
 *  Set to 0 for no support, 1 for support
 */
#ifndef UA_INCLUDE_MON_ITEM_TRIGGERING
#define UA_INCLUDE_MON_ITEM_TRIGGERING 1
#endif

/*****************************************************************************/
/** Include standard type information in address space
 *  Set to 0 to omit, 1 to include
 */
#ifndef UA_INCLUDE_STANDARD_ADDRESS_SPACE
#define UA_INCLUDE_STANDARD_ADDRESS_SPACE 1
#endif

/*****************************************************************************/
/** Include empty implementations of new and delete
 *  Set to 0 to omit, 1 to include
 */
#ifndef UA_OVERLOAD_NEW_AND_DELETE
#define UA_OVERLOAD_NEW_AND_DELETE 0
#endif

/*****************************************************************************/
/** Include C++ standard library dependencies
 *  Set to 0 to omit, 1 to include
 */
#ifndef UA_INCLUDE_CPP_STD_LIB_DEPS
#define UA_INCLUDE_CPP_STD_LIB_DEPS 0
#endif

/*****************************************************************************/
/** Some compilers do not allow throw() when exceptions are disabled.
 * Altering this setting may cause hard faults on your platform in low memory
 * conditions. Do not alter without consulting support@matrikonopc.com.
 */
#ifndef UA_NO_THROW
#define UA_NO_THROW throw()
#endif

/*****************************************************************************/
/** Support placement of standard nodes in a specific data section
 *  Leave empty for default linker behaviour
 */
#ifndef UA_STANDARD_NODES_SECTION_ATTRIBUTE_PREFIX
#define UA_STANDARD_NODES_SECTION_ATTRIBUTE_PREFIX
#endif

/*****************************************************************************/
/** Support placement of standard nodes in a specific data section
 *  Leave empty for default linker behaviour
 */
#ifndef UA_STANDARD_NODES_SECTION_ATTRIBUTE_POSTFIX
#define UA_STANDARD_NODES_SECTION_ATTRIBUTE_POSTFIX
#endif

/*****************************************************************************/
/** Support application defined Node Ids (string or GUID types)
 *  Set to 0 for no support, 1 for support
 */
#ifndef UA_INCLUDE_APP_DEFINED_NODE_IDS
#define UA_INCLUDE_APP_DEFINED_NODE_IDS 0
#endif

/*****************************************************************************/
/** Support security
 *  Set to 0 for no support, 1 for support
 */
#ifndef UA_INCLUDE_SECURITY
#define UA_INCLUDE_SECURITY 0
#endif

/*****************************************************************************/
/** Use OpenSSL security implementation
 *  Set to 0 for no support, 1 for support
 */
#ifndef UA_USE_OPENSSL
#define UA_USE_OPENSSL 0
#endif

/*****************************************************************************/
/** Use MatrixSSL security implementation
 *  Set to 0 for no support, 1 for support
 */
#ifndef UA_USE_MATRIXSSL
#define UA_USE_MATRIXSSL 0
#endif

/*****************************************************************************/
/** Support SecurityPolicy Basic 256 with MatrixSSL. This feature requires
 * MatrixSSL components not included in the openly available GPL version.
 * While testing MatrixSSL in advance of a purchase set this macro to 0 to
 * enable compilation.
 * Set to 0 for no support, 1 for support
 */
#ifndef UA_MATRIXSSL_SUPPORT_SECURITY_POLICY_BASIC256
#define UA_MATRIXSSL_SUPPORT_SECURITY_POLICY_BASIC256 0
#endif

/*****************************************************************************/
/** Support MatrixSSL certificate generation. This feature requires MatrixSSL
 * components not included in the openly available GPL version. While testing
 * MatrixSSL in advance of a purchase set this macro to 0 to enable
 * compilation.
 *  Set to 0 for no support, 1 for support
 */
#ifndef UA_MATRIXSSL_SUPPORT_CERTIFICATE_GENERATION
#define UA_MATRIXSSL_SUPPORT_CERTIFICATE_GENERATION 0
#endif

/*****************************************************************************/
/** Generated Certificate key length. Only used when security is included
 *  Set to 1024 or 2048 bits
 */
#ifndef APPLICATION_RSA_KEY_LENGTH
#define APPLICATION_RSA_KEY_LENGTH 1024
#endif

/*****************************************************************************/
/** Support file transfer methods
 *  Set to 0 for no support, 1 for support
 */
#ifndef UA_INCLUDE_FILE_TRANSFER_METHODS
#define UA_INCLUDE_FILE_TRANSFER_METHODS 0
#endif

/*****************************************************************************/
/** Support deferral of read operations
 *  Set to 0 for no support, 1 for support
 */
#ifndef UA_INCLUDE_READ_DEFERRALS
#define UA_INCLUDE_READ_DEFERRALS 0
#endif

/*****************************************************************************/
/** Support asynchronous operations
 *  Set to 0 for no support, 1 for support
 */
#ifndef UA_INCLUDE_ASYNC_OPS
#define UA_INCLUDE_ASYNC_OPS 0
#endif

/*****************************************************************************/
/** If including asynchronous operations define the platform mutex type here.
 * Otherwise just set it to void.
 */
#ifndef UA_MUTEX_T
#define UA_MUTEX_T void
#endif

/*****************************************************************************/
/** Allow user certificates with no signing (major security risk)
 *  Set to 0 for no support, 1 for support
 */
#ifndef ALLOW_USER_TOKEN_POLICY_X509v3_CERTIFICATE_TOKEN_SECURITY_POLICY_NONE
#define ALLOW_USER_TOKEN_POLICY_X509v3_CERTIFICATE_TOKEN_SECURITY_POLICY_NONE 0
#endif

/*****************************************************************************/
/** Optimise build for speed over memory utilisation
 *  Set to 0 for size, 1 for speed
 */
#ifndef UA_OPTIMISE_FOR_SPEED
#define UA_OPTIMISE_FOR_SPEED 0
#endif

/*****************************************************************************/
/** Floating point data type to use for deadband calculations
 *  Set to float for architectures without a double precision hardware FPU
 *  where the reduction in precision is acceptable for your application.
 *  For ARM Cortex-M4F and GCC use compile option -fsingle-precision-constant
 *  to optimise performance
 */
#ifndef UA_DEADBAND_DATA_TYPE_T
#define UA_DEADBAND_DATA_TYPE_T double
#endif

/*****************************************************************************/
/** \brief The configuration for the UA Server BuildInfo object
 *
 */
/** Product URI for BuildInfo Standard Node */
#define UA_PRODUCT_URI "PRODUCT_URI"
/** Product name for BuildInfo Standard Node */
#define UA_PRODUCT_NAME "PRODUCT_NAME"
/** Manufacturer name for BuildInfo Standard Node */
#define UA_MANUFACTURER_NAME "MANUFACTURER_NAME"
/** Software version for BuildInfo Standard Node */
#define UA_SOFTWARE_VERSION "SOFTWARE_VERSION"
/** Build number for BuildInfo Standard Node */
#define UA_BUILD_NUMBER "BUILD_NUMBER"
/** Build date (Windows FileTime format) for BuildInfo Standard Node */
#define UA_BUILD_DATE 0

/*@}*/

#endif /* UA_SERVER_BUILD_CONFIG_H_ */
