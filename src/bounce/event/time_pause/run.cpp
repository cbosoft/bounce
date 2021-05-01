#include <bounce/event/time_pause/time_pause.hpp>
#include <bounce/physics/engine/engine.hpp>
#include <bounce/game/game.hpp>

void TemporaryTimePause::run(Game *game)
{
    PhysicsEngine::ref().set_timescale(0.01);
    game->add_event(new DelayedUnPause(this->_ms));
}

void DelayedUnPause::run(Game *game)
{
    PhysicsEngine::ref().set_timescale(1.0);
}