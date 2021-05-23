#include <armadillo>
#include <map>

#include <bounce/game/game.hpp>
#include <bounce/physics/engine/engine.hpp>
#include <bounce/scene/scene.hpp>


void PhysicsEngine::check_set_time()
{
    Duration d = Clock::now() - this->epoch;
    this->irl_time = d.count();
}

void PhysicsEngine::timestep()
{
    this->check_set_time();
    while (this->time < this->irl_time) {
        this->timestep_objects();
    }
}

void PhysicsEngine::timestep_objects()
{
    this->time += this->dt/this->timescale;
    auto *scene = Game::ref().get_active_scene();

    // No active scene; don't run physics
    if (!scene)
        return;

    std::list<Collider *> colliders;
    scene->find_in_children_cast("collider", colliders);
    std::list<Rigidbody *> rigidbodies;
    for (Collider * collider : colliders) {
        if (collider->is_a("rigidbody")) {
            rigidbodies.push_back((Rigidbody *)collider);
        }
    }

    // resolve force fields acting on objects
    for (auto *rb : rigidbodies) {
        arma::vec2 f = rb->get_force();
        for (auto *field : scene->get_fields()) {
            f += field->measure_at(rb);
        }
        rb->set_force(f);
    }

    // Get proposed new positions for objects
    for (auto *rb : rigidbodies) {
        rb->on_physics_update();
        rb->timestep_force(this->dt);
    }

    // Check for and resolve any collisions
    int i = 0, j = 0;
    for (auto *a : rigidbodies) {
        CollisionInformation next_collision = {nullptr, {0, 0}, {0, 0}, 1e9, CD_LEFT, CD_LEFT};

        j = 0;
        for (auto *b : rigidbodies) {
            if (j >= i) break;
            CollisionInformation ci = {b, {0, 0}, {0, 0}, 1e9, CD_LEFT, CD_RIGHT};
            if (this->check_will_collide(a, b, ci)) {
                if (ci.when < next_collision.when) {
                    next_collision = ci;
                }
            }

            j++;
        }
        if (next_collision.b) {
            a->set_touching(next_collision.adir);
            next_collision.b->set_touching(next_collision.bdir);
            this->resolve_collision(a, next_collision.b, next_collision.normal);
        }

        i++;
    }

    // Accept resolved positions; zero forces
    for (auto *rb : rigidbodies) {
        rb->timestep_velocity(this->dt);
        rb->set_force({0, 0});
    }
}

