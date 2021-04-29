#include "logger.hpp"

Logger::Logger()
:   _log_level(LL_INFO)
{
    this->gen_unique_log_path();
}