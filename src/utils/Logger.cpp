#include "Logger.hpp"
#include <cstdarg>
#include <iomanip>

std::mutex Logger::_logMutex;
bool Logger::_isDebug = false;

const std::string DEBUG_COLOR = "\e[96m";
const std::string ERROR_COLOR = "\e[91m";
const std::string INFO_COLOR = "\e[97m";
const std::string WARNING_COLOR = "\e[93m";
const std::string RESET_COLOR = "\e[0m";

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Getters
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @return The state of the logger
 */
[[nodiscard]] bool Logger::isDebug()
{
    return _isDebug;
}

/**
 * Set the state of the logger.
 *
 * @param isDebug The new state of the logger
 */
void Logger::setDebug(const bool isDebug)
{
    _isDebug = isDebug;
}

void Logger::log(const LogLevel level, const char* format, va_list args)
{
    std::lock_guard guard(_logMutex);

    const std::string textColor = getTextColor(level);
    std::ostream& output = getOutput(level);
    const std::string levelToString = logLevelToString(level);

    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);

    output << textColor + currentTime() // timestamp : HH:MM:SS
            + " [" + levelToString + "]\t" // level of log : [DEBUG] - [ERROR] - [INFO] - [WARNING]
            + (levelToString == "INFO" ? "\t" : "") // extra tab for alignment
            + buffer + RESET_COLOR << std::endl; // actual message
}

/**
* @return The appropriate text color depending on the log level.
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
 * @return The appropriate std::ostream depending on the log level.
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
* @return The current timestamp.
*/
std::string Logger::currentTime()
{
    // Get the current system time
    const auto now = std::chrono::system_clock::now();

    // Convert to time_t for breaking into hh:mm:ss
    const auto now_time_t = std::chrono::system_clock::to_time_t(now);
    const auto local_time = *std::localtime(&now_time_t);

    // Extract milliseconds
    const auto milliseconds = duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

    // Format the time
    std::ostringstream oss;
    oss << std::put_time(&local_time, "%H:%M:%S") << ":"
              << std::setfill('0') << std::setw(3) << milliseconds.count();
    return oss.str();
}

/**
* Convert the log level enum value into a string.
*
* @return A string representing the log level
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

/**
 * Detailed information, typically of interest only when diagnosing problems.
 *
 * @param message   C string that contains a format string that follows the same specifications as format in <a href="https://cplusplus.com/reference/cstdio/printf/">printf</a>
 * @param ...       Any amount of variables to replace the placeholders contained in the message
 */
void Logger::debug(const std::string& message, ...)
{
    if (!_isDebug)
    {
        return;
    }

    va_list args;
    va_start(args, message);
    log(LogLevel::DEBUG, message.c_str(), args);
    va_end(args);
}

/**
 * A serious issue, indicating that the program may not be able to continue running correctly.
 *
 * @param message   C string that contains a format string that follows the same specifications as format in <a href="https://cplusplus.com/reference/cstdio/printf/">printf</a>
 * @param ...       Any amount of variables to replace the placeholders contained in the message
 */
void Logger::error(const std::string& message, ...)
{
    va_list args;
    va_start(args, message);
    log(LogLevel::ERROR, message.c_str(), args);
    va_end(args);
}

/**
 * Confirmation that things are working as expected.
 *
 * @param message   C string that contains a format string that follows the same specifications as format in <a href="https://cplusplus.com/reference/cstdio/printf/">printf</a>
 * @param ...       Any amount of variables to replace the placeholders contained in the message
 */
void Logger::info(const std::string& message, ...)
{
    va_list args;
    va_start(args, message);
    log(LogLevel::INFO, message.c_str(), args);
    va_end(args);
}

/**
 * An indication that something unexpected happened, but the application can still function.
 *
 * @param message   C string that contains a format string that follows the same specifications as format in <a href="https://cplusplus.com/reference/cstdio/printf/">printf</a>
 * @param ...       Any amount of variables to replace the placeholders contained in the message
 */
void Logger::warning(const std::string& message, ...)
{
    va_list args;
    va_start(args, message);
    log(LogLevel::WARNING, message.c_str(), args);
    va_end(args);
}