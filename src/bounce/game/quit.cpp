#include <bounce/game/game.hpp>

/**
 * Set quit flag. This will cause a running game to exit the run loop.
 */
void Game::quit()
{
    this->should_quit = true;
}
