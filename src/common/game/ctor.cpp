#include "game.hpp"

Game::Game(int w, int h)
  : should_quit(false)
  , physics(PhysicsEngine::engine())
  , renderer(Renderer::init(w, h, "bounce"))
{
    // do nothing
}
