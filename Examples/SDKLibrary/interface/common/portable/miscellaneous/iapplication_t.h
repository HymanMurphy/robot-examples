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

#ifndef _IAPPLICATION_T_
#define _IAPPLICATION_T_

#include "uasdk_includes.h"
#include "iref_count_t.h"

namespace uasdk
{

/** \addtogroup grpMiscellaneous
 *@{*/

class IApplication_t : public IRefCount_t
{
public:
  virtual ~IApplication_t() {};

  virtual Status_t Poll(void) = 0;
};

/** @} */

}

#endif // _IAPPLICATION_T_
