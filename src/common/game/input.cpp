#include "game.hpp"

InputContext *Game::get_context() const
{
    return this->active_scene;
}

void Game::quit()
{
    this->should_quit = true;
}
