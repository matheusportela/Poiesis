// @file   Log.cpp
// @author Matheus Vieira Portela
// @date   20/04/2015
//
// @brief Logger class implementation.

#include "Logger.h"

Logger::Logger() : level(Info)
{
}

Logger& Logger::GetInstance()
{
    // Singleton pattern using the approach suggested at
    // http://stackoverflow.com/questions/1008019/c-singleton-design-pattern
    static Logger instance;
    return instance;
};

Logger::LogLevel Logger::GetLevel()
{
    return level;
}

void Logger::SetLevel(LogLevel level)
{
    this->level = level;
}

std::string Logger::GetLevelString(LogLevel level)
{
    switch (level)
    {
        case Debug:
            return "D";
        case Info:
            return "I";
        case Warning:
            return "W";
        case Error:
            return "E";
    }

    std::cerr << "ERROR [Logger] Log level \"" << level << "\" undefined."
              << std::endl;
    exit(1);
}

std::string Logger::GetLevelColor(LogLevel level)
{
    switch (level)
    {
        case Debug:
            return "\e[1;35m"; // purple
        case Info:
            return "\e[1;1m"; // white
        case Warning:
            return "\e[1;33m"; // yellow
        case Error:
            return "\e[1;31m"; // red
    }

    std::cerr << "ERROR [Logger] Log level \"" << level << "\" undefined."
              << std::endl;
    exit(1);
}

std::string Logger::GetPrefix(LogLevel level)
{
    return GetLevelColor(level) + GetLevelString(level) + ": ";
}

std::string Logger::GetSufix()
{
    return "\e[0;0m\n";
}