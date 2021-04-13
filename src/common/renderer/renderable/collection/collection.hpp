#pragma once
#include <vector>
#include "../renderable.hpp"

class CollectionRenderable : public Renderable {
public:

    void add_child(Renderable *rbl);

    void draw() const override;

private:
    std::vector<Renderable *> children;
};