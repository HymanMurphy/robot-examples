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

#ifndef ATOMIC_T_H_
#define ATOMIC_T_H_

#include "uasdk_includes.h"

#if (UASDK_INCLUDE_ATOMIC_CPP11 > 0)

#include <atomic>

namespace uasdk
{
/** \addtogroup grplockCPP11
 *@{*/

/*****************************************************************************/
/** \brief Atomic_t
 *
 * A class implements the thread safe data access using the CPP11 starndard library.
 *
 */
  template<class T>
  class Atomic_t
  {
  private:
    std::atomic<T> value;

  public:
    Atomic_t()
    {
      value = 0;
    }

    /*****************************************************************************/
    /** function used to initialize the object
     *
     * @return
     * returns result of the operation.
     */
    Status_t Initialise(void)
    {
      return OpcUa_Good;
    }

    /*****************************************************************************/
    /** function used to get the value
     *
     * @return
     * returns number of times a reference counting pointer is referenced
     */
    T Value(void)
    {
      return value;
    }

    /*****************************************************************************/
    /** function used to set the value
     *
     * @param[in] val
     * new value that atomic value to be assigned with
     */
    void Value(T val)
    {
      value = val;
    }

    /*****************************************************************************/
    /** function used to increment the value
     *
     * @return
     * returns incremented value
     */
    T Increment(void)
    {
      return value.fetch_add(1);
    }

    /*****************************************************************************/
    /** function used to decrement the value
     *
     * @return
     * returns decremented value
     */
    T Decrement(void)
    {
      return value.fetch_sub(1);
    }

  };
/** @} */

} /* namespace uasdk */

#endif //UASDK_INCLUDE_ATOMIC_CPP11

#endif /* ATOMIC_T_H_ */
