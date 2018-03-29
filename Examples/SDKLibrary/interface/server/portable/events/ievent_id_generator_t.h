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

#ifndef _IEVENT_ID_GENERATOR_T_
#define _IEVENT_ID_GENERATOR_T_

#include "opcua_bytestring_t.h"

#if (UASDK_INCLUDE_EVENTS > 0)

#include "iref_count_t.h"
#include "intrusive_ptr_t.h"

namespace uasdk
{
/** \addtogroup grpEventsandAC
*@{*/

/*****************************************************************************/
/** \brief Event Id generator
*
* A class that is used to generate a unique event Id
*
*/
class IEventIdGenerator_t : public IRefCount_t
{
public:
  virtual ~IEventIdGenerator_t() {}

  /*****************************************************************************/
  /** Generate a unique event Id
   *
   *  @param[out] eventId
   *  The generated event Id.
   *
   * @return
   * The status of the operation
   */
  virtual Status_t GenerateEventId(IntrusivePtr_t<ByteString_t>& eventId) = 0;
};

/** @} */

}

#endif //UASDK_INCLUDE_EVENTS

#endif // _IEVENT_ID_GENERATOR_T_
