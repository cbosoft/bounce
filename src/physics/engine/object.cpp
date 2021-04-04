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
    const arma::vec &v = free_body->get_velocity();
    double nn = arma::dot(norm, norm);
    double vn = arma::dot(v, norm);
    arma::vec2 vel_parallel_to_norm = (vn/nn)*norm;
    arma::vec2 vel_perpendicular_to_norm = v - vel_parallel_to_norm;

    free_body->set_velocity(vel_perpendicular_to_norm - vel_parallel_to_norm);
    free_body->set_new_position(free_body->get_velocity()*this->dt + free_body->get_position());

    return this->_cached_collision;
}

CollisionInformation &PhysicsEngine::resolve_collision_free_bodies(PhysicsObject *a, PhysicsObject *b)
{
    // collision response - https://en.wikipedia.org/wiki/Collision_response
    double cor = 1.0;
    arma::vec2 relative_velocity = b->get_velocity() - a->get_velocity();
    const arma::vec2 &norm = -this->_cached_collision.normal;
    if (norm.has_nan())
      throw std::runtime_error("nan in norm");
    double vr_dot_n = arma::dot(relative_velocity, norm);
    double impulse_magnitude_num = -(1 + cor)*vr_dot_n;

    // inertia
    arma::mat I = arma::eye(2, 2);
    arma::mat I_inv = I; // only for identity

    const arma::vec2 &p = this->_cached_collision.at;
    arma::vec2 pa = p - a->get_new_position();
    arma::vec2 pb = p - b->get_new_position();
    arma::vec2 irnr_a = (I_inv*(pa*norm.t()))*pa;
    arma::vec2 irnr_b = (I_inv*(pb*norm.t()))*pb;
    arma::vec2 irnr = irnr_a+irnr_b;
    double impulse_magnitude_den = 1./a->get_mass() + 1./b->get_mass() + arma::dot(irnr, norm);
    double impulse_magnitude = impulse_magnitude_num/impulse_magnitude_den;
    arma::vec2 impulse = impulse_magnitude*norm;

    a->set_velocity(a->get_velocity() - impulse/a->get_mass());
    b->set_velocity(b->get_velocity() + impulse/b->get_mass());

    a->set_new_position(a->get_velocity()*this->dt + a->get_position());
    b->set_new_position(b->get_velocity()*this->dt + b->get_position());

    return this->_cached_collision;
}
