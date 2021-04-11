#include "renderer.hpp"

void Renderer::add_texture(const std::string &path)
{
    this->textures[path] = new Texture(path);
}

Texture *Renderer::get_texture(const std::string &name)
{
    auto it = this->textures.find(name);
    if (it == this->textures.end()) {
        this->textures[name] = new Texture(name);
    }
    return this->textures[name];
}