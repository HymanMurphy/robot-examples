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

#ifndef _IOPERATION_COMPLETE_LISTENER_T_
#define _IOPERATION_COMPLETE_LISTENER_T_

#include "uasdk_includes.h"
#include "iref_count_t.h"

namespace uasdk
{

/** \addtogroup grpMiscellaneous
 *@{*/

class IOperationCompleteListener_t : public IRefCount_t
{
public:
  virtual ~IOperationCompleteListener_t() {};

  /*****************************************************************************/
  /** This function can be used to necessary action on completion of certain operation.
   *
   * @param[in] result
   * Status of the operation
   *
   */
  virtual void OperationComplete(Status_t result) = 0;
};

/** @} */

}

#endif // _IOPERATION_COMPLETE_LISTENER_T_
