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

#ifndef _TIME_PROVIDER_T_
#define _TIME_PROVIDER_T_

#include "uasdk_includes.h"

#if (UASDK_INCLUDE_TIMERS_ANY_PLATFORM_POLLED > 0)

#include "intrusive_ptr_t.h"
#include "allocatable_t.h"
#include "itimer_provider_t.h"
#include "intrusive_list_t.h"

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
    uint32_t start_time_ms;
    uint32_t stop_time_ms;
    uint32_t interval_ms;
    bool started;
    bool one_shot;

    IntrusivePtr_t<ICallbackTimerElapsed_t> elapsedCallback;

  public:
    PlatformTimer_t() : start_time_ms(0), stop_time_ms(0), interval_ms(0), started(false), one_shot(false) {}
    virtual ~PlatformTimer_t(void)
    {
      Stop();
    }

    /*****************************************************************************/
    /** Function used to get the timer start time
     *
     * @return
     * returns start time in millisecond.
     */
    uint32_t StartTime(void) { return start_time_ms; }

    /*****************************************************************************/
    /** Function used to get the timer stop time
     *
     * @return
     * returns stop time in millisecond.
     */
    uint32_t StopTime(void) { return stop_time_ms; }

    /*****************************************************************************/
    /** Function gets the time interval
     *
     * @return
     * returns interval time in millisecond.
     */
    uint32_t Interval(void) { return interval_ms; }

    /*****************************************************************************/
    /** Function gets the timer one_shot status
     *
     * @return
     * returns boolean status.
     */
    bool OneShot(void) { return one_shot; }

    /*****************************************************************************/
    /** Function gets the instance of the time elapsed callback
     *
     * @return
     * returns the class instance
     */
    IntrusivePtr_t<ICallbackTimerElapsed_t>& ElapsedCallback(void) { return elapsedCallback; }

    /*****************************************************************************/
    /** Function used to check the whether timer started or not.
     *
     * @return
     * returns the boolean status.
     */
    bool Started(void) { return started; }

    /*****************************************************************************/
    /** Function used to configure or initialize the time interval and time elapsed call.
     *
     * @param[in] interval_ms_
     * interval time
     *
     * @param[in] elapsedCallback_
     * time elapsed from the call back
     */
    void Configure(uint32_t interval_ms_,
                   IntrusivePtr_t<ICallbackTimerElapsed_t>& elapsedCallback_)
    {
      interval_ms = interval_ms_;
      elapsedCallback = elapsedCallback_;
    }

    /*****************************************************************************/
    /** Function used to start the time in one_shot and set the status to true.
     *
     */
    void StartOneShot(void)
    {
      if (interval_ms > 0)
      {
        start_time_ms = UASDK_millisecond();
        stop_time_ms = start_time_ms + interval_ms;
        one_shot = true;
        started = true;
      }
    }

    /*****************************************************************************/
    /** Function starts the timer repeatedly and sets the status of one shot timer to false.
     *
     */
    void StartRepeating(void)
    {
      if (interval_ms > 0)
      {
        start_time_ms = UASDK_millisecond();
        stop_time_ms = start_time_ms + interval_ms;
        one_shot = false;
        started = true;
      }
    }

    /*****************************************************************************/
    /** Function timer started status to false.
     *
     */
    void Stop(void)
    {
      started = false;
    }

   /*****************************************************************************/
   /** This function sets the timer expiry status after checking the start time,
    * current time and stop time values.
    *
    * @return
    * returns boolean status.
    */
    bool Expired(void)
    {
      bool expired = false;

      uint32_t current_time_ms = UASDK_millisecond();

      if ((stop_time_ms > start_time_ms) && ((current_time_ms >= stop_time_ms) || (current_time_ms < start_time_ms)))
      {
        expired = true;
      }
      else if ((stop_time_ms < start_time_ms) && ((current_time_ms >= stop_time_ms) && (current_time_ms < start_time_ms)))
      {
        expired = true;
      }

      if (expired)
      {
        if (one_shot)
        {
          /* Stop timer */
          started = false;
        }
        else
        {
          /* Increment stop time */
          uint32_t no_of_cycles = 0;

          if (stop_time_ms <= current_time_ms)
          {
            uint32_t delta = current_time_ms - stop_time_ms;
            no_of_cycles = delta / interval_ms;
          }
          else
          {
            uint32_t delta = (UINT32_MAX - stop_time_ms) + current_time_ms;
            no_of_cycles = delta / interval_ms;
          }

          stop_time_ms += interval_ms * (no_of_cycles + 1);
        }
      }
      return expired;
    }

    /*****************************************************************************/
    /** Function changes the timer period based on the status of one_shot timer.
     *
     * @param[in]delayInMs
     * delay in millisecond.
     */
    virtual void ChangePeriod(uint32_t delayInMs)
    {
      Stop();
      interval_ms = delayInMs;
      if (one_shot)
      {
        StartOneShot();
      }
      else
      {
        StartRepeating();
      }
    }

   /*****************************************************************************/
   /** Function used to resets the start time and stop time.
    *
    * @param[in]delayInMs
    * delay in millisecond.
    */
    virtual void Restart(void)
    {
      if (started)
      {
        start_time_ms = UASDK_millisecond();
        stop_time_ms = start_time_ms + interval_ms;
      }
    }

    void Delete(void)
    {
      elapsedCallback.reset();
    }

  };

  Lock_t lock;
  IntrusiveList_t<PlatformTimer_t> timers;

