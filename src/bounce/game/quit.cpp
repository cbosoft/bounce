#include <bounce/game/game.hpp>
#include <bounce/logging/logger.hpp>

/**
 * Set quit flag. This will cause a running game to exit the run loop.
 */
void Game::quit()
{
    this->should_quit = true;
    Logger::ref() << LL_INFO << "Quit flag set, quit pending...\n";
}
