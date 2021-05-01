#pragma once
#include <sstream>
#include <iostream>
#include <filesystem>

enum LogLevel {LL_INFO, LL_WARN, LL_ERROR};

class Logger {
public:
    static Logger &ref();
    ~Logger();

    Logger &operator<<(LogLevel level)
    {
        this->_log_level = level;
        switch (level) {
            case LL_INFO:
                (*this) << "i) ";
                break;
            case LL_WARN:
                (*this) << "w) ";
                break;
            case LL_ERROR:
                (*this) << "E) ";
                break;
        }
        return *this;
    }

    template<typename T>
    Logger &operator<<(T thing)
    {
        this->_buffer << thing;
        if (this->_log_level > LL_INFO)
            std::cerr << thing;
        this->maybe_flush();
        return *this;
    }

private:
    Logger();

    void gen_unique_log_path();
    void maybe_flush();
    void flush();

    std::filesystem::path _output_path;
    std::stringstream _buffer;
    LogLevel _log_level;
};