public:

  virtual ~TimerProvider_t()
  {
    Shutdown();
  }

  /*****************************************************************************/
  /** Function initializes the timer module
   *
   * @return
   * returns the status of the operation.
   */
  Status_t Initialise(void)
  {
    return lock.Initialise();
  }

  /*****************************************************************************/
  /** This function used to check timer expiry and
   *  set the time elapsed from the callback.
   *
   *
   * @return
   * return the status of the operation.
   */
  Status_t Poll(void)
  {
    AutoLock_t lk(lock);

    timers.ResetCurrent();
    uint32_t count = timers.Count();
    for (uint32_t i = 0; i < count; i++)
    {
      IntrusivePtr_t<PlatformTimer_t> timer = timers.GetNext();
      if (!timer.is_set())
      {
        UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
      }
      if (timer->Expired())
      {
        IntrusivePtr_t<ICallbackTimerElapsed_t> elapsedCallback = timer->ElapsedCallback();
        if (!elapsedCallback.is_set())
        {
          UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
        }
        elapsedCallback->TimerElapsed();
        if (timer->OneShot())
        {
          timers.RemoveSpecific(*timer);
        }
      }
    }
    return OpcUa_Good;
  }

  /*****************************************************************************/
   /** This function creates and starts one_shot timer.
    *
    * @param[in]delayInMs
    * delay in milli second
    *
    * @param[in]elapsedCallback
    * call back timer elapsed object
    *
    * @param[out]timer
    * timer object
    *
    * @return
    * return the status of the operation.
    */
  virtual Status_t CreateOneShotTimer(uint32_t delayInMs,
                          IntrusivePtr_t<ICallbackTimerElapsed_t>& elapsedCallback,
                          IntrusivePtr_t<ITimer_t>& timer)
  {
    AutoLock_t lk(lock);

    IntrusivePtr_t<PlatformTimer_t> tmr = new SafeRefCount_t<PlatformTimer_t>();
    if (!tmr.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }

    tmr->Configure(delayInMs, elapsedCallback);

    Status_t status = timers.AddToTail(*tmr);
    if (status.IsBad())
    {
      return status;
    }

    tmr->StartOneShot();
    timer = tmr;
    return OpcUa_Good;
  }

  /*****************************************************************************/
  /** This function creates and starts timer periodically by calling StartRepeating().
   *
   * @param[in]delayInMs
   * delay in milli second
   *
   * @param[in]elapsedCallback
   * call back timer elapsed object
   *
   * @param[out]timer
   * timer object
   *
   * @return
   * return the status of the operation.
   */
  virtual Status_t CreatePeriodicTimer(uint32_t delayInMs,
                                       IntrusivePtr_t<ICallbackTimerElapsed_t>& elapsedCallback,
                                       IntrusivePtr_t<ITimer_t>& timer)
  {
    AutoLock_t lk(lock);

    IntrusivePtr_t<PlatformTimer_t> tmr = new SafeRefCount_t<PlatformTimer_t>();
    if (!tmr.is_set())
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }

    tmr->Configure(delayInMs, elapsedCallback);

    Status_t status = timers.AddToTail(*tmr);
    if (status.IsBad())
    {
      return status;
    }

    tmr->StartRepeating();
    timer = tmr;
    return OpcUa_Good;
  }

  /*****************************************************************************/
  /** This function removes or deletes the specific timer from the list.
   *
   * @param[in/out] timer
   * timer which is needs to be delete.
   *
   * @return
   * return the status of the operation.
   */
  virtual Status_t DeleteTimer(ITimer_t& timer)
  {
    AutoLock_t lk(lock);

    timers.ResetCurrent();
    uint32_t count = timers.Count();
    for (uint32_t i = 0; i < count; i++)
    {
      IntrusivePtr_t<PlatformTimer_t> tmr = timers.GetNext();
      if (!tmr.is_set())
      {
        UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
      }
      ITimer_t& base = *tmr;
      if (&timer == &base)
      {
        tmr->Delete();
        timers.RemoveSpecific(*tmr);
        return OpcUa_Good;
      }
    }
    //May have already been deleted if one-shot
    return OpcUa_Good;
  }

  /*****************************************************************************/
  /** This function is used to change the period of the timer.
  *
  * @param[in] timer
  * timer which is to be deleted
  *
  * @param[in] delayInMs
  * delay in milliseconds which will be adjusted to the timer
  */
  virtual void ChangePeriod(ITimer_t& timer, uint32_t delayInMs)
  {
    PlatformTimer_t& concreteTimer = static_cast<PlatformTimer_t&>(timer);
    concreteTimer.ChangePeriod(delayInMs);
  }

  /*****************************************************************************/
  /** This function is used to restart the timer.
  *
  * @param[in] timer
  * timer which is to be deleted
  *
  */
  virtual void Restart(ITimer_t& timer)
  {
    PlatformTimer_t& concreteTimer = static_cast<PlatformTimer_t&>(timer);
    concreteTimer.Restart();
  }

  /*****************************************************************************/
  /** This function will be used to shutdown the timer provider
  *
  * @return
  * return the status of the operation.
  */
  virtual Status_t Shutdown(void)
  {
    AutoLock_t lk(lock);
    timers.DeleteAll();
    return OpcUa_Good;
  }

};

/*@}*/

}

#endif //UASDK_INCLUDE_TIMERS_ANY_PLATFORM_POLLED

#endif // _TIME_PROVIDER_T_
