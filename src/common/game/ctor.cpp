#include "game.hpp"

Game::Game(int w, int h)
  : should_quit(false)
  , physics(PhysicsEngine::engine())
  , renderer(Renderer::init(w, h, "bounce"))
{
    this->camera = &this->renderer.camera_transform;
}
