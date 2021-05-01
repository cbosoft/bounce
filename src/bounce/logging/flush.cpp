#include <fstream>

#include <bounce/logging/logger.hpp>

void Logger::maybe_flush()
{
    if (this->_number_things > 10)
        this->flush();
}

void Logger::flush()
{
    if (!this->_output_path.empty()) {
        std::ofstream ofs(this->_output_path, std::ios::app);
        ofs << this->_buffer.str();
        this->_buffer.str("");
        this->_number_things = 0;
    }
}