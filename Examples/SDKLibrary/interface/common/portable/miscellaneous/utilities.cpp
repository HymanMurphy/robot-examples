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

#include "utilities.h"
#include "uasdk_includes.h"
#include "opcua_string_t.h"
#include "ilog_listener_t.h"

namespace uasdk
{

int32_t Utilities_t::Strnlen(const char* str, size_t maxLen)
{
  const void* terminator = UASDK_memchr( str, '\0', maxLen);
  if (terminator == 0)
  {
    if (maxLen > INT32_MAX)
    {
      return 0;
    }
    else
    {
      return static_cast<int32_t>(maxLen);
    }
  }
  else
  {
    uintptr_t length = reinterpret_cast<const char*>(terminator) - str;
    if (length > INT32_MAX)
    {
      return 0;
    }
    return static_cast<int32_t>(length);
  }
}

uint64_t Utilities_t::IntegerPower(uint64_t x, uint64_t y)
{
  uint64_t result = 1;
  for (uint64_t i = 0; i < y; i++)
  {
    result *= x;
  }
  return result;
}

uint64_t Utilities_t::StringToUlong(const String_t& str)
{
  uint64_t result = 0;
  const int ASCII_OFFSET = 48;

  if ((str.Length() <= 0) || !str.Payload().Data())
  {
    return 0;
  }

  const uint8_t* bytes = str.Payload().Data();
  int32_t count = str.Length();
  for (int32_t i = 0; i < count; i++)
  {
    if ((bytes[i] < ASCII_OFFSET) || (bytes[i] >= ASCII_OFFSET + 10))
    {
      return 0;
    }
    if (i < count - 1)
    {
      result += (bytes[i] - ASCII_OFFSET) * IntegerPower(10, count - i - 1);
    }
    else
    {
      result += (bytes[i] - ASCII_OFFSET);
    }
  }
  return result;
}

Status_t Utilities_t::UlongToString(uint64_t value, String_t& str)
{
  uint64_t source = value;
  const uint8_t ASCII_OFFSET = 48;
  const uint8_t MAX_DIGITS = 20;
  uint8_t digits[MAX_DIGITS];
  uint32_t no_of_digits = 0;

  for (int32_t i = MAX_DIGITS - 1; i >= 0; i--)
  {
    no_of_digits++;

    uint64_t digit = source;
    if (digit < 10)
    {
      digits[i] = ASCII_OFFSET + static_cast<uint8_t>(digit);
      break;
    }
    else
    {
      digit = source % 10;
      source = source / 10;
      digits[i] = ASCII_OFFSET + static_cast<uint8_t>(digit);
    }
  }

  return str.Payload().CopyFrom(&digits[MAX_DIGITS - no_of_digits], no_of_digits);
}

Status_t Utilities_t::ValidateIndexRange(const String_t& indexRange, Array_t<IndexRange_t>& subRanges)
{
  if (indexRange.IsNull())
  {
    subRanges.Initialise(0);
    return OpcUa_Good;
  }

  const uint8_t* indexRange_ = indexRange.Payload().Data();
  int32_t indexRangeLen_ = indexRange.Length();

  if(!ValidateIndexRangeInternal(indexRange_, indexRangeLen_))
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadIndexRangeInvalid);
  }

  uint32_t noOfRanges = IndexRangeNoOfRanges(indexRange_, indexRangeLen_);
  if(noOfRanges <= 0)
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadIndexRangeNoData);
  }

  Status_t status = subRanges.Initialise(noOfRanges);
  if(status.IsBad())
  {
    return status;
  }

  for(uint32_t i = 0; i < noOfRanges; i++)
  {
    IndexRange_t range;

    if(!(ParseIndexRange(indexRange_, indexRangeLen_, i, range)))
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadIndexRangeNoData);
    }
    subRanges[i].start = range.start;
    subRanges[i].end = range.end;

  }

  return OpcUa_Good;
}

bool Utilities_t::ValidateIndexRangeInternal(const uint8_t* index_range, int32_t length)
{
  uint32_t no_of_ranges = IndexRangeNoOfRanges(index_range, length);
  if (no_of_ranges == 0)
  {
    return false;
  }
  return true;
}

uint32_t Utilities_t::IndexRangeNoOfRanges(const uint8_t* index_range, const int32_t length)
{
  if (index_range == 0)
  {
    return 0;
  }

  if (length <= 0)
  {
    return 0;
  }

  uint32_t no_of_ranges = 0;
  int32_t length_remaining = length;

  while (length_remaining > 0)
  {
    //lint --e{578}
    IndexRange_t range;
    uint16_t length_parsed = 0;
    uint32_t index = length - length_remaining;

    if (ParseAnIndexRange(&index_range[index], length_remaining, range, length_parsed))
    {
      no_of_ranges++;
      length_remaining -= length_parsed;
    }
    else
    {
      //An error occurred
      return 0;
    }
  }
  return no_of_ranges;
}

//lint -e{578}
bool Utilities_t::ParseIndexRange(const uint8_t* index_range,
                                  const int32_t length,
                                  uint32_t which_range,
                                  IndexRange_t& range)
{

  if (index_range == 0)
  {
    return 0;
  }

  if (length <= 0)
  {
    return false;
  }

  uint16_t length_remaining = length;

  for (uint32_t i = 0; (i <= which_range) && (length_remaining > 0); i++)
  {
    uint16_t length_parsed = 0;
    uint16_t index = length - length_remaining;

    range.start = 0, range.end = 0;

    bool result = ParseAnIndexRange(&index_range[index], length_remaining, range, length_parsed);
    if (i == which_range)
    {
      return result;
    }
    else if (result)
    {
      length_remaining -= length_parsed;
    }
    else
    {
      //An error occurred
      return 0;
    }
  }
  return false;
}

