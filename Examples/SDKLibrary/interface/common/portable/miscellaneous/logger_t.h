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

#ifndef _LOGGER_T_
#define _LOGGER_T_

/** \addtogroup grpMiscellaneous
 *@{*/

#include "uasdk_includes.h"

#if (UASDK_DEBUG != 0)

#include "ilog_listener_t.h"

namespace uasdk
{

class Logger_t
{
private:
  static ILogListener_t* listener;

public:
  static void Initialise(ILogListener_t& listener);

  static void Shutdown(void);

  static void LogMessage(ILogListener_t::LogLevel_t logLevel, const char* format, ...);

  static void LogMessage(ILogListener_t::LogLevel_t logLevel, const char* functionName, int lineNumber, const char* format, ...);
};

} // namespace uasdk

#endif //(UASDK_DEBUG != 0)

#if defined(_WIN32) && (UASDK_DEBUG != 0)

#define LOG_MESSAGE(logLevel, format, ...) Logger_t::LogMessage(logLevel, format, __VA_ARGS__)

#define LOG_MESSAGE_WITH_LOCATION(logLevel, format, ...) Logger_t::LogMessage(logLevel, __FUNCTION__, __LINE__, format, __VA_ARGS__)

#define LOG_INFO(format, ...) LOG_MESSAGE(ILogListener_t::LOG_LEVEL_INFORMATION, format, __VA_ARGS__)

#define LOG_WARNING(format, ...) LOG_MESSAGE(ILogListener_t::LOG_LEVEL_WARNING, format, __VA_ARGS__)

#define LOG_ERROR(format, ...) LOG_MESSAGE(ILogListener_t::LOG_LEVEL_ERROR, format, __VA_ARGS__)

#define LOG_CRITICAL(format, ...) LOG_MESSAGE(ILogListener_t::LOG_LEVEL_CRITICAL, format, __VA_ARGS__)

#define LOG_INFO_WITH_LOCATION(format, ...) LOG_MESSAGE_WITH_LOCATION(ILogListener_t::LOG_LEVEL_INFORMATION, format, __VA_ARGS__)

#define LOG_WARNING_WITH_LOCATION(format, ...) LOG_MESSAGE_WITH_LOCATION(ILogListener_t::LOG_LEVEL_WARNING, format, __VA_ARGS__)

#define LOG_ERROR_WITH_LOCATION(format, ...) LOG_MESSAGE_WITH_LOCATION(ILogListener_t::LOG_LEVEL_ERROR, format, __VA_ARGS__)

#define LOG_CRITICAL_WITH_LOCATION(format, ...) LOG_MESSAGE_WITH_LOCATION(ILogListener_t::LOG_LEVEL_CRITICAL, format, __VA_ARGS__)

#define LOG_BAD_STATUS(status) LOG_MESSAGE_WITH_LOCATION(ILogListener_t::LOG_LEVEL_WARNING, "Bad status of %#08lx encountered", (unsigned long)status)

#define LOG_UNEXPECTED_ERROR LOG_MESSAGE_WITH_LOCATION(ILogListener_t::LOG_LEVEL_WARNING, "An unexpected error encountered")

#elif defined(__GNUC__) && (UASDK_DEBUG != 0)

#define LOG_MESSAGE(logLevel, format, ...) Logger_t::LogMessage(logLevel, format, ##__VA_ARGS__)

#define LOG_MESSAGE_WITH_LOCATION(logLevel, format, ...) Logger_t::LogMessage(logLevel, __FUNCTION__, __LINE__, format, ##__VA_ARGS__)

#define LOG_INFO(format, ...) LOG_MESSAGE(ILogListener_t::LOG_LEVEL_INFORMATION, format, ##__VA_ARGS__)

#define LOG_WARNING(format, ...) LOG_MESSAGE(ILogListener_t::LOG_LEVEL_WARNING, format, ##__VA_ARGS__)

#define LOG_ERROR(format, ...) LOG_MESSAGE(ILogListener_t::LOG_LEVEL_ERROR, format, ##__VA_ARGS__)

#define LOG_CRITICAL(format, ...) LOG_MESSAGE(ILogListener_t::LOG_LEVEL_CRITICAL, format, ##__VA_ARGS__)

#define LOG_INFO_WITH_LOCATION(format, ...) LOG_MESSAGE_WITH_LOCATION(ILogListener_t::LOG_LEVEL_INFORMATION, format, ##__VA_ARGS__)

#define LOG_WARNING_WITH_LOCATION(format, ...) LOG_MESSAGE_WITH_LOCATION(ILogListener_t::LOG_LEVEL_WARNING, format, ##__VA_ARGS__)

#define LOG_ERROR_WITH_LOCATION(format, ...) LOG_MESSAGE_WITH_LOCATION(ILogListener_t::LOG_LEVEL_ERROR, format, ##__VA_ARGS__)

