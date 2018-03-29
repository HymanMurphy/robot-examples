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

#ifndef THREAD_POOL_T_H_
#define THREAD_POOL_T_H_

#include "uasdk_includes.h"

#if (UASDK_INCLUDE_THREAD_POOL_ANY_PLATFORM_ST > 0)

#include "safe_intrusive_embedded_queue_t.h"

namespace uasdk
{

  class ThreadPool_t : public IThreadPool_t, public Allocatable_t
  {
  private:
    IntrusiveEmbeddedQueue_t<IRunnable_t> runQueue;
    bool running;

  public:
    ThreadPool_t() : running(true)
    {}

    /*****************************************************************************/
    /** Function used to enqueue or push the objects into the queue.
     *
     * @param[in] objectToRun
     * Object which is needs to be store into the queue
     *
     * @return
     * returns unsigned integer value.
     */
    virtual Status_t QueueToThreadPool(IntrusivePtr_t<IRunnable_t>& objectToRun)
    {
      if (running)
      {
        runQueue.Push(objectToRun);
      }
      return OpcUa_Good;
    }

    /*****************************************************************************/
    /** Function used to dequeue or pop the objects from the queue.
     *
     * @param[in] objectToRun
     * Object which is need to access from the queue
     *
     * @return
     * returns unsigned integer value.
     */
    virtual Status_t Operate(void)
    {
      IntrusivePtr_t<IRunnable_t> job;
      Status_t status = OpcUa_BadNothingToDo;
      runQueue.Pop(job);
      if (job.is_set())
      {
        job->Run();
        status = OpcUa_GoodCallAgain;
      }
      return status;
    }

    /*****************************************************************************/
    /** This function will be used to shutdown the thread pool
    *
    * @return
    * return the status of the operation.
    */
    virtual Status_t Shutdown(void)
    {
      IntrusivePtr_t<IRunnable_t> job;
      do 
      {
        runQueue.Pop(job);
      } while (job.is_set());

      running = false;
      return OpcUa_Good;
    }

  };

} /* namespace uasdk */

#endif //UASDK_INCLUDE_THREAD_POOL_ANY_PLATFORM_ST

#endif /* THREAD_POOL_T_H_ */
