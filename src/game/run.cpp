#include "game.hpp"

void Game::run()
{
  while (!this->should_quit)
  {
    this->physics_step();
    this->render_step();
    this->input_step();
  }
}
