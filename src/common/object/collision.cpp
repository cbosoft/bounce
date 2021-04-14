#include "object.hpp"

void Object::accept_position()
{
    if (!this->fixed())
        this->set_position(this->new_position);
}

bool Object::will_collide_with(const Object *other)
{
    arma::vec2 dp = other->get_new_position() - this->get_new_position();
    double dist = arma::norm(dp);
    double tdist = other->get_radius() + this->get_radius() + Object::COLLISION_THRESH;
    return dist <= tdist;
}

bool Object::will_collide_with(const Object *other, arma::vec2 &normal)
{
    arma::vec2 dummy;
    return this->will_collide_with(other, normal, dummy);
}

bool Object::will_collide_with(const Object *other, arma::vec2 &normal, arma::vec2 &at)
{
    arma::vec2 dp = other->get_new_position() - this->get_new_position();
    double dist = arma::norm(dp);
    double tdist = other->get_radius() + this->get_radius() + Object::COLLISION_THRESH;
    if (dist <= tdist) {
        normal = arma::normalise(dp);
        at = this->get_position() + normal*this->_radius;
        return true;
    }

    return false;
}

void Object::run_collision(Object *other)
{
    if (this->_collision_callback)
        this->_collision_callback(this, other);
}

void Object::set_collision_callback(collision_callback cb)
{
    this->_collision_callback = cb;
}