#include <bounce/physics/engine/engine.hpp>

PhysicsEngine& PhysicsEngine::ref()
{
    static PhysicsEngine pe;
    return pe;
}
