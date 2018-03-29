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

#ifndef _CONTENT_FILTER_T_
#define _CONTENT_FILTER_T_

#include "status_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "opcua_iruntime_type_t.h"
#include "opcua_identifiers.h"
#include "opcua_structure_t.h"
#include "opcua_array_ua_t.h"
#include "opcua_datatype_utilities_t.h"
#include "content_filter_result_t.h"
#include "content_filter_element_t.h"
#include "inode_t.h"
#include "icontent_filter_t.h"
#include "iattribute_access_t.h"

namespace uasdk
{
/** \addtogroup grpEventsandAC
*@{*/

/*****************************************************************************/
/** \brief ContentFilter_t
*
* This class implements the ContentFilter type
*
*/
class ContentFilter_t : public Structure_t, public IContentFilter_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(ContentFilter_t);

private:

	/*****************************************************************************/
	/* @var ArrayUA_t<ContentFilterElement_t>  elements
	* List of operators and their operands that compose the filter criteria. 
	* The filter is evaluated by starting with the first entry in this array. 
	* This structure is defined in-line with the following indented items.
	*/
  ArrayUA_t<ContentFilterElement_t>  elements;

public:
	/*****************************************************************************/
	/* @var uint32_t TYPE_ID
	* Data type ID
	*/
  static const uint32_t TYPE_ID = OpcUaId_ContentFilter;

	/*****************************************************************************/
	/** Default constructor for the class.
	*
	*/
  ContentFilter_t();

	/*****************************************************************************/
	/** Parameterized constructor for the class.
	*
	*/
  ContentFilter_t(ArrayUA_t<ContentFilterElement_t> elements_);

	/*****************************************************************************/
	/** Destructor for the class.
	*
	*/
  virtual ~ContentFilter_t();

	/*****************************************************************************/
	/** == operator overloading
	*
	* @param[in] BaseDataType_t const & obj
	* Object to be compared with
	*
	* @return
	* True - If the both the objects are same
	* False - If the both the objects are not same
	*/
	virtual bool operator==(BaseDataType_t const & obj) const;

	/*****************************************************************************/
	/** == operator overloading
	*
	* @param[in] ContentFilter_t const & obj
	* Object to be compared with
	*
	* @return
	* True - If the both the objects are same
	* False - If the both the objects are not same
	*/
  bool operator==(ContentFilter_t const & obj) const;

	/*****************************************************************************/
	/** > operator overloading
	*
	* @param[in] BaseDataType_t const & obj
	* Object to be compared with
	*
	* @return
	* True - If grater than RHS
	* False - If less than RHS
	*/
	virtual bool operator>(BaseDataType_t const & obj) const;

	/*****************************************************************************/
	/** > operator overloading
	*
	* @param[in] ContentFilter_t const & obj
	* Object to be compared with
	*
	* @return
	* True indicates that the LHS ContentFilter_t object is greater than RHS ContentFilter_t object
	*/
  bool operator>(ContentFilter_t const & obj) const;

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
	* @param[in] const ContentFilter_t& source
	*  ContentFilter source object to copy from
	*
	* @return
	* Status of the operation
	*/
  Status_t CopyFrom(const ContentFilter_t& source);
	
	/*****************************************************************************/
	/** Get the Type ID
	*
	* @param[in] uint16_t& namespaceIndex
	* Reference to the name space index
	*
	* @return
	* Returns the Type ID
	*/
	virtual uint32_t TypeId(uint16_t& namespaceIndex)  const;

	/*****************************************************************************/
	/** Get the Binary Encoding Id
	*
	* @param[in] uint16_t& namespaceIndex
	* Reference to the name space index
	*
	* @return
	* Returns the Binary Encoding Id
	*/
	virtual uint32_t BinaryEncodingId(uint16_t& namespaceIndex) const;

