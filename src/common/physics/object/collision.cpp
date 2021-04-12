#include "object.hpp"

void PhysicsObject::accept_position()
{
    if (!this->fixed())
        this->set_position(this->new_position);
}

bool PhysicsObject::will_collide_with(const PhysicsObject *other)
{
    arma::vec2 dp = other->get_new_position() - this->get_new_position();
    double dist = arma::norm(dp);
    double tdist = other->get_radius() + this->get_radius() + PhysicsObject::COLLISION_THRESH;
    return dist <= tdist;
}

bool PhysicsObject::will_collide_with(const PhysicsObject *other, arma::vec2 &normal)
{
    arma::vec2 dummy;
    return this->will_collide_with(other, normal, dummy);
}

bool PhysicsObject::will_collide_with(const PhysicsObject *other, arma::vec2 &normal, arma::vec2 &at)
{
    arma::vec2 dp = other->get_new_position() - this->get_new_position();
    double dist = arma::norm(dp);
    double tdist = other->get_radius() + this->get_radius() + PhysicsObject::COLLISION_THRESH;
    if (dist <= tdist) {
        normal = arma::normalise(dp);
        at = this->get_position() + normal*this->_radius;
        return true;
    }

    return false;
}
