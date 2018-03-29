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

#ifndef _CONTENT_FILTER_ELEMENT_OR_T_
#define _CONTENT_FILTER_ELEMENT_OR_T_

#include "content_filter_element_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

namespace uasdk
{
/** \addtogroup grpEventsandAC
*@{*/

/*****************************************************************************/
/** \brief ContentFilterElement_Or_t
*
* This class implements the Or operator in Content Filter
*
*/
class ContentFilterElement_Or_t : public ContentFilterElement_t
{

public:
  UA_DECLARE_RUNTIME_TYPE(ContentFilterElement_Or_t);

	/*****************************************************************************/
	/** Constructor for the class.
	*
	*/
	ContentFilterElement_Or_t();

	/*****************************************************************************/
	/** Destructor for the class.
	*
	*/
	virtual ~ContentFilterElement_Or_t();

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
	* @param[in] const ContentFilterElement_Or_t& source
	*  ContentFilterElement_Or_t source object to copy from
	*
	* @return
	* Status of the operation
	*/
  Status_t CopyFrom(const ContentFilterElement_Or_t& source);
};

/** @} */

} // namespace uasdk

#endif // UASDK_INCLUDE_EVENTS

#endif // _CONTENT_FILTER_ELEMENT_OR_T_
