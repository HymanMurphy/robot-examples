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

#ifndef _ILOG_LISTENER_T_
#define _ILOG_LISTENER_T_

#include <stdarg.h>
#include "iref_count_t.h"

namespace uasdk
{

/** \addtogroup grpMiscellaneous
 *@{*/

class ILogListener_t : public IRefCount_t
{
public:
  typedef enum
  {
    LOG_LEVEL_INFORMATION = 0,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_CRITICAL,
    LOG_LEVEL_END
  } LogLevel_t;

  virtual ~ILogListener_t() {}

  /*****************************************************************************/
  /** This function is used to Log the Message..
   *
   * @param[in] logLevel
   * Log level type.
   *
   *  @param[in] message
   *  message to be logged
   */
  virtual void LogMessage(LogLevel_t logLevel, const char* format, va_list& args) const = 0;

  virtual void LogMessage(LogLevel_t logLevel, const char* functionName, int lineNumber, const char* format, va_list& args) const = 0;
};

/** @} */

} // namespace uasdk

#endif // _ILOG_LISTENER_T_
