#include "object.hpp"

void PhysicsObject::set_mass(double _mass)
{
    this->mass = _mass;
    this->inv_mass = 1./_mass;
}

double PhysicsObject::get_mass() const
{
    return this->mass;
}

void PhysicsObject::set_new_position(const arma::vec2 &_new_position)
{
    this->new_position = _new_position;
}

void PhysicsObject::set_new_position(const arma::vec2 &&_new_position)
{
    this->new_position = _new_position;
}

void PhysicsObject::set_velocity(const arma::vec2 &_velocity)
{
    this->velocity = _velocity;
}

void PhysicsObject::set_velocity(const arma::vec2 &&_velocity)
{
    this->velocity = _velocity;
}

void PhysicsObject::set_force(const arma::vec2 &_force)
{
    this->force = _force;
}

void PhysicsObject::set_force(const arma::vec2 &&_force)
{
    this->force = _force;
}

const arma::vec2 &PhysicsObject::get_new_position() const
{
    return this->new_position;
}

const arma::vec2 &PhysicsObject::get_velocity() const
{
    return this->velocity;
}

const arma::vec2 &PhysicsObject::get_force() const
{
    return this->force;
}

bool PhysicsObject::fixed() const
{
    return this->_fixed;
}


double PhysicsObject::get_cor() const
{
    return this->cor;
}

void PhysicsObject::set_cor(double _cor)
{
    this->cor = _cor;
}