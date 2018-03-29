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

#include "uasdk_includes.h"
#include "logger_t.h"
#include "intrusive_ptr_t.h"

#if (UASDK_DEBUG > 0)

#include <cstdarg>

namespace uasdk
{

  ILogListener_t* Logger_t::listener;

  void Logger_t::Initialise(ILogListener_t& listener_)
  {
    listener = &listener_;
  }

  void Logger_t::Shutdown(void)
  {
    listener = 0;
  }

  void Logger_t::LogMessage(ILogListener_t::LogLevel_t logLevel, const char* format, ...)
  {
    va_list args;
    va_start(args, format);

    if (listener)
    {
      listener->LogMessage(logLevel, format, args);
    }

    va_end(args);
  }


  void Logger_t::LogMessage(ILogListener_t::LogLevel_t logLevel, const char* functionName, int lineNumber, const char* format, ...)
  {
    va_list args;
    va_start(args, format);

    if (listener)
    {
      listener->LogMessage(logLevel, functionName, lineNumber, format, args);
    }

    va_end(args);
  }

} // namespace uasdk

#endif // UASDK_DEBUG > 0
