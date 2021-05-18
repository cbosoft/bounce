#pragma once
#include <string>
#include <map>
#include <armadillo>
#include <array>

#include "../globj.hpp"

struct TextureAnimLoop {
    unsigned int from, to;
};

struct TextureFrameCoords {
    arma::Col<float>::fixed<2> bl, wh;
};

class Colour;

class Texture : public GLObject {
public:
    Texture(const std::string &path, const std::string &name);
    explicit Texture(const std::string &name);

    void use() const override;

    [[nodiscard]] const TextureFrameCoords &get_texcoords_of_frame(unsigned int index) const;
    [[nodiscard]] const TextureAnimLoop &get_named_loop(const std::string &name) const;
    [[nodiscard]] bool is_null() const;

    void set_image_data(unsigned char *data, int w, int h);

    const static TextureAnimLoop default_loop;
    const static TextureFrameCoords default_framing;

    [[nodiscard]] const std::string &get_name() const;

private:
    explicit Texture(void *vptr);

    const std::string _name;

    std::vector<TextureFrameCoords> _frame_texcoords;
    std::map<std::string, TextureAnimLoop> _loops;
    friend class Renderer;
};