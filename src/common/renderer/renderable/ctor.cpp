#include "renderable.hpp"

Renderable::Renderable()
: Transform()
, _colour(Colour::from_rgb(255, 255, 255))
, _scale(1.0)
, _object(nullptr)
{
    // do nothing
}