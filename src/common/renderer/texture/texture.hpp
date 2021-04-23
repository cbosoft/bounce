#pragma once
#include <string>
#include "../globj.hpp"

class Texture : public GLObject {
public:
    explicit Texture(const std::string &path);
    Texture();

    void use() const override;

private:
    explicit Texture(void *vptr);
    friend class Renderer;
};