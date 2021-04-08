#include "game.hpp"

void Game::run()
{
  while (!this->should_quit)
  {
    this->physics.timestep();
    this->logic_step();
    this->renderer.render();
    InputManager::get_active(this)->handle_input();
  }
}
