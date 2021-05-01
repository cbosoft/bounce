#include <bounce/game/game.hpp>

/**
 * Get return the input context (scene) at the top of the current stack. That is, the currently active scene.
 * @return Currently active Scene ptr, cast to InputContext ptr.
 */
InputContext *Game::get_context() const
{
    return this->get_active_scene();
}