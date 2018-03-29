/* -----------------------------------------------------------------------------------------------------------------
 * COPYRIGHT (c) 2009 - 2017
 * HONEYWELL INC.,
 * ALL RIGHTS RESERVED
 *
 * This software is a copyrighted work and/or information protected as a trade
 * secret. Legal rights of Honeywell Inc. in this software are distinct from
 * ownership of any medium in which the software is embodied. Copyright or trade
 * secret notices included must be reproduced in any copies authorized by
 * Honeywell Inc. The information in this software is subject to change without
 * notice and should not be considered as a commitment by Honeywell Inc.
 *----------------------------------------------------------------------------------------------------------------- */

#ifndef _HASH_SET_T_
#define _HASH_SET_T_

#include "uasdk_includes.h"
#include "array_t.h"
#include "intrusive_list_t.h"
#include "linked_list_t.h"
#include "intrusive_ptr_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

namespace uasdk
{

  template<class T>
  class Hash_Set_t
  {
  private:
    Array_t<LinkedList_t<T> > buckets;
    int32_t count;
    int32_t currentBucket;
    T* currentItem;

  public:
    Hash_Set_t() :count(0), currentBucket(-1), currentItem(NULL) {}

    ~Hash_Set_t() {}

    const int32_t& Count() const
    {
      return count;
    }
   
    T* GetFirst()
    {
      currentBucket = 0;
      currentItem = NULL;
      while (currentBucket < buckets.Count() && NULL == currentItem)
      {
        currentItem = buckets[currentBucket].GetFirst();
        if (NULL == currentItem)
        {
          ++currentBucket;
        }
      }

      return currentItem;
    }

    T* GetNext()
    {

      if (currentBucket < 0 || currentBucket >= buckets.Count())
      {
        currentItem = NULL;
        return NULL;
      }

      do
      {
        currentItem = buckets[currentBucket].GetNext();
        if (NULL == currentItem)
        {
          while (NULL == currentItem && ++currentBucket < buckets.Count())
          {
            currentItem = buckets[currentBucket].GetFirst();
          }
        }
      } while (NULL == currentItem && currentBucket < buckets.Count());

      return currentItem;
    }

    Status_t Initialise(uint32_t noOfBuckets)
    {
      count = 0;
      currentBucket = -1;
      currentItem = NULL;
      return buckets.Initialise(noOfBuckets);
    }

    Status_t Add(const T item)
    {
      if (true == Contains(item))
      {
        return OpcUa_BadNothingToDo;
      }


       uint32_t index = (uint32_t)item % buckets.Size();

            //Force uniqueness
      Status_t result = buckets[index].AddToTail(item);
      if (result.IsGood())
      {
        ++count;
      }
      return result;
    }

    Status_t Add(Hash_Set_t<T> &set)
    {
      T* item = set.GetFirst();
      while (item != NULL)
      {
        Status_t status = Add(*item);
        if (status.IsOutOfMemory())
        {
          return status;
        }

        item = set.GetNext();
      }

      return OpcUa_Good;
    }

    bool Contains(const T item) const
    {

      uint32_t index = (uint32_t)item % buckets.Size();

      T* currentItem = buckets[index].GetFirst();
      while (NULL != currentItem)
      {
        if (*currentItem == item)
        {
          return true;
        }
        currentItem = buckets[index].GetNext();
      }
      return false;
    }

    Status_t Delete(const T itemToDelete)
    {
      uint32_t index = (uint32_t)itemToDelete % buckets.Count();

      T* currentItem = buckets[index].GetFirst();

      while (NULL != currentItem)
      {
        if (*currentItem == itemToDelete)
        {
          buckets[index].DeleteCurrent();
          --count;
          //invalidates iteration for now
          currentBucket = 0;
          currentItem = NULL;
          return OpcUa_Good;
        }
        currentItem = buckets[index].GetNext();
      }
      return OpcUa_BadNotFound;
    }

    bool operator!=(const Hash_Set_t&second) const
    {
      return !(*this == second);
    }

    bool operator==(const Hash_Set_t & second) const
    {
      if (count == second.count)
      {
        T* item1 = const_cast<Hash_Set_t *>(this)->GetFirst();

        while (item1 != NULL && second.Contains(*item1))
        {
          item1 = const_cast<Hash_Set_t *>(this)->GetNext();
        }

        //Only way to get to item1 == null is to run out of items in the current set without finding one missing from the second set.
        if (item1 == NULL)
        {
          return true;
        }
      }

      return false;
    }

		void operator=(const Hash_Set_t & second)
		{
			//Initialize should clear out
			Initialise(second.buckets.Count());
			T* item = const_cast<Hash_Set_t *>(&second)->GetFirst();
			while (item != NULL)
			{
				Add(*item);
				item = const_cast<Hash_Set_t *>(&second)->GetNext();
			}
		}

  };

  template<class T> Status_t Union(Hash_Set_t<T> * set1, Hash_Set_t<T> * set2, Hash_Set_t<T> *result)
  {
    
    if (set1 == NULL || set2 == NULL || result == NULL)
    {
      return OpcUa_BadInvalidArgument;
    }

    Status_t status = result->Add(*set1);
    
    if (status.IsOutOfMemory())
    {
      return status;
    }
    
    status = result->Add(*set2);
    
    if (status.IsOutOfMemory())
    {
      return status;
    }

    return OpcUa_Good;
  }

} //namespace uasdk

#endif // UASDK_INCLUDE_EVENTS

#endif // _HASH_SET_T_

