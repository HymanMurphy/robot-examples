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

#include "content_filter_element_like_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "ua_system_calls.h"
#include "opcua_boolean_t.h"

namespace uasdk
{
  
UA_DEFINE_RUNTIME_TYPE(ContentFilterElement_Like_t, ContentFilterElement_t);

ContentFilterElement_Like_t::ContentFilterElement_Like_t() :
  ContentFilterElement_t(FilterOperator_t::FILTER_OP_LIKE),
  isCompiled(false), isValid(false), stateTable(Array_t<ParsingState_t>()), numStates(0)
{
}

ContentFilterElement_Like_t::~ContentFilterElement_Like_t()
{
}

uint32_t  ContentFilterElement_Like_t::MinimumOperandCount(void) const
{
	return 2;
}

uint32_t  ContentFilterElement_Like_t::MaximumOperandCount(void) const
{
	return 2;
}

Status_t ContentFilterElement_Like_t::ApplyFilterElement(const INode_t& node, IContentFilter_t* filter, IntrusivePtr_t<IAttributeAccess_t>& eventAttributes, IntrusivePtr_t<IServerConfiguration_t> configuration, IntrusivePtr_t<BaseDataType_t>& evaluationResult, IntrusivePtr_t<ContentFilterElementResult_t>& elementResult, bool diagnosticsRequested)
{
	//Two inputs, both must resolve to a string (UTF8)
	//input 0 is the target
	//input 1 is the pattern.
  IntrusivePtr_t<BaseDataType_t> dest;
  uint16_t namespaceIndex1 = 0;
  uint16_t namespaceIndex2 = 0;
  Status_t status = OpcUa_Good;

  status = CheckApplyFilterElementArguments(filter, eventAttributes, evaluationResult, elementResult, diagnosticsRequested);

  if (status.IsBad())
  {
    return status;
  }

	IntrusivePtr_t<BaseDataType_t> value1, value2;
	status = GetValidFilterOperandValue(0, node, filter, eventAttributes, configuration, value1, elementResult, diagnosticsRequested);

	if (status.IsBad())
	{
		return status;
	}

	status = GetValidFilterOperandValue(1, node, filter, eventAttributes, configuration, value2, elementResult, diagnosticsRequested);

	if (status.IsBad())
	{
		return status;
	}

  IntrusivePtr_t<String_t> stringValue1;
  if(value1->TypeId(namespaceIndex1) == OpcUaId_String )
  {
    stringValue1 = RuntimeCast<String_t*>(*value1);
  }
  else
  {
    IntrusivePtr_t<BaseDataType_t> dest = stringValue1;
    status = TypeConversionRule(value1, dest);
  }

	if (status.IsBad())
  {
    return status;
  }

  IntrusivePtr_t<String_t> stringValue2;
  if (value2->TypeId(namespaceIndex2) == OpcUaId_String)
  {
    stringValue2 = RuntimeCast<String_t*>(*value2);
  }
  else
  {
    IntrusivePtr_t<BaseDataType_t> dest = stringValue2;
    status = TypeConversionRule(value2, dest);
  }

	if (status.IsBad())
  {
    return status;
  }
  
	if (false == isCompiled)
	{
		//Decode input 1 to a string, and pass to the compiler
		isValid = CompileEpsilonNFA(stringValue2->Payload().Data(), stringValue2->Payload().Length());
#ifdef DEBUG_LIKE_DFA
    LOG_INFO("\n\nEpsilonNFA:");
    DumpStateTable();
#endif
	
    if(true == isValid)
    isCompiled = CompileEpsilonNFAToDFA();

#ifdef DEBUG_LIKE_DFA
    LOG_INFO("\n\nEpsilonDFA:");
    DumpStateTable();
#endif
  }

  if(true == isValid)
  {    
		//decode input 0 to a string, and execute the compiled match.
		bool matchResult = Match(stringValue1->Payload().Data(), stringValue1->Payload().Length());
    //Setting the out paramaters
    if (status.IsGood())
    {
      IntrusivePtr_t<Boolean_t> result = new SafeRefCount_t<Boolean_t>();
      if (!result.is_set())
      {
        status = OpcUa_BadOutOfMemory;
      }
      else
      {
        status = result->Value(matchResult==true);

        if (status.IsGood())
        {
          status = result->CopyTo(evaluationResult);
        }
      }
    }

    elementResult->StatusCode() = status;
    //Fill the result if any failure occurred after Type Conversion
    if (status.IsBad())
    {
      elementResult->OperandStatusCodes()[0]->Value() = status.Value();
      elementResult->OperandStatusCodes()[1]->Value() = status.Value();
    }

    return status;
  }	
	else
	{
		return OpcUa_BadFilterOperandInvalid; //failed to compile the dfa?
	}
  
	return OpcUa_Good;
}

Status_t ContentFilterElement_Like_t::CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const
{
	return CopyToDestination(*this, destination);
}

Status_t ContentFilterElement_Like_t::CopyFrom(const BaseDataType_t& source)
{
	IntrusivePtr_t<const ContentFilterElement_Like_t> ptr = RuntimeCast<const ContentFilterElement_Like_t*>(source);
	if (!ptr.is_set())
	{
		return OpcUa_BadTypeMismatch;
	}

	return CopyFrom(*ptr);
}

Status_t ContentFilterElement_Like_t::CopyFrom(const ContentFilterElement_Like_t& source)
{
	Status_t status = FilterOperands().CopyFrom(source.FilterOperands());
	if (status.IsBad())
	{
		return status;
	}

	return OpcUa_Good;
}

Status_t ContentFilterElement_Like_t::ResetStateTable()
{

  if (stateTable.Initialised())
  {
    stateTable.Resize(0);
    stateTable.Resize(5);
  }
  else
  {
    stateTable.Initialise(5);
  }

  return OpcUa_Good;
}

//This is a simplified regexp, with no alternate paths.
// Need to construct an FSA.
// Input symbol set: UTF8
bool ContentFilterElement_Like_t::CompileEpsilonNFA(const uint8_t *data, const int32_t length)
{
  bool valid = true;

  ResetStateTable();
  //First stage:  Generate the epsilon-NFA.
  uint16_t currentState = AddNewState("start");
  if (currentState == 0) return false;

  int32_t pos = 0;

  while (pos < length && valid == true)
  {
    if (data[pos] == '_')
    {
      currentState = GenerateNFARule_wildcard(currentState, false);
      ++pos;
    }
    else if(data[pos] == '%')
    {
      currentState = GenerateNFARule_wildcard(currentState, true);
      ++pos;
    }
    else if (data[pos] == '\\' )
    {
      ++pos;
      if (pos < length)
      {
        currentState = GenerateNFARule_simpleChar(currentState, data[pos]);
        ++pos;
      }
      else
      {
        valid = false;
        break;
      }
    }
    else if (data[pos] == '[')
    {
      //Find the end of the [...] char list, accounting for the fact that \] is a valid member of the list.
      int32_t tmpPos;
      bool escaped = false;
      for (tmpPos = pos + 1; tmpPos < length; ++tmpPos)
      {
        if (escaped == false)
        {
          if (data[tmpPos] == '\\')
          {
            escaped = true;
          }
          else if (data[tmpPos] == ']')
          {
            break;
          }
        }
        else
        {
          escaped = false;
        }
      }

      if (tmpPos < length && tmpPos > pos + 1)
      {
        currentState = GenerateNFARule_charList(currentState, &data[pos + 1], tmpPos - pos - 1);
        pos = tmpPos + 1;
      }
      else
      {
        valid = false;
        break;
      }
    }
    else if (data[pos] <= UTF8_NRM_END)
    {
      currentState = GenerateNFARule_simpleChar(currentState, data[pos]);
      ++pos;
    }
    else if (
      UTF8_EXT_START2 == (data[pos] & ContentFilterElement_Like_t::UTF8_EXT_START2_MASK)
      || UTF8_EXT_START3 == (data[pos] & ContentFilterElement_Like_t::UTF8_EXT_START3_MASK)
      || UTF8_EXT_START4 == (data[pos] & ContentFilterElement_Like_t::UTF8_EXT_START4_MASK)
      )
    {
      int32_t consumedBytes = 0;
      UTF8Decode(&data[pos], length - pos, consumedBytes);
      //Just verify it is a valid UTF-8 extended symbol.
      if (consumedBytes > 0)
      {
        currentState = GenerateNFARule_sequence(currentState, &data[pos], consumedBytes);
        pos += consumedBytes;
      }
      else
      {
        valid = false;
        break;
      }     
    }

    if (currentState == 0)
    {
      valid = false; //ended up in a bad state, or ran out of states.  
    }
  }

  //The final state in this case is always a terminal state
  //In a more complex system, there are many ways to accept and exit, but this is just a compiled string match.
  if (valid == true)
  {
    stateTable[currentState].accept = true;
  }

  return valid;
}

bool ContentFilterElement_Like_t::CompileEpsilonNFAToDFA()
{ 
  for (uint16_t i = 1; i <= numStates; ++i)
  {
    ComputeClosure(stateTable[i].closures);
  }
  return true;
}

bool ContentFilterElement_Like_t::ComputeClosure(Hash_Set_t<uint16_t> &set)
{
  /* Implements closure(S) per "Modern Compiler Implementation in C" -- Andrew A. Appel*/  
  Hash_Set_t<uint16_t> T;
  Hash_Set_t<uint16_t> Tprime;

  T.Initialise(ParsingState_t::CLOSURE_NUM_BUCKETS);
  T.Add(set);
  Status_t status = OpcUa_Good;

  do
  {
    //T <-- T'
    Tprime.Initialise(ParsingState_t::CLOSURE_NUM_BUCKETS);
    Tprime.Add(T);
    //Add all possible states from each closure state.

    // T <-- T' union (closures of all states in T')
    uint16_t * epsilonTransition = Tprime.GetFirst();
    while (epsilonTransition != NULL)
    {
      status = T.Add(stateTable[*epsilonTransition].closures);

      epsilonTransition = Tprime.GetNext();
    }
   
  } while (T != Tprime && false == status.IsOutOfMemory()); //keep going until nothing changes
  
  if(status.IsGood())
  {
    set = T;
    return true;
  };

  return false;
}


#ifdef DEBUG_LIKE_DFA

void ContentFilterElement_Like_t::DumpStateTable()
{
  LOG_INFO("\n-----------------------------------------------\nNumStates=%d", numStates);
  for (uint16_t i = 1; i <= numStates; ++i)
  {
    LOG_INFO("\nstate[%hu] (accept=%d) %s : \n  closures: ", i, stateTable[i].accept, stateTable[i].comment);
    DumpSet(stateTable[i].closures);
    LOG_INFO("\n{");
    for (uint16_t j = 0; j < ParsingState_t::STATE_TABLE_EDGES; ++j)
    {
      if (j % 32 == 0)
      {
        LOG_INFO("\n (0x%02x) ", j);
      }
      else if (j % 8 == 0)
      {
        LOG_INFO("  (0x%02x) ", j);
      }
      if (stateTable[i].edges[j] == 0)
      {
        LOG_INFO("__,"); //make zeros fade out, not important
      }
      else
      {
        LOG_INFO("%2hhu,", stateTable[i].edges[j]);
      }
    }
    LOG_INFO("}\n");
  }
}

void ContentFilterElement_Like_t::DumpSet(Hash_Set_t<uint16_t> & set)
{
  uint16_t * item = set.GetFirst();

  LOG_INFO("{");
  while(item != NULL)
  {
    LOG_INFO("%hu,", *item);
    item = set.GetNext();
  }

  LOG_INFO("}");
}
#endif

Status_t ContentFilterElement_Like_t::DFAEdge(Hash_Set_t<uint16_t> & currentStates, uint8_t symbol, /* OUT */ Hash_Set_t<uint16_t>& newPossibleStates)
{
  newPossibleStates.Initialise(ParsingState_t::CLOSURE_NUM_BUCKETS);
  uint16_t * currentStateItem = currentStates.GetFirst();
  while (currentStateItem != NULL)
  {
    uint16_t possibleState = stateTable[*currentStateItem].edges[symbol];
    if (possibleState != 0)
    {
      newPossibleStates.Add(possibleState);
      newPossibleStates.Add(stateTable[possibleState].closures);
    }

    currentStateItem = currentStates.GetNext();
  }

  return OpcUa_Good;
}

bool ContentFilterElement_Like_t::Match(const uint8_t *data, const int32_t length)
{
  Hash_Set_t<uint16_t> possibleStates;
  Hash_Set_t<uint16_t> newPossibleStates;
  newPossibleStates.Initialise(ParsingState_t::CLOSURE_NUM_BUCKETS);
  possibleStates.Initialise(ParsingState_t::CLOSURE_NUM_BUCKETS);
  possibleStates.Add(stateTable[1].closures);

  Status_t status = OpcUa_Good;

  for (int32_t symbolIndex = 0; symbolIndex < length && status.IsGood(); ++symbolIndex)
  {
  	status = DFAEdge(possibleStates, data[symbolIndex], newPossibleStates);
#ifdef DEBUG_LIKE_DFA
    LOG_INFO("\n match pass %u: symbol '%c' \\x%02x incoming possible states", symbolIndex, data[symbolIndex], data[symbolIndex]);
  	DumpSet(possibleStates);
    LOG_INFO(", new possible states");
  	DumpSet(newPossibleStates);
#endif

  	possibleStates = newPossibleStates;
  	newPossibleStates.Initialise(ParsingState_t::CLOSURE_NUM_BUCKETS); //Reset so that the next pass doesn't hold past possible states.
  }

  uint16_t * resultState = possibleStates.GetFirst();
  while (resultState != NULL)
  {
    if (*resultState > 0 && *resultState <= numStates && stateTable[*resultState].accept == true)
    {
      //if any of the possible states we are in is acceptable, then we have a match.
      return true;
    }

    resultState = possibleStates.GetNext();
  }

  return false;
}

//Handles the [...] pick-one-of type.
uint16_t ContentFilterElement_Like_t::GenerateNFARule_charList(uint16_t startingState, const uint8_t *data, int32_t len)
{
  //The input here is just the inside of the [...] (i.e. the ...)
  uint16_t entryState = 0;
  uint16_t endState = 0;
  bool inverse = false;
  int32_t pos = 0;
  uint16_t u21 = 0;
  uint16_t u31 = 0, u32 = 0;
  uint16_t u41 = 0, u42 = 0, u43 = 0;

  if (data[0] == '^')
  {
    inverse = true;
    entryState = AddNewState("SelectInverseE");
    u41 = AddNewState("SelectInverseU41");
    u42 = AddNewState("SelectInverseU42");
    u43 = AddNewState("SelectInverseU43");
    u31 = AddNewState("SelectInverseU31");
    u32 = AddNewState("SelectInverseU32");
    u21 = AddNewState("SelectInverseU21");
    endState = AddNewState("SelectInverseExit");
    pos = 1; // skip this char 
  }
  else
  {
    inverse = false;
    entryState = AddNewState("SelectEnter");
    u41 = AddNewState("SelectU41");
    u42 = AddNewState("SelectU42");
    u43 = AddNewState("SelectU43");
    u31 = AddNewState("SelectU31");
    u32 = AddNewState("SelectU32");
    u21 = AddNewState("SelectU21");
    endState = AddNewState("SelectExit");
  }

  if (entryState == 0)
  {
  	return 0;
  }

  if (u41 == 0)
  {
  	return 0;
  }

  if (u42 == 0)
  {
  	return 0;
  }

  if (u43 == 0)
  {
  	return 0;
  }

  if (u31 == 0)
  {
  	return 0;
  }

  if (u32 == 0)
  {
  	return 0;
  }

  if (u21 == 0)
  {
  	return 0;
  }
  
  if (endState == 0)
  {
  	return 0;
  }

  if (inverse)
  {
    //Precondition the edges so invalid edges can be removed.
    for (uint16_t i = 0; i <= ContentFilterElement_Like_t::UTF8_NRM_END; ++i)
    {
      stateTable[entryState].edges[i] = endState;
    }

    for (uint16_t i = UTF8_EXT_START2; i <= ContentFilterElement_Like_t::UTF8_EXT_END2; ++i)
    {
      stateTable[entryState].edges[i] = u21;
    }

    for (uint16_t i = UTF8_EXT_START; i <= ContentFilterElement_Like_t::UTF8_EXT_END; ++i)
    {
      stateTable[u21].edges[i] = endState;
    }

    //3 byte states plug into the 2 byte states to finish.
    for (uint16_t i = UTF8_EXT_START3; i <= ContentFilterElement_Like_t::UTF8_EXT_END3; ++i)
    {
      stateTable[entryState].edges[i] = u31;
    }

    for (uint16_t i = UTF8_EXT_START; i <= ContentFilterElement_Like_t::UTF8_EXT_END; ++i)
    {
      stateTable[u31].edges[i] = u32;
    }

    for (uint16_t i = UTF8_EXT_START; i <= ContentFilterElement_Like_t::UTF8_EXT_END; ++i)
    {
      stateTable[u32].edges[i] = endState;
    }

    //4 byte states plug into the 3 byte states to finish
    for (uint16_t i = UTF8_EXT_START4; i <= ContentFilterElement_Like_t::UTF8_EXT_END4; ++i)
    {
      stateTable[entryState].edges[i] = u41;
    }

    for (uint16_t i = UTF8_EXT_START; i <= ContentFilterElement_Like_t::UTF8_EXT_END; ++i)
    {
      stateTable[u41].edges[i] = u42;
    }

    for (uint16_t i = UTF8_EXT_START; i <= ContentFilterElement_Like_t::UTF8_EXT_END; ++i)
    {
      stateTable[u42].edges[i] = u43;
    }

    for (uint16_t i = UTF8_EXT_START; i <= ContentFilterElement_Like_t::UTF8_EXT_END; ++i)
    {
      stateTable[u43].edges[i] = endState;
    }
  }

  stateTable[startingState].closures.Add(entryState);

  //Scan forward.  If - is hit, interpolate.
  // if escapes or UTF8 do show up, consume them in a single pass.

  char unicodeBuffer[6] = { 0 };

  bool inRange = false;
  uint32_t lastChar = 0;
  uint32_t currentChar = 0;

  for (; pos < len; ++pos)
  {
    if (((data[pos] & UTF8_EXT_START4_MASK) == UTF8_EXT_START4)
      || ((data[pos] & UTF8_EXT_START3_MASK) == UTF8_EXT_START3)
      || ((data[pos] & UTF8_EXT_START2_MASK) == UTF8_EXT_START2))
    {
      int32_t consumedBytes = 0;
      currentChar = UTF8Decode(&data[pos], len - pos, consumedBytes);
      if (consumedBytes > 0)
      {
        pos += consumedBytes-1;
      }
      else
      {
        return 0;
      }
    }
    else if (data[pos] == '\\')
    {
      ++pos;
      currentChar = data[pos];

      switch (currentChar)
      {
        case '%':
        case '_':
        case '\\':
        case '[':
        case '-':
        case ']':
        case '^':
          break;

        default:
          return 0;  //invalid escape char.
      }
    }
    else if (data[pos] == '-')
    {
      if (inRange)
      {
        //Processed --, not legal.
        return 0;
      }
      inRange = true;
      continue;
    }
    else
    {
      currentChar = data[pos];
    }

    if (inRange)
    {
      //Process the whole range.  Actually, the first member of the range is already done.
      if (pos > 1 && currentChar > lastChar)
      {
        for (uint32_t i = lastChar + 1; i <= currentChar; ++i)
        {
          if (i <= UTF8_NRM_END)
          {
            stateTable[entryState].edges[(uint8_t)i] = inverse ? 0 : endState;
          }
          else
          {
            uint32_t bytes = UTF8Encode(i, 6, (uint8_t*)&unicodeBuffer[0]);
            if (bytes > 0)
            {
              switch (bytes)
              {
                case 4:
                  stateTable[entryState].edges[(uint8_t)unicodeBuffer[0]] = inverse ? 0 : u41;
                  stateTable[u41].edges[(uint8_t)unicodeBuffer[1]] = inverse ? 0 : u42;
                  stateTable[u42].edges[(uint8_t)unicodeBuffer[2]] = inverse ? 0 : u43;
                  stateTable[u43].edges[(uint8_t)unicodeBuffer[3]] = inverse ? 0 : endState;
                  break;
                case 3:
                  stateTable[entryState].edges[(uint8_t)unicodeBuffer[0]] = inverse ? 0 : u31;
                  stateTable[u31].edges[(uint8_t)unicodeBuffer[1]] = inverse ? 0 : u32;
                  stateTable[u32].edges[(uint8_t)unicodeBuffer[2]] = inverse ? 0 : endState;
                  break;
                case 2:
                  stateTable[entryState].edges[(uint8_t)unicodeBuffer[0]] = inverse ? 0 : u21;
                  stateTable[u21].edges[(uint8_t)unicodeBuffer[1]] = inverse ? 0 : endState;
                  break;
                default:
                  return 0;
              }
            }
            else
            {
              return 0;
            }
          }
        }
        lastChar = currentChar;
      }
      else
      {
        return 0; //Invalid string.
      }
      inRange = false;

    }
    else
    {
      if (currentChar <= UTF8_NRM_END)
      {
        stateTable[entryState].edges[(uint8_t)currentChar] = inverse ? 0 : endState;
      }
      else
      {
        int32_t bytes = UTF8Encode(currentChar, 6, (uint8_t*)&unicodeBuffer[0]);
        if (bytes > 0)
        {
          switch (bytes)
          {
            case 4:
              stateTable[entryState].edges[(uint8_t)unicodeBuffer[0]] = inverse ? 0 : u41;
              stateTable[u41].edges[(uint8_t)unicodeBuffer[1]] = inverse ? 0 : u42;
              stateTable[u42].edges[(uint8_t)unicodeBuffer[2]] = inverse ? 0 : u43;
              stateTable[u43].edges[(uint8_t)unicodeBuffer[3]] = inverse ? 0 : endState;
              break;
            case 3:
              stateTable[entryState].edges[(uint8_t)unicodeBuffer[0]] = inverse ? 0 : u31;
              stateTable[u31].edges[(uint8_t)unicodeBuffer[1]] = inverse ? 0 : u32;
              stateTable[u32].edges[(uint8_t)unicodeBuffer[2]] = inverse ? 0 : endState;
              break;
            case 2:
              stateTable[entryState].edges[(uint8_t)unicodeBuffer[0]] = inverse ? 0 : u21;
              stateTable[u21].edges[(uint8_t)unicodeBuffer[1]] = inverse ? 0 : endState;
              break;
            default:
              return 0;
          }
        }
      }
      lastChar = currentChar;
    }
  }

  if (inRange == true)
  {
    //Invalid pattern.
    return 0;
  }

  return endState;
}

// A simple charactor generates a edge to a new state.
uint16_t ContentFilterElement_Like_t::GenerateNFARule_simpleChar(uint16_t currentState, uint8_t symbol)
{
   if (0 == stateTable[currentState].edges[symbol])
    {
      uint16_t newState = AddNewState("simple");
      if (newState == 0) return 0;
      stateTable[currentState].edges[symbol] = newState;

      return newState;
    }
    else
    {
      //This is allowed, to help automatically compress possible UTF8 extension states
      return stateTable[currentState].edges[symbol];
    }
}

//Adds states for a sequence of charactors, returning the final state at the end of the sequence.
//This is written for UTF8's for sure
uint16_t ContentFilterElement_Like_t::GenerateNFARule_sequence(uint16_t startingState, const uint8_t * sequence, int32_t sequenceLength)
{
  if (sequence != NULL)
  {
    uint16_t currentState = startingState;
    for (int32_t i = 0; i < sequenceLength && currentState != 0; ++i)
    {
      currentState = GenerateNFARule_simpleChar(currentState, sequence[i]);
    }

    return currentState;
  }
  else
  {
    return 0;
  }
}

uint16_t ContentFilterElement_Like_t::AddNewState(const char* comment)
{
  uint16_t newState = ++numStates;
  if (newState >= stateTable.Count())
  {
    //Don't grow every time - that would cause a lot of reallocations.
    Status_t status = stateTable.Resize(stateTable.Count() + ContentFilterElement_Like_t::STATE_TABLE_GROWTH);
    if (status.IsBad())
    {
      //Most likely out of memory.
      return 0;
    }
  }
 
  stateTable[newState].closures.Add(newState); //every state is closed to itself.

#ifdef DEBUG_LIKE_DFA

  if (comment != 0)
  {
    UASDK_memcpy(stateTable[newState].comment, (void *)comment, strlen(comment)+1);
  }
  else
  {
    stateTable[newState].comment[0] =0;
  }
#else
  UASDK_UNUSED(comment);
#endif

  return newState;
}

//Handle the _ wildcard. next valid state is any valid character.  Needs to handle unicode extensions as well.
uint16_t ContentFilterElement_Like_t::GenerateNFARule_wildcard(uint16_t startingState, bool loop)
{  
  uint16_t wildcardState = AddNewState("wildcardState");
  if (wildcardState == 0) return 0;
  stateTable[startingState].closures.Add(wildcardState);

  //Create the intermediate UTF8 states.  Assumes valid UTF8 encodings anyways.
  uint16_t U4state = AddNewState("u4");
  if (U4state == 0) return 0;
  
  uint16_t U3state = AddNewState("u3");
  if (U3state == 0) return 0;

  uint16_t U2state = AddNewState("u2");
  if (U2state == 0) return 0;

  //Insert the epsilon transition.  The compiler should will resolve this later.  

  uint16_t endState = AddNewState("wildcardEnd");
  if (endState == 0) return 0;

  //If this is for a % (multi wild), the end state is a loop back to the wildcard state (which is an epsilon state.)
  if (true == loop)
  {
    stateTable[endState].closures.Add(wildcardState);
    //Also, in a % state, we can skip from wildcard to endstate as an epsilon, since % allows nothing.
    stateTable[wildcardState].closures.Add(endState);
  }  

  //First, any valid non utf8 symbol goes to the end state
  for (uint8_t i = UTF8_NRM_START; i <= ContentFilterElement_Like_t::UTF8_NRM_END; ++i)
  {
    stateTable[wildcardState].edges[i] = endState;
  }

  //Yes this can probably be optimized a lot, but writing it correctly and clearly first.
  // So, a wildcard lookes somthing like this:
  //
  /*

     eps-->()---any valid ascii 7 bit--------------------
          |                                                 \
          +----->U4 start --->(needs 3 more)                |
          |                       |                         |
          |                      ext byte                   |
          |                       V                         |
          +---->U3 start----->(needs 2 more)                |
          |                       |                         |
          |                      ext byte                   |
          |                       V                         |
          +---->U2 start----->(needs 1 more)------ext byte--+->(end state)



  */
  
  //2 byte UTF8 - needs one valid extension byte
  for (uint16_t i = UTF8_EXT_START2; i <= ContentFilterElement_Like_t::UTF8_EXT_END2; ++i)
  {
    stateTable[wildcardState].edges[i] = U2state;
  }

  for (uint16_t i = UTF8_EXT_START; i <= ContentFilterElement_Like_t::UTF8_EXT_END; ++i)
  {
    stateTable[U2state].edges[i]= endState;
  }

  //3 byte states plug into the 2 byte states to finish.
  for (uint16_t i = UTF8_EXT_START3; i <= ContentFilterElement_Like_t::UTF8_EXT_END3; ++i)
  {
    stateTable[wildcardState].edges[i]= U3state;
  }

  for (uint16_t i = UTF8_EXT_START; i <= ContentFilterElement_Like_t::UTF8_EXT_END; ++i)
  {
    stateTable[U3state].edges[i]= U2state;
  }

  //4 byte states plug into the 3 byte states to finish
  for (uint16_t i = UTF8_EXT_START4; i <= ContentFilterElement_Like_t::UTF8_EXT_END4; ++i)
  {
    stateTable[wildcardState].edges[i]= U4state;
  }

  for (uint16_t i = UTF8_EXT_START; i <= ContentFilterElement_Like_t::UTF8_EXT_END; ++i)
  {
    stateTable[U4state].edges[i]= U3state;
  }

  return endState;  
}


uint32_t ContentFilterElement_Like_t::UTF8Decode(const uint8_t * data, int32_t length,  /*OUT*/ int32_t & consumedBytes) const
{
  //Note that UA Spec for string specifies "UTF-8" which can encode code points of up to 21 bits, so, uint32 is required.
  uint32_t codePoint = 0;
  consumedBytes = 0;
  if (length < 1 || NULL == data)
  {
    return 0;
  }

  if ((data[0] & UTF8_EXT_START4_MASK) == UTF8_EXT_START4)
  {
    if (length < 4)
    {
      return 0;
    }
    consumedBytes = 4;
    codePoint = (uint32_t)(data[0] & (~UTF8_EXT_START4_MASK));
  }

  else if ((data[0] & UTF8_EXT_START3_MASK) == UTF8_EXT_START3)
  {
    if (length < 3)
    {
      return 0;
    }
    consumedBytes = 3;
    codePoint = data[0] & (~UTF8_EXT_START3_MASK);
  }

  else if ((data[0] & UTF8_EXT_START2_MASK) == UTF8_EXT_START2)
  {
    if (length < 2)
    {
      return 0;
    }
    consumedBytes = 2;
    codePoint = data[0] & (~UTF8_EXT_START2_MASK);
  }
    
  //Each extension byte is 6 more bits.
  for (int32_t i = 1; i < consumedBytes; ++i)
  {
    if ((data[i] & UTF8_EXT_MASK) == UTF8_EXT_START)
    {
      codePoint = (codePoint << UTF8_EXT_BITS) | (data[i] & (~UTF8_EXT_MASK));
    }
    else
    {
      consumedBytes = 0;
      return 0;
    }
  }

  return codePoint;
}

uint32_t ContentFilterElement_Like_t::UTF8Encode(uint32_t codePoint, int32_t maxLength, /* OUT */ uint8_t * sequence) const
{
  uint32_t bytes = 0;

  if (NULL == sequence || maxLength < 1)
  {
    return 0;
  }

  if (codePoint <= UTF8_NRM_END)
  {
    bytes = 1;
    sequence[0] = codePoint & ContentFilterElement_Like_t::UTF8_NRM_MASK;
  }
  else if (codePoint >= ContentFilterElement_Like_t::UTF8_EXT_FIRST_SYMBOL2 && codePoint <= ContentFilterElement_Like_t::UTF8_EXT_LAST_SYMBOL2 && maxLength >= 2)
  {
    bytes = 2;
    sequence[1] = ContentFilterElement_Like_t::UTF8_EXT_START | (codePoint & (~ContentFilterElement_Like_t::UTF8_EXT_MASK));
    codePoint >>=UTF8_EXT_BITS;
    sequence[0] = ContentFilterElement_Like_t::UTF8_EXT_START2 | (codePoint & (~ContentFilterElement_Like_t::UTF8_EXT_START2_MASK));
  }
  else if (codePoint >= ContentFilterElement_Like_t::UTF8_EXT_FIRST_SYMBOL3 && codePoint <= ContentFilterElement_Like_t::UTF8_EXT_LAST_SYMBOL3 && maxLength >= 3)
  {
    bytes = 3;
    sequence[2] = ContentFilterElement_Like_t::UTF8_EXT_START | (codePoint & (~ContentFilterElement_Like_t::UTF8_EXT_MASK));
    codePoint >>= 6;
    sequence[1] = ContentFilterElement_Like_t::UTF8_EXT_START | (codePoint & (~ContentFilterElement_Like_t::UTF8_EXT_MASK));
    codePoint >>= 6;
    sequence[0] = ContentFilterElement_Like_t::UTF8_EXT_START3 | (codePoint & (~ContentFilterElement_Like_t::UTF8_EXT_START3_MASK));
  }
  else if (codePoint >= ContentFilterElement_Like_t::UTF8_EXT_FIRST_SYMBOL4 && codePoint <= ContentFilterElement_Like_t::UTF8_EXT_LAST_SYMBOL4 && maxLength >= 4)
  {
    bytes = 4;
    sequence[3] = ContentFilterElement_Like_t::UTF8_EXT_START | (codePoint & (~ContentFilterElement_Like_t::UTF8_EXT_MASK));
    codePoint >>= 6;
    sequence[2] = ContentFilterElement_Like_t::UTF8_EXT_START | (codePoint & (~ContentFilterElement_Like_t::UTF8_EXT_MASK));
    codePoint >>= 6;
    sequence[1] = ContentFilterElement_Like_t::UTF8_EXT_START | (codePoint & (~ContentFilterElement_Like_t::UTF8_EXT_MASK));
    codePoint >>= 6;
    sequence[0] = ContentFilterElement_Like_t::UTF8_EXT_START4 | (codePoint & (~ContentFilterElement_Like_t::UTF8_EXT_START4_MASK));
  }
  else
  {
    bytes = 0;
  }
  return bytes;
}

ParsingState_t::ParsingState_t(): accept(false)
{
  UASDK_memset(edges, 0, sizeof(uint16_t) * ParsingState_t::STATE_TABLE_EDGES);
  closures.Initialise(CLOSURE_NUM_BUCKETS);
}

ParsingState_t::ParsingState_t(const ParsingState_t & copy)
{
  accept = copy.accept;
  UASDK_memcpy(edges, copy.edges, sizeof(uint16_t) * ParsingState_t::STATE_TABLE_EDGES);
  Status_t status = closures.Initialise(ParsingState_t::CLOSURE_NUM_BUCKETS);
  if (status.IsGood())
  {
    status = closures.Add(const_cast<Hash_Set_t<uint16_t> &>(copy.closures));
  }
#ifdef DEBUG_LIKE_DFA
  if (status.IsGood())
  {
    UASDK_memcpy(comment, copy.comment, sizeof(comment));
  }
#endif

}


ParsingState_t::~ParsingState_t()
{
}

} // namespace uasdk

#endif // UASDK_INCLUDE_EVENTS
