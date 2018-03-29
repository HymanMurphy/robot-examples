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

#ifndef _TIMER_PROVIDER_T_
#define _TIMER_PROVIDER_T_

#include "uasdk_includes.h"
#include "iref_count_t.h"

namespace uasdk
{

/** \addtogroup grpTimer
 *@{*/

class ICallbackTimerElapsed_t : public IRefCount_t
{
public:
  virtual ~ICallbackTimerElapsed_t() {};

  /*****************************************************************************/
  /** This function is gives the time elapsed information
   *
   *
   * @return
   * return the status of the operation.
   */
  virtual Status_t TimerElapsed(void) = 0;
};

class ITimer_t : public IRefCount_t
{
public:
  virtual ~ITimer_t() {};
};

class ITimerProvider_t : public IRefCount_t
{
public:
  virtual ~ITimerProvider_t() {};

  /*****************************************************************************/
  /** This function is used to create the one time timer
   *
   * @parm[in] delayInMs
   * delay in milliseconds after which timer will elapse
   *
   * @parm[in] elapsedCallback
   * elapsed call back. Which will be called after timer elapse
   *
   * @parm[out] timer
   * timer object
   *
   * @return
   * return the status of the operation.
   */
  virtual Status_t CreateOneShotTimer(uint32_t delayInMs,
                                      IntrusivePtr_t<ICallbackTimerElapsed_t>& elapsedCallback,
                                      IntrusivePtr_t<ITimer_t>& timer) = 0;

  /*****************************************************************************/
  /** This function is used to create the Periodic timer.
   *
   * @parm[in] delayInMs
   * Delay in milliseconds after which timer will restarts
   *
   * @parm[in] elapsedCallback
   * elapsed call back. Which will be called after timer elapse
   *
   * @parm[out] timer
   * timer object
   *
   * @return
   * return the status of the operation.
   */

  virtual Status_t CreatePeriodicTimer(uint32_t delayInMs,
                                       IntrusivePtr_t<ICallbackTimerElapsed_t>& elapsedCallback,
                                       IntrusivePtr_t<ITimer_t>& timer) = 0;

  /*****************************************************************************/
  /** This function is used to delete the timer.
   *
   * @param[in] timer
   * timer which is to be deleted
   *
   * @return
   * return the status of the operation.
   */
  virtual Status_t DeleteTimer(ITimer_t& timer) = 0;
  
  /*****************************************************************************/
  /** This function is used to change the period of the timer.
  *
  * @param[in] timer
  * timer which is to be deleted
  *
  * @param[in] delayInMs
  * delay in milliseconds which will be adjusted to the timer
  */
  virtual void ChangePeriod(ITimer_t& timer, uint32_t delayInMs) = 0;

  /*****************************************************************************/
  /** This function is used to restart the timer.
  *
  * @param[in] timer
  * timer which is to be deleted
  *
  */
  virtual void Restart(ITimer_t& timer) = 0;

  /*****************************************************************************/
  /** This function will be used to check the timer elapsed information
   *
   *
   * @return
   * return the status of the operation.
   */
  virtual Status_t Poll(void) = 0;

  /*****************************************************************************/
  /** This function will be used to shutdown the timer provider
  *
  * @return
  * return the status of the operation.
  */
  virtual Status_t Shutdown(void) = 0;

};

/** @} */

}

#endif // _TIMER_PROVIDER_T_
