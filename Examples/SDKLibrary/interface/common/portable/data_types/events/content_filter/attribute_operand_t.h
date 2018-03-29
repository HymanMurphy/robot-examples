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

#ifndef _ATTRIBUTE_OPERAND_T_
#define _ATTRIBUTE_OPERAND_T_

#include "filter_operand_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "opcua_relative_path_element_t.h"
#include "opcua_identifiers.h"
#include "opcua_node_id_t.h"
#include "opcua_relative_path_element_t.h"
#include "opcua_array_ua_t.h"
#include "opcua_datatype_utilities_t.h"
#include "content_filter_element_t.h"
#include "inode_t.h"

namespace uasdk
{

/** \addtogroup grpEventsandAC
*@{*/

/*****************************************************************************/
/** \brief AttributeOperand_t
*
* This class implements the AttributeOperand type
*
*/
class AttributeOperand_t : public FilterOperand_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(AttributeOperand_t);

private:

	/*****************************************************************************/
	/* @var IntrusivePtr_t<NodeId_t> nodeId
	* NodeId of a Node from the type system.
	*/
  IntrusivePtr_t<NodeId_t>          nodeId;

	/*****************************************************************************/
	/* @var String_t alias
	* An optional parameter used to identify or refer to an alias. 
	* An alias is a symbolic name that can be used to alias this operand and use it in other locations in the filter structure.
	*/
  String_t                          alias;

	/*****************************************************************************/
	/* @var ArrayUA_t<RelativePathElement_t>  browsePath
	* Browse path relative to the Node identified by the nodeId parameter.
	*/
  ArrayUA_t<RelativePathElement_t>  browsePath;

	/*****************************************************************************/
	/* @var IntegerId_t  attributeId
	* Id of the Attribute. This shall be a valid AttributeId.
	*/
  IntegerId_t                       attributeId;

	/*****************************************************************************/
	/* @var String_t  indexRange
	* This parameter is used to identify a single element of an array or a single range of indexes for an array. 
	* The first element is identified by index 0 (zero). This parameter is not used if the specified Attribute is not an array. 
	* However, if the specified Attribute is an array and this parameter is not used, then all elements are to be included in the range. The parameter is null if not used.
	*/
  String_t                          indexRange;

public:
	/*****************************************************************************/
	/* @var uint32_t TYPE_ID
	* Data type ID
	*/
  static const uint32_t TYPE_ID = OpcUaId_AttributeOperand;

	/*****************************************************************************/
	/** Constructor for the class.
	*
	*/
  AttributeOperand_t();

	/*****************************************************************************/
	/** Destructor for the class.
	*
	*/
  virtual ~AttributeOperand_t();
	
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
	* @param[in] AttributeOperand_t const & obj
	* Object to be compared with
	*
	* @return
	* True - If the both the objects are same
	* False - If the both the objects are not same
	*/
  bool operator==(AttributeOperand_t const & obj) const;

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
	* @param[in] AttributeOperand_t const & obj
	* Object to be compared with
	*
	* @return
	* True indicates that the LHS AttributeOperand_t object is greater than RHS AttributeOperand_t object
	*/
  bool operator>(AttributeOperand_t const & obj) const;

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
	* @param[in] const AttributeOperand_t& source
	*  AttributeOperand source object to copy from
	*
	* @return
	* Status of the operation
	*/
  Status_t CopyFrom(const AttributeOperand_t& source);

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
	/** Get the NodeId
	*
	* @return
	* Returns the NodeId. An intrusive reference counting Boost-style
	* smart pointer to the NodeId. The caller must test the pointer before dereferencing it.
	*/
	IntrusivePtr_t<const NodeId_t> NodeId() const;

	/*****************************************************************************/
	/** Set the NodeId
	*
	* @return
	* Returns the NodeId reference. An intrusive reference counting Boost-style
	* smart pointer to the NodeId. The caller must set a valid pointer.
	*/
	IntrusivePtr_t<NodeId_t>& NodeId();

	/*****************************************************************************/
	/** Get the Alias
	*
	* @return
	* Returns the Alias
	*/
	const String_t& Alias() const;

	/*****************************************************************************/
	/** Set the Alias
	*
	* @return
	* Returns the Alias
	*/
	String_t& Alias();

	/*****************************************************************************/
	/** Get the BrowsePath
	*
	* @return
	* Returns the BrowsePath
	*/
	const ArrayUA_t<RelativePathElement_t>& BrowsePath() const;

	/*****************************************************************************/
	/** Set the BrowsePath
	*
	* @return
	* Returns the BrowsePath
	*/
	ArrayUA_t<RelativePathElement_t>& BrowsePath();

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
	* @param[out] IntrusivePtr_t<AttributeOperand_t>& result
	* Decoded AttributeOperand object
	*
	* @return
	* Returns status of the operation
	*/
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, IntrusivePtr_t<AttributeOperand_t>& result);

};

/** @} */

} // namespace uasdk

#endif // UASDK_INCLUDE_EVENTS

#endif // _ATTRIBUTE_OPERAND_T_

