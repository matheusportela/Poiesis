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
            return "\e[1;1m"; // standard
        case Warning:
            return "\e[1;33m"; // yellow
        case Error:
            return "\e[1;31m"; // red
    }

    std::cerr << "ERROR [Logger] Log level \"" << level << "\" undefined."
              << std::endl;
    exit(1);
}

void Logger::Print(LogLevel level, const char* format, ...)
{
    if (level < this->level)
        return;

    va_list args;
    std::string level_color = GetLevelColor(level);
    std::string level_string = GetLevelString(level);

    fprintf(stderr, "%s%s: ", level_color.c_str(), level_string.c_str());
    
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fprintf(stderr, "\e[0;0m\n");
}