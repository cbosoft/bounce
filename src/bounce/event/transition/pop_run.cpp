#include <bounce/event/transition/transition.hpp>
#include <bounce/game/game.hpp>

void PopSceneTransitionEvent::run(Game *game)
{
    game->pop_active_scene();
}