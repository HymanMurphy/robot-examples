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

#ifndef THREAD_POOL_T_H_
#define THREAD_POOL_T_H_

#include "uasdk_includes.h"

#if (UASDK_INCLUDE_THREAD_POOL_CPP11 > 0)

#include <thread>
#include <mutex>
#include <vector>
#include <condition_variable>
#include "ithread_pool_t.h"
#include "safe_intrusive_embedded_queue_t.h"
#include "atomic_t.h"


namespace uasdk
{

  class ThreadPool_t : public IThreadPool_t, public Allocatable_t
  {
  private:
    std::mutex mtx;
    std::condition_variable cv;
    IntrusivePtr_t<SafeIntrusiveEmbeddedQueue_t<IRunnable_t> > runQueue;
    Atomic_t<bool> quit;
    Atomic_t<uint32_t> runningThreads;
    std::vector<std::thread> threads;
    bool running;

    /*****************************************************************************/
    /** Function used to dequeue the jobs from the queue.
     *
     */
    void MessagePump(void);

  public:
    ThreadPool_t();
    ~ThreadPool_t();

    /*****************************************************************************/
    /** Function used to create and initialize the threads.
     *
     * @param[in] noOfThreads
     * Number of threads to be create and initialize
     *
     * @return
     * returns the status of the operation
     */
    Status_t Initialise(uint32_t noOfThreads);

   /*****************************************************************************/
   /** Function used to enqueue or push the objects into the queue.
    *
    * @param[in] objectToRun
    * Object which is needs to be store into the queue
    *
    * @return
    * returns unsigned integer value.
    */
    virtual Status_t QueueToThreadPool(IntrusivePtr_t<IRunnable_t>& objectToRun);

    /*****************************************************************************/
     /** Function used to operate.
      *
      * @return
      * returns status of the operation
      */
    virtual Status_t Operate(void);

    Status_t Shutdown(void);

  };

} /* namespace uasdk */


#endif //UASDK_INCLUDE_THREAD_POOL_CPP11

#endif /* THREAD_POOL_T_H_ */
