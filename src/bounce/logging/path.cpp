#include <fstream>

#include <bounce/logging/logger.hpp>

void Logger::gen_unique_log_path()
{
    // generate unique log path based on date
    this->_output_path = "./bounce_log.txt";
    std::ofstream ofs(this->_output_path, std::ios::trunc);
}