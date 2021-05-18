#include <bounce/renderer/renderable/mesh/mesh.hpp>

MeshRenderable::MeshRenderable()
:   _anchor{0, 0}
{
    this->add_tag("mesh renderable");
}

MeshRenderable::MeshRenderable(const std::vector<arma::vec2> &points)
:   MeshRenderable()
{
    this->_points = points;
}

RectangleMeshRenderable::RectangleMeshRenderable(double w, double h)
{
    this->add_tag("rectangle mesh renderable");
    this->_points = { {-.5, -.5}, {-.5, .5}, {.5, .5}, {.5, -.5} };
    this->set_size({w, h});
}

FilletedRectangleMeshRenderable::FilletedRectangleMeshRenderable(double w, double h, double r)
{
    this->add_tag("filleted rectangle mesh renderable");
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
    this->add_tag("regular polygon mesh renderable");
    double dtheta = 2.*M_PI/double(n);
    for (int i = 0; i < n; i++) {
        this->_points.push_back({std::cos(theta)*.5f, std::sin(theta)*.5f});
        theta += dtheta;
    }
}