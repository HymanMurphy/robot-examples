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

#include "timer_provider_t.h"

#if (UASDK_INCLUDE_TIMERS_CPP11 > 0)

#include <chrono>

uint32_t uasdk::TimerProvider_t::PlatformTimer_t::IntervalInLoops(void)
{
  return intervalInLoops;
}

bool uasdk::TimerProvider_t::PlatformTimer_t::OneShot(void)
{
  return oneShot;
}

bool uasdk::TimerProvider_t::PlatformTimer_t::IsMarkedForDeletion(void)
{
  return markForDeletion;
}

void uasdk::TimerProvider_t::PlatformTimer_t::MarkForDeletion(void)
{
  markForDeletion = true;
}

uasdk::IntrusivePtr_t<uasdk::ICallbackTimerElapsed_t>& uasdk::TimerProvider_t::PlatformTimer_t::ElapsedCallback(void)
{
  return elapsedCallback;
}

void uasdk::TimerProvider_t::PlatformTimer_t::Initialise(bool oneShot_, uint32_t intervalInMs, uint32_t serverCyclicRateInMs_, IntrusivePtr_t<ICallbackTimerElapsed_t>& elapsedCallback_)
{
  oneShot = oneShot_;
  serverCyclicRateInMs = serverCyclicRateInMs_;
  elapsedCallback = elapsedCallback_;
  ChangePeriod(intervalInMs);
}

bool uasdk::TimerProvider_t::PlatformTimer_t::PollAndCheckExpired(void)
{
  UASDK_ASSERT(loopsRemaining > 0);
  loopsRemaining--;
  if (loopsRemaining == 0)
  {
    UASDK_ASSERT(elapsedCallback.is_set());
    elapsedCallback->TimerElapsed();
    if (oneShot)
    {
      MarkForDeletion();
    }
    else
    {
      Restart();
    }
    return true;
  }
  return false;
}

void uasdk::TimerProvider_t::PlatformTimer_t::ChangePeriod(uint32_t intervalInMs)
{
  if (intervalInMs < serverCyclicRateInMs)
  {
    intervalInMs = serverCyclicRateInMs;
  }

  uint32_t loopCount = intervalInMs / serverCyclicRateInMs;
  if (intervalInMs % serverCyclicRateInMs)
  {
    loopCount += 1;
  }

  intervalInLoops = loopCount;
  Restart();
}

void uasdk::TimerProvider_t::PlatformTimer_t::Restart(void)
{
  loopsRemaining = intervalInLoops;
}

void uasdk::TimerProvider_t::PlatformTimer_t::Delete(void)
{
  elapsedCallback.reset();
}

void uasdk::TimerProvider_t::Thread(void)
{
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    std::chrono::microseconds interval(serverCyclicRateInMs * 1000);
    std::chrono::microseconds delay = interval;
    std::chrono::steady_clock::time_point expectedEnd = start + interval;
    std::chrono::seconds maxOvershootToAllow(10);
  
    do
    {
      if (delay > interval)
      {
        //Should never happen so reset the delay to default
        delay = interval;
      }
  
      std::this_thread::sleep_for(delay);
      std::chrono::steady_clock::time_point actualEnd = ::std::chrono::steady_clock::now();
      if (actualEnd > expectedEnd)
      {
        std::chrono::microseconds overshoot = std::chrono::duration_cast<std::chrono::microseconds>(actualEnd - expectedEnd);

        //Protect ourselves from an erroneously large value being provided by the platform
        if (overshoot <= maxOvershootToAllow)
        {
          //delay = interval - (overshoot % interval);
          // VS2013 does not support this operation, so change it to
          std::chrono::microseconds remainder = overshoot;
          while (remainder >= interval)
          {
            remainder = (remainder - interval);
          }
          delay = interval - remainder;
        }
        else
        {
          delay = interval;
        }

        expectedEnd = actualEnd + delay;
        PollTimers();
      }
      else if (actualEnd < expectedEnd)
      {
        std::chrono::microseconds undershoot = std::chrono::duration_cast<std::chrono::microseconds>(expectedEnd - actualEnd);
        delay = undershoot;
      }
      else //(actualEnd == expectedEnd)
      {
        delay = interval;
        expectedEnd = actualEnd + delay;
        PollTimers();
      }
  
      if (quit.Value())
      {
        break;
      }
  
    } while (true);
}

