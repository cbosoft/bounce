#include <bounce/logging/logger.hpp>

Logger::~Logger()
{
    this->flush();
}