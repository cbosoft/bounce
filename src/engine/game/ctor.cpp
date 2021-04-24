#include "game.hpp"

Game::Game()
  : should_quit(false)
  , physics(PhysicsEngine::ref())
  , renderer(Renderer::get())
{
    this->renderer.init(this, 1280, 960, "bounce");
}
