// @file   Log.h
// @author Matheus Vieira Portela
// @date   20/04/2015
//
// @brief Logger class definition.

#ifndef LOGGER_H_
#define LOGGER_H_

#include <cstdio>
#include <cstdarg>

class Logger
{
  public:
    // Possible log levels to filter which log message will be displayed.
    enum LogLevel
    {
        Debug,
        Info,
        Warning,
        Error,
    };

    // Gets config instance as in the singleton pattern.
    static Logger& GetInstance();

    // Getters and setters.
    void SetLevel(LogLevel level);

    // Print message with a log level.
    void Print(LogLevel level, const char* format, ...);

  private:
    // Singleton pattern using the approach suggested at
    // http://stackoverflow.com/questions/1008019/c-singleton-design-pattern
    Logger();
    Logger(Logger const &) = delete;
    void operator=(Logger const &) = delete;

    // Current log level.
    LogLevel level;
};

#endif // LOGGER_H_