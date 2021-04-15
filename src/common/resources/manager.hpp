#pragma once

#include <filesystem>
#include <string>

class ResourceManager {
public:
    ResourceManager(const ResourceManager &other) =delete;
    ResourceManager &operator=(ResourceManager &other) =delete;
    ~ResourceManager() =default;

    static ResourceManager &ref();

    std::string get_path(const std::string &subdir, const std::string &name, const std::string &extension);

private:
    ResourceManager();

    void set_root();

    std::filesystem::path _root;
};