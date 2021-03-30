#include <iostream>
#include "object.hpp"

PhysicsObject::PhysicsObject(arma::vec2 position, bool fixed)
  : position(position)
  , new_position(position)
  , velocity({0, 0})
  , _fixed(fixed)
{
    this->set_mass(1.0);
}

PhysicsObject::PhysicsObject(arma::vec2 position, double mass)
  : position(position)
  , new_position(position)
  , velocity({0, 0})
  , _fixed(false)
{
    this->set_mass(mass);
}

void PhysicsObject::set_mass(double mass)
{
    this->mass = mass;
    this->inv_mass = 1./mass;
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

bool PhysicsObject::will_collide(const PhysicsObject *other, arma::vec2 &norm) const
{
  for (auto *eqn : this->eqns) {
    for (auto *oeqn : other->eqns) {
      if (eqn->intersects(*oeqn, norm))
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
