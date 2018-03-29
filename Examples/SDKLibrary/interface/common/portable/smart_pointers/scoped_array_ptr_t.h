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

#ifndef _UA_SCOPED_ARRAY_
#define _UA_SCOPED_ARRAY_

#include "uasdk_includes.h"

namespace uasdk
{

/** \addtogroup grpSmartPointer
 *@{*/

/*****************************************************************************/
/** This class used for safe reference counting.
 * ScopedArrayPtr_t mimics a built-in pointer except that it guarantees deletion
 * of the object pointed to, either on destruction of the ScopedArrayPtr_t or via
 * an explicit reset(). ScopedArrayPtr_t is a simple solution for simple needs;
 * use shared_ptr or std::auto_ptr if your needs are more complex.
 * It is a non-copyable object
 */
template<class T> class ScopedArrayPtr_t // noncopyable
{
//  template<class A, class B>
//  friend void IntrusivePtr_t_transfer(ScopedArrayPtr_t<A> & a, ScopedArrayPtr_t<B> & b) UA_NO_THROW;

private:

  T* px;

  ScopedArrayPtr_t(ScopedArrayPtr_t const &);
  ScopedArrayPtr_t & operator=(ScopedArrayPtr_t const &);

  typedef ScopedArrayPtr_t<T> this_type;

  void operator==( ScopedArrayPtr_t const& ) const;
  void operator!=( ScopedArrayPtr_t const& ) const;

public:

  typedef T element_type;

  /*****************************************************************************/
  /** Parameterized Constructor of the class
   *
   * @param[in] T* p
   *  Pointer to the template class object
   */
  explicit ScopedArrayPtr_t( T * p = 0 ): px( p ) // never throws
  {
  }

  /*****************************************************************************/
  /** Destructor of the class
   */
  ~ScopedArrayPtr_t() // never throws
  {
    if (px != 0)
    {
      delete[] px;
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

//  T * operator->() const UA_NO_THROW
//  {
//    UASDK_ASSERT( px != 0 );
//    return px;
//  }
//
//  T& operator*() const UA_NO_THROW
//  {
//    UASDK_ASSERT( px != 0 );
//    return *px;
//  }

  /*****************************************************************************/
  /** [] operator overloading
   *
   * @param[in] uint32_t i
   * array index
   *
   */
  T& operator[](uint32_t i) const UASDK_NO_THROW
  {
    UASDK_ASSERT( px != 0 );
    return px[i];
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
   * @param[in] ScopedArrayPtr_t & b
   * object to be swapped with
   */
  void swap(ScopedArrayPtr_t & b) UASDK_NO_THROW
  {
    T * tmp = b.px;
    b.px = px;
    px = tmp;
  }

};

/*****************************************************************************/
/**  swap the intrusive pointers
 *
 * @param[in] ScopedArrayPtr_t<T> const & a
 *  Scoped Array pointer object with template T
 *
 * @param[in] ScopedArrayPtr_t<T> const & b
 *  Scoped Array pointer object with template T
 */
template<class T> inline void swap(ScopedArrayPtr_t<T> & a, ScopedArrayPtr_t<T> & b) UASDK_NO_THROW
{
  a.swap(b);
}

/*****************************************************************************/
/** get_pointer(p) is a generic way to say p.get()
 *
 * @param[in] ScopedArrayPtr_t<T> const & p
 *  Scoped Array pointer object with template T
 *
 * @return
 * returns the pointer to the object(template type) *
 */
template<class T> inline T * get_pointer(ScopedArrayPtr_t<T> const & p) UASDK_NO_THROW
{
  return p.get();
}

/*****************************************************************************/
/**  wrapper to function to do the static cast of a pointer
 *
 * @param[in] ScopedArrayPtr_t<U> const & p
 *  Scoped array pointer object with template U
 *
 * @return
 * returns the pointer to the object of template type T
 */
template<class T, class U> T* static_pointer_cast(ScopedArrayPtr_t<U> const & p)
{
    return static_cast<T*>(p.get());
}

/** @} */

} // namespace uasdk

#endif // _UA_SCOPED_ARRAY_
