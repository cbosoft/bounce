#include "engine.hpp"
#include <iostream>

void PhysicsEngine::add_object(PhysicsObject *obj)
{
    this->objects.push_back(obj);
}

void PhysicsEngine::add_field(ForceField *forceField)
{
    std::cerr << "added_field\n";
    this->fields.push_back(forceField);
}

CollisionInformation &PhysicsEngine::resolve_collision(PhysicsObject *a, PhysicsObject *b)
{
    // If both are fixed, don't resolve collision
    if (a->fixed() && b->fixed()) {
        this->_cached_collision.happens = false;
        return this->_cached_collision;
    }

    if (!a->will_collide(b, this->_cached_collision.normal, this->_cached_collision.at)) {
        this->_cached_collision.happens = false;
        return this->_cached_collision;
    }
    else if (a->fixed() || b->fixed()) {
        return this->resolve_collision_one_fixed(b->fixed()?a:b);
    }

    return this->resolve_collision_free_bodies(a, b);
}

CollisionInformation &PhysicsEngine::resolve_collision_one_fixed(PhysicsObject *free_body)
{
    const arma::vec &norm = this->_cached_collision.normal;
    const arma::vec &v = free_body->velocity;
    double nn = arma::dot(norm, norm);
    double vn = arma::dot(v, norm);
    arma::vec2 vel_parallel_to_norm = (vn/nn)*norm;
    arma::vec2 vel_perpendicular_to_norm = v - vel_parallel_to_norm;

    free_body->velocity = vel_perpendicular_to_norm - vel_parallel_to_norm;
    free_body->new_position = free_body->velocity*this->dt + free_body->position;
    return this->_cached_collision;
}

CollisionInformation &PhysicsEngine::resolve_collision_free_bodies(PhysicsObject *a, PhysicsObject *b)
{
    // not yet implemented!
    (void) a;
    (void) b;
    return this->_cached_collision;
}