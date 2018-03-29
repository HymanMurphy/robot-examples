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

#ifndef __UTILITIES_H__
#define __UTILITIES_H__

#include "uasdk_includes.h"
#include "allocatable_t.h"

#ifdef  __cplusplus

namespace uasdk
{

class String_t;
class Status_t;
template<typename T>
class Array_t;
template<typename T>
class IntrusivePtr_t;

/** \addtogroup grpMiscellaneous
 *@{*/


/*****************************************************************************/
/** \brief IndexRange_t
 * Index Range wrapper
 */
class IndexRange_t : public Allocatable_t
{
public:
  uint32_t start;
  uint32_t end;
};



/*****************************************************************************/
/** \brief Utilities_t
 * This class implements utility functions required for UA SDK
 */
class Utilities_t
{
  public:

  /*****************************************************************************/
  /** Check if the number is power of two
   *
   * @param[in] uint32_t x
   * Number to be checked
   *
   * @return
   * True - Power of two
   * False - Not a power of two
   */
  static inline bool Is_power_of_2(uint32_t x) { return x && !(x & (x - 1)); }

  /*****************************************************************************/
  /** Round the number to the nearest power of two
   *
   * @param[in] unsigned x
   * Number to be rounded up
   *
   * @return
   * Rounded number
   */
  static inline unsigned Round_up_to_power_of_2(unsigned x)
  {
    x = x - 1;
    x = x | (x >> 1);
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
    x = x | (x >>16);
    return x + 1;
 }

  /*****************************************************************************/
  /** Get the log base 2 of the number
   *
   * @param[in] uint32_t val
   * Value
   *
   * @return
   * Result of the Log base 2 of a number
   */
  static inline uint32_t Log_base_2(uint32_t val)
  {
    uint32_t result = 0;
    while (val > 1)
    {
      result++;
      val = val >> 1;
    };
    return result;
  }

  /*****************************************************************************/
  /** Check if the memory is aligned or not
   *
   * @param[in] uint32_t val
   * Value
   *
   * @return
   * Result of the Log base 2 of a number
   */
  static inline bool Is_aligned(const void* address)
  {
    if (address != 0)
    {
      return ((uintptr_t)address & (uintptr_t)(UASDK_MAX_ALIGNMENT - 1)) == 0;
    }
    return false;
  }

  /*****************************************************************************/
  /** Get string length of the character array
   *
   * @param[in] const char* str
   * Character array string
   *
   * @param[in] size_t maxLen
   * The maximum length of an array
   *
   * @return
   * Returns the string length of the character array
   */
  static int32_t Strnlen(const char* str, size_t maxLen);

  /*****************************************************************************/
  /** Get integer power  x to the power y
   *
   * @param[in] uint64_t x
   * Base number
   *
   * @param[in] uint64_t y
   * Power
   *
   * @return
   * Returns the result
   */
  static uint64_t IntegerPower(uint64_t x, uint64_t y);

  /*****************************************************************************/
  /** Convert the string to unsigned long
   *
   * @param[in] const String_t& str
   * String to be converted
   *
   * @return
   * Returns the result unsigned long
   */
  static uint64_t StringToUlong(const String_t& str);

  /*****************************************************************************/
  /** Convert the unsigned long to string
   *
   * @param[in] uint64_t value
   * Value to be converted
   *
   * @param[out] const String_t& str
   * Converted string
   *
   * @return
   * Returns status of the operation
   */
  static Status_t UlongToString(uint64_t value, String_t& str);

  /*****************************************************************************/
  /** Validate the index range
   *
   * @param[in] const String_t& indexRange
   * Index range
   *
   * @param[in] Array_t<IndexRange_t>& subRanges
   * Sub Range
   *
   * @return
   * Returns status of the operation
   */
  static Status_t ValidateIndexRange(const String_t& indexRange, Array_t<IndexRange_t>& subRanges);

  /*****************************************************************************/
  /** Validate the internal index range
   *
   * @param[in] const uint8_t* index_range
   * Index range
   *
   * @param[in] int32_t length
   * Length of an array
   *
   * @return
   * Returns status of the operation
   */
  static bool ValidateIndexRangeInternal(const uint8_t* index_range, int32_t length);

  /*****************************************************************************/
  /** Index Range Number of Ranges
   *
   * @param[in] const uint8_t* index_range
   * Index range
   *
   * @param[in] int32_t length
   * Length of an array
   *
   * @return
   * Returns status of the operation
   */
  static uint32_t IndexRangeNoOfRanges(const uint8_t* index_range, const int32_t length);

  /*****************************************************************************/
  /** Parse Index Range
   *
   * @param[in] const uint8_t* index_range
   * Index range
   *
   * @param[in] int32_t length
   * Length of an array
   *
   * @param[in] uint32_t which_range
   * Which Range to parse
   *
   * @param[out] IndexRange_t& range
   * Parsed Index range
   *
   * @return
   * Returns status of the operation
   */
  static bool ParseIndexRange(const uint8_t* index_range,
                              const int32_t length,
                              uint32_t which_range,
                              IndexRange_t& range);

  /*****************************************************************************/
  /** Parse Index Range
   *
   * @param[in] const uint8_t* index_range
   * Index range
   *
   * @param[in] int32_t length
   * Length of an array
   *
   * @param[out] IndexRange_t& range
   * Index range
   *
   * @param[out] uint16_t& length_parsed
   * Length parsed
   *
   * @return
   * Returns status of the operation
   */
  static bool ParseAnIndexRange(const uint8_t* index_range,
                                int32_t length,
                                IndexRange_t& range,
                                uint16_t& length_parsed);

	/*****************************************************************************/
	/** Function generates string identifier
	*
	* @param[in] input1
	* browseName of the parent node
	*
	* @param[in] input2
	* browseName of the input node
	*
	* @param[in] withSeparator
	* if the separator is required for concatenation of input strings
	*
	* @param[in] separator
	* separator between input1 and input2
	*
	* @param[out] result
	* result will be concatenation of input parameters with / separator. Example: parentBrowseName/browseName
	*
	* @return
	* status of the operation
	*
	*/
	static Status_t ConcatenateInputStrings(const String_t& input1, const String_t& input2, bool withSeparator, char separator, String_t& result);

};

/** @} */

}

#endif //__cplusplus

#endif /* __UTILITIES_H__ */
