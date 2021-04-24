#include <iostream>
#include <filesystem>

#include "texture.hpp"
#include "../image/image.hpp"
#include "../../resources/manager.hpp"

const TextureAnimLoop Texture::default_loop = {0, 1};
const TextureFrameCoords Texture::default_framing = {{0.f, 0.f}, {1.f, 1.f}};

Texture::Texture(const std::string &texture_name)
{
    auto &rm = ResourceManager::ref();
    std::string path = rm.get_path("textures", texture_name, ".png");
    if (!std::filesystem::exists(path)) {
        throw std::runtime_error("error opening texture: file not found");
    }

    try {
        json metadata = rm.get_metadata("textures", texture_name);
        json frames = metadata["frames"];
        metadata = metadata["meta"];
        float total_w = metadata["size"]["w"];
        float total_h = metadata["size"]["h"];
        for (auto& frame : frames) {
            float x = float(frame["frame"]["x"])/total_w;
            float y = float(frame["frame"]["y"])/total_h;
            float w = float(frame["frame"]["w"])/total_w;
            float h = float(frame["frame"]["h"])/total_h;
            this->_frame_texcoords.push_back({{x, y}, {w, h}});
        }

        json frame_tags = metadata["frameTags"];
        for (const json &frame_tag : frame_tags) {
            std::string name = frame_tag["name"];
            unsigned int from = frame_tag["from"];
            unsigned int to = frame_tag["to"];
            this->_loops[name] = {from, to};
        }
    }
    catch (const std::runtime_error &e) {
        // no metadata
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