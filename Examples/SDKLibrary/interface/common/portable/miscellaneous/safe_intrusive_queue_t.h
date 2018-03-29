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

#ifndef _SAFE_INTRUSIVE_QUEUE_T_
#define _SAFE_INTRUSIVE_QUEUE_T_

#include "intrusive_list_t.h"
#include "auto_lock_t.h"

namespace uasdk
{

/** \addtogroup grpMiscellaneous
 *@{*/

/*****************************************************************************/
/** \brief SafeIntrusiveQueue_t
 *
 * This class implements the Safe Intrusive Queue
 *
 */
template<class T>
class SafeIntrusiveQueue_t : public IRefCount_t, public Allocatable_t
{
private:


  /*****************************************************************************/
  /** @var IntrusiveList_t<T> first
   * Intrusive List
   */
  IntrusiveList_t<T> list;

  /*****************************************************************************/
  /** Lock_t lock
   * Lock for the safe data access
   */
  mutable Lock_t lock;

public:

  /*****************************************************************************/
  /** Initialize the class
   *
   * @return
   * Status of the operation
   */
  Status_t Initialise(void)
  {
    return lock.Initialise();
  }

  /*****************************************************************************/
  /** Push the element to the queue
   *
   * @param[in] A& item
   * Element to be pushed inside the queue
   *
   * @return
   * Status of the operation
   *
   */
  template<typename A> Status_t Push(A& item)
  {
    AutoLock_t lk(lock);
    return list.AddToTail(item);
  }

  /*****************************************************************************/
  /** Push the element to the back of the queue
   *
   * @param[in] A& item
   * Element to be pushed inside the queue
   *
   * @return
   * Status of the operation
   *
   */
  template<typename A> Status_t PushBack(A& item)
  {
    AutoLock_t lk(lock);
    return list.AddToHead(item);
  }

  /*****************************************************************************/
  /** Pop the element to the queue
   *
   * @return
   * Element popped from the queue.
   *
   */
  IntrusivePtr_t<T> Pop(void)
  {
    AutoLock_t lk(lock);
    IntrusivePtr_t<T> first = list.GetFirst();
    list.DeleteAtHead();
    return first;
  }

  /*****************************************************************************/
  /** Delete all the elements from the queue
   */
  void DeleteAll(void)
  {
    AutoLock_t lk(lock);
    list.DeleteAll();
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
    return list.Count();
  }

};

/** @} */

}

#endif // _SAFE_INTRUSIVE_QUEUE_T_
