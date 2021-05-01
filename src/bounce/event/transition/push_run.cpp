#include <bounce/event/transition/transition.hpp>
#include <bounce/game/game.hpp>

void PushSceneTransitionEvent::run(Game *game)
{
    game->push_active_scene(this->_target_scene_name);
}