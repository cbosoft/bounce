#include <bounce/resources/manager.hpp>

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

json ResourceManager::get_metadata(const std::string &subdir,
                                      const std::string &name)
{
    std::filesystem::path path = this->_root;
    path /= subdir;
    path /= name;
    path += ".json";

    std::string content = this->read_file_to_string(path.string());
    return json::parse(content);
}
