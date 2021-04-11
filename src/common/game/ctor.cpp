#include "game.hpp"

Game::Game(int w, int h)
  : should_quit(false)
  , physics(PhysicsEngine::init_engine(this, 1e-3, 1.0))
  , renderer(Renderer::init(this, w, h, "bounce"))
  , active_scene(nullptr)
{
    // do nothing
}
