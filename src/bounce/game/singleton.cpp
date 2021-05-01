#include <bounce/game/game.hpp>

/**
 * @return Reference to Game singleton.
 */
Game &Game::ref()
{
    static Game game;
    return game;
}