#include <bounce/transform/transform.hpp>
#include <bounce/game/game.hpp>

Transform::Transform()
:   _parent{nullptr}
,   _relative_position({0.0, 0.0})
,   _active{true}
,   _scale(1.0)
,   _relative_z(0)
{
    this->add_tag("transform");
}

Transform::Transform(Transform *parent)
: Transform()
{
    this->set_parent(parent);
}

Transform::Transform(Transform *parent, const arma::vec2 &position)
: Transform(parent)
{
    this->set_position(position);
}
