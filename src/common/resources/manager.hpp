#pragma once

#include <filesystem>
#include <string>

#include "../serialisation/json.hpp"

class ResourceManager {
public:
    ResourceManager(const ResourceManager &other) =delete;
    ResourceManager &operator=(ResourceManager &other) =delete;
    ~ResourceManager() =default;

    static ResourceManager &ref();

    std::string get_path(const std::string &subdir, const std::string &name, const std::string &extension);
    json get_metadata(const std::string &category, const std::string &name);

private:
    std::string read_file_to_string(const std::string &path);
    ResourceManager();

    void set_root();

    std::filesystem::path _root;
};