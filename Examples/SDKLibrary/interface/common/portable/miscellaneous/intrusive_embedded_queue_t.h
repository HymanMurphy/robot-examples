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

#ifndef _INTRUSIVE_EMBEDDED_QUEUE_T_
#define _INTRUSIVE_EMBEDDED_QUEUE_T_

#include "scoped_ptr_t.h"

namespace uasdk
{
/** \addtogroup grpMiscellaneous
 *@{*/

/*****************************************************************************/
/** \brief IntrusiveEmbeddedQueue_t
 *
 * This class implements the intrusive embedded queue
 *
 */
template<class T>
class IntrusiveEmbeddedQueue_t
{
private:

  /*****************************************************************************/
  /** @var IntrusivePtr_t<T> first
   * Intrusive Pointer to the first element of the queue
   */
  IntrusivePtr_t<T> first;

  /*****************************************************************************/
  /** T* last
   * Pointer to the last element of the queue
   */
  T* last;

  /*****************************************************************************/
  /** uint32_t count
   *  Number of elements in the queue
   */
  uint32_t count;

public:

  /*****************************************************************************/
  /** Constructor of the class
   */
  IntrusiveEmbeddedQueue_t() : first(0), last(0), count(0)
  { }

  /*****************************************************************************/
  /** Destructor of the class
   */
  ~IntrusiveEmbeddedQueue_t()
  {
  }

  /*****************************************************************************/
  /** Push the element to the queue
   *
   * @param[in] IntrusivePtr_t<T>& item
   * Element to be pushed inside the queue
   */
  void Push(IntrusivePtr_t<T>& item)
  {
    if (item.is_set())
    {
      item->Next().reset();

      if (!first.is_set())
      {
        first = item;
        last = first.get();
        count = 1;
      }
      else if (last)
      {
        last->Next(item);
        last = last->Next().get();
        count++;
      }
    }
  }

  /*****************************************************************************/
  /** Pop the element to the queue
   *
   * @param[out] IntrusivePtr_t<T>& item
   * Element to be popped from the queue
   */
  void Pop(IntrusivePtr_t<T>& item)
  {
    if (first.is_set())
    {
      item = first;
      first = first->Next();
      item->Next().reset();
      if (--count == 0)
      {
        last = 0;
      }
    }
    else
    {
      item.reset();
    }
  }

  /*****************************************************************************/
  /** Get the number of elements in the queue
   *
   * @return
   * Return the number of elements in the queue
   */
  uint32_t Count(void) const
  {
    return count;
  }

};

/** @} */

}
#endif // _INTRUSIVE_EMBEDDED_QUEUE_T_
