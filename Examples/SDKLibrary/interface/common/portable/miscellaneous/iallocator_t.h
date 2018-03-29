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

#ifndef _IALLOCATOR_T_
#define _IALLOCATOR_T_

#include "uasdk_includes.h"

/** \addtogroup grpMemory
 *@{*/

class PlacementNew_t
{
public:
  void* const p;

  PlacementNew_t(void* p_) : p(p_) {}
private:

  /*****************************************************************************/
  /** This function used to overload the "=" Operator.
   *
   * @param[in]
   * Input parameter is of PlacementNew_t type
   *
   * @return
   * returns the value is of type PlacementNew_t.
   */
  PlacementNew_t &operator=(PlacementNew_t const &);
};

/** @} */

/*****************************************************************************/
/** This function used to overload the "new" Operator.
 *
 * @param[in] nbytes
 * Number of bytes.
 *
 * @param[in] obj
 * Input parameter is of PlacementNew_t type
 */
inline void* operator new(size_t nbytes, PlacementNew_t& obj) UASDK_NO_THROW
{
  UASDK_UNUSED(nbytes);
  return obj.p;
}

/*****************************************************************************/
/** This function used to overload the "delete" Operator.
 *
 * @param[in] void *
 * Input is of pointer type
 *
 * @param[in] obj
 * Input parameter is of PlacementNew_t type
 */
inline void operator delete(void*, PlacementNew_t& obj) UASDK_NO_THROW
{
  UASDK_UNUSED(obj);
}

namespace uasdk
{

/** \addtogroup grpMemory
 *@{*/

//** This class is used to allocate the memory.
class IAllocator_t
{
public:
  virtual ~IAllocator_t(){}

  /*****************************************************************************/
  /** This function used to allocate the memory dynamically.
   *
   * @param[in] size
   * size of the memory to be allocate.
   *
   */
  virtual void* Malloc(uint32_t size) = 0;

  /*****************************************************************************/
  /** This function used to free the memory on heap.
   *
   * @param[in] void *
   * size of the memory to be deallocate.
   *
   */
  virtual void Free(void* p) = 0;

  /*****************************************************************************/
  /** This function used to get the memory information.
   *
   * @param[out] totalMemoryProvided
   * total memory provided for the process.
   *
   * @param[out] usableMemory
   * usable memory out of total memory.
   *
   * @param[out] maxMemoryCommitted
   * maximum memory committed for the process.
   *
   * @param[out] currentMemoryCommitted
   * current memory committed for the process.
   *
   * @param[out]  totalMemoryRecommended
   * total memory recommended for the the process.
   *
   * @return
   * returns status of the operation.
   *
   */
  virtual Status_t MemoryInfo(uint32_t& totalMemoryProvided,
                              uint32_t& usableMemory,
                              uint32_t& maxMemoryCommitted,
                              uint32_t& currentMemoryCommitted,
                              uint32_t& totalMemoryRecommended) = 0;

};

/** @} */

}

/*****************************************************************************/
/** This function used to allocate the memory dynamically.
 *
 * @param[in] size
 * size of the memory to be allocate.
 *
 */
#if (UASDK_OVERLOAD_NEW_AND_DELETE != 0)
inline void* operator new(size_t nbytes) UASDK_NO_THROW
{
  /* Catch usage when debugging */
  UASDK_ASSERT(false);
  return 0;
}

/*****************************************************************************/
/** This function used to free the memory on heap.
 *
 * @param[in] size
 * size of the memory to be deallocate.
 *
 */
inline void operator delete(void* p)
{
  /* Catch usage when debugging */
  UASDK_ASSERT(false);
}

/*****************************************************************************/
/** This function used to allocate the memory for array dynamically.
 *
 * @param[in] size
 * number of bytes to be allocate.
 *
 */
inline void* operator new[] (size_t nbytes) UASDK_NO_THROW
{
  /* Catch usage when debugging */
  UASDK_ASSERT(false);
  return 0;
}


/*****************************************************************************/
/** This function used to free the memory allocated for array on heap.
 *
 * @param[in] size
 * number of bytes to be allocate.
 *
 */
inline void operator delete[] (void* p)
{
  /* Catch usage when debugging */
  UASDK_ASSERT(false);
}
#endif

#endif // _IALLOCATOR_T_
