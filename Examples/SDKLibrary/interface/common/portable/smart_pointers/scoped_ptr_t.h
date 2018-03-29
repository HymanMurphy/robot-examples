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

//  (C) Copyright Greg Colvin and Beman Dawes 1998, 1999.
//  Copyright (c) 2001, 2002 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  http://www.boost.org/libs/smart_ptr/intrusive_ptr_t.htm
//

#ifndef _UA_SCOPED_PTR_
#define _UA_SCOPED_PTR_

#include "uasdk_includes.h"

namespace uasdk
{

/** \addtogroup grpSmartPointer
 *@{*/

/*****************************************************************************/
/** This class used for safe reference counting.
 * ScopedArrayPtr_t mimics a built-in pointer except that it guarantees deletion
 * of the object pointed to, either on destruction of the ScopedPtr_t or via
 * an explicit reset(). ScopedPtr_t is a simple solution for simple needs;
 * use shared_ptr or std::auto_ptr if your needs are more complex.
 * It is a non-copyable object
 */
template<class T> class ScopedPtr_t // noncopyable
{

  /*****************************************************************************/
  /** Transfer the pointer from the source to destination
   *
   * @param[in] ScopedPtr_t<U> & a
   *  Scoped Pointer which points to the template class object
   *
   * @param[in] ScopedPtr_t<v> & b
   *  Scoped Pointer which points to the template class object
   */
  template<class U, class V>
  friend void ScopedPtr_t_transfer(ScopedPtr_t<U> & a, ScopedPtr_t<V> & b) UASDK_NO_THROW;

private:

  T* px;

  ScopedPtr_t(ScopedPtr_t const &);
  ScopedPtr_t & operator=(ScopedPtr_t const &);

  typedef ScopedPtr_t<T> this_type;

  void operator==( ScopedPtr_t const& ) const;
  void operator!=( ScopedPtr_t const& ) const;

public:

  typedef T element_type;

  /*****************************************************************************/
  /** Parameterized Constructor of the class
   *
   * @param[in] T* p
   *  Pointer to the template class object
   */
  explicit ScopedPtr_t( T * p = 0 ): px( p ) // never throws
  {
  }

  /*****************************************************************************/
  /** Destructor of the class
   */
  ~ScopedPtr_t() // never throws
  {
    if (px != 0)
    {
      delete px;
    }
  }

  /*****************************************************************************/
  /** reset the pointer to NULL or the pointer passed by the user
   */
  void reset(T * p = 0) // never throws
  {
    UASDK_ASSERT( p == 0 || p != px ); // catch self-reset errors
    this_type(p).swap(*this);
  }

  /*****************************************************************************/
  /** reset the pointer to the pointer passed by the caller
   */
  template<class U> void reset(U* p)
  {
    T* pp = static_cast<T*>(p);
    reset(pp);
  }

  /*****************************************************************************/
  /** -> operator overloading
   *
   * @return
   * Returns the pointer to the template class object
   */
  T * operator->() const UASDK_NO_THROW
  {
    UASDK_ASSERT( px != 0 );
    return px;
  }

  /*****************************************************************************/
  /** * operator overloading
   *
   * @return
   * Returns the Reference to the template class object
   */
  T& operator*() const UASDK_NO_THROW
  {
    UASDK_ASSERT( px != 0 );
    return *px;
  }

  /*****************************************************************************/
  /** Get the pointer
   *
   * @return
   * returns the pointer to the object(template type)
   */
  T * get() const UASDK_NO_THROW
  {
    return px;
  }

  /*****************************************************************************/
  /** NULL pointer check
   *
   * return
   * true - if not NULL
   * false - if NULl
   */
  bool is_set() const UASDK_NO_THROW
  {
    return (0 != px);
  }

  /*****************************************************************************/
  /**  This method is used for copy and swap Idioms
   *
   * @param[in] ScopedPtr_t & b
   * object to be swapped with
   */
  void swap(ScopedPtr_t & b) UASDK_NO_THROW
  {
    T * tmp = b.px;
    b.px = px;
    px = tmp;
  }

};

/*****************************************************************************/
/**  swap the intrusive pointers
 *
 * @param[in] ScopedPtr_t<T> const & a
 *  Scoped pointer object with template T
 *
 * @param[in] v<T> const & b
 *  Scoped pointer object with template T
 */
template<class T> inline void swap(ScopedPtr_t<T> & a, ScopedPtr_t<T> & b) UASDK_NO_THROW
{
  a.swap(b);
}

/*****************************************************************************/
/** Transfer the pointer from the source to destination
 *
 * @param[in] ScopedPtr_t<U> & source
 *  Scoped Pointer which points to the template class object
 *
 * @param[in] ScopedPtr_t<v> & destination
 *  Scoped Pointer which points to the template class object
 */
template<class T, class U> inline void ScopedPtr_t_transfer(
    ScopedPtr_t<T> & source,
    ScopedPtr_t<U> & destination) UASDK_NO_THROW
{
  T * tmp = source.px;
  source.px = 0;
  destination.reset(tmp);
}

/*****************************************************************************/
/** get_pointer(p) is a generic way to say p.get()
 *
 * @param[in] ScopedPtr_t<T> const & p
 *  Reference of the Scoped pointer object with template type T
 *
 * @return
 * returns the pointer to the object(template type) *
 */
template<class T> inline T * get_pointer(ScopedPtr_t<T> const & p) UASDK_NO_THROW
{
  return p.get();
}

/*****************************************************************************/
/**  wrapper to function to do the static cast of a pointer
 *
 * @param[in] ScopedPtr_t<U> const & p
 *  Scoped array pointer object with template U
 *
 * @return
 * returns the pointer to the object of template type T
 */
template<class T, class U> T* static_pointer_cast(ScopedPtr_t<U> const & p)
{
    return static_cast<T*>(p.get());
}

/** @} */

} // namespace uasdk

#endif // _UA_SCOPED_PTR_
