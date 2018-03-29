/** @file */

/*****************************************************************************/
/** \file ua_server_config_template.h
 *  \brief Template configuration for the OPC-UA Embedded Server SDK.
 *
 */

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

/** \addtogroup grpServerConfig
*@{*/

#ifndef UA_SERVER_BUILD_CONFIG_H_
#define UA_SERVER_BUILD_CONFIG_H_

/*****************************************************************************/
/** SDK License description (Do not change)
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
/** Some compilers do not allow throw() when exceptions are disabled.
 * Altering this setting may cause hard faults on your platform in low memory
 * conditions. Do not alter without consulting support@matrikonopc.com.
 */
#ifndef UA_NO_THROW
#define UA_NO_THROW throw()
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
/** Use NanoSSL security implementation
 *  Set to 0 for no support, 1 for support
 */
#ifndef UA_USE_NANOSSL
#define UA_USE_NANOSSL 0
#endif

/*****************************************************************************/
/** Use mBedTLS security implementation
 *  Set to 0 for no support, 1 for support
 */
#ifndef UA_USE_MBEDTLS
#define UA_USE_MBEDTLS 0
#endif

/*****************************************************************************/
/** Generated Certificate key length. Only used when security is included
 *  Set to 1024 or 2048 bits
 */
#ifndef APPLICATION_RSA_KEY_LENGTH
#define APPLICATION_RSA_KEY_LENGTH 1024
#endif

 /*****************************************************************************/
 /** Security directory store path. Set this to pki path e.g "C:\\MatrikonOPCUA"
  */
#ifndef SECURITY_CERTIFICATE_DIRECTORY_STORE_PATH
#define SECURITY_CERTIFICATE_DIRECTORY_STORE_PATH "."
#endif

/*****************************************************************************/
/** Support file transfer methods
 *  Set to 0 for no support, 1 for support
 */
#ifndef UA_INCLUDE_FILE_TRANSFER_METHODS
#define UA_INCLUDE_FILE_TRANSFER_METHODS 0
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
#define UA_OPTIMISE_FOR_SPEED 1
#endif

/*****************************************************************************/
/** Floating point data type to use for deadband calculations
 *  Set to float for architectures without a double precision hardware FPU
 *  where the reduction in precision is acceptable for your application
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
