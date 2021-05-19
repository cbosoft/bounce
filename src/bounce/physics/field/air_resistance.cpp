#include <bounce/physics/field/air_resistance.hpp>

AirResField::AirResField(double strength)
:   _strength(strength)
{

}

arma::vec2 AirResField::f(Object *obj) const
{
    return -this->_strength*obj->get_velocity();
}

void AirResField::set_strength(double strength)
{
    this->_strength = strength;
}