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

#ifndef _SAFE_INTRUSIVE_EMBEDDED_QUEUE_T_
#define _SAFE_INTRUSIVE_EMBEDDED_QUEUE_T_

#include "intrusive_embedded_queue_t.h"
#include "uasdk_includes.h"
#include "auto_lock_t.h"
#include "iref_count_t.h"
#include  "allocatable_t.h"


namespace uasdk
{

template<class T>
class SafeIntrusiveEmbeddedQueue_t : public IRefCount_t, public Allocatable_t
{
private:

  /*****************************************************************************/
  /** @var IntrusiveEmbeddedQueue_t<T> queue
   * Intrusive Embedded Queue
   */
  IntrusiveEmbeddedQueue_t<T> queue;

  /*****************************************************************************/
  /** Lock_t lock
   * Lock for the safe data access
   */
  Lock_t lock;

public:

  /*****************************************************************************/
  /** Initialize the class
   *
   * @return
   * Status of the operation
   */
  Status_t Initialise(void)
  {
    Status_t status;
    status = lock.Initialise();
    return status;
  }

  /*****************************************************************************/
  /** Push the element to the queue
   *
   * @param[in] IntrusivePtr_t<T>& item
   * Element to be pushed inside the queue
   *
   */
  void Push(IntrusivePtr_t<T>& item)
  {
    AutoLock_t lk(lock);
    queue.Push(item);
  }

  /*****************************************************************************/
  /** Push the element to the queue
   *
   * @param[in] IntrusivePtr_t<T>& item
   * Element to be pushed inside the queue
   *
   * @param[out] uint32_t& count_
   * Number of elements in the queue
   */
  void Push(IntrusivePtr_t<T>& item, uint32_t& count_)
  {
    AutoLock_t lk(lock);
    queue.Push(item);
    count_ = queue.Count();
  }

  /*****************************************************************************/
  /** Pop the element to the queue
   *
   * @param[out] IntrusivePtr_t<T>& item
   * Element to be popped from the queue
   *
   */
  void Pop(IntrusivePtr_t<T>& item)
  {
    AutoLock_t lk(lock);
    queue.Pop(item);
  }

  /*****************************************************************************/
  /** Pop the element to the queue
   *
   * @param[out] IntrusivePtr_t<T>& item
   * Element to be popped from the queue
   *
   * @param[out] uint32_t& count_
   * Number of elements in the queue
   *
   */
  void Pop(IntrusivePtr_t<T>& item, uint32_t& count_)
  {
    AutoLock_t lk(lock);
    queue.Pop(item);
    count_ = queue.Count();
  }

  /*****************************************************************************/
  /** Get the number of elements in the queue
   *
   * @return
   * Return the number of elements in the queue
   */
  uint32_t Count(void)
  {
    AutoLock_t lk(lock);
    return queue.Count();
  }

};

/** @} */

}

#endif // _SAFE_INTRUSIVE_EMBEDDED_QUEUE_T_
