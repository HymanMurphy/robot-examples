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

#ifndef _FINITE_STATE_VARIABLE_TYPE_T_
#define _FINITE_STATE_VARIABLE_TYPE_T_

#include "uasdk_includes.h"

#if ((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

#include "allocatable_t.h"
#include "opcua_localized_text_t.h"
#include "opcua_node_id_t.h"
#include "opcua_qualified_name_t.h"
#include "opcua_uint32_t.h"
  
namespace uasdk
{

/** \addtogroup grpEventsandAC
*@{*/

/*****************************************************************************/
/** \brief FiniteStateVariableType_t
*
* This class implements the FiniteStateVariableType
* FiniteStateVariableType is used to represent states
*
*/
class FiniteStateVariableType_t : public Allocatable_t, public IRefCount_t
{
private:

  /*****************************************************************************/
  /* @var IntrusivePtr_t<NodeId_t> id
  * Id is inherited from the FiniteStateVariableType and overridden to reflect the required DataType (Boolean). 
  * This value shall be the NodeId of one of the State Objects of the FiniteStateMachineType.
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
  /* @var IntrusivePtr_t<LocalizedText_t> effectiveDisplayName
  * effectiveDisplayName from the FiniteStateVariableType is used if a state has sub states. 
  * It contains a human readable name for the current state after taking the state of any SubStateMachines in account.
  */
  IntrusivePtr_t<LocalizedText_t> effectiveDisplayName;

public:

  /*****************************************************************************/
  /** Constructor for the class.
  *
  */
  FiniteStateVariableType_t();

  /*****************************************************************************/
  /** Destructor for the class.
  *
  */
  virtual ~FiniteStateVariableType_t();

  /*****************************************************************************/
  /** Initialise() the FiniteStateVariableType_t
  *
  * @param[in] id_
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
  /** Copy from the source
  *
  * @param[in] const FiniteStateVariableType_t& source
  *  FiniteStateVariableType_t source to copy from
  *
  * @return
  * Status of the operation
  */
  Status_t CopyFrom(const FiniteStateVariableType_t& source);

  /*****************************************************************************/
  /** Copy to the destination
  *
  * @param[out] IntrusivePtr_t<FiniteStateVariableType_t>& destination
  * Destination data type
  *
  * @return
  * Status of the operation
  */
  Status_t CopyTo(IntrusivePtr_t<FiniteStateVariableType_t>& destination);

};

/** @} */

}

#endif //((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

#endif // _FINITE_STATE_VARIABLE_TYPE_T_