bool Utilities_t::ParseAnIndexRange(const uint8_t* index_range,
                                    int32_t length,
                                    IndexRange_t& range,
                                    uint16_t& length_parsed)
{
  if (length <= 0)
  {
    return false;
  }

  typedef enum
  {
    ST_START,
    ST_FIRST_IN_PROGRESS,
    ST_COLON_FOUND,
    ST_SECOND_IN_PROGRESS,
    ST_COMMA_FOUND
  } State_t;

  State_t state = ST_START;

  if (length <= 0)
  {
    return false;
  }

  if (index_range == 0)
  {
    return false;
  }

  const uint32_t MAX_DIGITS = 100;
  uint8_t digits[2][MAX_DIGITS];
  uint32_t start_count = 0;
  uint32_t end_count = 0;

  for (uint32_t i = 0; i < 2; i++)
  {
    for (uint32_t j = 0; j < MAX_DIGITS; j++)
    {
      digits[i][j] = 0;
    }
  }


  for (int32_t i = 0; i < length; i++)
  {
    if ((start_count >= (MAX_DIGITS - 1)) || (end_count >= (MAX_DIGITS - 1)))
    {
      return false;
    }

    uint8_t digit = index_range[i];

    switch (state)
    {
    case ST_START:
      if ((digit >= '0') && (digit <= '9'))
      {
        digits[0][start_count++] = digit - '0';
        state = ST_FIRST_IN_PROGRESS;
      }
      else
      {
        return false;
      }
      break;

    case ST_FIRST_IN_PROGRESS:
      if ((digit >= '0') && (digit <= '9'))
      {
        digits[0][start_count++] = digit - '0';
      }
      else if (digit == ':')
      {
        state = ST_COLON_FOUND;
      }
      else if (digit == ',')
      {
        state = ST_COMMA_FOUND;
      }
      else
      {
        return false;
      }
      break;

    case ST_COLON_FOUND:
      if ((digit >= '0') && (digit <= '9'))
      {
        digits[1][end_count++] = digit - '0';
        state = ST_SECOND_IN_PROGRESS;
      }
      else
      {
        return false;
      }
      break;

    case ST_SECOND_IN_PROGRESS:
      if ((digit >= '0') && (digit <= '9'))
      {
        digits[1][end_count++] = digit - '0';
      }
      else if (digit == ',')
      {
        state = ST_COMMA_FOUND;
      }
      else
      {
        return false;
      }
      break;

    case ST_COMMA_FOUND:
      break;
    }

    if (state == ST_COMMA_FOUND)
    {
      if ((i + 1) < length)
      {
        length_parsed = i + 1;
        break;
      }
      else
      {
        return false;
      }
    }

    if (i == (length - 1))
    {
      length_parsed = length;
    }
  }

  //Convert start_count
  range.start = 0;
  for (uint32_t i = 0; i < start_count; i++)
  {
    uint32_t multiplier = 1;
    for (uint32_t j = 0; j < start_count - i - 1; j++)
    {
        multiplier *= 10;
    }
    range.start += digits[0][i] * multiplier;
  }

  if (end_count == 0)
  {
    range.end = range.start;
  }
  else
  {
    //Convert end_count
    range.end = 0;
    for (uint32_t i = 0; i < end_count; i++)
    {
      uint32_t multiplier = 1;
      for (uint32_t j = 0; j < end_count - i - 1; j++)
      {
        multiplier *= 10;
      }
      range.end += digits[1][i] * multiplier;
    }

    if (range.start == range.end)
    {
      return false;
    }
    if (range.start > range.end)
    {
      return false;
    }
  }

  return true;
}

Status_t Utilities_t::ConcatenateInputStrings(const String_t& input1, const String_t& input2, bool withSeparator, char separator, String_t& result)
{
	Status_t status;

	ScopedPtr_t< Array_t<char> > inputString1, inputString2;
	status = input1.ToString(inputString1);
	if (status.IsBad() || !inputString1.is_set())
	{
		return OpcUa_BadUnexpectedError;
	}

	status = input2.ToString(inputString2);
	if (status.IsBad() || !inputString2.is_set())
	{
		return OpcUa_BadUnexpectedError;
	}

	int32_t separatorLength = withSeparator ? 1 : 0;

	Array_t<char> dest;
	
	status = dest.Initialise(input1.Length() + separatorLength + input2.Length() + 1); //1 for '\0'
	if (status.IsBad())
	{
		return status;
	}

	char* destination = dest.Value();
	if (!destination)
	{
		return OpcUa_BadUnexpectedError;
	}

	//Add inputString1 to destination
	if (UASDK_memcpy(destination, inputString1->Value(), input1.Length()) != destination)
	{
		return OpcUa_BadUnexpectedError;
	}
	destination = destination + input1.Length();

	//Add separator to destination
	if (withSeparator)
	{
		*destination = separator;
		destination++;
	}

	//Add inputString2 to destination
	if (UASDK_memcpy(destination, inputString2->Value(), input2.Length()) != destination)
	{
		return OpcUa_BadUnexpectedError;
	}
	destination = destination + input2.Length();

	if (!destination)
	{
		return OpcUa_BadUnexpectedError;
	}

	*destination = '\0';

	return result.CopyFrom(dest.Value());
}


} //namespace uasdk
