#include "object.hpp"

void PhysicsObject::accept_position()
{
    this->set_position(this->new_position);
}

bool PhysicsObject::will_collide(const PhysicsObject *other, arma::vec2 &norm, arma::vec2 &at) const
{
    for (auto *eqn : this->get_shape()) {
        for (auto *oeqn : other->get_shape()) {
            if (eqn->intersects(*oeqn, norm, at)) {
                return true;
            }
        }
    }
    return false;
}
