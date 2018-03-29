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

#ifndef _FINITE_STATE_MACHINE_TYPE_T_
#define _FINITE_STATE_MACHINE_TYPE_T_

#include "uasdk_includes.h"

#if ((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

#include "allocatable_t.h"
#include "ilocalizable_text_t.h"
#include "finite_state_variable_type_t.h"
#include "finite_transition_variable_type_t.h"
  
namespace uasdk
{

/** \addtogroup grpEventsandAC
*@{*/

/*****************************************************************************/
/** \brief FiniteStateMachineType_t
*
* This class implements the FiniteStateMachineType
* FiniteStateMachineType is used to represent states which has two values i.e. TRUE or FALSE
*
*/
class FiniteStateMachineType_t : public Allocatable_t, public IRefCount_t
{
private:

  /*****************************************************************************/
  /* @var IntrusivePtr_t<FiniteStateVariableType_t> currentStateProperties
  * This will hold the properties of currentStateValue
  */
  IntrusivePtr_t<FiniteStateVariableType_t> currentStateProperties;

  /*****************************************************************************/
  /* @var IntrusivePtr_t<FiniteTransitionVariableType_t> lastTransitionProperties
  * This will hold the properties of lastTransitionValue
  */
  IntrusivePtr_t<FiniteTransitionVariableType_t> lastTransitionProperties;

  /*****************************************************************************/
  /* @var IntrusivePtr_t<ILocalizableText_t> currentStateValue
  * CurrentState stores the current state of an instance of the FiniteStateMachineType
  */
  IntrusivePtr_t<ILocalizableText_t> currentStateValue;

  /*****************************************************************************/
  /* @var IntrusivePtr_t<ILocalizableText_t> lastTransitionValue
  * LastTransition stores the last transition which occurred in an instance of the FiniteStateMachineType.
  */
  IntrusivePtr_t<ILocalizableText_t> lastTransitionValue;

public:

  /*****************************************************************************/
  /** Constructor for the class.
  *
  */
  FiniteStateMachineType_t();

  /*****************************************************************************/
  /** Destructor for the class.
  *
  */
  virtual ~FiniteStateMachineType_t();

  /*****************************************************************************/
  /** Initialise() the FiniteStateMachineType_t
  *
  * @return
  * status of the operation
  */
  Status_t Initialise();

  /*****************************************************************************/
  /** Get the CurrentState properties
  *
  * @return
  * Returns the CurrentState value
  */
  IntrusivePtr_t<const FiniteStateVariableType_t> CurrentStateProperties(void) const;

  /*****************************************************************************/
  /** Set the CurrentState properties
  *
  * @return
  * Returns the CurrentState value
  */
  IntrusivePtr_t<FiniteStateVariableType_t>& CurrentStateProperties(void);

  /*****************************************************************************/
  /** Get the LastTransition properties
  *
  * @return
  * Returns the LastTransition value
  */
  IntrusivePtr_t<const FiniteTransitionVariableType_t> LastTransitionProperties(void) const;

  /*****************************************************************************/
  /** Set the LastTransition properties
  *
  * @return
  * Returns the LastTransition value
  */
  IntrusivePtr_t<FiniteTransitionVariableType_t>& LastTransitionProperties(void);

  /*****************************************************************************/
  /** Get the CurrentState value
  *
  * @return
  * Returns the CurrentState value
  */
  IntrusivePtr_t<const ILocalizableText_t> CurrentStateValue(void) const;

  /*****************************************************************************/
  /** Set the CurrentState value
  *
  * @return
  * Returns the CurrentState value
  */
  IntrusivePtr_t<ILocalizableText_t>& CurrentStateValue(void);

  /*****************************************************************************/
  /** Get the LastTransition value
  *
  * @return
  * Returns the LastTransition value
  */
  IntrusivePtr_t<const ILocalizableText_t> LastTransitionValue(void) const;

  /*****************************************************************************/
  /** Set the LastTransition value
  *
  * @return
  * Returns the LastTransition value
  */
  IntrusivePtr_t<ILocalizableText_t>& LastTransitionValue(void);

  /*****************************************************************************/
  /** Copy from the source
  *
  * @param[in] const FiniteStateMachineType_t& source
  *  FiniteStateMachineType_t source to copy from
  *
  * @return
  * Status of the operation
  */
  Status_t CopyFrom(const FiniteStateMachineType_t& source);

  /*****************************************************************************/
  /** Copy to the destination
  *
  * @param[out] IntrusivePtr_t<FiniteStateMachineType_t>& destination
  * Destination data type
  *
  * @return
  * Status of the operation
  */
  Status_t CopyTo(IntrusivePtr_t<FiniteStateMachineType_t>& destination);

};

/** @} */

}

#endif //((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

#endif // _FINITE_STATE_MACHINE_TYPE_T_
