#include "engine.hpp"

PhysicsEngine::~PhysicsEngine()
{
    for (auto *field : this->fields) {
        delete field;
    }
}