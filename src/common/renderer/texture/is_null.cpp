#include "texture.hpp"

bool Texture::is_null() const
{
    return this->_id == GLuint(-1);
}