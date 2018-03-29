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

#ifndef _CONTENT_FILTER_ELEMENT_LIKE_T_
#define _CONTENT_FILTER_ELEMENT_LIKE_T_

#include "content_filter_element_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "hash_set_t.h"
#include "array_t.h"

//This turns on a lot of extra debugging printf's to examine the state transistions.  Generally don't need it.
//#define DEBUG_LIKE_DFA

namespace uasdk
{

class ParsingState_t
{
public:
	ParsingState_t();
	~ParsingState_t();
	ParsingState_t(const ParsingState_t & copy);

	static const uint16_t STATE_TABLE_MAX = 255;
	static const uint16_t STATE_TABLE_EDGES = 256;
	static const uint16_t CLOSURE_NUM_BUCKETS = 64;

	uint16_t edges[ParsingState_t::STATE_TABLE_EDGES];
	bool accept;
	//0 means DFA, >0 means that edges[0,epsilonCount) are potential epsilon states.
	Hash_Set_t<uint16_t> closures;
#ifdef DEBUG_LIKE_DFA
	char comment[16];
#endif

};

/** \addtogroup grpEventsandAC
*@{*/

/*****************************************************************************/
/** \brief ContentFilterElement_Like_t
*
* This class implements the Like operator in Content Filter
*
*/
class ContentFilterElement_Like_t : public ContentFilterElement_t
{
protected:

  static const uint8_t UTF8_NRM_START = 0x00;
  static const uint8_t UTF8_NRM_END = 0x7F;
  static const uint8_t UTF8_NRM_MASK = 0x7F;
  
  //2 byte UTF8 start: 110x xxxx
  //             mask: 1110 0000
  static const uint8_t UTF8_EXT_START2 = 0xC0;
  static const uint8_t UTF8_EXT_END2 = 0xDF;
  static const uint8_t UTF8_EXT_START2_BITS = 5; 
  static const uint8_t UTF8_EXT_START2_MASK = 0xE0;
  static const uint32_t UTF8_EXT_FIRST_SYMBOL2 = 0x0080;
  static const uint32_t UTF8_EXT_LAST_SYMBOL2 = 0x07FF;

  //3 byte UTF8 start: 1110 xxxx
  //            mask:  1111 0000
  static const uint8_t UTF8_EXT_START3 = 0xE0;
  static const uint8_t UTF8_EXT_END3 = 0xEF;
  static const uint8_t UTF8_EXT_START3_BITS = 4;
  static const uint8_t UTF8_EXT_START3_MASK = 0xF0;
  static const uint32_t UTF8_EXT_FIRST_SYMBOL3 = 0x0800;
  static const uint32_t UTF8_EXT_LAST_SYMBOL3 = 0xFFFF;

  //4 byte UTF8 start: 1111 0xxx
  //             mask: 1111 1000
  static const uint8_t UTF8_EXT_START4 = 0xF0;
  static const uint8_t UTF8_EXT_END4 = 0xF7;
  static const uint8_t UTF8_EXT_START4_MASK = 0xF8;
  static const uint8_t UTF8_EXT_START4_BITS = 3;
  static const uint32_t UTF8_EXT_FIRST_SYMBOL4 = 0x10000;
  static const uint32_t UTF8_EXT_LAST_SYMBOL4 = 0x1FFFFF;

  //UTF 8 extension byte start= 10xx xxxx
  //                      mask= 1100 0000
  static const uint8_t UTF8_EXT_START = 0x80; //All extended code bytes have this flag but the first
  static const uint8_t UTF8_EXT_END = 0xBF; //All extended code bytes have this flag but the first
  static const uint8_t UTF8_EXT_MASK = 0xC0;
  static const uint8_t UTF8_EXT_BITS = 6; //7 useable bits per extension byte.

public:
  UA_DECLARE_RUNTIME_TYPE(ContentFilterElement_Like_t);

	/*****************************************************************************/
	/** Constructor for the class.
	*
	*/
	ContentFilterElement_Like_t();

	/*****************************************************************************/
	/** Destructor for the class.
	*
	*/
	virtual ~ContentFilterElement_Like_t();

	/*****************************************************************************/
	/** Get the minimum number of operands for this operator
	*
	* @return
	* Returns the minimum number of operands for this operator
	*/
	uint32_t MinimumOperandCount(void) const;

