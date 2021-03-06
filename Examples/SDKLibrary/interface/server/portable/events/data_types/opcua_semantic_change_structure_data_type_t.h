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

#ifndef _OPCUA_SEMANTIC_CHANGE_STRUCTURE_DATA_TYPE_T_
#define _OPCUA_SEMANTIC_CHANGE_STRUCTURE_DATA_TYPE_T_

#include "status_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "opcua_identifiers.h"
#include "opcua_structure_t.h"
#include "intrusive_ptr_t.h"
#include "opcua_node_id_t.h"

namespace uasdk
{
/** \addtogroup grpEventsandAC
*@{*/

/*****************************************************************************/
/** \brief SemanticChangeStructureDataType_t
*
* This class implements SemanticChangeStructureDataType type
*
*/
class SemanticChangeStructureDataType_t : public Structure_t
{
private:

	/*****************************************************************************/
	/* @var IntrusivePtr_t<NodeId_t> affected
	* NodeId of the Node that owns the Property that has changed.
	*/
  IntrusivePtr_t<NodeId_t>  affected;

	/*****************************************************************************/
	/* @var IntrusivePtr_t<NodeId_t> affectedType
	* If the affected Node was an Object or Variable, affectedType contains the NodeId of the TypeDefinitionNode of the affected Node. 
	* Otherwise it is set to null.
	*/
  IntrusivePtr_t<NodeId_t>  affectedType;

public:
  UA_DECLARE_RUNTIME_TYPE(SemanticChangeStructureDataType_t);

	/*****************************************************************************/
	/* @var uint32_t TYPE_ID
	* Data type ID
	*/
  static const uint32_t TYPE_ID = OpcUaId_SemanticChangeStructureDataType;

	/*****************************************************************************/
	/** constructor for the class.
	*
	*/
	SemanticChangeStructureDataType_t();

	/*****************************************************************************/
	/** Destructor for the class.
	*
	*/
  virtual ~SemanticChangeStructureDataType_t();

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
	* @param[in] SemanticChangeStructureDataType_t const & obj
	* Object to be compared with
	*
	* @return
	* True - If the both the objects are same
	* False - If the both the objects are not same
	*/
  bool operator==(SemanticChangeStructureDataType_t const & obj) const;

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
	* @param[in] SemanticChangeStructureDataType_t const & obj
	* Object to be compared with
	*
	* @return
	* True indicates that the LHS SemanticChangeStructureDataType_t object is greater than RHS SemanticChangeStructureDataType_t object
	*/
  bool operator>(SemanticChangeStructureDataType_t const & obj) const;

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
	* @param[in] const SemanticChangeStructureDataType_t& source
	*  SemanticChangeStructureDataType source to copy from
	*
	* @return
	* Status of the operation
	*/
  Status_t CopyFrom(const SemanticChangeStructureDataType_t& source);

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
	/** Get the Type ID
	*
	* @param[in] uint16_t& namespaceIndex
	* Reference to the name space index
	*
	* @return
	* Returns the Type ID
	*/
	virtual uint32_t TypeId(uint16_t& namespaceIndex) const;

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
	/** Get the Affected
	*
	* @return
	* Returns the Affected
	*/
	IntrusivePtr_t<const NodeId_t> Affected(void) const;

	/*****************************************************************************/
	/** Set the Affected
	*
	* @return
	* Returns the Affected
	*/
	IntrusivePtr_t<NodeId_t>& Affected(void);

	/*****************************************************************************/
	/** Get the AffectedType
	*
	* @return
	* Returns the AffectedType
	*/
	IntrusivePtr_t<const NodeId_t> AffectedType(void) const;

	/*****************************************************************************/
	/** Set the AffectedType
	*
	* @return
	* Returns the AffectedType
	*/
	IntrusivePtr_t<NodeId_t>& AffectedType(void);

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
	* @param[out] SemanticChangeStructureDataType_t& result
	* Decoded SemanticChangeStructureDataType_t object
	*
	* @return
	* Returns status of the operation
	*/
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, SemanticChangeStructureDataType_t& result);

};

/** @} */

} // namespace uasdk

#endif // UASDK_INCLUDE_EVENTS

#endif // _OPCUA_SEMANTIC_CHANGE_STRUCTURE_DATA_TYPE_T_
