#include "renderer.hpp"
#include <filesystem>

void Renderer::add_texture(const std::string &path)
{
    this->textures[path] = new Texture(path);
}

Texture *Renderer::get_texture(const std::string &name)
{
    auto it = this->textures.find(name);
    if (it == this->textures.end()) {
        // if the texture name is a resource path, try to load it
        try {
            // raises runtime error if name is not found
            this->textures[name] = new Texture(name);
        }
        catch (const std::runtime_error &e) {
            std::cerr << "w) Could not find texture \"" << name <<"\" and could not load it from file." << std::endl;

            if (!this->textures.empty()) {
                std::cerr << "w) Falling back to first available texture" << std::endl;
                auto kv = *this->textures.begin();
                return kv.second;
            }
            else {
                std::cerr << "w) and no alternate textures available: returning null texture." << std::endl;
                it = this->textures.find("null");
                if (it == this->textures.end()) {
                    this->textures["null"] = new Texture(nullptr);
                }
                return this->textures["null"];
            }
        }
    }
    return this->textures[name];
}