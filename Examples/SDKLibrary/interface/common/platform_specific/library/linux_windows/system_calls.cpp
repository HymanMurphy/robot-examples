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

#include "uasdk_includes.h"

#if (UASDK_INCLUDE_LIBRARY_WINDOWS_LINUX > 0)

#include <stdint.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include "allocatable_t.h"

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
  return rand();
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
  return memcpy(destination, source, num);
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
  return memchr(ptr, value, num);
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
  return memset(ptr, value, num);
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
  return memcmp(ptr1, ptr2, num);
}

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
char* UASDK_strncpy(char *destination, const char *source, size_t num)
{
#ifdef _WIN32
  errno_t err = strncpy_s(destination, num, source, _TRUNCATE);
  if(err > 0)
  {
    return 0;
  }

  return destination;
#else
  return strncpy(destination, source, num);
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
/** Function used to get the current time in milliseconds
 *
 * @return
 * current time in milliseconds.
 */
uint32_t UASDK_millisecond(void)
{
#if _WIN32
  return static_cast<uint32_t> ( ::GetTickCount64() );
#else
  uint64_t msecs_rolled_over = 0;
  uint64_t tod_secs = 0;
  uint64_t tod_usecs = 0;
  uint64_t tod_msecs = 0;
  const uint64_t ONE_K = 1000;
  const uint64_t UMAX = UINT32_MAX;

  struct timeval time_of_day;

  if (gettimeofday(&time_of_day, NULL) < 0)
  {
    return 0;
  }

  tod_secs = time_of_day.tv_sec;
  tod_usecs = time_of_day.tv_usec;
  tod_msecs = (tod_secs * ONE_K) + (tod_usecs / ONE_K);
  msecs_rolled_over = tod_msecs % UMAX;

  return (uint32_t)msecs_rolled_over;
#endif
}

/*****************************************************************************/
/** function used to get the current date and time
 *
 * @return
 * Current date and time
 */
int64_t UASDK_datetime(void)
{
#ifdef _WIN32
  FILETIME ft;
  LARGE_INTEGER t;
  ::GetSystemTimeAsFileTime(&ft);
  t.HighPart = (LONG) ft.dwHighDateTime;
  t.LowPart = ft.dwLowDateTime;
  return t.QuadPart;
#else
  struct timeval time_of_day;
  uint64_t result = static_cast<uint64_t>(EPOCH_DIFF);

  gettimeofday(&time_of_day, NULL);
  result += time_of_day.tv_sec;
  result *= (uint64_t)10000000;
  result += time_of_day.tv_usec * 10;

  return (int64_t)result;
#endif
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
  UASDK_UNUSED(precision);

  int32_t length = 0;
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
  UASDK_UNUSED(precision);

  int32_t length = 0;
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
  UASDK_UNUSED(precision);

  int32_t length = 0;
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
  UASDK_UNUSED(precision);

  int32_t length = 0;
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
    length = _snprintf_s(str, maxStrLen - 1, _TRUNCATE, "%2.2llx", value);
  }
  else if (4 == precision)
  {
    length = _snprintf_s(str, maxStrLen - 1, _TRUNCATE, "%4.4llx", value);
  }
  else if (8 == precision)
  {
    length = _snprintf_s(str, maxStrLen - 1, _TRUNCATE, "%8.8llx", value);
  }
  else
  {
    length = _snprintf_s(str, maxStrLen - 1, _TRUNCATE, "%16.16llx", value);
  }
#else
  if (2 == precision)
  {
    length = snprintf(str, maxStrLen - 1, "%2.2x", static_cast<uint8_t>(value));
  }
  else if (4 == precision)
  {
    length = snprintf(str, maxStrLen - 1, "%4.4x", static_cast<uint16_t>(value));
  }
  else if (8 == precision)
  {
    length = snprintf(str, maxStrLen - 1, "%8.8x", static_cast<uint32_t>(value));
  }
  else
  {
    length = snprintf(str, maxStrLen - 1, "%16.16lux", static_cast<unsigned long>(value));
  }
#endif	//_WIN32

  if ((length < 0) || (length >= maxStrLen))
  {
    return -1;
  }
  return length;
}

} //extern "C"

#endif //UASDK_INCLUDE_LIBRARY_WINDOWS_LINUX
