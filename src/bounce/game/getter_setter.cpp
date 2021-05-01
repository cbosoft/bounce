#include <bounce/game/game.hpp>

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

void Game::set_name(const std::string &name)
{
    this->_name = name;
}

const std::string &Game::get_name() const
{
    return this->_name;
}