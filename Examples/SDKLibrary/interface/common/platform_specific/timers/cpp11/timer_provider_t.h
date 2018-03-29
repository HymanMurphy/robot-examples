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

#ifndef _TIME_PROVIDER_T_
#define _TIME_PROVIDER_T_

#include "uasdk_includes.h"

#if (UASDK_INCLUDE_TIMERS_CPP11 > 0)

#include <thread>
#include "intrusive_ptr_t.h"
#include "allocatable_t.h"
#include "itimer_provider_t.h"
#include "intrusive_list_t.h"
#include "atomic_t.h"
#include "safe_ref_count_t.h"
#include "auto_lock_t.h"

namespace uasdk
{

/** \addtogroup grpTimer
 *@{*/

/*****************************************************************************/
/** \brief TimerProvider_t
 *
 * This class provides the timer interface to the SDK
 *
 */
class TimerProvider_t : public ITimerProvider_t, public Allocatable_t
{
private:
  class PlatformTimer_t : public ITimer_t, public Allocatable_t
  {
  private:
    uint32_t intervalInLoops;
    uint32_t loopsRemaining;
    uint32_t serverCyclicRateInMs;
    bool oneShot;
    bool markForDeletion;

    IntrusivePtr_t<ICallbackTimerElapsed_t> elapsedCallback;

  public:
    PlatformTimer_t() : intervalInLoops(0), loopsRemaining(0), serverCyclicRateInMs(0), oneShot(false), markForDeletion(false) {}

    uint32_t IntervalInLoops(void);

    bool OneShot(void);

    bool IsMarkedForDeletion(void);

    void MarkForDeletion(void);

    IntrusivePtr_t<ICallbackTimerElapsed_t>& ElapsedCallback(void);

    void Initialise(
      bool oneShot_,
      uint32_t intervalInMs,
      uint32_t serverCyclicRateInMs_,
      IntrusivePtr_t<ICallbackTimerElapsed_t>& elapsedCallback_);

    bool PollAndCheckExpired(void);

    virtual void ChangePeriod(uint32_t intervalInMs);

    virtual void Restart(void);

    void Delete(void);

  };

  Lock_t lock;
  IntrusiveList_t<PlatformTimer_t> timers;
  uint32_t serverCyclicRateInMs;
  Atomic_t<bool> quit;
  std::thread theThread;

  void Thread(void);

  void PollTimers(void);

public:

  Status_t Initialise(uint32_t serverCyclicRateInMs_);

  Status_t Poll(void);

  virtual Status_t CreateOneShotTimer(uint32_t delayInMs,
                          IntrusivePtr_t<ICallbackTimerElapsed_t>& elapsedCallback,
                          IntrusivePtr_t<ITimer_t>& timer);

  virtual Status_t CreatePeriodicTimer(uint32_t delayInMs,
                                       IntrusivePtr_t<ICallbackTimerElapsed_t>& elapsedCallback,
                                       IntrusivePtr_t<ITimer_t>& timer);

  virtual Status_t DeleteTimer(ITimer_t& timer);

  virtual void ChangePeriod(ITimer_t& timer, uint32_t delayInMs);

  virtual void Restart(ITimer_t& timer);

  virtual Status_t Shutdown(void);

};

/** @} */

}

#endif //UASDK_INCLUDE_TIMERS_CPP11

#endif // _TIME_PROVIDER_T_
