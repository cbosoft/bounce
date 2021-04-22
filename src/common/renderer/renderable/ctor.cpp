#include "renderable.hpp"

Renderable::Renderable()
: Transform()
, _colour(Colours::white)
, _border_colour(Colours::white)
, _aspect_ratio(1.0)
, _angle(0.0)
, _border_size(0.0)
, _size({1.0, 1.0})
, _object(nullptr)
, _shader_name("default")
, _z(0)
, _visible(true)
{
    // do nothing
}