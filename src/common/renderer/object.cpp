#include "renderer.hpp"

void Renderer::add_object(PhysicsObject *object)
{
    this->objects.emplace_back(object);
}

void Renderer::remove_object(PhysicsObject *object)
{
    for (auto it = this->objects.begin(); it != this->objects.end(); it++) {
        PhysicsObject *ptr = *it;
        if (ptr == object)
            this->objects.erase(it);
    }
}