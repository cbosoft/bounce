#include <iostream>
#include <filesystem>

#include "texture.hpp"
#include "../image/image.hpp"
#include "../../resources/manager.hpp"

Texture::Texture(const std::string &texture_name)
{
    std::string path = ResourceManager::ref().get_path("textures", texture_name, ".png");
    if (!std::filesystem::exists(path)) {
        throw std::runtime_error("error opening texture: file not found");
    }
    auto cpath = path.c_str();
    int w, h, c;
    unsigned char *data = stbi_load(
            cpath,
            &w, &h, &c, 0);

    glGenTextures(1, &this->_id);
    glBindTexture(GL_TEXTURE_2D, this->_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                 w, h, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    stbi_image_free(data);
}

Texture::Texture()
{
    glGenTextures(1, &this->_id);
}

Texture::Texture(void *vptr)
{
    (void) vptr;
    this->_id = -1;
}