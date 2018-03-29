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

#ifndef _TRANSITION_TYPE_T_
#define _TRANSITION_TYPE_T_

#include "uasdk_includes.h"

#if ((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

#include "allocatable_t.h"
#include "opcua_uint32_t.h"

namespace uasdk
{
/** \addtogroup grpEventsandAC
*@{*/

/*****************************************************************************/
/** \brief TransitionType_t
*
* Transitions of a FiniteStateMachine are represented as Objects of the ObjectType TransitionType
*
*/
class TransitionType_t : public Allocatable_t, public IRefCount_t
{
private:

  /*****************************************************************************/
  /* @var UInt32_t transitionNumber
  * state number of the state
  */
  UInt32_t transitionNumber;

public:

  /*****************************************************************************/
  /** Constructor for the class.
  *
  */
  TransitionType_t();

  /*****************************************************************************/
  /** Destructor for the class.
  *
  */
  virtual ~TransitionType_t();

  /*****************************************************************************/
  /** Initialise() the TransitionType
  *
  * @return
  * status of the operation
  */
  Status_t Initialise();

  /*****************************************************************************/
  /** Get the TransitionNumber value
  *
  * @return
  * Returns the TransitionNumber value
  */
  const UInt32_t TransitionNumber(void) const;

  /*****************************************************************************/
  /** Set the TransitionNumber value
  *
  * @return
  * Returns the TransitionNumber value
  */
  UInt32_t& TransitionNumber(void);
 
  /*****************************************************************************/
  /** Copy from the source
  *
  * @param[in] const TransitionType_t& source
  *  TransitionType_t source to copy from
  *
  * @return
  * Status of the operation
  */
  Status_t CopyFrom(const TransitionType_t& source);

  /*****************************************************************************/
  /** Copy to the destination
  *
  * @param[out] IntrusivePtr_t<TransitionType_t>& destination
  * Destination data type
  *
  * @return
  * Status of the operation
  */
  Status_t CopyTo(IntrusivePtr_t<TransitionType_t>& destination);

};

/** @} */

}

#endif //((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

#endif // _TRANSITION_TYPE_T_
