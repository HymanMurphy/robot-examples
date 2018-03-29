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

#ifndef ARRAY_T_
#define ARRAY_T_

#include "uasdk_includes.h"
#include "utilities.h"
#include "status_t.h"
#include "allocatable_t.h"
#include "iref_count_t.h"

namespace uasdk
{
/** \addtogroup grpMiscellaneous
 *@{*/

/*****************************************************************************/
/** Free the array of primitive data type resource
 *
 * @param[in] T*& value
 * Reference to the pointer array
 *
 * @param[in] int32_t& size
 * Size of an array
 */

// Without this helper, an overloaded op&() will break everything.
template<typename T>
T *AddressOf(T &arg)
{
  // Don't ask. This is how many STL implementation do it.
  return reinterpret_cast<T*>(&const_cast<char&>(reinterpret_cast<const volatile char&>(arg)));
}

//
// Copies source to a new instance constructed at &destination,  which must be
// guaranteed to be raw memory big enough and aligned to hold the resulting
// instance. 
// Provide a *non* template overload for types that require special treatment -
// which will be just about all SDK types since they lack non-trivial copy
// constructors.
// \param [in] destination
// Pointer to uninitialised memory.
// \param [in] source
// \return
// Status_t
template<typename T>
Status_t UninitialisedCopy(T &destination, T const &source)
{
  PlacementNew_t pnx(static_cast<void*>(AddressOf(destination)));
  new(pnx) T(source);
  return OpcUa_Good;
}

//
// Copies source into destination. This is the default implementation
// and simply defers to the assignment operator. If your type does
// not support copy assignment due to it being non-trivial, then
// provide a *non* template overload.
// If your type follows the UA SDK conventions, that will typically
// be implemented by a call to CopyFrom().
template<typename T>
Status_t Copy(T &destination, T const &source)
{
  destination = source;
  return OpcUa_Good;
}

template<typename T>
void DefaultConstruct(T &a)
{
  new(static_cast<void*>(&a)) T();
}

// Default construct instances of T at &a[start] to &a[start + count - 1]
template<typename T>
Status_t DefaultConstructRange(T *a, int32_t size, int32_t start, int32_t count)
{
  if (!a || size <= 0 || start < 0 || count < 0 || (start + count > size))
    return OpcUa_BadInvalidArgument;

  int32_t end = start + count;
  for (int32_t i = start; i < end; ++i)
  {
    PlacementNew_t pnx(static_cast<void*>(&a[i]));
    new(pnx) T();
  }
  return OpcUa_Good;
}

template<> Status_t DefaultConstructRange<uint8_t>(uint8_t *a, int32_t size, int32_t start, int32_t count);

template<> Status_t DefaultConstructRange<char>(char *a, int32_t size, int32_t start, int32_t count);

// Calls the destructor of value.
template<typename T>
void Destroy(T &value)
{
  value.~T();
}

// Calls the destructor of a[start] to a[start + count - 1]
template<typename T>
Status_t DestroyRange(T *a, int32_t size, int32_t start, int32_t count)
{
  if (!a || size <= 0 || start < 0 || count < 0 || (start + count > size))
    return OpcUa_BadInvalidArgument;

  int32_t end = start + count;
  for (int32_t i = start; i < end; ++i)
  {
    Destroy(a[i]);
  }
  return OpcUa_Good;
}

template<> Status_t DestroyRange<uint8_t>(uint8_t *a, int32_t size, int32_t start, int32_t count);

template<> Status_t DestroyRange<char>(char *a, int32_t size, int32_t start, int32_t count);

//
// Holds an array of type T.
// If type U is a type to be used with Array_t<>, it must either support copy
// construction or a free function with the signature:
// Status_t UninitialiseCopy(U &, U const &)
// must be provided.
//
template<typename T>
class Array_t : public Allocatable_t
{
private:
  T* value;
  int32_t size;

protected:
  static T *Allocate(size_t count)
  {
    return static_cast<T*>(UASDK_Malloc(count * sizeof(T)));
  }

  static void Deallocate(void *p)
  {
    UASDK_Free(p);
  }

  //
  // Conceptually perform new((void*) &destination[i]) T(source[i]) for
  // i = 0 to (count - 1). To accommodate types that do not have copy
  // constructors, we delegate to:
  //  Status_t UninitializedCopy(T &destination, T const &source)
  // to perform the copy construction.
  //
  // @param [in,out] destination
  // Pointer to the destination buffer.
  // @param [in] destinationSize
  // Size of the buffer in T elements.
  // @param [in] source
  // Pointer to the source array.
  // @param [in] sourceSize.
  // Size of the source array in T elements.
  // @param [in] start
  // Index where the copy starts.
  // @param [in] count
  // Number of elements to copy.
  // @return
  // OpcUa_Good if successful, error code otherwise.
  static Status_t UninitialisedCopyRange(T *destination, int32_t destinationSize,
    T const *source, int32_t sourceSize,
    int32_t start, int32_t count)
  {

    if (!destination || destinationSize <= 0 ||
      !source || sourceSize < 0 ||
      start < 0 || count <= 0 ||
      start + count > destinationSize || start + count > sourceSize)
    {
      return OpcUa_BadInvalidArgument;
    }

    Status_t status = OpcUa_Good;
    int32_t end = start + count;
    for (int32_t i = start; i < end; ++i)
    {
      status = UninitialisedCopy(destination[i], source[i]);
      if (status.IsBad())
      {
        DestroyRange(destination, destinationSize, start, i + 1);
        return status;
      }
    }
    return status;
  }

