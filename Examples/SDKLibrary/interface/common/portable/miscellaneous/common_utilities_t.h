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

#ifndef __COMMON_UTILITIES_T__
#define __COMMON_UTILITIES_T__

#include "uasdk_includes.h"

#define MILLISECONDS 1000
#define MICROSECONDS 1000000

#define YEAR            0
#define MONTH           1
#define DAY             2
#define HOUR            3
#define MINUTE          4
#define SECONDS         5
#define MILLI_SECONDS   6



/** \addtogroup grpMiscellaneous
*@{*/

/*
* Any Utilities which is required for Both C and C++ can be implemented in these files
*/

#ifdef  __cplusplus
extern "C"
{
#endif


  /*****************************************************************************/
  /** \brief DatetimeFormat_t
  * DatetimeFormat represents date and time and
  * is used to hold the date time converted from filetime
  * year is the actual year
  * month value start with 1
  */
  typedef struct
  {
    int32_t year;
    int32_t month;
    int32_t day;
    int32_t hour;
    int32_t minute;
    int32_t second;
  } UASDK_DatetimeFormat_t;

  typedef enum
  {
    JANUARY = 1,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER
  } UASDK_Month_t;

  /*****************************************************************************/
  /** Function to get number of days in a given month
  *
  * @param[in] year
  * input year
  *
  * @param[in] month
  * input month
  *
  * @return
  * no of days
  *
  */
  int32_t UASDK_GetDaysInMonth(int32_t year, int32_t month);

  /*****************************************************************************/
  /** Function to convert input UADateTimeFormat to fileTime
  *
  * @param[in] dateTimeFormat
  * input dateTime format
  *
  * @return
  * fileTime converted from the input
  *
  */
  int64_t UASDK_GetFileTimeFromDateTimeFormat(UASDK_DatetimeFormat_t dadateTimeFormat);

  /*****************************************************************************/
  /** Function to convert fileTime to UADateTimeFormat
  *
  * @param[in] fileTime
  * input fileTime
  *
  * @return
  * DatetimeFormat_t converted from the input fileTime
  *
  */
  UASDK_DatetimeFormat_t UASDK_GetDateTimeFormatFromFileTime(int64_t fileTime);

  /*****************************************************************************/
  /** Function to get file time in string format
  *
  * @param[in] fileTime
  * input fileTime
  *
  * @param[in] appendCharacterZ
  * append 'Z' to the output string if appendCharacterZ > 0
  *
  * @param[in] stringLength
  * string length
  *
  * @param[out] stringtime
  * output string. The format is YYYYMMDDHHMMSSZ
  *
  * @return
  *
  */
  void UASDK_GetStringFromFileTime(int64_t filetime, int32_t appendCharacterZ, size_t stringLength, char* stringtime);

  /*****************************************************************************/
  /** Function to UA get date time format in string format
  *
  * @param[in] dateTimeFormat
  * input dateTimeFormat. It should be passed in UTC.
  *
  * @param[in] appendCharacterZ
  * append 'Z' to the output string if appendCharacterZ > 0
  *
  * @param[in] stringLength
  * string length
  *
  * @param[out] stringtime
  * output string. The format is YYYYMMDDHHMMSSZ
  *
  * @return
  *
  */
  void UASDK_GetStringFromDateTimeFormat(UASDK_DatetimeFormat_t dateTimeFormat, int32_t appendCharacterZ, size_t stringLength, char* stringtime);

  /*****************************************************************************/
  /** Function to date time from input buffer
  *
  * @param[in] text
  * input text
  *
  * @param[in] yearLength
  * number of digits in year. It can be either 2 or 4 only
  *
  * @param[out] result
  * time
  *
  * @return
  * return void
  *
  */
  void UASDK_TextToFileTime(const char* text, int32_t yearLength, int64_t* result);

  /*****************************************************************************/
  /** Function to get string length of input string
  *
  * @param[in] inputString
  * input string
  *
  * @param[in] maxLength
  * maximum length of the string
  *
  * @return
  * return the length of the string
  *
  */
  int32_t UASDK_Strnlen(const char* inputString, size_t maxLength);

  /*****************************************************************************/
  /** Remove white space in the given string
  *
  * This function will return the pointer to the character in string.
  *
  * @param[in] text
  * string in which character to be found.
  *
  * @return
  * Returns pointer to the string without white spaces
  */
  const char* UASDK_RemoveWhiteSpacesFromInputText(const char* text);

  /*****************************************************************************/
  /** Find Character in the given string.
  *
  * This function will return the pointer to the character in string.
  *
  * @param[in] text
  * string in which character to be found.
  *
  * @param[in] value
  * character data to be found.
  *
  * @param[out] count
  * length of the string till that character from the begining of input text
  *
  * @return
  * Returns pointer to the charater in the string
  */
  const char* UASDK_FindCharInInputText(const char* text, const char value, int32_t* count);

  /*****************************************************************************/
  /** Function to get seconds from input string or input number based on the parseString flag.
  * It will give seconds from 1601-JAN-01 - 00:00:000 to input time
  *
  * @param[in] dateTimeString
  * input date time in string format
  *
  * @param[in] length
  * length of the input string
  *
  * @param[in] what
  * will describe if the input string is an year, month, day, hour, seconds, milliseconds
  *
  * @param[in] inputNumber
  * input number
  *
  * @param[in] parseNumber
  * if parseNumber > 0, it will process inputNumber else it will process dateTimeString
  *
  * @return
  * seconds based on the input
  */
  int64_t UASDK_GetSecondsFromInputString(const char* dateTimeString, const int32_t length, int32_t what, int32_t inputNumber, int32_t parseNumber);

  /*****************************************************************************/
  /** get ascii text from a number
  *
  * @param[in] input
  * the number to convert
  *
  * @param[in] length
  * the maximum number of bytes in the temp
  *
  * @param[in/out] stringTime
  * string to write too.
  *
  */
  void UASDK_GetAscii(int32_t input, int32_t length, char* stringTime);

  /*****************************************************************************/
  /** get string ipv4 to ipv4octet
  *
  * @param[in] ip_addresses
  * ip_addresses ip address in string format e.g. "199.68.28.100"
  *
  * @param[out] ipv4octet
  * ipv4 in octet format e.g char ipv4octet[4] = {199, 68, 28, 100}
  *
  * @param[out] return
  * -1 if failed, 0 if success.
  *
  */
  int get_string_ipv4_to_ipv4octet(const UA_UTF8_string_t* ip_addresses, unsigned char* ipv4octet);

#ifdef  __cplusplus
} // extern "C"
#endif

  /** @} */

#endif /* __COMMON_UTILITIES_T__ */
