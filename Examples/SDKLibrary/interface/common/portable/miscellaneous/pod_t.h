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

#ifndef _ALLOCATABLE_POD_T_
#define _ALLOCATABLE_POD_T_

#include "allocatable_t.h"
#include "iref_count_t.h"

namespace uasdk
{
/** \addtogroup grpMiscellaneous
 *@{*/

/*****************************************************************************/
/** \brief POD_t
 *
 * A Class to implements the  plain old data object
 *
 */
template<typename T> class POD_t : public Allocatable_t, public IRefCount_t
{
private:
  T value;

public:

  /*****************************************************************************/
  /** Get the Value
   *
   * @return
   * Returns the Value
   */
  const T& Value(void) const { return value; }

  /*****************************************************************************/
  /** Get the Value
   *
   * @return
   * Returns the Value
   */
  T& Value(void) { return value; }
};

/** @} */

}

#endif //_ALLOCATABLE_POD_T_
