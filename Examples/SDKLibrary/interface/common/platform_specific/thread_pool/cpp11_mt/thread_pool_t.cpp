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

#include "thread_pool_t.h"

#if (UASDK_INCLUDE_THREAD_POOL_CPP11 > 0)

#include "safe_ref_count_t.h"

namespace uasdk 
{
  void ThreadPool_t::MessagePump(void)
  {
    runningThreads.Increment();
    while (quit.Value() == false)
    {
      std::unique_lock<std::mutex> lk(mtx);
      cv.wait(lk);
      lk.unlock();

      IntrusivePtr_t<IRunnable_t> job;
      runQueue->Pop(job);
      while (job.is_set())
      {
        job->Run();
        runQueue->Pop(job);
      }
    }
    runningThreads.Decrement();
  }

  ThreadPool_t::ThreadPool_t() : running(false)
  {
    runningThreads.Value(0);
  }

  ThreadPool_t::~ThreadPool_t()
  {
    if (!threads.empty())
    {
      quit.Value(true);
      cv.notify_all();
      for (auto& t : threads)
      {
        t.join();
      }
    }
  }

  Status_t ThreadPool_t::Initialise(uint32_t noOfThreads)
  {
    runQueue = new SafeRefCount_t<SafeIntrusiveEmbeddedQueue_t<IRunnable_t> >();
    if (!runQueue.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }
    Status_t status = runQueue->Initialise();
    if (status.IsBad())
    {
      return status;
    }

    quit.Value(false);

    for (uint32_t i = 0; i < noOfThreads; i++)
    {
      threads.push_back(std::thread(&ThreadPool_t::MessagePump, this));
    }
    while ((uint32_t)(runningThreads.Value()) < noOfThreads)
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    running = true;

    return OpcUa_Good;
  }

    Status_t ThreadPool_t::QueueToThreadPool(IntrusivePtr_t<IRunnable_t>& objectToRun)
    {
      if (running)
      {
        runQueue->Push(objectToRun);
        cv.notify_one();
      }
      return OpcUa_Good;
    }

    Status_t ThreadPool_t::Operate(void)
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadNothingToDo);
    }

    uasdk::Status_t ThreadPool_t::Shutdown(void)
    {
      quit.Value(true);
      cv.notify_all();
      for (auto& t : threads)
      {
        t.join();
      }
      threads.clear();

      running = false;

      return OpcUa_Good;
    }
  }

#endif //UASDK_INCLUDE_THREAD_POOL_CPP11