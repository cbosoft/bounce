#include "texture.hpp"
#include "../image/image.hpp"

Texture::Texture(const std::string &path)
: w(0)
, h(0)
, c(0)
{
    auto cpath = path.c_str();
    unsigned char *data = stbi_load(
            cpath,
            &this->w, &this->h, &this->c, 0);

    GLuint id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                 this->w, this->h, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    stbi_image_free(data);
    this->set_id(id);
}