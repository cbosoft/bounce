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