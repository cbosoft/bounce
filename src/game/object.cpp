#include "game.hpp"

void Game::add_object(PhysicsObject *obj)
{
    this->objects.push_back(obj);
    PhysicsEngine::engine().add_object(obj);
}