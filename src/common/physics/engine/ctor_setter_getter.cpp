#include "engine.hpp"

PhysicsEngine::PhysicsEngine(Game *game, double dt, double timescale)
    : game(game)
    , dt(dt)
    , time(0.0)
    , irl_time(0.0)
    , timescale(timescale)
{
    this->epoch = Clock::now();
}

double PhysicsEngine::get_time() const
{
    return this->time;
}

void PhysicsEngine::set_timescale(double v)
{
    this->timescale = v;
}

double PhysicsEngine::get_dt() const
{
    return this->dt;
}

