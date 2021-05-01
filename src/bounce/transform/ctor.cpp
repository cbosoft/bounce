#include <bounce/transform/transform.hpp>

Transform::Transform()
: _parent{nullptr}
, _relative_position({0.0, 0.0})
, _active{true}
{
    // do nothing
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