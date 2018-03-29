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

#ifndef _ISAFE_REF_COUNT_ARRAY_T_
#define _ISAFE_REF_COUNT_ARRAY_T_

#include "uasdk_includes.h"

#if (UASDK_INCLUDE_REF_COUNT_CPP11 > 0)

#include <atomic>

namespace uasdk
{

/** \addtogroup grpSmartPointer
 *@{*/

  /*****************************************************************************/
  /** This class used for safe reference counting.
   *
   */
  template<class T>
  class SafeRefCountArray_t : public T
  {
  private:
    mutable std::atomic<int> safeRefCount;

  protected:

    /*****************************************************************************/
    /** Get the reference count
     *
     * @return
     * Returns the reference count
     */
    virtual int RefCount(void) const
    {
      return safeRefCount;
    }

  public:

    /*****************************************************************************/
    /** Default of the constructor of the class
     */
    SafeRefCountArray_t() : safeRefCount(0) {}

    /*****************************************************************************/
    /** Destructor of the class
     */
    virtual ~SafeRefCountArray_t() {};

    /*****************************************************************************/
    /** This function used to add the references..
     *
     */
    virtual void AddReference() const
    {
      safeRefCount.fetch_add(1, std::memory_order_relaxed);
    }

    /*****************************************************************************/
    /** This function used to remove the references. when the count reaches zero
     * deallocate the pointer array
     */
    virtual void RemoveReference() const
    {
      if (safeRefCount.fetch_sub(1, std::memory_order_release) == 1)
      {
        std::atomic_thread_fence(std::memory_order_acquire);
        delete this;
      }
    }

  };

/** @} */

} /* namespace uasdk */

#endif  //UASDK_INCLUDE_REF_COUNT_CPP11

#endif // _ISAFE_REF_COUNT_ARRAY_T_
