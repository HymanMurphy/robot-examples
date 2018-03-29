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

#ifndef _SIMPLE_ATTRIBUTE_OPERAND_T_
#define _SIMPLE_ATTRIBUTE_OPERAND_T_

#include "filter_operand_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "opcua_qualified_name_t.h"
#include "opcua_identifiers.h"
#include "opcua_array_ua_t.h"

namespace uasdk
{
/** \addtogroup grpEventsandAC
*@{*/

/*****************************************************************************/
/** \brief SimpleAttributeOperand_t
*
* This class implements the SimpleAttributeOperand type
*
*/
class SimpleAttributeOperand_t : public FilterOperand_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(SimpleAttributeOperand_t);

private:

	/*****************************************************************************/
	/* @var IntrusivePtr_t<NodeId_t> typeId
	* NodeId of a TypeDefinitionNode. This parameter restricts the operand to instances of the TypeDefinitionNode or one of its subtypes
	*/
  IntrusivePtr_t<NodeId_t>    typeId;

	/*****************************************************************************/
	/* @var ArrayUA_t<QualifiedName_t>  browsePath
	* A relative path to a Node.
	*/
  ArrayUA_t<QualifiedName_t>  browsePath;

	/*****************************************************************************/
	/* @var IntegerId_t attributeId
	* Id of the Attribute
	*/
  IntegerId_t                 attributeId;

	/*****************************************************************************/
	/* @var String_t indexRange
	* This parameter is used to identify a single element of an array, or a single range of indexes for an array. 
	* The first element is identified by index 0 (zero). This parameter is ignored if the selected Node is not a Variable or the Value of a Variable is not an array
	* The parameter is null if not specified.
	*/
  String_t                    indexRange;
	
public:
	/*****************************************************************************/
	/* @var uint32_t TYPE_ID
	* Data type ID
	*/
  static const uint32_t TYPE_ID = OpcUaId_SimpleAttributeOperand;

	/*****************************************************************************/
	/** Default constructor for the class.
	*
	*/
  SimpleAttributeOperand_t();

	/*****************************************************************************/
	/** Parameterized constructor for the class.
	*
	*/
  SimpleAttributeOperand_t(IntrusivePtr_t<NodeId_t> typeId_,
                           ArrayUA_t<QualifiedName_t> browsePath_,
                           IntegerId_t attributeId_,
                           String_t indexRange_);

	/*****************************************************************************/
	/** Destructor for the class.
	*
	*/
  virtual ~SimpleAttributeOperand_t();

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
	* @param[in] SimpleAttributeOperand_t const & obj
	* Object to be compared with
	*
	* @return
	* True - If the both the objects are same
	* False - If the both the objects are not same
	*/
  bool operator==(SimpleAttributeOperand_t const & obj) const;

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
	* @param[in] SimpleAttributeOperand_t const & obj
	* Object to be compared with
	*
	* @return
	* True indicates that the LHS SimpleAttributeOperand_t object is greater than RHS SimpleAttributeOperand_t object
	*/
  bool operator>(SimpleAttributeOperand_t const & obj) const;

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
	* @param[in] const SimpleAttributeOperand_t& source
	*  SimpleAttributeOperand source object to copy from
	*
	* @return
	* Status of the operation
	*/
  Status_t CopyFrom(const SimpleAttributeOperand_t& source);

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
	/** Get the TypeId
	*
	* @return
	* Returns the TypeId. An intrusive reference counting Boost-style
	* smart pointer to the TypeId. The caller must test the pointer before dereferencing it.
	*/
	IntrusivePtr_t<const NodeId_t> TypeId() const;

	/*****************************************************************************/
	/** Set the TypeId
	*
	* @return
	* Returns the TypeId reference. An intrusive reference counting Boost-style
	* smart pointer to the TypeId. The caller must set a valid pointer.
	*/
	IntrusivePtr_t<NodeId_t>& TypeId();

	/*****************************************************************************/
	/** Get the BrowsePath
	*
	* @return
	* Returns the BrowsePath
	*/
	const ArrayUA_t<QualifiedName_t>& BrowsePath() const;

	/*****************************************************************************/
	/** Set the BrowsePath
	*
	* @return
	* Returns the BrowsePath
	*/
	ArrayUA_t<QualifiedName_t>& BrowsePath();

	/*****************************************************************************/
	/** Get the AttributeId
	*
	* @return
	* Returns the AttributeId
	*/
	const IntegerId_t& AttributeId() const;

	/*****************************************************************************/
	/** Set the AttributeId
	*
	* @return
	* Returns the AttributeId
	*/
	IntegerId_t& AttributeId();

	/*****************************************************************************/
	/** Get the IndexRange
	*
	* @return
	* Returns the IndexRange
	*/
	const String_t& IndexRange() const;

	/*****************************************************************************/
	/** Set the IndexRange
	*
	* @return
	* Returns the IndexRange
	*/
	String_t& IndexRange();

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
	* @param[out] IntrusivePtr_t<SimpleAttributeOperand_t>& result
	* Decoded SimpleAttributeOperand object
	*
	* @return
	* Returns status of the operation
	*/
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, IntrusivePtr_t<SimpleAttributeOperand_t>& result);

	/*****************************************************************************/
	/** Validate the SimpleAttributeOperand
	*
	* @return
	* Returns status of the operation
	*/
	Status_t Validate();

  //public interfaces for testing

	/*****************************************************************************/
	/** Set the TypeId
	*
	* @param[in] IntrusivePtr_t<NodeId_t>& id
	* input typeId
	*
	* @return
	* Returns the status of the operation
	*/
	Status_t TypeId(IntrusivePtr_t<NodeId_t>& id);

	/*****************************************************************************/
	/** Set the BrowsePath
	*
	* @param[in] ArrayUA_t<QualifiedName_t>& path
	* input BrowsePath
	*
	* @return
	* Returns the status of the operation
	*/
  Status_t BrowsePath(ArrayUA_t<QualifiedName_t>& path);

	/*****************************************************************************/
	/** Set the AttributeId
	*
	* @param[in] IntegerId_t& attrId
	* input attributeId
	*
	* @return
	* Returns the status of the operation
	*/
	Status_t AttributeId(IntegerId_t& attrId);

	/*****************************************************************************/
	/** Set the IndexRange
	*
	* @param[in] String_t& range
	* input indexRange
	*
	* @return
	* Returns the status of the operation
	*/
  Status_t IndexRange(String_t& range);
};

/** @} */

} // namespace uasdk

#endif // UASDK_INCLUDE_EVENTS

#endif // _SIMPLE_ATTRIBUTE_OPERAND_T_

