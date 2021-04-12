#include "mesh.hpp"

MeshRenderable *MeshRenderable::regular_polygon(int n, double angle)
{
    double dtheta = 2.*M_PI/double(n);
    std::vector<arma::vec2> pts(n);
    for (int i = 0; i < n; i++) {
        pts[i] = {std::cos(angle), std::sin(angle)};
        angle += dtheta;
    }
    return new MeshRenderable(pts);
}