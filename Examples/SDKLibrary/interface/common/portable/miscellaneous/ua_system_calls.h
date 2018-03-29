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

/*****************************************************************************/
/* Copyright (c) 2015 MatrikonOPC.
 *
 * ALL RIGHTS RESERVED.
 *
 * The information contained herein is the confidential and proprietary product
 * of MatrikonOPC.  Any unauthorized use, reproduction or
 * transfer of this information is strictly prohibited.
 */

#ifndef _UA_SYSTEM_CALLS_H_
#define _UA_SYSTEM_CALLS_H_

/*****************************************************************************/
/* Include Files
 */
#include <stddef.h>
#include <stdint.h>

#define EPOCH_DIFF 11644473600LL // number of seconds from 1 Jan. 1601 00:00 to 1 Jan 1970 00:00 UTC is 11644473600

#ifdef __cplusplus
extern "C"
{
#endif

/*****************************************************************************/
/** Function provided by host to enable library to time its internal operations
 *
 * The library requires a millisecond timer in order to operate. This timer is
 * implemented via a uint32_t which increments every millisecond. The host must
 * implement this function as it is called periodically by the stack.
 *
 * @return
 * A counter that increments every millisecond.
 */
uint32_t UASDK_millisecond(void);

/*****************************************************************************/
/** Function provided by host to enable library to obtain current date and time
 *
 * The library requires the current date and time in order to operate. This timer
 * is implemented via an int64_t which represents UTC time and data in
 * accordance with Windows FILETIME. This is the number of 100ns intervals
 * since January 1, 1601. The host must implement this function as it is called
 * periodically by the library.
 *
 * @return
 * Current date and time.
 */
int64_t UASDK_datetime(void);

/*****************************************************************************/
/** Function provided by host to provide pseudo-random numbers
 *
 * The library requires a pseudo-random number generator in order to operate.
 * The host must implement this function as it is called periodically by the
 * library.
 *
 * @return
 * A pseudo-random number.
 */
uint32_t UASDK_pseudeo_random_number(void);

/*****************************************************************************/
/** Function provided by host to provide a memcpy implementation
 *
 * Some platforms can dramatically improve the performance of memcpy for
 * large data blocks by using DMA or other techniques. If required, a custom
 * implementation may be inserted here. Where a custom implementation is not required
 * simply call the standard library implementation.
 *
 * @param[in] destination
 * Pointer to the destination array where the content is to be copied, type-casted
 * to a pointer of type void*.
 *
 * @param[in] source
 * Pointer to the source of data to be copied, type-casted to a pointer of type
 * const void*.
 *
 * @param[in] num
 * Number of bytes to copy. size_t is an unsigned integral type.
 *
 * @return
 * "destination" is returned.
 */
void* UASDK_memcpy(void * destination, const void * source, size_t num);

/*****************************************************************************/
/** Function provided by host to provide a memchr implementation
 *
 * Simply call the standard library implementation.
 *
 * @param[in] ptr
 * Pointer to the block of memory where the search is performed.
 *
 * @param[in] value
 * Value to be located. The value is passed as an int, but the function performs
 * a byte per byte search using the unsigned char conversion of this value.
 *
 * @param[in] num
 * Number of bytes to be analyzed. size_t is an unsigned integral type.
 *
 * @return
 * A pointer to the first occurrence of value in the block of memory pointed
 * by ptr. If the value is not found, the function returns a null pointer.
 */
const void* UASDK_memchr(const void* ptr, int32_t value, size_t num);

/*****************************************************************************/
/** Function provided by host to provide a memset implementation
 *
 * Simply call the standard library implementation.
 *
 * @param[in] ptr
 * Pointer to the block of memory to fill.
 *
 * @param[in] value
 * Value to be set. The value is passed as an int, but the function fills the
 * block of memory using the unsigned char conversion of this value.
 *
 * @param[in] num
 * Number of bytes to be set to the value. size_t is an unsigned integral type.
 *
 * @return
 * "ptr" is returned.
 */
void* UASDK_memset(void * ptr, int32_t value, size_t num);

/*****************************************************************************/
/** Function provided by host to provide a memcmp implementation
 *
 * Simply call the standard library implementation.
 *
 * @param[in] ptr1
 * Pointer to block of memory.
 *
 * @param[in] ptr2
 * Pointer to block of memory.
 *
 * @param[in] num
 * Number of bytes to compare.
 *
 * @return
 * Returns an integral value indicating the relationship between the content
 * of the memory blocks:
 * A zero value indicates that the contents of both memory blocks are equal.
 * A value greater than zero indicates that the first byte that does not match
 * in both memory blocks has a greater value in ptr1 than in ptr2 as if evaluated
 * as unsigned char values; And a value less than zero indicates the opposite.
 */
int UASDK_memcmp(const void * ptr1, const void * ptr2, size_t num);

/*****************************************************************************/
/** Function provided by host to provide a strncpy implementation
 *
 * Simply call the standard library implementation.
 *
 * @param[in] destination
 * Pointer to the destination array where the content is to be copied.
 *
 * @param[in] source
 * C string to be copied.
 *
 * @param[in] num
 * Maximum number of characters to be copied from source.
 * size_t is an unsigned integral type.
 *
 * @return
 * destination is returned.
 */
char* UASDK_strncpy(char *destination, const char *source, size_t num);

/*****************************************************************************/
/** Function provided by host to provide a strncat implementation
 *
 * Simply call the standard library implementation.
 *
 * @param[in] destination
 * Pointer to the destination array where the content is to be copied.
 *
 * @param[in] destBufSize
 * Specify the destination buffer size
 *
 * @param[in] source
 * C string to be copied.
 *
 * @param[in] num
 * Number of characters to be copied from source.
 * size_t is an unsigned integral type.
 *
 * @return
 * destination is returned.
 */
char* UASDK_strncat(char* destination, size_t destBufSize, const char* source, size_t num);

/*****************************************************************************/
/** Function provided by host to provide a strstr implementation
 *
 * Simply call the standard library implementation.
 *
 * @param[in] str1
 * Pointer to the str in which to search.
 *
 * @param[in] str2
 * Pointer to the str to find
 *
 * @return
 * The first occurance of str2 or else null.
 */
char * UASDK_strstr (char * str1, const char * str2 );

/*****************************************************************************/
/** function used to compare two strings
 *
 * @param[in] string1
 * the first string of two strings to compare
 *
 * @param[in] string2
 * the second string of two strings to compare
 *
 * @return
 * 0 if both strings are equal, non-zero otherwise.
 */
int UASDK_strcmp(const char* string1, const char* string2);

/*****************************************************************************/
/** Function provided by host to provide String to double implementation
 *
 * Simply call the standard library implementation.
 * Note: Out of range values handling is dependent on the library function used and platform
 *
 * @param[in] str
 * Pointer to the string which has to be converted to double
 *
 * @param[out] endptr
 * Pointer to the character past the last character interpreted
 *
 * @return
 * converted double value.
 */
double UASDK_strtod(const char* str, char** endptr);

/*****************************************************************************/
/** Function provided by host to provide String to float implementation
 *
 * Simply call the standard library implementation.
 * Note: Out of range values handling is dependent on the library function used and platform
 *
 * @param[in] str
 * Pointer to the string which has to be converted to double
 *
 * @param[out] endptr
 * Pointer to the character past the last character interpreted
 *
 * @return
 * converted float value.
 */
float UASDK_strtof(const char* str, char** endptr);

/*****************************************************************************/
/** Function provided by host to provide String to long long integer implementation
 *
 * Simply call the standard library implementation.
 * Note: Out of range values handling is dependent on the library function used and platform
 *
 * @param[in] str
 * Pointer to the string which has to be converted to long long (int64_t)
 *
 * @param[out] endptr
 * Pointer to the character past the last character interpreted
 *
 * @param[in] base
 * Numerical base (radix)
 *
 * @return
 * converted int64_t value.
 */
int64_t UASDK_strtoll(const char* str, char** endptr, int base);

/*****************************************************************************/
/** Function provided by host to provide String to unsigned long long integer implementation
 *
 * Simply call the standard library implementation.
 * Note: Out of range values handling is dependent on the library function used and platform
 *
 * @param[in] str
 * Pointer to the string which has to be converted to double
 *
 * @param[out] endptr
 * Pointer to the character past the last character interpreted
 *
 * @param[in] base
 * Numerical base (radix)
 *
 * @return
 * converted float value.
 */
uint64_t UASDK_strtoull(const char* str, char** endptr, int base);

/*****************************************************************************/
/** Function provided by host to provide a Double to String implementation
 *
 * @param[in] value
 * Value which has to be converted to String
 *
 * @param[in] precision
 * Number of digits after the decimal point
 *
 * @param[out] str
 * String where the converted number has to be stored
 *
 * @param[in] maxStrLen
 * Maximum length of the string
 *
 * @return
 * converted length of the converted Value.
 *
 * Note: If there is any error, this function will return -1
 */
int32_t UASDK_double_to_string(double value, uint32_t precision, char* str, int maxStrLen);

/*****************************************************************************/
/** Function provided by host to provide a Float to String implementation
 *
 * @param[in] value
 * Value which has to be converted to String
 *
 * @param[in] precision
 * Number of digits after the decimal point
 *
 * @param[out] str
 * String where the converted number has to be stored
 *
 * @param[in] maxStrLen
 * Maximum length of the string
 *
 * @return
 * converted length of the converted Value.
 *
 * Note: If there is any error, this function will return -1
 */
int32_t UASDK_float_to_string(float value, uint32_t precision, char* str, int maxStrLen);

/*****************************************************************************/
/** Function provided by host to provide a Signed Integer to String implementation
 *
 * @param[in] value
 * Value which has to be converted to String
 *
 * @param[in] precision
 * Minimum number of digits
 *
 * @param[out] str
 * String where the converted number has to be stored
 *
 * @param[in] maxStrLen
 * Maximum length of the string
 *
 * @return
 * converted length of the converted Value.
 *
 * Note: If there is any error, this function will return -1
 */
int32_t UASDK_signed_integer_to_string(int64_t value, uint32_t precision, char* str, int maxStrLen);

/*****************************************************************************/
/** Function provided by host to provide a Unsigned Integer to String implementation
 *
 * @param[in] value
 * Value which has to be converted to String
 *
 * @param[in] precision
 * Minimum number of digits
 *
 * @param[out] str
 * String where the converted number has to be stored
 *
 * @param[in] maxStrLen
 * Maximum length of the string
 *
 * @return
 * converted length of the converted Value.
 *
 * Note: If there is any error, this function will return -1
 */
int32_t UASDK_unsigned_integer_to_string(uint64_t value, uint32_t precision, char* str, int maxStrLen);

/*****************************************************************************/
/** Function provided by host to provide a Unsigned Integer to Hex String implementation
 *  with the base 16 instead of base 10 in the UASDK_signed_integer_to_string() function.
 *
 * @param[in] value
 * Value which has to be converted to String
 *
 * @param[in] precision
 * Minimum number of digits
 *
 * @param[out] str
 * String where the converted number has to be stored
 *
 * @param[in] maxStrLen
 * Maximum length of the string
 *
 * @return
 * converted length of the converted Value.
 *
 * Note: If there is any error, this function will return -1
 */
int32_t UASDK_unsigned_integer_to_hex_string(uint64_t value, uint32_t precision, char* str, int maxStrLen);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /*_UA_SYSTEM_CALLS_H_*/
