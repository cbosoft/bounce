#include "game.hpp"

void Game::add_object(Object *obj)
{
    this->all_objects.push_back(obj);
}