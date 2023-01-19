#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <chrono>

class Logger
{
    public:
        static void Log(const std::string& message);
        static void Error(const std::string& errorMessage);

    private:
        static const std::tm* GetLocalTimeNow();
};

#endif