  void Free(void)
  {
    if (value && (size > 0))
    {
      DestroyRange(value, size, 0, size);

      Array_t<T>::Deallocate(value);
      value = NULL;
      size = 0;
    }
  }

public:
  typedef T ValueType;

  Array_t()
    : value(0), size(0)
  {}

  ~Array_t()
  {
    Free();
  }

  T& operator[](int32_t i)
  {
    UASDK_ASSERT(value != 0);
    return value[i];
  }

  const T& operator[](int32_t i) const
  {
    UASDK_ASSERT(value != 0);
    return value[i];
  }

  const T* Value(void) const
  {
    return value;
  }

  T* Value(void)
  {
    return value;
  }

  int32_t Size(void) const
  {
    return size;
  }

  int32_t Count(void) const
  {
    return Size();
  }

  bool IsEmpty(void) const
  {
    return Size() == 0;
  }

  bool Initialised(void) const
  {
    return value != 0;
  }

  Status_t Initialise(int32_t count)
  {
    Free();

    if (count <= 0)
    {
      return OpcUa_Good;
    }

    T *a = Array_t<T>::Allocate(count);
    if (!a)
    {
      UASDK_RETURN_BAD_STATUS(OpcUa_BadOutOfMemory);
    }

    Status_t status = DefaultConstructRange(a, count, 0, count);
    if (status.IsBad())
    {
      Array_t<T>::Deallocate(a);
      return status;
    }

    status = DestroyRange(a, count, 0, count);

    status = DefaultConstructRange(a, count, 0, count);
    if (status.IsBad())
    {
      Array_t<T>::Deallocate(a);
      return status;
    }


    value = a;
    size = count;

    return OpcUa_Good;
  }

  /*
   * Resizes the array.
   *
   * @param newSize
   * The new size of the array. If newSize is less than or equal to zero
   * the elements of the array are destroyed and the memory deallocated.
   *
   * If newSize is greater than the current size of the array, the array
   * is expanded, existing elements are copied into the larger array, and
   * the additional elements are default constructed. The elements in the
   * previous array are destroyed and the memory is free'd.
   *
   * If newSize is less than the current size of the array, the array is
   * is shrunk. The remaining elements of the existing array are copy
   * constructed into the new array. The elements in the previous array are
   * destroyed and the array memory is free'd.
   *
   * @return
   * Success or out of memory if a memory allocation fails.
   */
   // TODO: provide machinery to Initialise() with arguments on constructed
   //       elements. Would need C++11 to be useful.
  Status_t Resize(int32_t newSize)
  {
    if (newSize <= 0)
    {
      Array_t<T>::Free();
      return OpcUa_Good;
    }

    if (newSize == this->size)
    {
      return OpcUa_Good;
    }

    T *newValue = NULL;
    if (newSize > this->size)
    {
      newValue = Array_t<T>::Allocate(newSize);
      if (!newValue)
        return OpcUa_BadOutOfMemory;

      Status_t status = Array_t<T>::UninitialisedCopyRange(newValue, newSize,
        this->value, this->size,
        0, size);
      if (status.IsBad())
      {
        Array_t<T>::Deallocate(newValue);
        return status;
      }

      status = DefaultConstructRange(newValue, newSize, size,
        newSize - this->size);
      if (status.IsBad())
      {
        Array_t<T>::Deallocate(newValue);
        return status;
      }
    }
    else
    {
      newValue = Array_t<T>::Allocate(newSize);
      if (!newValue)
        return OpcUa_BadOutOfMemory;

      Status_t status = Array_t<T>::UninitialisedCopyRange(newValue, newSize,
        this->value, this->size,
        0, newSize);
      if (status.IsBad())
      {
        Array_t<T>::Deallocate(newValue);
        return status;
      }
    }

    Array_t<T>::Free();

    this->value = newValue;
    this->size = newSize;

    return OpcUa_Good;
  }

  // Loops through the array calling pred(k, *this[i]) and
  // returns the index of the first element that returns true.
  template<typename K, typename Predicate>
  int32_t FindFirstWithPredicate(K const &k, int32_t start, int32_t count, Predicate const &pred) const
  {
    int32_t end = start + count;
    for (int32_t i = start; i < end; ++i)
    {
      if (pred(k, value[i]))
        return i;
    }
    return -1;
  }

};

template<typename T> class ArrayRef_t : public Array_t<T>, public IRefCount_t
{

};

/** @} */

}

#endif 

