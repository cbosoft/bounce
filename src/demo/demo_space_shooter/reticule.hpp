#pragma once

#include <bounce/bounce.hpp>

class DemoReticule final: public RegularPolygonMeshRenderable {
public:
    explicit DemoReticule(Transform *parent)
            : RegularPolygonMeshRenderable(50)
    {
        this->set_parent(parent);
        this->set_size({5.0, 5.0});
        this->set_z(100);
        this->set_texture_name("crosshair");
    }
};
