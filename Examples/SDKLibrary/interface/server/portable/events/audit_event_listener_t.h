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

#ifndef __AUDIT_EVENT_LISTENER_T_
#define __AUDIT_EVENT_LISTENER_T_

#include "uasdk_includes.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "simple_attribute_operand_t.h"
#include "iattribute_access_t.h"
#include "iaudit_event_attribute_logger_t.h"
#include "allocatable_t.h"
#include "iaudit_event_listener_t.h"

namespace uasdk
{
/** \addtogroup grpEventsandAC
*@{*/

/*****************************************************************************/
/** \brief AuditEventListener_t
*
* This class is used for logging audit events
*
*/
class AuditEventListener_t : public IAuditEventListener_t, public Allocatable_t
{
private:
	/*****************************************************************************/
	/* @var IntrusiveList_t<SimpleAttributeOperand_t> simpleAttributeOperandList
	* List of attributes to be logged.
	*/
	IntrusiveList_t<SimpleAttributeOperand_t> simpleAttributeOperandList;

	/*****************************************************************************/
	/* @var IntrusivePtr_t<IAuditEventAttributeLogger_t> attributeLogger
	* The instance of the logger used to log the attributes.
	*/
	IntrusivePtr_t<IAuditEventAttributeLogger_t> attributeLogger;

public:

	/*****************************************************************************/
	/** constructor for the class.
	*
	*/
	AuditEventListener_t();

	/*****************************************************************************/
	/** Destructor for the class.
	*
	*/
	virtual ~AuditEventListener_t();

	/*****************************************************************************/
	/** Initialises the logger instance to be used.
	* @param[in] IntrusivePtr_t<IAuditEventAttributeLogger_t> attributeLogger_
	* input logger instance
	*
	*/
	Status_t Initialise(IntrusivePtr_t<IAuditEventAttributeLogger_t> attributeLogger_);

	/*****************************************************************************/
	/** Audit Event Occurred
	*
	* @param[in] auditEvent
	* The audit event that occurred
	*
	*/
	virtual void AuditEventOccured(IntrusivePtr_t<IAttributeAccess_t>& auditEvent) const;

	/*****************************************************************************/
	/** Adds the event attributes to be logged
	*
	* @param[in] IntrusivePtr_t<SimpleAttributeOperand_t>& simpleAttributeOperand
	* The audit event attribute to be logged.
	*
	*/
	Status_t AddAttributeToLog(IntrusivePtr_t<SimpleAttributeOperand_t>& simpleAttributeOperand);

	/*****************************************************************************/
	/** Adds the base event attributes to the list of attributes to be loggged.
	*
	*/
	Status_t AddBaseAttributeToLog(void);
};

/** @} */

}

#endif //UASDK_INCLUDE_EVENTS

#endif // __AUDIT_EVENT_LISTENER_T_
