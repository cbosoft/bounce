#include "engine.hpp"

static PhysicsEngine *engine_singleton = nullptr;

PhysicsEngine &PhysicsEngine::init_engine(double dt, double timescale)
{
    engine_singleton = new PhysicsEngine(dt, timescale);
    return *engine_singleton;
}

PhysicsEngine& PhysicsEngine::engine()
{
    if (!engine_singleton)
        throw std::runtime_error("PhysicsEngine::init_engine() must be called before PhysicsEngine::engine()");
    return *engine_singleton;
}
