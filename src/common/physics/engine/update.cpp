#include <iostream>
#include <armadillo>
#include "engine.hpp"


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

    // resolve force fields acting on objects
    for (auto *obj : this->objects) {
        for (auto *field : this->fields) {
            obj->set_force(obj->get_force() + field->measure_at(obj->get_position()));
        }
    }

    // Get proposed new positions for objects
    for (auto *obj : this->objects) {
        obj->timestep(this->dt);
    }

    // Check for an resolve any collisions
    for (size_t i = 0; i < this->objects.size(); i++) {
        for (size_t j = 0; j < this->objects.size(); j++) {
            if (j >= i) break;
            this->resolve_collision(this->objects[i], this->objects[j]);
        }
    }

    // Accept resolved positions; zero forces
    for (auto *obj : this->objects) {
        obj->accept_position();
        obj->set_force({0, 0});
    }
}

