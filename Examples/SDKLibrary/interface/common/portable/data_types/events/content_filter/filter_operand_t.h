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

#ifndef _FILTER_OPERAND_T_
#define _FILTER_OPERAND_T_

#include "status_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "opcua_node_id_t.h"
#include "opcua_identifiers.h"
#include "opcua_structure_t.h"
#include "intrusive_ptr_t.h"
#include "inode_t.h"
#include "icontent_filter_t.h"
#include "content_filter_element_t.h"

namespace uasdk
{
/** \addtogroup grpEventsandAC
*@{*/

/*****************************************************************************/
/** \brief FilterOperand_t
*
* This class is the base interface of all the content filter operands
*
*/
class FilterOperand_t : public Structure_t
{

public:
  UA_DECLARE_RUNTIME_TYPE(FilterOperand_t);

	/*****************************************************************************/
	/* @var uint32_t TYPE_ID
	* Data type ID
	*/
  static const uint32_t TYPE_ID = OpcUaId_FilterOperand;

	/*****************************************************************************/
	/* @var uint32_t filterOperandId_encoding_defaultBinary
	* encoding type to identify which type of operand is encoded or decoded.
	*/
  static uint32_t filterOperandId_encoding_defaultBinary;
	
	/*****************************************************************************/
	/** Default constructor for the class.
	*
	*/
  FilterOperand_t();

	/*****************************************************************************/
	/** Destructor for the class.
	*
	*/
  virtual ~FilterOperand_t();

	/*****************************************************************************/
	/** Get the Type ID
	*
	* @param[in] uint16_t& namespaceIndex
	* Reference to the name space index
	*
	* @return
	* Returns the Type ID
	*/
  virtual uint32_t TypeId(uint16_t& namespaceIndex) const = 0;

	/******************************************************************************************************/
	/** Get the value of the operand
	*
	* @param[in] node
	* node is the node passed via content filter
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
	* @param[out] value
	* value is the evaluated operand value
	*
	* @param[out] elementResult
	* elementResult is the result of the evaluation.
	*
	* @param[in] diagnosticsRequested
	* diagnosticsRequested is the flag to get the diagnostic information in the result structure
	*
	* @return status
	* status will return Good if the value is evaluated successfully, otherwise bad.
	*/
  virtual Status_t GetValue(const INode_t& node, IContentFilter_t* filter, IntrusivePtr_t<IAttributeAccess_t>& eventAttributes, IntrusivePtr_t<IServerConfiguration_t> configuration, IntrusivePtr_t<BaseDataType_t>& value, IntrusivePtr_t<ContentFilterElementResult_t>& elementResult, bool diagnosticsRequested) = 0;
			
	/*****************************************************************************/
	/** Decode the buffer
	*
	* @param[in] const IBuffer_t& buffer
	* Decode buffer
	*
	* @param[in] ICodec_t& decoder
	* Reference to the decoder object
	*
	* @param[out] IntrusivePtr_t<FilterOperand_t>& result
	* Decoded FilterOperand object
	*
	* @return
	* Returns status of the operation
	*/
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, IntrusivePtr_t<FilterOperand_t>& result);

	/*****************************************************************************/
	/** Set the FilterOperandId_encoding_defaultBinary
	*
	* @param[in] uint32_t filterOperandId_encoding_defaultBinary_
	* input encoding type to identify which type of operand is encoded or decoded.
	*
	* @return void
	*/
  static void FilterOperandId_encoding_defaultBinary(uint32_t filterOperandId_encoding_defaultBinary_);

};

/** @} */

} // namespace uasdk

#endif // UASDK_INCLUDE_EVENTS

#endif // _FILTER_OPERAND_T_
