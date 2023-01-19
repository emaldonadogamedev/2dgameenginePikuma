#include "Logger.h"

#include <iostream>
#include <chrono>
#include <sstream>

void Logger::Log(const std::string& message)
{
    const std::tm* localTimeNow = GetLocalTimeNow();

    std::stringstream streamToConstructMessage;

    streamToConstructMessage << "LOG | " << localTimeNow->tm_mday << "-" << localTimeNow->tm_mon 
        << "-" << localTimeNow->tm_year << " " << localTimeNow->tm_hour << ":" << localTimeNow->tm_min
        << localTimeNow->tm_sec << " - " << message;
    // LOG | 12-OCT-2020 9:34:11 - [MESSAGE]
    // IN GREEN
    std::cout << message;
}

void Logger::Error(const std::string& errorMessage)
{
    // ERROR | 12-OCT-2020 9:34:11 - [MESSAGE]
    // IN RED
    std::cerr << errorMessage;
}

const std::tm* GetLocalTimeNow()
{
    const auto systemClockNow = std::chrono::system_clock::now();
    const std::time_t endTime = std::chrono::system_clock::to_time_t(systemClockNow);
    const std::tm* const localTimeNow = std::localtime(&endTime);

    return localTimeNow;
}