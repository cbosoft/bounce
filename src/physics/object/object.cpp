#include <iostream>
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

const arma::vec2 &PhysicsObject::get_position() const
{
    return this->position;
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

const std::vector<GeometricEquation *> &PhysicsObject::get_equations() const
{
    return this->eqns;
}



void PhysicsObject::timestep(double dt)
{
  if (this->_fixed)
    return;

  this->velocity += this->inv_mass*dt*this->force;
  this->new_position = this->position + this->velocity*dt;
}

void PhysicsObject::accept_position()
{
  this->position = this->new_position;
}

bool PhysicsObject::will_collide(const PhysicsObject *other, arma::vec2 &norm, arma::vec2 &at) const
{
  for (auto *eqn : this->eqns) {
    for (auto *oeqn : other->eqns) {
      if (eqn->intersects(*oeqn, norm, at))
        return true;
    }
  }
  return false;
}

bool PhysicsObject::fixed() const
{
  return this->_fixed;
}

void PhysicsObject::add_geometry(GeometricEquation *eqn)
{
  if (eqn == nullptr)
    return;

  eqn->p = &this->new_position;
  this->eqns.push_back(eqn);
}

void PhysicsObject::add_geometry(std::vector<GeometricEquation *> eqns)
{
  for (auto *eqn : eqns) {
    this->add_geometry(eqn);
  }
}
