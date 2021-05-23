#include <bounce/physics/rigidbody/rigidbody.hpp>
void Rigidbody::set_mass(double mass)
{
    this->_mass = mass;
    this->_inv_mass = 1./mass;
}

double Rigidbody::get_mass() const
{
    return this->_mass;
}

void Rigidbody::set_velocity(const arma::vec2 &_velocity)
{
    this->_velocity = _velocity;
}

void Rigidbody::set_force(const arma::vec2 &_force)
{
    this->_force = _force;
}

const arma::vec2 &Rigidbody::get_velocity() const
{
    return this->_velocity;
}

const arma::vec2 &Rigidbody::get_force() const
{
    return this->_force;
}

void Rigidbody::add_force(const arma::vec2 &dforce)
{
    this->_force += dforce;
}

bool Rigidbody::is_fixed() const
{
    return this->_fixed;
}

void Rigidbody::set_fixed(bool value)
{
    this->_fixed = value;
}
void Rigidbody::set_bounciness(double bounciness)
{
    this->_material.bounciness = bounciness;
}

void Rigidbody::set_friction(double friction)
{
    this->_material.dynamic_friction = friction;
}

const PhysicsMaterial &Rigidbody::get_material() const
{
    return this->_material;
}
