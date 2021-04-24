#include "game.hpp"

void Game::run()
{
    this->renderer.check_shaders();
    while (!this->should_quit)
    {
        this->logic_step();
        this->renderer.render();
        InputManager::get_active(this)->handle_input();
        this->physics.timestep();
    }
}
