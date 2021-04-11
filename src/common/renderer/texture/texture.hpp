#pragma once
#include <string>
#include "../globj.hpp"

class Texture : public GLObject {
public:
    Texture(const std::string &path);

    int get_width();
    int get_height();
    int get_n_channels();

    void use() const override;

private:
    int w, h, c;
};