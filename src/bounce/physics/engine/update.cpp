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

    std::list<Object *> active_objects = this->get_active_objects();

    // resolve force fields acting on objects
    for (auto *obj : active_objects) {
        arma::vec2 f = obj->get_force();
        for (auto *field : scene->get_fields()) {
            f += field->measure_at(obj);
        }
        obj->set_force(f);
    }

    // Get proposed new positions for objects
    std::map<std::string, std::vector<Object *> > by_layer;
    for (auto *obj : active_objects) {
        obj->on_physics_update();
        obj->timestep(this->dt);
        by_layer[obj->get_layer()].emplace_back(obj);
    }

    // Check for and resolve any collisions
    for (const auto &kv : by_layer) {
        const auto &objs = kv.second;
        for (size_t i = 0; i < objs.size(); i++) {
            for (size_t j = 0; j < objs.size(); j++) {
                if (j >= i) break;
                this->resolve_collision(objs[i], objs[j]);
            }
        }
    }

    // Accept resolved positions; zero forces
    for (auto *obj : active_objects) {
        obj->accept_position();
        obj->set_force({0, 0});
    }
}

