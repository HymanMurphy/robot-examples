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

#ifndef _IREGISTER_NODE_LISTENER_T_
#define _IREGISTER_NODE_LISTENER_T_

#include "uasdk_includes.h"
#include "iref_count_t.h"

#if (UASDK_INCLUDE_SERVER > 0)
namespace uasdk
{

/** \addtogroup grpServer
 *@{*/

/*****************************************************************************/
/** \brief Register Node Listener
 *
 * A class provides interface to register and unregister the nodes to listen on accessing
 *
 */
class IRegisterNodeListener_t : public IRefCount_t
{
public:
  virtual ~IRegisterNodeListener_t() {};

  /*****************************************************************************/
  /** Listener called when node has been registered
   *
   * @param[in] sessionId
   * The ID of the session
   *
   * @param[in] nodeId
   * The NodeId to be registered
   *
   * @return
   * Returns the status of the operation
   */
  virtual Status_t RegisterNode(
    IntrusivePtr_t<const NodeId_t> sessionId,
    IntrusivePtr_t<const NodeId_t> nodeId) const = 0;

  /*****************************************************************************/
  /** Listner called when Node has been unregistered
   *
   * @param[in] sessionId
   * The ID of the session
   *
   * @param[in] nodeId
   * The NodeId to be unregistered
   *
   * @return
   * Returns the status of the operation
   */
  virtual Status_t UnregisterNode(
    IntrusivePtr_t<const NodeId_t> sessionId,
    IntrusivePtr_t<const NodeId_t> nodeId) const = 0;
};

/** @} */

}
#endif //#if (UASDK_INCLUDE_SERVER > 0)
#endif // _IREGISTER_NODE_LISTENER_T_
