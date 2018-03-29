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

#ifndef UASDK_INCLUDES_H_
#define UASDK_INCLUDES_H_

#include "uasdk_default_build_config.h"
#include "uasdk_c_declarations.h"
#include "ua_system_calls.h"

#ifdef __cplusplus
#include "status_t.h"
#endif

#define UASDK_SOFTWARE_VERSION "Matrikon Flex OPC UA SDK R400.1"

#define DEFAULT_SMART_BUFFER_BLOCK_SIZE_IN_BYTES 490

#ifndef UA_VALGRIND
#define VALGRIND_MAKE_MEM_DEFINED(a, b)
#endif

/* Endian conversion for 16 and 32 bit values */

#if (UASDK_BIG_ENDIAN != 0)

#define host_to_uabinary_16(A)  ( \
  (((uint16_t)(A) & (uint16_t)0xff00) >> 8) | \
  (((uint16_t)(A) & (uint16_t)0x00ff) << 8))

#define host_to_uabinary_32(A)  ( \
  (((uint32_t)(A) & (uint32_t)0xff000000) >> 24) | \
  (((uint32_t)(A) & (uint32_t)0x00ff0000) >> 8)  | \
  (((uint32_t)(A) & (uint32_t)0x0000ff00) << 8)  | \
  (((uint32_t)(A) & (uint32_t)0x000000ff) << 24))

#define uabinary_16_to_host   host_to_uabinary_16
#define uabinary_32_to_host   host_to_uabinary_32

#else //UASDK_BIG_ENDIAN

#define host_to_uabinary_16(A) (A)
#define host_to_uabinary_32(A) (A)

#define uabinary_16_to_host(A) (A)
#define uabinary_32_to_host(A) (A)

#endif //UASDK_BIG_ENDIAN

#if (UASDK_USE_SYSTEM_HEAP == 0)
#if (INTPTR_MAX == INT64_MAX)
#error Allocator cannot be used on 64 bit platforms
#endif
#endif

#ifdef __cplusplus
#include "logger_t.h"
#endif

/*****************************************************************************/
/** Type to use for return bad status
*
*/
#ifndef UASDK_RETURN_BAD_STATUS
#if (UASDK_DEBUG > 0)
#define UASDK_RETURN_BAD_STATUS(a) LOG_BAD_STATUS(a); return a
#else
#define UASDK_RETURN_BAD_STATUS(a) return a
#endif
#endif

/*****************************************************************************/
/** Type to use for check and return status only if status is bad
*
*/
#ifndef UASDK_RETURN_STATUS_ONLY_IF_BAD
#define UASDK_RETURN_STATUS_ONLY_IF_BAD(a) if( (a & (1<<31)) != 0) { UASDK_RETURN_BAD_STATUS(a); }
#endif

/*****************************************************************************/
/** Type to use for check and return only if status is bad
*
*/
#ifndef UASDK_RETURN_IF_BAD
#if (UASDK_DEBUG > 0)
#define UASDK_RETURN_IF_BAD(a) if( (a & (1<<31)) != 0) { LOG_BAD_STATUS(a); return; }
#else
#define UASDK_RETURN_IF_BAD(a)  if( (a & (1<<31)) != 0) { return; }
#endif
#endif

/*****************************************************************************/
/** Intrusive pointer NULL check. Return bad and unexpected status if null
*
*/
#ifndef UASDK_RETURN_UNEXPECTED_IF_NULL
#define UASDK_RETURN_UNEXPECTED_IF_NULL(a) if (!a.is_set()) { UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError); }
#endif

/*****************************************************************************/
/** Intrusive pointer NULL check. Return bad and invalid argument status if null
*
*/
#ifndef UASDK_RETURN_INVALID_ARGUMENT_IF_NULL
#define UASDK_RETURN_INVALID_ARGUMENT_IF_NULL(a) if (!a.is_set()) { UASDK_RETURN_BAD_STATUS(OpcUa_BadInvalidArgument); }
#endif

/*****************************************************************************/
/** Intrusive pointer NULL check. Return bad and outofmemory status if null
*
*/
#ifndef UASDK_RETURN_OUT_OF_MEMORY_IF_NULL
#define UASDK_RETURN_OUT_OF_MEMORY_IF_NULL(a) if (!a.is_set()) { UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory); }
#endif

/*****************************************************************************/
/** Intrusive pointer NULL check. Return if null
*
*/
#ifndef UASDK_RETURN_IF_NULL
#define UASDK_RETURN_IF_NULL(a) if (!a.is_set()) { LOG_ERROR("Null pointer was unexpected"); return; }
#endif

#if (UASDK_DEBUG != 0)
#if defined(WIN32)
#include <crtdbg.h>
#define UASDK_ASSERT(a) if(!(a)) { _CrtDbgBreak(); while(1);}
#elif defined(LINUX)
#include <signal.h>
#define UASDK_ASSERT(a) if(!(a)) { raise(SIGABRT); while(1);}
#else
#define UASDK_ASSERT(a) if (!(a)) { while (1) ; }
#endif
#else //(UASDK_DEBUG != 0)
#define UASDK_ASSERT(a)
#endif //(UASDK_DEBUG != 0)


#endif /* UASDK_INCLUDES_H_ */
