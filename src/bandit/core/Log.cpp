#include "bandit/core/Log.h"

Log::LogLevel Log::level = Log::Info;

void Log::SetLevel(LogLevel level)
{
    Log::level = level;
}

std::ostream& Log::GetStream()
{
    return std::cerr;
};

std::string Log::GetLevelString(LogLevel level)
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

    std::cerr << "ERROR [Log] Log level \"" << level << "\" undefined."
              << std::endl;
    exit(1);
}

std::string Log::GetLevelColor(LogLevel level)
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

    std::cerr << "ERROR [Log] Log level \"" << level << "\" undefined."
              << std::endl;
    exit(1);
}

std::string Log::GetPrefix(LogLevel level)
{
    return GetLevelColor(level) + GetLevelString(level) + ": ";
}

std::string Log::GetSufix()
{
    return "\e[0;0m\n";
}