/* ----------------------------------------------------------------------------------------
                                        COPYRIGHT (c) 2009 - 2017
                                         HONEYWELL INC.,
                                        ALL RIGHTS RESERVED

            This software is a copyrighted work and/or information protected as a trade
            secret. Legal rights of Honeywell Inc. in this software are distinct from
            ownership of any medium in which the software is embodied. Copyright or trade
            secret notices included must be reproduced in any copies authorized by
            Honeywell Inc. The information in this software is subject to change without
            notice and should not be considered as a commitment by Honeywell Inc.
---------------------------------------------------------------------------------------- */

#include "uasdk_includes.h"

#if (UASDK_INCLUDE_LIBRARY_C_API > 0)

#include <stdint.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include "allocatable_t.h"
#include "ua_server.h"

#ifdef _WIN32 
#include <Windows.h>
#else
#include <sys/time.h>
#endif

extern "C" {

/*****************************************************************************/
/** function used to generate Random number
 *
 * @return
 * generated Random number
 */
uint32_t UASDK_pseudeo_random_number(void)
{
  return UAServer_Callback_pseudeo_random_number();
}

/*****************************************************************************/
/** function used to Copy the data from one memory location to another
 *
 * @param[in] destination
 * address of the location where data to be copied
 *
 * @param[in] source
 * address of the location from where data to be copied
 *
 * @param[in] num
 * number of bytes to be copied
 *
 * @return
 * pointer to the destination
 */
void* UASDK_memcpy(void * destination, const void * source, size_t num)
{
  return UAServer_Callback_memcpy(destination, source, num);
}

/*****************************************************************************/
/** function used to find the character in the block of memory
 *
 * @param[in] ptr
 * address of the location in which value has to be found
 *
 * @param[in] value
 * value to be found in the block of memory
 *
 * @param[in] num
 * number of bytes in the memory block where value to be found
 *
 * @return
 * first occurrence of the value
 */
const void* UASDK_memchr(const void* ptr, int32_t value, size_t num)
{
  return UAServer_Callback_memchr(ptr, value, num);
}

/*****************************************************************************/
/** function used to set the memory buffer with specific value
 *
 * @param[in] ptr
 * address of the memory location which need to be set with given value
 *
 * @param[in] value
 * value to be set with
 *
 * @param[in] num
 * number of bytes to be set with value
 *
 * @return
 * pointer to the memory buffer which was set with value
 */
void* UASDK_memset(void * ptr, int32_t value, size_t num)
{
  return UAServer_Callback_memset(ptr, value, num);
}

/*****************************************************************************/
/** function used to compare two memory location.
 *
 * @param[in] ptr1
 * pointer to the memory location 1
 *
 * @param[in] ptr2
 * pointer to the memory location 2
 *
 * @param[in] num
 * number of bytes to be compared
 *
 * @return
 * 0 if two memory locations are equal
 * > 0, if first character ptr1 is greater than ptr2
 * < 0, if first character ptr2 is greater than ptr1
 */
int UASDK_memcmp(const void * ptr1, const void * ptr2, size_t num)
{
  return UAServer_Callback_memcmp(ptr1, ptr2, num);
}

/*****************************************************************************/
/** Function used to get the current time in milliseconds
 *
 * @return
 * current time in milliseconds.
 */
uint32_t UASDK_millisecond(void)
{
  return UAServer_Callback_millisecond();
}

/*****************************************************************************/
/** function used to get the current date and time
 *
 * @return
 * Current date and time
 */
int64_t UASDK_datetime(void)
{
  return UAServer_Callback_datetime();
}

//#if (UASDK_INCLUDE_XML_SUPPORT > 0)

/*****************************************************************************/
/** function used to copy the string to destination string
 *
 * @param[in] dest
 * pointer to char, where source to be copied
 *
 * @param[in] src
 * pointer to source which need to be copied to destination
 *
 * @param[in] n
 * number of bytes to be copied
 *
 * @return
 * pointer to the destination
 */
char* UASDK_strncpy(char *dest, const char *src, size_t n)
{
#ifdef _WIN32
  errno_t err = strncpy_s(dest, n, src, _TRUNCATE);
  if(err > 0)
  {
    return 0;
  }

  return dest;
#else
  return strncpy(dest, src, n);
#endif	//_WIN32
}

/*****************************************************************************/
/** function used to append source string to destination string
 *
 * @param[in] destination
 * destination string to which source string to be added
 *
 * @param[in] destBufSize
 * Size of the destination buffer
 *
 * @param[in] source
 * string which has to be added added to the destination
 *
 * @param[in] num
 * number of bytes to be added from source string to destination
 *
 * @return
 * pointer to the destination
 */
char* UASDK_strncat(char* destination, size_t destBufSize, const char* source, size_t num)
{
#ifdef _WIN32
  errno_t err = strncat_s(destination, destBufSize, source, num);
  if(err > 0)
  {
    return 0;
  }

  return destination;
#else
  UASDK_UNUSED(destBufSize);
  return strncat(destination, source, num);
#endif	//_WIN32
}

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
int UASDK_strcmp(const char* string1, const char* string2)
{
  return strcmp(string1, string2);
}

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
char * UASDK_strstr (char * str1, const char * str2 )
{
  return strstr(str1, str2);
}

/*****************************************************************************/
/** function used to convert string to double
 *
 * @param[in] str
 * string to be converted to double
 *
 * @param[in] endptr
 * end point to the string after which conversion will not happen
 *
 * @return
 * converted double number
 */
double UASDK_strtod(const char* str, char** endptr)
{
  return strtod(str, endptr);
}

/*****************************************************************************/
/** function used to convert string to float
 *
 * @param[in] str
 * string to be converted to float
 *
 * @param[in] endptr
 * end point to the string after which conversion will not happen
 *
 * @return
 * converted float number
 */
float UASDK_strtof(const char* str, char** endptr)
{
#ifdef _WIN32
  return static_cast<float>(strtod(str, endptr));
#else
  return strtof(str, endptr);
#endif	//_WIN32
}

/*****************************************************************************/
/** function used to convert string to signed integer
 *
 * @param[in] str
 * string to be converted to long integer
 *
 * @param[in] endptr
 * end point to the string after which conversion will not happen
 *
 * @param[in] base
 * base to which string to be converted
 *
 * @return
 * converted integer value
 */
int64_t UASDK_strtoll(const char* str, char** endptr, int base)
{
#ifdef _WIN32
  return _strtoi64(str, endptr, base);
#else
  return strtoll(str, endptr, base);
#endif	//_WIN32
}

/*****************************************************************************/
/** function used to convert string to unsigned integer
 *
 * @param[in] str
 * string to be converted to unsigned integer
 *
 * @param[in] endptr
 * end point to the string after which conversion will not happen
 *
 * @param[in] base
 * base to which string to be converted
 *
 * @return
 * converted unsigned integer value
 */
uint64_t UASDK_strtoull(const char* str, char** endptr, int base)
{
#ifdef _WIN32
  return _strtoui64(str, endptr, base);
#else
  return strtoull(str, endptr, base);
#endif	//_WIN32
}

/*****************************************************************************/
/** function used to convert double to string
 *
 * @param[in] value
 * double value which has to be converted
 *
 * @param[in] precision
 * precision of the value
 *
 * @param[out] str
 * pointer to memory where converted value will be stored
 *
 * @param[in] maxStrLen
 * maximum length of the string
 *
 * @return
 * number of bytes converted to string
 */
int32_t UASDK_double_to_string(double value, uint32_t precision, char* str, int maxStrLen)
{
  int32_t length = 0;

  UASDK_UNUSED(precision);

#ifdef _WIN32
  length = _snprintf_s(str, maxStrLen - 1, _TRUNCATE, "%lf", value);
#else
  length = snprintf(str, maxStrLen - 1, "%lf", value);
#endif	//_WIN32

  if ((length < 0) || (length >= maxStrLen))
  {
    return -1;
  }
  return length;
}

/*****************************************************************************/
/** function used to convert float to string
 *
 * @param[in] value
 * double value which has to be converted
 *
 * @param[in] precision
 * precision of the value
 *
 * @param[out] str
 * pointer to memory where converted value will be stored
 *
 * @param[in] maxStrLen
 * maximum length of the string
 *
 * @return
 * number of bytes converted to string
 */
int32_t UASDK_float_to_string(float value, uint32_t precision, char* str, int maxStrLen)
{
  int32_t length = 0;

  UASDK_UNUSED(precision);

#ifdef _WIN32
  length = _snprintf_s(str, maxStrLen - 1, _TRUNCATE, "%f", value);
#else
  length = snprintf(str, maxStrLen - 1, "%f", value);
#endif	//_WIN32

  if ((length < 0) || (length >= maxStrLen))
  {
    return -1;
  }
  return length;
}

/*****************************************************************************/
/** function used to convert singed integer to string
 *
 * @param[in] value
 * double value which has to be converted
 *
 * @param[in] precision
 * precision of the value
 *
 * @param[out] str
 * pointer to memory where converted value will be stored
 *
 * @param[in] maxStrLen
 * maximum length of the string
 *
 * @return
 * number of bytes converted to string
 */
 
int32_t UASDK_signed_integer_to_string(int64_t value, uint32_t precision, char* str, int maxStrLen)
{
  int32_t length = 0;

  UASDK_UNUSED(precision);

#ifdef _WIN32
  length = _snprintf_s(str, maxStrLen - 1, _TRUNCATE, "%lld", value);
#else
  length = snprintf(str, maxStrLen - 1, "%lld", value);
#endif	//_WIN32

  if ((length < 0) || (length >= maxStrLen))
  {
    return -1;
  }
  return length;
}

//#endif //(UASDK_INCLUDE_XML_SUPPORT > 0)

/*****************************************************************************/
/** function used to convert unsigned integer to string
 *
 * @param[in] value
 * double value which has to be converted
 *
 * @param[in] precision
 * precision of the value
 *
 * @param[out] str
 * pointer to memory where converted value will be stored
 *
 * @param[in] maxStrLen
 * maximum length of the string
 *
 * @return
 * number of bytes converted to string
 */
int32_t UASDK_unsigned_integer_to_string(uint64_t value, uint32_t precision, char* str, int maxStrLen)
{
  int32_t length = 0;

  UASDK_UNUSED(precision);

#ifdef _WIN32
  length = _snprintf_s(str, maxStrLen - 1, _TRUNCATE, "%llu", value);
#else
  length = snprintf(str, maxStrLen - 1, "%llu", value);
#endif	//_WIN32

  if ((length < 0) || (length >= maxStrLen))
  {
    return -1;
  }
  return length;
}

int32_t UASDK_unsigned_integer_to_hex_string(uint64_t value, uint32_t precision, char* str, int maxStrLen)
{
  int32_t length = 0;

  if (2 == precision)
  {
	  if (value > UINT8_MAX)
	  {
		  return -1;
	  }
  }
  else if (4 == precision)
  {
	  if (value > UINT16_MAX)
	  {
		  return -1;
	  }
  }
  else if (8 == precision)
  {
	  if (value > UINT32_MAX)
	  {
		  return -1;
	  }
  }
  else if (16 == precision)
  {
	  if (value > UINT64_MAX)
	  {
		  return -1;
	  }
  }
  else
  {
	 return -1;
  }

#ifdef _WIN32
  if (2 == precision)
  {
    length = _snprintf_s(str, maxStrLen - 1, _TRUNCATE, "%2.2x", (uint8_t)value);
  }
  else if (4 == precision)
  {
    length = _snprintf_s(str, maxStrLen - 1, _TRUNCATE, "%4.4x", (uint16_t)value);
  }
  else if (8 == precision)
  {
    length = _snprintf_s(str, maxStrLen - 1, _TRUNCATE, "%8.8x", (uint32_t)value);
  }
  else
  {
    length = _snprintf_s(str, maxStrLen - 1, _TRUNCATE, "%16.16llux", value);
  }
#else
  if (2 == precision)
  {
    length = snprintf(str, maxStrLen - 1, "%2.2x", value);
  }
  else if (4 == precision)
  {
    length = snprintf(str, maxStrLen - 1, "%4.4x", value);
  }
  else if (8 == precision)
  {
    length = snprintf(str, maxStrLen - 1, "%8.8x", value);
  }
  else
  {
    length = snprintf(str, maxStrLen - 1, "%16.16x", value);
  }
#endif	//_WIN32

  if ((length < 0) || (length >= maxStrLen))
  {
    return -1;
  }
  return length;
}

} //extern "C"

#endif //UASDK_INCLUDE_LIBRARY_C_API
