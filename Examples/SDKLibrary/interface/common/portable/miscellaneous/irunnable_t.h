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

#ifndef _IRUNNABLE_T_
#define _IRUNNABLE_T_

#include "iintrusive_embedded_queue_support_t.h"
#include "iref_count_t.h"

namespace uasdk
{
/** \addtogroup grpMiscellaneous
 *@{*/

class IRunnable_t : public IRefCount_t, public IIntrusiveEmbeddedQueueSupport_t<IRunnable_t>
{
public:
  virtual ~IRunnable_t() {}

  /*****************************************************************************/
  /** This function used to Run the server.
   *
   */
  virtual void Run(void) = 0;
};

/** @} */
}

#endif // _IRUNNABLE_T_
