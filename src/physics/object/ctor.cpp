#include "object.hpp"

PhysicsObject::PhysicsObject(const arma::vec2 &position, bool fixed)
        : position(position)
        , new_position(position)
        , velocity({0, 0})
        , force({0,0})
        , mass(1.0)
        , inv_mass(1.0)
        , _fixed(fixed)
{
    this->set_mass(1.0);
}

PhysicsObject::PhysicsObject(const arma::vec2 &position, double mass)
        : position(position)
        , new_position(position)
        , velocity({0, 0})
        , force({0, 0})
        , mass(1.0)
        , inv_mass(1.0)
        , _fixed(false)
{
    this->set_mass(mass);
}
