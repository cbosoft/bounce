#include "object.hpp"
#include "../physics/engine/engine.hpp"


Object::Object(Transform *parent)
    :   Transform(parent)
    ,   _shape(CollisionShape::circle(0.5))
    ,   new_position({0, 0})
    ,   velocity({0, 0})
    ,   force({0, 0})
    ,   mass(1.0)
    ,   inv_mass(1.0)
    ,   cor(1.0)
    ,   _layer("unset")
    ,   c(Colour::from_grayscale(255))
    ,   _fixed(false)
    ,   _renderable_collider(nullptr)
{
    // nothing
    PhysicsEngine::ref().register_object(this);
}

Object::Object(Transform *parent, const arma::vec2 &position, bool fixed, double cor)
    :   Object(parent)
{
    this->_fixed = fixed;
    this->cor = cor;
    this->set_position(position);
}

Object::Object(Transform *parent, const arma::vec2 &position, double mass, double cor)
    :   Object(parent)
{
    this->cor = cor;
    this->set_position(position);
    this->set_mass(mass);
}
