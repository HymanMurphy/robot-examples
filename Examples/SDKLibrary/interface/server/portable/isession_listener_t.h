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

#ifndef _ISESSION_LISTENER_T_
#define _ISESSION_LISTENER_T_

#include "uasdk_includes.h"

#if (UASDK_INCLUDE_SERVER > 0)

#include "opcua_server_state_t.h"
#include "opcua_node_id_t.h"
#include "iref_count_t.h"

namespace uasdk
{

/** \addtogroup grpServer
 *@{*/

/*****************************************************************************/
/** \brief Session Listener
 *
 * A class provides interface to detect the session state changes
 *
 */
  class ISessionListener_t : public IRefCount_t
  {
  public:
    /*****************************************************************************/
    /** Session created callback
    *
    * This function will be called by the SDK when the session is created
    */
    virtual void SessionCreated(IntrusivePtr_t<const NodeId_t>& sessionId) = 0;

    /*****************************************************************************/
    /** Session Activated callback
    *
    * This function will be called by the SDK when the session is Activated
    */
    virtual void SessionActivated(IntrusivePtr_t<const NodeId_t>& sessionId) = 0;

    /*****************************************************************************/
    /** Session closed callback
    *
    * This function will be called by the SDK when the session is closed
    */
    virtual void SessionClosed(IntrusivePtr_t<const NodeId_t>& sessionId) = 0;
  };

/** @} */

}

#endif // (UASDK_INCLUDE_SERVER > 0)

#endif // _ISESSION_LISTENER_T_
