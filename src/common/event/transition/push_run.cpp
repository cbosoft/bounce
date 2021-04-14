#include "transition.hpp"
#include "../../game/game.hpp"

void PushSceneTransitionEvent::run(Game *game)
{
    game->push_active_scene(this->_target_scene_name);
}