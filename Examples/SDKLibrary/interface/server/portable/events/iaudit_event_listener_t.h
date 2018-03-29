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

#ifndef _IAUDIT_EVENT_LISTENER_T_
#define _IAUDIT_EVENT_LISTENER_T_

#include "uasdk_includes.h"
#if (UASDK_INCLUDE_SERVER > 0)

#if (UASDK_INCLUDE_EVENTS > 0)

#include "iref_count_t.h"
#include "status_t.h"
#include "iattribute_access_t.h"

namespace uasdk
{

/** \addtogroup grpServer
 *@{*/

/*****************************************************************************/
/** \brief Audit Event Listener
 *
 * This class provides interfaces to listen for audit events generated in the server stack
 *
 */
class IAuditEventListener_t : public IRefCount_t
{
public:
  virtual ~IAuditEventListener_t() {};

  /*****************************************************************************/
  /** Audit Event Occurred
   *
   * @param[in] auditEvent
	 * The audit event that occurred
   *
   */
  virtual void AuditEventOccured(IntrusivePtr_t<IAttributeAccess_t>& auditEvent) const = 0;

};

/** @} */

}

#endif // UASDK_INCLUDE_EVENTS > 0

#endif //#if (UASDK_INCLUDE_SERVER > 0)
#endif // _IAUDIT_EVENT_LISTENER_T_
