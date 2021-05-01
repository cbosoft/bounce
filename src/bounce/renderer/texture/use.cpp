#include <bounce/renderer/texture/texture.hpp>

void Texture::use() const
{
    glBindTexture(GL_TEXTURE_2D, this->_id);
}