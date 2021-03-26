#include "game.hpp"

void Game::input_step()
{

  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    switch (e.type) {
      case SDL_QUIT:
        this->should_quit = true;
        break;

      case SDL_KEYDOWN:
        this->keydown(e.key.keysym.scancode);
        break;
    }
  }

}

void Game::keydown(SDL_Scancode scancode)
{
  switch (scancode)
  {
    case SDL_SCANCODE_ESCAPE:
      this->should_quit = true;
      break;

    default:
      break;
  }
}
