#include "engine.hpp"

PhysicsEngine& PhysicsEngine::engine()
{
    static PhysicsEngine pe(1e-4);
    return pe;
}
