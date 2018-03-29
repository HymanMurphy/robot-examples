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

#ifndef _ITIMER_COMPLETE_HANDLER_T_
#define _ITIMER_COMPLETE_HANDLER_T_

#include "uasdk_includes.h"

#if ((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

namespace uasdk
{

class ITimerCompleteHandler_t
{
public:

  virtual ~ITimerCompleteHandler_t() {} 

	/*****************************************************************************/
	/** TimerCompleteCallback()
	*  To notify if the timer is completed
	*
	* @return
	*/
	virtual void TimerCompleteCallback(void) = 0;

};

/** @} */

}

#endif //((UASDK_INCLUDE_EVENTS > 0) && (UASDK_INCLUDE_ALARMS_AND_CONDITIONS > 0))

#endif // _ITIMER_COMPLETE_HANDLER_T_
