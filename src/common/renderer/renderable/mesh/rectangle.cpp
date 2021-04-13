#include "mesh.hpp"

MeshRenderable * MeshRenderable::rectangle(double w, double h)
{
    double hh = 1.0, hw = 1.0, aspect = w/h, scale = h;
    if (aspect > 1.0) {
        hh = 1./aspect;
        scale = w;
    }
    else {
        hw = aspect;
    }

    auto *rbl = new MeshRenderable({ {-hw, -hh}, {-hw, hh}, {hw, hh}, {hw, -hh} });
    rbl->set_scale(scale);
    return rbl;
}