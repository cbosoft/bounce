#include <bounce/physics/field/gravity.hpp>

GravityField::GravityField(double strength)
:   _strength(strength)
{
    // do nothing
}

arma::vec2 GravityField::f(Object *obj) const
{
    arma::vec2 accel{0, -this->_strength};
    return accel*obj->get_mass();
}

void GravityField::set_strength(double strength)
{
    this->_strength = strength;
}