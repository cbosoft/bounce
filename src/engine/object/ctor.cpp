#include "object.hpp"
#include "../physics/engine/engine.hpp"

Object::Object(Transform *parent, const arma::vec2 &position, bool fixed, double cor)
        : Transform(parent)
        , new_position(position)
        , velocity({0, 0})
        , force({0,0})
        , mass(1.0)
        , inv_mass(1.0)
        , cor(cor)
        , _radius(1.0)
        , _layer("unset")
        , c(Colour::from_grayscale(255))
        , _fixed(fixed)
{
    this->set_position(position);
    this->set_mass(1.0);
    PhysicsEngine::ref().register_object(this);
}

Object::Object(Transform *parent, const arma::vec2 &position, double mass, double cor)
        : Transform(parent)
        , new_position(position)
        , velocity({0, 0})
        , force({0, 0})
        , mass(1.0)
        , inv_mass(1.0)
        , cor(cor)
        , _radius(1.0)
        , _layer("unset")
        , c(Colour::from_grayscale(255))
        , _fixed(false)
{
    this->set_position(position);
    this->set_mass(mass);
    PhysicsEngine::ref().register_object(this);
}
