#include <bounce/colour/colour.hpp>
#include <bounce/serialisation/json.hpp>

Colour Colour::from_json(json j) noexcept
{
    int r = j[0], g = j[1], b = j[2], a = j[3];
    return Colour::from_rgb(r, g, b, a);
}

json Colour::serialise() const
{
    return {this->r, this->g, this->b, this->a};
}