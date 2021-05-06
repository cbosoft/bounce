#include <bounce/object/object.hpp>

void Object::timestep(double dt)
{
    if (!this->_fixed) {
        this->velocity += this->inv_mass*dt*this->force;
    }

    this->new_position = this->get_position() + this->velocity*dt;
}
