#include <bounce/physics/rigidbody/rigidbody.hpp>

Rigidbody::Rigidbody(Transform *parent)
:   Collider(parent)
,   _velocity({0, 0})
,   _previous_velocity({0, 0})
,   _force({0, 0})
,   _mass(1.)
,   _inv_mass(1.)
,   _material({0., 0.})
,   _fixed(false)
{
    this->add_tag("rigidbody");
}