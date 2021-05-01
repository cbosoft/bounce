#include <bounce/game/game.hpp>
#include <bounce/scene/scene.hpp>

/**
 * Game object destructor.
 *
 * Clean up pointers owned by game - Event ptrs and Scene ptrs.
 */
Game::~Game()
{
    for (Event *event : this->events) {
        delete event;
    }

    for (auto &kv : this->scenes_by_name) {
        delete kv.second;
    }
}
