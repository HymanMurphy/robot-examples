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

#ifndef _LITERAL_OPERAND_T_
#define _LITERAL_OPERAND_T_

#include "filter_operand_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "opcua_base_data_type_t.h"
#include "opcua_identifiers.h"
#include "opcua_datatype_utilities_t.h"

namespace uasdk
{
/** \addtogroup grpEventsandAC
*@{*/

/*****************************************************************************/
/** \brief LiteralOperand_t
*
* This class implements the LiteralOperand type
*
*/
class LiteralOperand_t : public FilterOperand_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(LiteralOperand_t);
private:

	/*****************************************************************************/
	/* @var IntrusivePtr_t<BaseDataType_t> value
	* A literal value
	*/
  IntrusivePtr_t<BaseDataType_t>  value;

public:
	/*****************************************************************************/
	/* @var uint32_t TYPE_ID
	* Data type ID
	*/
  static const uint32_t TYPE_ID = OpcUaId_LiteralOperand;

	/*****************************************************************************/
	/** Default constructor for the class.
	*
	*/
  LiteralOperand_t();

	/*****************************************************************************/
	/** Parameterized constructor for the class.
	*
	*/
  LiteralOperand_t(IntrusivePtr_t<BaseDataType_t> value);

	/*****************************************************************************/
	/** Destructor for the class.
	*
	*/
  virtual ~LiteralOperand_t();

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
	* @param[in] LiteralOperand_t const & obj
	* Object to be compared with
	*
	* @return
	* True - If the both the objects are same
	* False - If the both the objects are not same
	*/
  bool operator==(LiteralOperand_t const & obj) const;

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
	* @param[in] LiteralOperand_t const & obj
	* Object to be compared with
	*
	* @return
	* True indicates that the LHS LiteralOperand_t object is greater than RHS LiteralOperand_t object
	*/
  bool operator>(LiteralOperand_t const & obj) const;

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
	* @param[in] const LiteralOperand_t& source
	*  LiteralOperand source object to copy from
	*
	* @return
	* Status of the operation
	*/
  Status_t CopyFrom(const LiteralOperand_t& source);

	/*****************************************************************************/
	/** Get the Type ID
	*
	* @param[in] uint16_t& namespaceIndex
	* Reference to the name space index
	*
	* @return
	* Returns the Type ID
	*/
	uint32_t TypeId(uint16_t& namespaceIndex)  const;

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
	/** Get the Value
	*
	* @return
	* Returns the Value
	*/
	IntrusivePtr_t<const BaseDataType_t> Value(void) const;

	/*****************************************************************************/
	/** Set the Value
	*
	* @return
	* Returns the Value
	*/
	IntrusivePtr_t<BaseDataType_t>& Value(void);

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
  virtual Status_t GetValue(const INode_t& node, IContentFilter_t* filter, IntrusivePtr_t<IAttributeAccess_t>& eventAttributes, IntrusivePtr_t<IServerConfiguration_t> configuration, IntrusivePtr_t<BaseDataType_t>& value, IntrusivePtr_t<ContentFilterElementResult_t>& elementResult, bool diagnosticsRequested);

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
	* @param[out] IntrusivePtr_t<LiteralOperand_t>& result
	* Decoded LiteralOperand object
	*
	* @return
	* Returns status of the operation
	*/
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, IntrusivePtr_t<LiteralOperand_t>& result);

  //public interface for testing

	/*****************************************************************************/
	/** Set the Value
	*
	* @param[in] IntrusivePtr_t<BaseDataType_t>& value_
	* input value
	*
	* @return
	* Returns the status of the operation
	*/
	Status_t Value(IntrusivePtr_t<BaseDataType_t>& value_);

};

/** @} */

} // namespace uasdk

#endif // UASDK_INCLUDE_EVENTS

#endif // _LITERAL_OPERAND_T_

