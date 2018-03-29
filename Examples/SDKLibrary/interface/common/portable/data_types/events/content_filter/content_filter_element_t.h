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

#ifndef _CONTENT_FILTER_ELEMENT_T_
#define _CONTENT_FILTER_ELEMENT_T_

#include "status_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "opcua_extensible_parameter_t.h"
#include "opcua_identifiers.h"
#include "opcua_base_data_type_t.h"
#include "opcua_structure_t.h"
#include "type_conversion_t.h"
#include "opcua_diagnostic_info_t.h"
#include "opcua_status_code_t.h"
#include "opcua_array_ua_t.h"
#include "inode_t.h"

#include "opcua_iruntime_type_t.h"
#include "filter_operator_t.h"
#include "icontent_filter_t.h"
#include "filter_operand_t.h"
#include "content_filter_element_result_t.h"
#include "iattribute_access_t.h"
#include "iaddress_space_t.h"

namespace uasdk
{

typedef enum
{
  LOGIC_NULL = -1,
  LOGIC_FALSE = FALSE,
  LOGIC_TRUE = TRUE
} LogicalTrueTableValue_t;

/** \addtogroup grpEventsandAC
*@{*/

/*****************************************************************************/
/** \brief ContentFilterElement_t
*
* This class implements the ContentFilterElement type
*
*/
class ContentFilterElement_t : public Structure_t, public TypeConversion_t
{
public: 
  UA_DECLARE_RUNTIME_TYPE(ContentFilterElement_t);
private:

	/*****************************************************************************/
	/* @var ArrayUA_t<ExtensibleParameter_t>  filterOperands
	* Operands used by the selected operator. The number and use depend on the operators.
	* This array needs at least one entry. This extensible parameter type is the FilterOperand parameter type.
	* It specifies the list of valid FilterOperand values.
	*/
	ArrayUA_t<ExtensibleParameter_t>  filterOperands;

protected:

	/*****************************************************************************/
	/* @var FilterOperator_t filterOperator
	* Filter operator to be evaluated.
	*/
	FilterOperator_t filterOperator;

public:
	/*****************************************************************************/
	/* @var uint32_t TYPE_ID
	* Data type ID
	*/
	static const uint32_t TYPE_ID = OpcUaId_ContentFilterElement;

	/*****************************************************************************/
	/** Default constructor for the class.
	*
	*/
	ContentFilterElement_t();

	/*****************************************************************************/
	/** Parameterized constructor for the class.
	*
	*/
	ContentFilterElement_t(FilterOperator_t::Enum_t operatorType);

	/*****************************************************************************/
	/** Destructor for the class.
	*
	*/
	virtual ~ContentFilterElement_t();

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
	* @param[in] ContentFilterElement_t const & obj
	* Object to be compared with
	*
	* @return
	* True - If the both the objects are same
	* False - If the both the objects are not same
	*/
	bool operator==(ContentFilterElement_t const & obj) const;

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
	* @param[in] ContentFilterElement_t const & obj
	* Object to be compared with
	*
	* @return
	* True indicates that the LHS ContentFilterElement_t object is greater than RHS ContentFilterElement_t object
	*/
	bool operator>(ContentFilterElement_t const & obj) const;

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
	/** Get the minimum number of operands for this operator
	*
	* @return
	* Returns the minimum number of operands for this operator
	*/
	virtual uint32_t MinimumOperandCount(void) const = 0;

	/*****************************************************************************/
	/** Get the maximum number of operands for this operator.
	*
	* @return
	* Returns the maximum number of operands for this operator
	*/
	virtual uint32_t MaximumOperandCount(void) const = 0;

	/*****************************************************************************/
	/** Get the FilterOperands
	*
	* @return
	* Returns the FilterOperands
	*/
	virtual const ArrayUA_t<ExtensibleParameter_t>& FilterOperands(void) const;

	/*****************************************************************************/
	/** Set the FilterOperands
	*
	* @return
	* Returns the FilterOperands
	*/
	virtual ArrayUA_t<ExtensibleParameter_t>& FilterOperands(void);

	/*****************************************************************************/
	/** Get the FilterOperator
	*
	* @return
	* Returns the FilterOperator
	*/
	virtual const FilterOperator_t& FilterOperator() const;