#define LOG_CRITICAL_WITH_LOCATION(format, ...) LOG_MESSAGE_WITH_LOCATION(ILogListener_t::LOG_LEVEL_CRITICAL, format, ##__VA_ARGS__)

#define LOG_BAD_STATUS(status) LOG_MESSAGE_WITH_LOCATION(ILogListener_t::LOG_LEVEL_WARNING, "Bad status of %#08lx encountered", (unsigned long)status)

#define LOG_UNEXPECTED_ERROR LOG_MESSAGE_WITH_LOCATION(ILogListener_t::LOG_LEVEL_WARNING, "An unexpected error encountered")

#else

#define LOG_MESSAGE(logLevel, format, ...)
#define LOG_INFO(format, ...)
#define LOG_WARNING(format, ...)
#define LOG_ERROR(format, ...)
#define LOG_CRITICAL(format, ...)

#define LOG_MESSAGE_WITH_LOCATION(logLevel, format, ...)
#define LOG_INFO_WITH_LOCATION(format, ...)
#define LOG_WARNING_WITH_LOCATION(format, ...)
#define LOG_ERROR_WITH_LOCATION(format, ...)
#define LOG_CRITICAL_WITH_LOCATION(format, ...)

#define LOG_BAD_STATUS(status)

#define LOG_UNEXPECTED_ERROR

#endif

#if defined(_WIN32) && (UASDK_DEBUG_SESSIONS > 0)

#define SESSION_LOG_INFO(format, ...) LOG_INFO(format, __VA_ARGS__)
#define SESSION_LOG_WARNING(format, ...) LOG_WARNING(format, __VA_ARGS__)
#define SESSION_LOG_ERROR(format, ...) LOG_ERROR(format, __VA_ARGS__)
#define SESSION_LOG_CRITICAL(format, ...) LOG_CRITICAL(format, __VA_ARGS__)

#elif defined(__GNUC__) && (UASDK_DEBUG_SESSIONS > 0)

#define SESSION_LOG_INFO(format, ...) LOG_INFO(format, ##__VA_ARGS__)
#define SESSION_LOG_WARNING(format, ...) LOG_WARNING(format, ##__VA_ARGS__)
#define SESSION_LOG_ERROR(format, ...) LOG_ERROR(format, ##__VA_ARGS__)
#define SESSION_LOG_CRITICAL(format, ...) LOG_CRITICAL(format, ##__VA_ARGS__)

#else

#define SESSION_LOG_INFO(format, ...)
#define SESSION_LOG_WARNING(format, ...)
#define SESSION_LOG_ERROR(format, ...)
#define SESSION_LOG_CRITICAL(format, ...)

#endif

#if defined(_WIN32) && (UASDK_DEBUG_CONNECTIONS > 0)

#define CONNECTION_LOG_INFO(format, ...) LOG_INFO(format, __VA_ARGS__)
#define CONNECTION_LOG_WARNING(format, ...) LOG_WARNING(format, __VA_ARGS__)
#define CONNECTION_LOG_ERROR(format, ...) LOG_ERROR(format, __VA_ARGS__)
#define CONNECTION_LOG_CRITICAL(format, ...) LOG_CRITICAL(format, __VA_ARGS__)

#elif defined(__GNUC__) && (UASDK_DEBUG_CONNECTIONS > 0)

#define CONNECTION_LOG_INFO(format, ...) LOG_INFO(format, ##__VA_ARGS__)
#define CONNECTION_LOG_WARNING(format, ...) LOG_WARNING(format, ##__VA_ARGS__)
#define CONNECTION_LOG_ERROR(format, ...) LOG_ERROR(format, ##__VA_ARGS__)
#define CONNECTION_LOG_CRITICAL(format, ...) LOG_CRITICAL(format, ##__VA_ARGS__)

#else

#define CONNECTION_LOG_INFO(format, ...)
#define CONNECTION_LOG_WARNING(format, ...)
#define CONNECTION_LOG_ERROR(format, ...)
#define CONNECTION_LOG_CRITICAL(format, ...)

#endif

#if defined(_WIN32) && (UASDK_DEBUG_CHANNELS > 0)

#define CHANNEL_LOG_INFO(format, ...) LOG_INFO(format, __VA_ARGS__)
#define CHANNEL_LOG_WARNING(format, ...) LOG_WARNING(format, __VA_ARGS__)
#define CHANNEL_LOG_ERROR(format, ...) LOG_ERROR(format, __VA_ARGS__)
#define CHANNEL_LOG_CRITICAL(format, ...) LOG_CRITICAL(format, __VA_ARGS__)

#elif defined(__GNUC__) && (UASDK_DEBUG_CHANNELS > 0)