	/*****************************************************************************/
	/** Get the Elements
	*
	* @return
	* Returns the Elements
	*/
	const ArrayUA_t<ContentFilterElement_t>& Elements(void) const;

	/*****************************************************************************/
	/** Set the Elements
	*
	* @return
	* Returns the Elements
	*/
	ArrayUA_t<ContentFilterElement_t>& Elements(void);

	/*****************************************************************************/
	/** Encode the buffer
	*
	* @param[in] ICodec_t& encoder
	* Reference to the encoder object
	*
	* @param[out] IBuffer_t& buffer
	* Encode buffer
	*
	* @return
	* Returns status of the operation
	*/
  Status_t Encode(ICodec_t& encoder, IBuffer_t& buffer) const;

	/*****************************************************************************/
	/** Decode the buffer
	*
	* @param[in] const IBuffer_t& buffer
	* Decode buffer
	*
	* @param[in] ICodec_t& decoder
	* Reference to the decoder object
	*
	* @param[out] ContentFilter_t& result
	* Decoded ContentFilter object
	*
	* @return
	* Returns status of the operation
	*/
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, ContentFilter_t& result);

	/******************************************************************************************************/
	/** Processes the content filter for the given node and obtains the result of evaluating the filter against the provided node
	*
	* @param[in] node
	* node is the node to pass through the filter
	*
	* @param[in] eventAttributes
	* eventAttributes is the event instance. This is used by the SimpleAttributeOperand to get the attribute values based on the input parameters.
	*
	* @param[in] configuration
	* configuration is the instance of server configuration
	*
	* @param[out] resultStructure
	* resultStructure is the result of the content filter.
	*
	* @param[out] evaluatedResult
	* evaluationResult is the result of the evaluation.
	*
	* @param[in] diagnosticsRequested
	* diagnosticsRequested is the flag to get the diagnostic information in the result structure
	*
	* @return status
	* status will return Good if the filter was applied correctly or if empy filter, bad otherwise.
	*/
  Status_t ApplyFilter(const INode_t& node, IntrusivePtr_t<IAttributeAccess_t>& eventAttributes, IntrusivePtr_t<IServerConfiguration_t> configuration, IntrusivePtr_t<ContentFilterResult_t>& resultStructure, IntrusivePtr_t<BaseDataType_t> &evaluatedResult, bool diagnosticsRequested = false);

	/******************************************************************************************************/
	/** Processes this filter element and obtains the result of evaluating the filter against the provided node
	*
	* @param[in] element
	* The element index to be processed
	*
	* @param[in] node
	* node is the node to pass through the filter
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
  virtual Status_t EvaluateFilterElement(uint32_t element, const INode_t& node, IntrusivePtr_t<IAttributeAccess_t>& eventAttributes, IntrusivePtr_t<IServerConfiguration_t> configuration, IntrusivePtr_t<BaseDataType_t>& evaluatedResult, IntrusivePtr_t<ContentFilterElementResult_t>& elementResult, bool diagnosticsRequested);

	/******************************************************************************************************/
	/** Validates the input content filter
	*
	* @param[in] configuration
	* configuration is the instance of server configuration
	*
	* @param[out] contentFilterResult
	* Result which contains any errors associated with the filter.
	*
	* @return status
	* status will return Good if the filter is valid, else Bad.
	*/
	Status_t Validate(IntrusivePtr_t<IServerConfiguration_t> configuration, IntrusivePtr_t<ContentFilterResult_t>& contentFilterResult);
  
  //Public interface for testing

	/*****************************************************************************/
	/** Set the Elements
	*
	* @param[in] ArrayUA_t<ContentFilterElement_t>& elements_
	* input Elements
	*
	* @return
	* Returns the status of the operation
	*/
  Status_t Elements(ArrayUA_t<ContentFilterElement_t>& elements_);
};

/** @} */

} //namespace uasdk

#endif // UASDK_INCLUDE_EVENTS

#endif // _CONTENT_FILTER_T_

