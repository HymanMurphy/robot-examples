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

#include "common_utilities_t.h"
#include "utilities.h"

#ifdef  __cplusplus
extern "C"
{
#endif
  bool UASDK_IsLeapYear(int32_t year)
  {
    return ((year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? true : false);
  }

  int32_t UASDK_GetDaysInMonth(int32_t year, int32_t month)
  {
    int32_t result = 0;

    switch (month)
    {
      case FEBRUARY:
        result = UASDK_IsLeapYear(year) ? 29 : 28;
        break;
      case JANUARY:
      case MARCH:
      case MAY:
      case JULY:
      case AUGUST:
      case OCTOBER:
      case DECEMBER:
        result = 31;
        break;
      case APRIL:
      case JUNE:
      case SEPTEMBER:
      case NOVEMBER:
        result = 30;
        break;
      default:
        break;
    }

    return result;
  }

  void UASDK_GetDateTimeFromFileTime(int64_t systime_s, int32_t* rem_sec, int32_t *rem_min, int32_t* rem_hr, int32_t* rem_days, int32_t* yr)
  {
    int32_t no_of_leap_yr = 0;
    int64_t hr = 0, min = 0;
    int64_t days = 0;

    *rem_sec = systime_s % 60;
    min = systime_s / 60;

    *rem_min = min % 60;
    hr = min / 60;

    *rem_hr = hr % 24;
    days = hr / 24;

    *rem_days = days % 365;
    *yr = (int32_t)(days / 365);

    no_of_leap_yr = (*yr + 2) / 4;

    //if (((*yr + 2) % 4) == 0)
    if (UASDK_IsLeapYear(*yr + 2))
    {
      if ((*rem_days - no_of_leap_yr) < (UASDK_GetDaysInMonth(*yr, 1) + UASDK_GetDaysInMonth(*yr, 2)))
      {
        no_of_leap_yr--;
      }
    }

    if ((int32_t)no_of_leap_yr > (*rem_days))
    {
      (*rem_days) += 365;
      (*yr)--;
      no_of_leap_yr = *yr / 4;

      (*rem_days) -= no_of_leap_yr;
    }
    else
    {
      (*rem_days) -= no_of_leap_yr;
    }

    if ((*rem_days) == 0)
    {
      if (*yr > 0)
      {
        (*rem_days) = 365;
        (*yr)--;
      }
    }
  }

  void UASDK_GetDateMonthYear(int32_t rem_days, int32_t yr, int32_t* date, int32_t* month, int32_t* year)
  {
    *year = yr + 1970;
    for (int32_t mth = 1; mth <= DECEMBER; mth++)
    {
      int32_t days = 0;
      days = UASDK_GetDaysInMonth(*year, mth);
      if (rem_days < days)
      {
        *month = mth;
        *date = rem_days + 1;
        break;
      }
      else
      {
        rem_days -= days;
      }
    }
  }

  void UASDK_GetAscii(int32_t input, int32_t length, char* stringTime)
  {
    int32_t i = length;

    for (; i > 0; i--)
    {
      int32_t divider = 1;
      int32_t j = i - 1;
      while (j)
      {
        divider *= 10;
        j--;
      }
      stringTime[length - i] = '0' + (input / divider);
      input = (input % divider);
    }
  }

  int32_t UASDK_GetFourDigitYear(int32_t twoDigitYear)
  {
    return (twoDigitYear + 2000);
  }

  int64_t UASDK_GetFileTimeFromDateTimeFormat(UASDK_DatetimeFormat_t dateTimeFormat)
  {
    int64_t time = (EPOCH_DIFF * MICROSECONDS * 10);

    time += ((UASDK_GetSecondsFromInputString(NULL, 0, YEAR, dateTimeFormat.year, 1)) * (MICROSECONDS * 10));
    time += ((UASDK_GetSecondsFromInputString(NULL, 0, MONTH, dateTimeFormat.month, 1)) * (MICROSECONDS * 10));
    time += ((UASDK_GetSecondsFromInputString(NULL, 0, DAY, dateTimeFormat.day, 1)) * (MICROSECONDS * 10));
    time += ((UASDK_GetSecondsFromInputString(NULL, 0, HOUR, dateTimeFormat.hour, 1)) * (MICROSECONDS * 10));
    time += ((UASDK_GetSecondsFromInputString(NULL, 0, MINUTE, dateTimeFormat.minute, 1)) * (MICROSECONDS * 10));
    time += ((UASDK_GetSecondsFromInputString(NULL, 0, SECONDS, dateTimeFormat.second, 1)) * (MICROSECONDS * 10));

    return time;
  }

  UASDK_DatetimeFormat_t UASDK_GetDateTimeFormatFromFileTime(int64_t fileTime)
  {
    int64_t filetime_us = fileTime / 10;
    int64_t systime_s = filetime_us / 1000000 - EPOCH_DIFF;
    int32_t rem_sec = 0, rem_min = 0, rem_hr = 0, rem_days = 0, yr = 0, date = 0, month = 0, year = 0;
    UASDK_DatetimeFormat_t time;
    UASDK_GetDateTimeFromFileTime(systime_s, &rem_sec, &rem_min, &rem_hr, &rem_days, &yr);

    UASDK_GetDateMonthYear(rem_days, yr, &date, &month, &year);

    time.year = year;
    time.month = month;
    time.day = date;
    time.hour = rem_hr;
    time.minute = rem_min;
    time.second = rem_sec;

    return time;
  }

  void UASDK_GetStringFromFileTime(int64_t filetime, int32_t appendCharacterZ, size_t stringLength, char* stringtime)
  {
    size_t minimumLength = appendCharacterZ ? 16 : 15;
    if (stringLength >= minimumLength && stringtime)
    {
      int64_t filetime_us = filetime / 10;
      int64_t systime_s = filetime_us / 1000000 - EPOCH_DIFF;
      int32_t rem_sec = 0, rem_min = 0, rem_hr = 0, rem_days = 0, yr = 0, date = 0, month = 0, year = 0;

      UASDK_GetDateTimeFromFileTime(systime_s, &rem_sec, &rem_min, &rem_hr, &rem_days, &yr);

      UASDK_GetDateMonthYear(rem_days, yr, &date, &month, &year);

      UASDK_GetAscii(year, 4, stringtime);
      UASDK_GetAscii(month, 2, &stringtime[4]);
      UASDK_GetAscii(date, 2, &stringtime[6]);
      UASDK_GetAscii(rem_hr, 2, &stringtime[8]);
      UASDK_GetAscii(rem_min, 2, &stringtime[10]);
      UASDK_GetAscii(rem_sec, 2, &stringtime[12]);

      if (appendCharacterZ > 0)
      {
        stringtime[minimumLength - 2] = 'Z';
      }
      stringtime[minimumLength - 1] = '\0';
    }
  }

  void UASDK_GetStringFromDateTimeFormat(UASDK_DatetimeFormat_t dateTimeFormat, int32_t appendCharacterZ, size_t stringLength, char* stringtime)
  {
    size_t minimumLength = appendCharacterZ ? 16 : 15;
    if (stringLength >= minimumLength && stringtime)
    {
      UASDK_GetAscii(dateTimeFormat.year, 4, stringtime);
      UASDK_GetAscii(dateTimeFormat.month, 2, &stringtime[4]);
      UASDK_GetAscii(dateTimeFormat.day, 2, &stringtime[6]);
      UASDK_GetAscii(dateTimeFormat.hour, 2, &stringtime[8]);
      UASDK_GetAscii(dateTimeFormat.minute, 2, &stringtime[10]);
      UASDK_GetAscii(dateTimeFormat.second, 2, &stringtime[12]);

      if (appendCharacterZ > 0)
      {
        stringtime[minimumLength - 2] = 'Z';
      }
      stringtime[minimumLength - 1] = '\0';
    }
  }

  void UASDK_TextToFileTime(const char* text, int32_t yearLength, int64_t* result)
  {
    if (!text)
    {
      return;
    }

    //Validate year length
    if (!(yearLength == 2 || yearLength == 4))
    {
      return;
    }

    text = UASDK_RemoveWhiteSpacesFromInputText(text);
    if (!text)
    {
      return;
    }

    int64_t time = (EPOCH_DIFF * MICROSECONDS * 10);

    /*
    * ex:  20170223085714Z -- Four digit year
    *      170223085714Z -- Two digit year
    */
    time += UASDK_GetSecondsFromInputString(text, yearLength, YEAR, 0, 0) * (MICROSECONDS * 10);
    text = text + yearLength;
    time += UASDK_GetSecondsFromInputString(text, 2, MONTH, 0, 0) * (MICROSECONDS * 10);
    text = text + 2;
    time += UASDK_GetSecondsFromInputString(text, 2, DAY, 0, 0) * (MICROSECONDS * 10);
    text = text + 2;
    time += UASDK_GetSecondsFromInputString(text, 2, HOUR, 0, 0) * (MICROSECONDS * 10);
    text = text + 2;
    time += UASDK_GetSecondsFromInputString(text, 2, MINUTE, 0, 0) * (MICROSECONDS * 10);
    text = text + 2;
    time += UASDK_GetSecondsFromInputString(text, 2, SECONDS, 0, 0) * (MICROSECONDS * 10);
    text = text + 2;

    *result = time;
  }

  int32_t UASDK_Strnlen(const char* inputString, size_t maxLength)
  {
    return uasdk::Utilities_t::Strnlen(inputString, maxLength);
  }

  const char* UASDK_RemoveWhiteSpacesFromInputText(const char* text)
  {
    if (!text)
    {
      return text;
    }

    while (*text == ' ')
    {
      if (*text == '\0')
      {
        return 0;
      }
      text++;
    }

    return text;
  }

  const char* UASDK_FindCharInInputText(const char* text, const char value, int32_t* count)
  {
    if (!text || !count)
    {
      return text;
    }

    while (*text != value)
    {
      if (*text == '\0')
      {
        return 0;
      }
      text++;
      (*count)++;
    }

    return text;
  }

  int64_t UASDK_GetSecondsFromInputString(const char* dateTimeString, const int32_t length, int32_t what, int32_t inputNumber, int32_t parseNumber)
  {
    static int32_t year = 0;
    int32_t count = 0;
    int32_t temp = 0;
    int32_t i, j;
    int64_t result = 0;

    if (parseNumber > 0) //Parse inputNumber
    {
      count = inputNumber;
    }
    else //Parse dateTimeString
    {
      //2010-09-15T14:50:06.483Z
      if (!dateTimeString)
      {
        return 0;
      }

      for (i = 0; i < length; i++)
      {
        temp = (dateTimeString[i] - '0');
        for (j = 0; j < (length - i - 1); j++)
        {
          temp *= 10;
        }
        count += temp;
      }
    }

    if ((what == YEAR) && (length == 2))
    {
      count = UASDK_GetFourDigitYear(count);
    }

    if (what == YEAR)
    {
      year = count;
    }

    //Based on the required data parse the value and pass ther value in seconds
    switch (what)
    {
      case YEAR:
        for (i = 1970; i < count; i++)
        {
          result += ((UASDK_IsLeapYear(i)) ? 366 : 365);
        }
        result *= 24 * 60 * 60;
        break;

      case MONTH:

        for (i = 1; i < count; i++) // If month is Sep, for all months before September the values should be calculated!
        {
          result += UASDK_GetDaysInMonth(year, i);
        }

        year = 0;
        result *= 24 * 60 * 60;
        break;

      case DAY:
        //if count == 1 that does not mean 1 day is elapsed, it means day in progress. only if count > 1 result has to be calculated!
        result = (count - 1) * 24 * 60 * 60;
        break;

      case HOUR:
        result = count * 60 * 60;
        break;

      case MINUTE:
        result = count * 60;
        break;

      case SECONDS:
      case MILLI_SECONDS:
        result = count;
        break;

      default:
        break;
    }

    return result;
  }


  int get_string_ipv4_to_ipv4octet(const UA_UTF8_string_t* ip_addresses, unsigned char* ipv4octet)
  {
    const unsigned char* buf = 0;
    int i = 0, k = 0, j = 0, y = 0;
    unsigned char x = 0;

    if (!ip_addresses || !ip_addresses->data || !ipv4octet)
    {
      return (-1);
    }

    buf = ip_addresses->data;

    for (; i < ip_addresses->length; i++)
    {
      if (buf[i] == '.')
      {
        ipv4octet[k] = x;
        j = x = 0;
        k++;
        continue;
      }
      y = (buf[i] - '0');
      x = x * 10 + y;
      j++;

      if (j > 3 || k > 3 || x > 255 || y > 9 || y < 0)
      {
        return (-1);
      }
    }
    ipv4octet[k] = x;

    return (0);
  }

#ifdef  __cplusplus
} // extern "C"
#endif

