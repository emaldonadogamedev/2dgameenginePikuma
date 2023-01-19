#include "Logger.h"

#include <iostream>

void Logger::Log(const std::string& message)
{
    const auto formattedLocalTimeNow = GetFormattedLocalTimeNow();

    const std::string outputMessage = 
        "LOG: [" + formattedLocalTimeNow + "]: " + message;

    LogEntry newLogEntry(LogEntryType::LOG_INFO, outputMessage);

    std::cout << LOG_COLOR_OUTPUT_FORMAT_GREEN << newLogEntry.logMessage << "\033[0m" << std::endl;

    m_logEntries.push_back(newLogEntry);
}

void Logger::Error(const std::string& errorMessage)
{
    const auto formattedLocalTimeNow = GetFormattedLocalTimeNow();

    const std::string outputMessage =
        "ERROR: [" + formattedLocalTimeNow + "]: " + errorMessage;

    LogEntry newLogEntry(LogEntryType::LOG_ERROR, outputMessage);

    std::cerr << ERROR_COLOR_OUTPUT_FORMAT_RED << newLogEntry.logMessage << "\033[0m" << std::endl;

    m_logEntries.push_back(newLogEntry);
}

const std::string Logger::GetFormattedLocalTimeNow()
{
    const std::tm localTimeNow = GetLocalTimeNow();

    std::string formattedLocalTimeNow(30, '\0');

    std::strftime(
        &formattedLocalTimeNow[0],
        formattedLocalTimeNow.size(),
        "%d-%b-%Y %H:%M:%S",
        &localTimeNow);

    return formattedLocalTimeNow;
}

const std::tm Logger::GetLocalTimeNow()
{
    const auto systemClockNow = std::chrono::system_clock::now();
    const std::time_t systemClockNowTime_t = 
        std::chrono::system_clock::to_time_t(systemClockNow);

    struct tm localTimeTM;
    localtime_s(&localTimeTM, &systemClockNowTime_t);

    return localTimeTM;
}

std::string CurrentDateTimeToString()
{
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    std::string output(30, '\0');

    struct tm newtime;

    localtime_s(&newtime, &now);

    std::strftime(&output[0], output.size(), "%d-%b-%Y %H:%M:%S", &newtime);

    return output;
}

std::vector<LogEntry> Logger::m_logEntries = std::vector<LogEntry>();
const std::string Logger::LOG_COLOR_OUTPUT_FORMAT_GREEN = "\x1B[32m";
const std::string Logger::ERROR_COLOR_OUTPUT_FORMAT_RED = "\x1B[91m";