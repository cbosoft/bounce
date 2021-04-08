#include "game.hpp"

Game::~Game()
{
  for (auto *object : this->objects)
      delete object;
}
