#include "time_pause.hpp"
#include "../../physics/engine/engine.hpp"
#include "../../game/game.hpp"

void TemporaryTimePause::run(Game *game)
{
    PhysicsEngine::ref().set_timescale(0.01);
    game->add_event(new DelayedUnPause(this->_ms));
}

void DelayedUnPause::run(Game *game)
{
    PhysicsEngine::ref().set_timescale(1.0);
}