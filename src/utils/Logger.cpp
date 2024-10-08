#include "Logger.hpp"
#include <cstdarg>

std::mutex Logger::logMutex;

const std::string DEBUG_COLOR = "\e[96m";
const std::string ERROR_COLOR = "\e[91m";
const std::string INFO_COLOR = "\e[97m";
const std::string WARNING_COLOR = "\e[93m";
const std::string RESET_COLOR = "\e[0m";

void Logger::log(const LogLevel level, const char* format, va_list args)
{
    std::lock_guard guard(logMutex);

    const std::string textColor = getTextColor(level);
    std::ostream& output = getOutput(level);
    const std::string levelToString = logLevelToString(level);

    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);

    output << textColor + currentTime() + " [" + levelToString + "]\t"
            + (levelToString == "INFO" ? "\t" : "") // extra tab for alignment
            + buffer + RESET_COLOR << std::endl;
}

/**
* Convert the appropriate text color depending on the log level.
*/
std::string Logger::getTextColor(const LogLevel level)
{
    switch (level)
    {
        case LogLevel::DEBUG: return DEBUG_COLOR;
        case LogLevel::ERROR: return ERROR_COLOR;
        case LogLevel::INFO: return INFO_COLOR;
        case LogLevel::WARNING: return WARNING_COLOR;
        default: return "";
    }
}

/**
 * Convert the appropriate std::ostream depending on the log level.
 */
std::ostream& Logger::getOutput(const LogLevel level)
{
    switch (level)
    {
        case LogLevel::ERROR: return std::cerr;
        default: return std::clog;
    }
}

/**
* Get the current timestamp.
*/
std::string Logger::currentTime()
{
    const std::time_t now = std::time(nullptr);
    char buf[80];
    std::strftime(buf, sizeof(buf), "%H:%M:%S", std::localtime(&now));
    return {buf};
}

/**
* Convert the log level into a string.
*/
std::string Logger::logLevelToString(const LogLevel level)
{
    switch (level)
    {
        case LogLevel::DEBUG: return "DEBUG";
        case LogLevel::ERROR: return "ERROR";
        case LogLevel::INFO: return "INFO";
        case LogLevel::WARNING: return "WARNING";
        default: return "";
    }
}

void Logger::debug(const std::string& message, ...)
{
    va_list args;
    va_start(args, message);
    log(LogLevel::DEBUG, message.c_str(), args);
    va_end(args);
}

void Logger::error(const std::string& message, ...)
{
    va_list args;
    va_start(args, message);
    log(LogLevel::ERROR, message.c_str(), args);
    va_end(args);
}

void Logger::info(const std::string& message, ...)
{
    va_list args;
    va_start(args, message);
    log(LogLevel::INFO, message.c_str(), args);
    va_end(args);
}

void Logger::warning(const std::string& message, ...)
{
    va_list args;
    va_start(args, message);
    log(LogLevel::WARNING, message.c_str(), args);
    va_end(args);
}