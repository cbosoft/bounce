#include "game.hpp"

void Game::run()
{
  while (!this->should_quit)
  {
    this->physics_step();
    this->logic_step();
    this->render_step();
    this->input_step();
  }
}

void Game::quit()
{
  this->should_quit = true;
}