#define CHANNEL_LOG_INFO(format, ...) LOG_INFO(format, ##__VA_ARGS__)
#define CHANNEL_LOG_WARNING(format, ...) LOG_WARNING(format, ##__VA_ARGS__)
#define CHANNEL_LOG_ERROR(format, ...) LOG_ERROR(format, ##__VA_ARGS__)
#define CHANNEL_LOG_CRITICAL(format, ...) LOG_CRITICAL(format, ##__VA_ARGS__)

#else

#define CHANNEL_LOG_INFO(format, ...)
#define CHANNEL_LOG_WARNING(format, ...)
#define CHANNEL_LOG_ERROR(format, ...)
#define CHANNEL_LOG_CRITICAL(format, ...)

#endif

#if defined(_WIN32) && (UASDK_DEBUG_MEMORY > 0)

#define MEMORY_LOG_INFO(format, ...) LOG_INFO(format, __VA_ARGS__)
#define MEMORY_LOG_WARNING(format, ...) LOG_WARNING(format, __VA_ARGS__)
#define MEMORY_LOG_ERROR(format, ...) LOG_ERROR(format, __VA_ARGS__)
#define MEMORY_LOG_CRITICAL(format, ...) LOG_CRITICAL(format, __VA_ARGS__)

#elif defined(__GNUC__) && (UASDK_DEBUG_MEMORY > 0)

#define MEMORY_LOG_INFO(format, ...) LOG_INFO(format, ##__VA_ARGS__)
#define MEMORY_LOG_WARNING(format, ...) LOG_WARNING(format, ##__VA_ARGS__)
#define MEMORY_LOG_ERROR(format, ...) LOG_ERROR(format, ##__VA_ARGS__)
#define MEMORY_LOG_CRITICAL(format, ...) LOG_CRITICAL(format, ##__VA_ARGS__)

#else

#define MEMORY_LOG_INFO(format, ...)
#define MEMORY_LOG_WARNING(format, ...)
#define MEMORY_LOG_ERROR(format, ...)
#define MEMORY_LOG_CRITICAL(format, ...)

#endif

#if defined(_WIN32) && (UASDK_DEBUG_SUBSCRIPTIONS > 0)

#define SUBSCRIPTION_LOG_INFO(format, ...) LOG_INFO(format, __VA_ARGS__)
#define SUBSCRIPTION_LOG_WARNING(format, ...) LOG_WARNING(format, __VA_ARGS__)
#define SUBSCRIPTION_LOG_ERROR(format, ...) LOG_ERROR(format, __VA_ARGS__)
#define SUBSCRIPTION_LOG_CRITICAL(format, ...) LOG_CRITICAL(format, __VA_ARGS__)

#elif defined(__GNUC__) && (UASDK_DEBUG_SUBSCRIPTIONS > 0)

#define SUBSCRIPTION_LOG_INFO(format, ...) LOG_INFO(format, ##__VA_ARGS__)
#define SUBSCRIPTION_LOG_WARNING(format, ...) LOG_WARNING(format, ##__VA_ARGS__)
#define SUBSCRIPTION_LOG_ERROR(format, ...) LOG_ERROR(format, ##__VA_ARGS__)
#define SUBSCRIPTION_LOG_CRITICAL(format, ...) LOG_CRITICAL(format, ##__VA_ARGS__)

#else

#define SUBSCRIPTION_LOG_INFO(format, ...)
#define SUBSCRIPTION_LOG_WARNING(format, ...)
#define SUBSCRIPTION_LOG_ERROR(format, ...)
#define SUBSCRIPTION_LOG_CRITICAL(format, ...)

#endif

#if defined(_WIN32) && (UASDK_DEBUG_MESSAGES > 0)

#define MESSAGE_LOG_INFO(format, ...) LOG_INFO(format, __VA_ARGS__)
#define MESSAGE_LOG_WARNING(format, ...) LOG_WARNING(format, __VA_ARGS__)
#define MESSAGE_LOG_ERROR(format, ...) LOG_ERROR(format, __VA_ARGS__)
#define MESSAGE_LOG_CRITICAL(format, ...) LOG_CRITICAL(format, __VA_ARGS__)

#elif defined(__GNUC__) && (UASDK_DEBUG_MESSAGES > 0)

#define MESSAGE_LOG_INFO(format, ...) LOG_INFO(format, ##__VA_ARGS__)
#define MESSAGE_LOG_WARNING(format, ...) LOG_WARNING(format, ##__VA_ARGS__)
#define MESSAGE_LOG_ERROR(format, ...) LOG_ERROR(format, ##__VA_ARGS__)
#define MESSAGE_LOG_CRITICAL(format, ...) LOG_CRITICAL(format, ##__VA_ARGS__)

#else

#define MESSAGE_LOG_INFO(format, ...)
#define MESSAGE_LOG_WARNING(format, ...)
#define MESSAGE_LOG_ERROR(format, ...)
#define MESSAGE_LOG_CRITICAL(format, ...)

#endif




/** @} */

#endif // _LOGGER_T_
