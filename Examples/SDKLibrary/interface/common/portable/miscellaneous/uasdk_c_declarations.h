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

#ifndef _UASDK_C_DECLARATIONS_
#define _UASDK_C_DECLARATIONS_

/*****************************************************************************/
/* Include Files
*/

#include "uasdk_default_build_config.h"

#include <stddef.h>

#if (UASDK_USE_SYSTEM_HEAP > 0)
#include <stdint.h>
#include <stdlib.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/*****************************************************************************/
/* Defines Macros Types
 */

/** \addtogroup grpCTypes
 *@{*/

/*****************************************************************************/
/** \brief Represents an OPC-UA status code
 *
 * OPC-UA status codes are defined in opcua_status_codes.h
 */
typedef uint32_t UA_Status_t;

/*****************************************************************************/
/** \brief Represents an OPC-UA DateTime
 *
 */
typedef int64_t UA_DateTime_t;

/*****************************************************************************/
/** \brief Enumeration of message security policies
 *
 */
typedef enum
{
  SECURITY_POLICY_INVALID, /**< Invalid */
  SECURITY_POLICY_NONE, /**< No security */
  SECURITY_POLICY_BASIC128RSA15, /**< SecurityPolicyBasic128Rsa15 */
  SECURITY_POLICY_BASIC256, /**< SecurityPolicyBasic256 */
  SECURITY_POLICY_BASIC256SHA256 /**< SecurityPolicyBasic256Sha256 */
} SecurityPolicy_t;

/*****************************************************************************/
/** \brief Enumeration of Certificate Groups
 *
 */
typedef enum
{
  UA_CERTIFICATE_GROUP_INVALID = 0,   /**< Invalid */
  UA_CERTIFICATE_GROUP_DEFAULT_APPLICATION_GROUP = 1,   /**< Application */
  UA_CERTIFICATE_GROUP_DEFAULT_HTTPS_GROUP = 2,   /**< HTTPS */
  UA_CERTIFICATE_GROUP_DEFAULT_USER_GROUP = 3   /**< User */
} UA_CertificateGroup_t;

/*****************************************************************************/
/** \brief Enumeration of Certificate Types
 *
 */
typedef enum
{
  UA_CERTIFICATE_TYPE_INVALID = 0,   /**< Invalid */
  UA_CERTIFICATE_TYPE_APPLICATION_TYPE = 1,   /**< Application Type */
  UA_CERTIFICATE_TYPE_RSA_MIN_APPLICATION_TYPE = 2,   /**< RSA Min */
  UA_CERTIFICATE_TYPE_RSA_SHA_256_APPLICATION_TYPE = 3,   /**< RSA SHA 256 */
  UA_CERTIFICATE_TYPE_HTTPS_TYPE = 4   /**< HTTPS */
} UA_CertificateType_t;

/*****************************************************************************/
/** bool is not portable so define our own boolean type for the API
 *
 */
#define bool_t int
#ifndef TRUE
#define TRUE 1    /**< bool_t true value */
#endif
#ifndef FALSE
#define FALSE 0   /**< bool_t false value */
#endif
/*****************************************************************************/
/** \brief Represents a UTF8 string for translation of human readable text
 *
 * A UTF8 string is a multi byte character string that supports localization.
 * Where it is required to represent an ASCII C style string using this data
 * structure the length field is the number of characters excluding the 0
 * terminator and the data pointer is a cast pointer to the C style string.
 */
typedef struct
{
  int32_t length;       /**< Length of the byte array */
  const uint8_t* data;  /**< Pointer to the byte array containing characters */
} UA_UTF8_string_t;

/*****************************************************************************/
/** \brief Represents a variable length byte string
 *
 * This structure is used for representing data values containing byte array,
 * string and XML element data types. The additional max_length element is
 * included to inform the stack of the maximum length of the allocated storage
 * to facilitate value write operations by the stack.
 */
typedef struct
{
  int32_t length;     /**< Current length of the byte array */
  int32_t max_length; /**< Maximum length of the byte array */
  uint8_t* data;      /**< Pointer to the byte array */
} UA_Byte_string_t;

/*****************************************************************************/
/** \brief A structure representing UTF8 string values.
 *
 */
typedef UA_Byte_string_t UA_Var_string_t;

/** @} */

/*****************************************************************************/
/** Allocate a block of memory from the SDK memory allocation subsystem
 *
 * If the application needs to perform dynamic memory allocation it can use the
 * SDK memory allocation subsystem rather than a general purpose heap (which in
 * any case may not be available). The allocation must be less than
 * UA_Configuration_Internals_t::MAX_ALLOCATION_SIZE_IN_BYTES specified in the
 * runtime configuration (typically by 8 bytes).
 *
 * @param[in] size
 * The size in bytes of the required block of memory.
 *
 * @return  A pointer to the allocated memory or NULL (0) on failure.
 */
void* UASDK_Malloc(size_t size);

/*****************************************************************************/
/** Allocate a block of memory from the SDK memory allocation subsystem
 * and zero the block. The allocation must be less than
 * UA_Configuration_Internals_t::MAX_ALLOCATION_SIZE_IN_BYTES specified in the
 * runtime configuration (typically by 8 bytes).
 *
 * @param[in] size
 * The size in bytes of the required block of memory.
 *
 * @return  A pointer to the allocated memory or NULL (0) on failure.
 */
void* UASDK_Calloc(size_t size);

/*****************************************************************************/
/** Increase or decrease the size of a previously allocated block of memory
 * from the SDK memory allocation subsystem. The allocation must be less than
 * UA_Configuration_Internals_t::MAX_ALLOCATION_SIZE_IN_BYTES specified in the
 * runtime configuration (typically by 8 bytes).
 *
 * @param[in] ptr
 * A pointer previously returned by one of the memory allocation routines.
 *
 * @param[in] size
 * The size in bytes of the required block of memory.
 *
 * @return  A pointer to the allocated memory or NULL (0) on failure.
 */
void* UASDK_Realloc(void* ptr, size_t size);

/*****************************************************************************/
/** Free a memory block previously allocated with UAServer_Malloc(),
 * UAServer_Calloc() or UAServer_Realloc().
 *
 * @param[in] ptr
 * The pointer previously returned by one of the memory allocation routines.
 *
 */
void UASDK_Free(void* ptr);


#ifdef __cplusplus
} // extern "C"
#endif

#endif /*_UASDK_C_DECLARATIONS_*/
