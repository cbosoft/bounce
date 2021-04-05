#include "game.hpp"

Game::~Game()
{
  if (this->renderer)
    SDL_DestroyRenderer(this->renderer);

  if (this->win)
    SDL_DestroyWindow(this->win);

  SDL_Quit();

  for (auto *object : this->objects)
      delete object;
}
