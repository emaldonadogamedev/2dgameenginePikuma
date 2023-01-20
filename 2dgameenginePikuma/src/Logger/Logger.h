#ifndef LOGGER_H
#define LOGGER_H

#include <vector>
#include <string>
#include <chrono>

enum class LogEntryType : unsigned char
{
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR
};

struct LogEntry
{
    LogEntry(
        LogEntryType logEntryType = LogEntryType::LOG_INFO,
        std::string logMessage = ""):
        logEntryType(logEntryType),
        logMessage(logMessage)
    {
    }

    LogEntryType logEntryType;
    std::string logMessage;
};

class Logger
{
    public:
        static void Log(const std::string& message);
        static void Error(const std::string& errorMessage);

    private:
        static const std::string GetFormattedLocalTimeNow();
        static const std::tm GetLocalTimeNow();

        static std::vector<LogEntry> m_logEntries;

        static const std::string LOG_COLOR_OUTPUT_FORMAT_GREEN;
        static const std::string ERROR_COLOR_OUTPUT_FORMAT_RED;
};

#endif