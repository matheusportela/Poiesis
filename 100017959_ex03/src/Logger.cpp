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

void Logger::Print(LogLevel level, const char* format, ...)
{
    if (level < this->level)
        return;

    va_list args;
    
    fprintf(stderr, "LOG: ");
    
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fprintf(stderr, "\n");
}