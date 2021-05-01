#include <bounce/game/game.hpp>

/**
 * Run the main game loop.
 *
 * Check that there are shaders loaded for the renderer, then run the main game loop. In order, the game loop consists
 * of rendering the scene (Renderer#render), then processing events (Game#logic_step), processing input
 * (InputManager#handle_input) and last (certainly not least) process physics (PhysicsEngine#timestep) - where objects
 * have collisions resolved and velocities/forces updated.
 */
void Game::run()
{
    this->renderer.check_shaders();
    while (!this->should_quit)
    {
        this->renderer.render();
        this->logic_step();
        InputManager::get_active()->handle_input();
        this->physics.timestep();
    }
}
