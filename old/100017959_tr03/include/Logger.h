// @file   Log.h
// @author Matheus Vieira Portela
// @date   20/04/2015
//
// @brief Logger class definition.

#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <string>

// Configures to display logs with level higher or equal to the given one.
#define LOG_SET_DEBUG() Logger::GetInstance().SetLevel(Logger::Debug);
#define LOG_SET_INFO() Logger::GetInstance().SetLevel(Logger::Info);
#define LOG_SET_WARNING() Logger::GetInstance().SetLevel(Logger::Warning);
#define LOG_SET_ERROR() Logger::GetInstance().SetLevel(Logger::Error);

// Outputs a log message if it's level is high enough.
#define LOG(level, message) \
    do { \
        if (level >= Logger::GetInstance().GetLevel()) { \
            Logger::GetInstance().GetStream() \
            << Logger::GetInstance().GetPrefix(level) \
            << message \
            << Logger::GetInstance().GetSufix(); \
        } \
    } while (false)

// Outputs debug log message.
#define LOG_D(message) LOG(Logger::Debug, message)

// Outputs informational log message.
#define LOG_I(message) LOG(Logger::Info, message)

// Outputs warning log message.
#define LOG_W(message) LOG(Logger::Warning, message)

// Outputs error log message.
#define LOG_E(message) LOG(Logger::Error, message)

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
    LogLevel GetLevel();
    void SetLevel(LogLevel level);

    // Gets the stream where messages will be displayed.
    std::ostream& GetStream() { return std::cerr; };

    // Maps log levels to strings for printing purposes.
    std::string GetLevelString(LogLevel level);

    // Maps log levels to colors for printing purposes.
    std::string GetLevelColor(LogLevel level);

    // Formats a prefix for the log message.
    std::string GetPrefix(LogLevel level);

    // Formats a sufix for the log message.
    std::string GetSufix();

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