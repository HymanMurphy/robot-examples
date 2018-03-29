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

#ifndef _TWO_STATE_VARIABLE_TYPE_T_
#define _TWO_STATE_VARIABLE_TYPE_T_

#include "uasdk_includes.h"

#if ((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

#include "allocatable_t.h"
#include "opcua_date_time_t.h"
#include "ilocalizable_text_t.h"
#include "opcua_localized_text_t.h"
#include "opcua_boolean_t.h"
#include "opcua_qualified_name_t.h"
#include "opcua_uint32_t.h"

namespace uasdk
{

/** \addtogroup grpEventsandAC
*@{*/

/*****************************************************************************/
/** \brief TwoStateVariableType_t
*
* This class implements the TwoStateVariableType
* TwoStateVariableType is used to represent states which has two values i.e. TRUE or FALSE
*
*/
class TwoStateVariableType_t : public Allocatable_t, public IRefCount_t
{
private:

  /*****************************************************************************/
  /* @var Boolean_t id
  * Id is inherited from the StateVariableType and overridden to reflect the required DataType (Boolean). 
  * The value shall be the current state, i.e. either TRUE or FALSE.
  */
  IntrusivePtr_t<Boolean_t> id;

  /*****************************************************************************/
  /* @var UtcTime_t transitionTime
  * transitionTime specifies the time when the current state was entered.
  */
  IntrusivePtr_t<UtcTime_t> transitionTime;

  /*****************************************************************************/
  /* @var UtcTime_t effectiveTransitionTime
  * effectiveTransitionTime specifies the time when the current state or one of its sub states was entered.
  */
  IntrusivePtr_t<UtcTime_t> effectiveTransitionTime;

  /*****************************************************************************/
  /* @var IntrusivePtr_t<ILocalizableText_t> trueState
  * trueState contain the localized string for the TwoStateVariable value when its Id Property has the value TRUE.
  */
  IntrusivePtr_t<ILocalizableText_t> trueState;

  /*****************************************************************************/
  /* @var IntrusivePtr_t<ILocalizableText_t> falseState
  * falseState contain the localized string for the TwoStateVariable value when its Id Property has the value FALSE.
  */
  IntrusivePtr_t<ILocalizableText_t> falseState;

  /*****************************************************************************/
  /* @var IntrusivePtr_t<QualifiedName_t> name
  * name is a QualifiedName which uniquely identifies the current state within the StateMachineType.
  */
  IntrusivePtr_t<QualifiedName_t> name;

  /*****************************************************************************/
  /* @var IntrusivePtr_t<UInt32_t> number
  * number is an integer which uniquely identifies the current state within the StateMachineType.
  */
  IntrusivePtr_t<UInt32_t> number;

  /*****************************************************************************/
  /* @var IntrusivePtr_t<LocalizedText_t> effectiveDisplayName
  * effectiveDisplayName from the StateVariableType is used if a state has sub states. 
  * It contains a human readable name for the current state after taking the state of any SubStateMachines in account.
  */
  IntrusivePtr_t<LocalizedText_t> effectiveDisplayName;

public:

  /*****************************************************************************/
  /** Constructor for the class.
  *
  */
  TwoStateVariableType_t();

  /*****************************************************************************/
  /** Destructor for the class.
  *
  */
  virtual ~TwoStateVariableType_t();

  /*****************************************************************************/
  /** Initialise() the TwoStateVariableType_t
  *
  * @param[in] initialState
  * initial value of id
  *
  * @param[in trueState_
  * list of localizable text for TrueState
  *
  * @param[in falseState_
  * list of localizable text for FalseState
  *
  * @return
  * status of the operation
  */
  Status_t Initialise(
    bool initialState,
    IntrusivePtr_t<ILocalizableText_t> trueState_,
    IntrusivePtr_t<ILocalizableText_t> falseState_);

  /*****************************************************************************/
  /** Set the Id value
  *
  * @return
  * Returns the Id value
  */
  IntrusivePtr_t<Boolean_t>& Id(void);