	/*****************************************************************************/
	/** Set the FilterOperator
	*
	* @return
	* Returns the FilterOperator
	*/
	virtual FilterOperator_t& FilterOperator();

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
	* @param[out] IntrusivePtr_t<ContentFilterElement_t>& result
	* Decoded ContentFilterElement object
	*
	* @return
	* Returns status of the operation
	*/
	static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, IntrusivePtr_t<ContentFilterElement_t>& result);

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
	 * @param[out] localizableTextStored
	 * localizableTextStored is the updated object which contains the input localeId and text
	 *
	 * @return status
	 * status will return Good if the filter was applied correctly, bad otherwise.
	 */

	virtual Status_t ApplyFilterElement(const INode_t& node, IContentFilter_t* filter, IntrusivePtr_t<IAttributeAccess_t>& eventAttributes, IntrusivePtr_t<IServerConfiguration_t> configuration, IntrusivePtr_t<BaseDataType_t>& evaluationResult, IntrusivePtr_t<ContentFilterElementResult_t>& elementResult, bool diagnosticsRequested) = 0;

	/******************************************************************************************************/
	/** Validates the operand type
	*
	* @param[in] operandValue
	* input operand value
	*
	* @return status
	* status will return Good if the filter is valid, else Bad.
	*/
	Status_t ValidateFilterOperandType(IntrusivePtr_t<BaseDataType_t> operandValue);

	/**
	 * Public interface
	 */

	 /*****************************************************************************/
	 /** Set the FilterOperands
	 *
	 * @param[in] ArrayUA_t<ExtensibleParameter_t>& filterOperands_
	 * input filterOperands_
	 *
	 * @return
	 * Returns the status of the operation
	 */
  Status_t FilterOperands(ArrayUA_t<ExtensibleParameter_t>& filterOperands_);

	/******************************************************************************************************/
	/** Get the value of the operand based on the input operand index
	*
	* @param[in] operandIndex
	* The index of the operand
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
	Status_t GetValidFilterOperandValue(uint32_t operandIndex, const INode_t& node, IContentFilter_t* filter, IntrusivePtr_t<IAttributeAccess_t>& eventAttributes, IntrusivePtr_t<IServerConfiguration_t> configuration, IntrusivePtr_t<BaseDataType_t>& value, IntrusivePtr_t<ContentFilterElementResult_t>& elementResult, bool diagnosticsRequested);

	 /******************************************************************************************************/
	 /** Perform the Logical And operation as per Part 4 - Table 120 - Logic AND Truth Table
	 *
	 * @param[in] aValue
	 * first operand
	 *
	 * @param[in] aValue
	 * second operand
	 *	 
	 * @return LogicalTrueTableValue_t
	 * result of the Logical And operation
	 */
	LogicalTrueTableValue_t LogicalAndTruthTable(LogicalTrueTableValue_t &aValue, LogicalTrueTableValue_t &bValue);

	 /******************************************************************************************************/
	 /** Perform the Logical Or operation as per Part 4 - Table 121 - Logic OR Truth Table
	 *
	 * @param[in] aValue
	 * first operand
	 *
	 * @param[in] aValue
	 * second operand
	 *
	 * @return LogicalTrueTableValue_t
	 * result of the Logical Or operation
	 */
	LogicalTrueTableValue_t LogicalOrTruthTable(LogicalTrueTableValue_t &aValue, LogicalTrueTableValue_t &bValue);

	/******************************************************************************************************/
	/** Validates the input arguments passed to ApplyFilterElement
	*
	* @param[in] filter
	* filter the content filter owning this element.  This is used by the ElementOperand when a sub element is referenced
	*
	* @param[in] eventAttributes
	* eventAttributes is the event instance. This is used by the SimpleAttributeOperand to get the attribute values based on the input parameters.
	*
	* @param[in] evaluationResult
	* It is out parameter in ApplyFilterElement but it is checked in this method if it is previously set.
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
	Status_t CheckApplyFilterElementArguments(
											  IContentFilter_t *filter,
												IntrusivePtr_t<IAttributeAccess_t>& eventAttributes,
											  IntrusivePtr_t<BaseDataType_t>& evaluationResult,
												IntrusivePtr_t<ContentFilterElementResult_t>& elementResult,
												bool diagnosticsRequested);
 
};

/** @} */

} // namespace uasdk

#endif // UASDK_INCLUDE_EVENTS

#endif // _CONTENT_FILTER_ELEMENT_T_
