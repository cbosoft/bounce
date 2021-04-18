#include "game.hpp"

Game::Game()
  : should_quit(false)
  , physics(PhysicsEngine::init_engine(this, 1e-3, 1.0))
  , renderer(Renderer::get())
{
    this->renderer.init(this, 1280, 960, "bounce");
}
