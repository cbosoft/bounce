#include "logger.hpp"

Logger::~Logger()
{
    this->flush();
}