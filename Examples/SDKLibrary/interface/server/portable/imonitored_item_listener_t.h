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

#ifndef _IMONITORED_ITEM_LISTENER_T_
#define _IMONITORED_ITEM_LISTENER_T_

#include "uasdk_includes.h"
#include "opcua_monitoring_mode_t.h"
#include "opcua_timestamps_to_return_t.h"
#include "opcua_uint32_t.h"
#include "iref_count_t.h"

#if (UASDK_INCLUDE_SERVER > 0)
namespace uasdk
{

class INode_t;
class MonItemCreateRequest_t;
class MonItemCreateResult_t;
class MonItemModifyRequest_t;
class MonItemModifyResult_t;
class StatusCode_t;
class DiagnosticInfo_t;

/** \addtogroup grpServer
 *@{*/

/*****************************************************************************/
/** \brief Monitored Item Listener
 *
 * A class provides listener for Monitored item.
 *
 */
class IMonitoredItemListener_t : public IRefCount_t
{
public:
  virtual ~IMonitoredItemListener_t() {};

#if (UASDK_INCLUDE_SUBSCRIPTIONS > 0)

  /*****************************************************************************/
  /** Monitor item created listener
   *
   * This functions will be called when a monitored item is created.
   * Server can do necessary action if required when a monitored item is created.
   *
   * @param[in] node
   * The Node which is Monitored
   *
   * @param[in] monitoredItemId
   * The Monitored Item ID
   *
   * @param[in] revisedSamplingInterval
   * The Revised Sampling Interval of the monitored item
   *
   * @param[in] timestampsToReturn
   * The time stamp to return for the monitored item
   *
   * @param[in] monitoringMode
   * The monitoring mode of the Monitored item
   */
  virtual void MonitoredItemCreated(IntrusivePtr_t<const INode_t>& node,
                                    uint32_t monitoredItemId,
                                    uint64_t revisedSamplingInterval,
                                    TimestampsToReturn_t::Enum_t timestampsToReturn,
                                    MonitoringMode_t::Enum_t monitoringMode) const = 0;

  /*****************************************************************************/
  /** Monitored item mode set listener
   *
   * This functions will be called when the monitored item mode has been set with new value
   *
   * @param[in] node
   * The Node of the Monitored item
   *
   * @param[in] monitoredItemId
   * The Monitored Item ID
   *
   * @param[in] monitoringMode
   * The monitoring mode to be set
   */
  virtual void MonitoredItemMonitoringModeSet(IntrusivePtr_t<const INode_t>& node,
                                              uint32_t monitoredItemId,
                                              MonitoringMode_t::Enum_t monitoringMode) const = 0;

  /*****************************************************************************/
  /** Monitored item modified listner
   *
   * This functions will be called when the monitored item is modified.
   *
   * @param[in] node
   * The Node to be Monitored
   *
   * @param[in] monitoredItemId
   * The Monitored Item ID
   *
   * @param[in] revisedSamplingInterval
   * The Revised Sampling Interval
   *
   * @param[in] timestampsToReturn
   * The time stamp to return
   *
   * @param[in] monitoringMode
   * The monitoring mode of the Monitored item
   */
  virtual void MonitoredItemModified(IntrusivePtr_t<const INode_t>& node,
                                     uint32_t monitoredItemId,
                                     uint64_t revisedSamplingInterval,
                                     TimestampsToReturn_t::Enum_t timestampsToReturn,
                                     MonitoringMode_t::Enum_t monitoringMode) const = 0;

  /*****************************************************************************/
  /** monitored item listner
   *
   * This functions will be called when the monitored item is deleted.
   *
   * @param[in] node
   * The Node of the Monitored item
   *
   * @param[in] monitoredItemId
   * The Monitored Item ID
   */
  virtual void MonitoredItemDeleted(IntrusivePtr_t<const INode_t>& node,
                                    uint32_t monitoredItemId) const = 0;

#endif //UASDK_INCLUDE_SUBSCRIPTIONS
};

/** @} */

}
#endif //#if (UASDK_INCLUDE_SERVER > 0)
#endif // _IMONITORED_ITEM_LISTENER_T_