void uasdk::TimerProvider_t::PollTimers(void)
{
  AutoLock_t lk(lock);

  IntrusivePtr_t<PlatformTimer_t> timer = timers.GetFirst();
  while (timer.is_set())
  {
    if (!timer->IsMarkedForDeletion())
    {
      timer->PollAndCheckExpired();
    }

    if (timer->IsMarkedForDeletion())
    {
      timer->Delete();
      timers.DeleteCurrent();
      //LOG_INFO("Deleting timer. %d timers active", timers.Count());
    }

    timer = timers.GetNext();
  }
}

uasdk::Status_t uasdk::TimerProvider_t::Initialise(uint32_t serverCyclicRateInMs_)
{
  quit.Value(false);
  serverCyclicRateInMs = serverCyclicRateInMs_;
  Status_t status = lock.Initialise();
  if (status.IsBad())
  {
    return status;
  }
  theThread = std::thread(&TimerProvider_t::Thread, this);
  return OpcUa_Good;
}

uasdk::Status_t uasdk::TimerProvider_t::Poll(void)
{
  return OpcUa_Good;
}

uasdk::Status_t uasdk::TimerProvider_t::CreateOneShotTimer(uint32_t delayInMs, IntrusivePtr_t<ICallbackTimerElapsed_t>& elapsedCallback, IntrusivePtr_t<ITimer_t>& timer)
{
  AutoLock_t lk(lock);

  IntrusivePtr_t<PlatformTimer_t> tmr = new SafeRefCount_t<PlatformTimer_t>();
  if (!tmr.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  tmr->Initialise(true, delayInMs, serverCyclicRateInMs, elapsedCallback);

  Status_t status = timers.AddToTail(*tmr);
  if (status.IsBad())
  {
    return status;
  }

  //LOG_INFO("Adding one-shot timer. %d timers active", timers.Count());

  timer = tmr;
  return OpcUa_Good;
}

uasdk::Status_t uasdk::TimerProvider_t::CreatePeriodicTimer(uint32_t delayInMs, IntrusivePtr_t<ICallbackTimerElapsed_t>& elapsedCallback, IntrusivePtr_t<ITimer_t>& timer)
{
  AutoLock_t lk(lock);

  IntrusivePtr_t<PlatformTimer_t> tmr = new SafeRefCount_t<PlatformTimer_t>();
  if (!tmr.is_set())
  {
    UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
  }

  tmr->Initialise(false, delayInMs, serverCyclicRateInMs, elapsedCallback);

  Status_t status = timers.AddToTail(*tmr);
  if (status.IsBad())
  {
    return status;
  }
  //LOG_INFO("Adding periodic timer. %d timers active", timers.Count());

  timer = tmr;
  return OpcUa_Good;
}

uasdk::Status_t uasdk::TimerProvider_t::DeleteTimer(ITimer_t& timer)
{
  AutoLock_t lk(lock);
  PlatformTimer_t& concreteTimer = static_cast<PlatformTimer_t&>(timer);
  concreteTimer.MarkForDeletion();
  return OpcUa_Good;
}

void uasdk::TimerProvider_t::ChangePeriod(ITimer_t& timer, uint32_t delayInMs)
{
  AutoLock_t lk(lock);
  PlatformTimer_t& concreteTimer = static_cast<PlatformTimer_t&>(timer);
  concreteTimer.ChangePeriod(delayInMs);
}

void uasdk::TimerProvider_t::Restart(ITimer_t& timer)
{
  AutoLock_t lk(lock);
  PlatformTimer_t& concreteTimer = static_cast<PlatformTimer_t&>(timer);
  concreteTimer.Restart();
}

uasdk::Status_t uasdk::TimerProvider_t::Shutdown(void)
{
  {
    AutoLock_t lk(lock);
    timers.ResetCurrent();
    IntrusivePtr_t<PlatformTimer_t> tmr;

    do
    {
      tmr = timers.GetNext();
      if (tmr.is_set())
      {
        tmr->Delete();
        timers.DeleteCurrent();
      }
    } while (tmr.is_set());
  }

  quit.Value(true);
  if (theThread.joinable())
  {
    theThread.join();
  }

  return OpcUa_Good;
}

#endif //UASDK_INCLUDE_TIMERS_CPP11
