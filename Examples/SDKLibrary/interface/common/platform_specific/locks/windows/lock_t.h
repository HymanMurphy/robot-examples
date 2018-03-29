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

#ifndef LOCK_T_H_
#define LOCK_T_H_

#include "uasdk_includes.h"

#if (UASDK_INCLUDE_LOCKS_WINDOWS > 0)

#include <windows.h>
#include <synchapi.h>

namespace uasdk
{

  class Lock_t
  {
  private:
    CRITICAL_SECTION criticalSection;
    bool initialised;

  public:
    Lock_t() : initialised(false) {}

    ~Lock_t()
    {
      if (initialised)
      {
        DeleteCriticalSection(&criticalSection);
      }
    }

  /*****************************************************************************/
  /** function used to initialize with critical section
   *
   * @return
   * returns result of the operation.
   */
    Status_t Initialise(void)
    {
      InitializeCriticalSection(&criticalSection);
      initialised = true;
      return OpcUa_Good;
    }

  /*****************************************************************************/
  /** This function allows to enter critical section.
   *
   */
    void Enter(void)
    {
      EnterCriticalSection(&criticalSection);
    }
  /*****************************************************************************/
  /** This function allows to leave critical section.
   *
   */
    void Exit(void)
    {
      LeaveCriticalSection(&criticalSection);
    }
  };

} /* namespace uasdk */

#endif  //UASDK_INCLUDE_LOCKS_WINDOWS

#endif /* LOCK_T_H_ */
