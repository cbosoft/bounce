#include "game.hpp"

Game::Game(int w, int h)
  : should_quit(false)
  , physics(PhysicsEngine::init_engine(this, 5e-3, 1.0))
  , renderer(Renderer::get())
{
    // do nothing
    this->renderer.init(this, w, h, "bounce");
}
