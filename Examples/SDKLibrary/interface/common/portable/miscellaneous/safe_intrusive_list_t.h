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

#ifndef _SAFE_INTRUSIVE_LIST_T_
#define _SAFE_INTRUSIVE_LIST_T_

#include "intrusive_list_t.h"
#include "auto_lock_t.h"

namespace uasdk
{

/** \addtogroup grpMiscellaneous
 *@{*/

/*****************************************************************************/
/** \brief SafeIntrusiveList_t
 *
 * Safe Doubly Linked List implementation
 *
 */
template<class T>
class SafeIntrusiveList_t : public IRefCount_t, public Allocatable_t
{
private:
  IntrusiveList_t<T> list;
  mutable Lock_t lock;

public:
  Status_t Initialise(void)
  {
    return lock.Initialise();
  }

public:

  /*****************************************************************************/
  /** Default Constructor of the class
   */
  SafeIntrusiveList_t() 
  { }

  /*****************************************************************************/
  /** Add the element as a head of the linked list
   *
   * @param[in] A& item
   * The element to be added to the linked list
   *
   * @return
   * Status of the operation
   */
  template<typename A> Status_t AddToHead(A& item)
  {
    AutoLock_t lk(lock);
    return list.AddToHead(item);
  }

  /*****************************************************************************/
  /** Add the element to the tail of the linked list
   *
   * @param[in] A& item
   * The element to be added to the linked list
   *
   * @return
   * Status of the operation
   */
  template<typename A> Status_t AddToTail(A& item)
  {
    AutoLock_t lk(lock);
    return list.AddToTail(item);
  }

  /*****************************************************************************/
  /** Delete the current node of the linked list
   *
   */
  void DeleteCurrent(void)
  {
    AutoLock_t lk(lock);
    list.DeleteCurrent();
  }

  /*****************************************************************************/
  /** Delete the head node of the linked list
   *
   */
  void DeleteAtHead(void)
  {
    AutoLock_t lk(lock);
    return list.DeleteAtHead();
  }

  /*****************************************************************************/
  /** Delete the tail node of the linked list
   *
   */
  void DeleteAtTail(void)
  {
    AutoLock_t lk(lock);
    return list.DeleteAtTail();
  }

  /*****************************************************************************/
  /** Reset the current node
   *
   */
  void ResetCurrent(void) const
  {
    AutoLock_t lk(lock);
    return list.ResetCurrent();
  }

  /*****************************************************************************/
  /** Get the Data at the current Node
   *
   *  @return
   *  Returns the Data at the current Node.
   */
  IntrusivePtr_t<T> GetCurrent(void) const
  {
    AutoLock_t lk(lock);
    return list.GetCurrent();
  }

  /*****************************************************************************/
  /** Get the Data at the first Node
   *
   *  @return
   *  Returns the Data at the first Node.
   */
  IntrusivePtr_t<T> GetFirst(void) const
  {
    AutoLock_t lk(lock);
    return list.GetFirst();
  }

  /*****************************************************************************/
  /** Get the Data at the Last Node
   *
   *  @return
   *  Returns the Data at the Last Node.
   */
  IntrusivePtr_t<T> GetLast(void) const
  {
    AutoLock_t lk(lock);
    return list.GetLast();
  }

  /*****************************************************************************/
  /** Get the Data at the next Node
   *
   *  @return
   *  Returns the Data at the next Node.
   */
  IntrusivePtr_t<T> GetNext(void) const
  {
    AutoLock_t lk(lock);
    return list.GetNext();
  }

  /*****************************************************************************/
  /** Remove the specific data from list
   *
   *  @param[in] T& item
   *  item to be deleted from the list
   *
   *  @return
   *  Returns the Data at the deleted Node.
   */
  IntrusivePtr_t<T> RemoveSpecific(T& item)
  {
    AutoLock_t lk(lock);
    return list.RemoveSpecific(item);
  }

  /*****************************************************************************/
  /** Get the data at a specific index
   *
   *  @param[in] uint32_t i
   *  index
   *
   *  @return
   *  Returns the Data at index i
   */
  IntrusivePtr_t<T> GetAtIndex(uint32_t index) const
  {
    AutoLock_t lk(lock);
    return list.GetAtIndex(index);
  }

  /*****************************************************************************/
  /** Get the number of elements from the queue
   *
   *  @return
   *  Returns the number of elements from the queue
   */
  uint32_t Count(void) const
  {
    AutoLock_t lk(lock);
    return list.Count();
  }

  /*****************************************************************************/
  /** Add the element from the Intrusive list
   *
   *  @param[in] IntrusiveList_t<T>& source
   *  List to be added
   *
   *  @param[in] bool remove
   *  Remove the head node of the list if true
   *
   *  @return
   *  Result of the operation
   */
  Status_t AddFrom(IntrusiveList_t<T>& source, bool remove = false)
  {
    AutoLock_t lk(lock);
    return list.AddFrom(source, remove);
  }

  /*****************************************************************************/
  /** Delete all the element from the Intrusive list
   *
   */
  void DeleteAll(void)
  {
    AutoLock_t lk(lock);
    return list.DeleteAll();
  }

};

/*@}*/

}

#endif // _SAFE_INTRUSIVE_LIST_T_
