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
-----------------------------------------------------------------------------------------------------------------*/

//
//  intrusive_ptr_t.hpp
//
//  Copyright (c) 2001, 2002 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/smart_ptr/intrusive_ptr_t.html for documentation.
//

#ifndef _UA_INTRUSIVE_PTR_
#define _UA_INTRUSIVE_PTR_

#include "uasdk_includes.h"
#include "safe_ref_count_t.h"

namespace uasdk
{
/** \addtogroup grpSmartPointer
 *@{*/


/*****************************************************************************/
/** Add reference to the Intrusive pointer
 *
 * @param[in] p
 * An intrusive reference counting Boost-style smart pointer.
 *
 */
template<typename T> void IntrusivePtr_t_add_ref(T * p)
{
  if (p)
  {
    p->AddReference();
  }
}

/*****************************************************************************/
/** Remove reference of the Intrusive pointer
 *
 * @param[in] p
 * An intrusive reference counting Boost-style smart pointer.
 *
 */
template<typename T> void IntrusivePtr_t_release(T * p)
{
  if (p)
  {
    p->RemoveReference();
  }
}


//
//  IntrusivePtr_t
//
//  A smart pointer that uses intrusive reference counting.
//
//  Relies on unqualified calls to
//
//      void IntrusivePtr_t_add_ref(T * p);
//      void IntrusivePtr_t_release(T * p);
//
//          (p != 0)
//
//  The object is responsible for destroying itself.
//


/*****************************************************************************/
/** \brief IntrusivePtr_t
 *
 * A smart pointer that uses intrusive reference counting. The object is
 * responsible for destroying itself.
 *
 *   Relies on unqualified calls to
 *        void IntrusivePtr_t_add_ref(T * p);
 *        void IntrusivePtr_t_release(T * p);
 */
template<class T> class IntrusivePtr_t
{
private:

    typedef IntrusivePtr_t this_type;

public:

    typedef T element_type;

  /*****************************************************************************/
  /** Default Constructor of the class
   */
    IntrusivePtr_t() UASDK_NO_THROW : px( 0 )
    {
    }
  
  /*****************************************************************************/
  /** Parameterized Constructor of the class
     * @param[in] T* p
   *  Pointer to the template class object
   *
   * @param[in] bool add_ref
   *  This is a default parameter set to true which enables reference counting
   *
   */

    IntrusivePtr_t( T * p, bool add_ref = true ): px( p )
    {
      if( px != 0 && add_ref ) IntrusivePtr_t_add_ref( px );
    }

  /*****************************************************************************/
  /** Parameterized Constructor of the class
   *
   * @param[in] T& obj
   *  Reference of the template class object.
   */
    IntrusivePtr_t(T& obj): px( &obj )
    {
        if( px != 0 ) IntrusivePtr_t_add_ref( px );
    }

  /*****************************************************************************/
  /** copy Constructor of the class
   *
   * @param[in] IntrusivePtr_t const & rhs
   *  Object to be copied
   */
    IntrusivePtr_t(IntrusivePtr_t const & rhs): px( rhs.px )
    {
        if( px != 0 ) IntrusivePtr_t_add_ref( px );
    }

  /*****************************************************************************/
  /** copy Constructor of the class
   *
   * @param[in] IntrusivePtr_t<U> const & rhs
   *  Object to be copied
   */
    template<class U> IntrusivePtr_t(IntrusivePtr_t<U> const & rhs): px( rhs.get() )
    {
        if( px != 0 ) IntrusivePtr_t_add_ref( px );
    }

  /*****************************************************************************/
  /** Destructor of the class
   */
    ~IntrusivePtr_t()
    {
        if( px != 0 ) IntrusivePtr_t_release( px );
    }

  /*****************************************************************************/
  /** = operator overloading
   *
   * @param[in] IntrusivePtr_t<U> const & rhs
   *  Object to be assigned
   */
    template<class U> IntrusivePtr_t & operator=(IntrusivePtr_t<U> const & rhs)
    {
        this_type(rhs).swap(*this);
        return *this;
    }

  /*****************************************************************************/
  /** = operator overloading
   *
   * @param[in] IntrusivePtr_t const & rhs
   *  Object to be assigned
   */
    IntrusivePtr_t & operator=(IntrusivePtr_t const & rhs)
    {
        this_type(rhs).swap(*this);
        return *this;
    }

  /*****************************************************************************/
  /** = operator overloading
   *
   * @param[in] T * rhs
   *  template class object's pointer to be assigned
   */
    IntrusivePtr_t & operator=(T * rhs)
    {
        this_type(rhs).swap(*this);
        return *this;
    }

  /*****************************************************************************/
  /** reset the pointer to NULL
   */
    void reset() UASDK_NO_THROW
    {
        this_type().swap( *this );
    }

  /*****************************************************************************/
  /** reset the intrusive pointer with the pointer passed by the user
   *
   * @param[in] T * rhs
   *  template class object's pointer to be assigned
   */
    void reset( T * rhs )
    {
        this_type( rhs ).swap( *this );
    }

  /*****************************************************************************/
  /** Get the pointer
   *
   * @return
   *  Returns the pointer to the template class object
   */
    T * get() const UASDK_NO_THROW
    {
        return px;
    }

  /*****************************************************************************/
  /** Is the pointer is set to a valid object or not
   *
   * @return
   *  true - if the pointer is not NULL
   *  false - if the pointer is NULL
   */
    bool is_set() const UASDK_NO_THROW
    {
      return (0 != px);
    }

  /*****************************************************************************/
  /**  * operator overloading
   *
   * @return
   *  Returns the object which intrusive pointer points to
   */
    T & operator*() const
    {
        UASDK_ASSERT( px != 0 );
        return *px;
    }

  /*****************************************************************************/
  /**  -> operator overloading
   *
   * @return
   *  Returns the intrusive pointer points to an object
   */
    T * operator->() const
    {
        UASDK_ASSERT( px != 0 );
        return px;
    }

// implicit conversion to "bool"
//#include <boost/smart_ptr/detail/operator_bool.hpp>

private:

  /*****************************************************************************/
  /**  This method is used for copy and swap Idioms
   *
   * @return
   *  Returns the intrusive pointer points to an object
   */
    void swap(IntrusivePtr_t & rhs) UASDK_NO_THROW
    {
        T * tmp = px;
        px = rhs.px;
        rhs.px = tmp;
    }

  /*****************************************************************************/
  /** @var T* px
   * Pointer to the template class object
   */
    T * px;
};

/*****************************************************************************/
/**  == operator overloading
 *
 * @param[in] IntrusivePtr_t<T> const & a
 *  Intrusive pointer object with template T
 *
 * @param[in] IntrusivePtr_t<U> const & b
 *  Intrusive pointer object with template U
 *
 * @return
 *  True - if equal
 *  False - if not equal
 */
template<class T, class U> inline bool operator==(IntrusivePtr_t<T> const & a, IntrusivePtr_t<U> const & b)
{
    return a.get() == b.get();
}

/*****************************************************************************/
/**  != operator overloading
 *
 * @param[in] IntrusivePtr_t<T> const & a
 *  Intrusive pointer object with template T
 *
 * @param[in] IntrusivePtr_t<U> const & b
 *  Intrusive pointer object with template U
 * @return
 *  True - if not equal
 *  False - if equal
 */
template<class T, class U> inline bool operator!=(IntrusivePtr_t<T> const & a, IntrusivePtr_t<U> const & b)
{
    return a.get() != b.get();
}

/*****************************************************************************/
/**  == operator overloading
 *
 * @param[in] IntrusivePtr_t<T> const & a
 *  Intrusive pointer object with template T
 *
 * @param[in] U* b
 *  Pointer to an object of template type U
 *
 * @return
 *  True - if equal
 *  False - if not equal
 */
template<class T, class U> inline bool operator==(IntrusivePtr_t<T> const & a, U * b)
{
    return a.get() == b;
}

/*****************************************************************************/
/**  != operator overloading
 *
 * @param[in] IntrusivePtr_t<T> const & a
 *  Intrusive pointer object with template T
 *
 * @param[in] U* b
 *  Pointer to an object of template type U
 *
 * @return
 *  True - if not equal
 *  False - if equal
 */
template<class T, class U> inline bool operator!=(IntrusivePtr_t<T> const & a, U * b)
{
    return a.get() != b;
}

/*****************************************************************************/
/**  == operator overloading
 *
 * @param[in] T* a
 *  Pointer to an object of template type T
 *
 * @param[in] IntrusivePtr_t<U> const & b
 *  Intrusive pointer object with template U
 *
 * @return
 *  True - if equal
 *  False - if not equal
 */
template<class T, class U> inline bool operator==(T * a, IntrusivePtr_t<U> const & b)
{
    return a == b.get();
}

/*****************************************************************************/
/**  != operator overloading
 *
 * @param[in] T* a
 *  Pointer to an object of template type T
 *
 * @param[in] IntrusivePtr_t<U> const & b
 *  Intrusive pointer object with template U
 *
 * @return
 *  True - if not equal
 *  False - if equal
 */
template<class T, class U> inline bool operator!=(T * a, IntrusivePtr_t<U> const & b)
{
    return a != b.get();
}

#if __GNUC__ == 2 && __GNUC_MINOR__ <= 96

// Resolve the ambiguity between our op!= and the one in rel_ops

/*****************************************************************************/
/**  != operator overloading
 *
 * @param[in] IntrusivePtr_t<T> const & a
 *  Intrusive pointer object with template T
 *
 * @param[in] IntrusivePtr_t<U> const & b
 *  Intrusive pointer object with template U
 *
 * @return
 *  True - if not equal
 *  False - if equal
 */
template<class T> inline bool operator!=(IntrusivePtr_t<T> const & a, IntrusivePtr_t<T> const & b)
{
    return a.get() != b.get();
}

#endif

/*****************************************************************************/
/**  > operator overloading
 *
 * @param[in] IntrusivePtr_t<T> const & a
 *  Intrusive pointer object with template T
 *
 * @param[in] IntrusivePtr_t<U> const & b
 *  Intrusive pointer object with template U
 *
 * @return
 *  True - if *a > *b
 *  False - if *a < *b
 */
template<class T> inline bool operator>(IntrusivePtr_t<T> const & a, IntrusivePtr_t<T> const & b)
{
  if (a.is_set() && b.is_set())
  {
    return *a > *b;
  }
  return false;
}

/*****************************************************************************/
/**  swap the intrusive pointers
 *
 * @param[in] IntrusivePtr_t<T> const & lhs
 *  Intrusive pointer object with template T
 *
 * @param[in] IntrusivePtr_t<T> const & rhs
 *  Intrusive pointer object with template T
 */
template<class T> void swap(IntrusivePtr_t<T> & lhs, IntrusivePtr_t<T> & rhs)
{
    lhs.swap(rhs);
}

/*****************************************************************************/
/**  Get the pointer to the object of template type T
 *
 * @param[in] IntrusivePtr_t<T> const & p
 *  Intrusive pointer object with template T
 *
 *@return
 * returns the pointer to the object of template type T
 */
template<class T> T * get_pointer(IntrusivePtr_t<T> const & p)
{
    return p.get();
}

/*****************************************************************************/
/**  wrapper to function to do the static cast of a pointer
 *
 * @param[in] IntrusivePtr_t<U> const & p
 *  Intrusive pointer object with template U
 *
 *@return
 * returns the pointer to the object of template type T
 */
template<class T, class U> IntrusivePtr_t<T> static_pointer_cast(IntrusivePtr_t<U> const & p)
{
    return static_cast<T *>(p.get());
}

/*****************************************************************************/
/**  wrapper to function to do the const cast of a pointer
 *
 * @param[in] IntrusivePtr_t<T> const & p
 *  Intrusive pointer object with template T
 *
 *@return
 * returns the pointer to the object of template type T
 */
template<class T, class U> IntrusivePtr_t<T> const_pointer_cast(IntrusivePtr_t<U> const & p)
{
    return const_cast<T *>(p.get());
}

/**
 * Wrapper for allocating an object managed by IntrusivePtr_t.
 * Check for allocation success with is_set().
 * @return
 * Returns an InstrusivePtr_t.
 */
template<typename T> IntrusivePtr_t<T> MakeIntrusive()
{
  return IntrusivePtr_t<T>(new SafeRefCount_t<T>);
}

/** @} */

} // namespace uasdk

#endif // _UA_INTRUSIVE_PTR_
