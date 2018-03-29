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

#ifndef _IAUDIT_EVENT_ATTRIBUTE_LOGGER_T_
#define _IAUDIT_EVENT_ATTRIBUTE_LOGGER_T_

#include "uasdk_includes.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "iref_count_t.h"
#include "opcua_base_data_type_t.h"

namespace uasdk
{
/** \addtogroup grpEventsandAC
*@{*/

/*****************************************************************************/
/** \brief IAuditEventAttributeLogger_t
*
* This class is used  to log attributes of audit events
*
*/
class IAuditEventAttributeLogger_t : public IRefCount_t
{
public:
	virtual ~IAuditEventAttributeLogger_t() {};

	/*****************************************************************************/
	/** Audit Event Logger
	*
	* @param[in] attribute
	* The attribute value has to be printed on Console or in LogFile
	*
	*/
	virtual void LogAttribute(IntrusivePtr_t<BaseDataType_t> attribute) const = 0;

	/*****************************************************************************/
	/** Audit Event Logger
	*
	* @param[in] data
	* The data value has to be printed on Console or in LogFile
	*
	*/
	virtual void LogAttribute(const char* data) const = 0;
};

/** @} */

}

#endif // UASDK_INCLUDE_EVENTS

#endif // _IAUDIT_EVENT_ATTRIBUTE_LOGGER_T_
