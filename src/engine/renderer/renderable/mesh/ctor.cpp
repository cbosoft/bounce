#include "mesh.hpp"

MeshRenderable::MeshRenderable(const std::vector<arma::vec2> &points)
:   _points(points)
,   _anchor{0, 0}
{
    // do nothing
}

RectangleMeshRenderable::RectangleMeshRenderable(double w, double h)
{
    this->_points = { {-.5, -.5}, {-.5, .5}, {.5, .5}, {.5, -.5} };
    this->set_size({w, h});
}

FilletedRectangleMeshRenderable::FilletedRectangleMeshRenderable(double w, double h, double r)
{
    this->_points = {
            {-.5, -.5+r}, {-.5+r, -.5},
            {.5-r, -.5}, {.5, -.5+r},
            {.5, .5-r}, {.5-r, .5},
            {-.5+r, .5}, {-.5, .5-r}
    };
    this->set_size({w, h});
}

RegularPolygonMeshRenderable::RegularPolygonMeshRenderable(int n, double theta)
{
    double dtheta = 2.*M_PI/double(n);
    for (int i = 0; i < n; i++) {
        this->_points.push_back({std::cos(theta)*.5f, std::sin(theta)*.5f});
        theta += dtheta;
    }
}