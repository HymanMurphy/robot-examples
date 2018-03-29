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

#ifndef _ISAFE_REF_COUNT_T_
#define _ISAFE_REF_COUNT_T_

#include "atomic_t.h"

#if (UASDK_INCLUDE_REF_COUNT_ANY_PLATFORM_ST > 0)

namespace uasdk
{

/** \addtogroup grpSmartPointer
 *@{*/

  /*****************************************************************************/
  /** This class used for safe reference counting.
   *
   */
  template<class T>
  class SafeRefCount_t : public T
  {
  private:
    mutable int refCount;

  protected:

    /*****************************************************************************/
    /** Get the reference count
     *
     * @return
     * Returns the reference count
     */
    virtual int RefCount(void) const
    {
      return refCount;
    }

  public:
    SafeRefCount_t() : refCount(0)
    {}

    /*****************************************************************************/
    /** Destructor of the class
     */
    virtual ~SafeRefCount_t() {}

    /*****************************************************************************/
    /** This function used to add the references..
     *
     */
    virtual void AddReference() const
    {
      refCount++;
    }

    /*****************************************************************************/
    /** This function used to remove the references. when the count reaches zero
     * deallocate the pointer
     */
    virtual void RemoveReference() const
    {
      if (--refCount == 0)
      {
        delete this;
      }
    }

  };

  template<typename T> class RefCount_t : public SafeRefCount_t<T>
  {

  };

/*@}*/

} /* namespace uasdk */

#endif  //UASDK_INCLUDE_REF_COUNT_ANY_PLATFORM_ST

#endif // _ISAFE_REF_COUNT_T_
