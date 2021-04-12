#include "mesh.hpp"

MeshRenderable * MeshRenderable::rectangle(double w, double h)
{
    double hh = 1.0, hw = 1.0, aspect = w/h;
    if (aspect > 1.0) {
        hh = 1./aspect;
    }
    else {
        hw = aspect;
    }

    return new MeshRenderable({ {-hw, -hh}, {-hw, hh}, {hw, hh}, {hw, -hh} });
}