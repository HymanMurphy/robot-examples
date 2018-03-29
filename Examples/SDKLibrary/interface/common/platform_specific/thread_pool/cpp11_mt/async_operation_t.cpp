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

#include "async_operation_t.h"

#if (UASDK_INCLUDE_THREAD_POOL_CPP11 > 0)

namespace uasdk
{

AsyncOperation_t::AsyncOperation_t()
{}

AsyncOperation_t::~AsyncOperation_t()
{}

Status_t AsyncOperation_t::Initialise(const IntrusivePtr_t<IApplication_t>&)
{
  result = OpcUa_Good;
  return OpcUa_Good;
}

Status_t AsyncOperation_t::WaitForResult()
{
  std::unique_lock<std::mutex> lock(mtx);
  cv.wait(lock);
  return result;
}

void AsyncOperation_t::OnComplete(Status_t result_)
{
  {
    std::unique_lock<std::mutex> lock(mtx);
    result = result_;
  }
  cv.notify_one();
}

}

#endif  //(UASDK_INCLUDE_THREAD_POOL_CPP11 > 0)
