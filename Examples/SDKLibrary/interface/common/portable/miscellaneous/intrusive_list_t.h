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

#ifndef _INTRUSIVE_LIST_T_
#define _INTRUSIVE_LIST_T_

#include "uasdk_includes.h"
#include "intrusive_ptr_t.h"
#include "iref_count_t.h"
#include "allocatable_t.h"

namespace uasdk
{

/** \addtogroup grpMiscellaneous
 *@{*/

/*****************************************************************************/
/** \brief IntrusiveList_t
 *
 * Doubly Linked List implementation
 *
 */
template<class T>
class IntrusiveList_t : public IRefCount_t, public Allocatable_t
{
public:
  /*****************************************************************************/
  /** \brief Element_t
   * Doubly Linked List Node class
   */
  template<class A>
  class Element_t : public Allocatable_t
  {
  private:

    /*****************************************************************************/
    /** @var Element_t* previous
     * Pointer to the previous element
     */
    Element_t* previous;

    /*****************************************************************************/
    /** @var Element_t* next
     * Pointer to the next element
     */
    Element_t* next;

    /*****************************************************************************/
    /** @var IntrusivePtr_t<A> payload
     * Intrusive Pointer to the payload
     */
    IntrusivePtr_t<A> payload;

  public:
    /*****************************************************************************/
    /** Constructor of the class
     */
    template<typename B> Element_t(B& payload_) : previous(0), next(0), payload(payload_){}

    /*****************************************************************************/
    /** Destructor of the class
     */
    ~Element_t()
    {
    }

    /*****************************************************************************/
    /** Get the previous node
     *
     * @return
     * Pointer to the previous Node
     */
    Element_t* Previous() const { return previous; }

    /*****************************************************************************/
    /** Set the previous node pointer
     *
     * @param[in] Element_t* val
     * Pointer to be set as a previous node
     */
    void Previous(Element_t* val) { previous = val; }

    /*****************************************************************************/
    /** Get the next node
     *
     * @return
     * Pointer to the next Node
     */
    Element_t* Next(void) { return next; }

    /*****************************************************************************/
    /** Set the next node pointer
     *
     * @param[in] Element_t* val
     * Pointer to be set as a next node
     */
    void Next(Element_t* val) { next = val; }

    /*****************************************************************************/
    /** Get the payload
     *
     * @return
     * Returns the payload.
     */
    IntrusivePtr_t<A>& Payload(void) { return this->payload; }
  };

private:

  /*****************************************************************************/
  /** @var uint32_t MAX
   * Maximum allowed size of the queue
   */
  const uint32_t MAX;

  /*****************************************************************************/
  /** @var Element_t* first
   * Pointer to the first node
   */
  Element_t<T>* first;

  /*****************************************************************************/
  /** @var Element_t* first
   * Pointer to the last node
   */
  Element_t<T>* last;

  /*****************************************************************************/
  /** @var Element_t* current
   * Pointer to the current node
   */
  mutable Element_t<T>* current;

  /*****************************************************************************/
  /** @var uint32_t count
   *  Total number of elements in the list
   */
  uint32_t count;

  /*****************************************************************************/
  /** Get the next Element in the linked list
   *
   * @return
   * Returns the next Element in the linked list
   */
  Element_t<T>* GetNextElement(void)
  {
    if (current == last)
    {
      return 0;
    }
    else if (current == 0)
    {
      current = first;
    }
    else
    {
      current = current->Next();
    }
    return current;
  }

protected:

  /*****************************************************************************/
  /** Reference count
   *
   * @return
   * Returns the reference count
   */
  virtual int RefCount(void) const
  {
    /* Allow use of subclasses without bolting on reference counting
     * functionality
     */
    UASDK_ASSERT(false);
    return 0;
  }

public:

  /*****************************************************************************/
  /** Default Constructor of the class
   */
  IntrusiveList_t() : MAX(UINT32_MAX), first(0), last(0), current(0), count(0)
  { }

  /*****************************************************************************/
  /** parameterized Constructor of the class
   *
   * @param[in] uint32_t max
   * The Maximum elements allowed in the linked list
   */
  IntrusiveList_t(uint32_t max) : MAX(max), first(0), last(0), current(0), count(0)
  { }

