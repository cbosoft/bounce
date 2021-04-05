#include "renderable.hpp"

Renderable::Renderable(Transform *parent)
: Transform(parent)
{
    // do nothing
}

Renderable::Renderable(Transform *parent, GeometricEquation *shape)
: Renderable(parent)
{
    this->_shape.emplace_back(shape);
}

Renderable::Renderable(Transform *parent, const std::vector<GeometricEquation *> &shape)
: Renderable(parent)
{
    this->_shape = shape;
}