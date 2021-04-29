#include <filesystem>

#include "../../logging/logger.hpp"
#include "../../resources/manager.hpp"
#include "../image/image.hpp"
#include "texture.hpp"

const TextureAnimLoop Texture::default_loop = {0, 1};
const TextureFrameCoords Texture::default_framing = {{0.f, 0.f}, {1.f, 1.f}};

Texture::Texture(const std::string &texture_name)
:   Texture()
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

    this->set_image_data(data, w, h);
    stbi_image_free(data);

    Logger::ref() << LL_INFO << "Loaded texture \"" << texture_name << "\".\n";
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