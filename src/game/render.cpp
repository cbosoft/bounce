#include "game.hpp"

void Game::render_init()
{
  if (SDL_Init(SDL_INIT_EVERYTHING)) {
    throw std::runtime_error(SDL_GetError());
  }

  if (SDL_CreateWindowAndRenderer(this->w, this->h, 0, &this->win, &this->renderer)) {
    throw std::runtime_error(SDL_GetError());
  }
}

void Game::render_step()
{
  SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(this->renderer);
  SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawLine(this->renderer, 300, 220, 340, 260);
  SDL_RenderDrawLine(this->renderer, 340, 220, 300, 260);
  SDL_RenderPresent(this->renderer);
}
