#include "game.hpp"

void Game::render_step()
{
  SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(this->renderer);
  SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawLine(this->renderer, 320, 200, 300, 240);
  SDL_RenderPresent(this->renderer);
}
