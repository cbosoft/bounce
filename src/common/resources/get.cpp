#include "manager.hpp"

std::string ResourceManager::get_path(const std::string &subdir,
                                      const std::string &name,
                                      const std::string &extension)
{
    std::filesystem::path path = this->_root;
    path /= subdir;
    path /= name;
    if (!extension.empty()) {
        if (extension[0] != '.')
            path += ".";
        path += extension;
    }

    if (!std::filesystem::exists(path)) {
        throw std::runtime_error("Requested file does not exist.");
    }

    return path.string();
}