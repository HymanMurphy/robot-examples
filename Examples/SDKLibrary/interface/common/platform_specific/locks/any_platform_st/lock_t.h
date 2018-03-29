/* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                        COPYRIGHT (c) 2009 - 2017
                                         HONEYWELL INC.,
                                        ALL RIGHTS RESERVED

            This software is a copyrighted work and/or information protected as a trade
            secret. Legal rights of Honeywell Inc. in this software are distinct from
            ownership of any medium in which the software is embodied. Copyright or trade
            secret notices included must be reproduced in any copies authorized by
            Honeywell Inc. The information in this software is subject to change without
            notice and should not be considered as a commitment by Honeywell Inc.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////// */

#ifndef LOCK_T_H_
#define LOCK_T_H_

#include "uasdk_includes.h"

#if (UASDK_INCLUDE_LOCKS_ANY_PLATFORM_ST > 0)

namespace uasdk
{

  class Lock_t
  {
  public:
  /*****************************************************************************/
  /** function used to initialize the object
   *
   * @return
   * returns result of the operation.
   */
    Status_t Initialise(void)
    {
      return OpcUa_Good;
    }

  /*****************************************************************************/
  /** This function used for locking the resource before accessing the same.
   *  This function will be empty for single threaded systems. 
   *
   */
    void Enter(void)
    {
    }
  
  /*****************************************************************************/
  /** This function will unlock the resource after usage.
   *  This function will be empty for single threaded systems. 
   *
   */

    void Exit(void)
    {
    }
  };

} /* namespace uasdk */

#endif //UASDK_INCLUDE_LOCKS_ANY_PLATFORM_ST

#endif /* LOCK_T_H_ */
