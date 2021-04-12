#pragma once

#include "../renderable.hpp"

class CircleRenderable : public Renderable {
public:
    void draw() const override;
};