  /*****************************************************************************/
  /** Destructor of the class
   */
  ~IntrusiveList_t()
  {
    DeleteAll();
  }

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
    if (count == MAX)
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfRange);
    }

    Element_t<T>* element = new Element_t<T>(item);
    if (element == 0)
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }

    if ((first == 0) || (last == 0))
    {
      current = first = last = element;
    }
    else
    {
      element->Next(first);
      current = first = element;
    }
    count++;
    return OpcUa_Good;
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
    if (count == MAX)
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfRange);
    }

    Element_t<T>* element = new Element_t<T>(item);
    if (element == 0)
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }

    if ((first == 0) || (last == 0))
    {
      current = first = last = element;
    }
    else
    {
      last->Next(element);
      element->Previous(last);
      current = last = element;
    }
    count++;
    return OpcUa_Good;
  }

  /*****************************************************************************/
  /** Delete the current node of the linked list
   *
   */
  void DeleteCurrent(void)
  {
    if (current != 0)
    {
      Element_t<T>* previous_element = current->Previous();
      Element_t<T>* next_element = current->Next();

      if (previous_element != 0)
      {
        previous_element->Next(next_element);
      }
      if (next_element != 0)
      {
        next_element->Previous(previous_element);
      }

      if (first == current)
      {
        first = next_element;
      }
      if (last == current)
      {
        last = previous_element;
      }
      delete current;
      current = previous_element;
      count--;
    }
  }

  /*****************************************************************************/
  /** Delete the head node of the linked list
   *
   */
  void DeleteAtHead(void)
  {
    current = first;
    DeleteCurrent();
  }

  /*****************************************************************************/
  /** Delete the tail node of the linked list
   *
   */
  void DeleteAtTail(void)
  {
    current = last;
    DeleteCurrent();
  }

  /*****************************************************************************/
  /** Reset the current node
   *
   */
  void ResetCurrent(void) const
  {
    current = 0;
  }

  /*****************************************************************************/
  /** Get the Data at the current Node
   *
   *  @return
   *  Returns the Data at the current Node.
   */
  IntrusivePtr_t<T> GetCurrent(void) const
  {
    if (current != 0)
    {
      return current->Payload();
    }
    else
    {
      return GetFirst();
    }
  }

  /*****************************************************************************/
  /** Get the Data at the first Node
   *
   *  @return
   *  Returns the Data at the first Node.
   */
  IntrusivePtr_t<T> GetFirst(void) const
  {
    if (first != 0)
    {
      current = first;
      return current->Payload();
    }
    else
    {
      IntrusivePtr_t<T> empty;
      return empty;
    }
  }

  /*****************************************************************************/
  /** Get the Data at the Last Node
   *
   *  @return
   *  Returns the Data at the Last Node.
   */
  IntrusivePtr_t<T> GetLast(void) const
  {
    if (last != 0)
    {
      current = last;
      return last->Payload();
    }
    else
    {
      IntrusivePtr_t<T> empty;
      return empty;
    }
  }

  /*****************************************************************************/
  /** Get the Data at the next Node
   *
   *  @return
   *  Returns the Data at the next Node.
   */
  IntrusivePtr_t<T> GetNext(void) const
  {
    if (current == last)
    {
      IntrusivePtr_t<T> empty;
      return empty;
    }
    else if (current == 0)
    {
      current = first;
    }
    else
    {
      current = current->Next();
    }

    if (current != 0)
    {
      return current->Payload();
    }
    IntrusivePtr_t<T> empty;
    return empty;
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
    ResetCurrent();
    IntrusivePtr_t<T> i;
    do
    {
      i = GetNext();
      if (i.get() == &item)
      {
        DeleteCurrent();
        break;
      }
    }while(i.is_set());

    return i;
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
    Element_t<T>* element = first;
    uint32_t no_blocks = Count();

    if (no_blocks <= index)
    {
      IntrusivePtr_t<T> empty;
      return empty;
    }

    for (uint32_t i = 0; i < index; i++)
    {
      element = element->Next();
    }

    current = element;
    if (current != 0)
    {
      return current->Payload();
    }
    IntrusivePtr_t<T> empty;
    return empty;
  }

  /*****************************************************************************/
  /** Get the number of elements from the queue
   *
   *  @return
   *  Returns the number of elements from the queue
   */
  uint32_t Count(void) const
  {
    return count;
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
    uint32_t count = source.Count();
    for (uint32_t i = 0; i < count; i++)
    {
      IntrusivePtr_t<T> element = source.GetFirst();
      if (!element.is_set())
      {
        UASDK_RETURN_BAD_STATUS(OpcUa_BadUnexpectedError);
      }
      if (remove)
      {
        source.DeleteAtHead();
      }
      Status_t status = AddToTail(element);
      if (status.IsBad())
      {
        return status;
      }
    }
    return OpcUa_Good;
  }

  /*****************************************************************************/
  /** Delete all the element from the Intrusive list
   *
   */
  void DeleteAll(void)
  {
    Element_t<T>* previous = 0;

    ResetCurrent();
    do
    {
      previous = current;
      current = GetNextElement();
      if (previous)
      {
        delete previous;
      }
    }while (current);
    count = 0;
    first = last = current = 0;
  }

  /*****************************************************************************/
  /** Add Reference for reference counting
   *
   */
  virtual void AddReference() const
  {
    /* Allow use without bolting on reference counting
     * functionality but catch it if it is used unintentionally
     */
    UASDK_ASSERT(false);
  }

  /*****************************************************************************/
  /** Remove Reference for reference counting
   *
   */
  virtual void RemoveReference() const
  {
    /* Allow use without bolting on reference counting
     * functionality but catch it if it is used unintentionally
     */
    UASDK_ASSERT(false);
  }

};

/** @} */

}

#endif // _INTRUSIVE_LIST_T_
