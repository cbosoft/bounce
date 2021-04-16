#include "renderable.hpp"

Renderable::Renderable()
: Transform()
, _colour(Colour::from_rgb(255, 255, 255))
, _scale(1.0)
, _angle(0.0)
, _object(nullptr)
, _shader_name("default")
, _z(0)
, _visible(true)
{
    // do nothing
}