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

#ifndef _FINITE_TRANSITION_VARIABLE_TYPE_T_
#define _FINITE_TRANSITION_VARIABLE_TYPE_T_

#include "uasdk_includes.h"

#if ((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

#include "allocatable_t.h"
#include "opcua_date_time_t.h"
#include "opcua_node_id_t.h"
#include "opcua_qualified_name_t.h"
#include "opcua_uint32_t.h"
  
namespace uasdk
{

/** \addtogroup grpEventsandAC
*@{*/

/*****************************************************************************/
/** \brief FiniteTransitionVariableType_t
*
* This class implements the FiniteTransitionVariableType
* FiniteTransitionVariableType is used to represent states
*
*/
class FiniteTransitionVariableType_t : public Allocatable_t, public IRefCount_t
{
private:

  /*****************************************************************************/
  /* @var IntrusivePtr_t<NodeId_t> id
  * Id is inherited from the FiniteTransitionVariableType and overridden to reflect the required DataType (Boolean). 
  * The value shall be the current state, i.e. either TRUE or FALSE.
  */
  IntrusivePtr_t<NodeId_t> id;
  
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
  /* @var UtcTime_t transitionTime
  * transitionTime specifies the time when the current state was entered.
  */
  UtcTime_t transitionTime;

  /*****************************************************************************/
  /* @var UtcTime_t effectiveTransitionTime
  * effectiveTransitionTime specifies the time when the current state or one of its sub states was entered.
  */
  UtcTime_t effectiveTransitionTime;

public:

  /*****************************************************************************/
  /** Constructor for the class.
  *
  */
  FiniteTransitionVariableType_t();

  /*****************************************************************************/
  /** Destructor for the class.
  *
  */
  virtual ~FiniteTransitionVariableType_t();

  /*****************************************************************************/
  /** Initialise() the FiniteTransitionVariableType_t
  *
  * @param[in] initialState
  * initial value of id
  *
  * @return
  * status of the operation
  */
  Status_t Initialise(IntrusivePtr_t<NodeId_t> id_);

  /*****************************************************************************/
  /** Set the Id value
  *
  * @return
  * Returns the Id value
  */
  IntrusivePtr_t<NodeId_t>& Id(void);

  /*****************************************************************************/
  /** Get the Id value
  *
  * @return
  * Returns the Id value
  */
  IntrusivePtr_t<const NodeId_t> Id(void) const;

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
  /** Set the TransitionTime value
  *
  * @return
  * Returns the TransitionTime value
  */
  UtcTime_t& TransitionTime(void);

  /*****************************************************************************/
  /** Get the TransitionTime value
  *
  * @return
  * Returns the TransitionTime value
  */
  const UtcTime_t& TransitionTime(void) const;

  /*****************************************************************************/
  /** Set the EffectiveTransitionTime value
  *
  * @return
  * Returns the EffectiveTransitionTime value
  */
  UtcTime_t& EffectiveTransitionTime(void);

  /*****************************************************************************/
  /** Get the EffectiveTransitionTime value
  *
  * @return
  * Returns the EffectiveTransitionTime value
  */
  const UtcTime_t& EffectiveTransitionTime(void) const;

  /*****************************************************************************/
  /** Copy from the source
  *
  * @param[in] const FiniteTransitionVariableType_t& source
  *  FiniteTransitionVariableType_t source to copy from
  *
  * @return
  * Status of the operation
  */
  Status_t CopyFrom(const FiniteTransitionVariableType_t& source);

  /*****************************************************************************/
  /** Copy to the destination
  *
  * @param[out] IntrusivePtr_t<FiniteTransitionVariableType_t>& destination
  * Destination data type
  *
  * @return
  * Status of the operation
  */
  Status_t CopyTo(IntrusivePtr_t<FiniteTransitionVariableType_t>& destination);

};

/** @} */

}

#endif //((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

#endif // _FINITE_TRANSITION_VARIABLE_TYPE_T_
