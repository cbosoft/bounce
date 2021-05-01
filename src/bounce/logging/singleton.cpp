#include <bounce/logging/logger.hpp>

Logger &Logger::ref()
{
    static Logger logger;
    return logger;
}