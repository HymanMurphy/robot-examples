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

#ifndef _IITERATOR_T_
#define _IITERATOR_T_

#include "uasdk_includes.h"
#include "iref_count_t.h"
#include "intrusive_ptr_t.h"
#include "status_t.h"

namespace uasdk
{
/** \addtogroup grpMiscellaneous
 *@{*/

template<class T>
class IIterator_t : public IRefCount_t
{
public:
  virtual ~IIterator_t() {};

  /*****************************************************************************/
  /* Function used to get the first element from the iterator.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<T> First(void) const = 0;

  /*****************************************************************************/
  /* Function used to get the next element from the iterator.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<T> Next(void) const = 0;

  /*****************************************************************************/
  /* Get current element from the iterator.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  virtual IntrusivePtr_t<T> Current(void) const = 0;

  /*****************************************************************************/
  /** Function used to remove the current element from the iterator.
   *
   * @return
   * An intrusive reference counting Boost-style smart pointer to the
   * node. The caller must test the pointer before dereferencing it.
   */
  virtual Status_t RemoveCurrent(void) = 0;

  /*****************************************************************************/
  /** Function used to reset the current element to iteratefrom the beginning.
  *
  */
  virtual void ResetCurrent(void) const = 0;
};

/** @} */

}

#endif // _IITERATOR_T_
