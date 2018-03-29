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

#ifndef ASYNC_OPERATION_T_H_
#define ASYNC_OPERATION_T_H_

#include "uasdk_includes.h"

#if (UASDK_INCLUDE_THREAD_POOL_CPP11 > 0)

#include "iref_count_t.h"
#include "allocatable_t.h"
#include "ithread_pool_t.h"
#include "iapplication_t.h"

#include <condition_variable>
#include <mutex>

namespace uasdk
{

class AsyncOperation_t : public Allocatable_t, public IRefCount_t
{
private:
  Status_t result;
  std::mutex mtx;
  std::condition_variable cv;

public:
  AsyncOperation_t();
  ~AsyncOperation_t();
 
  Status_t Initialise(const IntrusivePtr_t<IApplication_t>&);

  Status_t WaitForResult();

  virtual void OnComplete(Status_t result_);

private:
  AsyncOperation_t(AsyncOperation_t const &);
  AsyncOperation_t &operator=(AsyncOperation_t const &);
};

} /* namespace uasdk */

#endif  //(UASDK_INCLUDE_THREAD_POOL_CPP11 > 0)

#endif /* ASYNC_OPERATION_T_H_ */
