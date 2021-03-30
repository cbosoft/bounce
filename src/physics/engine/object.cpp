#include "engine.hpp"

void PhysicsEngine::add_object(PhysicsObject *obj)
{
    this->objects.push_back(obj);
}