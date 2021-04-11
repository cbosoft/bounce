#include "game.hpp"

void Game::add_object(PhysicsObject *obj)
{
    this->all_objects.push_back(obj);
}