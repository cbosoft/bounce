#include <bounce/physics/rigidbody/rigidbody.hpp>

void Rigidbody::timestep_force(double dt)
{
    if (!this->_fixed) {
        this->_velocity += this->_inv_mass*dt*this->_force;
    }
}

void Rigidbody::timestep_velocity(double dt)
{
    arma::vec2 dv = this->_velocity - this->_previous_velocity;
    this->set_relative_position(this->get_relative_position() + this->_velocity*dt + dv*dt*.5);
    this->_previous_velocity = this->_velocity;
}
