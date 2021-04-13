#include "mesh.hpp"

MeshRenderable *MeshRenderable::filleted_rectangle(double w, double h, double r)
{
    double hh = 1.0, hw = 1.0, aspect = w/h, scale = h;
    if (aspect > 1.0) {
        hh = 1./aspect;
        scale = w;
    }
    else {
        hw = aspect;
    }

    r /= scale;

    auto *rbl = new MeshRenderable({
        {-hw, -hh+r}, {-hw+r, -hh},
        {hw-r, -hh}, {hw, -hh+r},
        {hw, hh-r}, {hw-r, hh},
        {-hw+r, hh}, {-hw, hh-r}
    });
    rbl->set_scale(scale);
    return rbl;
}