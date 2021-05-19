#include <bounce/physics/engine/engine.hpp>
#include <bounce/game/game.hpp>
#include <bounce/scene/scene.hpp>
#include <bounce/events.hpp>

PhysicsMaterial PhysicsEngine::get_overall_material_properties(const PhysicsMaterial &a, const PhysicsMaterial &b)
{
    return {
        (a.bounciness < b.bounciness ? a.bounciness : b.bounciness),
        (a.dynamic_friction > b.dynamic_friction ? a.dynamic_friction : b.dynamic_friction)
        };
}

void PhysicsEngine::resolve_collision(Object *a, Object *b, const arma::vec2 &normal)
{
    // If both are fixed, don't resolve collision
    bool afixed = a->fixed(), bfixed = b->fixed();

    // objects collide
    // TODO only run collision event if the collision is new
    Game::ref().add_event(new CollisionEvent(a, b));
    if (afixed || bfixed) {
        return this->resolve_collision_one_fixed(bfixed?a:b, bfixed?b:a, normal);
    }

    return this->resolve_collision_free_bodies(a, b, normal);
}

void PhysicsEngine::resolve_collision_one_fixed(Object *free_body, Object *fixed_body, const arma::vec2 &normal)
{
    const arma::vec &v = free_body->get_velocity() - fixed_body->get_velocity()*2.f;
    double nn = arma::dot(normal, normal);
    double vn = arma::dot(v, normal);
    arma::vec2 vel_parallel_to_norm = (vn/nn)*normal;
    arma::vec2 vel_perpendicular_to_norm = v - vel_parallel_to_norm;

    const PhysicsMaterial overall = PhysicsEngine::get_overall_material_properties(
            free_body->get_material(), fixed_body->get_material());
    free_body->set_velocity(((1. - overall.dynamic_friction)*vel_perpendicular_to_norm - overall.bounciness*vel_parallel_to_norm));
    free_body->set_new_position(free_body->get_velocity()*this->dt + free_body->get_position());
}

void PhysicsEngine::resolve_collision_free_bodies(Object *a, Object *b, const arma::vec2 &normal)
{
    if (normal.has_nan())
        throw std::runtime_error("nan in norm");
    // collision response - https://en.wikipedia.org/wiki/Collision_response
    // const double cor = PhysicsEngine::get_overall_cor(a->get_cor(), b->get_cor());
    // arma::vec2 relative_velocity = b->get_velocity() - a->get_velocity();
    // double vr_dot_n = arma::dot(relative_velocity, norm);
    // double impulse_magnitude_num = -(1 + cor)*vr_dot_n;

    // // inertia
    // arma::mat I = arma::eye(2, 2);
    // const arma::mat &I_inv = I; // only for identity

    // const arma::vec2 &p = this->_cached_collision.at;
    // arma::vec2 pa = p - a->get_new_position();
    // arma::vec2 pb = p - b->get_new_position();
    // arma::vec2 irnr_a = (I_inv*(pa*norm.t()))*pa;
    // arma::vec2 irnr_b = (I_inv*(pb*norm.t()))*pb;
    // arma::vec2 irnr = irnr_a+irnr_b;
    // double impulse_magnitude_den = 1./a->get_mass() + 1./b->get_mass() + arma::dot(irnr, norm);
    // double impulse_magnitude = impulse_magnitude_num/impulse_magnitude_den;
    // arma::vec2 impulse = impulse_magnitude*norm;

    arma::vec2 avel = a->get_velocity(), bvel = b->get_velocity();
    a->set_velocity( bvel*b->get_mass()/a->get_mass());
    b->set_velocity( avel*a->get_mass()/b->get_mass());

    a->set_new_position(a->get_velocity()*this->dt + a->get_position());
    b->set_new_position(b->get_velocity()*this->dt + b->get_position());
}

void PhysicsEngine::register_object(Object *obj)
{
    this->_all_objects.push_back(obj);
}

void PhysicsEngine::unregister_object(Object *obj)
{
    this->_all_objects.remove(obj);
}

void PhysicsEngine::traverse_get_objects(Transform *t, std::list<Object *> &out) const
{
    for (Transform *child : t->get_children()) {
        if (child->is_active()) {
            if (child->is_physics_object()) {
                out.push_back((Object *) child);
            }
            this->traverse_get_objects(child, out);
        }
    }
}

std::list<Object *> PhysicsEngine::get_active_objects() const
{
    Transform *root = Game::ref().get_active_scene();
    std::list<Object *> rv;
    this->traverse_get_objects(root, rv);
    return rv;
}