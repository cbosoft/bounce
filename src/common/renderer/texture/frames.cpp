#include "texture.hpp"

const TextureFrameCoords &Texture::get_texcoords_of_frame(unsigned int index) const
{
    if (
            this->_frame_texcoords.empty() ||
            index >= this->_frame_texcoords.size()) {
        return Texture::default_framing;
    }

    return this->_frame_texcoords.at(index);
}

const TextureAnimLoop &Texture::get_named_loop(const std::string &name) const
{
    auto it = this->_loops.find(name);
    if (it == this->_loops.end()) {
        return Texture::default_loop;
    }

    return it->second;
}