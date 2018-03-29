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

#ifndef _EVENT_NOTIFIER_T_
#define _EVENT_NOTIFIER_T_

#include "opcua_identifiers.h"
#include "opcua_byte_t.h"

namespace uasdk
{

/** \addtogroup grpDataType
*@{*/

/*****************************************************************************/
/** \brief EventNotifier_t
*
* This class contains the EventNotifier definitions
*
*/
class EventNotifier_t : public Byte_t
{
public:
  UA_DECLARE_RUNTIME_TYPE(EventNotifier_t);
public:

	/*****************************************************************************/
	/** \brief Enumeration of event notifier
	*
	*/
  typedef enum
  {
    BIT_SUBSCRIBE_TO_EVENTS = 0,
    BIT_RESERVED_1 = 1,
    BIT_HISTORY_READ = 2,
    BIT_HISTORY_WRITE = 3,
    BIT_RESERVED
  } Bits_t;

private:

	/*****************************************************************************/
	/** Update the Event Notifier bits
	*
	* @param[in] bool val
	* Set or clear
	*
	* @param[in] uint32_t bit
	* Event Notifier to set or clear
	*/
  void SetOrClear(bool val, uint32_t bit);

public:

	/*****************************************************************************/
	/* @var uint32_t TYPE_ID
	* Data type ID
	*/
  static const uint32_t TYPE_ID = OpcUaId_Byte;

	/*****************************************************************************/
	/** Constructor for the class.
	*
	*/
  EventNotifier_t();

	/*****************************************************************************/
	/** Constructor for the class.
	*
	* @param[in] uint8_t val
	* EventNotifier to be assigned
	*/
  EventNotifier_t(uint8_t val);

	/*****************************************************************************/
	/** Copy constructor
	*
	* @param[in] EventNotifier_t const & other
	* Object to be copied from
	*/
  EventNotifier_t(EventNotifier_t const & other);

	/*****************************************************************************/
	/** Destructor for the class.
	*
	*/
  virtual ~EventNotifier_t();

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
	/** Get the SubscribeToEvents bit from the Event Notifier
	*
	* @return
	* Returns the SubscribeToEvents bit from the Event Notifier
	*/
  bool SubscribeToEvents(void) const;

	/*****************************************************************************/
	/** Set the SubscribeToEvents bit from the Event Notifier
	*
	* @param[in] bool val
	* The SubscribeToEvents bit from the Event Notifier to set or clear
	*/
  void SubscribeToEvents(bool val);

	/*****************************************************************************/
	/** Get the HistoryRead bit from the Event Notifier
	*
	* @return
	* Returns the HistoryRead bit from the Event Notifier
	*/
  bool HistoryRead(void) const;

	/*****************************************************************************/
	/** Set the HistoryRead bit from the Event Notifier
	*
	* @param[in] bool val
	* The HistoryRead bit from the Event Notifier to set or clear
	*/
  void HistoryRead(bool val);

	/*****************************************************************************/
	/** Get the HistoryWrite bit from the Event Notifier
	*
	* @return
	* Returns the HistoryWrite bit from the Event Notifier
	*/
  bool HistoryWrite(void) const;

	/*****************************************************************************/
	/** Set the HistoryWrite bit from the Event Notifier
	*
	* @param[in] bool val
	* The HistoryWrite bit from the Event Notifier to set or clear
	*/
  void HistoryWrite(bool val);
};

/** @} */

} // namespace uasdk

#endif // _EVENT_NOTIFIER_T_
