#include "object.hpp"

void PhysicsObject::timestep(double dt)
{
    if (this->_fixed)
        return;

    this->velocity += this->inv_mass*dt*this->force;
    this->new_position = this->get_position() + this->velocity*dt;
}