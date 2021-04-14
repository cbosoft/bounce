#include "transition.hpp"
#include "../../game/game.hpp"

void PopSceneTransitionEvent::run(Game *game)
{
    game->pop_active_scene();
}