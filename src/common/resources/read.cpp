#include <fstream>
#include <iostream>
#include "manager.hpp"

std::string ResourceManager::read_file_to_string(const std::string &path)
{
    std::string buff, rv;
    std::ifstream ifs(path);

    if (!ifs.is_open()) {
        std::perror(path.c_str());
        throw std::runtime_error("Could not open file.");
    }

    while (std::getline(ifs, buff)) {
        rv += buff;
    }

    return rv;
}