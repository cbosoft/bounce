#include "renderable.hpp"

std::vector<GeometricEquation *> Renderable::get_shape() const
{
    return this->_shape;
}