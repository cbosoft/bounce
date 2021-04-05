#include "game.hpp"

void Game::input_step()
{

  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    switch (e.type) {
      case SDL_QUIT:
        this->quit();
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
      this->quit();
      break;

    default:
      break;
  }
}
