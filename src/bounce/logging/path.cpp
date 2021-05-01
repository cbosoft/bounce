#include <fstream>

#include <bounce/logging/logger.hpp>
#include <bounce/game/game.hpp>

void Logger::gen_unique_log_path()
{
    if (this->_output_path.empty()) {
        this->_output_path = Game::ref().get_settings_saves_path();
        this->_output_path /= "log.txt"; // TODO generate unique log name?
        std::ofstream ofs(this->_output_path, std::ios::trunc);
    }
    else {
        (*this) << LL_WARN << "Logger tried to *RE*generate output path - this is not allowed.\n";
    }
}