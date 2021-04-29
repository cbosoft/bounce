#include <filesystem>

#include "manager.hpp"

#ifndef RESOURCES_DIR
#define RESOURCES_DIR "."
#endif


void ResourceManager::set_root()
{
    std::filesystem::path provisional_root{"."};
    provisional_root /= "resources";
    if (std::filesystem::exists(provisional_root)) {
        this->_root = provisional_root;
        return;
    }

    provisional_root = std::filesystem::path{".."};
    provisional_root /= "resources";
    if (std::filesystem::exists(provisional_root)) {
        this->_root = provisional_root;
        return;
    }

    provisional_root = std::filesystem::path{RESOURCES_DIR};
    provisional_root /= "resources";
    if (std::filesystem::exists(provisional_root)) {
        this->_root = provisional_root;
        return;
    }

    // TODO no resources dir found: error?
}