	/*****************************************************************************/
	/** Get the maximum number of operands for this operator
	*
	* @return
	* Returns the maximum number of operands for this operator
	*/
	uint32_t MaximumOperandCount(void) const;
  
	/******************************************************************************************************/
	/** Processes this filter element and obtains the result of evaluating the filter against the provided node
	*
	* @param[in] node
	* node is the node to pass through the filter
	*
	* @param[in] filter
	* filter the content filter owning this element.  This is used by the ElementOperand when a sub element is referenced
	*
	* @param[in] eventAttributes
	* eventAttributes is the event instance. This is used by the SimpleAttributeOperand to get the attribute values based on the input parameters.
	*
	* @param[in] configuration
	* configuration is the instance of server configuration
	*
	* @param[out] evaluationResult
	* evaluationResult is the result of the evaluation.  May be a null reference for a null result, a Boolean_t for a boolean result, or any other data type for a casting request.
	*
	* @param[out] elementResult
	* elementResult is the result of the given content filter element.
	*
	* @param[in] diagnosticsRequested
	* diagnosticsRequested is the flag to get the diagnostic information in the result structure
	*
	* @return status
	* status will return Good if the filter was applied correctly, bad otherwise.
	*/
  virtual Status_t ApplyFilterElement(const INode_t& node, IContentFilter_t* filter, IntrusivePtr_t<IAttributeAccess_t>& eventAttributes, IntrusivePtr_t<IServerConfiguration_t> configuration, IntrusivePtr_t<BaseDataType_t>& evaluationResult, IntrusivePtr_t<ContentFilterElementResult_t>& elementResult, bool diagnosticsRequested);

	/*****************************************************************************/
	/** Copy to the destination
	*
	* @param[out] IntrusivePtr_t<BaseDataType_t>& destination
	* Destination data type
	*
	* @return
	* Status of the operation
	*/
	virtual Status_t CopyTo(IntrusivePtr_t<BaseDataType_t>& destination) const;

	/*****************************************************************************/
	/** Copy from the source
	*
	* @param[in] const BaseDataType_t& source
	* Source data type
	*
	* @return
	* Status of the operation
	*/
	virtual Status_t CopyFrom(const BaseDataType_t& source);

	/*****************************************************************************/
	/** Copy from the source
	*
	* @param[in] const ContentFilterElement_Like_t& source
	*  ContentFilterElement_Like_t source object to copy from
	*
	* @return
	* Status of the operation
	*/
  Status_t CopyFrom(const ContentFilterElement_Like_t& source);

protected:
	bool isCompiled;
	bool isValid;
  
  Status_t ResetStateTable();
  //All generators return the number of the final state generated.
  uint16_t GenerateNFARule_simpleChar(uint16_t currentState, uint8_t symbol);
  uint16_t GenerateNFARule_sequence(uint16_t startingState, const uint8_t * sequence, int32_t sequenceLength);
  uint16_t GenerateNFARule_wildcard(uint16_t startingState, bool loop);
  uint16_t GenerateNFARule_charList(uint16_t startingState, const uint8_t *data, int32_t len);

  uint32_t UTF8Decode(const uint8_t * data, int32_t length,  /*OUT*/ int32_t & consumedBytes) const;
  uint32_t UTF8Encode(uint32_t codePoint, int32_t maxLength, /* OUT */ uint8_t * sequence) const;

  uint16_t AddNewState(const char * comment = NULL);
  
  bool CompileEpsilonNFA(const uint8_t *data, const int32_t length);
  bool CompileEpsilonNFAToDFA();
  
  bool ComputeClosure(Hash_Set_t<uint16_t> &set);
  Status_t DFAEdge(Hash_Set_t<uint16_t> & currentStates, uint8_t symbol, /* OUT */ Hash_Set_t<uint16_t>& newPossibleStates);
	
  bool Match(const uint8_t *data, const int32_t length);

#ifdef DEBUG_LIKE_DFA
  void DumpStateTable();
  void DumpSet(Hash_Set_t<uint16_t> & set);
#endif
	
  Array_t<ParsingState_t> stateTable;
	uint16_t numStates;

	static const uint16_t STATE_INIT = 0;
  static const uint32_t STATE_TABLE_GROWTH = 5;

};

/** @} */

} // namespace uasdk

#endif // UASDK_INCLUDE_EVENTS

#endif // _CONTENT_FILTER_ELEMENT_LIKE_T_
