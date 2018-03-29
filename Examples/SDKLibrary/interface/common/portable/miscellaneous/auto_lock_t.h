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

#ifndef AUTO_LOCK_T_H_
#define AUTO_LOCK_T_H_

#include "lock_t.h"

namespace uasdk
{
/** \addtogroup grpMiscellaneous
 *@{*/

/*****************************************************************************/
/** \brief AutoLock_t
 *
 * This class implements the interface to execute the code atomically
 *
 */
  class AutoLock_t
  {
  private:
    Lock_t& lock;

  public:

  /*****************************************************************************/
  /** Constructor for the class
   * Enters the critical section
   *
   * @param[in] Lock_t& lock_
   * Reference to the Critical section lock.
   */
    AutoLock_t(Lock_t& lock_) : lock(lock_)
    {
      lock.Enter();
    }

  /*****************************************************************************/
  /** Destructor for the class.
   * Exit the critical section
   */
    ~AutoLock_t()
    {
      lock.Exit();
    }
  };

/** @} */

} /* namespace uasdk */

#endif /* AUTO_LOCK_T_H_ */
