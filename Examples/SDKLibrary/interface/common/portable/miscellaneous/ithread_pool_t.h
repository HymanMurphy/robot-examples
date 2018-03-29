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

#ifndef _ITHREAD_POOL_T_
#define _ITHREAD_POOL_T_

#include "uasdk_includes.h"
#include "irunnable_t.h"
#include "status_t.h"

namespace uasdk
{
/** \addtogroup grpMiscellaneous
 *@{*/

class IThreadPool_t : public IRefCount_t
{
public:
  virtual ~IThreadPool_t() {};

  /*****************************************************************************/
  /** This function is used to queue the object to a thread.
   *
   * @param[in] objectToRun
   * object to queue on thread pool
   *
   * @return
   * returns the status of operation.
   *
   */
  virtual Status_t QueueToThreadPool(IntrusivePtr_t<IRunnable_t>& objectToRun) = 0;

  /*****************************************************************************/
  /** This function is used to operate the thread for single threaded implementations.
  *
  * @return
  * returns the status of operation. Returns OpcUa_BadNothingToDo if there are
  * no jobs to run.
  *
  */
  virtual Status_t Operate(void) = 0;

  /*****************************************************************************/
  /** This function will be used to shutdown the thread pool
  *
  * @return
  * return the status of the operation.
  */
  virtual Status_t Shutdown(void) = 0;

};

/** @} */

}

#endif // _ITHREAD_POOL_T_
