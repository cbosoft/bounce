#include "engine.hpp"

PhysicsEngine::PhysicsEngine(double dt)
    : dt(dt)
    , time(0.0)
    , timescale(1.0)
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

