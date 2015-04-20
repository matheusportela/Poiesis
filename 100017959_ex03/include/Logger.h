// @file   Log.h
// @author Matheus Vieira Portela
// @date   20/04/2015
//
// @brief Logger class definition.

#ifndef LOGGER_H_
#define LOGGER_H_

#include <cstdio>
#include <cstdarg>
#include <iostream>
#include <string>

#define LOG_SET_DEBUG() Logger::GetInstance().SetLevel(Logger::Debug);
#define LOG_SET_INFO() Logger::GetInstance().SetLevel(Logger::Info);
#define LOG_SET_WARNING() Logger::GetInstance().SetLevel(Logger::Warning);
#define LOG_SET_ERROR() Logger::GetInstance().SetLevel(Logger::Error);
#define LOGD(args...) Logger::GetInstance().Print(Logger::Debug, args);
#define LOGI(args...) Logger::GetInstance().Print(Logger::Info, args);
#define LOGW(args...) Logger::GetInstance().Print(Logger::Warning, args);
#define LOGE(args...) Logger::GetInstance().Print(Logger::Error, args);

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

    // Maps log levels to strings for printing purposes.
    std::string GetLevelString(LogLevel level);

    // Maps log levels to colors for printing purposes.
    std::string GetLevelColor(LogLevel level);

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