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

#ifndef _IINTRUSIVE_EMBEDDED_QUEUE_SUPPORT_T_
#define _IINTRUSIVE_EMBEDDED_QUEUE_SUPPORT_T_

#include "intrusive_ptr_t.h"

namespace uasdk
{
/** \addtogroup grpMiscellaneous
 *@{*/

/*****************************************************************************/
/** \brief IntrusiveEmbeddedQueue_t
 *
 * This class provides an abstract interface to the
 * intrusive embedded queue support utilities
 */
template<class T>
class IIntrusiveEmbeddedQueueSupport_t
{
public:

  /*****************************************************************************/
  /** Destructor of the class
   */
  virtual ~IIntrusiveEmbeddedQueueSupport_t() {}

  /*****************************************************************************/
  /** Get the next element from the queue
   *
   * @return
   * Reference to the Intrusive Pointer object fetched from the queue
   */
  virtual IntrusivePtr_t<T>& Next(void) = 0;

  /*****************************************************************************/
  /** Get the next element from the queue
   *
   * @param[out] IntrusivePtr_t<T>& val
   * Reference to the Intrusive Pointer object fetched from the queue
   */
  virtual void Next(IntrusivePtr_t<T>& val) = 0;
};

/** @} */

}
#endif // _IINTRUSIVE_EMBEDDED_QUEUE_SUPPORT_T_
