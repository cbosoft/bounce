#include "logger.hpp"

Logger &Logger::ref()
{
    static Logger logger;
    return logger;
}