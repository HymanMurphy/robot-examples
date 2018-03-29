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

#ifndef _READ_ONLY_NODES_
#define _READ_ONLY_NODES_

#include "uasdk_includes.h"

namespace uasdk
{

  class ReadOnlyNodes_t
  {
  public:
    static const uint32_t EMBEDDED_PROFILE_STANDARD_NODES_LENGTH;
	static const uint8_t EMBEDDED_PROFILE_STANDARD_NODES[];

    static const uint32_t NANO_AND_MICRO_PROFILE_STANDARD_NODES_LENGTH;
	static const uint8_t NANO_AND_MICRO_PROFILE_STANDARD_NODES[];
  };

}

#endif // _READ_ONLY_NODES_
