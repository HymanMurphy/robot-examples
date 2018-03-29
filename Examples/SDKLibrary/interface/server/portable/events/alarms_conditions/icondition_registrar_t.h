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

#ifndef _ICONDITION_REGISTRAR_T_
#define _ICONDITION_REGISTRAR_T_

#include "inode_method_handler_t.h"

#if ((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

#include "auto_lock_t.h"
#include "icondition_t.h"
#include "iserver_configuration_t.h"

namespace uasdk
{

/** \addtogroup grpEventsandAC
*@{*/

/*****************************************************************************/
/** \brief Condition Registrar
*
* A class that is used to maintain the list of conditions created.
*
*/

class IConditionRegistrar_t : public INodeMethodHandler_t, public Allocatable_t
{
public:

  virtual ~IConditionRegistrar_t() {}

  /*****************************************************************************/
  /** Register the condition with the Condition Registrar
  *
  *  @param[in] condition
  *  Intrusive pointer of type ICondition_t, which needs to be registered
  *
  * @return
  * status of the operation
  */
  virtual Status_t Register(IntrusivePtr_t<ICondition_t> condition) = 0;

  /*****************************************************************************/
  /** Unregister the condition with the Condition Registrar
  *
  *  @param[in] condition
  *  Intrusive pointer of type ICondition_t, which needs to be unregistered
  *
  * @return
  * status of the operation
  */
  virtual Status_t UnRegister(IntrusivePtr_t<ICondition_t> condition) = 0;

  /*****************************************************************************/
  /** Unregister all the conditions in the Condition Registrar
  *
  * @return
  * status of the operation
  */
  virtual Status_t UnRegisterAll(void) = 0;

  /*****************************************************************************/
  /** Get the condition from the condition registrar based on the input condition id
  *
  *  @param[in] conditionId
  *  input condition id for the condition
  *
  *  @param[out] result
  *  status of the operation
  *
  * @return
  * condition instance if found, else returns empty instance
  */
  virtual IntrusivePtr_t<const ICondition_t> GetCondition(const NodeId_t& conditionId, Status_t& result) const = 0;

  /*****************************************************************************/
  /** Get the condition from the condition registrar based on the input condition id
  *
  *  @param[in] conditionId
  *  input condition id for the condition
  *
  *  @param[out] result
  *  status of the operation
  *
  * @return
  * condition instance if found, else returns empty instance
  */
  virtual IntrusivePtr_t<ICondition_t> GetCondition(const NodeId_t& conditionId, Status_t& result) = 0;

  /*****************************************************************************/
  /** Check if the input conditionId exists in the address space and condition registrar
  *
  *  @param[in] conditionId
  *  input condition id for the condition
  *
  * @return
  * return Good if the input conditionId is unique and does not exists in the 
  * address space and condition registrar, else return BadNodeIdExists.
  */
  virtual Status_t CheckConditionIdIsAvaiable(const NodeId_t& conditionId) = 0;

};

/** @} */

} // namespace uasdk

#endif //((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

#endif // _ICONDITION_REGISTRAR_T_
