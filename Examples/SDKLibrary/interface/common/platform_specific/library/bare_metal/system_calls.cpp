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

#if (UASDK_INCLUDE_LIBRARY_BARE_METAL > 0)

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include "allocatable_t.h"
#include "stm32f4xx_it.h"

extern "C" {

int64_t dateTime = 0;
uint32_t lastTicks = 0;
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
  return strncpy(dest, src, n);
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
  UASDK_UNUSED(destBufSize);
  return strncat(destination, source, num);
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
/** Function used to get the current time in milliseconds
 *
 * @return
 * current time in milliseconds.
 */
uint32_t UASDK_millisecond(void)
{
  return ticks;
}

/*****************************************************************************/
/** function used to get the current date and time
 *
 * @return
 * Current date and time
 */
int64_t UASDK_datetime(void)
{
  uint32_t ticks_elapsed = 0;
  int64_t result = dateTime;
  uint32_t sys_time = UASDK_millisecond();

  if (sys_time != lastTicks)
  {
    if (sys_time > lastTicks)
    {
      ticks_elapsed = sys_time - lastTicks;
    }
    else if (sys_time < lastTicks)
    {
      ticks_elapsed = UINT32_MAX - lastTicks + sys_time;
    }
    result += 10000 * ticks_elapsed;
  }

  lastTicks = sys_time;
  dateTime += 10000 * ticks_elapsed;

  return result;
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
  return strtof(str, endptr);
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
  return strtoll(str, endptr, base);
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
  return strtoull(str, endptr, base);
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
  length = snprintf(str, maxStrLen - 1, "%lf", value);

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
  length = snprintf(str, maxStrLen - 1, "%f", value);

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
  length = snprintf(str, maxStrLen - 1, "%lld", value);

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
  length = snprintf(str, maxStrLen - 1, "%llu", value);

  if ((length < 0) || (length >= maxStrLen))
  {
    return -1;
  }
  return length;
}

} //extern "C"

#endif //UASDK_INCLUDE_LIBRARY_BARE_METAL
