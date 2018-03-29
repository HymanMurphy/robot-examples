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

#ifndef _LINKED_LIST_T_
#define _LINKED_LIST_T_

#include "allocatable_t.h"

namespace uasdk
{

  /** \addtogroup grpMiscellaneous
   *@{*/

   /*****************************************************************************/
   /** \brief LinkedList_t
    *
    * Doubly Linked List implementation
    *
    */
  template<class T>
  class LinkedList_t
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
      A payload;

    public:

      /*****************************************************************************/
      /** Constructor of the class
       */
      template<typename B> Element_t(B& payload_) : previous(0), next(0), payload(payload_) {}

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
      A& Payload(void) { return this->payload; }
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
    Element_t<T>* GetNextElement(void) UASDK_NO_THROW
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

  public:

    /*****************************************************************************/
    /** Default Constructor of the class
     */
    LinkedList_t() : MAX(UINT32_MAX), first(0), last(0), current(0), count(0)
    { }


    /*****************************************************************************/
    /** parameterized Constructor of the class
     *
     * @param[in] uint32_t max
     * The Maximum elements allowed in the linked list
     */
    LinkedList_t(uint32_t max) : MAX(max), first(0), last(0), current(0), count(0)
    { }


    /*****************************************************************************/
    /** Destructor of the class
     */
    ~LinkedList_t()
    {
      DeleteAll();
    }


    /*****************************************************************************/
    /** Add the element to the tail of the linked list
     *
     * @param[in] A& item
     * The element to be added to the linked list
     *
     * @return
     * True - element added to the tail
     * False - Failed to add the element
     */
    template<typename A> bool AddToTail(A& item)
    {
      if (count == MAX)
      {
        return false;
      }

      Element_t<T>* element = new Element_t<T>(item);
      if (element == 0)
      {
        return false;
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
      return true;
    }

    /*****************************************************************************/
    /** Delete the current node of the linked list
     *
     */
    void DeleteCurrent(void) UASDK_NO_THROW
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
    void ResetCurrent(void) const UASDK_NO_THROW
    {
      current = 0;
    }

    /*****************************************************************************/
    /** Get the Data at the current Node
     *
     *  @return
     *  Returns the Data at the current Node.
     */
    T* GetCurrent(void) const
    {
      if (current != 0)
      {
        return &current->Payload();
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
    T* GetFirst(void) const
    {
      if (first != 0)
      {
        current = first;
        return &current->Payload();
      }
      else
      {
        return 0;
      }
    }

    /*****************************************************************************/
    /** Get the Data at the Last Node
     *
     *  @return
     *  Returns the Data at the Last Node.
     */
    T* GetLast(void) const
    {
      current = last;
      if (current != 0)
      {
        return &current->Payload();
      }
      else
      {
        return 0;
      }
    }

    /*****************************************************************************/
    /** Get the Data at the next Node
     *
     *  @return
     *  Returns the Data at the next Node.
     */
    T* GetNext(void) const
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

      if (current != 0)
      {
        return &current->Payload();
      }
      return 0;
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
    T* GetAtIndex(uint32_t index) const
    {
      Element_t<T>* element = first;
      uint32_t no_blocks = Count();

      if (no_blocks <= index)
      {
        return 0;
      }

      for (uint32_t i = 0; i < index; i++)
      {
        element = element->Next();
      }

      current = element;
      if (current != 0)
      {
        return &current->Payload();
      }
      return 0;
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
    /** Delete all the element from the Intrusive list
     *
     */
    void DeleteAll(void) UASDK_NO_THROW
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
      } while (current);
      count = 0;
      first = last = current = 0;
    }

    /*****************************************************************************/
    /** Delete the specific elements from the linked list
     *
     * @param[in] const T& data
     * Data to be deleted
     */
    const T* DeleteSpecific(const T& data)
    {
      const T* element = GetFirst();

      while (element != 0)
      {
        if (*element == data)
        {
          DeleteCurrent();
          return element;
        }
        element = GetNext();
      }

      return 0;
    }

    /*****************************************************************************/
    /** Find the specific elements from the linked list
     *
     * @param[in] const T& data
     * Data to find
     */
    const T* Find(const T& data) const
    {
      const T* element = GetFirst();

      while (element != 0)
      {
        if (*element == data)
        {
          return element;
        }
        element = GetNext();
      }

      return 0;
    }

  };

}
/** @} */

#endif // _LINKED_LIST_T_
