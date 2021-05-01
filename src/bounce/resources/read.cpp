#include <fstream>
#include <sstream>

#include <bounce/resources/manager.hpp>

std::string ResourceManager::read_file_to_string(const std::string &path)
{
    std::string buff, rv;
    std::ifstream ifs(path);

    if (!ifs.is_open()) {
        std::stringstream ss;
        ss << "Could not open file: \"" << path << "\"" << strerror(errno);
        throw std::runtime_error(ss.str());
    }

    while (std::getline(ifs, buff)) {
        rv += buff;
    }

    return rv;
}