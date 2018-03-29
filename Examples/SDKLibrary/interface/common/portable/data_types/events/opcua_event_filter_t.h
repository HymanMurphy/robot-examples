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

#ifndef _OPCUA_EVENT_FILTER_T_
#define _OPCUA_EVENT_FILTER_T_

#include "status_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "opcua_identifiers.h"
#include "opcua_structure_t.h"
#include "intrusive_ptr_t.h"
#include "inode_t.h"
#include "simple_attribute_operand_t.h"
#include "content_filter_t.h"
#include "opcua_array_ua_t.h"
#include "opcua_datatype_utilities_t.h"

namespace uasdk
{
/** \addtogroup grpEventsandAC
*@{*/

/*****************************************************************************/
/** \brief EventFilter_t
*
* This class implements EventFilter type
*
*/
class EventFilter_t : public Structure_t
{
private:
	/*****************************************************************************/
	/* @var ArrayUA_t<SimpleAttributeOperand_t>  selectClauses
	* List of the values to return with each Event in a Notification. At least one valid clause shall be specified.
	*/
  ArrayUA_t<SimpleAttributeOperand_t>  selectClauses;

	/*****************************************************************************/
	/* @var ContentFilter_t whereClause
	* Limit the Notifications to those Events that match the criteria defined by this ContentFilter.
	*/
  ContentFilter_t                      whereClause;

public:
  UA_DECLARE_RUNTIME_TYPE(EventFilter_t);

	/*****************************************************************************/
	/* @var uint32_t TYPE_ID
	* Data type ID
	*/
  static const uint32_t TYPE_ID = OpcUaId_EventFilter;

	/*****************************************************************************/
	/** constructor for the class.
	*
	*/
  EventFilter_t();

	/*****************************************************************************/
	/** Destructor for the class.
	*
	*/
  virtual ~EventFilter_t();

	/*****************************************************************************/
	/** = operator overloading
	*
	* @param[in] EventFilter_t const & obj
	* Object to be assigned
	*
	* @return
	* Reference to the EventFilter object assigned
	*/
  EventFilter_t& operator=(EventFilter_t const &);

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
	* @param[in] EventFilter_t const & obj
	* Object to be compared with
	*
	* @return
	* True - If the both the objects are same
	* False - If the both the objects are not same
	*/
  bool operator==(EventFilter_t const & obj) const;

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
	* @param[in] EventFilter_t const & obj
	* Object to be compared with
	*
	* @return
	* True indicates that the LHS EventFilter_t object is greater than RHS EventFilter_t object
	*/
  bool operator>(EventFilter_t const & obj) const;

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
	* @param[in] const EventFilter_t& source
	*  EventFilter source to copy from
	*
	* @return
	* Status of the operation
	*/
  Status_t CopyFrom(const EventFilter_t& source);

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
	/** Get the SelectClauses
	*
	* @return
	* Returns the SelectClauses
	*/
  const ArrayUA_t<SimpleAttributeOperand_t>& SelectClauses(void) const;

	/*****************************************************************************/
	/** Set the SelectClauses
	*
	* @return
	* Returns the SelectClauses
	*/
  ArrayUA_t<SimpleAttributeOperand_t>& SelectClauses(void);

	/*****************************************************************************/
	/** Get the WhereClause
	*
	* @return
	* Returns the WhereClause
	*/
  const ContentFilter_t& WhereClause(void) const;

	/*****************************************************************************/
	/** Set the WhereClause
	*
	* @return
	* Returns the WhereClause
	*/
  ContentFilter_t& WhereClause(void);

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
	* @param[out] EventFilter_t& result
	* Decoded EventFilter object
	*
	* @return
	* Returns status of the operation
	*/
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, EventFilter_t& result);

	/******************************************************************************************************/
	/** Evaluates the filter against the input target node
	*
	* @param[in] targetNode
	* node is the node to pass through the filter
	*
	* @param[in] eventAttributes
	* eventAttributes is the event instance. This is used by the SimpleAttributeOperand to get the attribute values based on the input parameters.
	*
	* @param[in] configuration
	* configuration is the instance of server configuration
	*
	* @return bool
	* True if the node pass the filter, otherwise false
	*/
  bool DoesEventPassFilter(const INode_t& targetNode, IntrusivePtr_t<IAttributeAccess_t>& eventAttributes, IntrusivePtr_t<IServerConfiguration_t> configuration);

};

/** @} */

} // namespace uasdk

#endif // UASDK_INCLUDE_EVENTS

#endif // _OPCUA_EVENT_FILTER_T_
