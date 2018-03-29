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

#ifndef ASYNC_OPERATION_T_H_
#define ASYNC_OPERATION_T_H_

#include "uasdk_includes.h"

#if (UASDK_INCLUDE_THREAD_POOL_ANY_PLATFORM_ST > 0)

#include "iref_count_t.h"
#include "allocatable_t.h"
#include "ithread_pool_t.h"
#include "iapplication_t.h"

namespace uasdk
{

  class AsyncOperation_t : public Allocatable_t, public IRefCount_t
  {
  private:
    IntrusivePtr_t<IApplication_t> application;
    bool isComplete;
    Status_t result;

  public:
    AsyncOperation_t() : isComplete(false) {}

    Status_t Initialise(const IntrusivePtr_t<IApplication_t>& application_)
    {
      UASDK_ASSERT(application_.is_set());
      UASDK_RETURN_UNEXPECTED_IF_NULL(application_);
      application = application_;
      return OpcUa_Good;
    }

    Status_t WaitForResult(void)
    {
      UASDK_RETURN_UNEXPECTED_IF_NULL(application);

      Status_t status;
      do
      {
        if (isComplete)
        {
          return result;
        }
        status = application->Poll();
      }
      while (status.IsGood());

      return status;
    }

    virtual void OnComplete(Status_t result_)
    {
      result = result_;
      isComplete = true;
    }

  };


} /* namespace uasdk */

#endif //UASDK_INCLUDE_THREAD_POOL_ANY_PLATFORM_ST

#endif /* ASYNC_OPERATION_T_H_ */
