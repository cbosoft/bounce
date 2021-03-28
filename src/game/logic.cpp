#include "game.hpp"

void Game::logic_step()
{
  this->camera_position = this->objects[0]->position;
}
