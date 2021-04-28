#include "game.hpp"

void Game::show_colliders()
{
    this->_visible_colliders = true;
}

void Game::hide_colliders()
{
    this->_visible_colliders = false;
}

bool Game::should_show_colliders() const
{
    return this->_visible_colliders;
}