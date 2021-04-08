#include "game.hpp"

void Game::set_player(PhysicsObject *player)
{
    this->_player = player;
    this->camera->set_parent(player);
}

PhysicsObject *Game::get_player() const
{
    return this->_player;
}