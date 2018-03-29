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

#ifndef _ALLOCATABLE_T_
#define _ALLOCATABLE_T_

#include "uasdk_includes.h"
#include "iallocator_t.h"

namespace uasdk
{
/** \addtogroup grpMemory
 *@{*/

/*****************************************************************************/
/** \brief Allocatable_t
 *
 * A Class to manage the memory allocation in heap
 *
 */
class Allocatable_t
{
private:
#if (UASDK_USE_SYSTEM_HEAP == 0)
  static IAllocator_t* allocator;
#endif

public:
  Allocatable_t(){}
  virtual ~Allocatable_t(){}

#if (UASDK_USE_SYSTEM_HEAP == 0)
  /*****************************************************************************/
  /** new operator overloading
   *
   * @param[in] size_t size
   * number of bytes to allocate
   *
   * @return
   * Address of the allocated memory
   */
  static void* operator new(size_t size) UASDK_NO_THROW;

  /*****************************************************************************/
  /** new[] operator overloading
   *
   * @param[in] size_t size
   * size of an array to allocate
   *
   * @return
   * Starting address of an array
   */
  static void* operator new[] (size_t nbytes) UASDK_NO_THROW;

  /*****************************************************************************/
  /** delete operator overloading
   *
   * @param[in] void* p
   * pointer to deallocate
   */
  static void operator delete(void *p) UASDK_NO_THROW;

  /*****************************************************************************/
  /** delete[] operator overloading
   *
   * @param[in] void* p
   * Array of pointer to deallocate
   */
  static void operator delete[] (void* p) UASDK_NO_THROW;

  /*****************************************************************************/
  /** Get the allocator object
   *
   * @return
   * Returns the pointer to the object of an allocator
   */
  static IAllocator_t* Allocator(void) { return allocator; }

  /*****************************************************************************/
  /** Set the allocator object
   *
   * @param[in] IAllocator_t* value
   * pointer to the object of an allocator
   */
  static void Allocator(IAllocator_t* value) { allocator  = value; }

  /*****************************************************************************/
   /** operator new overloading
    *
    * @param[in] size_t nbytes
    * pointer to the object of an allocator
    *
    * @param[in] PlacementNew_t& obj
    * Reference to an object PlacementNew_t
    *
    * @return
    * void pointer to the allocated memory
    */
  static void* operator new(size_t nbytes, PlacementNew_t& obj) UASDK_NO_THROW;

  /*****************************************************************************/
   /** operator delete overloading
    *
    * @param[in] void* p
    * pointer to the memory to deallocate
    *
    * @param[in] PlacementNew_t& obj
    * Reference to an object PlacementNew_t
    */
  static void operator delete(void*, PlacementNew_t& obj) UASDK_NO_THROW;

#endif

};

/** @} */

}

#endif //_ALLOCATABLE_T_