  /*****************************************************************************/
  /** Get the Id value
  *
  * @return
  * Returns the Id value
  */
  IntrusivePtr_t<const Boolean_t> Id(void) const;

  /*****************************************************************************/
  /** Set the TransitionTime value
  *
  * @return
  * Returns the TransitionTime value
  */
  IntrusivePtr_t<UtcTime_t>& TransitionTime(void);

  /*****************************************************************************/
  /** Get the TransitionTime value
  *
  * @return
  * Returns the TransitionTime value
  */
  IntrusivePtr_t<const UtcTime_t> TransitionTime(void) const;

  /*****************************************************************************/
  /** Set the EffectiveTransitionTime value
  *
  * @return
  * Returns the EffectiveTransitionTime value
  */
  IntrusivePtr_t<UtcTime_t>& EffectiveTransitionTime(void);

  /*****************************************************************************/
  /** Get the EffectiveTransitionTime value
  *
  * @return
  * Returns the EffectiveTransitionTime value
  */
  IntrusivePtr_t<const UtcTime_t> EffectiveTransitionTime(void) const;

  /*****************************************************************************/
  /** Get the TrueState value
  *
  * @return
  * Returns the TrueState value
  */
  IntrusivePtr_t<const ILocalizableText_t> TrueState(void) const;

  /*****************************************************************************/
  /** Set the TrueState value
  *
  * @return
  * Returns the TrueState value
  */
  IntrusivePtr_t<ILocalizableText_t>& TrueState(void);

  /*****************************************************************************/
  /** Get the FalseState value
  *
  * @return
  * Returns the FalseState value
  */
  IntrusivePtr_t<const ILocalizableText_t> FalseState(void) const;

  /*****************************************************************************/
  /** Set the FalseState value
  *
  * @return
  * Returns the FalseState value
  */
  IntrusivePtr_t<ILocalizableText_t>& FalseState(void);
  
  /*****************************************************************************/
  /** Get the Name value
  *
  * @return
  * Returns the Name value
  */
  IntrusivePtr_t<const QualifiedName_t> Name(void) const;

  /*****************************************************************************/
  /** Set the Name value
  *
  * @return
  * Returns the Name value
  */
  IntrusivePtr_t<QualifiedName_t>& Name(void);

  /*****************************************************************************/
  /** Get the Number value
  *
  * @return
  * Returns the Number value
  */
  IntrusivePtr_t<const UInt32_t> Number(void) const;

  /*****************************************************************************/
  /** Set the Number value
  *
  * @return
  * Returns the Number value
  */
  IntrusivePtr_t<UInt32_t>& Number(void);

  /*****************************************************************************/
  /** Get the EffectiveDisplayName value
  *
  * @return
  * Returns the EffectiveDisplayName value
  */
  IntrusivePtr_t<const LocalizedText_t> EffectiveDisplayName(void) const;

  /*****************************************************************************/
  /** Set the EffectiveDisplayName value
  *
  * @return
  * Returns the EffectiveDisplayName value
  */
  IntrusivePtr_t<LocalizedText_t>& EffectiveDisplayName(void);

  /*****************************************************************************/
  /** Get the state value
  *
  * @return
  * Returns the state value
  */
  IntrusivePtr_t<const ILocalizableText_t> Value(void);

  /*****************************************************************************/
  /** Copy from the source
  *
  * @param[in] const TwoStateVariableType_t& source
  *  TwoStateVariableType_t source to copy from
  *
  * @return
  * Status of the operation
  */
  Status_t CopyFrom(const TwoStateVariableType_t& source);

  /*****************************************************************************/
  /** Copy to the destination
  *
  * @param[out] IntrusivePtr_t<TwoStateVariableType_t>& destination
  * Destination data type
  *
  * @return
  * Status of the operation
  */
  Status_t CopyTo(IntrusivePtr_t<TwoStateVariableType_t>& destination);

};

/** @} */

}

#endif //((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

#endif // _TWO_STATE_VARIABLE_TYPE_T_
