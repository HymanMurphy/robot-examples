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

#ifndef _ICONTENT_FILTER_T_
#define _ICONTENT_FILTER_T_

#include "status_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "iserver_configuration_t.h"
#include "intrusive_ptr_t.h"
#include "opcua_array_ua_t.h"
#include "opcua_base_data_type_t.h"
#include "inode_t.h"
#include "iattribute_access_t.h"
#include "content_filter_result_t.h"

namespace uasdk 
{
/** \addtogroup grpEventsandAC
*@{*/

/*****************************************************************************/
/** \brief IContentFilter_t
*
* This class implements the IContentFilter_t interface
*
*/
class IContentFilter_t
{
public:

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
  virtual Status_t EvaluateFilterElement(uint32_t element, const INode_t& node, IntrusivePtr_t<IAttributeAccess_t>& eventAttributes, IntrusivePtr_t<IServerConfiguration_t> configuration, IntrusivePtr_t<BaseDataType_t>& evaluatedResult, IntrusivePtr_t<ContentFilterElementResult_t>& elementResult, bool diagnosticsRequested) = 0;
};

/** @} */

} // namespace uasdk

#endif // UASDK_INCLUDE_EVENTS

#endif // _ICONTENT_FILTER_T_

