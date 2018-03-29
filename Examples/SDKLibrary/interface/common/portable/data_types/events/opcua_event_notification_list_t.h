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

#ifndef _OPCUA_EVENT_NOTIFICATION_LIST_T_
#define _OPCUA_EVENT_NOTIFICATION_LIST_T_

#include "status_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "opcua_identifiers.h"
#include "opcua_structure_t.h"
#include "intrusive_ptr_t.h"
#include "opcua_event_field_list_t.h"
#include "opcua_array_ua_t.h"
#include "opcua_datatype_utilities_t.h"

namespace uasdk
{
/** \addtogroup grpEventsandAC
*@{*/

/*****************************************************************************/
/** \brief EventNotificationList_t
*
* This class implements EventNotificationList type
*
*/
class EventNotificationList_t : public Structure_t
{
private:

	/*****************************************************************************/
	/* @var ArrayUA_t<EventFieldList_t>  events
	* The list of Events being delivered.
	*/
  ArrayUA_t<EventFieldList_t>  events;

public:
  UA_DECLARE_RUNTIME_TYPE(EventNotificationList_t);

	/*****************************************************************************/
	/* @var uint32_t TYPE_ID
	* Data type ID
	*/
  static const uint32_t TYPE_ID = OpcUaId_EventNotificationList;

	/*****************************************************************************/
	/** constructor for the class.
	*
	*/
  EventNotificationList_t();

	/*****************************************************************************/
	/** Destructor for the class.
	*
	*/
  virtual ~EventNotificationList_t();

	/*****************************************************************************/
	/** = operator overloading
	*
	* @param[in] EventNotificationList_t const & obj
	* Object to be assigned
	*
	* @return
	* Reference to the EventNotificationList object assigned
	*/
  EventNotificationList_t& operator=(EventNotificationList_t const &);

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
	* @param[in] EventNotificationList_t const & obj
	* Object to be compared with
	*
	* @return
	* True - If the both the objects are same
	* False - If the both the objects are not same
	*/
  bool operator==(EventNotificationList_t const & obj) const;

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
	* @param[in] EventNotificationList_t const & obj
	* Object to be compared with
	*
	* @return
	* True indicates that the LHS EventNotificationList_t object is greater than RHS EventNotificationList_t object
	*/
  bool operator>(EventNotificationList_t const & obj) const;

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
	* @param[in] const EventNotificationList_t& source
	*  EventNotificationList source to copy from
	*
	* @return
	* Status of the operation
	*/
  Status_t CopyFrom(const EventNotificationList_t& source);

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
	/** Get the Events
	*
	* @return
	* Returns the Events
	*/
  const ArrayUA_t<EventFieldList_t>& Events(void) const;

	/*****************************************************************************/
	/** Set the Events
	*
	* @return
	* Returns the Events
	*/
  ArrayUA_t<EventFieldList_t>& Events(void);

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
	* @param[out] EventNotificationList_t& result
	* Decoded EventNotificationList object
	*
	* @return
	* Returns status of the operation
	*/
  static Status_t Decode(const IBuffer_t& buffer, ICodec_t& decoder, EventNotificationList_t& result);

};

/** @} */

} // namespace uasdk

#endif // UASDK_INCLUDE_EVENTS

#endif // _OPCUA_EVENT_NOTIFICATION_LIST_T_
