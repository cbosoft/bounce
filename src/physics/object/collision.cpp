#include "object.hpp"

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
