#include "game.hpp"

void Game::run()
{
  while (!this->should_quit)
  {
    this->physics.timestep();
    this->logic_step();
    this->renderer.render();
    this->input_step();
  }
}

void Game::quit()
{
  this->should_quit = true;
}
