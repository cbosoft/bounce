#include "game.hpp"

void Game::run()
{
  while (!this->should_quit)
  {
    PhysicsEngine::engine().timestep();
    this->logic_step();
    this->render_step();
    this->input_step();
  }
}

void Game::quit()
{
  this->should_quit = true;
}
