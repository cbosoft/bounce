#include "renderable.hpp"

Renderable::Renderable()
: Transform()
, _colour(Colours::white)
, _border_colour(Colours::white)
, _scale(1.0)
, _angle(0.0)
, _object(nullptr)
, _shader_name("default")
, _z(0)
, _visible(true)
{
    // do nothing
}