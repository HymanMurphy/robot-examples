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

#ifndef _ISERVER_STATE_LISTENER_T_
#define _ISERVER_STATE_LISTENER_T_

#include "uasdk_includes.h"
#include "opcua_server_state_t.h"
#include "iref_count_t.h"

#if (UASDK_INCLUDE_SERVER > 0)
namespace uasdk
{

/** \addtogroup grpServer
 *@{*/

/*****************************************************************************/
/** \brief Server State Listener
 *
 * A class provides interface to detect the server state changes
 *
 */
class IServerStateListener_t : public IRefCount_t
{
public:
  virtual ~IServerStateListener_t() {};

  /*****************************************************************************/
  /** Server state changed
   *
   *  This function is called when a server state has been changed.
   *  With this function the application layer can take the necessary actions
   *  on server state change
   *
   * @param[in] state
   * The Server State
   */
  virtual void StateHasChanged(ServerState_t::Enum_t state) const = 0;

  /*****************************************************************************/
  /** An unhandled error occurred
  *
  *  This function is called when an error occurs internally in the server
  *  which is not handled. This should be logged by the application.
  *
  * @param[in] errorCode
  * The unhandled error
  */
  virtual void UnhandledError(Status_t errorCode) const = 0;

};

/** @} */

}

#endif //#if (UASDK_INCLUDE_SERVER > 0)
#endif // _ISERVER_STATE_LISTENER_T_
