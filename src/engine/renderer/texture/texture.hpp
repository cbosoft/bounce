#pragma once
#include <string>
#include <vector>
#include <map>
#include <armadillo>

#include "../globj.hpp"

struct TextureAnimLoop {
    unsigned int from, to;
};

struct TextureFrameCoords {
    arma::Col<float>::fixed<2> bl, wh;
};

class Texture : public GLObject {
public:
    explicit Texture(const std::string &path);
    Texture();

    void use() const override;

    [[nodiscard]] const TextureFrameCoords &get_texcoords_of_frame(unsigned int index) const;
    [[nodiscard]] const TextureAnimLoop &get_named_loop(const std::string &name) const;
    [[nodiscard]] bool is_null() const;

    const static TextureAnimLoop default_loop;
    const static TextureFrameCoords default_framing;

private:
    explicit Texture(void *vptr);

    std::vector<TextureFrameCoords> _frame_texcoords;
    std::map<std::string, TextureAnimLoop> _loops;
    friend class Renderer;
};