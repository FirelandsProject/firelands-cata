/*
 * This file is part of the FirelandsCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _FIRELANDS_LOG_H
#define _FIRELANDS_LOG_H

#include "Define.h"
#include "AsioHacksFwd.h"
#include "LogCommon.h"
#include "StringFormat.h"
#include <memory>
#include <unordered_map>
#include <vector>

class Appender;
class Logger;
struct LogMessage;

namespace Firelands
{
    namespace Asio
    {
        class IoContext;
    }
}

#define LOGGER_ROOT "root"

typedef Appender*(*AppenderCreatorFn)(uint8 id, std::string const& name, LogLevel level, AppenderFlags flags, std::vector<char const*>&& extraArgs);

template <class AppenderImpl>
Appender* CreateAppender(uint8 id, std::string const& name, LogLevel level, AppenderFlags flags, std::vector<char const*>&& extraArgs)
{
    return new AppenderImpl(id, name, level, flags, std::forward<std::vector<char const*>>(extraArgs));
}

class FC_COMMON_API Log
{
    typedef std::unordered_map<std::string, Logger> LoggerMap;

    private:
        Log();
        ~Log();
        Log(Log const&) = delete;
        Log(Log&&) = delete;
        Log& operator=(Log const&) = delete;
        Log& operator=(Log&&) = delete;

    public:
        static Log* instance();

        void Initialize(Firelands::Asio::IoContext* ioContext);
        void SetSynchronous();  // Not threadsafe - should only be called from main() after all threads are joined
        void LoadFromConfig();
        void Close();
        bool ShouldLog(std::string const& type, LogLevel level) const;
        bool SetLogLevel(std::string const& name, char const* level, bool isLogger = true);

        template<typename Format, typename... Args>
        inline void outMessage(std::string const& filter, LogLevel const level, Format&& fmt, Args&&... args)
        {
            outMessage(filter, level, Firelands::StringFormat(std::forward<Format>(fmt), std::forward<Args>(args)...));
        }

        template<typename Format, typename... Args>
        void outCommand(uint32 account, Format&& fmt, Args&&... args)
        {
            if (!ShouldLog("commands.gm", LOG_LEVEL_INFO))
                return;

            outCommand(Firelands::StringFormat(std::forward<Format>(fmt), std::forward<Args>(args)...), std::to_string(account));
        }

        void outCharDump(char const* str, uint32 account_id, uint64 guid, char const* name);

        void SetRealmId(uint32 id);

        template <class AppenderImpl>
        void RegisterAppender()
        {
            using Index = typename AppenderImpl::TypeIndex;
            RegisterAppender(Index::value, &CreateAppender<AppenderImpl>);
        }

        std::string const& GetLogsDir() const { return m_logsDir; }
        std::string const& GetLogsTimestamp() const { return m_logsTimestamp; }

    private:
        static std::string GetTimestampStr();
        void write(std::unique_ptr<LogMessage>&& msg) const;

        Logger const* GetLoggerByType(std::string const& type) const;
        Appender* GetAppenderByName(std::string const& name);
        uint8 NextAppenderId();
        void CreateAppenderFromConfig(std::string const& name);
        void CreateLoggerFromConfig(std::string const& name);
        void ReadAppendersFromConfig();
        void ReadLoggersFromConfig();
        void RegisterAppender(uint8 index, AppenderCreatorFn appenderCreateFn);
        void outMessage(std::string const& filter, LogLevel const level, std::string&& message);
        void outCommand(std::string&& message, std::string&& param1);

        std::unordered_map<uint8, AppenderCreatorFn> appenderFactory;
        std::unordered_map<uint8, std::unique_ptr<Appender>> appenders;
        std::unordered_map<std::string, std::unique_ptr<Logger>> loggers;
        uint8 AppenderId;
        LogLevel lowestLogLevel;

        std::string m_logsDir;
        std::string m_logsTimestamp;

        Firelands::Asio::IoContext* _ioContext;
        Firelands::Asio::Strand* _strand;
};

#define sLog Log::instance()

#define LOG_EXCEPTION_FREE(filterType__, level__, ...) \
    { \
        try \
        { \
            sLog->outMessage(filterType__, level__, __VA_ARGS__); \
        } \
        catch (std::exception& e) \
        { \
            sLog->outMessage("server", LOG_LEVEL_ERROR, "Wrong format occurred (%s) at %s:%u.", \
                e.what(), __FILE__, __LINE__); \
        } \
    }

#ifdef PERFORMANCE_PROFILING
#define LOG_MESSAGE_BODY(filterType__, level__, ...) ((void)0)
#elif FC_PLATFORM != FC_PLATFORM_WINDOWS
void check_args(char const*, ...) ATTR_PRINTF(1, 2);
void check_args(std::string const&, ...);

// This will catch format errors on build time
#define LOG_MESSAGE_BODY(filterType__, level__, ...)                 \
        do {                                                            \
            if (sLog->ShouldLog(filterType__, level__))                 \
            {                                                           \
                if (false)                                              \
                    check_args(__VA_ARGS__);                            \
                                                                        \
                LOG_EXCEPTION_FREE(filterType__, level__, __VA_ARGS__); \
            }                                                           \
        } while (0)
#else
#define LOG_MESSAGE_BODY(filterType__, level__, ...)                 \
        __pragma(warning(push))                                         \
        __pragma(warning(disable:4127))                                 \
        do {                                                            \
            if (sLog->ShouldLog(filterType__, level__))                 \
                LOG_EXCEPTION_FREE(filterType__, level__, __VA_ARGS__); \
        } while (0)                                                     \
        __pragma(warning(pop))
#endif

#define LOG_TRACE(filterType__, ...) \
    LOG_MESSAGE_BODY(filterType__, LOG_LEVEL_TRACE, __VA_ARGS__)

#define LOG_DEBUG(filterType__, ...) \
    LOG_MESSAGE_BODY(filterType__, LOG_LEVEL_DEBUG, __VA_ARGS__)

#define LOG_INFO(filterType__, ...)  \
    LOG_MESSAGE_BODY(filterType__, LOG_LEVEL_INFO, __VA_ARGS__)

#define LOG_WARN(filterType__, ...)  \
    LOG_MESSAGE_BODY(filterType__, LOG_LEVEL_WARN, __VA_ARGS__)

#define LOG_ERROR(filterType__, ...) \
    LOG_MESSAGE_BODY(filterType__, LOG_LEVEL_ERROR, __VA_ARGS__)

#define LOG_FATAL(filterType__, ...) \
    LOG_MESSAGE_BODY(filterType__, LOG_LEVEL_FATAL, __VA_ARGS__)

#endif
