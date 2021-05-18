#include <bounce/object/object.hpp>
#include <bounce/physics/engine/engine.hpp>


Object::Object(Transform *parent)
    :   Transform(parent)
    ,   _shape(CollisionShape::circle(0.5))
    ,   new_position({0, 0})
    ,   velocity({0, 0})
    ,   force({0, 0})
    ,   mass(1.0)
    ,   inv_mass(1.0)
    ,   _layer("unset")
    ,   _material({1.0, 0.0})
    ,   c(Colour::from_grayscale(255))
    ,   _fixed(false)
    ,   _renderable_collider(nullptr)
{
    PhysicsEngine::ref().register_object(this);
    this->add_tag("object");
}