#include "object.hpp"

PhysicsObject::PhysicsObject(Transform *parent, const arma::vec2 &position, bool fixed, double cor)
        : Transform(parent, position)
        , new_position(position)
        , velocity({0, 0})
        , force({0,0})
        , mass(1.0)
        , inv_mass(1.0)
        , cor(cor)
        , _fixed(fixed)
{
    this->set_mass(1.0);
}

PhysicsObject::PhysicsObject(Transform *parent, const arma::vec2 &position, double mass, double cor)
        : Transform(parent, position)
        , new_position(position)
        , velocity({0, 0})
        , force({0, 0})
        , mass(1.0)
        , inv_mass(1.0)
        , cor(cor)
        , _fixed(false)
{
    this->set_mass(mass);
}
