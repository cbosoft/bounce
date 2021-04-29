#include "logger.hpp"
#include <fstream>

void Logger::maybe_flush()
{
    // TODO decide when/if should flush
    this->flush();
}

void Logger::flush()
{
    std::ofstream ofs(this->_output_path, std::ios::app);
    ofs << this->_buffer.str();
    this->_buffer.str("");
}