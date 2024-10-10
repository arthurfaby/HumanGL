#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <mutex>

enum class LogLevel
{
    DEBUG,
    ERROR,
    INFO,
    WARNING,
};

class Logger
{
public:
    // Constructors
    Logger() = delete;
    Logger(const Logger& other) = delete;

    // Destructor
    ~Logger() = delete;

    // Getters
    [[nodiscard]] static bool isDebug();

    // Setters
    static void setDebug(bool isDebug);

    // Operator overloads
    Logger& operator=(const Logger& other) = delete;

    // Methods
    static void debug(const std::string& message, ...);
    static void error(const std::string& message, ...);
    static void info(const std::string& message, ...);
    static void warning(const std::string& message, ...);

private:
    /**
    * Mutex dedicated to logging.
    */
    static std::mutex _logMutex;

    /**
    * State of the logger.
    */
    static bool _isDebug;

    // Methods
    static void log(LogLevel level, const char* format, va_list args);
    static std::string getTextColor(LogLevel level);
    static std::ostream& getOutput(LogLevel level);
    static std::string currentTime();
    static std::string logLevelToString(LogLevel level);
};

#endif //LOGGER_HPP