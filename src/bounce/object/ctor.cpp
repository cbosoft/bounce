#include <bounce/object/object.hpp>
#include <bounce/physics/engine/engine.hpp>


Object::Object(Transform *parent)
    :   Transform(parent)
    ,   _shape(CollisionShape::circle(0.5))
    ,   _velocity({0, 0})
    ,   _previous_velocity({0, 0})
    ,   _force({0, 0})
    ,   _mass(1.0)
    ,   _inv_mass(1.0)
    ,   _layer("unset")
    ,   _material({0.0, 0.0})
    ,   _fixed(false)
    ,   _renderable_collider(nullptr)
    ,   _colliding_flags(0)
{
    PhysicsEngine::ref().register_object(this);
    this->add_tag("object");
}