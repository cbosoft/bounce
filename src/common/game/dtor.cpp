#include "game.hpp"

Game::~Game()
{
  for (auto *object : this->all_objects)
      delete object;
}
