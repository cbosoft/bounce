#include "game.hpp"

void Game::add_object(PhysicsObject *obj)
{
    this->objects.push_back(obj);
    this->physics.add_object(obj);
    this->renderer.add_object(obj);
}