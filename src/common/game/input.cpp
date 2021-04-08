#include "game.hpp"

InputContext *Game::get_context() const
{
    return this->context;
}

void Game::quit()
{
    this->should_quit = true;
}
